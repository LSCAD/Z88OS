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
* V14.0 January 14, 2009
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
* diese Compilerunit umfasst: spur88 - Elementsteifigkeitsroutine
*                             sb88   - Berechnung der Matrix b
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
int sb88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s,FR_DOUBLE *t);

/***********************************************************************
* hier beginnt Function spur88
***********************************************************************/
int spur88(void)
{
extern FR_DOUBLEAY se;

extern FR_DOUBLE xk[],yk[],zk[];
extern FR_DOUBLE b[],xx[],d[];

extern FR_DOUBLE emode,rnuee;

extern FR_INT4 intore;

FR_DOUBLE db[7];

FR_DOUBLE r,s,t,det,wt,stiff;
FR_DOUBLE f0,f1,f2;

FR_INT4 ne= 12,i,igauss,j,k,l;

int iret;
  
/*----------------------------------------------------------------------
* Gauss-Legendre Stuetzstellen
*---------------------------------------------------------------------*/
static FR_DOUBLE rg[26]= 
{
0.,0.,0.,0.,0.,    /* Elemente 0 bis 4 leer       */
0.25,              /* 1 Stuetzstelle, Start i=5   */
0.,0.,0.,0.,0.,    /* Elemente 6 bis 16 leer      */
0.,0.,0.,0.,0.,0.,
0.58541020,        /* 4 Stuetzstellen, Start i=17 */
0.13819660,
0.13819660,
0.13819660,
0.25,              /* 5 Stuetzstellen, Start i=21 */
0.5,
0.16666667,
0.16666667,
0.16666667
};

static FR_DOUBLE sg[26]= 
{
0.,0.,0.,0.,0.,    /* Elemente 0 bis 4 leer       */
0.25,              /* 1 Stuetzstelle, Start i=5   */
0.,0.,0.,0.,0.,    /* Elemente 6 bis 16 leer      */
0.,0.,0.,0.,0.,0.,
0.13819660,        /* 4 Stuetzstellen, Start i=17 */
0.58541020,
0.13819660,
0.13819660,
0.25,              /* 5 Stuetzstellen, Start i=21 */
0.16666667,
0.5,
0.16666667,
0.16666667
};

static FR_DOUBLE tg[26]= 
{
0.,0.,0.,0.,0.,    /* Elemente 0 bis 4 leer       */
0.25,              /* 1 Stuetzstelle, Start i=5   */
0.,0.,0.,0.,0.,    /* Elemente 6 bis 16 leer      */
0.,0.,0.,0.,0.,0.,
0.13819660,        /* 4 Stuetzstellen, Start i=17 */
0.13819660,
0.58541020,
0.13819660,
0.25,              /* 5 Stuetzstellen, Start i=21 */
0.16666667,
0.16666667,
0.5,
0.16666667
};

/*----------------------------------------------------------------------
* Gauss-Legendre Integrationsgewichte
*---------------------------------------------------------------------*/
static FR_DOUBLE wg[26]= 
{ 
0.,0.,0.,0.,0.,    /* Elemente 0 bis 4 leer       */
1.0,               /* 1 Stuetzstelle, Start i=5   */
0.,0.,0.,0.,0.,    /* Elemente 6 bis 16 leer      */
0.,0.,0.,0.,0.,0.,
0.25,              /* 4 Stuetzstellen, Start i=17 */
0.25,
0.25,
0.25,
-0.8,              /* 5 Stuetzstellen, Start i=21 */
0.45,
0.45,
0.45,
0.45
};

/*----------------------------------------------------------------------
* xk und yk umspeichern
*---------------------------------------------------------------------*/
for(i = 1;i <= 4;i++)
  {
  xx[i]  = xk[i];
  xx[4+i]= yk[i];
  xx[8+i]= zk[i];
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
* Elementsteifigkeitsmatrix aufstellen: 12 x 12
*---------------------------------------------------------------------*/
for(i = 1;i <= 144;i++)
  se[i]= 0.;

for(igauss = 1;igauss <= intore;igauss++) 
  {
  r= rg[igauss + intore*4];
  s= sg[igauss + intore*4];
  t= tg[igauss + intore*4];
        
/*======================================================================
* Matrix b der partiellen Ableitungen & Jacobi Determinante holen
*=====================================================================*/
  iret= sb88(&det,&r,&s,&t);
  if(iret != 0) return(iret);
    
  wt= wg[igauss + intore*4] * det * 0.1666666667; /* x 1/6 */ 

  for(j = 1;j <= 12;j++)
    {
    for(k = 1;k <= 6;k++)
      {
      db[k]= 0.;
      for(l = 1;l <= 6;l++)
        {
        db[k]= db[k] + d[(k-1)*6 + l] * b[(l-1)*12 + j];
        }
      }
 
    for(i = j;i <= 12;i++)
      {
      stiff= 0.;
      for(l = 1;l <= 6;l++)
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
* hier beginnt Function sb88
***********************************************************************/
int sb88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s,FR_DOUBLE *t)
{
/*---------------------------------------------------------------------
* xx geht rein, unveraendert (ex)
* b  geht raus, neu (ex)
* det geht raus, neu
* r,s,t gehen rein, unveraendert
*--------------------------------------------------------------------*/

extern FR_DOUBLE b[],xx[],p[];

FR_DOUBLE xj[10], xji[10];              /* ist 3x3 +1 */

FR_DOUBLE dum;
        
FR_INT4 i,j,k,k3;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach r
*---------------------------------------------------------------------*/
p[1]= -1.;
p[2]=  1.;
p[3]=  0.;
p[4]=  0.;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach s
*---------------------------------------------------------------------*/
p[5]= -1.;
p[6]=  0.;
p[7]=  1.;
p[8]=  0.;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach t
*---------------------------------------------------------------------*/
p[ 9]= -1.;
p[10]=  0.;
p[11]=  0.;
p[12]=  1.;

/*----------------------------------------------------------------------
* Jacobi-Matrix am Punkt (r,s,t) entwickeln
*---------------------------------------------------------------------*/
for(i = 1;i <= 3;i++)
  {
  for(j = 1;j <= 3;j++)
    {
    dum= 0.;
    for(k = 1;k <= 4;k++)
      {
      dum+= p[(i-1)*4 + k] * xx[(j-1)*4 + k];
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
for(i = 1;i <= 72;i++)
  b[i]= 0.;

k3= 0;

for(k = 1;k <= 4;k++)
  {
  k3+= 3;

  for(i = 1;i <= 3;i++)
    {
    b[     k3-2]= b[     k3-2] + xji[    i] * p[(i-1)*4 + k];
    b[12 + k3-1]= b[12 + k3-1] + xji[3 + i] * p[(i-1)*4 + k];
    b[24 + k3  ]= b[24 + k3  ] + xji[6 + i] * p[(i-1)*4 + k];
    }
  b[36 + k3-2]= b[12 + k3-1];
  b[36 + k3-1]= b[     k3-2];
            
  b[48 + k3-1]= b[24 + k3  ];
  b[48 + k3  ]= b[12 + k3-1];

  b[60 + k3-2]= b[24 + k3  ];
  b[60 + k3  ]= b[     k3-2];
  }
 
return(0);
}

