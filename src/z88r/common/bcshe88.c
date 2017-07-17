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
* diese Compilerunit umfasst: bcshe88 - Routine Lastvektor
*                               bcb88  - Formfunktionen und Ableitungen
* 8-Knoten Serendipity Scheibe
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
int bcb88(FR_DOUBLE s);

/***********************************************************************
* hier beginnt Function bcshe88
***********************************************************************/
int bcshe88(void)
{
extern FR_DOUBLE xk[],yk[];
extern FR_DOUBLE be[],hi[],hj[];

extern FR_DOUBLE pree,tr1e;

extern FR_INT4   intore;

FR_DOUBLE        s,wt;

FR_INT4          i,ly,j;

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
* Lastvektor aufstellen
*---------------------------------------------------------------------*/
for(i = 1;i <= 8;i++)
  be[i]= 0.;

for(ly = 1;ly <= intore;ly++) 
  {
  s= xg[(ly-1)*4 + intore];

/*======================================================================
* Matrix be der partiellen Ableitungen & Jacobi Determinante holen
*=====================================================================*/
  bcb88(s);

  wt= wgt[(ly-1)*4 + intore];

/*======================================================================
* Element- Lastvektor be
*=====================================================================*/
  for(j = 1;j <= 8;j++)
    {
    be[j]+= hi[j]*wt*pree + hj[j]*wt*tr1e;
    }

  }

return(0);
}

/***********************************************************************
* hier beginnt Function bcb88
***********************************************************************/
int bcb88(FR_DOUBLE s)
{
/*---------------------------------------------------------------------
* s geht rein, unveraendert
*--------------------------------------------------------------------*/
extern FR_DOUBLE hi[],hj[],xk[],yk[],zk[];

FR_DOUBLE f1,f2,f3,f4,dn1,dn2,dn3,dn4,dxs,dys;

FR_DOUBLE sh3,sh2,sh1,es;

/*----------------------------------------------------------------------
* Klammern der Formfunktionen belegen
*---------------------------------------------------------------------*/
sh3= s * s * s;
sh2= s * s;
sh1= s;
es = 1./16.;

/*----------------------------------------------------------------------
* Formfunktionen
*---------------------------------------------------------------------*/
f1= es*(  9.*sh3 + 9.*sh2 -    sh1 - 1.);   /* Knoten 2 */
f2= es*(- 9.*sh3 + 9.*sh2 +    sh1 - 1.);   /* Knoten 3 */
f3= es*(-27.*sh3 - 9.*sh2 + 27*sh1 + 9.);   /* Knoten 7 */
f4= es*( 27.*sh3 - 9.*sh2 - 27*sh1 + 9.);   /* Knoten 8 */

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach s
*---------------------------------------------------------------------*/
dn1= es*( 27.*sh2 + 18.*sh1 -  1.);         /* Knoten 2 */
dn2= es*(-27.*sh2 + 18.*sh1 +  1.);         /* Knoten 3 */
dn3= es*(-81.*sh2 - 18.*sh1 + 27.);         /* Knoten 7 */
dn4= es*( 81.*sh2 - 18.*sh1 - 27.);         /* Knoten 8 */
          
/*-------------------------------------------------------------
* Summe Ableitungen x Koordinaten: 
* dN1/ds * x1 + dN2/ds * x2 + dN3/ds * x3 + dN4/ds * x4
* dN1/ds * y1 + dN2/ds * y2 + dN3/ds * y3 + dN4/ds * y4
*------------------------------------------------------------*/
dxs= dn1*xk[1] + dn2*xk[2] + dn3*xk[3] + dn4*xk[4];
dys= dn1*yk[1] + dn2*yk[2] + dn3*yk[3] + dn4*yk[4];

/*----------------------------------------------------------------------
* Entwickeln der Formfunktionen fuer den Lastvektor be
*---------------------------------------------------------------------*/
hi[1]= f1* dys; 
hi[2]= f1*-dxs;  
hi[3]= f2* dys; 
hi[4]= f2*-dxs;  
hi[5]= f3* dys; 
hi[6]= f3*-dxs;  
hi[7]= f4* dys; 
hi[8]= f4*-dxs; 

hj[1]= f1*-dxs; 
hj[2]= f1*-dys;  
hj[3]= f2*-dxs; 
hj[4]= f2*-dys;  
hj[5]= f3*-dxs; 
hj[6]= f3*-dys; 
hj[7]= f4*-dxs; 
hj[8]= f4*-dys; 
 
return(0);
}
