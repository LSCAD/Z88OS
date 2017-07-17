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
* diese Compilerunit umfasst: sapl88 - Elementsteifigkeitsroutine
*                             sab88  - Berechnung der Matrix b
* 2.1.2010 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>    /* fprintf */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <stdio.h>    /* fprintf */
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
int sab88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s);
FR_DOUBLE platgh(FR_DOUBLE rsig[]);
FR_DOUBLE platnh(FR_DOUBLE rsig[]);
FR_DOUBLE platsh(FR_DOUBLE rsig[]);

/***********************************************************************
* hier beginnt Function sapl88
***********************************************************************/
int sapl88(void)
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
extern FR_DOUBLE xk[],yk[];
extern FR_DOUBLE b[],xx[],d[];

extern FR_DOUBLE emode,rnuee,qparae;

extern FR_INT4 ninto,isflag,ipflag,kc,jpri,ifnili,ngau;

FR_DOUBLE eps[6],sig[6],rsig[6],rv[5];
FR_DOUBLE facbi,facsv,r,s,det,rmok,skf,fmom,fque;

FR_DOUBLE xs,ys,sigv,ax,ay,rmin;

FR_INT4 jp[5];
FR_INT4 i,lx,ly,j,k,jk;

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
* Gauss-Legendre Stuetzstellen, fix fuer 2 x 2
*---------------------------------------------------------------------*/
static FR_DOUBLE xgo[5]= { 0.,
-.5773502691896,
+.5773502691896,
+.5773502691896,
-.5773502691896};

static FR_DOUBLE ygo[5]= { 0.,
-.5773502691896,
-.5773502691896,
+.5773502691896,
+.5773502691896};

/*----------------------------------------------------------------------
* natuerliche Koordinaten der Eckknoten
*---------------------------------------------------------------------*/
static FR_DOUBLE rkr[5]= { 0.,
                       -1., 1., 1.,-1. };
static FR_DOUBLE rks[5]= { 0.,
                       -1.,-1., 1., 1. };

/*----------------------------------------------------------------------
* xk und yk umspeichern
*---------------------------------------------------------------------*/
for(i = 1;i <= 8;i++)
  {
  xx[i]  = xk[i];
  xx[8+i]= yk[i];
  }

/*----------------------------------------------------------------------
* Materialmatrix aufstellen
*---------------------------------------------------------------------*/
for(i = 1;i <= 25;i++)
  d[i]= 0.;

/*----------------------------------------------------------------------
* Elastizitaetsmatrix aufstellen: Platten-Biegung
*---------------------------------------------------------------------*/
facbi = emode*qparae*qparae*qparae/(12.*(1. - rnuee*rnuee));

d[1] = facbi;
d[2] = facbi * rnuee;

d[6] = d[2];
d[7] = d[1];

d[13]= facbi * .5 * (1. - rnuee);
        
/*----------------------------------------------------------------------
* Elastizitaetsmatrix aufstellen: transversale Schubverzerrung
*---------------------------------------------------------------------*/
rmok= 1;
if(ipflag == 1)  rmok= 1.;     /* Reissner- Mindlin */
if(ipflag == 2)  rmok= 0.1;    /* Schubeinfluss daempfen */
if(ipflag == 3)  rmok= 0.01;   /* Schubeinfluss daempfen */
if(ipflag == 4)  rmok= 0.001;  /* Schubeinfluss daempfen */

skf= 5./6.;                    /* Schubkorrekturfaktor */

facsv= rmok*emode*skf*qparae/(2*(1. + rnuee));

d[19]= facsv;
d[25]= facsv;

/*----------------------------------------------------------------------
* Spannungen in den Gauss-Punkten berechnen
*---------------------------------------------------------------------*/
if(ninto > 0)
  {

/*======================================================================
* Spannungen in den Gauss-Punkten berechnen, variabel
*=====================================================================*/
  for(lx = 1;lx <= ninto;lx++)
    {
    r= xg[(lx-1)*4 + ninto];
    for(ly = 1;ly <= ninto;ly++)
      {
      s= xg[(ly-1)*4 + ninto];
      
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
      iret= sab88(&det,&r,&s);
      if(iret != 0) return(iret);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verzerrungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
      for(k = 1;k <= 5;k++)
        {
        eps[k]= 0.;
        for(j = 1;j <= 24;j++)
          { 
          eps[k]+= b[(k-1)*24 + j] * ul[j];
          }
        }
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Spannungen berechnen: Biegemomente und Querkraefte pro Laenge
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
      for(k = 1;k <= 5;k++)
        {
        sig[k]= 0.;
        for(j = 1;j <= 5;j++)
          {
          sig[k]+= d[(k-1)*5 + j] * eps[j];
          }
        }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* echte Spannungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
      fmom= 12.*(qparae/2.)/(qparae*qparae*qparae);

      for(k = 1;k <= 3;k++)
        rsig[k]= sig[k]*fmom;

      fque= 3./2. /qparae;

      for(k = 4;k <= 5;k++)
        rsig[k]= sig[k]*fque;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Integrationspunkte in echte Koordinaten umrechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
      xs= 0.;
      ys= 0.;
 
      for(j = 1;j <= 8;j++)
        {
        xs+= h[j] * xx[   j];
        ys+= h[j] * xx[8 +j];
        }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Spannungen ausschreiben
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
      if(isflag == 0 && ifnili == 0)
        {
        fprintf(fo3,NL P10E P10E P11E P11E P11E P11E P11E P11E P11E P11E P11E P11E
        ,xs,ys,sig[1],sig[2],sig[3],sig[4],sig[5],rsig[1],rsig[2],rsig[3],rsig[4],rsig[5]);
        }

      if(isflag == 1 || isflag == 2 || isflag == 3)
        {
        if(isflag == 1) sigv= platgh(rsig);
        if(isflag == 2) sigv= platnh(rsig);
        if(isflag == 3) sigv= platsh(rsig);

        ngau++;
        sigvku[ngau]+= sigv;

        if(ifnili == 0)
          {
          fprintf(fo3,NL P10E P10E P11E P11E P11E P11E P11E P11E P11E P11E P11E P11E P11E
          ,xs,ys,sig[1],sig[2],sig[3],sig[4],sig[5],rsig[1],rsig[2],rsig[3],rsig[4],rsig[5],sigv);
          }
        if(jpri == 1)
          {
          fprintf(fo5,NL P11E P11E P11E,xs,ys,sigvku[ngau]);
          }
        gmw[kc]+= sigv; 
        }
      }
    }
  gmw[kc]/= ninto*ninto;  /* Mittelwert berechnen */

/*======================================================================
* die Eckpunkte berechnen
*=====================================================================*/
  for(lx = 1;lx <= 4;lx++) 
    {
    r= rkr[lx];
    s= rks[lx];
      
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    iret= sab88(&det,&r,&s);
    if(iret != 0) return(iret);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Integrationspunkte in echte Koordinaten umrechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    xs= 0.;
    ys= 0.;
 
    for(j = 1;j <= 8;j++)
      {
      xs+= h[j] * xx[   j];
      ys+= h[j] * xx[8 +j];
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* welcher Knoten ist's wirklich?
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(j = 1;j <= 4;j++)
      {
      ax   = xk[j] - xs;
      ay   = yk[j] - ys;
      rv[j]= FR_SQRT(ax*ax + ay*ay);
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

    jp[lx]= jk;
    }

/*======================================================================
* Spannungen in den Gauss-Punkten berechnen, fix fuer Z88O
*=====================================================================*/
  for(lx = 1;lx <= 4;lx++) 
    {
    r= xgo[lx];
    s= ygo[lx];
      
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    iret= sab88(&det,&r,&s);
    if(iret != 0) return(iret);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verzerrungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 5;k++)
      {
      eps[k]= 0.;
      for(j = 1;j <= 24;j++)
        { 
        eps[k]+= b[(k-1)*24 + j] * ul[j];
        }
      }
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Spannungen berechnen: Biegemomente und Querkraefte pro Laenge
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 5;k++)
      {
      sig[k]= 0.;
      for(j = 1;j <= 5;j++)
        {
        sig[k]+= d[(k-1)*5 + j] * eps[j];
        }
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* echte Spannungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    fmom= 12.*(qparae/2.)/(qparae*qparae*qparae);

    for(k = 1;k <= 3;k++)
      rsig[k]= sig[k]*fmom;

    fque= 3./2. /qparae;

    for(k = 4;k <= 5;k++)
      rsig[k]= sig[k]*fque;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Vergleichsspannungen aufaddieren
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(isflag == 1) sigv= platgh(rsig);
    if(isflag == 2) sigv= platnh(rsig);
    if(isflag == 3) sigv= platsh(rsig);

    smw[koi[koffs[kc]+jp[lx]-1]]+= sigv;
    jsm[koi[koffs[kc]+jp[lx]-1]]++;
    }  /* Ende Z88O */
  }    /* Ende Gausspunkte variabel */  

/*----------------------------------------------------------------------
* Spannungen in den Eckknoten berechnen
*---------------------------------------------------------------------*/
if(ninto == 0)
  {
  for(lx = 1;lx <= 4;lx++)
    {
    r= rkr[lx];
    s= rks[lx];
      
/*======================================================================
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*=====================================================================*/
    iret= sab88(&det,&r,&s);
    if(iret != 0) return(iret);
    
/*======================================================================
* Verzerrungen berechnen
*=====================================================================*/
    for(k = 1;k <= 5;k++)
      {
      eps[k]= 0.;
      for(j = 1;j <= 24;j++)
        { 
        eps[k]+= b[(k-1)*24 + j] * ul[j];
        }
      }
 
/*======================================================================
* Spannungen berechnen: Biegemomente und Querkraefte pro Laenge
*=====================================================================*/
    for(k = 1;k <= 5;k++)
      {
      sig[k]= 0.;
      for(j = 1;j <= 5;j++)
        {
        sig[k]+= d[(k-1)*5 + j] * eps[j];
        }
      }

/*======================================================================
* echte Spannungen berechnen
*=====================================================================*/
    fmom= 12.*(qparae/2.)/(qparae*qparae*qparae);

    for(k = 1;k <= 3;k++)
      rsig[k]= sig[k]*fmom;

    fque= 3./2. /qparae;

    for(k = 4;k <= 5;k++)
      rsig[k]= sig[k]*fque;

/*======================================================================
* Eckpunkte in echte Koordinaten umrechnen
*=====================================================================*/
    xs= 0.;
    ys= 0.;
 
    for(j = 1;j <= 8;j++)
      {
      xs+= h[j] * xx[   j];
      ys+= h[j] * xx[8 +j];
      }

/*======================================================================
* Spannungen ausschreiben
*=====================================================================*/
    if(ifnili == 0)
      {
      fprintf(fo3,NL P10E P10E P11E P11E P11E P11E P11E P11E P11E P11E P11E P11E
      ,xs,ys,sig[1],sig[2],sig[3],sig[4],sig[5],rsig[1],rsig[2],rsig[3],rsig[4],rsig[5]);
      }
    }
  }

return(0);
}

/***********************************************************************
* hier beginnt Function sab88
***********************************************************************/
int sab88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s)
{
/*---------------------------------------------------------------------
* xx geht rein, unveraendert (ex)
* bbi und bsv gehen raus, neu (ex)
* det geht raus, neu
* r,s gehen rein, unveraendert
*--------------------------------------------------------------------*/

extern FR_DOUBLE h[];
extern FR_DOUBLE b[],xx[],p[];

FR_DOUBLE xj[5], xji[5];          /* ist 2x2 +1 */

FR_DOUBLE rp,sp,rm,sm,rqm,sqm,r2,s2,dum;
        
FR_INT4 i,j,k,k3;
         
/*----------------------------------------------------------------------
* Klammern der Formfunktionen belegen
*---------------------------------------------------------------------*/
rp= 1. + (*r);
sp= 1. + (*s);
rm= 1. - (*r);
sm= 1. - (*s);
rqm= 1. - (*r)*(*r);
sqm= 1. - (*s)*(*s);
r2= 2. * (*r);
s2= 2. * (*s);

/*----------------------------------------------------------------------
* Formfunktionen
*---------------------------------------------------------------------*/
h[1]= .25 *(rp*sp - rqm*sp - sqm*rp);
h[2]= .25 *(rm*sp - rqm*sp - sqm*rm);
h[3]= .25 *(rm*sm - sqm*rm - rqm*sm);
h[4]= .25 *(rp*sm - rqm*sm - sqm*rp);
h[5]= .5 *rqm*sp;
h[6]= .5 *sqm*rm;
h[7]= .5 *rqm*sm;
h[8]= .5 *sqm*rp;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach r
*---------------------------------------------------------------------*/
p[1]= .25 *(sp + r2*sp -sqm);
p[2]= .25 *((-sp) + r2*sp + sqm);
p[3]= .25 *((-sm) + sqm + r2*sm);
p[4]= .25 *(sm + r2*sm - sqm);
p[5]= .5 *(-r2)*sp;
p[6]= (-.5 )*sqm;
p[7]= .5 *(-r2)*sm;
p[8]= .5 *sqm;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach s
*---------------------------------------------------------------------*/
p[9] = .25 *(rp - rqm + s2*rp);
p[10]= .25 *(rm - rqm + s2*rm);
p[11]= .25 *((-rm) + s2*rm + rqm);
p[12]= .25 *((-rp) + rqm + s2*rp);
p[13]= .5 *rqm;
p[14]= .5 *(-s2)*rm;
p[15]= (-.5 )*rqm;
p[16]= .5 *(-s2)*rp;

/*----------------------------------------------------------------------
* Jacobi-Matrix am Punkt (r,s) entwickeln
*---------------------------------------------------------------------*/
for(i = 1;i <= 2;i++)
  {
  for(j = 1;j <= 2;j++)
    {
    dum= 0.;
    for(k = 1;k <= 8;k++)
      {
      dum+= p[(i-1)*8 + k] * xx[(j-1)*8 + k];
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
for(i = 1;i <= 5*24;i++)
  b[i]= 0.;

k3= 0;

for(k = 1;k <= 8;k++)
  {
  k3+= 3;

/*======================================================================
* Biegeanteile
*=====================================================================*/
  for(i = 1;i <= 2;i++)
    {
    b[   k3  ]+= xji[  i] * p[(i-1)*8+k];    /* 1.Zeile: B(1,3) */
    b[24+k3-1]-= xji[2+i] * p[(i-1)*8+k];    /* 2.Zeile: B(2,2) */
    }
  b[48+k3  ]= -b[24+k3-1];                   /* 3.Zeile: B(3,3) */
  b[48+k3-1]= -b[   k3  ];                   /* 3.Zeile: B(3,3) */

/*======================================================================
* Schubanteile
*=====================================================================*/
  for(i = 1;i <= 2;i++)
    {
    b[72+k3-2]+= xji[2+i] * p[(i-1)*8+k];    /* 4.Zeile: B(4,1) */
    b[96+k3-2]+= xji[  i] * p[(i-1)*8+k];    /* 5.Zeile: B(5,1) */
    }
  b[72+k3-1]= -h[k];                         /* 4.Zeile: B(4,2) */
  b[96+k3  ]=  h[k];                         /* 5.Zeile: B(5,3) */

  }

return(0);
}
