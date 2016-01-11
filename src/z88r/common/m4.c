/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows & UNIX OS.
*
* Composed and edited and copyright by 
* Professor Dr.-Ing. Frank Rieg, University of Bayreuth, Germany
*
* eMail: 
* frank.rieg@uni-bayreuth.de
* dr.frank.rieg@t-online.de
* 
* V14.0  January 14, 2009
*
* Z88 should compile and run under any UNIX OS and Windows.
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
* Compiler-Unit m4.c enthaelt:
*        sshe88.for : 6-knoten scheibe
*        srin88.for : 3-knoten torus
* 2.1.2010 Rieg
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

#ifdef FR_XDOUB
#define P10E " %+#10.2lE"
#define P11E " %+#11.3lE"
#endif

#ifdef FR_XQUAD
#define P10E " %+#10.2LE"
#define P11E " %+#11.3LE"
#endif

/***********************************************************************
*  Functions
***********************************************************************/
FR_DOUBLE sheigh(FR_DOUBLE sig[]);
FR_DOUBLE torgh(FR_DOUBLE sig[]);
FR_DOUBLE sheinh(FR_DOUBLE sig[]);
FR_DOUBLE tornh(FR_DOUBLE sig[]);
FR_DOUBLE sheish(FR_DOUBLE sig[]);
FR_DOUBLE torsh(FR_DOUBLE sig[]);

/***********************************************************************
* hier beginnt Function sshe88
***********************************************************************/
int sshe88(void)
{
extern FILE *fo3,*fo5;

extern FR_DOUBLEAY gmw;
extern FR_DOUBLEAY sigvku;

extern FR_DOUBLE ul[];
extern FR_DOUBLE xk[],yk[];

extern FR_DOUBLE emode,rnuee;

extern FR_INT4 kflag,isflag,kc,jpri,ifnili,ngau;

FR_DOUBLE sig[4];

FR_DOUBLE rr,phirad,phideg,sinphi,cosphi;
FR_DOUBLE qsin,qcos,sincos; 
FR_DOUBLE x21,x31,y21,y31,det,uxsi,vxsi,ueta,veta,xs,ys;
FR_DOUBLE epsx,epsy,gamxy,sigr,sigt,taurt,sigv;

/***********************************************************************
* Hilfswerte berechnen
***********************************************************************/
x21= xk[2] - xk[1];
x31= xk[3] - xk[1];
y21= yk[2] - yk[1];
y31= yk[3] - yk[1];

/***********************************************************************
* Jacobi-Determinate
***********************************************************************/
det= x21 * y31 - x31 * y21;

/***********************************************************************
* Partielle Ableitungen im Einheitsdreieck glch.2.169,s.123  
***********************************************************************/
uxsi= (ul[3] - ul[1] + 4. * (ul[9]  - ul[11])) / 3.;
vxsi= (ul[4] - ul[2] + 4. * (ul[10] - ul[12])) / 3.;
ueta= (ul[5] - ul[1] + 4. * (ul[9]  - ul[7] )) / 3.;
veta= (ul[6] - ul[2] + 4. * (ul[10] - ul[8] )) / 3.;

/***********************************************************************
* Dehnungen lt. Glch. 2.167, s.123  
***********************************************************************/
epsx=  (y31 * uxsi - y21 * ueta) / det;
epsy=  (x21 * veta - x31 * vxsi) / det;
gamxy= (x21 * ueta - x31 * uxsi + y31 * vxsi - y21 * veta) / det;

/***********************************************************************
* Spannungen lt. Glch. 2.166, s.123
***********************************************************************/
sig[1]= emode * (epsx + rnuee * epsy) / (1. - rnuee * rnuee);
sig[2]= emode * (rnuee * epsx + epsy) / (1. - rnuee * rnuee);
sig[3]= emode * gamxy / (2. * (1. + rnuee));

/***********************************************************************
* Entscheiden, ob mit oder ohne Polarkoordinaten
***********************************************************************/
xs= (xk[1] + xk[2] + xk[3]) / 3.;
ys= (yk[1] + yk[2] + yk[3]) / 3.;

if(isflag == 0)                                            /* ohne VglS */
  {
  if(kflag == 1)                                           /* mit sigr */
    {
    rr= FR_SQRT(xs * xs + ys * ys);
    if(xs == 0.) xs= 1e-10;
    phirad= FR_ATAN(ys/xs);
    phideg= phirad*57.29578;

    sinphi= FR_SIN(phirad);
    cosphi= FR_COS(phirad);
    qsin= sinphi*sinphi;
    qcos= cosphi*cosphi;
    sincos= sinphi*cosphi;

    sigr=  sig[1] * qcos + sig[2] * qsin + 2. * sig[3] * sincos;
    sigt=  sig[1] * qsin + sig[2] * qcos - 2. * sig[3] * sincos;
    taurt= (sig[2] - sig[1]) * sincos + sig[3] * (qcos-qsin);

    if(ifnili == 0)
      {
      fprintf(fo3,NL P10E P10E P11E P11E P11E P10E P10E P11E P11E P11E
      ,xs,ys,sig[1],sig[2],sig[3],rr,phideg,sigr,sigt,taurt);
      }
    }                                                      /* e if mit sigr */
  else
    {                                                      /* ohne sigr */
    if(ifnili == 0)
      {
      fprintf(fo3,NL P10E P10E P11E P11E P11E
      ,xs,ys,sig[1],sig[2],sig[3]);
      }                                                    /* e if jpri */
    }                                                      /* e if ohne sigr */
  }                                                        /* e if ohne GEH */ 

if(isflag == 1 || isflag == 2 || isflag == 3)              /* mit GEH */
  {
  if(isflag == 1) sigv= sheigh(sig);
  if(isflag == 2) sigv= sheinh(sig);
  if(isflag == 3) sigv= sheish(sig);

  ngau++;
  sigvku[ngau]+= sigv;

  if(kflag == 1)                                           /* mit sigr */
    {
    rr= FR_SQRT(xs * xs + ys * ys);
    if(xs == 0.) xs= 1e-10;
    phirad= FR_ATAN(ys/xs);
    phideg= phirad*57.29578;

    sinphi= FR_SIN(phirad);
    cosphi= FR_COS(phirad);
    qsin= sinphi*sinphi;
    qcos= cosphi*cosphi;
    sincos= sinphi*cosphi;

    sigr=  sig[1] * qcos + sig[2] * qsin + 2. * sig[3] * sincos;
    sigt=  sig[1] * qsin + sig[2] * qcos - 2. * sig[3] * sincos;
    taurt= (sig[2] - sig[1]) * sincos + sig[3] * (qcos-qsin);

    if(ifnili == 0)
      {
      fprintf(fo3,NL P10E P10E P11E P11E P11E P10E P10E P11E P11E P11E P11E
      ,xs,ys,sig[1],sig[2],sig[3],rr,phideg,sigr,sigt,taurt,sigv);
      }
    }                                                      /* e if mit sigr */
  else
    {                                                      /* ohne sigr */
    if(ifnili == 0)
      {     
      fprintf(fo3,P10E P10E P11E P11E P11E P11E
      ,xs,ys,sig[1],sig[2],sig[3],sigv);
      }
    }                                                      /* e if ohne sigr */

  if(jpri == 1)
    {
    fprintf(fo5,NL P11E P11E P11E,xs,ys,sigvku[ngau]);
    }
  gmw[kc]= sigv; 
  }                                                        /* e if mit GEH */ 

return(0);
}

/***********************************************************************
* hier beginnt Function srin88
***********************************************************************/
int srin88(void)
{
extern FILE *fo3,*fo5;

extern FR_DOUBLEAY gmw;
extern FR_DOUBLEAY sigvku;

extern FR_DOUBLE ul[];
extern FR_DOUBLE xk[],yk[];

extern FR_DOUBLE emode,rnuee;

extern FR_INT4 isflag,kc,jpri,ifnili,ngau;

FR_DOUBLE a[4],b[4],c[4],d[4];
FR_DOUBLE hdb[25];                        /* 4 x 6 +1 */
FR_DOUBLE sig[5],sigmit[5];
        
FR_DOUBLE f0,f1,f2,flaec,tsig1,tsig2,tsig3,tsig4,sigv,xx,yy,xs,ys;
         
FR_INT4 k,i,j;

static FR_INT4 izyk[6]= { 0,
                          1,2,3,1,2 };

/***********************************************************************
* Flaeche des Dreiecks
***********************************************************************/
flaec= 0.5 * ( xk[1] * (yk[2] - yk[3]) + xk[2] * (yk[3] - yk[1]) +
            +  xk[3] * (yk[1] - yk[2]) );   

/***********************************************************************
* Berechnung f0, f1 & f2
***********************************************************************/
f0= emode*(1.-rnuee)/(1.+rnuee)/(1.-2.*rnuee); 
f1= rnuee/(1.-rnuee); 
f2= (1.-2.*rnuee)/2./(1.-rnuee);  

/***********************************************************************
* Berechnung von a(i), b(i) ,c(i) & d(i)
***********************************************************************/
for(i = 1;i <= 4;i++)
  sigmit[i]= 0.;

for(i = 1;i <= 3;i++)                  /* ueber 3 Knoten */      
  {                                                        /* 70 */
  xx= xk[i];
  yy= yk[i];         
  for(k = 1;k <= 3;k++)
    {
    a[k]= xk[izyk[k+1]] * yk[izyk[k+2]] - xk[izyk[k+2]] * yk[izyk[k+1]]; 
    b[k]= yk[izyk[k+1]] - yk[izyk[k+2]]; 
    c[k]= xk[izyk[k+2]] - xk[izyk[k+1]]; 
    d[k]= a[k] / xx + b[k] + c[k] * yy / xx;
    }                                                      /* e 30 */

/***********************************************************************
* Matrix hdb = d*b berechnen
***********************************************************************/
  hdb[1 ]= f1 * b[1] + f1 * d[1];
  hdb[7 ]= b[1]      + f1 * d[1];
  hdb[13]= f1 * b[1] +      d[1];
  hdb[19]= f2 * c[1];

  hdb[2 ]= c[1];
  hdb[8 ]= f1 * c[1];
  hdb[14]= f1 * c[1];
  hdb[20]= f2 * b[1];

  hdb[3 ]= f1 * b[2] + f1 * d[2];
  hdb[9 ]= b[2]      + f1 * d[2];
  hdb[15]= f1 * b[2] +      d[2];
  hdb[21]= f2 * c[2];

  hdb[4 ]= c[2];
  hdb[10]= f1 * c[2];
  hdb[16]= f1 * c[2];
  hdb[22]= f2 * b[2];

  hdb[5 ]= f1 * b[3] + f1 * d[3];
  hdb[11]= b[3]      + f1 * d[3];
  hdb[17]= f1 * b[3] +      d[3];
  hdb[23]= f2 * c[3];

  hdb[6 ]= c[3];
  hdb[12]= f1 * c[3];
  hdb[18]= f1 * c[3];
  hdb[24]= f2 * b[3];
    
/***********************************************************************
* nun Spannungen berechnen
***********************************************************************/
  for(j = 1;j <= 4;j++)
    {
    sig[j]= 0.;
    for(k = 1;k <= 6;k++)
      {
      sig[j]= sig[j] + hdb[(j-1)*6 + k] * ul[k] * f0 / 2. / flaec;
      }
    sigmit[j]= sigmit[j] + sig[j];
    }
  }                                                        /* e70 */

/*---------------------------------------------------------------------
* mittlere Spannungen im Elementschwerpunkt berechnen
*--------------------------------------------------------------------*/
for(i = 1;i <= 4;i++)
   sigmit[i]= sigmit[i] * 0.33333333;  /* durch 3, weil 3 Knoten */

/*---------------------------------------------------------------------
* bis jetzt gilt:
* sigmit[1] = ueber die Knoten gemittelte SIGZZ
* sigmit[2] = ueber die Knoten gemittelte SIGRR
* sigmit[3] = ueber die Knoten gemittelte SIGTE
* sigmit[4] = ueber die Knoten gemittelte TAURZ
* ab jetzt werden die sigmit vertauscht: fuer torgh und Kompatibilitaet
* zu sqsh88 und scsh88
*--------------------------------------------------------------------*/
tsig1= sigmit[1];
tsig2= sigmit[2];
tsig3= sigmit[3];
tsig4= sigmit[4];
sigmit[1]= tsig2;
sigmit[2]= tsig1;
sigmit[3]= tsig4;
sigmit[4]= tsig3;

/*---------------------------------------------------------------------
* ab jetzt gilt:
* sigmit[1] = ueber die Knoten gemittelte SIGRR
* sigmit[2] = ueber die Knoten gemittelte SIGZZ
* sigmit[3] = ueber die Knoten gemittelte TAURZ
* sigmit[4] = ueber die Knoten gemittelte SIGTE
*--------------------------------------------------------------------*/

/***********************************************************************
* Beschreiben der Files Z88O3.TXT & Z88O5.TXT
***********************************************************************/
xs= 0.33333333 * (xk[1] + xk[2] + xk[3]);
ys= 0.33333333 * (yk[1] + yk[2] + yk[3]);

if(isflag == 0 && ifnili == 0)                           /* ohne VglS */
  {
  fprintf(fo3,NL P10E P10E P11E P11E P11E P11E
  ,xs,ys,sigmit[1],sigmit[2],sigmit[3],sigmit[4]);
  }

if(isflag == 1 || isflag == 2 || isflag == 3)              /* mit GEH */
  {
  if(isflag == 1) sigv= torgh(sigmit);
  if(isflag == 2) sigv= tornh(sigmit);
  if(isflag == 3) sigv= torsh(sigmit);

  ngau++;
  sigvku[ngau]+= sigv;

  if(ifnili == 0)
    {
    fprintf(fo3,NL P10E P10E P11E P11E P11E P11E P11E
    ,xs,ys,sigmit[1],sigmit[2],sigmit[3],sigmit[4],sigv);
    }
  if(jpri == 1)
    {
    fprintf(fo5,NL P11E P11E P11E,xs,ys,sigvku[ngau]);
    }
  gmw[kc]= sigv; 
  }                                                        /* e if mit GEH */
return(0);
}
