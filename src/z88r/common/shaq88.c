/************************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows
* and UNIX OS.
*
* Composed and edited and copyright by 
* Professor Dr.-Ing. Frank Rieg, University of Bayreuth, Germany
*
* eMail: 
* frank.rieg@uni-bayreuth.de
* dr.frank.rieg@t-online.de
* 
* V15.0 November 18, 2015
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; see the file COPYING.  If not, write to
* the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
***********************************************************************/ 
/***********************************************************************
* diese Compilerunit umfasst: shaq88 - Elementsteifigkeitsroutine
*                             qq88   - Berechnung der Matrix b
* diese Compilerunit enthaelt Routinen, die gedanklich an FORTRAN-
* Quellen von H.J.Bathe, MIT, Cambridge, MA, USA angelehnt sind.
* 17.7.2011 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <stdio.h>
#endif

/***********************************************************************
* Fuer Windows & GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88r.h>
#include <stdio.h>
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int qq88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s,FR_DOUBLE *t);

/***********************************************************************
* hier beginnt Function shac88
***********************************************************************/
int shaq88(void)
{
extern FR_DOUBLEAY se;

extern FR_DOUBLE xk[],yk[],zk[];
extern FR_DOUBLE b[],xx[],d[];

extern FR_DOUBLE emode,rnuee;

extern FR_INT4 intore;

FR_DOUBLE db[7];

FR_DOUBLE r,s,t,det,wt,stiff;
FR_DOUBLE f0,f1,f2;

FR_INT4 ne= 48,i,lx,ly,lz,j,k,l,intor_t;

int iret;
  
/*----------------------------------------------------------------------
* Gauss-Legendre Stuetzstellen
*---------------------------------------------------------------------*/
static FR_DOUBLE xg[17]= { 0.,
   0., -.5773502691896, -.7745966692415, -.8611363115941,
   0., +.5773502691896,              0., -.3399810435849,
   0.,              0., +.7745966692415, +.3399810435849,
   0.,              0.,              0., +.8611363115941 };

/*----------------------------------------------------------------------
* Gauss-Legendre Integrationsgewichte
*---------------------------------------------------------------------*/
static FR_DOUBLE wgt[17]= { 0.,
   2.,              1., +.5555555555556, +.3478548451375,
   0.,              1., +.8888888888889, +.6521451548625,
   0.,              0., +.5555555555556, +.6521451548625,
   0.,              0.,              0., +.3478548451375 };

/*----------------------------------------------------------------------
* xk und yk umspeichern
*---------------------------------------------------------------------*/
for(i = 1;i <= 16;i++)
  {
  xx[i]   = xk[i];
  xx[16+i]= yk[i];
  xx[32+i]= zk[i];
  }

/*----------------------------------------------------------------------
* Materialkonstanten
*---------------------------------------------------------------------*/
f0= emode*(1.-rnuee) / ((1.+rnuee)*(1.-2.*rnuee));

f1= rnuee/(1.-rnuee) * f0;
f2= (1.-2.*rnuee) / (2.*(1.-rnuee)) * f0;

/*----------------------------------------------------------------------
* Elastizitaetsmatrix aufstellen
*---------------------------------------------------------------------*/
for(i = 1;i <= 36;i++)
  d[i]= 0.;

d[1] = f0; 
d[7] = f1;
d[13]= f1; 
d[2] = f1;
d[8] = f0; 
d[14]= f1; 
d[3] = f1; 
d[9] = f1; 
d[15]= f0; 
d[22]= f2;
d[29]= f2;
d[36]= f2;

/*----------------------------------------------------------------------
* Elementsteifigkeitsmatrix aufstellen
*---------------------------------------------------------------------*/
intor_t= 2;

for(i = 1;i <= 2304;i++)  /* 48 x 48 */
  se[i]= 0.;

for(lx = 1;lx <= intore;lx++) 
  {
  r= xg[(lx-1)*4 + intore];
  for(ly = 1;ly <= intore;ly++)
    {
    s= xg[(ly-1)*4 + intore];
    for(lz = 1;lz <= intor_t;lz++)
      {
      t= xg[(lz-1)*4 + intor_t];
      
/*======================================================================
* Matrix b der partiellen Ableitungen & Jacobi Determinante holen
*=====================================================================*/
      iret= qq88(&det,&r,&s,&t);
      if(iret != 0) return(iret);
    
      wt= wgt[(lx-1)*4 + intore]  * 
          wgt[(ly-1)*4 + intore]  * 
          wgt[(lz-1)*4 + intor_t] * det;

      for(j = 1;j <= 48;j++)
        {
        for(k = 1;k <= 6;k++) 
          {
          db[k]= 0.;
          for(l = 1;l <= 6;l++) 
            {
            db[k]= db[k] + d[(k-1)*6 + l] * b[(l-1)*48 + j];
            } 
          }  
 
        for(i = j;i <= 48;i++) 
          {
          stiff= 0.;
          for(l = 1;l <= 6;l++) 
            {
            stiff+= b[(l-1)*48 + i] * db[l];
            }   
          se[i+ne*(j-1)]= se[i+ne*(j-1)] + stiff * wt;
          } 
        }
      } 
    } 
  } 

for(j = 1;j <= 48;j++)
  {  
  for(i = j;i <= 48;i++)
    {
    se[j+ne*(i-1)]= se[i+ne*(j-1)];
    } 
  } 

return(0);
}

/***********************************************************************
* hier beginnt Function qq88
***********************************************************************/
int qq88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s,FR_DOUBLE *t)
{
/*---------------------------------------------------------------------
* xx geht rein, unveraendert (ex)
* b  geht raus, neu (ex)
* det geht raus, neu
* r,s,t gehen rein, unveraendert
*--------------------------------------------------------------------*/

extern FR_DOUBLE b[],xx[],h[],p[];

FR_DOUBLE xj[10], xji[10];              /* ist 3x3 +1 */

FR_DOUBLE rp,sp,rm,sm,rqm,sqm,r2,s2,dum,ept,emt;
        
FR_INT4 i,j,k,k3;
        
/*----------------------------------------------------------------------
* Klammern der Formfunktionen belegen
*---------------------------------------------------------------------*/
rp=  1. + (*r);
sp=  1. + (*s);
rm=  1. - (*r);
sm=  1. - (*s);
rqm= 1. - (*r)*(*r);
sqm= 1. - (*s)*(*s);
r2=  2. * (*r);
s2=  2. * (*s);
ept= 0.5* (1. + (*t));
emt= 0.5* (1. - (*t));

/*----------------------------------------------------------------------
* Formfunktionen obere und untere Ebene
*---------------------------------------------------------------------*/
h[ 1]= .25 * (rp*sp - rqm*sp - sqm*rp) * ept;
h[ 2]= .25 * (rm*sp - rqm*sp - sqm*rm) * ept;
h[ 3]= .25 * (rm*sm - sqm*rm - rqm*sm) * ept;
h[ 4]= .25 * (rp*sm - rqm*sm - sqm*rp) * ept;
h[ 5]= .5 * rqm * sp * ept;
h[ 6]= .5 * sqm * rm * ept;
h[ 7]= .5 * rqm * sm * ept;
h[ 8]= .5 * sqm * rp * ept;

h[ 9]= .25 * (rp*sp - rqm*sp - sqm*rp) * emt;
h[10]= .25 * (rm*sp - rqm*sp - sqm*rm) * emt;
h[11]= .25 * (rm*sm - sqm*rm - rqm*sm) * emt;
h[12]= .25 * (rp*sm - rqm*sm - sqm*rp) * emt;
h[13]= .5 * rqm * sp * emt;
h[14]= .5 * sqm * rm * emt;
h[15]= .5 * rqm * sm * emt;
h[16]= .5 * sqm * rp * emt;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach r
*---------------------------------------------------------------------*/
p[ 1]= .25 * (sp + r2*sp -sqm) * ept;
p[ 2]= .25 * ((-sp) + r2*sp + sqm) * ept;
p[ 3]= .25 * ((-sm) + sqm + r2*sm) * ept;
p[ 4]= .25 * (sm + r2*sm - sqm) * ept;
p[ 5]= .5 * (-r2)*sp * ept;
p[ 6]= (-.5 ) * sqm * ept;
p[ 7]= .5 * (-r2) * sm * ept;
p[ 8]= .5 * sqm * ept;

p[ 9]= .25 * (sp + r2*sp -sqm) * emt;
p[10]= .25 * ((-sp) + r2*sp + sqm) * emt;
p[11]= .25 * ((-sm) + sqm + r2*sm) * emt;
p[12]= .25 * (sm + r2*sm - sqm) * emt;
p[13]= .5 * (-r2)*sp * emt;
p[14]= (-.5 ) * sqm * emt;
p[15]= .5 * (-r2) * sm * emt;
p[16]= .5 * sqm * emt;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach s
*---------------------------------------------------------------------*/
p[17]= .25 * (rp - rqm + s2*rp) * ept;
p[18]= .25 * (rm - rqm + s2*rm) * ept;
p[19]= .25 * ((-rm) + s2*rm + rqm) * ept;
p[20]= .25 * ((-rp) + rqm + s2*rp) * ept;
p[21]= .5 * rqm * ept;
p[22]= .5 * (-s2) * rm * ept;
p[23]= (-.5 ) * rqm * ept;
p[24]= .5 * (-s2) * rp * ept;

p[25]= .25 * (rp - rqm + s2*rp) * emt;
p[26]= .25 * (rm - rqm + s2*rm) * emt;
p[27]= .25 * ((-rm) + s2*rm + rqm) * emt;
p[28]= .25 * ((-rp) + rqm + s2*rp) * emt;
p[29]= .5 * rqm * emt;
p[30]= .5 * (-s2) * rm * emt;
p[31]= (-.5 ) * rqm * emt;
p[32]= .5 * (-s2) * rp * emt;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach t
*---------------------------------------------------------------------*/
p[33]= .25 * (rp*sp - rqm*sp - sqm*rp) * 0.5;
p[34]= .25 * (rm*sp - rqm*sp - sqm*rm) * 0.5;
p[35]= .25 * (rm*sm - sqm*rm - rqm*sm) * 0.5;
p[36]= .25 * (rp*sm - rqm*sm - sqm*rp) * 0.5;
p[37]= .5 * rqm * sp * 0.5;
p[38]= .5 * sqm * rm * 0.5;
p[39]= .5 * rqm * sm * 0.5;
p[40]= .5 * sqm * rp * 0.5;

p[41]= .25 * (rp*sp - rqm*sp - sqm*rp) * -0.5;
p[42]= .25 * (rm*sp - rqm*sp - sqm*rm) * -0.5;
p[43]= .25 * (rm*sm - sqm*rm - rqm*sm) * -0.5;
p[44]= .25 * (rp*sm - rqm*sm - sqm*rp) * -0.5;
p[45]= .5 * rqm * sp * -0.5;
p[46]= .5 * sqm * rm * -0.5;
p[47]= .5 * rqm * sm * -0.5;
p[48]= .5 * sqm * rp * -0.5;

/*----------------------------------------------------------------------
* Jacobi-Matrix am Punkt (r,s,t) entwickeln
*---------------------------------------------------------------------*/
for(i = 1;i <= 3;i++)
  {
  for(j = 1;j <= 3;j++)
    {
    dum= 0.;
    for(k = 1;k <= 16;k++)
      {
      dum+= p[(i-1)*16 + k] * xx[(j-1)*16 + k];
      }
    xj[(i-1)*3 + j]= dum;
    }
  }

/*----------------------------------------------------------------------
* Jacobi-Determinante am Punkt (r,s,t) entwickeln
*---------------------------------------------------------------------*/
(*det)= (xj[1] * xj[5] * xj[9]) - (xj[1] * xj[6] * xj[8]) +
        (xj[2] * xj[6] * xj[7]) - (xj[2] * xj[4] * xj[9]) +
        (xj[3] * xj[4] * xj[8]) - (xj[3] * xj[5] * xj[7]);

if(FR_FABS(*det) < 0.00000000001)
  {
  return(AL_JACNEG);
  }

/*----------------------------------------------------------------------
* Berechnung der inversen Jacobi-Matrix
*---------------------------------------------------------------------*/
dum= 1./(*det);

xji[1]=  (xj[5] * xj[9] - xj[8] * xj[6])*dum;
xji[2]= -(xj[2] * xj[9] - xj[8] * xj[3])*dum;
xji[3]=  (xj[2] * xj[6] - xj[5] * xj[3])*dum;
xji[4]= -(xj[4] * xj[9] - xj[7] * xj[6])*dum;
xji[5]=  (xj[1] * xj[9] - xj[7] * xj[3])*dum;
xji[6]= -(xj[1] * xj[6] - xj[4] * xj[3])*dum;
xji[7]=  (xj[4] * xj[8] - xj[7] * xj[5])*dum;
xji[8]= -(xj[1] * xj[8] - xj[7] * xj[2])*dum;
xji[9]=  (xj[1] * xj[5] - xj[4] * xj[2])*dum;

/*----------------------------------------------------------------------
* Entwickeln der Matrix b
*---------------------------------------------------------------------*/
for(i = 1;i <= 288;i++)  /* 16 Knoten * 3 FG * 6 */
  b[i]= 0.;

k3= 0;

for(k = 1;k <= 16;k++)
  {
  k3+= 3;

  for(i = 1;i <= 3;i++)
    {
    b[     k3-2]= b[     k3-2] + xji[    i] * p[(i-1)*16 + k];
    b[48 + k3-1]= b[48 + k3-1] + xji[3 + i] * p[(i-1)*16 + k];
    b[96 + k3  ]= b[96 + k3  ] + xji[6 + i] * p[(i-1)*16 + k];
    }
  b[144 + k3-2]= b[48 + k3-1];
  b[144 + k3-1]= b[     k3-2];
            
  b[192 + k3-1]= b[96 + k3  ];
  b[192 + k3  ]= b[48 + k3-1];

  b[240 + k3-2]= b[96 + k3  ];
  b[240 + k3  ]= b[     k3-2];
  }

return(0);
}

