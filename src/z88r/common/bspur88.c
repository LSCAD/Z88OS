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
* Z88 should compile and run under any Windows & UNIX OS and GTK+.
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
* diese Compilerunit umfasst: bspur88 - Lastvektorroutine Ele 17
*                             bsb88   - Formfunktionen und Ableitungen 
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
int bsb88(FR_DOUBLE *,FR_DOUBLE *);

/***********************************************************************
* hier beginnt Function bspur88
***********************************************************************/
int bspur88(void)
{
extern FR_DOUBLE xk[],yk[],zk[];
extern FR_DOUBLE be[],hi[];

extern FR_DOUBLE pree;

extern FR_INT4   intore;

FR_DOUBLE        r,s,wt;

FR_INT4          i,igauss,j;

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
* intore anpassen, damit Verwendung mit spur88 moeglich ist
*---------------------------------------------------------------------*/
if(intore == 1 || intore == 4) intore = 3;
if(intore == 5)                intore = 7;

/*----------------------------------------------------------------------
* Elementlastvektor aufstellen
*---------------------------------------------------------------------*/
for(i = 1;i <= 9;i++)
  be[i]= 0.;

for(igauss = 1;igauss <= intore;igauss++)
  {
  r= rg[igauss+2*intore];
  s= sg[igauss+2*intore];
       
/*======================================================================
* Matrix b der partiellen Ableitungen & Jacobi Determinante holen
*=====================================================================*/
  bsb88(&r,&s);

  wt= wg[igauss+2*intore]*0.5 ; /* Gaussg. halbieren */

  for(j = 1;j <= 9;j++)
    {
    be[j]+= hi[j]*wt*pree;
    }
  }

return(0);
}

/***********************************************************************
* hier beginnt Function bsb88
***********************************************************************/
int bsb88(FR_DOUBLE *r,FR_DOUBLE *s)
{
extern FR_DOUBLE h[],hi[],p[],xk[],yk[],zk[];

FR_DOUBLE sx,sy,sz,sx1,sx2,sx3,sx4,sy1,sy2,sy3,sy4,sz1,sz2,sz3,sz4;
        
FR_INT4 i,k;
         
/*----------------------------------------------------------------------
* Formfunktionen
*---------------------------------------------------------------------*/
h[1]= 1. - (*r) - (*s);
h[2]= (*r);
h[3]= (*s);

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach r
*---------------------------------------------------------------------*/
p[1]= -1.;
p[2]= 1.;
p[3]= 0.;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach s
*---------------------------------------------------------------------*/
p[4] = -1.;
p[5] = 0.;
p[6] = 1.;

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

for(k = 1;k <= 3;k++)
  {
  sx1+= p[3+k]*yk[k]; 
  sx2+= p[k  ]*zk[k];
  sx3+= p[k  ]*yk[k];
  sx4+= p[3+k]*zk[k];

  sy1+= p[3+k]*zk[k]; 
  sy2+= p[k  ]*xk[k];
  sy3+= p[k  ]*zk[k];
  sy4+= p[3+k]*xk[k];

  sz1+= p[3+k]*xk[k]; 
  sz2+= p[k  ]*yk[k];
  sz3+= p[k  ]*xk[k];
  sz4+= p[3+k]*yk[k];
  }
sx= sx1*sx2-sx3*sx4;                 /* Normalenvektor */
sy= sy1*sy2-sy3*sy4;
sz= sz1*sz2-sz3*sz4;

/*----------------------------------------------------------------------
* Entwickeln der Formfunktionen fuer den Lastvektor be
*---------------------------------------------------------------------*/
for(i = 1;i <= 9;i++)
  hi[i]= 0.;

for(k = 1;k <= 3;k++)
  {
  hi[(k-1)*3+1]= h[k]*sx; 
  hi[(k-1)*3+2]= h[k]*sy;  
  hi[(k-1)*3+3]= h[k]*sz;  
  } 

return(0);
}

