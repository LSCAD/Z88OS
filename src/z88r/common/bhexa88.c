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
* diese Compilerunit umfasst: bhexa88 - Lastvektorroutine Ele 10
*                             bhb88   - Formfunktionen und Ableitungen 
* 2.1.2010 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>
#endif

/***********************************************************************
* Fuer Windows 
***********************************************************************/
#ifdef FR_WIN 
#include <z88r.h>
#include <stdio.h>
#endif

/***********************************************************************
* Fuer Windows & GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88r.h>
#include <stdio.h>
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int bhb88(FR_DOUBLE *,FR_DOUBLE *,FR_DOUBLE *);

/***********************************************************************
* hier beginnt Function bhexa88
***********************************************************************/
int bhexa88(void)
{
extern FR_DOUBLE xk[],yk[],zk[];
extern FR_DOUBLE be[],hi[],hj[],hk[];

extern FR_DOUBLE pree,tr1e,tr2e;

extern FR_INT4   intore;

FR_DOUBLE        det,r,s,wt;

FR_INT4          i,lx,ly,j;

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
* Elementlastvektor aufstellen
*---------------------------------------------------------------------*/
for(i = 1;i <= 24;i++)
  be[i]= 0.;

for(lx = 1;lx <= intore;lx++)
  {
  r= xg[(lx-1)*4 + intore];
  for(ly = 1;ly <= intore;ly++)
    {
    s= xg[(ly-1)*4 + intore];
       
/*======================================================================
* Matrix b der partiellen Ableitungen, Lastvektor be 
*=====================================================================*/
    bhb88(&det,&r,&s);
    
    wt= wgt[(lx-1)*4 + intore] * wgt[(ly-1)*4 + intore];

    for(j = 1;j <= 24;j++)
      {
      be[j]+= hi[j]*wt*pree+hj[j]*wt*det*(-tr1e)+hk[j]*wt*det*(-tr2e);
      }
    }
  }

return(0);
}

/***********************************************************************
* hier beginnt Function bhb88
***********************************************************************/
int bhb88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s)
{
extern FR_DOUBLE h[],hi[],hj[],hk[],p[],xk[],yk[],zk[];

FR_DOUBLE rp,sp,rm,sm,rqm,sqm,r2,s2;
FR_DOUBLE sx,sy,sz,sx1,sx2,sx3,sx4,sy1,sy2,sy3,sy4,sz1,sz2,sz3,sz4;
FR_DOUBLE ax,ay,az,bx,by,bz;
        
FR_INT4 i,k;
         
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
* Entwickeln der Formfunktionen fuer den Lastvektor be
*---------------------------------------------------------------------*/
/*----------------------------------------------------------------------
* Normalenvektor am Punkt (x,y,z) entwickeln
*---------------------------------------------------------------------*/
sx1=0.;
sx2=0.;
sx3=0.;
sx4=0.;
sy1=0.;
sy2=0.;
sy3=0.;
sy4=0.;
sz1=0.;
sz2=0.;
sz3=0.;
sz4=0.;

for(k = 1;k <= 8;k++)
  {
  sx1+= p[8+k]*yk[k]; 
  sx2+= p[k  ]*zk[k];
  sx3+= p[k  ]*yk[k];
  sx4+= p[8+k]*zk[k];

  sy1+= p[8+k]*zk[k]; 
  sy2+= p[k  ]*xk[k];
  sy3+= p[k  ]*zk[k];
  sy4+= p[8+k]*xk[k];

  sz1+= p[8+k]*xk[k]; 
  sz2+= p[k  ]*yk[k];
  sz3+= p[k  ]*xk[k];
  sz4+= p[8+k]*yk[k];
  }
sx= sx1*sx2-sx3*sx4;                 /* Normalenvektor */
sy= sy1*sy2-sy3*sy4;
sz= sz1*sz2-sz3*sz4;

/*----------------------------------------------------------------------
* Normalerweise muesste der Normalenvektor normiert, d.h. durch sein
* Laenge geteilt werden. Bei der Integration kommt dafuer wieder die
* Laenge des Normalenvektors als Flaechenelement (als Jacobi-Det.)
* hinzu, sodass sich beide gegeneinander kuerzen.
*---------------------------------------------------------------------*/

/*----------------------------------------------------------------------
* Tangentenvektor r am Punkt (x,y,z) entwickeln und normieren
*---------------------------------------------------------------------*/
bx= sy2/FR_SQRT(sy2*sy2 + sx3*sx3 + sy3*sy3);  /* dx/dr = bx = sy2 */
by= sx3/FR_SQRT(sy2*sy2 + sx3*sx3 + sy3*sy3);  /* dx/dr = by = sx3 */
bz= sy3/FR_SQRT(sy2*sy2 + sx3*sx3 + sy3*sy3);  /* dx/dr = bz = sy3 */

/*----------------------------------------------------------------------
* Tangentenvektor s am Punkt (x,y,z) entwickeln und normieren
*---------------------------------------------------------------------*/
ax= sz1/FR_SQRT(sz1*sz1 + sz4*sz4 + sx4*sx4);  /* dx/ds = ax = sz1 */
ay= sz4/FR_SQRT(sz1*sz1 + sz4*sz4 + sx4*sx4);  /* dx/ds = ay = sz4 */
az= sx4/FR_SQRT(sz1*sz1 + sz4*sz4 + sx4*sx4);  /* dx/ds = az = sx4 */

/*----------------------------------------------------------------------
* "Jacobi-Determinante" am Punkt (x,y,z) entwickeln fuer die Tangenten-
* vektoren r und s
*---------------------------------------------------------------------*/
(*det)= FR_SQRT(sx*sx + sy*sy + sz*sz);

/*----------------------------------------------------------------------
* Entwickeln der Formfunktionen fuer den Lastvektor be
*---------------------------------------------------------------------*/
for(i = 1;i <= 24;i++)
  {
  hi[i]= 0.;
  hj[i]= 0.;
  hk[i]= 0.;
  }

for(k = 1;k <= 8;k++)
  {
  hi[(k-1)*3+1]= h[k]*sx; 
  hi[(k-1)*3+2]= h[k]*sy;  
  hi[(k-1)*3+3]= h[k]*sz;  
  } 

for(k = 1;k <= 8;k++)
  {
  hj[(k-1)*3+1]= h[k]*bx;  
  hj[(k-1)*3+2]= h[k]*by;  
  hj[(k-1)*3+3]= h[k]*bz;  
  } 

for(k = 1;k <= 8;k++)
  {
  hk[(k-1)*3+1]= h[k]*ax;  
  hk[(k-1)*3+2]= h[k]*ay;  
  hk[(k-1)*3+3]= h[k]*az;  
  } 

return(0);
}

