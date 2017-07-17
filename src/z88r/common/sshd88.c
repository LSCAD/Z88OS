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
* diese Compilerunit umfasst: sshd88 - Elementsteifigkeitsroutine
*                             ssd88   - Berechnung der Matrix b
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
int ssd88(FR_DOUBLE *r,FR_DOUBLE *s,FR_DOUBLE *t);
FR_DOUBLE hexgh(FR_DOUBLE sig[]);
FR_DOUBLE hexnh(FR_DOUBLE sig[]);
FR_DOUBLE hexsh(FR_DOUBLE sig[]);
             
/***********************************************************************
* hier beginnt Function sshd88
***********************************************************************/
int sshd88(void)
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

FR_DOUBLE eps[7],sig[7],rv[13];

FR_DOUBLE r,s,t,xs,ys,zs,sigv,ax,ay,az,rmin;
FR_DOUBLE f0,f1,f2;

FR_INT4 jp[13];
FR_INT4 i,lx,lz,j,k,jk,ninto_t;

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
* Gauss-Legendre Stuetzstellen fuer t
*---------------------------------------------------------------------*/
static FR_DOUBLE xg[17]= { 0.,
   0., -.5773502691896, -.7745966692415, -.8611363115941,
   0., +.5773502691896,              0., -.3399810435849,
   0.,              0., +.7745966692415, +.3399810435849,
   0.,              0.,              0., +.8611363115941 };

/*----------------------------------------------------------------------
* Gauss-Legendre Stuetzstellen, fix fuer 3 x 2 Punkte
*---------------------------------------------------------------------*/
static FR_DOUBLE xgo[7]= { 0.,
0.1666666666667,
0.6666666666667,
0.1666666666667,
0.1666666666667,
0.6666666666667,
0.1666666666667};

static FR_DOUBLE ygo[7]= { 0.,
0.1666666666667,
0.1666666666667,
0.6666666666667,
0.1666666666667,
0.1666666666667,
0.6666666666667};

static FR_DOUBLE zgo[7]= {0.,
+.5773502691896,
+.5773502691896,
+.5773502691896,
-.5773502691896,
-.5773502691896,
-.5773502691896 };

/*----------------------------------------------------------------------
* Natuerliche Koordinaten der Eckknoten
*---------------------------------------------------------------------*/
static FR_DOUBLE rkr[7]= { 0.,
                        0., 1., 0., 0., 1., 0. };
static FR_DOUBLE rks[7]= { 0.,
                        0., 0., 1., 0., 0., 1. };
static FR_DOUBLE rkt[7]= { 0.,
                        1., 1., 1.,-1.,-1.,-1. };

/*----------------------------------------------------------------------
* xk und yk umspeichern
*---------------------------------------------------------------------*/
for(i = 1;i <= 12;i++)
  {
  xx[i]   = xk[i];
  xx[12+i]= yk[i];
  xx[24+i]= zk[i];
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
    r= rg[lx+2*ninto];
    s= sg[lx+2*ninto];
    for(lz = 1;lz <= ninto_t;lz++)
      {
      t= xg[(lz-1)*4 + ninto_t];
      
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
      iret= ssd88(&r,&s,&t);
      if(iret != 0) return(iret);
    
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verzerrungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
      for(k = 1;k <= 6;k++)
        {
        eps[k]= 0.;
        for(j = 1;j <= 36;j++)
          { 
          eps[k]+= b[(k-1)*36 + j] * ul[j];
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
          sig[k]+= d[(k-1)*6 + j] * eps[j];
          }
        }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Integrationspunkte in echte Koordinaten umrechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
      xs= 0.;
      ys= 0.;
      zs= 0.;
 
      for(j = 1;j <= 12;j++)
        {
        xs+= h[j] * xx[   j];
        ys+= h[j] * xx[12+j];
        zs+= h[j] * xx[24+j];
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
  gmw[kc]/= ninto*ninto*ninto_t;  /* Mittelwert berechnen */

/*======================================================================
* die Eckknoten berechnen
*=====================================================================*/
  for(lx = 1;lx <= 6;lx++)                              
    {
    r= rkr[lx];
    s= rks[lx];
    t= rkt[lx];
      
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    iret= ssd88(&r,&s,&t);
    if(iret != 0) return(iret);
    
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Integrationspunkte in echte Koordinaten umrechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    xs= 0.;
    ys= 0.;
    zs= 0.;
 
    for(j = 1;j <= 12;j++)
      {
      xs+= h[j] * xx[   j];
      ys+= h[j] * xx[12+j];
      zs+= h[j] * xx[24+j];
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* welcher Knoten ist's wirklich?
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(j = 1;j <= 12;j++)  /* weil die unteren Eckknoten erst ab */
      {                     /* Knotennr. 7 kommen */
      ax   = xk[j] - xs;
      ay   = yk[j] - ys;
      az   = zk[j] - zs;
      rv[j]= FR_SQRT(ax*ax + ay*ay + az*az);
      }

    rmin= 1e88;
    for(j = 1;j <= 12;j++)
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
  for(lx = 1;lx <= 6;lx++)                              
    {
    r= xgo[lx];
    s= ygo[lx];
    t= zgo[lx];
      
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    iret= ssd88(&r,&s,&t);
    if(iret != 0) return(iret);
    
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verzerrungen berechnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(k = 1;k <= 6;k++)
      {
      eps[k]= 0.;
      for(j = 1;j <= 36;j++)
        { 
        eps[k]+= b[(k-1)*36 + j] * ul[j];
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
        sig[k]+= d[(k-1)*6 + j] * eps[j];
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
  for(lx = 1;lx <= 6;lx++)
    {
    r= rkr[lx];
    s= rks[lx];
    t= rkt[lx];
      
/*======================================================================
* Matrix b der partiellen Ableitungen & Formfunktionen holen
*=====================================================================*/
    iret= ssd88(&r,&s,&t);
    if(iret != 0) return(iret);
    
/*======================================================================
* Verzerrungen berechnen
*=====================================================================*/
    for(k = 1;k <= 6;k++)
      {
      eps[k]= 0.;
      for(j = 1;j <= 36;j++)
        { 
        eps[k]+= b[(k-1)*36 + j] * ul[j];
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
        sig[k]+= d[(k-1)*6 + j] * eps[j];
        }
      } 

/*======================================================================
* Eckpunkte in echte Koordinaten umrechnen
*=====================================================================*/
    xs= 0.;
    ys= 0.;
    zs= 0.;
 
    for(j = 1;j <= 12;j++)
      {
      xs+= h[j] * xx[   j];
      ys+= h[j] * xx[12+j];
      zs+= h[j] * xx[24+j];
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
* hier beginnt Function ssd88
***********************************************************************/
int ssd88(FR_DOUBLE *r,FR_DOUBLE *s,FR_DOUBLE *t)
{
/*---------------------------------------------------------------------
* xx geht rein, unveraendert (ex)
* h geht raus, neu (ex)
* b  geht raus, neu (ex)
* r,s,t gehen rein, unveraendert
*--------------------------------------------------------------------*/

extern FR_DOUBLE b[],xx[],h[],p[];

FR_DOUBLE xj[10], xji[10];              /* ist 3x3 +1 */

FR_DOUBLE rr2,ss2,r4,r3,s4,s3,rs4,dum,det,ept,emt;
        
FR_INT4 i,j,k,k3;
        
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
ept= 0.5* (1. + (*t));
emt= 0.5* (1. - (*t));

/*----------------------------------------------------------------------
* Formfunktionen obere und untere Ebene
*---------------------------------------------------------------------*/
h[ 1]= (rr2 + ss2 + rs4 - r3 - s3 + 1.) * ept;
h[ 2]= (rr2 - (*r)) * ept;
h[ 3]= (ss2 - (*s)) * ept;
h[ 4]= (r4 - 2*rr2 - rs4) * ept;
h[ 5]= rs4 * ept;
h[ 6]= (s4 - 2*ss2 - rs4) * ept;

h[ 7]= (rr2 + ss2 + rs4 - r3 - s3 + 1.) * emt;
h[ 8]= (rr2 - (*r)) * emt;
h[ 9]= (ss2 - (*s)) * emt;
h[10]= (r4 - 2*rr2 - rs4) * emt;
h[11]= rs4 * emt;
h[12]= (s4 - 2*ss2 - rs4) * emt;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach r
*---------------------------------------------------------------------*/
p[ 1]= (r4 + s4 - 3.) * ept;
p[ 2]= (r4 - 1.) * ept;
p[ 3]= 0.;
p[ 4]= (4. - 8*(*r) -s4) * ept;
p[ 5]= s4 * ept;
p[ 6]= -s4 * ept;

p[ 7]= (r4 + s4 - 3.) * emt;
p[ 8]= (r4 - 1.) * emt;
p[ 9]= 0.;
p[10]= (4. - 8*(*r) -s4) * emt;
p[11]= s4 * emt;
p[12]= -s4 * emt;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach s
*---------------------------------------------------------------------*/
p[13] = (s4 + r4 - 3.) * ept;
p[14] = 0.;
p[15] = (s4 - 1.) * ept;
p[16]= -r4 * ept;
p[17]= r4 * ept;
p[18]= (4. - r4 - 8*(*s)) * ept;

p[19] = (s4 + r4 - 3.) * emt;
p[20] = 0.;
p[21] = (s4 - 1.) * emt;
p[22]= -r4 * emt;
p[23]= r4 * emt;
p[24]= (4. - r4 - 8*(*s)) * emt;

/*----------------------------------------------------------------------
* Partielle Ableitung der Formfunktionen nach t
*---------------------------------------------------------------------*/
p[25]= (rr2 + ss2 + rs4 - r3 - s3 + 1.) * 0.5;
p[26]= (rr2 - (*r)) * 0.5;
p[27]= (ss2 - (*s)) * 0.5;
p[28]= (r4 - 2*rr2 - rs4) * 0.5;
p[29]= rs4 * 0.5;
p[30]= (s4 - 2*ss2 - rs4) * 0.5;

p[31]= -(rr2 + ss2 + rs4 - r3 - s3 + 1.) * 0.5;
p[32]= -(rr2 - (*r)) * 0.5;
p[33]= -(ss2 - (*s)) * 0.5;
p[34]= -(r4 - 2*rr2 - rs4) * 0.5;
p[35]= -rs4 * 0.5;
p[36]= -(s4 - 2*ss2 - rs4) * 0.5;

/*----------------------------------------------------------------------
* Jacobi-Matrix am Punkt (r,s,t) entwickeln
*---------------------------------------------------------------------*/
for(i = 1;i <= 3;i++)
  {
  for(j = 1;j <= 3;j++)
    {
    dum= 0.;
    for(k = 1;k <= 12;k++)
      {
      dum+= p[(i-1)*12 + k] * xx[(j-1)*12 + k];
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
for(i = 1;i <= 216;i++)  /* 12 Knoten * 3 FG * 6 */
  b[i]= 0.;

k3= 0;

for(k = 1;k <= 12;k++)
  {
  k3+= 3;

  for(i = 1;i <= 3;i++)
    {
    b[     k3-2]+= xji[    i] * p[(i-1)*12 + k];
    b[36 + k3-1]+= xji[3 + i] * p[(i-1)*12 + k];
    b[72 + k3  ]+= xji[6 + i] * p[(i-1)*12 + k];
    }
  b[108 + k3-2]= b[36 + k3-1];
  b[108 + k3-1]= b[     k3-2];
            
  b[144 + k3-1]= b[72 + k3  ];
  b[144 + k3  ]= b[36 + k3-1];

  b[180 + k3-2]= b[72 + k3  ];
  b[180 + k3  ]= b[     k3-2];
  }

return(0);
}

