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
* Diese Compiler-Unit m2.c enthaelt:
*        shei88  : 6-Knoten Scheibe
*        ring88  : 3-Knoten Torus
* Diese Compiler-Unit enthaelt Programmteile, die gedanklich an FORTRAN-
* Quellen von H.R. Schwarz, ETH Zuerich, Schweiz, angelehnt sind.
* 2.1.2010 Rieg
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
* Fuer Windows & GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88r.h>
#endif

/***********************************************************************
* hier beginnt Function shei88
***********************************************************************/
int shei88(void)
{
extern FR_DOUBLEAY se;

extern FR_DOUBLE xk[],yk[];

extern FR_DOUBLE emode,rnuee,qparae;

FR_DOUBLE rj,factor,rmu,x21,x31,y21,y31;
FR_DOUBLE a1,a2,a3,b1,b2,b3,c1,c2,c3,d3;
        
FR_INT4 n,i,ii,iim1,j,jj,jjm1; 

/*----------------------------------------------------------------------
* Die Matrizen k1,k2 und k3 belegen
*---------------------------------------------------------------------*/
static FR_INT4 k1[37]= { 0,
                         3, 1, 0,-4, 0, 0,              
                         1, 3, 0,-4, 0, 0,
                         0, 0, 0, 0, 0, 0,
                        -4,-4, 0, 8, 0, 0,
                         0, 0, 0, 0, 8,-8,
                         0, 0, 0, 0,-8, 8 };
                         
static FR_INT4 k2[37]= { 0,
                         3, 0, 1, 0, 0,-4,
                         1, 0,-1,-4, 4, 0,
                         0, 0, 0, 0, 0, 0,
                        -4, 0, 0, 4,-4, 4,
                         0, 0, 4,-4, 4,-4,
                         0, 0,-4, 4,-4, 4 };
                          
static FR_INT4 k3[37]= { 0,
                         3, 0, 1, 0, 0,-4,
                         0, 0, 0, 0, 0, 0,
                         1, 0, 3, 0, 0,-4,
                         0, 0, 0, 8,-8, 0,
                         0, 0, 0,-8, 8, 0,
                        -4, 0,-4, 0, 0, 8 };
                                         

/***********************************************************************
* Start
***********************************************************************/
rmu= (1. - rnuee)*0.5;
       
x21= xk[2] - xk[1];
x31= xk[3] - xk[1];
y21= yk[2] - yk[1];
y31= yk[3] - yk[1];
        
/***********************************************************************
* Jacobi-Determinante , I,S.68
***********************************************************************/ 
rj= x21 * y31 - x31 * y21;

/***********************************************************************
* moegliche Fehlerbedingung: Jacobi-Determinate negativ
***********************************************************************/
if(rj <= 0.) return(AL_JACNEG);

/***********************************************************************
* factor enthaelt: eh/(1-v**2), j und 1/6 aus den Grundmatrizen
***********************************************************************/ 
factor=emode * qparae/(1. - rnuee * rnuee)/rj/6.;

/***********************************************************************
* Berechnung der Koeffizienten a1 bis d3 nach I,S.116
***********************************************************************/
a1= (rmu*x31*x31 + y31*y31) * factor;
b1=-(rmu*x21*x31 + y21*y31) * factor;
c1= (rmu*x21*x21 + y21*y21) * factor;
a2= (x31*x31 + rmu*y31*y31) * factor;
b2=-(x21*x31 + rmu*y21*y31) * factor;
c2= (x21*x21 + rmu*y21*y21) * factor;
a3= -0.5*(1.+rnuee)*x31*y31 * factor;
b3= (rnuee*x21*y31+rmu*x31*y21)*factor;
c3= (rnuee*x31*y21+rmu*x21*y31)*factor;
d3= -0.5*(1.+rnuee)*x21*y21  *factor;

/***********************************************************************
* Berechnung der Element-Steifigkeitsmatrix Scheibenelement
***********************************************************************/
n=12;

for(i = 1;i <= 6;i++)
  {
  ii=i+i;
  iim1= ii-1;
  for(j = 1;j <= 6;j++)
    {
    jj= j+j;
    jjm1= jj-1;
    se[iim1 +n*(jjm1-1)]= a1 * k1[(i-1)*6 + j] +
                          b1 * (k2[(i-1)*6 + j] + k2[(j-1)*6 + i]) +
                          c1 * k3[(i-1)*6 + j];
   
    se[ii +n*(jj-1)]=     a2 * k1[(i-1)*6 + j]+
                          b2 * (k2[(i-1)*6 + j] + k2[(j-1)*6 + i]) +
                          c2 * k3[(i-1)*6 + j];

    se[iim1 +n*(jj-1)]=   a3 * k1[(i-1)*6 + j] +
                          b3 * k2[(i-1)*6 + j] + 
                          c3 * k2[(j-1)*6 + i] + 
                          d3 * k3[(i-1)*6 + j];

    se[jj +n*(iim1-1)]= se[iim1 +n*(jj-1)];
    }
  }

return(0);
}

/***********************************************************************
* hier beginnt Function ring88
***********************************************************************/
int ring88(void)
{
extern FR_DOUBLEAY se;

extern FR_DOUBLE xk[],yk[];

extern FR_DOUBLE emode,rnuee;

FR_DOUBLE a[4],b[4],c[4];
FR_DOUBLE ke[5];           /* 2x2 */
        
FR_DOUBLE factor,f0,f1,f2;
FR_DOUBLE rmit,zmit,flaec,pi,gi,gj;

FR_INT4 k,ne,i,j;

static FR_INT4 izyk[6]= { 0,1,2,3,1,2 };

pi= 3.141592654;
ne= 6;

/***********************************************************************
* Flaeche des Dreiecks
***********************************************************************/
flaec=  0.5*( xk[1]*(yk[2]-yk[3]) + 
              xk[2]*(yk[3]-yk[1]) +
              xk[3]*(yk[1]-yk[2]) );

/***********************************************************************
* Berechnung f0, f1 & f2
***********************************************************************/
f0= emode *(1.-rnuee)/(1.+rnuee)/(1.-2.*rnuee); 
f1= rnuee/(1.-rnuee); 
f2= (1.-2.*rnuee)/2./(1.-rnuee);

/***********************************************************************
* Berechnung von a(i), b(i) und c(i)
***********************************************************************/
for(k = 1;k <= 3;k++)
  {
  a[k]= xk[izyk[k+1]]*yk[izyk[k+2]] - 
        xk[izyk[k+2]]*yk[izyk[k+1]]; 
  b[k]= yk[izyk[k+1]]-yk[izyk[k+2]]; 
  c[k]= xk[izyk[k+2]]-xk[izyk[k+1]]; 
  }

/***********************************************************************
* Berechnung von rmit und zmit & des gemeinsamen Faktors factor
***********************************************************************/
rmit= (xk[1]+xk[2]+xk[3])/3.;
zmit= (yk[1]+yk[2]+yk[3])/3.;
        
factor= pi*f0*rmit/2./flaec;

/***********************************************************************
* Berechnung der Untermatrix ke und sodann der Steifigkeitsmatrix se
***********************************************************************/
for(i = 1;i <= 3;i++)
  {
  gi= a[i]/rmit + b[i] + c[i]*zmit/rmit;
  for(j = 1;j <= 3;j++)
    {
    gj= a[j]/rmit + b[j] + c[j]*zmit/rmit;
    ke[1]= (b[i]+gi*f1)*b[j] + (b[i]*f1+gi)*gj + c[i]*c[j]*f2;
    ke[3]= c[i]*f1*(b[j]+gj) + b[i]*f2*c[j];
    ke[2]= c[j]*f1*(b[i]+gi) + b[j]*f2*c[i];
    ke[4]= c[i]*c[j] + b[i]*b[j]*f2;

/*---------------------------------------------------------------------
* Einbau zur 6*6 Steifigkeitsmatrix
*--------------------------------------------------------------------*/
    se[2*i-1 + ne*(2*j-2)]= ke[1]*factor;
    se[2*i   + ne*(2*j-2)]= ke[3]*factor;
    se[2*i-1 + ne*(2*j-1)]= ke[2]*factor;
    se[2*i   + ne*(2*j-1)]= ke[4]*factor;
    }
  }

return(0);
}

