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
* diese Compilerunit umfasst: bapla88 - Elementsteifigkeitsroutine
*                             bab88   - Berechnung der Matrizen bbi & bsv
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
* Fuer Windows & GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88r.h>
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int bab88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s);

/***********************************************************************
* hier beginnt Function bapla88
***********************************************************************/
int bapla88(void)
{
extern FR_DOUBLEAY se;

extern FR_DOUBLE xk[],yk[];
extern FR_DOUBLE xx[],be[],hi[];

extern FR_DOUBLE pree;

extern FR_INT4 intore;

FR_DOUBLE r,s,det,wt;

FR_INT4 ne=24,i,lx,ly,j;

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
* Lastvektor aufstellen
*---------------------------------------------------------------------*/
for(i = 1;i <= ne;i++)
  be[i]= 0.;

for(lx = 1;lx <= intore;lx++)
  {
  r= xg[(lx-1)*4 + intore];
  for(ly = 1;ly <= intore;ly++)
    {
    s= xg[(ly-1)*4 + intore];

/*======================================================================
* Matrix be der partiellen Ableitungen & Jacobi Determinante holen
*=====================================================================*/
    iret= bab88(&det,&r,&s);
    if(iret != 0) return(iret);
    
    wt= wgt[(lx-1)*4 + intore] * wgt[(ly-1)*4 + intore] * det;

/*======================================================================
* Element- Lastvektor be
*=====================================================================*/
    for(j = 1;j <= ne;j++)
      {
      be[j]+= hi[j]*wt*pree;
      }
    }
  }

return(0);
}

/***********************************************************************
* hier beginnt Function bab88
***********************************************************************/
int bab88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s)
{
/*---------------------------------------------------------------------
* xx geht rein, unveraendert (ex)
* det geht raus, neu
* r,s gehen rein, unveraendert
*--------------------------------------------------------------------*/

extern FR_DOUBLE h[];
extern FR_DOUBLE xx[],p[],hi[];

FR_DOUBLE xj[5];          /* ist 2x2 +1 */

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

if((*det) < 1e-88)
  return(AL_JACNEG);

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
