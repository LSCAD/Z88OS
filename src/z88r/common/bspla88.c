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
* diese Compilerunit umfasst: bspla88 - Routine Lastvektor
*                             bssb88  - Formfunktionen und Ableitungen
* 6-Knoten Serendipity Reissner- Mindlin- Platte, dreieckig
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
int bssb88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s);

/***********************************************************************
* hier beginnt Function bspla88
***********************************************************************/
int bspla88(void)
{
extern FR_DOUBLE xk[],yk[];
extern FR_DOUBLE xx[],be[],hi[];

extern FR_DOUBLE pree;

extern FR_INT4   intore;

FR_DOUBLE        r,s,det,wt;

FR_INT4          ne= 18,i,igauss,j;

int              iret;
  
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
* intore anpassen, damit Mischen mit apla88 via z88g moeglich ist
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
* Lastvektor aufstellen
*---------------------------------------------------------------------*/
for(i = 1;i <= ne;i++)
  be[i]= 0.;

for(igauss = 1;igauss <= intore;igauss++)
  {
  r= rg[igauss+2*intore];
  s= sg[igauss+2*intore];

/*======================================================================
* Matrix be der partiellen Ableitungen & Jacobi Determinante holen
*=====================================================================*/
  iret= bssb88(&det,&r,&s);
  if(iret != 0) return(iret);

  wt= wg[igauss+2*intore]*0.5 * det; /* Gaussg. halbieren */

/*======================================================================
* Element- Lastvektor be
*=====================================================================*/
  for(j = 1;j <= ne;j++)
    {
    be[j]+= hi[j]*wt*pree;
    }
  }

return(0);
}

/***********************************************************************
* hier beginnt Function bssb88
***********************************************************************/
int bssb88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s)
{
/*---------------------------------------------------------------------
* xx geht rein, unveraendert (ex)
* bbi und bsv gehen raus, neu (ex)
* det geht raus, neu
* r,s gehen rein, unveraendert
*--------------------------------------------------------------------*/
extern FR_DOUBLE h[];
extern FR_DOUBLE xx[],p[],hi[],xk[],yk[],zk[];

FR_DOUBLE xj[5];          /* ist 2x2 +1 */

FR_DOUBLE rr2,ss2,r4,r3,s4,s3,rs4,dum;
/* FR_DOUBLE sx,sy,sz,sx1,sx2,sx3,sx4,sy1,sy2,sy3,sy4,sz1,sz2,sz3,sz4; */       
FR_INT4 i,j,k,k3;
         
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

if((*det) < 1e-88)
  return(AL_JACLOA);

/*----------------------------------------------------------------------
* Entwickeln der Formfunktionen fuer den Lastvektor be
*---------------------------------------------------------------------*/
for(i = 1;i <= 18;i++)
  hi[i]= 0.;

k3= 1;

for(k = 1;k <= 6;k++)
  {
  hi[k3]= h[k];  
  k3+= 3;
  }

return(0);
}
