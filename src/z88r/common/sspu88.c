/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows &
* the UNIX OS.
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
* Z88 should compile and run under any UNIX OS and Windows & GTK+.
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
* diese Compilerunit umfasst: sspu88 - Elementsteifigkeitsroutine
*                             ss88   - Berechnung der Matrix b
* 2.1.2010 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>       /* fprintf */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <stdio.h>       /* fprintf */
#endif

/***********************************************************************
* Fuer Windows & GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88r.h>
#include <stdio.h>
#endif

/***********************************************************************
* Formate
***********************************************************************/
#define NL "\n"

#ifdef FR_XDOUB
#define P10E " %+#10.2lE"
#define P11E " %+#11.3lE"
#endif

#ifdef FR_XQUAD
#define P10E " %+#10.2LE"
#define P11E " %+#11.3LE"
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int ss88(FR_DOUBLE *r,FR_DOUBLE *s,FR_DOUBLE *t);
FR_DOUBLE hexgh(FR_DOUBLE sig[]);
FR_DOUBLE hexnh(FR_DOUBLE sig[]);
FR_DOUBLE hexsh(FR_DOUBLE sig[]);
             
/***********************************************************************
* hier beginnt Function sspu88
***********************************************************************/
int sspu88(void)
{
extern FILE *fo3,*fo5;

extern FR_DOUBLEAY smw;
extern FR_DOUBLEAY gmw;
extern FR_DOUBLEAY sigvku;

extern FR_INT4AY jsm;
extern FR_INT4AY koi;
extern FR_INT4AY koffs;

extern FR_DOUBLE ul[];
extern FR_DOUBLE h[];
extern FR_DOUBLE xk[],yk[],zk[];
extern FR_DOUBLE b[],xx[],d[];

extern FR_DOUBLE emode,rnuee;

extern FR_INT4 ninto,isflag,kc,jpri,ifnili,ngau;

FR_DOUBLE eps[7],sig[7],rv[5];

FR_DOUBLE r,s,t,xs,ys,zs,sigv,ax,ay,az,rmin;
FR_DOUBLE f0,f1,f2;

FR_INT4 jp[5];
FR_INT4 i,igauss,j,k,lx,jk;

int iret;

/*----------------------------------------------------------------------
* Gauss-Legendre Stuetzstellen, variable Integrationsordnung
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
* Gauss-Legendre Stuetzstellen, fixe Integrationsordnung fuer Z88O
*---------------------------------------------------------------------*/
static FR_DOUBLE rgo[5]= { 0.,
0.13819660,  
0.58541020,
0.13819660,
0.13819660};

static FR_DOUBLE sgo[5]= { 0.,
0.13819660,
0.13819660,
0.58541020,
0.13819660};

static FR_DOUBLE tgo[5]= { 0.,
0.13819660,
0.13819660,
0.13819660,
0.58541020};

/*----------------------------------------------------------------------
* natuerliche Koordinaten der Eckknoten
*---------------------------------------------------------------------*/
static FR_DOUBLE rkr[5]= { 0.,
                        0.,1.,0.,0. };
static FR_DOUBLE rks[5]= { 0.,
                        0.,0.,1.,0. };
static FR_DOUBLE rkt[5]= { 0.,
                        0.,0.,0.,1. };
         
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
* Spannungen in den Gauss-Punkten berechnen
*---------------------------------------------------------------------*/
if(ninto > 0)
  {
/*======================================================================
* Spannungen in den Gauss-Punkten berechnen, variabel
*=====================================================================*/
  for(igauss = 1;igauss <= ninto;igauss++)
    {
    r= rg[igauss + ninto*4];
    s= sg[igauss + ninto*4];
    t= tg[igauss + ninto*4];
      
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    iret= ss88(&r,&s,&t);
    if(iret != 0) return(iret);
    
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verzerrungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 6;k++)
      {
      eps[k]= 0.;
      for(j = 1;j <= 12;j++)
        {
        eps[k]= eps[k] + b[(k-1)*12 + j] * ul[j];
        } 
      } 
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Spannungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 6;k++)
      {
      sig[k]= 0.;
      for(j = 1;j <= 6;j++)
        {
        sig[k]= sig[k] + d[(k-1)*6 + j] * eps[j];
        }
      }
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Integrationspunkte in echte Koordinaten umrechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    xs= 0.;
    ys= 0.;
    zs= 0.;
 
    for(j = 1;j <= 4;j++)
      {
      xs+= h[j] * xx[  j];
      ys+= h[j] * xx[4+j];
      zs+= h[j] * xx[8+j];
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Spannungen ausschreiben
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(isflag == 0 && ifnili == 0) 
      {
      fprintf(fo3,NL P10E P10E P10E P11E P11E P11E P11E P11E P11E
      ,xs,ys,zs,sig[1],sig[2],sig[3],sig[4],sig[5],sig[6]);
      }

    if(isflag == 1 || isflag == 2 || isflag == 3) 
      {
      if(isflag == 1) sigv= hexgh(sig);
      if(isflag == 2) sigv= hexnh(sig);
      if(isflag == 3) sigv= hexsh(sig);

      ngau++;
      sigvku[ngau]+= sigv;

      if(ifnili == 0)
        {
        fprintf(fo3,NL P10E P10E P10E P11E P11E P11E P11E P11E P11E P11E
        ,xs,ys,zs,sig[1],sig[2],sig[3],sig[4],sig[5],sig[6],sigv);
        }

      if(jpri == 1)
        {
        fprintf(fo5,NL P11E P11E P11E P11E,xs,ys,zs,sigvku[ngau]);
        }
      gmw[kc]+= sigv; 
      }
    }
  gmw[kc]/= ninto;  /* Mittelwert berechnen */

/*======================================================================
* die Eckpunkte berechnen
*=====================================================================*/
  for(igauss = 1;igauss <= 4;igauss++)
    {
    r= rkr[igauss];
    s= rks[igauss];
    t= rkt[igauss]; 
      
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    iret= ss88(&r,&s,&t);
    if(iret != 0) return(iret);
    
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Integrationspunkte in echte Koordinaten umrechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    xs= 0.;
    ys= 0.;
    zs= 0.;
 
    for(j = 1;j <= 4;j++)
      {
      xs+= h[j] * xx[  j];
      ys+= h[j] * xx[4+j];
      zs+= h[j] * xx[8+j];
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* welcher Knoten ist's wirklich?
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(j = 1;j <= 4;j++)
      {
      ax   = xk[j] - xs;
      ay   = yk[j] - ys;
      az   = zk[j] - zs;
      rv[j]= FR_SQRT(ax*ax + ay*ay + az*az);
      }

    rmin= 1e88;
    for(j = 1;j <= 4;j++)
      {
      if(rv[j] < rmin) 
        {
        rmin= rv[j];
        jk= j;     
        }
      }

    jp[igauss]= jk;
    }

/*======================================================================
* Spannungen in den Gauss-Punkten berechnen, fix fuer Z88O
*=====================================================================*/
  for(igauss = 1;igauss <= 4;igauss++)
    {
    r= rgo[igauss];
    s= sgo[igauss];
    t= tgo[igauss]; 
      
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    iret= ss88(&r,&s,&t);
    if(iret != 0) return(iret);
    
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verzerrungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 6;k++)
      {
      eps[k]= 0.;
      for(j = 1;j <= 12;j++)
        {
        eps[k]= eps[k] + b[(k-1)*12 + j] * ul[j];
        } 
      } 
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Spannungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 6;k++)
      {
      sig[k]= 0.;
      for(j = 1;j <= 6;j++)
        {
        sig[k]= sig[k] + d[(k-1)*6 + j] * eps[j];
        }
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Vergleichsspannungen aufaddieren
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(isflag == 1) sigv= hexgh(sig);
    if(isflag == 2) sigv= hexnh(sig);
    if(isflag == 3) sigv= hexsh(sig);

    smw[koi[koffs[kc]+jp[igauss]-1]]+= sigv;
    jsm[koi[koffs[kc]+jp[igauss]-1]]++;
    } /* Ende Z88O */
  }  /* Ende Gausspunkte variabel */

/*----------------------------------------------------------------------
* Spannungen in den Eckknoten berechnen
*---------------------------------------------------------------------*/
if(ninto == 0)
  {
  for(lx = 1;lx <= 4;lx++)
    {
    r= rkr[lx];
    s= rks[lx];
    t= rkt[lx];
      
/*======================================================================
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*=====================================================================*/
    iret= ss88(&r,&s,&t);
    if(iret != 0) return(iret);
    
/*======================================================================
* Dehnungen berechnen
*=====================================================================*/
    for(k = 1;k <= 6;k++) 
      {
      eps[k]= 0.;
      for(j = 1;j <= 12;j++)
        {                         
        eps[k]= eps[k] + b[(k-1)*12 + j] * ul[j];
        }                         
      }                           
 
/*======================================================================
* Spannungen berechnen
*=====================================================================*/
    for(k = 1;k <= 6;k++)         
      {
      sig[k]= 0.;
      for(j = 1;j <= 6;j++)       
        {
        sig[k]= sig[k] + d[(k-1)*6 + j] * eps[j];
        }                         
      }                           

/*======================================================================
* Eckpunkte in echte Koordinaten umrechnen
*=====================================================================*/
    xs= 0.;
    ys= 0.;
    zs= 0.;
 
    for(j = 1;j <= 4;j++)
      {
      xs+= h[j] * xx[  j];
      ys+= h[j] * xx[4+j];
      zs+= h[j] * xx[8+j];
      }

/*======================================================================
* Spannungen ausschreiben
*=====================================================================*/
    if(ifnili == 0)
      {
      fprintf(fo3,NL P10E P10E P10E P11E P11E P11E P11E P11E P11E
       ,xs,ys,zs,sig[1],sig[2],sig[3],sig[4],sig[5],sig[6]);
      }
    }                 
  }                   

return(0);
}

/***********************************************************************
* hier beginnt Function ss88
***********************************************************************/
int ss88(FR_DOUBLE *r,FR_DOUBLE *s,FR_DOUBLE *t)
{
/*---------------------------------------------------------------------
* xx geht rein, unveraendert (ex)
* h geht raus, neu (ex)
* b  geht raus, neu (ex)
* r,s,t gehen rein, unveraendert
*--------------------------------------------------------------------*/

extern FR_DOUBLE h[];
extern FR_DOUBLE b[],xx[],p[];

FR_DOUBLE xj[10], xji[10];              /* ist 3x3 +1 */

FR_DOUBLE dum,det;
        
FR_INT4 i,j,k,k3;
        
/*----------------------------------------------------------------------
* Formfunktionen
*---------------------------------------------------------------------*/
h[1] = 1 - *r - *s - *t;
h[2] = *r;
h[3] = *s;
h[4] = *t;

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
det= (xj[1] * xj[5] * xj[9]) - (xj[1] * xj[6] * xj[8]) +
        (xj[2] * xj[6] * xj[7]) - (xj[2] * xj[4] * xj[9]) +
        (xj[3] * xj[4] * xj[8]) - (xj[3] * xj[5] * xj[7]);

if(det < 0.00000001)
  return(AL_JACNEG);

/*----------------------------------------------------------------------
* Berechnung der inversen Jacobi-Matrix
*---------------------------------------------------------------------*/
dum= 1./det;

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

