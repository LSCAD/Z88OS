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
* diese Compilerunit umfasst: hexa88 - Elementsteifigkeitsroutine
*                             hb88   - Berechnung der Matrix b
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
int hb88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s,FR_DOUBLE *t);

/***********************************************************************
* hier beginnt Function hexa88
***********************************************************************/
int hexa88(void)
{
extern FR_DOUBLEAY se;

extern FR_DOUBLE xk[],yk[],zk[];
extern FR_DOUBLE b[],xx[],d[];

extern FR_DOUBLE emode,rnuee;

extern FR_INT4 intore;

FR_DOUBLE db[7];

FR_DOUBLE r,s,t,det,wt,stiff;
FR_DOUBLE f0,f1,f2;

FR_INT4 ne= 60,i,lx,ly,lz,j,k,l;

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
for(i = 1;i <= 20;i++)
  {
  xx[i]   = xk[i];
  xx[20+i]= yk[i];
  xx[40+i]= zk[i];
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
for(i = 1;i <= 3600;i++)
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
      iret= hb88(&det,&r,&s,&t);
      if(iret != 0) return(iret);
    
      wt= wgt[(lx-1)*4 + intore] * 
          wgt[(ly-1)*4 + intore] * 
          wgt[(lz-1)*4 + intore] * det;

      for(j = 1;j <= 60;j++)                               /* 90 */
        {
        for(k = 1;k <= 6;k++)                              /* 60 */
          {
          db[k]= 0.;
          for(l = 1;l <= 6;l++)                            /* 50 */
            {
            db[k]= db[k] + d[(k-1)*6 + l] * b[(l-1)*60 + j];
            }                                              /* e 50 */
          }                                                /* e 60 */
 
        for(i = j;i <= 60;i++)                             /* 80 */
          {
          stiff= 0.;
          for(l = 1;l <= 6;l++)                            /* 70 */
            {
            stiff+= b[(l-1)*60 + i] * db[l];
            }                                              /* e 70 */
          se[i+ne*(j-1)]= se[i+ne*(j-1)] + stiff * wt;
          }                                                /* e 80 */
        }                                                  /* e 90 */
      }                                                    /* e 100 */
    }                                                      /* e 110 */
  }                                                        /* e 120 */

for(j = 1;j <= 60;j++)
  {                                                        /* 140 */  
  for(i = j;i <= 60;i++)                                   /* 130 */
    {
    se[j+ne*(i-1)]= se[i+ne*(j-1)];
    }                                                      /* e 130 */
  }                                                        /* e 140 */

return(0);
}

/***********************************************************************
* hier beginnt Function hb88
***********************************************************************/
int hb88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s,FR_DOUBLE *t)
{
/*---------------------------------------------------------------------
* xx geht rein, unveraendert (ex)
* b  geht raus, neu (ex)
* det geht raus, neu
* r,s,t gehen rein, unveraendert
*--------------------------------------------------------------------*/

extern FR_DOUBLE b[],xx[],p[];

FR_DOUBLE xj[10], xji[10];              /* ist 3x3 +1 */

FR_DOUBLE dum,epr,emr,eps,ems,ept,emt;
FR_DOUBLE emrr,emss,emtt,zrm,zsm,ztm;
        
FR_INT4 i,j,k,k3;
        
/*----------------------------------------------------------------------
* Faktoren der Ableitungen der Formfunktionen belegen
*---------------------------------------------------------------------*/
epr = 1. + (*r);
emr = 1. - (*r);
eps = 1. + (*s);
ems = 1. - (*s);
ept = 1. + (*t);
emt = 1. - (*t);
        
emrr= 1. - (*r) * (*r);
emss= 1. - (*s) * (*s);
emtt= 1. - (*t) * (*t);
        
zrm = -2. * (*r);
zsm = -2. * (*s);
ztm = -2. * (*t);
        
/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach r
*---------------------------------------------------------------------*/
p[1]=  .125 *( eps*ept- zrm*eps*ept- emss*ept   - eps*emtt);
p[2]=  .125 *(-eps*ept- zrm*eps*ept+ emss*ept   + eps*emtt);
p[3]=  .125 *(-ems*ept+ emss*ept   - zrm*ems*ept+ ems*emtt);
p[4]=  .125 *( ems*ept- zrm*ems*ept- emss*ept   - ems*emtt);
p[5]=  .125 *( eps*emt- zrm*eps*emt- emss*emt   - eps*emtt); 
p[6]=  .125 *(-eps*emt- zrm*eps*emt+ emss*emt   + eps*emtt);
p[7]=  .125 *(-ems*emt+ emss*emt   - zrm*ems*emt+ ems*emtt);
p[8]=  .125 *( ems*emt- zrm*ems*emt- emss*emt   - ems*emtt);  
p[9]=  .250 *( zrm*eps*ept);
p[10]= .250 *(-emss*ept   );
p[11]= .250 *( zrm*ems*ept);
p[12]= .250 *( emss*ept   );
p[13]= .250 *( zrm*eps*emt);
p[14]= .250 *(-emss*emt   );
p[15]= .250 *( zrm*ems*emt);
p[16]= .250 *( emss*emt   );
p[17]= .250 *( eps*emtt   );
p[18]= .250 *(-eps*emtt   );
p[19]= .250 *(-ems*emtt   );
p[20]= .250 *( ems*emtt   );

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach s
*---------------------------------------------------------------------*/
p[21]=  .125 *( epr*ept -emrr*ept    -epr*zsm*ept -epr*emtt);
p[22]=  .125 *( emr*ept -emrr*ept    -emr*zsm*ept -emr*emtt);
p[23]=  .125 *(-emr*ept -emr*zsm*ept +emrr*ept    +emr*emtt);
p[24]=  .125 *(-epr*ept +emrr*ept    -epr*zsm*ept +epr*emtt);
p[25]=  .125 *( epr*emt -emrr*emt    -epr*zsm*emt -epr*emtt);
p[26]=  .125 *( emr*emt -emrr*emt    -emr*zsm*emt -emr*emtt);
p[27]=  .125 *(-emr*emt -emr*zsm*emt +emrr*emt    +emr*emtt);
p[28]=  .125 *(-epr*emt +emrr*emt    -epr*zsm*emt +epr*emtt);
p[29]=  .250 *( emrr*ept   );
p[30]= .250 *( emr*zsm*ept);
p[31]= .250 *(-emrr*ept   );
p[32]= .250 *( epr*zsm*ept);
p[33]= .250 *( emrr*emt   );
p[34]= .250 *( emr*zsm*emt);
p[35]= .250 *(-emrr*emt   );
p[36]= .250 *( epr*zsm*emt);
p[37]= .250 *( epr*emtt   );
p[38]= .250 *( emr*emtt   );
p[39]= .250 *(-emr*emtt   );
p[40]= .250 *(-epr*emtt   );

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach t
*---------------------------------------------------------------------*/
p[41]=  .125 *( epr*eps -emrr*eps -epr*emss -epr*eps*ztm);
p[42]=  .125 *( emr*eps -emrr*eps -emr*emss -emr*eps*ztm);
p[43]=  .125 *( emr*ems -emr*emss -emrr*ems -emr*ems*ztm);
p[44]=  .125 *( epr*ems -emrr*ems -epr*emss -epr*ems*ztm);
p[45]=  .125 *(-epr*eps +emrr*eps +epr*emss -epr*eps*ztm);
p[46]=  .125 *(-emr*eps +emrr*eps +emr*emss -emr*eps*ztm);
p[47]=  .125 *(-emr*ems +emr*emss +emrr*ems -emr*ems*ztm);
p[48]=  .125 *(-epr*ems +emrr*ems +epr*emss -epr*ems*ztm);
p[49]=  .250 *( emrr*eps   );
p[50]= .250 *( emr*emss   );
p[51]= .250 *( emrr*ems   );
p[52]= .250 *( epr*emss   );
p[53]= .250 *(-emrr*eps   );
p[54]= .250 *(-emr*emss   );
p[55]= .250 *(-emrr*ems   );
p[56]= .250 *(-epr*emss   );
p[57]= .250 *( epr*eps*ztm);
p[58]= .250 *( emr*eps*ztm);
p[59]= .250 *( emr*ems*ztm);
p[60]= .250 *( epr*ems*ztm);

/*----------------------------------------------------------------------
* Jacobi-Matrix am Punkt (r,s,t) entwickeln
*---------------------------------------------------------------------*/
for(i = 1;i <= 3;i++)
  {
  for(j = 1;j <= 3;j++)
    {
    dum= 0.;
    for(k = 1;k <= 20;k++)
      {
      dum+= p[(i-1)*20 + k] * xx[(j-1)*20 + k];
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
for(i = 1;i <= 360;i++)
  b[i]= 0.;

k3= 0;

for(k = 1;k <= 20;k++)
  {
  k3+= 3;

  for(i = 1;i <= 3;i++)
    {
    b[     k3-2]= b[     k3-2] + xji[    i] * p[(i-1)*20 + k];
    b[60 + k3-1]= b[60 + k3-1] + xji[3 + i] * p[(i-1)*20 + k];
    b[120+ k3  ]= b[120+ k3  ] + xji[6 + i] * p[(i-1)*20 + k];
    }
  b[180 + k3-2]= b[60 + k3-1];
  b[180 + k3-1]= b[     k3-2];
            
  b[240 + k3-1]= b[120+ k3  ];
  b[240 + k3  ]= b[60 + k3-1];

  b[300 + k3-2]= b[120 +k3  ];
  b[300 + k3  ]= b[     k3-2];
  }

return(0);
}

