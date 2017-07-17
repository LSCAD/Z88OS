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
* diese Compilerunit umfasst: bshav88 - Routine Lastvektor
* ruft aus BAPLA88.C:         bab88   - Formfunktionen und Ableitungen
* 8-Knoten Serendipity flache Schale, viereckig
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
int bab88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s);

/***********************************************************************
* hier beginnt Function bshav88
***********************************************************************/
int bshav88(void)
{
extern FR_DOUBLE xk[],yk[],zk[];
extern FR_DOUBLE xx[],be[],hi[];
extern FR_DOUBLE xc[],yc[],zc[];

extern FR_DOUBLEAY tmt;
extern FR_DOUBLEAY tm;

extern FR_DOUBLE pree;

extern FR_INT4   intore;

FR_DOUBLE        bez[49];
FR_DOUBLE        a21x,a21y,a21z,rl21,a41x,a41y,a41z;
FR_DOUBLE        azsx,azsy,azsz,rlzs,aysx,aysy,aysz,rlys;
FR_DOUBLE        vxx,vxy,vxz,vyx,vyy,vyz,vzx,vzy,vzz;

FR_DOUBLE        r,s,det,wt,sum;

FR_INT4          ne= 24,i,lx,ly,j,inc,k;

int              iret;
  
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
* Vektor 4-1 wird fuer Kreuzprodukt azs gebraucht
*=====================================================================*/
a41x= xk[4]-xk[1];
a41y= yk[4]-yk[1];
a41z= zk[4]-zk[1];

/*======================================================================
* azs ist Kreuzprodukt aus a21 und a41 und bildet die lokale Achse z'
*=====================================================================*/
azsx= a21y*a41z - a21z*a41y;
azsy= a21z*a41x - a21x*a41z;
azsz= a21x*a41y - a21y*a41x;
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
for(i= 1; i <= 8; i++)
  {
  xc[i]= xk[i];
  yc[i]= yk[i];
  zc[i]= zk[i];
  }

/*======================================================================
* nun Koordinaten transformieren, xk,yk,zk sind nun lokal
*=====================================================================*/
for(i= 1; i <= 8; i++)
  {
  xk[i]= vxx*xc[i] + vxy*yc[i] + vxz*zc[i];
  yk[i]= vyx*xc[i] + vyy*yc[i] + vyz*zc[i];
  zk[i]= vzx*xc[i] + vzy*yc[i] + vzz*zc[i]; /* wird nicht gebraucht */
  }

/*----------------------------------------------------------------------
* xk und yk nochmal umspeichern
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

/*----------------------------------------------------------------------
* die Transformationsmatrix tm und die Transponierte tmt aufstellen
*---------------------------------------------------------------------*/
/*======================================================================
* Transformationsmatrix tm
*=====================================================================*/
for(i = 1; i <= 2304; i++)
  tm[i]= 0.;

for(i = 1; i <= 2304; i++)
  tmt[i]= 0.;

inc= 0;

for(i = 1; i <= 16; i++)
  {
  tm[inc*48+inc   +1]= vxx;
  tm[inc*48+inc   +2]= vxy;
  tm[inc*48+inc   +3]= vxz;
  tm[inc*48+inc+48+1]= vyx;
  tm[inc*48+inc+48+2]= vyy;
  tm[inc*48+inc+48+3]= vyz;
  tm[inc*48+inc+96+1]= vzx;
  tm[inc*48+inc+96+2]= vzy;
  tm[inc*48+inc+96+3]= vzz;
  inc+= 3;
  }

/*======================================================================
* Transponierte tmt der Transformationsmatrix tm
*=====================================================================*/
for(i= 1; i <= 48; i++)
  {
  for(j= 1; j <= 48; j++)
    {
    tmt[(i-1)*48+j]= tm[(j-1)*48+i];
    }
  }

/*----------------------------------------------------------------------
* den Lastvektor modifizieren und transformieren
*---------------------------------------------------------------------*/
for(i = 1; i <= 48; i++)
  bez[i]= 0.;

bez[ 3]= be[ 1];  /* Ux=1,Uy=2,Uz=3,ThetaX=4 --> w=1,thetax=2,theay=3 */
bez[ 9]= be[ 4];
bez[15]= be[ 7];
bez[21]= be[10];
bez[27]= be[13];
bez[33]= be[16];
bez[39]= be[19];
bez[45]= be[22];

/*======================================================================
* Matrix-Vektorprodukt: tmt * bez = be
*=====================================================================*/
for(i = 1;i <= 48;i++)
  {
  sum= 0.;
  for(k = 1; k <= 48; k++)
    {
    sum+= tmt[(i-1)*48+k] * bez[k];
    }
  be[i]= sum;
  }

return(0);
}

