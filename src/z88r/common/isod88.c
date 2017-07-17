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
* diese Compilerunit umfasst: isod88 - Elementsteifigkeitsroutine
*                             ib88   - Berechnung der Matrix b
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
int ib88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s,
         FR_DOUBLE *xbar,FR_INT4 *ktyp);

/***********************************************************************
* hier beginnt Function isod88
***********************************************************************/
int isod88(void)
{
extern FR_DOUBLEAY se;

extern FR_DOUBLE xk[],yk[];
extern FR_DOUBLE b[],xx[],d[];

extern FR_DOUBLE emode,rnuee,qparae;

extern FR_INT4 ktyp,intore;

FR_DOUBLE db[5];

FR_DOUBLE pi2= 6.283185307;
FR_DOUBLE facesz,facasz,r,s,det,xbar,wt,stiff;

FR_INT4 ne= 12,i,ist,igauss,j,k,l;

int iret;
  
/*----------------------------------------------------------------------
* Gauss-Legendre Stuetzstellen fuer r
*---------------------------------------------------------------------*/
static FR_DOUBLE rg[40]= 
{ 
0.,0.,0.,0.,0.,0.,0.,   /* Elemente 0 - 6 leer              */
0.1666666666667,        /* intore = 3, 1.Ele Start bei i=7  */
0.6666666666667,
0.1666666666667,
0.,0.,0.,0.,0.,         /* Elemente 10-14 leer              */
0.1012865073235,        /* intore = 7, 1.Ele Start bei i=15 */  
0.7974269853531,
0.1012865073235,
0.4701420641051,
0.4701420641051,
0.0597158717898,
0.3333333333333,
0.,0.,0.,0.,0.,         /* Elemente 22-26 leer              */
0.0651301029022,        /* intore =13, 1.Ele Start bei i=27 */
0.8697397941956,
0.0651301029022,
0.3128654960049,
0.6384441885698,
0.0486903154253,
0.6384441885698,
0.3128654960049,
0.0486903154253,
0.2603459660790,
0.4793080678419,
0.2603459660790,
0.3333333333333
};

/*----------------------------------------------------------------------
* Gauss-Legendre Stuetzstellen fuer s
*---------------------------------------------------------------------*/
static FR_DOUBLE sg[40]= 
{ 
0.,0.,0.,0.,0.,0.,0.,   /* Elemente 0 - 6 leer              */
0.1666666666667,        /* intore = 3, 1.Ele Start bei i=7  */
0.1666666666667,
0.6666666666667,
0.,0.,0.,0.,0.,         /* Elemente 10-14 leer              */
0.1012865073235,        /* intore = 7, 1.Ele Start bei i=15 */
0.1012865073235,
0.7974269853531,
0.0597158717898,
0.4701420641051,
0.4701420641051,
0.3333333333333,
0.,0.,0.,0.,0.,         /* Elemente 22-26 leer              */
0.0651301029022,        /* intore =13, 1.Ele Start bei i=27 */
0.0651301029022,
0.8697397941956,
0.0486903154253,
0.3128654960049,
0.6384441885698,
0.0486903154253,
0.6384441885698,
0.3128654960049,
0.2603459660790,
0.2603459660790,
0.4793080678419,
0.3333333333333
};

/*----------------------------------------------------------------------
* Gauss-Legendre Integrationsgewichte
*---------------------------------------------------------------------*/
static FR_DOUBLE wg[40]= 
{ 
0.,0.,0.,0.,0.,0.,0.,   /* Elemente 0 - 6 leer              */
0.3333333333333,        /* intore = 3, 1.Ele Start bei i=7  */
0.3333333333333,
0.3333333333333,
0.,0.,0.,0.,0.,         /* Elemente 10-14 leer              */
0.1259391805448,        /* intore = 7, 1.Ele Start bei i=15 */
0.1259391805448,
0.1259391805448,
0.1323941527885,
0.1323941527885,
0.1323941527885,
0.225,
0.,0.,0.,0.,0.,         /* Elemente 22-26 leer              */
0.0533472356088,        /* intore =13, 1.Ele Start bei i=27 */
0.0533472356088,
0.0533472356088,
0.0771137608903,
0.0771137608903,
0.0771137608903,
0.0771137608903,
0.0771137608903,
0.0771137608903,
0.1756152574332,
0.1756152574332,
0.1756152574332,
-0.1495700444677
};

/*----------------------------------------------------------------------
* intore anpassen, damit Mischen mit qshe88 via z88g moeglich ist
*---------------------------------------------------------------------*/
if(intore == 1 || intore == 2) intore = 3;
if(intore == 4)                intore = 7;

/*----------------------------------------------------------------------
* xk und yk umspeichern
*---------------------------------------------------------------------*/
for(i = 1;i <= 6;i++)
  {
  xx[i]  = xk[i];
  xx[6+i]= yk[i];
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
for(i = 1;i <= 144;i++)
  se[i]= 0.;

ist= 3;                /* ebener Spannungs- bzw. Verzerrungsz */
if(ktyp == 0) ist= 4;  /* axialsymmetrischer Spannungszustand */

for(igauss = 1;igauss <= intore;igauss++)
  {
  r= rg[igauss+2*intore];
  s= sg[igauss+2*intore];

/*======================================================================
* Matrix b der partiellen Ableitungen & Jacobi Determinante holen
*=====================================================================*/
  iret= ib88(&det,&r,&s,&xbar,&ktyp);
  if(iret != 0) return(iret);
    
  if(ktyp >  0) xbar= qparae;         /* ebener Spannungs/Verz.  */
  if(ktyp == 0) xbar= xbar*pi2;       /* axialsym. Spannungsz.   */

  wt= wg[igauss+2*intore]*0.5 * xbar * det; /* Gaussg. halbieren */
  for(j = 1;j <= 12;j++)
    {
    for(k = 1;k <= ist;k++)  
      {
      db[k]= 0.;
      for(l = 1;l <= ist;l++)
        {
        db[k]= db[k] + d[(k-1)*4 + l] * b[(l-1)*12 + j];
        }
      }
 
    for(i = j;i <= 12;i++)
      {
      stiff= 0.;
      for(l = 1;l <= ist;l++)
        {
        stiff+= b[(l-1)*12 + i] * db[l];
        }
      se[i+ne*(j-1)]= se[i+ne*(j-1)] + stiff * wt;
      }
    }
  } 

for(j = 1;j <= 12;j++)
  {  
  for(i = j;i <= 12;i++)
    {
    se[j+ne*(i-1)]= se[i+ne*(j-1)];
    } 
  } 
return(0);
}

/***********************************************************************
* hier beginnt Function ib88
***********************************************************************/
int ib88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s,
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

FR_DOUBLE rr2,ss2,r4,r3,s4,s3,rs4,dum;
        
FR_INT4 i,j,k,k2;
         
/*----------------------------------------------------------------------
* Klammern der Formfunktionen belegen
*---------------------------------------------------------------------*/
rr2= 2. * (*r) * (*r);
ss2= 2. * (*s) * (*s);
r4 = 4. * (*r);
r3 = 3. * (*r);
s4 = 4. * (*s);
s3 = 3. * (*s);
rs4= 4. * (*r) * (*s);

/*----------------------------------------------------------------------
* Formfunktionen
*---------------------------------------------------------------------*/
h[1]= rr2 + ss2 + rs4 - r3 - s3 + 1.;
h[2]= rr2 - (*r);
h[3]= ss2 - (*s);
h[4]= r4 - 2*rr2 - rs4;
h[5]= rs4;
h[6]= s4 - 2*ss2 - rs4;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach r
*---------------------------------------------------------------------*/
p[1]= r4 + s4 - 3.;
p[2]= r4 - 1.;
p[3]= 0.;
p[4]= 4. - 8*(*r) -s4;
p[5]= s4;
p[6]= -s4;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach s
*---------------------------------------------------------------------*/
p[7] = s4 + r4 - 3.;
p[8] = 0.;
p[9] = s4 - 1.;
p[10]= -r4;
p[11]= r4;
p[12]= 4. - r4 - 8*(*s);

/*----------------------------------------------------------------------
* Jacobi-Matrix am Punkt (r,s) entwickeln
*---------------------------------------------------------------------*/
for(i = 1;i <= 2;i++)
  {
  for(j = 1;j <= 2;j++)
    {
    dum= 0.;
    for(k = 1;k <= 6;k++)
      {
      dum+= p[(i-1)*6 + k] * xx[(j-1)*6 + k];
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

xji[1]= xj[4]    * dum;
xji[2]= (-xj[2]) * dum;
xji[3]= (-xj[3]) * dum;
xji[4]= xj[1]    * dum;

/*----------------------------------------------------------------------
* Entwickeln der Matrix b
*---------------------------------------------------------------------*/
for(i = 1;i <= 36;i++)
  b[i]= 0.;

k2= 0;

for(k = 1;k <= 6;k++)
  {
  k2+= 2;
  b[k2-1]= 0.;
  b[k2  ]= 0.;
  b[12 + k2-1]= 0.;
  b[12 + k2  ]= 0.;

  for(i = 1;i <= 2;i++)
    {
    b[     k2-1]= b[     k2-1] + xji[   i] * p[(i-1)*6 + k];
    b[12 + k2  ]= b[12 + k2  ] + xji[2 +i] * p[(i-1)*6 + k];
    }
  b[24 + k2  ]= b[    k2-1];
  b[24 + k2-1]= b[12 +k2  ];
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

for(k = 1;k <= 6;k++)
  (*xbar)= (*xbar) + h[k] * xx[k];

if((*xbar) <= 0.00000001)
  {
/*======================================================================
* Radius ist null
*=====================================================================*/
  for(k = 1;k <= 12;k++)
    b[36 + k]= b[k];

  return(0);

  }
else
  {
/*======================================================================
* Radius ist nicht null
*=====================================================================*/
  dum=1./(*xbar);
  k2= 0;

  for(k = 1;k <= 6;k++)
    {
    k2+= 2;
    b[36 + k2  ]= 0.;
    b[36 + k2-1]= h[k] * dum;
    }

  }
/**********************************************************************/
return(0);
}
