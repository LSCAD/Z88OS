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
* Functions zur Vergleichs-Spannungsberechnung
*
* torgh:  gh fuer Torus 6,8,12 und 15
* sheigh: gh fuer Scheibe 3,7,11 und 14
* hexgh:  gh fuer Hexaeder 1,10,Tetraeder 16,17, Schalen 21,22,24
* platgh: gh fuer Platte 18,19 und 20
*
* tornh:  nh fuer Torus 6,8,12 und 15
* sheinh: nh fuer Scheibe 3,7,11 und 14
* hexnh:  nh fuer Hexaeder 1,10,Tetraeder 16,17, Schalen 21,22,24
* platnh: nh fuer Platte 18,19 und 20
*
* torsh:  sh fuer Torus 6,8,12 und 15
* sheish: sh fuer Scheibe 3,7,11 und 14
* hexsh:  sh fuer Hexaeder 1,10,Tetraeder 16,17, Schalen 21,22,24
* platsh: sh fuer Platte 18,19 und 20
*
* 2.1.2010 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <math.h>
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <math.h>
#endif

/***********************************************************************
* Fuer Windows und GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88r.h>
#include <math.h>
#endif

/***********************************************************************
* Gestaltsaenderungsenergie-Hypothese, v.Mises stresses
***********************************************************************/
/***********************************************************************
* hier beginnt Function torgh
***********************************************************************/
FR_DOUBLE torgh(FR_DOUBLE sig[])
{        
FR_DOUBLE fret;
fret= FR_SQRT(sig[1]*sig[1] + sig[4]*sig[4] + sig[2]*sig[2] - 
             (sig[1]*sig[4] + sig[4]*sig[2] + sig[1]*sig[2]) +
           3.*sig[3]*sig[3]);
return(fret);
}
        
/***********************************************************************
* hier beginnt Function sheigh
***********************************************************************/
FR_DOUBLE sheigh(FR_DOUBLE sig[])
{
FR_DOUBLE fret;
fret= FR_SQRT(sig[1]*sig[1] + sig[2]*sig[2] - sig[1]*sig[2] +
           3.*sig[3]*sig[3]);
return(fret);
}
        
/***********************************************************************
* hier beginnt Function hexgh
***********************************************************************/
FR_DOUBLE hexgh(FR_DOUBLE sig[])
{
FR_DOUBLE fret;
fret= FR_SQRT(sig[1]*sig[1] + sig[2]*sig[2] + sig[3]*sig[3] - 
             (sig[1]*sig[2] + sig[2]*sig[3] + sig[1]*sig[3]) + 
          3.*(sig[4]*sig[4] + sig[5]*sig[5] + sig[6]*sig[6]));
return(fret);
}

/***********************************************************************
* hier beginnt Function platgh
***********************************************************************/
FR_DOUBLE platgh(FR_DOUBLE rsig[])
{
FR_DOUBLE fret;
fret= FR_SQRT(rsig[1]*rsig[1] + rsig[2]*rsig[2]
             -rsig[1]*rsig[2] + 3.*rsig[3]*rsig[3]);
return(fret);
}

/***********************************************************************
* Normalspannungs-Hypothese, principal stresses
***********************************************************************/
/***********************************************************************
* hier beginnt Function tornh
***********************************************************************/
FR_DOUBLE tornh(FR_DOUBLE sig[])
{        
FR_DOUBLE fret,sig1,sig2,sig3,wur;

/*----------------------------------------------------------------------
* Hauptspannungen
*---------------------------------------------------------------------*/
wur= FR_SQRT(sig[1]*sig[1]-2*sig[1]*sig[2]+sig[2]*sig[2]+4*sig[3]*sig[3]);

sig1= FR_FABS(0.5*(-wur+sig[1]+sig[2]));
sig2= FR_FABS(0.5*( wur+sig[1]+sig[2])); 
sig3= FR_FABS(sig[4]);

/*----------------------------------------------------------------------
* Spannungshypothese
*---------------------------------------------------------------------*/
fret= 0.;
if(sig1 >= sig2  && sig1 >= sig3) return(sig1);
if(sig2 >= sig1  && sig2 >= sig3) return(sig2);
if(sig3 >= sig1  && sig3 >= sig2) return(sig3);
return(fret);
}

/***********************************************************************
* hier beginnt Function sheinh
***********************************************************************/
FR_DOUBLE sheinh(FR_DOUBLE sig[])
{
FR_DOUBLE sig1,sig2,wur;
FR_DOUBLE fret;

/*----------------------------------------------------------------------
* Hauptspannungen
*---------------------------------------------------------------------*/
wur= FR_SQRT(FR_POW((sig[1]-sig[2]),2)/4. + sig[3]*sig[3]);

sig1= FR_FABS((sig[1]+sig[2])/2. + wur);
sig2= FR_FABS((sig[1]+sig[2])/2. - wur);

/*----------------------------------------------------------------------
* Spannungshypothese
*---------------------------------------------------------------------*/
fret= 0.;
if(sig1 >= sig2) return(sig1);
if(sig2 >= sig1) return(sig2);
return(fret);
}

/***********************************************************************
* hier beginnt Function hexnh
***********************************************************************/
FR_DOUBLE hexnh(FR_DOUBLE sig[])
{
extern FR_INT4 noci;

FR_DOUBLE J1,J2,J3,D,p,q,phi,y1,y2,y3,wup,sig1,sig2,sig3;
FR_DOUBLE fret=0;

/*----------------------------------------------------------------------
* die Invarianten berechnen
*---------------------------------------------------------------------*/
J1= sig[1]+sig[2]+sig[3];
J2= sig[1]*sig[2]+sig[1]*sig[3]+sig[2]*sig[3]-
    sig[4]*sig[4]-sig[6]*sig[6]-sig[5]*sig[5];
J3= sig[1]*sig[2]*sig[3]-sig[1]*sig[5]*sig[5]+
    sig[4]*sig[5]*sig[6]-sig[3]*sig[4]*sig[4]+
    sig[6]*sig[4]*sig[5]-sig[2]*sig[6]*sig[6];

/*----------------------------------------------------------------------
* reduzierte Form der kubischen Gleichung y^3+py+q=0 loesen
*---------------------------------------------------------------------*/
p= J2- J1*J1/3.;
q= J1*J2/3. - 2*J1*J1*J1/27. - J3;

D= q*q/4. + p*p*p/27.;  /* Diskriminante */

if(D >= 0) /* casus irreducibilis geht nicht */ 
  {
  noci= 1;
  return(0.);
  }

phi= FR_ACOS(-q/2./FR_SQRT(FR_POW((FR_FABS(p)/3.),3)));

wup= FR_SQRT(FR_FABS(p)/3.);
y1=  2*wup*FR_COS(phi/3.);
y2= -2*wup*FR_COS(phi/3.-1.0472);
y3= -2*wup*FR_COS(phi/3.+1.0472);

/*----------------------------------------------------------------------
* Hauptspannungen
*---------------------------------------------------------------------*/
sig1= FR_FABS(y1+J1/3.);
sig2= FR_FABS(y2+J1/3.);
sig3= FR_FABS(y3+J1/3.);

/*----------------------------------------------------------------------
* Spannungshypothese
*---------------------------------------------------------------------*/
fret= 0.;
if(sig1 >= sig2  && sig1 >= sig3) return(sig1);
if(sig2 >= sig1  && sig2 >= sig3) return(sig2);
if(sig3 >= sig1  && sig3 >= sig2) return(sig3);
return(fret);
}

/***********************************************************************
* hier beginnt Function platnh
***********************************************************************/
FR_DOUBLE platnh(FR_DOUBLE rsig[])
{
FR_DOUBLE sig1,sig2,wur;
FR_DOUBLE fret;

/*----------------------------------------------------------------------
* Hauptspannungen
*---------------------------------------------------------------------*/
wur= FR_SQRT(FR_POW((rsig[1]-rsig[2]),2)/4. + rsig[3]*rsig[3]);

sig1= FR_FABS((rsig[1]+rsig[2])/2. + wur);
sig2= FR_FABS((rsig[1]+rsig[2])/2. - wur);

/*----------------------------------------------------------------------
* Spannungshypothese
*---------------------------------------------------------------------*/
fret= 0.;
if(sig1 >= sig2) return(sig1);
if(sig2 >= sig1) return(sig2);
return(fret);
}

/***********************************************************************
* Schubspannungs-Hypothese, Tresca stresses
***********************************************************************/
/***********************************************************************
* hier beginnt Function torsh
***********************************************************************/
FR_DOUBLE torsh(FR_DOUBLE sig[])
{        
FR_DOUBLE fret,sig1,sig2,sig3,wur;

/*----------------------------------------------------------------------
* Hauptspannungen
*---------------------------------------------------------------------*/
wur= FR_SQRT(sig[1]*sig[1]-2*sig[1]*sig[2]+sig[2]*sig[2]+4*sig[3]*sig[3]);

sig1= 0.5*(-wur+sig[1]+sig[2]);
sig2= 0.5*( wur+sig[1]+sig[2]); 
sig3= sig[4];

/*----------------------------------------------------------------------
* Spannungshypothese
*---------------------------------------------------------------------*/
fret= 0.;
if(sig1 >= sig2 && sig2 >= sig3) return(sig1-sig3);
if(sig1 >= sig3 && sig3 >= sig2) return(sig1-sig2);
if(sig2 >= sig1 && sig1 >= sig3) return(sig2-sig3);
if(sig2 >= sig3 && sig3 >= sig1) return(sig2-sig1);
if(sig3 >= sig2 && sig2 >= sig1) return(sig3-sig1);
if(sig3 >= sig1 && sig1 >= sig2) return(sig3-sig2);
return(fret);
}

/***********************************************************************
* hier beginnt Function sheish
***********************************************************************/
FR_DOUBLE sheish(FR_DOUBLE sig[])
{
FR_DOUBLE sig1,sig2,wur;
FR_DOUBLE fret;

/*----------------------------------------------------------------------
* Hauptspannungen
*---------------------------------------------------------------------*/
wur= FR_SQRT(FR_POW((sig[1]-sig[2]),2)/4. + sig[3]*sig[3]);

sig1= (sig[1]+sig[2])/2. + wur;
sig2= (sig[1]+sig[2])/2. - wur;

/*----------------------------------------------------------------------
* Spannungshypothese
*---------------------------------------------------------------------*/
fret= 0.;
if(sig1 >= sig2 && sig2 >=   0.) return(FR_FABS(sig1));
if(sig1 <= sig2 && sig2 <=   0.) return(FR_FABS(sig1));
if(sig2 >= sig1 && sig1 >=   0.) return(FR_FABS(sig2));
if(sig2 <= sig1 && sig1 <=   0.) return(FR_FABS(sig2));
if(sig1 >=   0. && sig2 <=   0.) return(sig1-sig2);
if(sig2 >=   0. && sig1 <=   0.) return(sig2-sig1);
return(fret);
}

/***********************************************************************
* hier beginnt Function hexsh
***********************************************************************/
FR_DOUBLE hexsh(FR_DOUBLE sig[])
{
extern FR_INT4 noci;

FR_DOUBLE J1,J2,J3,D,p,q,phi,y1,y2,y3,wup,sig1,sig2,sig3;
FR_DOUBLE fret=0;

/*----------------------------------------------------------------------
* die Invarianten berechnen
*---------------------------------------------------------------------*/
J1= sig[1]+sig[2]+sig[3];
J2= sig[1]*sig[2]+sig[1]*sig[3]+sig[2]*sig[3]-
    sig[4]*sig[4]-sig[6]*sig[6]-sig[5]*sig[5];
J3= sig[1]*sig[2]*sig[3]-sig[1]*sig[5]*sig[5]+
    sig[4]*sig[5]*sig[6]-sig[3]*sig[4]*sig[4]+
    sig[6]*sig[4]*sig[5]-sig[2]*sig[6]*sig[6];

/*----------------------------------------------------------------------
* reduzierte Form der kubischen Gleichung y^3+py+q=0 loesen
*---------------------------------------------------------------------*/
p= J2- J1*J1/3.;
q= J1*J2/3. - 2*J1*J1*J1/27. - J3;

D= q*q/4. + p*p*p/27.;  /* Diskriminante */

if(D >= 0) /* casus irreducibilis geht nicht */ 
  {
  noci= 1;
  return(0.);
  }

phi= FR_ACOS(-q/2./FR_SQRT(FR_POW((FR_FABS(p)/3.),3)));

wup= FR_SQRT(FR_FABS(p)/3.);
y1=  2*wup*FR_COS(phi/3.);
y2= -2*wup*FR_COS(phi/3.-1.0472);
y3= -2*wup*FR_COS(phi/3.+1.0472);

/*----------------------------------------------------------------------
* Hauptspannungen
*---------------------------------------------------------------------*/
sig1= y1+J1/3.;
sig2= y2+J1/3.;
sig3= y3+J1/3.;

/*----------------------------------------------------------------------
* Spannungshypothese
*---------------------------------------------------------------------*/
fret= 0.;
if(sig1 >= sig2 && sig2 >= sig3) return(sig1-sig3);
if(sig1 >= sig3 && sig3 >= sig2) return(sig1-sig2);
if(sig2 >= sig1 && sig1 >= sig3) return(sig2-sig3);
if(sig2 >= sig3 && sig3 >= sig1) return(sig2-sig1);
if(sig3 >= sig2 && sig2 >= sig1) return(sig3-sig1);
if(sig3 >= sig1 && sig1 >= sig2) return(sig3-sig2);
return(fret);
}

/***********************************************************************
* hier beginnt Function platsh
***********************************************************************/
FR_DOUBLE platsh(FR_DOUBLE rsig[])
{
FR_DOUBLE sig1,sig2,wur;
FR_DOUBLE fret;

/*----------------------------------------------------------------------
* Hauptspannungen
*---------------------------------------------------------------------*/
wur= FR_SQRT(FR_POW((rsig[1]-rsig[2]),2)/4. + rsig[3]*rsig[3]);

sig1= (rsig[1]+rsig[2])/2. + wur;
sig2= (rsig[1]+rsig[2])/2. - wur;

/*----------------------------------------------------------------------
* Spannungshypothese
*---------------------------------------------------------------------*/
fret= 0.;
if(sig1 >= sig2 && sig2 >=   0.) return(FR_FABS(sig1));
if(sig1 <= sig2 && sig2 <=   0.) return(FR_FABS(sig1));
if(sig2 >= sig1 && sig1 >=   0.) return(FR_FABS(sig2));
if(sig2 <= sig1 && sig1 <=   0.) return(FR_FABS(sig2));
if(sig1 >=   0. && sig2 <=   0.) return(sig1-sig2);
if(sig2 >=   0. && sig1 <=   0.) return(sig2-sig1);
return(fret);
}
