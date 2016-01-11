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
* diese Compilerunit umfasst: shaf88 - Elementsteifigkeitsroutine
*    ruft                   : isod88 - der Scheibenanteil
*                           : spla88 - der Plattenanteil
* 24.5.2012 Rieg
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
int isod88(void);
int spla88(void);

/***********************************************************************
* hier beginnt Function shaf88
***********************************************************************/
int shaf88(void)
{
extern FR_DOUBLEAY se;
extern FR_DOUBLEAY sdu;
extern FR_DOUBLEAY tmt;
extern FR_DOUBLEAY tm;
extern FR_DOUBLEAY zm;

extern FR_DOUBLE xk[],yk[],zk[],be[];
extern FR_DOUBLE xc[],yc[],zc[];
extern FR_INT4 ktyp,ipflag,ihflag,intore;

FR_DOUBLE bez[37];
FR_DOUBLE a21x,a21y,a21z,rl21,a31x,a31y,a31z;
FR_DOUBLE azsx,azsy,azsz,rlzs,aysx,aysy,aysz,rlys;
FR_DOUBLE vxx,vxy,vxz,vyx,vyy,vyz,vzx,vzy,vzz;

FR_DOUBLE beta,diamin,sum;

FR_INT4 i,j,k,m,l,isdu,ise,inc;

int iret;
  
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
* die Scheibenrotine isod88 aufrufen
*---------------------------------------------------------------------*/
ktyp= 2;
iret= isod88();

/*----------------------------------------------------------------------
* die Ergebnisse Scheibe in die Steifigkeitsmatrix einbauen
*---------------------------------------------------------------------*/
for(i = 1; i <= 1296; i++)
  sdu[i]= 0.;

isdu= 0;
ise = 0;

for(l = 1; l <= 6; l++)
  {
  for(m = 1; m <= 2; m++)
    {
    j= 0;
    for(i= 1; i <= 6; i++)
      {
      for(k= 1; k <= 2; k++)
        {
        j++;
        sdu[(isdu+m-1)*36 + (i-1)*6+k]= se[(ise+m-1)*12 + j];
        }
      }
    }
  isdu+= 6;
  ise += 2;
  }

/*----------------------------------------------------------------------
* die Plattenroutine spla88 aufrufen
*---------------------------------------------------------------------*/
if(intore ==  7) intore = 3; /* damit eine Ordnung tiefer als ISOD88 */
if(intore == 13) intore = 7;

if(ihflag != 0) ipflag= ihflag;
else            ipflag= 1;

iret  = spla88();

ipflag= 0;

/*----------------------------------------------------------------------
* die Ergebnisse Platte in die Steifigkeitsmatrix einbauen
*---------------------------------------------------------------------*/
isdu= 2;
ise = 0;

for(l = 1; l <= 6; l++)
  {
  for(m = 1; m <= 3; m++)
    {
    j= 0;
    for(i= 1; i <= 6; i++)
      {
      for(k= 1; k <= 3; k++)
        {
        j++;
        sdu[(isdu+m-1)*36 + (i-1)*6+2+k]= se[(ise+m-1)*18 + j];
        }
      }
    }
  isdu+= 6;
  ise += 3;
  }

/*----------------------------------------------------------------------
* die Pseudo-Steifigkeiten ThetaZ in die Steifigkeitsmatrix einbauen
*---------------------------------------------------------------------*/
/*======================================================================
* die Pseudo-Steifigkeiten mit einem hohen Wert belegen
*=====================================================================*/
beta= 1e8;
sdu[ 186]= beta;
sdu[ 408]= beta;
sdu[ 630]= beta;
sdu[ 852]= beta;
sdu[1074]= beta;
sdu[1296]= beta;

/*======================================================================
* den kleinsten Diagonalwert finden
*=====================================================================*/
diamin= sdu[1];

for(i= 1; i <= 36; i++)
  {
  if(sdu[(i-1)*36+i] < diamin) diamin= sdu[(i-1)*36+i];
  }

/*======================================================================
* beta ist 0.001 x kleinster Diagonalwert
*=====================================================================*/
beta= 0.001 * diamin;

sdu[ 186]= beta;
sdu[ 408]= beta;
sdu[ 630]= beta;
sdu[ 852]= beta;
sdu[1074]= beta;
sdu[1296]= beta;

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
* Steifigkeitsmatrix transformieren: tmt * sdu * tm
*---------------------------------------------------------------------*/
/*======================================================================
* erstes Matrixprodukt: tmt * sdu = zm
*=====================================================================*/
for(i = 1;i <= 36;i++)
  {
  for(j = 1;j <= 36;j++)
    {
    sum= 0.;
    for(k = 1; k <= 36; k++)
      {
      sum+= tmt[(i-1)*36+k] * sdu[(k-1)*36+j];
      }
    zm[(i-1)*36+j]= sum;
    }
  }

/*======================================================================
* zweites Matrixprodukt: zm * tm = se
*=====================================================================*/
for(i = 1;i <= 36;i++)
  {
  for(j = 1;j <= 36;j++)
    {
    sum= 0.;
    for(k = 1; k <= 36; k++)
      {
      sum+= zm[(i-1)*36+k] * tm[(k-1)*36+j];
      }
    se[(i-1)*36+j]= sum;
    }
  }

/*----------------------------------------------------------------------
* den Lastvektor aus SPLA88 modifizieren und transformieren
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
