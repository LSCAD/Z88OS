/***********************************************************************
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
* Compiler-Unit m3.c enthaelt:
*        sest88.for : stab in der ebene
*        ssta88.for : stab im raum
*        swel88.for : welle im raum
*        sbal88.for : balken im raum
*        seba88.for : ebener balken
* Diese Compiler-Unit enthaelt Programmteile, die gedanklich an FORTRAN-
* Quellen von H.R. Schwarz, ETH Zuerich, Schweiz, angelehnt sind.
*
* 3.8.2011 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>    /* FILE,fprintf */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <stdio.h>    /* FILE,fprintf */
#endif

/***********************************************************************
* Fuer Windows & GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88r.h>
#include <stdio.h>
#endif

/***********************************************************************
* Formate
***********************************************************************/
#define NL "\n"

#ifdef FR_XINT
#define P5D "%5d"
#endif

#ifdef FR_XLONG
#define P5D "%5ld"
#endif

#ifdef FR_XLOLO
#define P5D "%5lld"
#endif

#ifdef FR_XDOUB
#define P11E "%+#11.3lE"
#define P11EB "%+#11.3lE "
#endif

#ifdef FR_XQUAD
#define P11E "%+#11.3LE"
#define P11EB "%+#11.3LE "
#endif

/***********************************************************************
*  hier beginnt Function sest88
***********************************************************************/
int sest88(FR_INT4 k)
{
extern FILE *fo3;

extern FR_DOUBLEAY gmw;

extern FR_DOUBLE ul[];
extern FR_DOUBLE xk[],yk[];

extern FR_DOUBLE emode;

extern FR_INT4 LANG,kc,ifnili;

FR_DOUBLE zug,dlunv,dlv,xv,yv,xu,yu;

/***********************************************************************
* gedehnte Laenge berechnen
***********************************************************************/
xv= xk[1]+ul[1] - xk[2]-ul[3];
yv= yk[1]+ul[2] - yk[2]-ul[4];

dlv= FR_SQRT( xv * xv + yv * yv );

/***********************************************************************
* unverformte Laenge bestimmen
***********************************************************************/
xu= xk[1]-xk[2];
yu= yk[1]-yk[2];

dlunv= FR_SQRT( xu * xu + yu * yu );

/***********************************************************************
* Spannung berechnen
***********************************************************************/
zug= emode * (dlv/dlunv - 1.);

if(ifnili == 0)
  {
  if(LANG == 1) fprintf(fo3,"\n\nElement # = " P5D "     Typ = Stab in Ebene\
     SIG = " P11E,k,zug);
  if(LANG == 2) fprintf(fo3,"\n\nelement # = " P5D "     type = truss in plane\
     SIG = " P11E,k,zug);
  }

gmw[kc]= zug;

return(0);
}

/***********************************************************************
* hier beginnt Function ssta88
***********************************************************************/
int ssta88(FR_INT4 k)
{
extern FILE *fo3;

extern FR_DOUBLEAY gmw;

extern FR_DOUBLE ul[];
extern FR_DOUBLE xk[],yk[],zk[];

extern FR_DOUBLE emode;

extern FR_INT4 LANG,kc,ifnili;

FR_DOUBLE zug,dlunv,dlv,xv,yv,zv,xu,yu,zu;
        
/***********************************************************************
* gedehnte Laenge berechnen
***********************************************************************/
xv= xk[1]+ul[1] - xk[2]-ul[4];
yv= yk[1]+ul[2] - yk[2]-ul[5];
zv= zk[1]+ul[3] - zk[2]-ul[6];

dlv= FR_SQRT( xv * xv + yv * yv + zv * zv);

/***********************************************************************
* unverformte Laenge bestimmen
***********************************************************************/
xu= xk[1]-xk[2];
yu= yk[1]-yk[2];
zu= zk[1]-zk[2];

dlunv= FR_SQRT( xu * xu + yu * yu + zu * zu);

/***********************************************************************
* Spannung berechnen
***********************************************************************/
zug= emode * (dlv/dlunv - 1.);

if(ifnili == 0)
  {
  if(LANG == 1) fprintf(fo3,"\n\nElement # = " P5D "     Typ = Stab im Raum\
     SIG = " P11E,k,zug);
  if(LANG == 2) fprintf(fo3,"\n\nelement # = " P5D "     type = truss in space\
     SIG = " P11E,k,zug);
  }

gmw[kc]= zug;

return(0);
}

/***********************************************************************
* hier beginnt Function swel88
***********************************************************************/
int swel88(void)
{
extern FILE *fo3;

extern FR_DOUBLE ul[];
extern FR_DOUBLE xk[];

extern FR_DOUBLE emode,rnuee,qparae;

extern FR_INT4 ifnili;

FR_DOUBLE rlu,rlv,fac,qrlu;
FR_DOUBLE sigxx,tauxx,sigxy1,sigxy2,sigxz1,sigxz2;

/***********************************************************************
* gedehnte Laenge & unverformte Laenge berechnen
***********************************************************************/
rlv= xk[2]+ul[7] - xk[1]-ul[1];
rlu= xk[2]-xk[1];

/***********************************************************************
* Spannungen berechnen
***********************************************************************/
sigxx= emode * (rlv/rlu - 1.);
tauxx= (ul[10] - ul[4])/rlu * emode /(4.*(1.+rnuee))*qparae;

fac= emode * 0.5 * qparae;
qrlu= rlu * rlu;

sigxy1= fac* 2. * (3. * (ul[8] - ul[2]) - 
        rlu * (2. * ul[6] + ul[12]))/qrlu;
sigxy2= sigxy1 + fac * 6. * (2. * (ul[2] - ul[8]) + 
        rlu * (ul[12] + ul[6]))/qrlu;

sigxz1= fac * 2. * (3. *(ul[9] - ul[3]) -
        rlu * (2. * ul[5] + ul[11]))/qrlu;
sigxz2= sigxz1 + fac * 6. * (2. * (ul[3] - ul[9]) +
        rlu * (ul[11] + ul[5]))/qrlu;

if(ifnili == 0)
  fprintf(fo3,NL P11EB P11EB P11EB P11EB P11EB P11E,
  sigxx,tauxx,sigxy1,sigxz1,sigxy2,sigxz2);

return(0);
}

/***********************************************************************
* hier beginnt Function sbal88
***********************************************************************/
int sbal88(void)
{      
extern FILE *fo3;

extern FR_DOUBLE ul[];
extern FR_DOUBLE xk[],yk[],zk[];

extern FR_DOUBLE emode,rnuee;
extern FR_DOUBLE eyye,ezze,rite,wte;

extern FR_INT4 ifnili;

FR_DOUBLE c[10];                /* 3 x 3 + 1 */
FR_DOUBLE ulo[13];

FR_DOUBLE rl,rlc,rlv,fac,xu,yu,zu,qrl;
FR_DOUBLE sigxx,tauxx,sigzz1,sigzz2,sigyy1,sigyy2;
        
FR_INT4 j;
        
/***********************************************************************
* die Richtungscosinus bestimmen
***********************************************************************/
xu= xk[2] - xk[1];
yu= yk[2] - yk[1];
zu= zk[2] - zk[1];
rl= FR_SQRT(xu * xu + yu * yu + zu * zu );
qrl = rl * rl;

c[1]= (xk[2]-xk[1])/rl;
c[2]= (yk[2]-yk[1])/rl;
c[3]= (zk[2]-zk[1])/rl;

rlc= FR_SQRT(c[1] * c[1] + c[2] * c[2]);
if(rlc > 1e-12)
  {
  c[4]= -c[2]/rlc;
  c[5]=  c[1]/rlc;
  c[6]=  0.;
  }
else
  {
  c[4]= 0.;
  c[5]= 1.;
  c[6]= 0.;
  }

c[7]= -c[3] * c[5];
c[8]=  c[3] * c[4];
c[9]=  c[1] * c[5] - c[2] * c[4];

/***********************************************************************
* Globale auf lokale Verschiebungen umrechnen
***********************************************************************/
for(j = 1;j <= 3;j++)
  {
  ulo[j]  = c[(j-1)*3+1]*ul[1] +c[(j-1)*3+2]*ul[2] +c[(j-1)*3+3]*ul[3];  
  ulo[j+3]= c[(j-1)*3+1]*ul[4] +c[(j-1)*3+2]*ul[5] +c[(j-1)*3+3]*ul[6]; 
  ulo[j+6]= c[(j-1)*3+1]*ul[7] +c[(j-1)*3+2]*ul[8] +c[(j-1)*3+3]*ul[9];  
  ulo[j+9]= c[(j-1)*3+1]*ul[10]+c[(j-1)*3+2]*ul[11]+c[(j-1)*3+3]*ul[12];  
  }

/***********************************************************************
* Spannungen berechnen
***********************************************************************/
rlv= rl + ulo[7] - ulo[1];

sigxx= emode * (rlv/rl - 1.);
tauxx= (ulo[10] - ulo[4])/rl * emode/(2. * (1. + rnuee)) * rite /wte;

fac= emode * ezze;

sigzz1= fac * 2. * (3. * (ulo[8] - ulo[2]) -
        rl * (2. * ulo[6] + ulo[12]))/qrl;
sigzz2= sigzz1 + fac * 6. * (2. * (ulo[2] - ulo[8]) +
        rl * (ulo[12] + ulo[6]))/qrl;

fac= emode * eyye;

sigyy1= fac * 2. * (3. * (ulo[9] - ulo[3]) +
        rl * (2. * ulo[5] + ulo[11]))/qrl;
sigyy2= sigyy1 + fac * 6. * (2. * (ulo[3] - ulo[9]) -
        rl * (ulo[11] + ulo[5]))/qrl;

if(ifnili == 0)
  fprintf(fo3,NL P11EB P11EB P11EB P11EB P11EB P11E, 
  sigxx,tauxx,sigzz1,sigyy1,sigzz2,sigyy2);

return(0);
}

/***********************************************************************
* hier beginnt Function seba88
***********************************************************************/
int seba88(void)
{
extern FILE *fo3;

extern FR_DOUBLE ul[];
extern FR_DOUBLE xk[],yk[];

extern FR_DOUBLE emode;
extern FR_DOUBLE ezze;

extern FR_INT4 ifnili;

FR_DOUBLE ulo[7];

FR_DOUBLE rl,rlv,fac,ca,sa,xu,yu,qrl;
FR_DOUBLE sigxx,sigzz1,sigzz2;
        
/***********************************************************************
* die Richtungscosinus bestimmen
***********************************************************************/
xu= xk[2] - xk[1];
yu= yk[2] - yk[1];
rl= FR_SQRT(xu * xu + yu * yu );
qrl = rl * rl;

ca= (xk[2]-xk[1])/rl;
sa= (yk[2]-yk[1])/rl;

/***********************************************************************
* Globale auf lokale Verschiebungen umrechnen
***********************************************************************/
ulo[1]=  ca * ul[1] + sa * ul[2];
ulo[2]= -sa * ul[1] + ca * ul[2];
ulo[3]=  ul[3];
ulo[4]=  ca * ul[4] + sa * ul[5];
ulo[5]= -sa * ul[4] + ca * ul[5];
ulo[6]=  ul[6];
        
/***********************************************************************
* Spannungen berechnen
***********************************************************************/     
rlv= rl + ulo[4] - ulo[1];

sigxx= emode * (rlv/rl - 1.);

fac= emode * ezze;

sigzz1= fac * 2. * (3. * (ulo[5] - ulo[2]) -
        rl * (2. * ulo[3] + ulo[6]))/qrl;
sigzz2= sigzz1 + fac * 6. * (2. * (ulo[2] - ulo[5]) +
        rl * (ulo[6] + ulo[3]))/qrl;

if(ifnili == 0)
  fprintf(fo3,NL P11E "                               " P11E\
"       " P11E,sigxx,sigzz1,sigzz2);

return(0);
}
