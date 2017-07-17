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
* diese Compilerunit umfasst: shav88 - Elementsteifigkeitsroutine
*    ruft                   : qshe88 - der Scheibenanteil
*                           : apla88 - der Plattenanteil
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
int qshe88(void);
int apla88(void);

/***********************************************************************
* hier beginnt Function shav88
***********************************************************************/
int shav88(void)
{
extern FR_DOUBLEAY se;
extern FR_DOUBLEAY sdu;
extern FR_DOUBLEAY tmt;
extern FR_DOUBLEAY tm;
extern FR_DOUBLEAY zm;

extern FR_DOUBLE xk[],yk[],zk[],be[];
extern FR_DOUBLE xc[],yc[],zc[];
extern FR_INT4 ktyp,ipflag,ihflag,intore;

FR_DOUBLE bez[49];
FR_DOUBLE a21x,a21y,a21z,rl21,a41x,a41y,a41z;
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
* die Scheibenrotine qshe88 aufrufen
*---------------------------------------------------------------------*/
ktyp= 2;
iret= qshe88();

/*----------------------------------------------------------------------
* die Ergebnisse Scheibe in die Steifigkeitsmatrix einbauen
*---------------------------------------------------------------------*/
for(i = 1; i <= 2304; i++)
  sdu[i]= 0.;

isdu= 0;
ise = 0;

for(l = 1; l <= 8; l++)
  {
  for(m = 1; m <= 2; m++)
    {
    j= 0;
    for(i= 1; i <= 8; i++)
      {
      for(k= 1; k <= 2; k++)
        {
        j++;
        sdu[(isdu+m-1)*48 + (i-1)*6+k]= se[(ise+m-1)*16 + j];
        }
      }
    }
  isdu+= 6;
  ise += 2;
  }

/*----------------------------------------------------------------------
* die Plattenroutine apla88 aufrufen
*---------------------------------------------------------------------*/
if(intore == 3) intore = 2; /* damit eine Ordnung tiefer als qshe88 */
if(intore == 4) intore = 3;

if(ihflag != 0) ipflag= ihflag;
else            ipflag= 1;

iret  = apla88();

ipflag= 0;

/*----------------------------------------------------------------------
* die Ergebnisse Platte in die Steifigkeitsmatrix einbauen
*---------------------------------------------------------------------*/
isdu= 2;
ise = 0;

for(l = 1; l <= 8; l++)
  {
  for(m = 1; m <= 3; m++)
    {
    j= 0;
    for(i= 1; i <= 8; i++)
      {
      for(k= 1; k <= 3; k++)
        {
        j++;
        sdu[(isdu+m-1)*48 + (i-1)*6+2+k]= se[(ise+m-1)*24 + j];
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
sdu[ 246]= beta;
sdu[ 540]= beta;
sdu[ 834]= beta;
sdu[1128]= beta;
sdu[1422]= beta;
sdu[1716]= beta;
sdu[2010]= beta;
sdu[2304]= beta;

/*======================================================================
* den kleinsten Diagonalwert finden
*=====================================================================*/
diamin= sdu[1];

for(i= 1; i <= 48; i++)
  {
  if(sdu[(i-1)*48+i] < diamin) diamin= sdu[(i-1)*48+i];
  }

/*======================================================================
* beta ist 0.001 x kleinster Diagonalwert
*=====================================================================*/
beta= 0.001 * diamin;

sdu[ 246]= beta;
sdu[ 540]= beta;
sdu[ 834]= beta;
sdu[1128]= beta;
sdu[1422]= beta;
sdu[1716]= beta;
sdu[2010]= beta;
sdu[2304]= beta;

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
* Steifigkeitsmatrix transformieren: tmt * sdu * tm
*---------------------------------------------------------------------*/
/*======================================================================
* erstes Matrixprodukt: tmt * sdu = zm
*=====================================================================*/
for(i = 1;i <= 48;i++)
  {
  for(j = 1;j <= 48;j++)
    {
    sum= 0.;
    for(k = 1; k <= 48; k++)
      {
      sum+= tmt[(i-1)*48+k] * sdu[(k-1)*48+j];
      }
    zm[(i-1)*48+j]= sum;
    }
  }

/*======================================================================
* zweites Matrixprodukt: zm * tm = se
*=====================================================================*/
for(i = 1;i <= 48;i++)
  {
  for(j = 1;j <= 48;j++)
    {
    sum= 0.;
    for(k = 1; k <= 48; k++)
      {
      sum+= zm[(i-1)*48+k] * tm[(k-1)*48+j];
      }
    se[(i-1)*48+j]= sum;
    }
  }

/*----------------------------------------------------------------------
* den Lastvektor aus apla88 modifizieren und transformieren
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
