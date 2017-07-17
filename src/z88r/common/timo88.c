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
* hier beginnt Function timo88
***********************************************************************/
int timo88(void)
{
extern FILE *fwlo;

extern FR_DOUBLEAY se;
extern FR_DOUBLEAY sdu;
extern FR_DOUBLEAY tmt;
extern FR_DOUBLEAY tm;
extern FR_DOUBLEAY zm;

extern FR_DOUBLE xk[],yk[],zk[];
extern FR_DOUBLE xc[],yc[],zc[];

extern FR_DOUBLE emode,rnuee,qparae,riyye,rizze,rite;
extern FR_DOUBLE xkp,ykp,zkp,rkape;

extern FR_INT4 ifbetie;

FR_DOUBLE a21x,a21y,a21z,rl21,a31x,a31y,a31z,rl31;
FR_DOUBLE azsx,azsy,azsz,rlzs,aysx,aysy,aysz,rlys;
FR_DOUBLE vxx,vxy,vxz,vyx,vyy,vyz,vzx,vzy,vzz;

FR_DOUBLE fystab,fytors,fy12,fy6,fy4,fy2,sum,gmode,fphi,edrka;

FR_INT4 i,j,k,inc;
  
/*----------------------------------------------------------------------
* globale Koordinaten in lokale Koordinaten umrechnen
*---------------------------------------------------------------------*/
fprintf(fwlo,"\nXK[1]= " P13E ", YK[1]= " P13E ", ZK[1]= " P13E "\n",xk[1],yk[1],zk[1]);
fprintf(fwlo,  "XK[2]= " P13E ", YK[2]= " P13E ", ZK[2]= " P13E "\n",xk[2],yk[2],zk[2]);
fprintf(fwlo,  "XCP  = " P13E ", YCP  = " P13E ", ZCP  = " P13E "\n",xkp,ykp,zkp);

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

fprintf(fwlo,
"x-Achse   :A21X= " P13E ", A21Y= " P13E ", A21Z= " P13E ", RL21= " P13E "\n",
a21x,a21y,a21z,rl21);

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

fprintf(fwlo,
"Hilfsachse:A31X= " P13E ", A31Y= " P13E ", A31Z= " P13E ", RL31= " P13E "\n",
a31x,a31y,a31z,rl31);

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

fprintf(fwlo,
"y-Achse   :AYSX= " P13E ", AYSY= " P13E ", AYSZ= " P13E ", RLYS= " P13E "\n",
aysx,aysy,aysz,rlys);

/*======================================================================
* azs ist Kreuzprodukt aus ays und a21 und bildet die lokale Achse z'
*=====================================================================*/
azsx= - aysy*a21z + aysz*a21y;
azsy= - aysz*a21x + aysx*a21z;
azsz= - aysx*a21y + aysy*a21x;
rlzs = FR_SQRT(azsx*azsx + azsy*azsy + azsz*azsz); /* Kontrolle */

fprintf(fwlo,
"z-Achse   :AZSX= " P13E ", AZSY= " P13E ", AZSZ= " P13E ", RLZS= " P13E "\n",
azsx,azsy,azsz,rlzs);
/*======================================================================
* Richtungscosinus x'x, x'y und x'z
*=====================================================================*/
vxx=a21x;
vxy=a21y;
vxz=a21z;
fprintf(fwlo,"VXX= " P13E ", VXY= " P13E ", VXZ= " P13E "\n",vxx,vxy,vxz);
/*======================================================================
* Richtungscosinus y'x, y'y und y'z
*=====================================================================*/
vyx=aysx;
vyy=aysy;
vyz=aysz;
fprintf(fwlo,"VYX= " P13E ", VYY= " P13E ", VYZ= " P13E "\n",vyx,vyy,vyz);
/*======================================================================
* Richtungscosinus z'x, z'y und z'z
*=====================================================================*/
vzx=azsx;
vzy=azsy;
vzz=azsz;
fprintf(fwlo,"VZX= " P13E ", VZY= " P13E ", VZZ= " P13E "\n",vzx,vzy,vzz);

/*======================================================================
* xk auf xc zwischensichern, damit xk lokal werden kann
*=====================================================================*/
for(i= 1; i <= 2; i++)
  {
  xc[i]= xk[i];
  yc[i]= yk[i];
  zc[i]= zk[i];
  }

/*======================================================================
* nun Koordinaten transformieren, xk,yk,zk sind nun lokal
*=====================================================================*/
for(i= 1; i <= 2; i++)
  {
  xk[i]= vxx*xc[i] + vxy*yc[i] + vxz*zc[i];
  yk[i]= vyx*xc[i] + vyy*yc[i] + vyz*zc[i];
  zk[i]= vzx*xc[i] + vzy*yc[i] + vzz*zc[i]; 
  }

/*----------------------------------------------------------------------
* die lokale Steifigkeitsmatrix aufstellen
*---------------------------------------------------------------------*/
for(i = 1;i <= 144;i++)
  sdu[i]= 0.;

/*======================================================================
* die Stabanteile - kein Timoshenko-Einfluss
*=====================================================================*/
fystab  =  emode*qparae/rl21;
sdu[1]  =  fystab;
sdu[7]  = -fystab;
sdu[73] = -fystab;
sdu[79] =  fystab;

/*======================================================================
* die Torsionsanteile - kein Timoshenko-Einfluss
*=====================================================================*/
gmode   =  emode/(2.*(1.+rnuee));
fytors  =  gmode*rite/rl21;
sdu[40] =  fytors;
sdu[46] = -fytors;
sdu[112]= -fytors;
sdu[118]=  fytors;

/*======================================================================
* die Biegeanteile in y-Richtung
*=====================================================================*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Bernoulli
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
if(ifbetie == 0)
  {
  fy12= emode*rizze * 12./(rl21*rl21*rl21);
  fy6 = emode*rizze *  6./(rl21*rl21);
  fy4 = emode*rizze *  4./ rl21;
  fy2 = fy4/2.;
  }
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Timoshenko
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
else
  {
  edrka= 1./rkape;
  fphi= 12.*emode*rizze*edrka/(qparae*gmode*rl21*rl21);

  fy12= emode*rizze * 12.      /((1.+fphi)*(rl21*rl21*rl21));
  fy6 = emode*rizze *  6.      /((1.+fphi)*(rl21*rl21));
  fy4 = emode*rizze * (4.+fphi)/((1.+fphi)*rl21);
  fy2 = emode*rizze * (2.-fphi)/((1.+fphi)*rl21);

  fprintf(fwlo,"FPHI= " P13E "\n",fphi);
  }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* gilt fuer beide
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
sdu[14] =  fy12;
sdu[18] =  fy6;
sdu[20] = -fy12;
sdu[24] =  fy6;

sdu[62] =  fy6;
sdu[66] =  fy4;
sdu[68] = -fy6;
sdu[72] =  fy2;

sdu[86] = -fy12;
sdu[90] = -fy6;
sdu[92] =  fy12;
sdu[96] = -fy6;

sdu[134]=  fy6;
sdu[138]=  fy2;
sdu[140]= -fy6;
sdu[144]=  fy4;

/*======================================================================
* die Biegeanteile in z-Richtung
*=====================================================================*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Bernoulli
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
if(ifbetie == 0)
  {
  fy12= emode*riyye * 12./(rl21*rl21*rl21);
  fy6 = emode*riyye *  6./(rl21*rl21);
  fy4 = emode*riyye *  4./ rl21;
  fy2 = fy4/2.;
  }
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Timoshenko
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
else
  {
  edrka= 1./rkape;
  fphi= 12.*emode*riyye*edrka/(qparae*gmode*rl21*rl21);

  fy12= emode*riyye * 12.      /((1.+fphi)*(rl21*rl21*rl21));
  fy6 = emode*riyye *  6.      /((1.+fphi)*(rl21*rl21));
  fy4 = emode*riyye * (4.+fphi)/((1.+fphi)*rl21);
  fy2 = emode*riyye * (2.-fphi)/((1.+fphi)*rl21);

  fprintf(fwlo,"FPHI= " P13E "\n",fphi);
  }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* gilt fuer beide
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
sdu[27] =  fy12;
sdu[29] = -fy6;
sdu[33] = -fy12;
sdu[35] = -fy6;

sdu[51] = -fy6;
sdu[53] =  fy4;
sdu[57] =  fy6;
sdu[59] =  fy2;

sdu[99] = -fy12;
sdu[101]=  fy6;
sdu[105]=  fy12;
sdu[107]=  fy6;

sdu[123]= -fy6;
sdu[125]=  fy2;
sdu[129]=  fy6;
sdu[131]=  fy4;

/*----------------------------------------------------------------------
* die Transformationsmatrix tm und die Transponierte tmt aufstellen
*---------------------------------------------------------------------*/
/*======================================================================
* Transformationsmatrix tm
*=====================================================================*/
for(i = 1; i <= 144; i++)
  tm[i]= 0.;

for(i = 1; i <= 144; i++)
  tmt[i]= 0.;

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

/*======================================================================
* Transponierte tmt der Transformationsmatrix tm
*=====================================================================*/
for(i= 1; i <= 12; i++)
  {
  for(j= 1; j <= 12; j++)
    {
    tmt[(i-1)*12+j]= tm[(j-1)*12+i];
    }
  }

/*----------------------------------------------------------------------
* Steifigkeitsmatrix transformieren: tmt * sdu * tm
*---------------------------------------------------------------------*/
/*======================================================================
* erstes Matrixprodukt: tmt * sdu = zm
*=====================================================================*/
for(i = 1;i <= 12;i++)
  {
  for(j = 1;j <= 12;j++)
    {
    sum= 0.;
    for(k = 1; k <= 12; k++)
      {
      sum+= tmt[(i-1)*12+k] * sdu[(k-1)*12+j];
      }
    zm[(i-1)*12+j]= sum;
    }
  }

/*======================================================================
* zweites Matrixprodukt: zm * tm = se
*=====================================================================*/
for(i = 1;i <= 12;i++)
  {
  for(j = 1;j <= 12;j++)
    {
    sum= 0.;
    for(k = 1; k <= 12; k++)
      {
      sum+= zm[(i-1)*12+k] * tm[(k-1)*12+j];
      }
    se[(i-1)*12+j]= sum;
    }
  }

return(0);
}


