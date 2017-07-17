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
* Z88 should compile and run under any UNIX OS and Windows & GTK+.
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
* diese Compilerunit umfasst: siso88 - Elementsteifigkeitsroutine
*                             ibs88   - Berechnung der Matrix b
* 2.1.2010 Rieg
* 6.2.2011 Rieg - Fehler bei sigr beseitigt (kdflag statt kflag)
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
int ibs88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s,
         FR_DOUBLE *xbar,FR_INT4 *ktyp);
FR_DOUBLE torgh(FR_DOUBLE sig[]);
FR_DOUBLE sheigh(FR_DOUBLE sig[]);
FR_DOUBLE tornh(FR_DOUBLE sig[]);
FR_DOUBLE sheinh(FR_DOUBLE sig[]);
FR_DOUBLE torsh(FR_DOUBLE sig[]);
FR_DOUBLE sheish(FR_DOUBLE sig[]);

/***********************************************************************
* hier beginnt Function siso88
***********************************************************************/
int siso88(void)
{
extern FILE *fo3,*fo5;

extern FR_DOUBLEAY smw;
extern FR_DOUBLEAY gmw;
extern FR_DOUBLEAY sigvku;

extern FR_INT4AY jsm;
extern FR_INT4AY koi;
extern FR_INT4AY koffs;

extern FR_DOUBLE ul[];
extern FR_DOUBLE h[];
extern FR_DOUBLE xk[],yk[];
extern FR_DOUBLE b[],xx[],d[];

extern FR_DOUBLE emode,rnuee,qparae;

extern FR_INT4 ktyp,ninto,kdflag,isflag,kc,jpri,ifnili,ngau;

FR_DOUBLE eps[5],sig[5],rv[4];

FR_DOUBLE facesz,facasz,r,s,xs,ys,det,xbar;
FR_DOUBLE rr,phirad,phideg,sinphi,cosphi;
FR_DOUBLE qsin,qcos,sincos,sigr,sigt,taurt,sigv,ax,ay,rmin;

FR_INT4 jp[4];

FR_INT4 i,ist,lx,j,k,jk;

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
* ninto anpassen, damit Mischen mit sqsh88 via z88g moeglich ist
*---------------------------------------------------------------------*/
if(ninto == 1 || ninto == 2) ninto = 3;
if(ninto == 4)               ninto = 7;

/*----------------------------------------------------------------------
* xk und yk umspeichern
*---------------------------------------------------------------------*/
for(i = 1;i <= 6;i++)
  {
  xx[i]  = xk[i];
  xx[6+i]= yk[i];
  }

/*----------------------------------------------------------------------
* Materialkonstanten
*---------------------------------------------------------------------*/
facesz= emode/(1. - rnuee*rnuee);
facasz= emode*(1. - rnuee)/( (1. + rnuee)*(1. - 2*rnuee) );
        
/*----------------------------------------------------------------------
* Elastizitaetsmatrix aufstellen: ebener Spannungszustand
*---------------------------------------------------------------------*/
if (ktyp == 2)
  {
  d[1] = facesz;
  d[5] = facesz * rnuee;
  d[9] = 0.;
  d[2] = d[5];
  d[6] = facesz;
  d[10]= 0.;
  d[3] = 0.;
  d[7] = 0.;
  d[11]= facesz * .5 * (1. - rnuee);
  }
        
/*----------------------------------------------------------------------
* Elastizitaetsmatrix aufstellen: ebener Verzerrungszustand
*---------------------------------------------------------------------*/
if (ktyp == 1)
  {
  d[1] = facasz;
  d[5] = facasz * rnuee / (1. - rnuee);
  d[9] = 0.;
  d[2] = d[5];
  d[6] = facasz;
  d[10]= 0.;
  d[3] = 0.;
  d[7] = 0.;
  d[11]= emode / (2.*(1. + rnuee));
  qparae= 1.;
  }

/*----------------------------------------------------------------------
* Elastizitaetsmatrix aufstellen: axialsymmetrischer Spannungszustand
*---------------------------------------------------------------------*/
if (ktyp == 0)
  {
  d[1] = facasz;
  d[5] = facasz * rnuee / (1. - rnuee);
  d[9] = 0.;
  d[13]= d[5];
  d[2] = d[5];
  d[6] = facasz;
  d[10]= 0.;
  d[14]= d[5];
  d[3] = 0.;
  d[7] = 0.;
  d[11]= emode / (2.*(1. + rnuee));
  d[15]= 0.;
  d[4]= d[5];
  d[8]= d[5];
  d[12]= 0.;
  d[16]= facasz;
  }

/*----------------------------------------------------------------------
* Spannungen in den Gauss-Punkten berechnen
*---------------------------------------------------------------------*/
ist= 3; 
if(ktyp == 0) ist= 4;

if(ninto > 0)
  {

/*======================================================================
* Spannungen in den Gauss-Punkten berechnen, variabel
*=====================================================================*/
  for(lx = 1;lx <= ninto;lx++)
    {
    r= rg[lx+2*ninto];
    s= sg[lx+2*ninto];
      
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    iret= ibs88(&det,&r,&s,&xbar,&ktyp);
    if(iret != 0) return(iret);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verzerrungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= ist;k++)
      {
      eps[k]= 0.;
      for(j = 1;j <= 12;j++)
        {
        eps[k]= eps[k] + b[(k-1)*12 + j] * ul[j];
        }
      }
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Spannungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= ist;k++)
      {
      sig[k]= 0.;
      for(j = 1;j <= ist;j++)
        {
        sig[k]= sig[k] + d[(k-1)*4 + j] * eps[j];
        }
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Integrationspunkte in echte Koordinaten umrechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    xs= 0.;
    ys= 0.;
 
    for(j = 1;j <= 6;j++)
      {
      xs+= h[j] * xx[   j];
      ys+= h[j] * xx[6 +j];
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Spannungen ausschreiben
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/* Torus */
    if(ktyp == 0)
      {
      if(isflag == 0 && ifnili == 0) 
        {
        fprintf(fo3,NL P10E P10E P11E P11E P11E P11E
        ,xs,ys,sig[1],sig[2],sig[3],sig[4]);
        }

      if(isflag == 1 || isflag == 2 || isflag == 3) 
        {
        if(isflag == 1) sigv= torgh(sig);
        if(isflag == 2) sigv= tornh(sig);
        if(isflag == 3) sigv= torsh(sig);

        ngau++;
        sigvku[ngau]+= sigv;

        if(ifnili == 0)
          {
          fprintf(fo3,NL P10E P10E P11E P11E P11E P11E P11E
          ,xs,ys,sig[1],sig[2],sig[3],sig[4],sigv);
          }
        if(jpri == 1)
          {
          fprintf(fo5,NL P11E P11E P11E,xs,ys,sigvku[ngau]);
          }
        gmw[kc]+= sigv; 
        }
      }                                                  /* e if torus */

/* Scheibe */
    if(ktyp == 2)
      {
      if(isflag == 0)                                    /* keine VglSpa.*/ 
        {
        if(kdflag == 1)                                   /* zus. sigr */
          {
          rr= FR_SQRT(xs*xs + ys*ys);
          if(xs == 0.) xs= 1.e-10;
          phirad= FR_ATAN(ys/xs);
          phideg= phirad*57.29578;

          sinphi= FR_SIN(phirad);
          cosphi= FR_COS(phirad);
          qsin= sinphi*sinphi;
          qcos= cosphi*cosphi;
          sincos= sinphi*cosphi;

          sigr= sig[1]*qcos + sig[2]*qsin + 2.*sig[3]*sincos;
          sigt= sig[1]*qsin + sig[2]*qcos - 2.*sig[3]*sincos;
          taurt=(sig[2]-sig[1])*sincos + sig[3]*(qcos-qsin);

          if(ifnili == 0)
            {
            fprintf(fo3,NL P10E P10E P11E P11E P11E P10E P10E P11E P11E P11E
            ,xs,ys,sig[1],sig[2],sig[3],rr,phideg,sigr,sigt,taurt);
            }
          }                                              /* e if zus. sigr */
        else
          {                                              /* ohne sigr */
          if(ifnili == 0)
            {
            fprintf(fo3,NL P10E P10E P11E P11E P11E
            ,xs,ys,sig[1],sig[2],sig[3]);
            } 
          }                                              /* e if ohne sigr */
        }                                                /* e if ohne VglS */

      if(isflag == 1 || isflag == 2 || isflag == 3)      /* GEH,NH,SH */
        {
        if(isflag == 1) sigv= sheigh(sig);
        if(isflag == 2) sigv= sheinh(sig);
        if(isflag == 3) sigv= sheish(sig);

        ngau++;
        sigvku[ngau]+= sigv;

        if(kdflag == 1)                                   /* zus. sigr */
          {
          rr= FR_SQRT(xs*xs + ys*ys);
          if(xs == 0.) xs= 1.e-10;
          phirad= FR_ATAN(ys/xs);
          phideg= phirad*57.29578;

          sinphi= FR_SIN(phirad);
          cosphi= FR_COS(phirad);
          qsin= sinphi*sinphi;
          qcos= cosphi*cosphi;
          sincos= sinphi*cosphi;

          sigr= sig[1]*qcos + sig[2]*qsin + 2.*sig[3]*sincos;
          sigt= sig[1]*qsin + sig[2]*qcos - 2.*sig[3]*sincos;
          taurt=(sig[2]-sig[1])*sincos + sig[3]*(qcos-qsin);

          if(ifnili == 0)
            {
            fprintf(fo3,NL P10E P10E P11E P11E P11E P10E P10E P11E P11E P11E P11E
            ,xs,ys,sig[1],sig[2],sig[3],rr,phideg,sigr,sigt,taurt,sigv);
            }
          }                                              /* e if zus. sigr */
        else
          {                                              /* ohne sigr */
          if(ifnili == 0)
            {
            fprintf(fo3,NL P10E P10E P11E P11E P11E P10E
            ,xs,ys,sig[1],sig[2],sig[3],sigv); 
            } 
          }                                              /* e if ohne sigr */
        if(jpri == 1)
          {
          fprintf(fo5,NL P11E P11E P11E,xs,ys,sigvku[ngau]);
          }
        gmw[kc]+= sigv; 
        }                                                /* e if mit GEH */
      }                                                  /* e if scheibe */
    }                                                    /* e for */
  gmw[kc]/= ninto;  /* Mittelwert berechnen */

/*======================================================================
* die Eckpunkte berechnen
*=====================================================================*/
  for(lx = 1;lx <= 3;lx++)
    {
    r= rkr[lx];
    s= rks[lx];

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    iret= ibs88(&det,&r,&s,&xbar,&ktyp);
    if(iret != 0) return(iret);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Eckpunkte in echte Koordinaten umrechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    xs= 0.;
    ys= 0.;
 
    for(j = 1;j <= 6;j++)
      {
      xs+= h[j] * xx[   j];
      ys+= h[j] * xx[6 +j];
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* welcher Knoten ist's wirklich?
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(j = 1;j <= 3;j++)
      {
      ax   = xk[j] - xs;
      ay   = yk[j] - ys;
      rv[j]= FR_SQRT(ax*ax + ay*ay);
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
* Spannungen in den Gauss-Punkten berechnen, fix fuer Z88O
*=====================================================================*/
  for(lx = 1;lx <= 3;lx++) 
    {
    r= xgo[lx];
    s= ygo[lx];

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    iret= ibs88(&det,&r,&s,&xbar,&ktyp);
    if(iret != 0) return(iret);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verzerrungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= ist;k++)
      {
      eps[k]= 0.;
      for(j = 1;j <= 12;j++)
        {
        eps[k]= eps[k] + b[(k-1)*12 + j] * ul[j];
        }
      }
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Spannungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= ist;k++)
      {
      sig[k]= 0.;
      for(j = 1;j <= ist;j++)
        {
        sig[k]= sig[k] + d[(k-1)*4 + j] * eps[j];
        }
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Vergleichsspannungen aufaddieren
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if (ktyp == 0 && isflag == 1) sigv= torgh (sig);
    if (ktyp == 2 && isflag == 1) sigv= sheigh(sig);
    if (ktyp == 0 && isflag == 2) sigv= tornh (sig);
    if (ktyp == 2 && isflag == 2) sigv= sheinh(sig);
    if (ktyp == 0 && isflag == 3) sigv= torsh (sig);
    if (ktyp == 2 && isflag == 3) sigv= sheish(sig);

    smw[koi[koffs[kc]+jp[lx]-1]]+= sigv;
    jsm[koi[koffs[kc]+jp[lx]-1]]++;
    } /* Ende Z88O */
  }   /* Ende Gausspunkte variabel */  

/*----------------------------------------------------------------------
* Spannungen in den Eckknoten berechnen
*---------------------------------------------------------------------*/
if(ninto == 0)
  {
  for(lx = 1;lx <= 3;lx++)
    {
    r= rkr[lx];
    s= rks[lx];
      
/*======================================================================
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*=====================================================================*/
    iret= ibs88(&det,&r,&s,&xbar,&ktyp);
    if(iret != 0) return(iret);
    
    for(k = 1;k <= ist;k++)
      {
      eps[k]= 0.;
      for(j = 1;j <= 12;j++)
        {
        eps[k]= eps[k] + b[(k-1)*12 + j] * ul[j];
        }
      }
 
    for(k = 1;k <= ist;k++)
      {
      sig[k]= 0.;
      for(j = 1;j <= ist;j++)
        {
        sig[k]= sig[k] + d[(k-1)*4 + j] * eps[j];
        } 
      }
/*......................................................................
* Eckpunkte in echte Koordinaten umrechnen
*.....................................................................*/
    xs= 0.;
    ys= 0.;
 
    for(j = 1;j <= 6;j++)
      {
      xs+= h[j] * xx[   j];
      ys+= h[j] * xx[6 +j];
      }

/*......................................................................
* Spannungen ausschreiben
*.....................................................................*/
/* Torus */
      if(ktyp == 0 && ifnili == 0)
        {
        fprintf(fo3,NL P10E P10E P11E P11E P11E P11E
        ,xs,ys,sig[1],sig[2],sig[3],sig[4]);
        }                                                  /* e if torus */

/* Scheibe */
      if(ktyp == 2)
        {
        if(kdflag == 1)                                     /* zus. sigr */
          {
          rr= FR_SQRT(xs*xs + ys*ys);
          if(xs == 0.) xs= 1.e-10;
          phirad= FR_ATAN(ys/xs);
          phideg= phirad*57.29578;

          sinphi= FR_SIN(phirad);
          cosphi= FR_COS(phirad);
          qsin= sinphi*sinphi;
          qcos= cosphi*cosphi;
          sincos= sinphi*cosphi;

          sigr= sig[1]*qcos + sig[2]*qsin + 2.*sig[3]*sincos;
          sigt= sig[1]*qsin + sig[2]*qcos - 2.*sig[3]*sincos;
          taurt=(sig[2]-sig[1])*sincos + sig[3]*(qcos-qsin);

          if(ifnili == 0)
            {
            fprintf(fo3,NL P10E P10E P11E P11E P11E P10E P10E P11E P11E P11E
            ,xs,ys,sig[1],sig[2],sig[3],rr,phideg,sigr,sigt,taurt);
            }
          }                                                /* e if zus. sigr */
        else
          {                                                /* ohne sigr */
          if(ifnili == 0)
            {
            fprintf(fo3,NL P10E P10E P11E P11E P11E 
            ,xs,ys,sig[1],sig[2],sig[3]); 
            } 
          }                                                /* e if ohne sigr */
        }                                                  /* e if scheibe */
    }                                                      /* e 140 */
  }                                                        /* e if ninto == 0 */

return(0);
}

/***********************************************************************
* hier beginnt Function ibs88
***********************************************************************/
int ibs88(FR_DOUBLE *det,FR_DOUBLE *r,FR_DOUBLE *s,
         FR_DOUBLE *xbar,FR_INT4 *ktyp)
{
/*---------------------------------------------------------------------
* xx geht rein, unveraendert (ex)
* b  geht raus, neu (ex)
* det geht raus, neu
* r,s gehen rein, unveraendert
* xbar geht raus, neu
* ktyp geht rein, unveraendert
*--------------------------------------------------------------------*/

extern FR_DOUBLE h[];
extern FR_DOUBLE b[],xx[],p[];

FR_DOUBLE xj[5], xji[5];          /* ist 2x2 +1 */

FR_DOUBLE rr2,ss2,r4,r3,s4,s3,rs4,dum;
        
FR_INT4 i,j,k,k2;
         
/*----------------------------------------------------------------------
* Klammern der Formfunktionen belegen
*---------------------------------------------------------------------*/
rr2= 2. * (*r) * (*r);
ss2= 2. * (*s) * (*s);
r4 = 4. * (*r);
r3 = 3. * (*r);
s4 = 4. * (*s);
s3 = 3. * (*s);
rs4= 4. * (*r) * (*s);

/*----------------------------------------------------------------------
* Formfunktionen
*---------------------------------------------------------------------*/
h[1]= rr2 + ss2 + rs4 - r3 - s3 + 1.;
h[2]= rr2 - (*r);
h[3]= ss2 - (*s);
h[4]= r4 - 2*rr2 - rs4;
h[5]= rs4;
h[6]= s4 - 2*ss2 - rs4;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach r
*---------------------------------------------------------------------*/
p[1]= r4 + s4 - 3.;
p[2]= r4 - 1.;
p[3]= 0.;
p[4]= 4. - 8*(*r) -s4;
p[5]= s4;
p[6]= -s4;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach s
*---------------------------------------------------------------------*/
p[7] = s4 + r4 - 3.;
p[8] = 0.;
p[9] = s4 - 1.;
p[10]= -r4;
p[11]= r4;
p[12]= 4. - r4 - 8*(*s);

/*----------------------------------------------------------------------
* Jacobi-Matrix am Punkt (r,s) entwickeln
*---------------------------------------------------------------------*/
for(i = 1;i <= 2;i++)
  {
  for(j = 1;j <= 2;j++)
    {
    dum= 0.;
    for(k = 1;k <= 6;k++)
      {
      dum+= p[(i-1)*6 + k] * xx[(j-1)*6 + k];
      }
    xj[(i-1)*2 + j]= dum;
    }
  }

/*----------------------------------------------------------------------
* Jacobi-Determinante am Punkt (r,s) entwickeln
*---------------------------------------------------------------------*/
(*det)= xj[1] * xj[4] - xj[3] * xj[2];

if((*det) < 0.00000001)
  return(AL_JACNEG);

/*----------------------------------------------------------------------
* Berechnung der inversen Jacobi-Matrix
*---------------------------------------------------------------------*/
dum= 1./(*det);

xji[1]= xj[4]    * dum;
xji[2]= (-xj[2]) * dum;
xji[3]= (-xj[3]) * dum;
xji[4]= xj[1]    * dum;

/*----------------------------------------------------------------------
* Entwickeln der Matrix b
*---------------------------------------------------------------------*/
for(i = 1;i <= 36;i++)
  b[i]= 0.;

k2= 0;

for(k = 1;k <= 6;k++)
  {
  k2+= 2;
  b[k2-1]= 0.;
  b[k2  ]= 0.;
  b[12 + k2-1]= 0.;
  b[12 + k2  ]= 0.;

  for(i = 1;i <= 2;i++)
    {
    b[     k2-1]= b[     k2-1] + xji[   i] * p[(i-1)*6 + k];
    b[12 + k2  ]= b[12 + k2  ] + xji[2 +i] * p[(i-1)*6 + k];
    }
  b[24 + k2  ]= b[    k2-1];
  b[24 + k2-1]= b[12 +k2  ];
  }

if((*ktyp) > 0) return(0);

/*----------------------------------------------------------------------
* im Falle des axialsymmetrischen Toruselementes 
* die folgende Normalspannungskomponente einfuegen
*---------------------------------------------------------------------*/
/*======================================================================
* Radius am Punkt (r,s) berechnen
*=====================================================================*/
(*xbar)= 0.;

for(k = 1;k <= 6;k++)
  (*xbar)= (*xbar) + h[k] * xx[k];

if((*xbar) <= 0.00000001)
  {
/*======================================================================
* Radius ist null
*=====================================================================*/
  for(k = 1;k <= 12;k++)
    b[36 + k]= b[k];

  return(0);

  }
else
  {
/*======================================================================
* Radius ist nicht null
*=====================================================================*/
  dum=1./(*xbar);
  k2= 0;

  for(k = 1;k <= 6;k++)
    {
    k2+= 2;
    b[36 + k2  ]= 0.;
    b[36 + k2-1]= h[k] * dum;
    }

  }
/**********************************************************************/
return(0);
}
