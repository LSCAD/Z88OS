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
* V14.0  January 14, 2011
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
* diese Compilerunit umfasst: sshq88 - Elementsteifigkeitsroutine
*                             ssh88   - Berechnung der Matrix b
* 18.7.2011 Rieg
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
int ssh88(FR_DOUBLE *r,FR_DOUBLE *s,FR_DOUBLE *t);
FR_DOUBLE hexgh(FR_DOUBLE sig[]);
FR_DOUBLE hexnh(FR_DOUBLE sig[]);
FR_DOUBLE hexsh(FR_DOUBLE sig[]);
             
/***********************************************************************
* hier beginnt Function sshq88
***********************************************************************/
int sshq88(void)
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

FR_DOUBLE eps[7],sig[7],rv[17];

FR_DOUBLE r,s,t,xs,ys,zs,sigv,ax,ay,az,rmin;
FR_DOUBLE f0,f1,f2;

FR_INT4 jp[17];
FR_INT4 i,lx,ly,lz,j,k,jk,ninto_t;

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
for(i = 1;i <= 16;i++)
  {
  xx[i]   = xk[i];
  xx[16+i]= yk[i];
  xx[32+i]= zk[i];
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
  ninto_t= 2;

  for(lx = 1;lx <= ninto;lx++)
    {
    r= xg[(lx-1)*4 + ninto];
    for(ly = 1;ly <= ninto;ly++)
      {
      s= xg[(ly-1)*4 + ninto];
      for(lz = 1;lz <= ninto_t;lz++)
        {
        t= xg[(lz-1)*4 + ninto_t];
      
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        iret= ssh88(&r,&s,&t);
        if(iret != 0) return(iret);
    
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verzerrungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        for(k = 1;k <= 6;k++)
          {
          eps[k]= 0.;
          for(j = 1;j <= 48;j++)
            { 
            eps[k]= eps[k] + b[(k-1)*48 + j] * ul[j];
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
 
        for(j = 1;j <= 16;j++)
          {
          xs+= h[j] * xx[   j];
          ys+= h[j] * xx[16+j];
          zs+= h[j] * xx[32+j];
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
  gmw[kc]/= ninto*ninto*ninto_t;  /* Mittelwert berechnen */

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
    iret= ssh88(&r,&s,&t);
    if(iret != 0) return(iret);
    
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Integrationspunkte in echte Koordinaten umrechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    xs= 0.;
    ys= 0.;
    zs= 0.;
 
    for(j = 1;j <= 16;j++)
      {
      xs+= h[j] * xx[   j];
      ys+= h[j] * xx[16+j];
      zs+= h[j] * xx[32+j];
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* welcher Knoten ist's wirklich?
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(j = 1;j <= 16;j++)
      {
      ax   = xk[j] - xs;
      ay   = yk[j] - ys;
      az   = zk[j] - zs;
      rv[j]= FR_SQRT(ax*ax + ay*ay + az*az);
      }

    rmin= 1e88;
    for(j = 1;j <= 16;j++)
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
    iret= ssh88(&r,&s,&t);
    if(iret != 0) return(iret);
    
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verzerrungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 6;k++)
      {
      eps[k]= 0.;
      for(j = 1;j <= 48;j++)
        { 
        eps[k]= eps[k] + b[(k-1)*48 + j] * ul[j];
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
    iret= ssh88(&r,&s,&t);
    if(iret != 0) return(iret);
    
/*======================================================================
* Verzerrungen berechnen
*=====================================================================*/
    for(k = 1;k <= 6;k++)
      {
      eps[k]= 0.;
      for(j = 1;j <= 48;j++)
        { 
        eps[k]= eps[k] + b[(k-1)*48 + j] * ul[j];
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
 
    for(j = 1;j <= 16;j++)
      {
      xs+= h[j] * xx[   j];
      ys+= h[j] * xx[16+j];
      zs+= h[j] * xx[32+j];
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
* hier beginnt Function ssh88
***********************************************************************/
int ssh88(FR_DOUBLE *r,FR_DOUBLE *s,FR_DOUBLE *t)
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

FR_DOUBLE rp,sp,rm,sm,rqm,sqm,r2,s2,dum,det,ept,emt;
        
FR_INT4 i,j,k,k3;
        
/*----------------------------------------------------------------------
* Klammern der Formfunktionen belegen
*---------------------------------------------------------------------*/
rp=  1. + (*r);
sp=  1. + (*s);
rm=  1. - (*r);
sm=  1. - (*s);
rqm= 1. - (*r)*(*r);
sqm= 1. - (*s)*(*s);
r2=  2. * (*r);
s2=  2. * (*s);
ept= 0.5* (1. + (*t));
emt= 0.5* (1. - (*t));

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

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach r
*---------------------------------------------------------------------*/
p[ 1]= .25 * (sp + r2*sp -sqm) * ept;
p[ 2]= .25 * ((-sp) + r2*sp + sqm) * ept;
p[ 3]= .25 * ((-sm) + sqm + r2*sm) * ept;
p[ 4]= .25 * (sm + r2*sm - sqm) * ept;
p[ 5]= .5 * (-r2)*sp * ept;
p[ 6]= (-.5 ) * sqm * ept;
p[ 7]= .5 * (-r2) * sm * ept;
p[ 8]= .5 * sqm * ept;

p[ 9]= .25 * (sp + r2*sp -sqm) * emt;
p[10]= .25 * ((-sp) + r2*sp + sqm) * emt;
p[11]= .25 * ((-sm) + sqm + r2*sm) * emt;
p[12]= .25 * (sm + r2*sm - sqm) * emt;
p[13]= .5 * (-r2)*sp * emt;
p[14]= (-.5 ) * sqm * emt;
p[15]= .5 * (-r2) * sm * emt;
p[16]= .5 * sqm * emt;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach s
*---------------------------------------------------------------------*/
p[17]= .25 * (rp - rqm + s2*rp) * ept;
p[18]= .25 * (rm - rqm + s2*rm) * ept;
p[19]= .25 * ((-rm) + s2*rm + rqm) * ept;
p[20]= .25 * ((-rp) + rqm + s2*rp) * ept;
p[21]= .5 * rqm * ept;
p[22]= .5 * (-s2) * rm * ept;
p[23]= (-.5 ) * rqm * ept;
p[24]= .5 * (-s2) * rp * ept;

p[25]= .25 * (rp - rqm + s2*rp) * emt;
p[26]= .25 * (rm - rqm + s2*rm) * emt;
p[27]= .25 * ((-rm) + s2*rm + rqm) * emt;
p[28]= .25 * ((-rp) + rqm + s2*rp) * emt;
p[29]= .5 * rqm * emt;
p[30]= .5 * (-s2) * rm * emt;
p[31]= (-.5 ) * rqm * emt;
p[32]= .5 * (-s2) * rp * emt;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach t
*---------------------------------------------------------------------*/
p[33]= .25 * (rp*sp - rqm*sp - sqm*rp) * 0.5;
p[34]= .25 * (rm*sp - rqm*sp - sqm*rm) * 0.5;
p[35]= .25 * (rm*sm - sqm*rm - rqm*sm) * 0.5;
p[36]= .25 * (rp*sm - rqm*sm - sqm*rp) * 0.5;
p[37]= .5 * rqm * sp * 0.5;
p[38]= .5 * sqm * rm * 0.5;
p[39]= .5 * rqm * sm * 0.5;
p[40]= .5 * sqm * rp * 0.5;

p[41]= .25 * (rp*sp - rqm*sp - sqm*rp) * -0.5;
p[42]= .25 * (rm*sp - rqm*sp - sqm*rm) * -0.5;
p[43]= .25 * (rm*sm - sqm*rm - rqm*sm) * -0.5;
p[44]= .25 * (rp*sm - rqm*sm - sqm*rp) * -0.5;
p[45]= .5 * rqm * sp * -0.5;
p[46]= .5 * sqm * rm * -0.5;
p[47]= .5 * rqm * sm * -0.5;
p[48]= .5 * sqm * rp * -0.5;

/*----------------------------------------------------------------------
* Jacobi-Matrix am Punkt (r,s,t) entwickeln
*---------------------------------------------------------------------*/
for(i = 1;i <= 3;i++)
  {
  for(j = 1;j <= 3;j++)
    {
    dum= 0.;
    for(k = 1;k <= 16;k++)
      {
      dum+= p[(i-1)*16 + k] * xx[(j-1)*16 + k];
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

if(FR_FABS(det) < 0.00000000001)
  {
  return(AL_JACNEG);
  }

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
for(i = 1;i <= 288;i++)  /* 16 Knoten * 3 FG * 6 */
  b[i]= 0.;

k3= 0;

for(k = 1;k <= 16;k++)
  {
  k3+= 3;

  for(i = 1;i <= 3;i++)
    {
    b[     k3-2]= b[     k3-2] + xji[    i] * p[(i-1)*16 + k];
    b[48 + k3-1]= b[48 + k3-1] + xji[3 + i] * p[(i-1)*16 + k];
    b[96 + k3  ]= b[96 + k3  ] + xji[6 + i] * p[(i-1)*16 + k];
    }
  b[144 + k3-2]= b[48 + k3-1];
  b[144 + k3-1]= b[     k3-2];
            
  b[192 + k3-1]= b[96 + k3  ];
  b[192 + k3  ]= b[48 + k3-1];

  b[240 + k3-2]= b[96 + k3  ];
  b[240 + k3  ]= b[     k3-2];
  }

return(0);
}

