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
* Diese Compilereinheit BETI88 enthaelt:
* - beti88 fuer Balken Nr.25 in allg.Lage, Bernoulli + Timoshenko
* - sbet88, die dazugehoerige Spannungsroutine
* 4.1.2013 Rieg
* 27.02.2013 Wehmann, Aenderung zs fuer Rechtssystem
* 01.03.2013 Wehmann, Spannungsberechnung Timoshenko hinzugefuegt
* 27.08.2013 Rieg, umbenennen von vormals BETI88.C, das beti88 und
*                  sbet88 enthielt, in timo88 und stim88, damit ist
*                  die Namensgebung wieder konsequent zum Rest, d.h.
*                  NAME88 = Steifigkeitsmatrix Element
*                  BNAME88= Lastvektoren fuer das Element
*                  SNAM88 = Spannungsroutine Element
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
* Leseformate
***********************************************************************/
#define NL "\n"

#ifdef FR_XDOUB
#define P13E "%+#13.5lE "
#define P11E "%+#11.3lE"
#define P11EB "%+#11.3lE "
#endif

#ifdef FR_XQUAD
#define P13E "%+#13.5LE "
#define P11E "%+#11.3LE"
#define P11EB "%+#11.3LE "
#endif


/***********************************************************************
* hier beginnt Function stim88
***********************************************************************/
int stim88(void)
{      
extern FILE *fo3;

extern FR_DOUBLEAY tm;

extern FR_DOUBLE ul[];
extern FR_DOUBLE xk[],yk[],zk[];

extern FR_DOUBLE emode,rnuee,qparae,ezze,eyye,rite,wte;
extern FR_DOUBLE riyye, rizze;
extern FR_DOUBLE xkp,ykp,zkp,rkape;

extern FR_INT4 ifbetie,ifnili;

FR_DOUBLE ulc[13];

FR_DOUBLE a21x,a21y,a21z,rl21,a31x,a31y,a31z,rl31;
FR_DOUBLE azsx,azsy,azsz,rlzs,aysx,aysy,aysz,rlys;
FR_DOUBLE vxx,vxy,vxz,vyx,vyy,vyz,vzx,vzy,vzz;

FR_DOUBLE rlv,fac,qrl,sum;
FR_DOUBLE sigxx,tauxx,sigzz1,sigzz2,sigyy1,sigyy2;

FR_DOUBLE gmode;

FR_DOUBLE BeTiBzz, BeTiRzz, BeTiSzz;
FR_DOUBLE BeTiByy, BeTiRyy, BeTiSyy;

FR_INT4 i,k,inc;

/*----------------------------------------------------------------------
* globale Verschiebungen in lokale Verschiebungen umrechnen,
* Transformationsmatrix aufstellen
*---------------------------------------------------------------------*/
/*======================================================================
* Einheits-Vektor 2-1 spannt die lokale x-Achse x' auf
*=====================================================================*/
a21x= xk[2] - xk[1]; 
a21y= yk[2] - yk[1];
a21z= zk[2] - zk[1];
rl21 = FR_SQRT(a21x*a21x + a21y*a21y + a21z*a21z);

a21x/= rl21;
a21y/= rl21;
a21z/= rl21;

/*======================================================================
* Einheits-Vektor 3-1 fuer Kreuzprodukt ays,xkp/ykp/zkp=Kontrollpunkt 3
*=====================================================================*/
a31x= xkp-xk[1];
a31y= ykp-yk[1];
a31z= zkp-zk[1];
rl31= FR_SQRT(a31x*a31x + a31y*a31y + a31z*a31z);

a31x/= rl31;
a31y/= rl31;
a31z/= rl31;

/*======================================================================
* ays ist Kreuzprodukt aus a21 und a31 und bildet die lokale Achse y'
*=====================================================================*/
aysx= a21y*a31z - a21z*a31y;
aysy= a21z*a31x - a21x*a31z;
aysz= a21x*a31y - a21y*a31x;
rlys = FR_SQRT(aysx*aysx + aysy*aysy + aysz*aysz);

aysx/= rlys;
aysy/= rlys;
aysz/= rlys;

/*======================================================================
* azs ist Kreuzprodukt aus ays und a21 und bildet die lokale Achse z'
*=====================================================================*/
azsx= - aysy*a21z + aysz*a21y;
azsy= - aysz*a21x + aysx*a21z;
azsz= - aysx*a21y + aysy*a21x;
rlzs = FR_SQRT(azsx*azsx + azsy*azsy + azsz*azsz); /* Kontrolle */

/*======================================================================
* Richtungscosinus x'x, x'y und x'z
*=====================================================================*/
vxx=a21x;
vxy=a21y;
vxz=a21z;

/*======================================================================
* Richtungscosinus y'x, y'y und y'z
*=====================================================================*/
vyx=aysx;
vyy=aysy;
vyz=aysz;

/*======================================================================
* Richtungscosinus z'x, z'y und z'z
*=====================================================================*/
vzx=azsx;
vzy=azsy;
vzz=azsz;

/*======================================================================
* Transformationsmatrix tm
*=====================================================================*/
for(i = 1; i <= 144; i++)
  tm[i]= 0.;

inc= 0;

for(i = 1; i <= 4; i++)
  {
  tm[inc*12+inc   +1]= vxx;
  tm[inc*12+inc   +2]= vxy;
  tm[inc*12+inc   +3]= vxz;
  tm[inc*12+inc+12+1]= vyx;
  tm[inc*12+inc+12+2]= vyy;
  tm[inc*12+inc+12+3]= vyz;
  tm[inc*12+inc+24+1]= vzx;
  tm[inc*12+inc+24+2]= vzy;
  tm[inc*12+inc+24+3]= vzz;
  inc+= 3;
  }

/*----------------------------------------------------------------------
* die globalen Verschiebungen zwischensichern
*---------------------------------------------------------------------*/
for(i = 1; i <= 12; i++)
  ulc[i]= ul[i];

/*----------------------------------------------------------------------
* Matrix-Vektorprodukt: tm * ulc(global) = ul(lokal)
*---------------------------------------------------------------------*/
for(i = 1;i <= 12;i++)
  {
  sum= 0.;
  for(k = 1; k <= 12; k++)
    {
    sum+= tm[(i-1)*12+k] * ulc[k];
    }
  ul[i]= sum; /* ul ist jetzt lokal */
  }

/*----------------------------------------------------------------------
* Spannungen berechnen
*---------------------------------------------------------------------*/
if(ifbetie == 0)
{
  rlv= rl21+ul[7]-ul[1];
  sigxx= emode*(rlv/rl21-1.);

  tauxx= (ul[10]-ul[4])/rl21 * emode/(2.*(1.+rnuee))*rite/wte;

  fac= emode*ezze;
  qrl= rl21*rl21;
  sigzz1=          fac*2.*(3.*(ul[8]-ul[2])-rl21*(2.*ul[6]+ul[12]))/qrl;
  sigzz2= sigzz1 + fac*6.*(2.*(ul[2]-ul[8])+rl21*(   ul[12]+ul[6]))/qrl;

  fac= emode*eyye;
  sigyy1=          fac*2.*(3.*(ul[9]-ul[3])+rl21*(2.*ul[5]+ul[11]))/qrl;
  sigyy2= sigyy1 + fac*6.*(2.*(ul[3]-ul[9])-rl21*(   ul[11]+ul[5]))/qrl;

  if(ifnili == 0)
    fprintf(fo3,NL P11EB P11EB P11EB P11EB P11EB P11E, 
    sigxx,tauxx,sigzz1,sigyy1,sigzz2,sigyy2);
}
else
{
  rlv= rl21+ul[7]-ul[1];
  sigxx= emode*(rlv/rl21-1.);

  tauxx= (ul[10]-ul[4])/rl21 * emode/(2.*(1.+rnuee))*rite/wte;
  
  gmode= emode/(2.*(1.+rnuee));

  fac= ezze/rizze;
  BeTiBzz=   (6.0*emode*rizze/(rl21*rl21)) 
           / (1.0+12.0*emode*rizze/(rkape*gmode*qparae*rl21*rl21));
  BeTiSzz=   (    4.0*emode*rizze/rl21 
               + 12.0*emode*emode*rizze*rizze/(rkape*gmode*qparae*rl21*rl21*rl21))
           / (1.0+12.0*emode*rizze/(rkape*gmode*qparae*rl21*rl21));
  BeTiRzz=   (    2.0*emode*rizze/rl21 
               - 12.0*emode*emode*rizze*rizze/(rkape*gmode*qparae*rl21*rl21*rl21))
           / (1.0+12.0*emode*rizze/(rkape*gmode*qparae*rl21*rl21));
  
  sigzz1= fac*(BeTiBzz*ul[2]+BeTiSzz*ul[6]-BeTiBzz*ul[8]+BeTiRzz*ul[12]);
  sigzz2= fac*(BeTiBzz*ul[2]+BeTiRzz*ul[6]-BeTiBzz*ul[8]+BeTiSzz*ul[12]);
  
  fac= eyye/riyye;
  BeTiByy=   (6.0*emode*riyye/(rl21*rl21)) 
           / (1.0+12.0*emode*riyye/(rkape*gmode*qparae*rl21*rl21));
  BeTiSyy=   (    4.0*emode*riyye/rl21 
               + 12.0*emode*emode*riyye*riyye/(rkape*gmode*qparae*rl21*rl21*rl21))
           / (1.0+12.0*emode*riyye/(rkape*gmode*qparae*rl21*rl21));
  BeTiRyy=   (    2.0*emode*riyye/rl21 
               - 12.0*emode*emode*riyye*riyye/(rkape*gmode*qparae*rl21*rl21*rl21))
           / (1.0+12.0*emode*riyye/(rkape*gmode*qparae*rl21*rl21));
  
  sigyy1= fac*(-BeTiByy*ul[3]+BeTiSyy*ul[5]+BeTiByy*ul[9]+BeTiRyy*ul[11]);
  sigyy2= fac*(-BeTiByy*ul[3]+BeTiRyy*ul[5]+BeTiByy*ul[9]+BeTiSyy*ul[11]);
  
  if(ifnili == 0)
    fprintf(fo3,NL P11EB P11EB P11EB P11EB P11EB P11E, 
    sigxx,tauxx,sigzz1,sigyy1,sigzz2,sigyy2);
}


return(0);
}

