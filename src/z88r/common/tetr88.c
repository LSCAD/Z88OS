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
* diese Compilerunit umfasst: tetr88 - Elementsteifigkeitsroutine
*                             tb88   - Berechnung der Matrix b
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
int tb88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s,FR_DOUBLE *t);

/***********************************************************************
* hier beginnt Function tetr88
***********************************************************************/
int tetr88(void)
{
extern FR_DOUBLEAY se;

extern FR_DOUBLE xk[],yk[],zk[];
extern FR_DOUBLE b[],xx[],d[];

extern FR_DOUBLE emode,rnuee;

extern FR_INT4 intore;

FR_DOUBLE db[7];

FR_DOUBLE r,s,t,det,wt,stiff;
FR_DOUBLE f0,f1,f2;

FR_INT4 ne= 30,i,igauss,j,k,l;

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
for(i = 1;i <= 10;i++)
  {
  xx[i]   = xk[i];
  xx[10+i]= yk[i];
  xx[20+i]= zk[i];
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
* Elementsteifigkeitsmatrix aufstellen: 30 x 30
*---------------------------------------------------------------------*/
for(i = 1;i <= 900;i++)
  se[i]= 0.;

for(igauss = 1;igauss <= intore;igauss++) 
  {
  r= rg[igauss + intore*4];
  s= sg[igauss + intore*4];
  t= tg[igauss + intore*4];
        
/*======================================================================
* Matrix b der partiellen Ableitungen & Jacobi Determinante holen
*=====================================================================*/
  iret= tb88(&det,&r,&s,&t);
  if(iret != 0) return(iret);
    
  wt= wg[igauss + intore*4] * det * 0.1666666667; /* x 1/6 */ 

  for(j = 1;j <= 30;j++)
    {
    for(k = 1;k <= 6;k++)
      {
      db[k]= 0.;
      for(l = 1;l <= 6;l++)
        {
        db[k]= db[k] + d[(k-1)*6 + l] * b[(l-1)*30 + j];
        }
      }
 
    for(i = j;i <= 30;i++)
      {
      stiff= 0.;
      for(l = 1;l <= 6;l++)
        {
        stiff+= b[(l-1)*30 + i] * db[l];
        }
      se[i+ne*(j-1)]= se[i+ne*(j-1)] + stiff * wt;
      } 
    }
  } 

for(j = 1;j <= 30;j++)
  {   
  for(i = j;i <= 30;i++)
    {
    se[j+ne*(i-1)]= se[i+ne*(j-1)];
    }
  }

return(0);
}

/***********************************************************************
* hier beginnt Function tb88
***********************************************************************/
int tb88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s,FR_DOUBLE *t)
{
/*---------------------------------------------------------------------
* xx geht rein, unveraendert (ex)
* b  geht raus, neu (ex)
* det geht raus, neu
* r,s,t gehen rein, unveraendert
*--------------------------------------------------------------------*/

extern FR_DOUBLE b[],xx[],p[];

FR_DOUBLE xj[10], xji[10];              /* ist 3x3 +1 */

FR_DOUBLE dum,r4,s4,t4;
        
FR_INT4 i,j,k,k3;

/*----------------------------------------------------------------------
* Einige Faktoren fuer Formfunktionen
*---------------------------------------------------------------------*/
r4= 4* (*r);
s4= 4* (*s);
t4= 4* (*t);
        
/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach r
*---------------------------------------------------------------------*/
p[1]=   r4 + s4 + t4 -  3.;
p[2]=   r4 -  1.;
p[3]=    0.;
p[4]=    0.;
p[5]=    4. - 2*r4 - s4 - t4; 
p[6]=   s4;
p[7]=  -s4;
p[8]=   t4;  
p[9]=    0.;
p[10]= -t4;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach s
*---------------------------------------------------------------------*/
p[11]=  s4 + r4 + t4 -  3.;
p[12]=   0.;
p[13]=  s4 -  1.;
p[14]=   0.;
p[15]= -r4 ;
p[16]=  r4;
p[17]=   4. - r4 - 2*s4 - t4;
p[18]=   0.;
p[19]=  t4;
p[20]= -t4;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach t
*---------------------------------------------------------------------*/
p[21]=  t4 + r4 + s4 -  3.;
p[22]=   0.;
p[23]=   0.;
p[24]=  t4 -  1.;
p[25]= -r4;
p[26]=   0.;
p[27]= -s4;
p[28]=  r4;
p[29]=  s4;
p[30]=   4. - r4 - s4 - 2.*t4;

/*----------------------------------------------------------------------
* Jacobi-Matrix am Punkt (r,s,t) entwickeln
*---------------------------------------------------------------------*/
for(i = 1;i <= 3;i++)
  {
  for(j = 1;j <= 3;j++)
    {
    dum= 0.;
    for(k = 1;k <= 10;k++)
      {
      dum+= p[(i-1)*10 + k] * xx[(j-1)*10 + k];
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

if(FR_FABS(*det) < 0.000000001)
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
for(i = 1;i <= 180;i++)
  b[i]= 0.;

k3= 0;

for(k = 1;k <= 10;k++)
  {
  k3+= 3;

  for(i = 1;i <= 3;i++)
    {
    b[     k3-2]= b[     k3-2] + xji[    i] * p[(i-1)*10 + k];
    b[30 + k3-1]= b[30 + k3-1] + xji[3 + i] * p[(i-1)*10 + k];
    b[60 + k3  ]= b[60 + k3  ] + xji[6 + i] * p[(i-1)*10 + k];
    }
  b[90 + k3-2]= b[30 + k3-1];
  b[90 + k3-1]= b[     k3-2];
            
  b[120 + k3-1]= b[60 + k3  ];
  b[120 + k3  ]= b[30 + k3-1];

  b[150 + k3-2]= b[60 + k3  ];
  b[150 + k3  ]= b[     k3-2];
  }
 
return(0);
}

