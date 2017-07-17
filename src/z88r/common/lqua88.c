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
* Z88 should compile and run under any Windows OS and UNIX OS and 
* GTK+.
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
* diese Compilerunit umfasst: lqua88 - Elementsteifigkeitsroutine
*                             lb88   - Berechnung der Matrix b
* diese Compilerunit enthaelt Routinen, die gedanklich an FORTRAN-
* Quellen von H.J.Bathe, MIT, Cambridge, MA, USA angelehnt sind.
* 2.1.2010 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#endif

/***********************************************************************
* Fuer Windows & GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88r.h>
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int lb88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s,FR_DOUBLE *t);

/***********************************************************************
* hier beginnt Function lqua88
***********************************************************************/
int lqua88(void)
{
extern FR_DOUBLEAY se;

extern FR_DOUBLE xk[],yk[],zk[];
extern FR_DOUBLE b[],xx[],d[];

extern FR_DOUBLE emode,rnuee;

extern FR_INT4 intore;

FR_DOUBLE db[7];

FR_DOUBLE r,s,t,det,wt,stiff;
FR_DOUBLE f0,f1,f2;

FR_INT4 ne= 24,i,lx,ly,lz,j,k,l;

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
for(i = 1;i <= 8;i++)
  {
  xx[i]   = xk[i];
  xx[8 +i]= yk[i];
  xx[16+i]= zk[i];
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
for(i = 1;i <= 576;i++)
  se[i]= 0.;

for(lx = 1;lx <= intore;lx++)                              /* 120 */
  {
  r= xg[(lx-1)*4 + intore];
  for(ly = 1;ly <= intore;ly++)                            /* 110 */
    {
    s= xg[(ly-1)*4 + intore];
    for(lz = 1;lz <= intore;lz++)                          /* 110 */
      {
      t= xg[(lz-1)*4 + intore];
      
/*======================================================================
* Matrix b der partiellen Ableitungen & Jacobi Determinante holen
*=====================================================================*/
      iret= lb88(&det,&r,&s,&t);
      if(iret != 0) return(iret);
    
      wt= wgt[(lx-1)*4 + intore] * 
          wgt[(ly-1)*4 + intore] * 
          wgt[(lz-1)*4 + intore] * det;

      for(j = 1;j <= 24;j++)                               /* 90 */
        {
        for(k = 1;k <= 6;k++)                              /* 60 */
          {
          db[k]= 0.;
          for(l = 1;l <= 6;l++)                            /* 50 */
            {
            db[k]= db[k] + d[(k-1)*6 + l] * b[(l-1)*24 + j];
            }                                              /* e 50 */
          }                                                /* e 60 */
 
        for(i = j;i <= 24;i++)                             /* 80 */
          {
          stiff= 0.;
          for(l = 1;l <= 6;l++)                            /* 70 */
            {
            stiff+= b[(l-1)*24 + i] * db[l];
            }                                              /* e 70 */
          se[i+ne*(j-1)]= se[i+ne*(j-1)] + stiff * wt;
          }                                                /* e 80 */
        }                                                  /* e 90 */
      }                                                    /* e 100 */
    }                                                      /* e 110 */
  }                                                        /* e 120 */

for(j = 1;j <= 24;j++)
  {                                                        /* 140 */  
  for(i = j;i <= 24;i++)                                   /* 130 */
    {
    se[j+ne*(i-1)]= se[i+ne*(j-1)];
    }                                                      /* e 130 */
  }                                                        /* e 140 */

return(0);
}

/***********************************************************************
* hier beginnt Function lb88
***********************************************************************/
int lb88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s,FR_DOUBLE *t)
{
/*---------------------------------------------------------------------
* xx geht rein, unveraendert (ex)
* b  geht raus, neu (ex)
* det geht raus, neu
* r,s,t gehen rein, unveraendert
*--------------------------------------------------------------------*/

extern FR_DOUBLE b[],xx[],p[];

FR_DOUBLE xj[10], xji[10];              /* ist 3x3 +1 */

FR_DOUBLE dum,rs,rt,st;
        
FR_INT4 i,j,k,k3;
        
/*----------------------------------------------------------------------
* Faktoren der Ableitungen der Formfunktionen belegen
*---------------------------------------------------------------------*/
rs= (*r) * (*s) ;
rt= (*r) * (*t) ;
st= (*s) * (*t) ;
        
/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach r
*---------------------------------------------------------------------*/
p[1]=  .125 *(+1. + (*s) + (*t) + st);
p[2]=  .125 *(-1. - (*s) - (*t) - st);
p[3]=  .125 *(-1. + (*s) - (*t) + st);
p[4]=  .125 *(+1. - (*s) + (*t) - st);
p[5]=  .125 *(+1. + (*s) - (*t) - st);
p[6]=  .125 *(-1. - (*s) + (*t) + st);
p[7]=  .125 *(-1. + (*s) + (*t) - st);
p[8]=  .125 *(+1. - (*s) - (*t) + st);

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach s
*---------------------------------------------------------------------*/
p[9] = .125 *(+1. + (*r) + (*t) + rt);
p[10]= .125 *(+1. - (*r) + (*t) - rt);
p[11]= .125 *(-1. + (*r) - (*t) + rt);
p[12]= .125 *(-1. - (*r) - (*t) - rt);
p[13]= .125 *(+1. + (*r) - (*t) - rt);
p[14]= .125 *(+1. - (*r) - (*t) + rt);
p[15]= .125 *(-1. + (*r) + (*t) - rt);
p[16]= .125 *(-1. - (*r) + (*t) + rt);

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach t
*---------------------------------------------------------------------*/
p[17]= .125 *(+1. + (*r) + (*s) + rs);
p[18]= .125 *(+1. - (*r) + (*s) - rs);
p[19]= .125 *(+1. - (*r) - (*s) + rs);
p[20]= .125 *(+1. + (*r) - (*s) - rs);
p[21]= .125 *(-1. - (*r) - (*s) - rs);
p[22]= .125 *(-1. + (*r) - (*s) + rs);
p[23]= .125 *(-1. + (*r) + (*s) - rs);
p[24]= .125 *(-1. - (*r) + (*s) + rs);

/*----------------------------------------------------------------------
* Jacobi-Matrix am Punkt (r,s,t) entwickeln
*---------------------------------------------------------------------*/
for(i = 1;i <= 3;i++)
  {
  for(j = 1;j <= 3;j++)
    {
    dum= 0.;
    for(k = 1;k <= 8;k++)
      {
      dum+= p[(i-1)*8 + k] * xx[(j-1)*8 + k];
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

if((*det) < 0.00000001)
  return(AL_JACNEG);

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
for(i = 1;i <= 144;i++)
  b[i]= 0.;

k3= 0;

for(k = 1;k <= 8;k++)
  {
  k3+= 3;

  for(i = 1;i <= 3;i++)
    {
    b[     k3-2]= b[     k3-2] + xji[    i] * p[(i-1)*8 + k];
    b[24 + k3-1]= b[24 + k3-1] + xji[3 + i] * p[(i-1)*8 + k];
    b[48 + k3  ]= b[48 + k3  ] + xji[6 + i] * p[(i-1)*8 + k];
    }
  b[72 + k3-2]= b[24 + k3-1];
  b[72 + k3-1]= b[     k3-2];
            
  b[96 + k3-1]= b[48+ k3   ];
  b[96 + k3  ]= b[24 + k3-1];

  b[120 + k3-2]= b[48 +k3   ];
  b[120 + k3  ]= b[     k3-2];
  }

return(0);
}

