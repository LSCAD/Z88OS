/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows & 
* the UNIX OS.
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
* diese Compilerunit umfasst: sshf88 - Elementsteifigkeitsroutine
* ruft:                       ibs88  - Berechnung Matrix b - Schale
* ruft:                       sss88  - Berechnung Matrix b - Platte
* 24.5.2012 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>    /* fprintf */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <stdio.h>    /* fprintf */
#endif

/***********************************************************************
* Fuer Windows und GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88r.h>
#include <stdio.h>    /* fprintf */
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
int ibs88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s,
         FR_DOUBLE *xbar,FR_INT4 *ktyp);
int sss88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s);
FR_DOUBLE platgh(FR_DOUBLE sig[]);
FR_DOUBLE platnh(FR_DOUBLE sig[]);
FR_DOUBLE platsh(FR_DOUBLE sig[]);

/***********************************************************************
* hier beginnt Function sshf88
***********************************************************************/
int sshf88(void)
{
extern FILE *fo3,*fo5;

extern FR_DOUBLEAY smw;
extern FR_DOUBLEAY gmw;
extern FR_DOUBLEAY sigvku;
extern FR_DOUBLEAY tm;
extern FR_DOUBLEAY tmt;

extern FR_INT4AY jsm;
extern FR_INT4AY koi;
extern FR_INT4AY koffs;

extern FR_DOUBLE ul[];
extern FR_DOUBLE h[];
extern FR_DOUBLE xk[],yk[],zk[];
extern FR_DOUBLE b[],xx[],ds[],dp[];
extern FR_DOUBLE xc[],yc[],zc[];

extern FR_DOUBLE emode,rnuee,qparae;

extern FR_INT4 ktyp,ninto,kflag,isflag,kc,jpri,ifnili,ngau,ihflag;

FR_DOUBLE ulc[37],uls[13],ulp[19];
FR_DOUBLE a21x,a21y,a21z,rl21,a31x,a31y,a31z;
FR_DOUBLE azsx,azsy,azsz,rlzs,aysx,aysy,aysz,rlys;
FR_DOUBLE vxx,vxy,vxz,vyx,vyy,vyz,vzx,vzy,vzz;

FR_DOUBLE sigs[6],sigp[6],rsig[6];
FR_DOUBLE eps[6],sig[7],rv[4];

FR_DOUBLE facesz,facasz,facbi,facsv,rmok,skf,fque,fmom;
FR_DOUBLE r,s,xs,ys,zs,xsc,ysc,zsc,det,xbar,sum;
FR_DOUBLE sigv,ax,ay,az,rmin;

FR_INT4 jp[4];

FR_INT4 i,lx,j,k,jk,inc,jnc;

int iret;
  
/*----------------------------------------------------------------------
* Gauss-Legendre Stuetzstellen fuer r
*---------------------------------------------------------------------*/
static FR_DOUBLE rg[40]= 
{ 
0.,0.,0.,0.,0.,0.,0.,   /* Elemente 0 - 6 leer              */
0.1666666666667,        /* intore = 3, 1.Ele Start bei i=7  */
0.6666666666667,
0.1666666666667,
0.,0.,0.,0.,0.,         /* Elemente 10-14 leer              */
0.1012865073235,        /* intore = 7, 1.Ele Start bei i=15 */  
0.7974269853531,
0.1012865073235,
0.4701420641051,
0.4701420641051,
0.0597158717898,
0.3333333333333,
0.,0.,0.,0.,0.,         /* Elemente 22-26 leer              */
0.0651301029022,        /* intore =13, 1.Ele Start bei i=27 */
0.8697397941956,
0.0651301029022,
0.3128654960049,
0.6384441885698,
0.0486903154253,
0.6384441885698,
0.3128654960049,
0.0486903154253,
0.2603459660790,
0.4793080678419,
0.2603459660790,
0.3333333333333
};

/*----------------------------------------------------------------------
* Gauss-Legendre Stuetzstellen fuer s
*---------------------------------------------------------------------*/
static FR_DOUBLE sg[40]= 
{ 
0.,0.,0.,0.,0.,0.,0.,   /* Elemente 0 - 6 leer              */
0.1666666666667,        /* intore = 3, 1.Ele Start bei i=7  */
0.1666666666667,
0.6666666666667,
0.,0.,0.,0.,0.,         /* Elemente 10-14 leer              */
0.1012865073235,        /* intore = 7, 1.Ele Start bei i=15 */
0.1012865073235,
0.7974269853531,
0.0597158717898,
0.4701420641051,
0.4701420641051,
0.3333333333333,
0.,0.,0.,0.,0.,         /* Elemente 22-26 leer              */
0.0651301029022,        /* intore =13, 1.Ele Start bei i=27 */
0.0651301029022,
0.8697397941956,
0.0486903154253,
0.3128654960049,
0.6384441885698,
0.0486903154253,
0.6384441885698,
0.3128654960049,
0.2603459660790,
0.2603459660790,
0.4793080678419,
0.3333333333333
};

/*----------------------------------------------------------------------
* Gauss-Legendre Stuetzstellen, fix fuer 3 Punkte
*---------------------------------------------------------------------*/
static FR_DOUBLE xgo[4]= { 0.,
0.1666666666667,
0.6666666666667,
0.1666666666667};

static FR_DOUBLE ygo[4]= { 0.,
0.1666666666667,
0.1666666666667,
0.6666666666667};

/*----------------------------------------------------------------------
* Natuerliche Koordinaten der Eckknoten
*---------------------------------------------------------------------*/
static FR_DOUBLE rkr[4]= { 0.,
                        0., 1., 0. };
static FR_DOUBLE rks[4]= { 0.,
                        0., 0., 1. };

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
  zk[i]= vzx*xc[i] + vzy*yc[i] + vzz*zc[i];
  }

/*----------------------------------------------------------------------
* xk und yk auf xx umspeichern, zk fuer die spaetere Ruecktransforma.
*---------------------------------------------------------------------*/
for(i = 1;i <= 6;i++)
  {
  xx[   i]= xk[i];
  xx[ 6+i]= yk[i];
  xx[12+i]= zk[i];
  }

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
* die globalen Verschiebungen zwischensichern
*---------------------------------------------------------------------*/
for(i = 1; i <= 36; i++)
  ulc[i]= ul[i];

/*----------------------------------------------------------------------
* Matrix-Vektorprodukt: tm * ulc(global) = ul(lokal)
*---------------------------------------------------------------------*/
for(i = 1;i <= 36;i++)
  {
  sum= 0.;
  for(k = 1; k <= 36; k++)
    {
    sum+= tm[(i-1)*36+k] * ulc[k];
    }
  ul[i]= sum; /* ul ist jetzt lokal */
  }

/*----------------------------------------------------------------------
* der Scheibenanteil von ul(lokal)
*---------------------------------------------------------------------*/
inc= 1;
jnc= 1;
for(i = 1;i <= 6;i++)
  {
  uls[jnc  ]= ul[inc  ];
  uls[jnc+1]= ul[inc+1];
  jnc+=2;
  inc+=6;
  }

/*----------------------------------------------------------------------
* der Plattenanteil von ul(lokal)
*---------------------------------------------------------------------*/
inc= 3;
jnc= 1;
for(i = 1;i <= 6;i++)
  {
  ulp[jnc  ]= ul[inc  ];
  ulp[jnc+1]= ul[inc+1];
  ulp[jnc+2]= ul[inc+2];
  jnc+=3;
  inc+=6;
  }
  
/*----------------------------------------------------------------------
* Scheibe: Materialmatrix aufstellen
*---------------------------------------------------------------------*/
for(i = 1;i <= 36;i++)
  ds[i]= 0.;

ktyp= 2;

facesz= emode/(1. - rnuee*rnuee);
facasz= emode*(1. - rnuee)/( (1. + rnuee)*(1. - 2*rnuee) );
        
ds[1] = facesz;
ds[5] = facesz * rnuee;
ds[9] = 0.;
ds[2] = ds[5];
ds[6] = facesz;
ds[10]= 0.;
ds[3] = 0.;
ds[7] = 0.;
ds[11]= facesz * .5 * (1. - rnuee);

/*----------------------------------------------------------------------
* Platte: Materialmatrix aufstellen
*---------------------------------------------------------------------*/
for(i = 1;i <= 36;i++)
  dp[i]= 0.;

facbi = emode*qparae*qparae*qparae/(12.*(1. - rnuee*rnuee));

dp[1] = facbi;
dp[2] = facbi * rnuee;

dp[6] = dp[2];
dp[7] = dp[1];

dp[13]= facbi * .5 * (1. - rnuee);
        
if     (ihflag == 1)  rmok= 1.;     /* Reissner- Mindlin */
else if(ihflag == 2)  rmok= 0.01;   /* Schubeinfluss daempfen */
else                  rmok= 1.;     /* Default */

skf= 5./6.;                         /* Schubkorrekturfaktor */

facsv= rmok*emode*skf*qparae/(2*(1. + rnuee));

dp[19]= facsv;
dp[25]= facsv;
        
/*----------------------------------------------------------------------
* Spannungen in den Gauss-Punkten berechnen
*---------------------------------------------------------------------*/
if(ninto > 0)
  {

/*======================================================================
* ninto > 0: Spannungen in den Gauss-Punkten berechnen, variabel
*=====================================================================*/
  for(lx = 1;lx <= ninto;lx++)
    {
    r= rg[lx+2*ninto];
    s= sg[lx+2*ninto];
      
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Scheibe: Matrix b & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    iret= ibs88(&det,&r,&s,&xbar,&ktyp);
    if(iret != 0) return(iret);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Scheibe: Verzerrungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 3;k++)
      {
      eps[k]= 0.;
      for(j = 1;j <= 12;j++)
        {
        eps[k]+= b[(k-1)*12 + j] * uls[j];
        }
      }
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Scheibe: Spannungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 3;k++)
      {
      sigs[k]= 0.;
      for(j = 1;j <= 3;j++)
        {
        sigs[k]+= ds[(k-1)*4 + j] * eps[j];
        }
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Platte: Matrix b & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    iret= sss88(&det,&r,&s);
    if(iret != 0) return(iret);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Platte: Verzerrungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 5;k++)
      {
      eps[k]= 0.;
      for(j = 1;j <= 18;j++)
        { 
        eps[k]+= b[(k-1)*18 + j] * ulp[j];
        }
      }
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Platte: Spannungen berechnen: Biegemomente und Querkraefte
* pro Laenge
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 5;k++)
      {
      sigp[k]= 0.;
      for(j = 1;j <= 5;j++)
        {
        sigp[k]+= dp[(k-1)*5 + j] * eps[j];
        }
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Platte: echte Spannungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    fmom= 12.*(qparae/2.)/(qparae*qparae*qparae);

    for(k = 1;k <= 3;k++)
      rsig[k]= sigp[k]*fmom;

    fque= 3./2. /qparae;

    for(k = 4;k <= 5;k++)
      rsig[k]= sigp[k]*fque;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Schale: aus Scheibe und Platte die Spannungen zusammenbauen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    sig[1]= sigs[1]+rsig[1];   /* SIGXX */
    sig[2]= sigs[2]+rsig[2];   /* SIGYY */
    sig[3]= sigs[3]+rsig[3];   /* TAUXY */
    sig[4]= 0;                 /* TAUXZ,d.h. rsig[4],vernachlaessigen */
    sig[5]= 0;                 /* TAUYZ,d.h. rsig[5],vernachlaessigen */
    sig[6]= 0.;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Schale: Integrationspunkte in echte Koordinaten umrechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    xsc= 0.;
    ysc= 0.;
    zsc= 0.;
 
    /* von r,t auf lokal */
    for(j = 1;j <= 6;j++)
      {
      xsc+= h[j] * xx[   j];
      ysc+= h[j] * xx[6 +j];
      zsc+= h[j] * xx[12+j];
      }

    /* von lokal auf global */
    xs= tmt[ 1]*xsc + tmt[ 2]*ysc + tmt[ 3]*zsc;
    ys= tmt[37]*xsc + tmt[38]*ysc + tmt[39]*zsc;
    zs= tmt[73]*xsc + tmt[74]*ysc + tmt[75]*zsc;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Schale: Spannungen ausschreiben
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(isflag == 0)                                   /* keine VglSpa.*/ 
      {
      if(ifnili == 0)
        {
        fprintf(fo3,NL P10E P10E P10E P11E P11E P11E 
        ,xs,ys,zs,sig[1],sig[2],sig[3]);
        } 
      }                                             /* e if ohne VglS */

    if(isflag == 1 || isflag == 2 || isflag == 3)      /* GEH,NH,SH */
      {
      if(isflag == 1) sigv= platgh(sig);
      if(isflag == 2) sigv= platnh(sig);
      if(isflag == 3) sigv= platsh(sig);

      ngau++;
      sigvku[ngau]+= sigv;

      if(ifnili == 0)
        {
        fprintf(fo3,NL P10E P10E P10E P11E P11E P11E P10E
        ,xs,ys,zs,sig[1],sig[2],sig[3],sigv); 
        } 
    
      if(jpri == 1)
        {
        fprintf(fo5,NL P11E P11E P11E P11E,xs,ys,zs,sigvku[ngau]);
        }
      gmw[kc]+= sigv; 
      }                                                /* e if mit GEH */
    }                                                    /* e for */
  gmw[kc]/= ninto;  /* Mittelwert berechnen */

/*======================================================================
* ninto > 0: die Eckpunkte berechnen
*=====================================================================*/
  for(lx = 1;lx <= 3;lx++)
    {
    r= rkr[lx];
    s= rks[lx];

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Matrix b der partiellen Ableitungen & Formfunktionen holen:
* egal, ob * Scheiben- oder Plattenformfunktionen ibs88 bzw. sss88 
* (identisch, * b nicht!), weil nur h[] gebraucht wird.
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    iret= ibs88(&det,&r,&s,&xbar,&ktyp);
    if(iret != 0) return(iret);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Schale: Eckpunkte in echte Koordinaten umrechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    xsc= 0.;
    ysc= 0.;
    zsc= 0.;
 
    /* von r,t auf lokal */
    for(j = 1;j <= 6;j++)
      {
      xsc+= h[j] * xx[   j];
      ysc+= h[j] * xx[6 +j];
      zsc+= h[j] * xx[12+j];
      }

    /* von lokal auf global */
    xs= tmt[ 1]*xsc + tmt[ 2]*ysc + tmt[ 3]*zsc;
    ys= tmt[37]*xsc + tmt[38]*ysc + tmt[39]*zsc;
    zs= tmt[73]*xsc + tmt[74]*ysc + tmt[75]*zsc;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: welcher Knoten ist's wirklich?
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(j = 1;j <= 3;j++)
      {
      ax   = xc[j] - xs;
      ay   = yc[j] - ys;
      az   = zc[j] - zs;
      rv[j]= FR_SQRT(ax*ax + ay*ay + az*az);
      }

    rmin= 1e88;
    for(j = 1;j <= 3;j++)
      {
      if(rv[j] < rmin) 
        {
        rmin= rv[j];
        jk= j;     
        }
      }

    jp[lx]= jk;
    }

/*======================================================================
* ninto > 0: Spannungen in den Gauss-Punkten berechnen, fix fuer Z88O
*=====================================================================*/
  for(lx = 1;lx <= 3;lx++) 
    {
    r= xgo[lx];
    s= ygo[lx];

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Scheibe: Matrix b & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    iret= ibs88(&det,&r,&s,&xbar,&ktyp);
    if(iret != 0) return(iret);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Scheibe: Verzerrungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 3;k++)
      {
      eps[k]= 0.;
      for(j = 1;j <= 12;j++)
        {
        eps[k]+= b[(k-1)*12 + j] * uls[j];
        }
      }
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Scheibe: Spannungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 3;k++)
      {
      sigs[k]= 0.;
      for(j = 1;j <= 3;j++)
        {
        sigs[k]+= ds[(k-1)*4 + j] * eps[j];
        }
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Platte: Matrix b & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    iret= sss88(&det,&r,&s);
    if(iret != 0) return(iret);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Platte: Verzerrungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 5;k++)
      {
      eps[k]= 0.;
      for(j = 1;j <= 18;j++)
        { 
        eps[k]+= b[(k-1)*18 + j] * ulp[j];
        }
      }
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Platte: Spannungen berechnen: Biegemomente und Querkraefte
* pro Laenge
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 5;k++)
      {
      sigp[k]= 0.;
      for(j = 1;j <= 5;j++)
        {
        sigp[k]+= dp[(k-1)*5 + j] * eps[j];
        }
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Platte: echte Spannungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    fmom= 12.*(qparae/2.)/(qparae*qparae*qparae);

    for(k = 1;k <= 3;k++)
      rsig[k]= sigp[k]*fmom;

    fque= 3./2. /qparae;

    for(k = 4;k <= 5;k++)
      rsig[k]= sigp[k]*fque;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Schale: aus Scheibe und Platte die Spannungen zusammenbauen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    sig[1]= sigs[1]+rsig[1];   /* SIGXX */
    sig[2]= sigs[2]+rsig[2];   /* SIGYY */
    sig[3]= sigs[3]+rsig[3];   /* TAUXY */
    sig[4]= 0;                 /* TAUXZ, ansich rsig[4] */
    sig[5]= 0;                 /* TAUYZ, ansich rsig[5] */
    sig[6]= 0.;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto > 0: Schale: Vergleichsspannungen aufaddieren
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(isflag == 1) sigv= platgh(sig);
    if(isflag == 2) sigv= platnh(sig);
    if(isflag == 3) sigv= platsh(sig);

    smw[koi[koffs[kc]+jp[lx]-1]]+= sigv;
    jsm[koi[koffs[kc]+jp[lx]-1]]++;
    } /* Ende Z88O */
  }   /* Ende Gausspunkte variabel, d.h. ninto > 0 */  

/*----------------------------------------------------------------------
* ninto = 0: Spannungen in den Eckknoten berechnen
*---------------------------------------------------------------------*/
if(ninto == 0)
  {
  for(lx = 1;lx <= 3;lx++)
    {
    r= rkr[lx];
    s= rks[lx];
      
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto = 0: Scheibe: Matrix b & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    iret= ibs88(&det,&r,&s,&xbar,&ktyp);
    if(iret != 0) return(iret);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto = 0: Scheibe: Verzerrungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 3;k++)
      {
      eps[k]= 0.;
      for(j = 1;j <= 12;j++)
        {
        eps[k]+= b[(k-1)*12 + j] * uls[j];
        }
      }
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto = 0: Scheibe: Spannungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 3;k++)
      {
      sigs[k]= 0.;
      for(j = 1;j <= 3;j++)
        {
        sigs[k]+= ds[(k-1)*4 + j] * eps[j];
        }
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto = 0: Platte: Matrix b & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    iret= sss88(&det,&r,&s);
    if(iret != 0) return(iret);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto = 0: Platte: Verzerrungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 5;k++)
      {
      eps[k]= 0.;
      for(j = 1;j <= 18;j++)
        { 
        eps[k]+= b[(k-1)*18 + j] * ulp[j];
        }
      }
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto = 0: Platte: Spannungen berechnen: Biegemomente und Querkraefte
* pro Laenge
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 5;k++)
      {
      sigp[k]= 0.;
      for(j = 1;j <= 5;j++)
        {
        sigp[k]+= dp[(k-1)*5 + j] * eps[j];
        }
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Platte: echte Spannungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    fmom= 12.*(qparae/2.)/(qparae*qparae*qparae);

    for(k = 1;k <= 3;k++)
      rsig[k]= sigp[k]*fmom;

    fque= 3./2. /qparae;

    for(k = 4;k <= 5;k++)
      rsig[k]= sigp[k]*fque;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* aus Scheibe und Platte die Spannungen zusammenbauen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    sig[1]= sigs[1]+rsig[1];   /* SIGXX */
    sig[2]= sigs[2]+rsig[2];   /* SIGYY */
    sig[3]= sigs[3]+rsig[3];   /* TAUXY */
    sig[4]= 0;                 /* TAUXZ,d.h. rsig[4],vernachlaessigen */
    sig[5]= 0;                 /* TAUYZ,d.h. rsig[5],vernachlaessigen */
    sig[6]= 0.;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto = 0: Schale: Eckpunkte in echte Koordinaten umrechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    xsc= 0.;
    ysc= 0.;
    zsc= 0.;
 
    /* von r,t auf lokal */
    for(j = 1;j <= 6;j++)
      {
      xsc+= h[j] * xx[   j];
      ysc+= h[j] * xx[6 +j];
      zsc+= h[j] * xx[12+j];
      }

    /* von lokal auf global */
    xs= tmt[ 1]*xsc + tmt[ 2]*ysc + tmt[ 3]*zsc;
    ys= tmt[37]*xsc + tmt[38]*ysc + tmt[39]*zsc;
    zs= tmt[73]*xsc + tmt[74]*ysc + tmt[75]*zsc;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ninto = 0: Schale: Spannungen ausschreiben
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(ifnili == 0)
      {
      fprintf(fo3,NL P10E P10E P10E P11E P11E P11E
      ,xs,ys,zs,sig[1],sig[2],sig[3]);
      }
    }
  }  /* Ende ninto = 0 */

return(0);
}


