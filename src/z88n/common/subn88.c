/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the UNIX and
* the Windows OS.
*
* Composed and edited and copyright by 
* Professor Dr.-Ing. Frank Rieg, University of Bayreuth, Germany
*
* eMail: 
* frank.rieg@uni-bayreuth.de
* dr.frank.rieg@t-online.de
* 
* V15.0  November 18 2015
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
* Diese Compilerunit umfasst:
*
* fq88  : liefert Formfunktionen Typ 7  h: extern
* fc88  : liefert Formfunktionen Typ 11 h: extern
* fh88  : liefert Formfunktionen Typ 10 h: extern
* fb88  : liefert Formfunktionen Typ 1  h: extern
* fa88  : liefert Formfunktionen Typ 21 h: extern
* ihh88 : liefert r oder s oder t als F-Return      (fuer Typ 10,7,8,20)
* ilq88 : liefert r oder s oder t als F-Return      (fuer Typ 1)   
* ikl88 : liefert r oder s als F-Return             (fuer Typ 19)
* cphh88: liefert xinc, yinc oder zinc als F-Return (fuer Typ 10,7,8,20)
* cphl88: liefert xinc, yinc oder zinc als F-Return (fuer Typ 1)
* cphl88: liefert xinc oder yinc als F-Return       (fuer Typ 19)
*
* 21.7.2011 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88n.h>
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88n.h>
#endif

/***********************************************************************
* hier beginnt Function fq88
***********************************************************************/
int fq88(FR_DOUBLE r,FR_DOUBLE s)
{
extern FR_DOUBLE h[];
FR_DOUBLE rp,sp,rm,sm,rqm,sqm;

/*----------------------------------------------------------------------
* Klammern der Formfunktionen belegen
*---------------------------------------------------------------------*/
rp = 1. + r;
sp = 1. + s;
rm = 1. - r;
sm = 1. - s;
rqm= 1. - r*r;
sqm= 1. - s*s;

/*----------------------------------------------------------------------
* Formfunktionen
*---------------------------------------------------------------------*/
h[1]= .25*(rp*sp - rqm*sp - sqm*rp);
h[2]= .25*(rm*sp - rqm*sp - sqm*rm);
h[3]= .25*(rm*sm - sqm*rm - rqm*sm);
h[4]= .25*(rp*sm - rqm*sm - sqm*rp);
h[5]= .5*rqm*sp;
h[6]= .5*sqm*rm;
h[7]= .5*rqm*sm;
h[8]= .5*sqm*rp;

return(0);
}

/***********************************************************************
* hier beginnt Function fc88
***********************************************************************/
int fc88(FR_DOUBLE r,FR_DOUBLE s)
{
extern FR_DOUBLE h[];
FR_DOUBLE epr,emr,eps,ems,emrr,emss,rr9,ss9,r3,s3;

/*----------------------------------------------------------------------
* Faktoren der Formfunktionen & der Ableitungen belegen
*---------------------------------------------------------------------*/
epr= 1. + r;
emr= 1. - r;
eps= 1. + s;
ems= 1. - s;

emrr= 1. - r*r;
emss= 1. - s*s;
rr9 = 9. *r*r;
ss9 = 9. *s*s;
r3  = 3. *r;
s3  = 3. *s;
        
/*----------------------------------------------------------------------
* Formfunktionen
*---------------------------------------------------------------------*/
h[1 ]=  .03125 * epr * eps * ( rr9 + ss9 - 10.);  
h[2 ]=  .03125 * emr * eps * ( rr9 + ss9 - 10.);
h[3 ]=  .03125 * emr * ems * ( rr9 + ss9 - 10.);
h[4 ]=  .03125 * epr * ems * ( rr9 + ss9 - 10.);
h[5 ]=  .28125 * eps * emrr* ( 1. + r3);
h[6 ]=  .28125 * eps * emrr* ( 1. - r3);
h[7 ]=  .28125 * emr * emss* ( 1. + s3);
h[8 ]=  .28125 * emr * emss* ( 1. - s3);
h[9 ]=  .28125 * ems * emrr* ( 1. - r3);
h[10]=  .28125 * ems * emrr* ( 1. + r3);
h[11]=  .28125 * epr * emss* ( 1. - s3);
h[12]=  .28125 * epr * emss* ( 1. + s3);  

return(0);
}
        
/***********************************************************************
* hier beginnt Function fb88
***********************************************************************/
int fb88(FR_DOUBLE r,FR_DOUBLE s,FR_DOUBLE t)
{
extern FR_DOUBLE h[];
FR_DOUBLE rs,rt,st,rst;

/*----------------------------------------------------------------------
* Faktoren der Formfunktionen belegen
*---------------------------------------------------------------------*/
rs= r*s;
rt= r*t;
st= s*t;
rst=r*s*t;

/*----------------------------------------------------------------------
* Formfunktionen
*---------------------------------------------------------------------*/
h[1]= .125 *(1. + r + s + rs + t + rt + st + rst);
h[2]= .125 *(1. - r + s - rs + t - rt + st - rst);
h[3]= .125 *(1. - r - s + rs + t - rt - st + rst);
h[4]= .125 *(1. + r - s - rs + t + rt - st - rst);
h[5]= .125 *(1. + r + s + rs - t - rt - st - rst);
h[6]= .125 *(1. - r + s - rs - t + rt - st + rst);
h[7]= .125 *(1. - r - s + rs - t + rt + st - rst);
h[8]= .125 *(1. + r - s - rs - t - rt + st + rst);

return(0);
}

/***********************************************************************
* hier beginnt Function fh88
***********************************************************************/
int fh88(FR_DOUBLE r,FR_DOUBLE s,FR_DOUBLE t)
{
extern FR_DOUBLE h[];
FR_DOUBLE epr,emr,eps,ems,ept,emt;
FR_DOUBLE emrr,emss,emtt;

/*----------------------------------------------------------------------
* Faktoren der Ableitungen der Formfunktionen belegen
*---------------------------------------------------------------------*/
epr = 1. + r;
emr = 1. - r;
eps = 1. + s;
ems = 1. - s;
ept = 1. + t;
emt = 1. - t;
        
emrr= 1. - r*r;
emss= 1. - s*s;
emtt= 1. - t*t;
        
/*----------------------------------------------------------------------
* Berechnung der Formfunktionen
*---------------------------------------------------------------------*/
h[1 ]= .125*( epr*eps*ept  -emrr*eps*ept  -epr*emss*ept - epr*eps*emtt);
h[2 ]= .125*( emr*eps*ept  -emrr*eps*ept  -emr*emss*ept - emr*eps*emtt);
h[3 ]= .125*( emr*ems*ept  -emr*emss*ept  -emrr*ems*ept - emr*ems*emtt);
h[4 ]= .125*( epr*ems*ept  -emrr*ems*ept  -epr*emss*ept - epr*ems*emtt);
h[5 ]= .125*( epr*eps*emt  -emrr*eps*emt  -epr*emss*emt - epr*eps*emtt);
h[6 ]= .125*( emr*eps*emt  -emrr*eps*emt  -emr*emss*emt - emr*eps*emtt);
h[7 ]= .125*( emr*ems*emt  -emr*emss*emt -emrr*ems*emt - emr*ems*emtt);
h[8 ]= .125*( epr*ems*emt  -emrr*ems*emt -epr*emss*emt - epr*ems*emtt);
h[9 ]= .25 * emrr* eps * ept;
h[10]= .25 * emr * emss* ept;
h[11]= .25 * emrr* ems * ept;
h[12]= .25 * epr * emss* ept;
h[13]= .25 * emrr* eps * emt;
h[14]= .25 * emr * emss* emt;
h[15]= .25 * emrr* ems * emt;
h[16]= .25 * epr * emss* emt;
h[17]= .25 * epr * eps * emtt;
h[18]= .25 * emr * eps * emtt;
h[19]= .25 * emr * ems * emtt;
h[20]= .25 * epr * ems * emtt;                       

return(0);
}
      
/***********************************************************************
* hier beginnt Function fa88
***********************************************************************/
int fa88(FR_DOUBLE r,FR_DOUBLE s,FR_DOUBLE t)
{
extern FR_DOUBLE h[];

FR_DOUBLE rp,sp,rm,sm,rqm,sqm,r2,s2,ept,emt;

/*----------------------------------------------------------------------
* Klammern der Formfunktionen belegen
*---------------------------------------------------------------------*/
rp=  1. + r;
sp=  1. + s;
rm=  1. - r;
sm=  1. - s;
rqm= 1. - r*r;
sqm= 1. - s*s;
r2=  2. * r;
s2=  2. * s;
ept= 0.5* (1. + t);
emt= 0.5* (1. - t);

/*----------------------------------------------------------------------
* Formfunktionen obere und untere Ebene
*---------------------------------------------------------------------*/
h[ 1]= .25 * (rp*sp - rqm*sp - sqm*rp) * ept;
h[ 2]= .25 * (rm*sp - rqm*sp - sqm*rm) * ept;
h[ 3]= .25 * (rm*sm - sqm*rm - rqm*sm) * ept;
h[ 4]= .25 * (rp*sm - rqm*sm - sqm*rp) * ept;
h[ 5]= .5 * rqm * sp * ept;
h[ 6]= .5 * sqm * rm * ept;
h[ 7]= .5 * rqm * sm * ept;
h[ 8]= .5 * sqm * rp * ept;

h[ 9]= .25 * (rp*sp - rqm*sp - sqm*rp) * emt;
h[10]= .25 * (rm*sp - rqm*sp - sqm*rm) * emt;
h[11]= .25 * (rm*sm - sqm*rm - rqm*sm) * emt;
h[12]= .25 * (rp*sm - rqm*sm - sqm*rp) * emt;
h[13]= .5 * rqm * sp * emt;
h[14]= .5 * sqm * rm * emt;
h[15]= .5 * rqm * sm * emt;
h[16]= .5 * sqm * rp * emt;

return(0);
}
  
/***********************************************************************
* hier beginnt Function ihh88 : typ 10 --> typ 10
***********************************************************************/
FR_DOUBLE ihh88(char cmode,FR_DOUBLE xinc,FR_INT4 j,FR_INT4 jmax)
{        
FR_DOUBLE r;
FR_INT4 jteil,jgerad;

r= 0.; /* nur wg. compiler warnings */
        
if(cmode == 'E' || cmode == 'e')
  r= 1. - xinc * (j-1);  
    
else if(cmode == 'L')
  {
  jteil= j/2;
  jgerad= j+1-((j+1)/2)*2;
  if(jgerad == 0) 
    r= 2.- FR_POW(xinc,(FR_DOUBLE)jteil);
  else
    r= ((2.-FR_POW(xinc,(FR_DOUBLE)jteil) )
       +(2.-FR_POW(xinc,(FR_DOUBLE)(jteil-1) ) ) )/2.;
  }
    
else if(cmode == 'l')
  {
  jteil= (jmax-j)/2;
  jgerad= j+1-((j+1)/2)*2;
  if(jgerad == 0) 
    r= FR_POW(xinc,(FR_DOUBLE)jteil) -2.;
  else
    r= ((FR_POW(xinc,(FR_DOUBLE)jteil) -2.)
       +(FR_POW(xinc,(FR_DOUBLE)(jteil+1)) -2.) )/2.;
  }
        
return(r);
}
        
/***********************************************************************
* hier beginnt Function ilq88 : typ 10 --> typ 1
***********************************************************************/
FR_DOUBLE ilq88(char cmode,FR_DOUBLE xinc,FR_INT4 j,FR_INT4 jmax)
{        
FR_DOUBLE r;

r= 0.; /* nur wg. compiler warnings */

if(cmode == 'E' || cmode == 'e') 
  r= 1. - xinc * (j-1);  
else if(cmode == 'L') 
  r= 2. - FR_POW(xinc,(FR_DOUBLE)(j-1));
else if(cmode == 'l') 
  r= FR_POW(xinc,(FR_DOUBLE)(jmax-j)) -2.;
        
return(r);
}

/***********************************************************************
* hier beginnt Function ikl88 : typ 20 --> typ 19
***********************************************************************/
FR_DOUBLE ikl88(char cmode,FR_DOUBLE xinc,FR_INT4 j,FR_INT4 jmax)
{        
FR_DOUBLE r;

r= 0.; /* nur wg. compiler warnings */

if(cmode == 'E' || cmode == 'e') 
  r= 1. - xinc * (j-1);  
else if(cmode == 'L') 
  r= 2. - FR_POW(xinc,(FR_DOUBLE)(j-1));
else if(cmode == 'l') 
  r= FR_POW(xinc,(FR_DOUBLE)(jmax-j)) -2.;
        
return(r);
}
        
/***********************************************************************
* hier beginnt Function cphh88
***********************************************************************/
FR_DOUBLE cphh88(char cmode,FR_INT4 jel)
{
FR_DOUBLE xinc;

xinc= 0.; /* nur wg. compiler warnings */

if(cmode == 'E' || cmode == 'e') 
  xinc= 2./(jel*2);
else if(cmode == 'L' || cmode == 'l') 
  xinc= FR_POW(3.,(1./jel));

return(xinc);
}

/***********************************************************************
* hier beginnt Function cphl88
***********************************************************************/
FR_DOUBLE cphl88(char cmode,FR_INT4 jel)
{
FR_DOUBLE xinc;

xinc= 0.; /* nur wg. compiler warnings */

if(cmode == 'E' || cmode == 'e')
  xinc= 2./jel;
else if(cmode == 'L' || cmode == 'l')
  xinc= FR_POW(3., (1./jel));

return(xinc);
}

/***********************************************************************
* hier beginnt Function cpkl88
***********************************************************************/
FR_DOUBLE cpkl88(char cmode,FR_INT4 jel)
{
FR_DOUBLE xinc;

xinc= 0.; /* nur wg. compiler warnings */

if(cmode == 'E' || cmode == 'e') 
  xinc= 2./(jel*3.);
else if(cmode == 'L' || cmode == 'l') 
  xinc= FR_POW(3.,(1./(jel*3.)));

return(xinc);
}
