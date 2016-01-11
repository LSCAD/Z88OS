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
* Diese Compiler-Unit m1.c enthaelt:
*        esta88.c  : stab in der ebene
*        stab88.c  : stab im raum
*        well88.c  : welle im raum
*        balk88.c  : balken im raum
*        ebal88.c  : ebener balken
* Diese Compiler-Unit enthaelt Programmteile, die gedanklich an FORTRAN-
* Quellen von H.R. Schwarz, ETH Zuerich, Schweiz, angelehnt sind.
*
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
* hier beginnt Function esta88
***********************************************************************/
int esta88(void)
{
extern FR_DOUBLEAY se;

extern FR_DOUBLE xk[],yk[];

extern FR_DOUBLE emode,qparae;

FR_DOUBLE x21,y21,rlaeng,fak,cosq,sinq,sincos; 

/***********************************************************************
* Bestimmung der Stablaenge
***********************************************************************/
x21= xk[2] - xk[1];
y21= yk[2] - yk[1];

rlaeng= FR_SQRT(x21*x21 + y21*y21);

/***********************************************************************
* Transformation auf globale Koordinaten ; Hilfsfaktor fak ber.
***********************************************************************/
fak= emode * qparae / rlaeng;

cosq  = fak * (x21/rlaeng)*(x21/rlaeng);
sinq  = fak * (y21/rlaeng)*(y21/rlaeng);
sincos= fak * x21*y21/(rlaeng*rlaeng);

/***********************************************************************
* Berechnen der Elementsteifigkeitsmatrix
***********************************************************************/
se[1] =  cosq;
se[2] =  sincos;
se[3] = -cosq;
se[4] = -sincos;
        
se[5] =  sincos;
se[6] =  sinq;
se[7] = -sincos;
se[8] = -sinq;
         
se[9] = -cosq;
se[10]= -sincos;
se[11]=  cosq;
se[12]=  sincos;
        
se[13]= -sincos;
se[14]= -sinq;
se[15]=  sincos;
se[16]=  sinq;
                
return(0);
}

/***********************************************************************
* hier beginnt Function stab88
***********************************************************************/
int stab88(void)
{
extern FR_DOUBLEAY se;

extern FR_DOUBLE xk[],yk[],zk[];

extern FR_DOUBLE emode,qparae;

FR_DOUBLE c[4];
        
FR_DOUBLE x21,y21,z21,rlaeng,h,fak;

FR_INT4 i,j,n;

n= 6;

/***********************************************************************
* Bestimmung der Stablaenge
***********************************************************************/
x21= xk[2] - xk[1];
y21= yk[2] - yk[1];
z21= zk[2] - zk[1];

rlaeng= FR_SQRT(x21*x21 + y21*y21 + z21*z21);

/***********************************************************************
* Transformation auf globale Koordinaten mit cos; Hilfsfaktor fak ber.
***********************************************************************/
c[1]= x21/rlaeng;
c[2]= y21/rlaeng;
c[3]= z21/rlaeng;

fak= emode * qparae / rlaeng;

/***********************************************************************
* Berechnen der Elementsteifigkeitsmatrix
***********************************************************************/
for(i = 1;i <= 3;i++)
  {
  for(j = 1;j <= 3;j++)
    {
    h= c[i] * c[j] * fak;
    se[i+n*(j-1)]= h;
    se[i+3+n*(j+2)]= h;
    se[i+3+n*(j-1)]= -h;
    se[i+n*(j+2)]= -h;
    }
  }

return(0);
}

/***********************************************************************
* hier beginnt Function well88
***********************************************************************/
int well88(void)
{
extern FR_DOUBLEAY se;

extern FR_DOUBLE xk[];

extern FR_DOUBLE emode,rnuee,qparae;

FR_DOUBLE rl,a,rib,rit,pi,qpqp;
FR_DOUBLE eal,ei12,ei6,git,ei4,ei2;
      
FR_INT4 i,j,n;
        
pi= 3.141592654;
n= 12;

/***********************************************************************
* Laenge,Flaeche und die beiden Traegheitsmomente bestimmen
***********************************************************************/
qpqp= qparae*qparae;

rl  = xk[2] - xk[1];
a   = pi * 0.25 * qpqp;
rib = pi / 64. * qpqp*qpqp;
rit = rib * 2.;

/***********************************************************************
* Koeffizienten bestimmen
***********************************************************************/
eal  = emode * a /rl;
ei12 = emode * rib * 12. / FR_POW(rl,3.);
ei6  = emode * rib * 6. / (rl*rl);
git  = emode * rit / (2.*(1.+rnuee)*rl);
ei4  = emode * rib * 4. / rl;
ei2  = 0.5 * ei4;

/***********************************************************************
* Elementsteifigkeitsmatrix se bestimmen
***********************************************************************/
for(i = 1;i <= 144;i++)
  se[i]= 0.;

se[1] =  eal;
se[7] = -eal;
se[14]=  ei12;
se[18]=  ei6;
se[20]= -ei12;
se[24]=  ei6;
se[27]=  ei12;
se[29]=  ei6;
se[33]= -ei12;
se[35]=  ei6;
se[40]=  git;
se[46]= -git;
se[53]=  ei4;
se[57]= -ei6;
se[59]=  ei2;
se[66]=  ei4;
se[68]= -ei6;
se[72]=  ei2;
se[79]=  eal;
se[92]=  ei12;
se[96]= -ei6;
se[105]= ei12;
se[107]=-ei6;
se[118]= git;
se[131]= ei4;
se[144]= ei4;

for(j = 1;j <= 12;j++)
  {
  for(i = j;i <= 12;i++)
    {
    se[j+n*(i-1)]= se[i+n*(j-1)];
    }
  }

return(0);
}
            
/***********************************************************************
* hier beginnt Function balk88
***********************************************************************/
int balk88(void)
{
extern FR_DOUBLEAY se;

extern FR_DOUBLE xk[],yk[],zk[];

extern FR_DOUBLE emode,rnuee,qparae,riyye,rizze,rite;

FR_DOUBLE c[10];     /* 3x3 */
FR_DOUBLE s[4];
        
FR_DOUBLE x21,y21,z21,rlaeng,slaeng;
FR_DOUBLE fakzs,fakts,fakb1s,fakb2s;
FR_DOUBLE ss,s32,s23;
      
FR_INT4 n,ih,jh,i,j,i1,j1,id,jd,k,ii,jj;

int icase;

static FR_INT4 isl[5] = { 0,
                          1,-1,
                         -1, 1 };
                         
static FR_INT4 isk[17]= { 0,
                          6, 3,-6, 3,
                          3, 2,-3, 1,
                         -6,-3, 6,-3,
                          3, 1,-3, 2 };
n= 12;

/***********************************************************************
* Laenge im Raum durch Pythagoras bestimmen
***********************************************************************/
x21 = xk[2]-xk[1];
y21 = yk[2]-yk[1];
z21 = zk[2]-zk[1];
rlaeng = FR_SQRT(x21*x21 + y21*y21 + z21*z21 );

/***********************************************************************
* Transformation auf globale Koordinaten mit COS
***********************************************************************/
c[1] = x21 / rlaeng;
c[2] = y21 / rlaeng;
c[3] = z21 / rlaeng;
slaeng = FR_SQRT (c[1]*c[1] + c[2]*c[2]);
c[4] = 0.;
c[5] = 1.;
c[6] = 0.;
      
if (FR_FABS(slaeng) > 1.e-12)
  {
  c[4] = -c[2] / slaeng;
  c[5] =  c[1] / slaeng;
  }
  
c[7] = -c[3] * c[5];
c[8] =  c[3] * c[4];
c[9] =  c[1] * c[5] - c[2] * c[4];

/***********************************************************************
* Hilfsfaktoren bestimmen
***********************************************************************/
fakzs = emode * qparae / rlaeng;
fakts = emode * rite / (2. *(1. + rnuee) * rlaeng);

fakb1s= emode * riyye * 2. / FR_POW(rlaeng,3.);
fakb2s= emode * rizze * 2. / FR_POW(rlaeng,3.);

/***********************************************************************
* Elementsteifigkeitsmatrix se bestimmen
***********************************************************************/
for(ih = 1;ih <= 2;ih++)
  {
  for(jh = 1;jh <= 2;jh++)
    {
    i= 6 * ih - 5;
    j= 6 * jh - 5;
    se[i+n*(j-1)]   = isl[(ih-1)*2 +jh] * fakzs;
    se[i+3+n*(j+2)] = isl[(ih-1)*2 +jh] * fakts;

    i1 = 2 * ih - 1;
    j1 = 2 * jh - 1;
    se[i+2+n*(j+1)]=  isk[(i1-1)*4 + j1  ] * fakb1s;
    se[i+2+n*(j+3)]= -isk[(i1-1)*4 + j1+1] * fakb1s * rlaeng;
    se[i+4+n*(j+1)]= -isk[(i1  )*4 + j1  ] * fakb1s * rlaeng;
    se[i+4+n*(j+3)]=  isk[(i1  )*4 + j1+1] * fakb1s * rlaeng*rlaeng;
    se[i+1+n*j    ]=  isk[(i1-1)*4 + j1  ] * fakb2s;
    se[i+1+n*(j+4)]=  isk[(i1-1)*4 + j1+1] * fakb2s * rlaeng;
    se[i+5+n*j    ]=  isk[(i1  )*4 + j1  ] * fakb2s * rlaeng;
    se[i+5+n*(j+4)]=  isk[(i1  )*4 + j1+1] * fakb2s * rlaeng*rlaeng;
    }
  }

for(ih = 1;ih <= 2;ih++)
  {                                                        /* 150 */
  for(jh = 1;jh <= 2;jh++)
    {                                                      /* 140 */
    id= 6 * ih - 5;
    jd= 6 * jh - 5;
    icase = 0;                                             /* false */      

L50:;
    for(i = 1;i <= 3;i++)
      s[i]= se[id+i-1 + n*(jd+i-2) ];

    for(i = 1;i <= 3;i++)
      {                                                    /* 90 */
      for(j = 1;j <= 3;j++)
        {                                                  /* 80 */
        ss= 0.;
        for(k = 1;k <= 3;k++)
          {                                                /* 70 */
          ss+= c[(k-1)*3 + i] * c[(k-1)*3 + j] * s[k];
          }                                                /* e70 */
        se[id+i-1 + n*(jd+j-2) ]= ss;
        }                                                  /* e80 */
      }                                                    /* e90 */

    if(icase == 1) goto L100;
    id+= 3;
    jd+= 3;
    icase= 1;                                              /* true */
    goto L50;

L100:;
    id-= 3;
    icase= 0;

L110:;
    s32= se[id+2+n*jd];
    s23= se[id+1+n*(jd+1)];

    for(i = 1;i <= 3;i++)
      {                                                    /* 130 */
      ii= id + i - 1;
      for(j = 1;j <= 3;j++)
        {                                                  /* 120 */
        jj= jd + j - 1;
        se[ii+n*(jj-1)]= 
        c[6 + i] * c[3 + j] * s32 + c[3 + i] * c[6 + j] * s23;
        }                                                  /* e120 */
      }                                                    /* e130 */

    if(icase == 1) goto L140;
    id+= 3;
    jd-= 3;
    icase= 1;
    goto L110;

L140:;
    }                                                      /* e140 */
  }                                                        /* e150 */

return(0);
}

/***********************************************************************
* hier beginnt Function ebal88
***********************************************************************/
int ebal88(void)
{
extern FR_DOUBLEAY se;

extern FR_DOUBLE xk[],yk[];

extern FR_DOUBLE emode,qparae,rizze;
        
FR_DOUBLE x21,y21,rlaeng,feil,fali,sa,ca;
        
FR_INT4 n,i,j;

n= 6;
        
/***********************************************************************
* Laenge im Raum durch Pythagoras bestimmen
***********************************************************************/
x21 = xk[2] - xk[1];
y21 = yk[2] - yk[1];
rlaeng = FR_SQRT (x21*x21 + y21*y21);

/***********************************************************************
* Richtung- Sinus & Cosinus bestimmen
***********************************************************************/
ca= x21 / rlaeng;
sa= y21 / rlaeng;

/***********************************************************************
* Hilfsfaktoren bestimmen
***********************************************************************/
feil= emode * rizze / FR_POW(rlaeng,3.);
fali= qparae * rlaeng * rlaeng / rizze; 

/***********************************************************************
* Elementsteifigkeitsmatrix se bestimmen
***********************************************************************/
/*----------------------------------------------------------------------
* oberes Dreieck erzeugen
*---------------------------------------------------------------------*/
se[1] = feil * (fali * ca * ca + 12. * sa * sa);
se[7] = feil * (fali - 12.) * sa * ca;
se[8] = feil * (fali * sa * sa + 12. * ca * ca);
se[13]= feil * (-6.) * rlaeng * sa;
se[14]= feil *  6. * rlaeng * ca;
se[15]= feil * 4. * rlaeng * rlaeng;
se[19]= -se[1];
se[20]= -se[7];        
se[21]= -se[13];        
se[22]=  se[1];        
se[25]= -se[7];        
se[26]= -se[8];        
se[27]= -se[14];        
se[28]=  se[7];        
se[29]=  se[8];        
se[31]=  se[13];        
se[32]=  se[14];        
se[33]=  feil * 2. * rlaeng * rlaeng;        
se[34]= -se[13];
se[35]= -se[14];        
se[36]=  se[15];        

/*----------------------------------------------------------------------
* unteres Dreieck erzeugen
*---------------------------------------------------------------------*/
for(j = 1;j <= 6;j++)
  {
  for(i = j;i <= 6;i++)
    {
    se[i+n*(j-1)]= se[j+n*(i-1)];
    }
  }

return(0);
}
