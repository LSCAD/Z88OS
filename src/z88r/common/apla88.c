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
* diese Compilerunit umfasst: apla88 - Elementsteifigkeitsroutine
*                             ab88   - Berechnung der Matrizen bbi & bsv
* 8-Knoten Serendipity Reissner- Mindlin- Platte
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
int ab88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s);

/***********************************************************************
* hier beginnt Function apla88
***********************************************************************/
int apla88(void)
{
extern FR_DOUBLEAY se;

extern FR_DOUBLE xk[],yk[];
extern FR_DOUBLE bbi[],bsv[],xx[],dbi[],dsv[],be[],hi[];

extern FR_DOUBLE emode,rnuee,qparae,riyye;

extern FR_INT4 intore,ipflag;

FR_DOUBLE dbbi[10],dbsv[5];

FR_DOUBLE facbi,facsv,r,s,det,wt,stiffbi,stiffsv,rmok,skf;

FR_INT4 ne= 24,i,lx,ly,j,k,l;

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
  xx[i]  = xk[i];
  xx[8+i]= yk[i];
  }

/*----------------------------------------------------------------------
* Elastizitaetsmatrix aufstellen: Platten-Biegung
*---------------------------------------------------------------------*/
facbi = emode*qparae*qparae*qparae/(12.*(1. - rnuee*rnuee));
dbi[1]= facbi;
dbi[2]= facbi * rnuee;
dbi[3]= 0.;
dbi[4]= dbi[2];
dbi[5]= dbi[1];
dbi[6]= 0.;
dbi[7]= 0.;
dbi[8]= 0.;
dbi[9]= facbi * .5 * (1. - rnuee);
        
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
dsv[1]= facsv;
dsv[2]= 0.;
dsv[3]= 0.;
dsv[4]= facsv;

/*----------------------------------------------------------------------
* Elementsteifigkeitsmatrix aufstellen
*---------------------------------------------------------------------*/
for(i = 1;i <= 576;i++)
  se[i]= 0.;

for(i = 1;i <= 24;i++)
  be[i]= 0.;

for(lx = 1;lx <= intore;lx++)
  {
  r= xg[(lx-1)*4 + intore];
  for(ly = 1;ly <= intore;ly++)
    {
    s= xg[(ly-1)*4 + intore];

/*======================================================================
* Matrix b der partiellen Ableitungen & Jacobi Determinante holen
*=====================================================================*/
    iret= ab88(&det,&r,&s);
    if(iret != 0) return(iret);
    
    wt= wgt[(lx-1)*4 + intore] * wgt[(ly-1)*4 + intore] * det;

/*======================================================================
* Element- Lastvektor be
*=====================================================================*/
    for(j = 1;j <= 24;j++)
      {
      be[j]+= hi[j]*wt*riyye;
      }
 
/*======================================================================
* Start Steifigkeitsmatrix
*=====================================================================*/
    for(j = 1;j <= 24;j++)
      {
 
/*======================================================================
* Biegeverzerrung: DBBI= B*C fuer Biegung
*=====================================================================*/
      for(k = 1;k <= 3;k++)
        {
        dbbi[k]= 0.;
        for(l = 1;l <= 3;l++)
          {
          dbbi[k]+= dbi[(k-1)*3 + l] * bbi[(l-1)*24 + j];
          }
        }

/*======================================================================
* Schubverzerrung: DBSV= B*C fuer Schub
*=====================================================================*/
      for(k = 1;k <= 2;k++)
        {
        dbsv[k]= 0.;
        for(l = 1;l <= 2;l++)
          {
          dbsv[k]+= dsv[(k-1)*2 + l] * bsv[(l-1)*24 + j];
          }
        }

/*======================================================================
* Steifigkeitsmatrix: Die jeweiligen DB's * B und aufsummieren
*=====================================================================*/
      for(i = j;i <= 24;i++)
        {
        stiffbi= 0.;
        stiffsv= 0.;
        
        for(l = 1;l <= 3;l++)
          stiffbi+= bbi[(l-1)*24 + i] * dbbi[l];

        for(l = 1;l <= 2;l++)
          stiffsv+= bsv[(l-1)*24 + i] * dbsv[l];

        se[i+ne*(j-1)]= se[i+ne*(j-1)] + (stiffbi+stiffsv) * wt;
        }
      }
    }
  }

/*======================================================================
* die andere Haelfte der Steifigkeitsmatrix
*=====================================================================*/
for(j = 1;j <= 24;j++)
  {  
  for(i = j;i <= 24;i++)
    {
    se[j+ne*(i-1)]= se[i+ne*(j-1)];
    }
  }

return(0);
}

/***********************************************************************
* hier beginnt Function ab88
***********************************************************************/
int ab88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s)
{
/*---------------------------------------------------------------------
* xx geht rein, unveraendert (ex)
* bbi und bsv gehen raus, neu (ex)
* det geht raus, neu
* r,s gehen rein, unveraendert
*--------------------------------------------------------------------*/

extern FR_DOUBLE h[];
extern FR_DOUBLE bbi[],bsv[],xx[],p[],hi[];

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
* Entwickeln der Matrix bbi fuer Biegung
*---------------------------------------------------------------------*/
for(i = 1;i <= 3*24;i++)
  bbi[i]= 0.;

k3= 0;

for(k = 1;k <= 8;k++)
  {
  k3+= 3;

  for(i = 1;i <= 2;i++)
    {
    bbi[   k3  ]+= xji[  i] * p[(i-1)*8+k];
    bbi[24+k3-1]-= xji[2+i] * p[(i-1)*8+k];
    }
  bbi[48+k3  ]= -bbi[24+k3-1];
  bbi[48+k3-1]= -bbi[   k3  ];
  }

/*----------------------------------------------------------------------
* Entwickeln der Matrix bsv fuer Schub
*---------------------------------------------------------------------*/
for(i = 1;i <= 2*24;i++)
  bsv[i]= 0.;

k3= 0;

for(k = 1;k <= 8;k++)
  {
  k3+= 3;

  for(i = 1;i <= 2;i++)
    {
    bsv[   k3-2]+= xji[2+i] * p[(i-1)*8+k];
    bsv[24+k3-2]+= xji[  i] * p[(i-1)*8+k];
    }
  bsv[   k3-1]= -h[k];
  bsv[24+k3  ]=  h[k];
  }

/*----------------------------------------------------------------------
* Entwickeln der Formfunktionen fuer den Lastvektor be
*---------------------------------------------------------------------*/
for(i = 1;i <= 24;i++)
  hi[i]= 0.;

k3= 1;

for(k = 1;k <= 8;k++)
  {
  hi[k3]= h[k];  
  k3+= 3;
  }

return(0);
}
