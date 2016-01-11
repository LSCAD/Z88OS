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
* V14.0  January 14, 2009
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
* diese Compilerunit umfasst: shex88 - Elementsteifigkeitsroutine
*                             sh88   - Berechnung der Matrix b
* 2.1.2010 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>       /* fprintf */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <stdio.h>       /* fprintf */
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
int sh88(FR_DOUBLE *r,FR_DOUBLE *s,FR_DOUBLE *t);
FR_DOUBLE hexgh(FR_DOUBLE sig[]);
FR_DOUBLE hexnh(FR_DOUBLE sig[]);
FR_DOUBLE hexsh(FR_DOUBLE sig[]);
             
/***********************************************************************
* hier beginnt Function shex88
***********************************************************************/
int shex88(void)
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
extern FR_DOUBLE xk[],yk[],zk[];
extern FR_DOUBLE b[],xx[],d[];

extern FR_DOUBLE emode,rnuee;

extern FR_INT4 ninto,isflag,kc,jpri,ifnili,ngau;

FR_DOUBLE eps[7],sig[7],rv[9];

FR_DOUBLE r,s,t,xs,ys,zs,sigv,ax,ay,az,rmin;
FR_DOUBLE f0,f1,f2;

FR_INT4 jp[9];
FR_INT4 i,lx,ly,lz,j,k,jk;

int iret;

/*----------------------------------------------------------------------
* Gauss-Legendre Stuetzstellen
*---------------------------------------------------------------------*/
static FR_DOUBLE xg[17]= { 0.,
   0., -.5773502691896, -.7745966692415, -.8611363115941,
   0., +.5773502691896,              0., -.3399810435849,
   0.,              0., +.7745966692415, +.3399810435849,
   0.,              0.,              0., +.8611363115941 };

/*----------------------------------------------------------------------
* Gauss-Legendre Stuetzstellen, fix fuer 2 x 2 x 2
*---------------------------------------------------------------------*/
static FR_DOUBLE xgo[9]= {0.,
+.5773502691896,
-.5773502691896,
-.5773502691896,
+.5773502691896,
+.5773502691896,
-.5773502691896,
-.5773502691896,
+.5773502691896 };

static FR_DOUBLE ygo[9]= {0.,
+.5773502691896,
+.5773502691896,
-.5773502691896,
-.5773502691896,
+.5773502691896,
+.5773502691896,
-.5773502691896,
-.5773502691896 };

static FR_DOUBLE zgo[9]= {0.,
+.5773502691896,
+.5773502691896,
+.5773502691896,
+.5773502691896,
-.5773502691896,
-.5773502691896,
-.5773502691896,
-.5773502691896 };

/*----------------------------------------------------------------------
* natuerliche Koordinaten der Eckknoten
*---------------------------------------------------------------------*/
static FR_DOUBLE rkr[9]= { 0.,
                        1.,-1.,-1., 1., 1.,-1.,-1., 1. };
static FR_DOUBLE rks[9]= { 0.,
                        1., 1.,-1.,-1., 1., 1.,-1.,-1. };
static FR_DOUBLE rkt[9]= { 0.,
                        1., 1., 1., 1.,-1.,-1.,-1.,-1. };
                      

/*----------------------------------------------------------------------
* xk und yk umspeichern
*---------------------------------------------------------------------*/
for(i = 1;i <= 20;i++)
  {
  xx[i]   = xk[i];
  xx[20+i]= yk[i];
  xx[40+i]= zk[i];
  }

/*----------------------------------------------------------------------
* Materialkonstanten
*---------------------------------------------------------------------*/
f0= emode*(1.-rnuee) / ((1.+rnuee)*(1.-2.*rnuee));

f1= rnuee/(1.-rnuee) * f0;
f2= (1.-2.*rnuee) / (2.*(1.-rnuee)) * f0;

/*----------------------------------------------------------------------
* Elastizitaetsmatrix aufstellen
*---------------------------------------------------------------------*/
for(i = 1;i <= 36;i++)
  d[i]= 0.;

d[1] = f0; 
d[7] = f1;
d[13]= f1; 
d[2] = f1;
d[8] = f0; 
d[14]= f1; 
d[3] = f1; 
d[9] = f1; 
d[15]= f0; 
d[22]= f2;
d[29]= f2;
d[36]= f2;

/*----------------------------------------------------------------------
* Spannungen in den Gauss-Punkten berechnen
*---------------------------------------------------------------------*/
if(ninto > 0)
  {

/*======================================================================
* Spannungen in den Gauss-Punkten berechnen, variabel
*=====================================================================*/
  for(lx = 1;lx <= ninto;lx++)
    {
    r= xg[(lx-1)*4 + ninto];
    for(ly = 1;ly <= ninto;ly++)
      {
      s= xg[(ly-1)*4 + ninto];
      for(lz = 1;lz <= ninto;lz++)
        {
        t= xg[(lz-1)*4 + ninto];
      
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        iret= sh88(&r,&s,&t);
        if(iret != 0) return(iret);
    
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verzerrungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        for(k = 1;k <= 6;k++)
          {
          eps[k]= 0.;
          for(j = 1;j <= 60;j++)
            { 
            eps[k]= eps[k] + b[(k-1)*60 + j] * ul[j];
            }
          }
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Spannungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        for(k = 1;k <= 6;k++)
          {
          sig[k]= 0.;
          for(j = 1;j <= 6;j++)
            {
            sig[k]= sig[k] + d[(k-1)*6 + j] * eps[j];
            }
          }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Integrationspunkte in echte Koordinaten umrechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        xs= 0.;
        ys= 0.;
        zs= 0.;
 
        for(j = 1;j <= 20;j++)
          {
          xs+= h[j] * xx[   j];
          ys+= h[j] * xx[20+j];
          zs+= h[j] * xx[40+j];
          }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Spannungen ausschreiben
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        if(isflag == 0 && ifnili == 0) 
          {
          fprintf(fo3,NL P10E P10E P10E P11E P11E P11E P11E P11E P11E
          ,xs,ys,zs,sig[1],sig[2],sig[3],sig[4],sig[5],sig[6]);
          }

        if(isflag == 1 || isflag == 2 || isflag == 3) 
          {
          if(isflag == 1) sigv= hexgh(sig);
          if(isflag == 2) sigv= hexnh(sig);
          if(isflag == 3) sigv= hexsh(sig);

          ngau++;
          sigvku[ngau]+= sigv;

          if(ifnili == 0)
            {
            fprintf(fo3,NL P10E P10E P10E P11E P11E P11E P11E P11E P11E P11E
            ,xs,ys,zs,sig[1],sig[2],sig[3],sig[4],sig[5],sig[6],sigv);
            }
          if(jpri == 1)
            {
            fprintf(fo5,NL P11E P11E P11E P11E,xs,ys,zs,sigvku[ngau]);
            }
          gmw[kc]+= sigv;      
          }
        } 
      } 
    } 
  gmw[kc]/= ninto*ninto*ninto;  /* Mittelwert berechnen */

/*======================================================================
* die Eckknoten berechnen
*=====================================================================*/
  for(lx = 1;lx <= 8;lx++)                              
    {
    r= rkr[lx];
    s= rks[lx];
    t= rkt[lx];
      
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    iret= sh88(&r,&s,&t);
    if(iret != 0) return(iret);
    
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Integrationspunkte in echte Koordinaten umrechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    xs= 0.;
    ys= 0.;
    zs= 0.;
 
    for(j = 1;j <= 20;j++)
      {
      xs+= h[j] * xx[   j];
      ys+= h[j] * xx[20+j];
      zs+= h[j] * xx[40+j];
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* welcher Knoten ist's wirklich?
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(j = 1;j <= 8;j++)
      {
      ax   = xk[j] - xs;
      ay   = yk[j] - ys;
      az   = zk[j] - zs;
      rv[j]= FR_SQRT(ax*ax + ay*ay + az*az);
      }

    rmin= 1e88;
    for(j = 1;j <= 8;j++)
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
  for(lx = 1;lx <= 8;lx++)                              
    {
    r= xgo[lx];
    s= ygo[lx];
    t= zgo[lx];
      
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    iret= sh88(&r,&s,&t);
    if(iret != 0) return(iret);
    
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verzerrungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 6;k++)
      {
      eps[k]= 0.;
      for(j = 1;j <= 60;j++)
        { 
        eps[k]= eps[k] + b[(k-1)*60 + j] * ul[j];
        }
      }
 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Spannungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 6;k++)
      {
      sig[k]= 0.;
      for(j = 1;j <= 6;j++)
        {
        sig[k]= sig[k] + d[(k-1)*6 + j] * eps[j];
        }
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Vergleichsspannungen aufaddieren
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(isflag == 1) sigv= hexgh(sig);
    if(isflag == 2) sigv= hexnh(sig);
    if(isflag == 3) sigv= hexsh(sig);

    smw[koi[koffs[kc]+jp[lx]-1]]+= sigv;
    jsm[koi[koffs[kc]+jp[lx]-1]]++;
    }  /* Ende Z88O */
  }    /* Ende Gausspunkte variabel */

/*----------------------------------------------------------------------
* Spannungen in den Eckknoten berechnen
*---------------------------------------------------------------------*/
if(ninto == 0)
  {
  for(lx = 1;lx <= 8;lx++)
    {
    r= rkr[lx];
    s= rks[lx];
    t= rkt[lx];
      
/*======================================================================
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*=====================================================================*/
    iret= sh88(&r,&s,&t);
    if(iret != 0) return(iret);
    
/*======================================================================
* Verzerrungen berechnen
*=====================================================================*/
    for(k = 1;k <= 6;k++)
      {
      eps[k]= 0.;
      for(j = 1;j <= 60;j++)
        { 
        eps[k]= eps[k] + b[(k-1)*60 + j] * ul[j];
        }
      } 
 
/*======================================================================
* Spannungen berechnen
*=====================================================================*/
    for(k = 1;k <= 6;k++)
      {
      sig[k]= 0.;
      for(j = 1;j <= 6;j++) 
        {
        sig[k]= sig[k] + d[(k-1)*6 + j] * eps[j];
        }
      } 

/*======================================================================
* Eckpunkte in echte Koordinaten umrechnen
*=====================================================================*/
    xs= 0.;
    ys= 0.;
    zs= 0.;
 
    for(j = 1;j <= 20;j++)
      {
      xs+= h[j] * xx[   j];
      ys+= h[j] * xx[20+j];
      zs+= h[j] * xx[40+j];
      }

/*======================================================================
* Spannungen ausschreiben
*=====================================================================*/
    if(ifnili == 0)
      {
      fprintf(fo3,NL P10E P10E P10E P11E P11E P11E P11E P11E P11E
      ,xs,ys,zs,sig[1],sig[2],sig[3],sig[4],sig[5],sig[6]);
      }
    }                                                      /* e 170 */
  }                                                        /* e if */

return(0);
}

/***********************************************************************
* hier beginnt Function sh88
***********************************************************************/
int sh88(FR_DOUBLE *r,FR_DOUBLE *s,FR_DOUBLE *t)
{
/*---------------------------------------------------------------------
* xx geht rein, unveraendert (ex)
* h geht raus, neu (ex)
* b  geht raus, neu (ex)
* r,s,t gehen rein, unveraendert
*--------------------------------------------------------------------*/

extern FR_DOUBLE h[];
extern FR_DOUBLE b[],xx[],p[];

FR_DOUBLE xj[10], xji[10];              /* ist 3x3 +1 */

FR_DOUBLE epr,emr,eps,ems,ept,emt,emrr,emss,emtt;
FR_DOUBLE zrm,zsm,ztm,dum,det;
        
FR_INT4 i,j,k,k3;
        
/*----------------------------------------------------------------------
* Faktoren der Formfunktionen belegen
*---------------------------------------------------------------------*/
epr = 1. + (*r);
emr = 1. - (*r);
eps = 1. + (*s);
ems = 1. - (*s);
ept = 1. + (*t);
emt = 1. - (*t);
        
emrr= 1. - (*r) * (*r);
emss= 1. - (*s) * (*s);
emtt= 1. - (*t) * (*t);
        
zrm = -2. * (*r);
zsm = -2. * (*s);
ztm = -2. * (*t);

/*----------------------------------------------------------------------
*  Berechnung der Formfunktionen
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
        
/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach r
*---------------------------------------------------------------------*/
p[1]=  .125 *( eps*ept- zrm*eps*ept- emss*ept   - eps*emtt);
p[2]=  .125 *(-eps*ept- zrm*eps*ept+ emss*ept   + eps*emtt);
p[3]=  .125 *(-ems*ept+ emss*ept   - zrm*ems*ept+ ems*emtt);
p[4]=  .125 *( ems*ept- zrm*ems*ept- emss*ept   - ems*emtt);
p[5]=  .125 *( eps*emt- zrm*eps*emt- emss*emt   - eps*emtt); 
p[6]=  .125 *(-eps*emt- zrm*eps*emt+ emss*emt   + eps*emtt);
p[7]=  .125 *(-ems*emt+ emss*emt   - zrm*ems*emt+ ems*emtt);
p[8]=  .125 *( ems*emt- zrm*ems*emt- emss*emt   - ems*emtt);  
p[9]=  .250 *( zrm*eps*ept);
p[10]= .250 *(-emss*ept   );
p[11]= .250 *( zrm*ems*ept);
p[12]= .250 *( emss*ept   );
p[13]= .250 *( zrm*eps*emt);
p[14]= .250 *(-emss*emt   );
p[15]= .250 *( zrm*ems*emt);
p[16]= .250 *( emss*emt   );
p[17]= .250 *( eps*emtt   );
p[18]= .250 *(-eps*emtt   );
p[19]= .250 *(-ems*emtt   );
p[20]= .250 *( ems*emtt   );

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach s
*---------------------------------------------------------------------*/
p[21]=  .125 *( epr*ept -emrr*ept    -epr*zsm*ept -epr*emtt);
p[22]=  .125 *( emr*ept -emrr*ept    -emr*zsm*ept -emr*emtt);
p[23]=  .125 *(-emr*ept -emr*zsm*ept +emrr*ept    +emr*emtt);
p[24]=  .125 *(-epr*ept +emrr*ept    -epr*zsm*ept +epr*emtt);
p[25]=  .125 *( epr*emt -emrr*emt    -epr*zsm*emt -epr*emtt);
p[26]=  .125 *( emr*emt -emrr*emt    -emr*zsm*emt -emr*emtt);
p[27]=  .125 *(-emr*emt -emr*zsm*emt +emrr*emt    +emr*emtt);
p[28]=  .125 *(-epr*emt +emrr*emt    -epr*zsm*emt +epr*emtt);
p[29]=  .250 *( emrr*ept   );
p[30]= .250 *( emr*zsm*ept);
p[31]= .250 *(-emrr*ept   );
p[32]= .250 *( epr*zsm*ept);
p[33]= .250 *( emrr*emt   );
p[34]= .250 *( emr*zsm*emt);
p[35]= .250 *(-emrr*emt   );
p[36]= .250 *( epr*zsm*emt);
p[37]= .250 *( epr*emtt   );
p[38]= .250 *( emr*emtt   );
p[39]= .250 *(-emr*emtt   );
p[40]= .250 *(-epr*emtt   );

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach t
*---------------------------------------------------------------------*/
p[41]=  .125 *( epr*eps -emrr*eps -epr*emss -epr*eps*ztm);
p[42]=  .125 *( emr*eps -emrr*eps -emr*emss -emr*eps*ztm);
p[43]=  .125 *( emr*ems -emr*emss -emrr*ems -emr*ems*ztm);
p[44]=  .125 *( epr*ems -emrr*ems -epr*emss -epr*ems*ztm);
p[45]=  .125 *(-epr*eps +emrr*eps +epr*emss -epr*eps*ztm);
p[46]=  .125 *(-emr*eps +emrr*eps +emr*emss -emr*eps*ztm);
p[47]=  .125 *(-emr*ems +emr*emss +emrr*ems -emr*ems*ztm);
p[48]=  .125 *(-epr*ems +emrr*ems +epr*emss -epr*ems*ztm);
p[49]=  .250 *( emrr*eps   );
p[50]= .250 *( emr*emss   );
p[51]= .250 *( emrr*ems   );
p[52]= .250 *( epr*emss   );
p[53]= .250 *(-emrr*eps   );
p[54]= .250 *(-emr*emss   );
p[55]= .250 *(-emrr*ems   );
p[56]= .250 *(-epr*emss   );
p[57]= .250 *( epr*eps*ztm);
p[58]= .250 *( emr*eps*ztm);
p[59]= .250 *( emr*ems*ztm);
p[60]= .250 *( epr*ems*ztm);

/*----------------------------------------------------------------------
* Jacobi-Matrix am Punkt (r,s,t) entwickeln
*---------------------------------------------------------------------*/
for(i = 1;i <= 3;i++)
  {
  for(j = 1;j <= 3;j++)
    {
    dum= 0.;
    for(k = 1;k <= 20;k++)
      {
      dum+= p[(i-1)*20 + k] * xx[(j-1)*20 + k];
      }
    xj[(i-1)*3 + j]= dum;
    }
  }

/*----------------------------------------------------------------------
* Jacobi-Determinante am Punkt (r,s,t) entwickeln
*---------------------------------------------------------------------*/
det= (xj[1] * xj[5] * xj[9]) - (xj[1] * xj[6] * xj[8]) +
     (xj[2] * xj[6] * xj[7]) - (xj[2] * xj[4] * xj[9]) +
     (xj[3] * xj[4] * xj[8]) - (xj[3] * xj[5] * xj[7]);

if(det < 0.00000001)
  return(AL_JACNEG);

/*----------------------------------------------------------------------
* Berechnung der inversen Jacobi-Matrix
*---------------------------------------------------------------------*/
dum= 1./det;

xji[1]=  (xj[5] * xj[9] - xj[8] * xj[6])*dum;
xji[2]= -(xj[2] * xj[9] - xj[8] * xj[3])*dum;
xji[3]=  (xj[2] * xj[6] - xj[5] * xj[3])*dum;
xji[4]= -(xj[4] * xj[9] - xj[7] * xj[6])*dum;
xji[5]=  (xj[1] * xj[9] - xj[7] * xj[3])*dum;
xji[6]= -(xj[1] * xj[6] - xj[4] * xj[3])*dum;
xji[7]=  (xj[4] * xj[8] - xj[7] * xj[5])*dum;
xji[8]= -(xj[1] * xj[8] - xj[7] * xj[2])*dum;
xji[9]=  (xj[1] * xj[5] - xj[4] * xj[2])*dum;

/*----------------------------------------------------------------------
* Entwickeln der Matrix b
*---------------------------------------------------------------------*/
for(i = 1;i <= 360;i++)
  b[i]= 0.;

k3= 0;

for(k = 1;k <= 20;k++)
  {
  k3+= 3;

  for(i = 1;i <= 3;i++)
    {
    b[     k3-2]= b[     k3-2] + xji[    i] * p[(i-1)*20 + k];
    b[60 + k3-1]= b[60 + k3-1] + xji[3 + i] * p[(i-1)*20 + k];
    b[120+ k3  ]= b[120+ k3  ] + xji[6 + i] * p[(i-1)*20 + k];
    }
  b[180+ k3-2]= b[60 + k3-1];
  b[180+ k3-1]= b[     k3-2];
            
  b[240+ k3-1]= b[120+ k3  ];
  b[240+ k3  ]= b[60 + k3-1];

  b[300 + k3-2]= b[120 +k3  ];
  b[300 + k3  ]= b[     k3-2];
  }

return(0);
}
