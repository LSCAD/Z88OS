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
* V14.0 January 14, 2011
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
* diese Compilerunit umfasst: bshaf88 - Routine Lastvektor
* ruft aus BSPAL88.C:         bssb88  - Formfunktionen und Ableitungen
* 6-Knoten Serendipity Reissner- Mindlin-Platte, dreieckig
* 24.5.2012 Rieg
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
* Fuer Windows und GTK+
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
* hier beginnt Function bshaf88
***********************************************************************/
int bshaf88(void)
{
extern FR_DOUBLE xk[],yk[],zk[];
extern FR_DOUBLE xx[],be[],hi[];
extern FR_DOUBLE xc[],yc[],zc[];

extern FR_DOUBLEAY tmt;
extern FR_DOUBLEAY tm;

extern FR_DOUBLE pree;

extern FR_INT4   intore;

FR_DOUBLE        bez[37];
FR_DOUBLE        a21x,a21y,a21z,rl21,a31x,a31y,a31z;
FR_DOUBLE        azsx,azsy,azsz,rlzs,aysx,aysy,aysz,rlys;
FR_DOUBLE        vxx,vxy,vxz,vyx,vyy,vyz,vzx,vzy,vzz;

FR_DOUBLE        r,s,det,wt,sum;

FR_INT4          ne= 18,i,igauss,j,inc,k;

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
* globale Koordinaten in lokale Koordinaten umrechnen
*---------------------------------------------------------------------*/
/*======================================================================
* Vektor 2-1 spannt die lokale x-Achse x' auf
*=====================================================================*/
a21x= xk[2] - xk[1]; 
a21y= yk[2] - yk[1];
a21z= zk[2] - zk[1];
rl21 = sqrt(a21x*a21x + a21y*a21y + a21z*a21z);

/*======================================================================
* Vektor 3-1 wird fuer Kreuzprodukt azs gebraucht
*=====================================================================*/
a31x= xk[3]-xk[1];
a31y= yk[3]-yk[1];
a31z= zk[3]-zk[1];

/*======================================================================
* azs ist Kreuzprodukt aus a21 und a31 und bildet die lokale Achse z'
*=====================================================================*/
azsx= a21y*a31z - a21z*a31y;
azsy= a21z*a31x - a21x*a31z;
azsz= a21x*a31y - a21y*a31x;
rlzs = sqrt(azsx*azsx + azsy*azsy + azsz*azsz);

/*======================================================================
* ays ist Kreuzprodukt aus azs und a21 und bildet die lokale Achse y'
*=====================================================================*/
aysx= azsy*a21z - azsz*a21y;
aysy= azsz*a21x - azsx*a21z;
aysz= azsx*a21y - azsy*a21x;
rlys = sqrt(aysx*aysx + aysy*aysy + aysz*aysz);
 
/*======================================================================
* Richtungscosinus x'x, x'y und x'z
*=====================================================================*/
vxx=a21x/rl21;
vxy=a21y/rl21;
vxz=a21z/rl21;

/*======================================================================
* Richtungscosinus y'x, y'y und y'z
*=====================================================================*/
vyx=aysx/rlys;
vyy=aysy/rlys;
vyz=aysz/rlys;

/*======================================================================
* Richtungscosinus z'x, z'y und z'z
*=====================================================================*/
vzx=azsx/rlzs;
vzy=azsy/rlzs;
vzz=azsz/rlzs;

/*======================================================================
* xk auf xc zwischensichern, damit xk lokal werden kann
*=====================================================================*/
for(i= 1; i <= 6; i++)
  {
  xc[i]= xk[i];
  yc[i]= yk[i];
  zc[i]= zk[i];
  }

/*======================================================================
* nun Koordinaten transformieren, xk,yk,zk sind nun lokal
*=====================================================================*/
for(i= 1; i <= 6; i++)
  {
  xk[i]= vxx*xc[i] + vxy*yc[i] + vxz*zc[i];
  yk[i]= vyx*xc[i] + vyy*yc[i] + vyz*zc[i];
  zk[i]= vzx*xc[i] + vzy*yc[i] + vzz*zc[i]; /* wird nicht gebraucht */
  }

/*----------------------------------------------------------------------
* xk und yk nochmal umspeichern
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

  }  /* Ende Schleife igauss */

/*----------------------------------------------------------------------
* die Transformationsmatrix tm und die Transponierte tmt aufstellen
*---------------------------------------------------------------------*/
/*======================================================================
* Transformationsmatrix tm
*=====================================================================*/
for(i = 1; i <= 1296; i++)
  tm[i]= 0.;

for(i = 1; i <= 1296; i++)
  tmt[i]= 0.;

inc= 0;

for(i = 1; i <= 12; i++)
  {
  tm[inc*36+inc   +1]= vxx;
  tm[inc*36+inc   +2]= vxy;
  tm[inc*36+inc   +3]= vxz;
  tm[inc*36+inc+36+1]= vyx;
  tm[inc*36+inc+36+2]= vyy;
  tm[inc*36+inc+36+3]= vyz;
  tm[inc*36+inc+72+1]= vzx;
  tm[inc*36+inc+72+2]= vzy;
  tm[inc*36+inc+72+3]= vzz;
  inc+= 3;
  }

/*======================================================================
* Transponierte tmt der Transformationsmatrix tm
*=====================================================================*/
for(i= 1; i <= 36; i++)
  {
  for(j= 1; j <= 36; j++)
    {
    tmt[(i-1)*36+j]= tm[(j-1)*36+i];
    }
  }

/*----------------------------------------------------------------------
* den Lastvektor modifizieren und transformieren
*---------------------------------------------------------------------*/
for(i = 1; i <= 36; i++)
  bez[i]= 0.;

bez[ 3]= be[ 1];
bez[ 9]= be[ 4];
bez[15]= be[ 7];
bez[21]= be[10];
bez[27]= be[13];
bez[33]= be[16];

/*======================================================================
* Matrix-Vektorprodukt: tmt * bez = be
*=====================================================================*/
for(i = 1;i <= 36;i++)
  {
  sum= 0.;
  for(k = 1; k <= 36; k++)
    {
    sum+= tmt[(i-1)*36+k] * bez[k];
    }
  be[i]= sum;
  }

return(0);
}

