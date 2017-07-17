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
* diese Compilerunit umfasst: cshe88 - Elementsteifigkeitsroutine
*                             cb88   - Berechnung der Matrix b
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
* Fuer Windows und GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88r.h>
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int cb88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s,
         FR_DOUBLE *xbar,FR_INT4 *ktyp);

/***********************************************************************
* hier beginnt Function cshe88
***********************************************************************/
int cshe88(void)
{
extern FR_DOUBLEAY se;

extern FR_DOUBLE xk[],yk[];
extern FR_DOUBLE b[],xx[],d[];

extern FR_DOUBLE emode,rnuee,qparae;

extern FR_INT4 ktyp,intore;

FR_DOUBLE db[5];

FR_DOUBLE pi2= 6.283185307;
FR_DOUBLE facesz,facasz,r,s,det,xbar,wt,stiff;

FR_INT4 ne= 24,i,ist,lx,ly,j,k,l;

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
for(i = 1;i <= 12;i++)
  {
  xx[i ]  = xk[i];
  xx[12+i]= yk[i];
  }

/*----------------------------------------------------------------------
* Materialkonstanten
*---------------------------------------------------------------------*/
facesz= emode/(1. - rnuee*rnuee);
facasz= emode*(1. - rnuee)/( (1. + rnuee)*(1. - 2*rnuee) );
        
/*----------------------------------------------------------------------
* Elastizitaetsmatrix aufstellen: ebener Spannungszustand
*---------------------------------------------------------------------*/
if (ktyp == 2)
  {
  d[1] = facesz;
  d[5] = facesz * rnuee;
  d[9] = 0.;
  d[2] = d[5];
  d[6] = facesz;
  d[10]= 0.;
  d[3] = 0.;
  d[7] = 0.;
  d[11]= facesz * .5 * (1. - rnuee);
  }
        
/*----------------------------------------------------------------------
* Elastizitaetsmatrix aufstellen: ebener Verzerrungszustand
*---------------------------------------------------------------------*/
if (ktyp == 1)
  {
  d[1] = facasz;
  d[5] = facasz * rnuee / (1. - rnuee);
  d[9] = 0.;
  d[2] = d[5];
  d[6] = facasz;
  d[10]= 0.;
  d[3] = 0.;
  d[7] = 0.;
  d[11]= emode / (2.*(1. + rnuee));
  qparae= 1.;
  }

/*----------------------------------------------------------------------
* Elastizitaetsmatrix aufstellen: axialsymmetrischer Spannungszustand
*---------------------------------------------------------------------*/
if (ktyp == 0)
  {
  d[1] = facasz;
  d[5] = facasz * rnuee / (1. - rnuee);
  d[9] = 0.;
  d[13]= d[5];
  d[2] = d[5];
  d[6] = facasz;
  d[10]= 0.;
  d[14]= d[5];
  d[3] = 0.;
  d[7] = 0.;
  d[11]= emode / (2.*(1. + rnuee));
  d[15]= 0.;
  d[4]= d[5];
  d[8]= d[5];
  d[12]= 0.;
  d[16]= facasz;
  }

/*----------------------------------------------------------------------
* Elementsteifigkeitsmatrix aufstellen
*---------------------------------------------------------------------*/
for(i = 1;i <= 576;i++)
  se[i]= 0.;

ist= 3; 
if(ktyp == 0) ist= 4;

for(lx = 1;lx <= intore;lx++)                              /* 90 */
  {
  r= xg[(lx-1)*4 + intore];
  for(ly = 1;ly <= intore;ly++)                            /* 80 */
    {
    s= xg[(ly-1)*4 + intore];

/*======================================================================
* Matrix b der partiellen Ableitungen & Jacobi Determinante holen
*=====================================================================*/
    iret= cb88(&det,&r,&s,&xbar,&ktyp);
    if(iret != 0) return(iret);
    
    if(ktyp >  0) xbar= qparae;
    if(ktyp == 0) xbar= xbar*pi2;

    wt= wgt[(lx-1)*4 + intore] * wgt[(ly-1)*4 + intore] * xbar * det;
    for(j = 1;j <= 24;j++)                                 /* 70 */
      {
      for(k = 1;k <= ist;k++)                              /* 40 */
        {
        db[k]= 0.;
        for(l = 1;l <= ist;l++)                            /* 30 */
          {
          db[k]= db[k] + d[(k-1)*4 + l] * b[(l-1)*24 + j];
          }                                                /* e 30 */
        }                                                  /* e 40 */
 
      for(i = j;i <= 24;i++)                               /* 60 */
        {
        stiff= 0.;
        for(l = 1;l <= ist;l++)                            /* 50 */
          {
          stiff+= b[(l-1)*24 + i] * db[l];
          }                                                /* e 50 */
        se[i+ne*(j-1)]= se[i+ne*(j-1)] + stiff * wt;
        }                                                  /* e 60 */
      }                                                    /* e 70 */
    }                                                      /* e 80 */
  }                                                        /* e 90 */

for(j = 1;j <= 24;j++)
  {                                                        /* 110 */  
  for(i = j;i <= 24;i++)                                   /* 100 */
    {
    se[j+ne*(i-1)]= se[i+ne*(j-1)];
    }                                                      /* e 100 */
  }                                                        /* e 110 */

return(0);
}

/***********************************************************************
* hier beginnt Function cb88
***********************************************************************/
int cb88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s,
         FR_DOUBLE *xbar,FR_INT4 *ktyp)
{
/*---------------------------------------------------------------------
* xx geht rein, unveraendert (ex)
* b  geht raus, neu (ex)
* det geht raus, neu
* r,s gehen rein, unveraendert
* xbar geht raus, neu
* ktyp geht rein, unveraendert
*--------------------------------------------------------------------*/

extern FR_DOUBLE h[];
extern FR_DOUBLE b[],xx[],p[];

FR_DOUBLE xj[5], xji[5];          /* ist 2x2 +1 */

FR_DOUBLE epr,emr,eps,ems,emrr,emss,rr27;
FR_DOUBLE ss27,rr9,ss9,r18,s18,r2,s2,r3,s3,dum;
        
FR_INT4 i,j,k,k2;
         
/*----------------------------------------------------------------------
* Klammern der Formfunktionen belegen
*---------------------------------------------------------------------*/
epr= 1. + (*r) ;
emr= 1. - (*r) ;
eps= 1. + (*s) ;
ems= 1. - (*s) ;

emrr= 1. -  (*r) * (*r) ;
emss= 1. -  (*s) * (*s) ;
rr27= 27. * (*r) * (*r) ;
ss27= 27. * (*s) * (*s) ;
rr9 = 9.  * (*r) * (*r) ;
ss9 = 9.  * (*s) * (*s) ;
r18 = 18. * (*r) ;
s18 = 18. * (*s) ;
r2  = 2.  * (*r) ;
s2  = 2.  * (*s) ;
r3  = 3.  * (*r) ;
s3  = 3.  * (*s) ;

/*----------------------------------------------------------------------
* Formfunktionen
*---------------------------------------------------------------------*/
h[1 ]=  .03125 * epr * eps * ( rr9 + ss9 - 10.);  
h[2 ]=  .03125 * emr * eps * ( rr9 + ss9 - 10.);
h[3 ]=  .03125 * emr * ems * ( rr9 + ss9 - 10.);
h[4 ]=  .03125 * epr * ems * ( rr9 + ss9 - 10.);
h[5 ]=  .28125 * eps * emrr* ( 1. + r3);
h[6 ]=  .28125 * eps * emrr* ( 1. - r3);
h[7 ]=  .28125 * emr * emss* ( 1. + s3);
h[8 ]=  .28125 * emr * emss* ( 1. - s3);
h[9 ]=  .28125 * ems * emrr* ( 1. - r3);
h[10]=  .28125 * ems * emrr* ( 1. + r3);
h[11]=  .28125 * epr * emss* ( 1. - s3);
h[12]=  .28125 * epr * emss* ( 1. + s3); 

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach r
*---------------------------------------------------------------------*/
p[1 ]=  .03125 * eps * ( rr27 + ss9 - 10. + r18);
p[2 ]=  .03125 * eps * (-rr27 - ss9 + 10. + r18);
p[3 ]=  .03125 * ems * (-rr27 - ss9 + 10. + r18);
p[4 ]=  .03125 * ems * ( rr27 + ss9 - 10. + r18);
p[5 ]=  .28125 * eps * (-rr9  - r2 + 3.);
p[6 ]=  .28125 * eps * ( rr9  - r2 - 3.); 
p[7 ]= -.28125 * emss *( 1.  + s3);
p[8 ]= -.28125 * emss *( 1.  - s3);
p[9 ]=  .28125 * ems * ( rr9  - r2 - 3.);
p[10]=  .28125 * ems * (-rr9  - r2 + 3.);
p[11]=  .28125 * emss* ( 1.  - s3);
p[12]=  .28125 * emss* ( 1.  + s3);

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach s
*---------------------------------------------------------------------*/
p[13]=  .03125 * epr * ( ss27 + rr9 - 10. + s18);
p[14]=  .03125 * emr * ( ss27 + rr9 - 10. + s18);
p[15]=  .03125 * emr * (-ss27 - rr9 + 10. + s18);
p[16]=  .03125 * epr * (-ss27 - rr9 + 10. + s18);
p[17]=  .28125 * emrr* ( 1.  + r3);
p[18]=  .28125 * emrr* ( 1.  - r3);
p[19]=  .28125 * emr * (-ss9  - s2  + 3.);
p[20]=  .28125 * emr * ( ss9  - s2  - 3.);
p[21]= -.28125 * emrr* ( 1.  - r3);
p[22]= -.28125 * emrr* ( 1.  + r3);
p[23]=  .28125 * epr * ( ss9  - s2  - 3.);
p[24]=  .28125 * epr * (-ss9  - s2  + 3.);

/*----------------------------------------------------------------------
* Jacobi-Matrix am Punkt (r,s) entwickeln
*---------------------------------------------------------------------*/
for(i = 1;i <= 2;i++)
  {
  for(j = 1;j <= 2;j++)
    {
    dum= 0.;
    for(k = 1;k <= 12;k++)
      {
      dum+= p[(i-1)*12 + k] * xx[(j-1)*12 + k];
      }
    xj[(i-1)*2 + j]= dum;
    }
  }

/*----------------------------------------------------------------------
* Jacobi-Determinante am Punkt (r,s) entwickeln
*---------------------------------------------------------------------*/
(*det)= xj[1] * xj[4] - xj[3] * xj[2];

if((*det) < 0.00000001)
  return(AL_JACNEG);

/*----------------------------------------------------------------------
* Berechnung der inversen Jacobi-Matrix
*---------------------------------------------------------------------*/
dum= 1./(*det);

xji[1]= xj[4] * dum;
xji[2]= (-xj[2]) * dum;
xji[3]= (-xj[3]) * dum;
xji[4]= xj[1] * dum;

/*----------------------------------------------------------------------
* Entwickeln der Matrix b
*---------------------------------------------------------------------*/
for(i = 1;i <= 96;i++)
  b[i]= 0.;

k2= 0;

for(k = 1;k <= 12;k++)
  {
  k2+= 2;
  b[k2-1]= 0.;
  b[k2  ]= 0.;
  b[24 + k2-1]= 0.;
  b[24 + k2  ]= 0.;

  for(i = 1;i <= 2;i++)
    {
    b[     k2-1]= b[     k2-1] + xji[   i] * p[(i-1)*12 + k];
    b[24 + k2  ]= b[24 + k2  ] + xji[2 +i] * p[(i-1)*12 + k];
    }
  b[48 + k2  ]= b[    k2-1];
  b[48 + k2-1]= b[24 +k2  ];
  }

if((*ktyp) > 0) return(0);

/*----------------------------------------------------------------------
* im Falle des axialsymmetrischen Toruselementes 
* die folgende Normalspannungskomponente einfuegen
*---------------------------------------------------------------------*/
/*======================================================================
* Radius am Punkt (r,s) berechnen
*=====================================================================*/
(*xbar)= 0.;

for(k = 1;k <= 12;k++)
  (*xbar)= (*xbar) + h[k] * xx[k];

if((*xbar) <= 0.00000001)
  {
/*======================================================================
* Radius ist null
*=====================================================================*/
  for(k = 1;k <= 24;k++)
    b[72 + k]= b[k];

  return(0);

  }
else
  {
/*======================================================================
* Radius ist nicht null
*=====================================================================*/
  dum=1./(*xbar);
  k2= 0;

  for(k = 1;k <= 12;k++)
    {
    k2+= 2;
    b[72 + k2  ]= 0.;
    b[72 + k2-1]= h[k] * dum;
    }

  }
/**********************************************************************/
return(0);
}
