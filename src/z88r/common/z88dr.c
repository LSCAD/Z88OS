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
* Z88DR.C
* Spannungsprozessor fuer Z88R
* 2.12.2015 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>    /* FILE,NULL,fopen,fclose,fprintf */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <stdio.h>    /* FILE,NULL,fopen,fclose,fprintf */
#endif

/***********************************************************************
* Fuer Windows und GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88r.h>
#include <stdio.h>    /* FILE,NULL,fopen,fclose,fprintf */
#endif

/***********************************************************************
* Formate
***********************************************************************/
#define NL "\n"

#ifdef FR_XINT
#define PD "%d"
#define PDB "%d "
#define P5D "%5d"
#define BP5D " %5d"
#define P7DB "%7d  "
#endif

#ifdef FR_XLONG
#define PD "%ld"
#define PDB "%ld "
#define P5D "%5ld"
#define BP5D " %5ld"
#define P7DB "%7ld  "
#endif

#ifdef FR_XLOLO
#define PD "%lld"
#define PDB "%lld "
#define P5D "%5lld"
#define BP5D " %5lld"
#define P7DB "%7lld  "
#endif

#ifdef FR_XDOUB
#define P11E "%+#11.3lE"
#endif

#ifdef FR_XQUAD
#define P11E "%+#11.3LE"
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int  wrim88r(FR_INT4,int);
int  wlog88r(FR_INT4,int);
int  wtyd88j(FR_INT4,FR_INT4);
int  ale88r(int);
int  riy88d(void);
int  slqu88(void);
int  sbal88(void);
int  sshe88(void);
int  ssta88(FR_INT4);
int  swel88(void);
int  srin88(void);
int  sqsh88(void);
int  sest88(FR_INT4);
int  shex88(void);
int  scsh88(void);
int  seba88(void);
int  siso88(void);
int  stet88(void);
int  sspu88(void);
int  sspl88(void);
int  sapl88(void);
int  shpl88(void);
void stop88r(void);
int  span88(void);  
int  sshq88(void);
int  sshd88(void);
int  sshf88(void);
int  sshv88(void);
int  stim88(void);

/****************************************************************************
*  globale Variable
****************************************************************************/
/*--------------------------------------------------------------------------
* Files
*-------------------------------------------------------------------------*/
extern FILE *fwlo,*fo3,*fo5;

/*--------------------------------------------------------------------------
* Pointer
*-------------------------------------------------------------------------*/
extern FR_DOUBLEAY rs;
extern FR_DOUBLEAY u;
extern FR_DOUBLEAY x;
extern FR_DOUBLEAY y;
extern FR_DOUBLEAY z;
extern FR_DOUBLEAY emod;
extern FR_DOUBLEAY rnue;
extern FR_DOUBLEAY qpara;
extern FR_DOUBLEAY riyy;
extern FR_DOUBLEAY eyy;
extern FR_DOUBLEAY rizz;
extern FR_DOUBLEAY ezz;
extern FR_DOUBLEAY rit;
extern FR_DOUBLEAY wt;
extern FR_DOUBLEAY xcp;
extern FR_DOUBLEAY ycp;
extern FR_DOUBLEAY zcp;
extern FR_DOUBLEAY rkap;
extern FR_DOUBLEAY smw;
extern FR_DOUBLEAY smwku;
extern FR_DOUBLEAY gmw;
extern FR_DOUBLEAY gmwku;

extern FR_INT4AY koi;
extern FR_INT4AY ifrei; 
extern FR_INT4AY ioffs;
extern FR_INT4AY koffs;
extern FR_INT4AY ityp;
extern FR_INT4AY ivon_mat;
extern FR_INT4AY ibis_mat;
extern FR_INT4AY ivon_elp;
extern FR_INT4AY ibis_elp; 
extern FR_INT4AY ivon_int;
extern FR_INT4AY ibis_int;   
extern FR_INT4AY ifbeti; 
extern FR_INT4AY intos;
extern FR_INT4AY jsm;

/*--------------------------------------------------------------------------
* Arrays
*-------------------------------------------------------------------------*/
extern FR_DOUBLE ul[];                     /* 61 ist 20 x 3 +1 */

extern FR_INT4 mspan[];                    /* 21 ist MAXPA */

/* Diese Arrays werden in SHEX88,SLQU88,SQSH88 und SCSH88 verwendet */

extern FR_DOUBLE xk[], yk[], zk[];         /* 21 ist MAXPA , SHEX88 */
extern FR_DOUBLE h[];                      /* 21 ist MAXPA , SHEX88 */
extern FR_DOUBLE b[];                      /* ist 6 x 60 +1, SHEX88 */
extern FR_DOUBLE xx[];                     /* ist 3 x 20 +1, SHEX88 */
extern FR_DOUBLE d[];                      /* ist 6 x 6  +1, SHEX88 */
extern FR_DOUBLE p[];                      /* ist 3 x 20 +1, SHEX88 */

/*--------------------------------------------------------------------------
* Variable
*-------------------------------------------------------------------------*/
extern FR_DOUBLE emode,rnuee,qparae,riyye,eyye,rizze,ezze,rite,wte;
extern FR_DOUBLE xkp,ykp,zkp,rkape;

extern FR_INT4 nel,ktyp,IDYNMEM,LANG,jpri,ifnili,ngau,ifbetie;
extern FR_INT4 ndim,nkp,ne,nfg,mmat,melp,mint,nfgp1,nkoi,ibflag,ipflag;
extern FR_INT4 mxknot,mxfrei,ninto,kdflag,isflag,kc,noci,iqflag,ihflag;

/***********************************************************************
* hier beginnt z88dr
***********************************************************************/
int z88dr(void)
{
FR_INT4 i,k,janz,nintoold;

int iret;

/***********************************************************************
* Speicher nullen
***********************************************************************/
ngau= 0;  /* Gausspunkte-Zaehler */

for(k= 1; k <= nkp; k++)
  {
  smw[k]= 0.;
  jsm[k]= 0.;
  }

for(k= 1; k <= ne; k++)
  gmw[k]= 0.;

/***********************************************************************
* wenn Berechnung der Spannungen in den Gausspunkten, dann ndim,ninto
*  & isflag in File Z88O5.TXT schreiben
***********************************************************************/
/*----------------------------------------------------------------------
* Integrationsordnung feststellen. Hier ist nur wichtig, dass ninto > 0
* ist, denn die Plotroutine prueft, ob das der Fall ist. Ansonsten ist 
* der Wert fuer Z88ADRIA 2 unwichtig. In der eigentlichen Elementloop
* wird das dann wirklich elementabhaengig (nochmal) gemacht.
*---------------------------------------------------------------------*/
ninto= 0;

for(k= 1;k <= ne;k++)
  {
  for(i = 1;i <= mint;i++)
    {
    if(k >= ivon_int[i] && k <= ibis_int[i])
      {
      nintoold= ninto;
      ninto= intos[i];
      if(ninto < nintoold) ninto= nintoold;  
      }
    }
  }

if(jpri == 1) 
  fprintf(fo5,BP5D BP5D BP5D,ndim,ninto,isflag);

/***********************************************************************
* Spannungsberechnung: sig= d*b*ul
***********************************************************************/
wrim88r(0,TX_SPANNU);
wlog88r(0,LOG_SPANNU);

if(ifnili == 0)
  {
  if(LANG == 1)
    {
    fprintf(fo3,"Ausgabedatei Z88O3.TXT : Spannungen, erzeugt mit Z88R V15OS\n");
    fprintf(fo3,"                         **********\n");
    }
  if(LANG == 2)
    {
    fprintf(fo3,"output file Z88O3.TXT : stresses, computed by Z88R V15OS\n");
    fprintf(fo3,"                        ********\n");
    }

  if(ninto == 0) 
    {
    if(LANG == 1) fprintf(fo3,"\nBei isoparametrischen Elementen Berechnung\
 der Spannungen in den Eckknoten");
    if(LANG == 2) fprintf(fo3,"\nisoparametric elements: computing\
 stresses in corner nodes");
    }
  else
    {
    if(LANG == 1) fprintf(fo3,"\nbei isoparametrischen Elementen Berechnung\
 der Spannungen in den Gausspunkten\n" PD " Punkte pro Achse/Element",ninto);
    if(LANG == 2) fprintf(fo3,"\nisoparametric elements: computing\
 stresses in Gauss points " PD " points per axis/element",ninto);   
    }
         
  if (ninto > 0 && isflag == 1)
    {
    if(LANG == 1) fprintf(fo3,"\nBerechnung der Vergleichsspannungen nach\
 Gestaltsaenderungsenergie-Hypothese fuer Elemente 3 + 6\
  \nsowie fuer Gausspunkte der Elemente 1,7,8,10,11,12,14 bis 24");
    if(LANG == 2) fprintf(fo3,"\ncomputing von Mises' stresses\
 for elements 3 + 6 and for Gauss points of\n\
 elements 1,7,8,10,11,12,14 to 24");
    }
  
  if (ninto > 0 && isflag == 2)
    {
    if(LANG == 1) fprintf(fo3,"\nBerechnung der Vergleichsspannungen nach\
 Normalspannungs-Hypothese fuer Elemente 3 + 6\
  \nsowie fuer Gausspunkte der Elemente 1,7,8,10,11,12,14 bis 24");
    if(LANG == 2) fprintf(fo3,"\ncomputing principal stresses\
 for elements 3 + 6 and for Gauss points of\n\
 elements 1,7,8,10,11,12,14 to 24");
    }

  if (ninto > 0 && isflag == 3)
    {
    if(LANG == 1) fprintf(fo3,"\nBerechnung der Vergleichsspannungen nach\
 Schubspannungs-Hypothese fuer Elemente 3 + 6\
  \nsowie fuer Gausspunkte der Elemente 1,7,8,10,11,12,14 bis 24");
    if(LANG == 2) fprintf(fo3,"\ncomputing Tresca stresses\
 for elements 3 + 6 and for Gauss points of\n\
 elements 1,7,8,10,11,12,14 to 24");
    }
  } 

/*----------------------------------------------------------------------
* Beginn der Elementschleife
*---------------------------------------------------------------------*/
for(k= 1;k <= ne;k++)
  {
  kc= k;  /* Weitergabe an die Elementroutinen */

/*----------------------------------------------------------------------
*  es ist ityp(k):    1  isoparametrischer hexaeder, linearer ansatz
*                     2  balken
*                     3  scheibe, dreieckig, quadratischer ansatz
*                     4  raeumlicher stab
*                     5  welle
*                     6  torus, dreieckig, linearer ansatz
*                     7  isoparametrische scheibe, quadratischer ansatz
*                     8  isoparametrischer torus , quadratischer ansatz
*                     9  ebenes stabelement 
*                    10  isop. serendipity hexaeder, quadratischer ans.
*                    11  isoparametrische scheibe, kubischer ansatz
*                    12  isoparametrischer torus,  kubischer ansatz 
*                    13  ebenes balkenelement
*                    14  krummlinige dreiecksscheibe, quadr. ansatz
*                    15  krummliniger dreieckstorus, quadr. ansatz
*                    16  krummliniger tetraeder, quadr. ansatz
*                    17  tetraeder, linearer ansatz
*                    18  6-knoten serendipity reissner mindlin platte
*                    19  16-knoten lagrange reissner mindlin platte
*                    20  8-knoten serendipity reissner mindlin platte
*                    21  16-knoten volumenschale
*                    22  12-knoten volumenschale
*                    23  8-knoten flaches schalenelement
*                    24  6-knoten flaches schalenelement
*                    25  balken in allg.lage,Bernoulli + Timoshenko
**--------------------------------------------------------------------*/
/*----------------------------------------------------------------------
* E-modul und Nue feststellen
*---------------------------------------------------------------------*/
for(i = 1;i <= mmat;i++)
  {
  if(k >= ivon_mat[i] && k <= ibis_mat[i])
    {
    emode = emod[i];
    rnuee = rnue[i];
    }
  }

/*----------------------------------------------------------------------
* Integrationsordnung feststellen
*---------------------------------------------------------------------*/
for(i = 1;i <= mint;i++)
  {
  if(k >= ivon_int[i] && k <= ibis_int[i])
    {
    ninto= intos[i];
    }
  }

/*----------------------------------------------------------------------
* Elementparameter feststellen
*---------------------------------------------------------------------*/
for(i = 1;i <= melp;i++)
  {
  if(k >= ivon_elp[i] && k <= ibis_elp[i])
    {    
    qparae= qpara[i];

    if(ibflag == 1)

      {
      riyye=   riyy[i];
      eyye =   eyy[i];
      rizze=   rizz[i];
      ezze =   ezz[i];
      rite =   rit[i];
      wte  =   wt[i];
      ifbetie= ifbeti[i];
      xkp    = xcp[i];
      ykp    = ycp[i];
      zkp    = zcp[i];
      rkape  = rkap[i];
      } 

    if(ipflag != 0 || ihflag != 0)
      {
      riyye= riyy[i];
      } 

    goto L60;
    }
  }

L60:;

/*----------------------------------------------------------------------
* Start 8-Knoten Quader, isoparametrischer linearer Ansatz
*---------------------------------------------------------------------*/
  if(ityp[k]== 1)
    {
    wtyd88j(k,1);

/*----------------------------------------------------------------------
* isopara 8-Knoten Hexaeder: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* Spannungen fuer iso-8-Knoten Hexaeder berechen
*---------------------------------------------------------------------*/
    if(ifnili == 0)
      {
      if(LANG == 1) fprintf(fo3,"\n\nElement # = " PD "     Typ = 8-K Hexaeder", k);
      if(LANG == 2) fprintf(fo3,"\n\nelement # = " PD "     type = 8-n hexahedron", k);

      if(isflag == 0 || ninto == 0)
        {
        fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX");
        }
      else
        {
        fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX       SIGV");
        }
      }

    for(i = 1;i <= 8;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 8;
    mxfrei= 3;            
    
    span88();

    iret= slqu88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-8-Knoten Hexaeder
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start Balkenelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 2)
    {
    wtyd88j(k,2);

/*----------------------------------------------------------------------
* Balkenelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]]];
    yk[1] = y [koi[koffs[k]]];
    zk[1] = z [koi[koffs[k]]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
    zk[2] = z [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* Spannungsberechnung fuer Balkenelement im Raum
*---------------------------------------------------------------------*/
    if(ifnili == 0)
      {
      if(LANG == 1) fprintf(fo3,"\n\nElement #= " P5D " Typ =3D-Balken\
  Knoten " P5D "            Knoten " P5D,k,koi[koffs[k]],koi[koffs[k]+1]);
      if(LANG == 2) fprintf(fo3,"\n\nelement #= " P5D " type =3Dbeam\
   node  " P5D "             node  " P5D,k,koi[koffs[k]],koi[koffs[k]+1]);

      fprintf(fo3,"\n    SIGXX       TAUXX       SIGZZ1\
      SIGYY1      SIGZZ2      SIGYY2");
      }

    mspan[1]= ioffs[koi[koffs[k]  ]] -1;
    mspan[2]= ioffs[koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 6;

    span88();
    sbal88();
    
    goto L7000;

/*----------------------------------------------------------------------
* Ende Balkenelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start Dreieck-Scheibenelement, quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 3)
    {
    wtyd88j(k,3);

/*----------------------------------------------------------------------
* Scheibenelement: zutreffende Koordinaten bestimmen 
* die Mittenknoten werden nicht gebraucht
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]  ]];
    yk[1] = y [koi[koffs[k]  ]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
    xk[3] = x [koi[koffs[k]+2]];
    yk[3] = y [koi[koffs[k]+2]];

/*----------------------------------------------------------------------
* nun Spannungsberechnung fuer Scheibenelement
*---------------------------------------------------------------------*/
    if(ifnili == 0)
      {
      if(LANG == 1) fprintf(fo3,"\n\nElement # = " PD "     Typ = 6-K Scheibe", k);
      if(LANG == 2) fprintf(fo3,"\n\nelement # = " PD "     type= 6-n plane stress", k);

      if(isflag == 0)                                        /* keine VglSp */
        {
        if(kdflag == 1)                                       /* zus. sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY       TAUXY\
       RR         PHI        SIGRR       SIGTT       TAURT");
          }
        else                                                 /* kein sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY\
       TAUXY");
          }
        }                                                    /* e if no VglSp */
      else                                                   /* ja, VglSp */
        {
        if(kdflag == 1)                                       /* zus. sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY       TAUXY\
       RR         PHI        SIGRR       SIGTT       TAURT       SIGV");
          }
        else                                                 /* kein sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY\
       TAUXY       SIGV");
          }
        }                                                    /* e if ja VglSp */
      }

    for(i = 1;i <= 6;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;
         
    mxknot= 6;
    mxfrei= 2;
            
    span88();
    sshe88();
    
    goto L7000;

/*----------------------------------------------------------------------
* Ende 6-k Scheibenelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start raeumliches Stabelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 4)
    {
    wtyd88j(k,4);

/*----------------------------------------------------------------------
* raeumliches Stabelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]]];
    yk[1] = y [koi[koffs[k]]];
    zk[1] = z [koi[koffs[k]]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
    zk[2] = z [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* Spannungsberechnung fuer raeumliches Stabelement
*---------------------------------------------------------------------*/
    mspan[1]= ioffs[ koi[koffs[k]  ]] -1;
    mspan[2]= ioffs[ koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 3;

    span88();
    ssta88(k);
    
    goto L7000;

/*----------------------------------------------------------------------
* Ende raeumliches Stabelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start Wellenelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 5)
    {
    wtyd88j(k,5);

/*----------------------------------------------------------------------
* Wellenelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]]];
    xk[2] = x [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* Spannungsberechnung fuer Wellenelement
*---------------------------------------------------------------------*/
    if(ifnili == 0)
      {
      if(LANG == 1) fprintf(fo3,"\n\nElement #= " P5D " Typ = Welle\
   Knoten " P5D "            Knoten " P5D,k,koi[koffs[k]],koi[koffs[k]+1]);
      if(LANG == 2) fprintf(fo3,"\n\nelement #= " P5D " type = shaft\
    node  " P5D "             node  " P5D,k,koi[koffs[k]],koi[koffs[k]+1]);

      fprintf(fo3,"\n    SIGXX       TAUXX       SIGXY1\
      SIGXZ1      SIGXY2      SIGXZ2");
      }

    mspan[1]= ioffs[ koi[koffs[k]  ]] -1;
    mspan[2]= ioffs[ koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 6;

    span88();
    swel88();
    
    goto L7000;

/*----------------------------------------------------------------------
* Ende Wellenelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start Toruselement, linearer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 6)
    {
    wtyd88j(k,6);

/*----------------------------------------------------------------------
* Toruselement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]  ]];
    yk[1] = y [koi[koffs[k]  ]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
    xk[3] = x [koi[koffs[k]+2]];
    yk[3] = y [koi[koffs[k]+2]];
          
/*----------------------------------------------------------------------
* nun Spannungsberechnung fuer Toruselement
*---------------------------------------------------------------------*/
    if(ifnili == 0)
      {
      if(LANG == 1) fprintf(fo3,"\n\nElement # = " PD "     Typ = 3-K Torus", k);
      if(LANG == 2) fprintf(fo3,"\n\nelement # = " PD "     type =3-n torus", k);

      if(isflag == 0)                                        /* keine VglSp */
        {
        fprintf(fo3,"\n RR         ZZ         SIGRR       SIGZZ\
       TAURZ       SIGTE");
        }                                                    /* e if no VglSp */
      else                                                   /* ja, VglSp */
        {
        fprintf(fo3,"\n RR         ZZ         SIGRR       SIGZZ\
       TAURZ       SIGTE       SIGV");
        }                                                    /* e if ja VglSp */
      }

    mspan[1]= ioffs[koi[koffs[k]  ]] -1;
    mspan[2]= ioffs[koi[koffs[k]+1]] -1;
    mspan[3]= ioffs[koi[koffs[k]+2]] -1;
         
    mxknot= 3;
    mxfrei= 2;

    span88();
    srin88();
    
    goto L7000;

/*----------------------------------------------------------------------
* Ende Toruselement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 8-knoten Scheibe/Torus, isoparametrischer quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 7 || ityp[k]== 8)
    {
    if (ityp[k]== 7)
      {
      wtyd88j(k,7);
      ktyp= 2;
      }
    else
      {
      wtyd88j(k,8);
      ktyp= 0;
      }

/*----------------------------------------------------------------------
* isopara 8-Knoten Scheibe/Torus: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* Spannungen fuer iso-8-Knoten Scheibe/Torus berechnen
*---------------------------------------------------------------------*/
/*======================================================================
* ktyp=2: isopara Scheibenelement mit 8 Knoten
*=====================================================================*/  
    if(ktyp == 2 && ifnili == 0)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = " PD "     Typ = 8-K Scheibe", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = " PD "     type= 8-n plane stress", k);

      if(isflag == 0 || ninto == 0)                         /* keine VglSp */
        {
        if(kdflag == 1)                                     /* zus. sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY       TAUXY\
       RR         PHI        SIGRR       SIGTT       TAURT");
          }
        else                                               /* kein sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY\
       TAUXY");
          }
        }                                                  /* e if no VglSp */
      else                                                 /* ja, VglSp */
        {
        if(kdflag == 1)                                     /* zus. sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY       TAUXY\
       RR         PHI        SIGRR       SIGTT       TAURT       SIGV");
          }
        else                                               /* kein sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY\
       TAUXY       SIGV");
          }
        }                                                  /* e if ja VglSp */
      }                                                    /* e if scheibe */
      
/*======================================================================
* ktyp=0: isopara Toruselement mit 8 Knoten
*=====================================================================*/  
    if(ktyp == 0 && ifnili == 0)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = " PD "     Typ = 8-K Torus", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = " PD "     type =8-n torus", k);

      if(isflag == 0 || ninto == 0)                         /* keine VglSp */
        {
        fprintf(fo3,"\n RR         ZZ         SIGRR       SIGZZ\
       TAURZ       SIGTE");
        }                                                  /* e if no VglSp */
      else                                                 /* ja, VglSp */
        {
        fprintf(fo3,"\n RR         ZZ         SIGRR       SIGZZ\
       TAURZ       SIGTE       SIGV");
        }                                                  /* e if ja VglSp */
      }                                                    /* e if torus */
      
/*======================================================================
* Rechnen
*=====================================================================*/  
    for(i = 1;i <= 8;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 8;
    mxfrei= 2;            
    
    span88();

    iret= sqsh88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-8-Knoten Scheibe/Torus
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start ebenes Stabelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 9)
    {
    wtyd88j(k,9);

/*----------------------------------------------------------------------
* ebenes Stabelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]  ]];
    yk[1] = y [koi[koffs[k]  ]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* Spannungsberechnung fuer ebenes Stabelement
*---------------------------------------------------------------------*/
    mspan[1]= ioffs[ koi[koffs[k]  ]] -1;
    mspan[2]= ioffs[ koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 2;

    span88();
    sest88(k);
    
    goto L7000;
    
/*----------------------------------------------------------------------
* Ende ebenes Stabelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 20-Knoten Hexaeder, isoparametrischer quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 10)
    {
    wtyd88j(k,10);
 
/*----------------------------------------------------------------------
* isopara 20-Knoten Hexaeder: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 20;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* Spannungen fuer iso-20-Knoten Hexaeder berechen
*---------------------------------------------------------------------*/
    if(ifnili == 0)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = " PD "     Typ = 20-K Hexaeder", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = " PD "     type =20-n hexahedron", k);
 
      if(isflag == 0 || ninto == 0)
        {
        fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX");
        }
      else
        {
        fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX       SIGV");
        }
      }
  
    for(i = 1;i <= 20;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 20;
    mxfrei= 3;            
    
    span88();

    iret= shex88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-20-Knoten Hexaeder
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 12-Knoten Scheibe/Torus, isoparametrischer kubischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 11 || ityp[k]== 12)
    {
    if (ityp[k]== 11)
      {
      wtyd88j(k,11);
      ktyp= 2;
      }
    else
      {
      wtyd88j(k,12);
      ktyp= 0;
      }

/*----------------------------------------------------------------------
* isopara 12-Knoten Scheibe/Torus: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 12;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* Spannungen fuer iso-12-Knoten Scheibe/Torus berechen
*---------------------------------------------------------------------*/
/*======================================================================
* ktyp=2: isopara Scheibenelement mit 12 Knoten
*=====================================================================*/  
    if(ktyp == 2 && ifnili == 0)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = " PD "     Typ = 12-K Scheibe", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = " PD "     type= 12-n plane stress", k);

      if(isflag == 0 || ninto == 0)                         /* keine VglSp */
        {
        if(kdflag == 1)                                     /* zus. sigr */
          {
  fprintf(fo3,"\n XX         YY         SIGXX       SIGYY       TAUXY\
       RR         PHI        SIGRR       SIGTT       TAURT");
          }
        else                                               /* kein sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY\
       TAUXY");
          }
        }                                                  /* e if no VglSp */
      else                                                 /* ja, VglSp */
        {
        if(kdflag == 1)                                     /* zus. sigr */
          {
  fprintf(fo3,"\n XX         YY         SIGXX       SIGYY       TAUXY\
       RR         PHI        SIGRR       SIGTT       TAURT       SIGV");
          }
        else                                               /* kein sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY\
       TAUXY       SIGV");
          }
        }                                                  /* e if ja VglSp */
      }                                                    /* e if scheibe */
      
/*======================================================================
* ktyp=0: isopara Toruselement mit 12 Knoten
*=====================================================================*/  
    if(ktyp == 0 && ifnili == 0)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = " PD "     Typ = 12-K Torus", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = " PD "     type =12-n torus", k);

      if(isflag == 0 || ninto == 0)                         /* keine VglSp */
        {
        fprintf(fo3,"\n RR         ZZ         SIGRR       SIGZZ\
       TAURZ       SIGTE");
        }                                                  /* e if no VglSp */
      else                                                 /* ja, VglSp */
        {
        fprintf(fo3,"\n RR         ZZ         SIGRR       SIGZZ\
       TAURZ       SIGTE       SIGV");
        }                                                  /* e if ja VglSp */
      }                                                    /* e if torus */
      
/*======================================================================
* Rechnen
*=====================================================================*/  
    for(i = 1;i <= 12;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 12;
    mxfrei= 2;            
    
    span88();

    iret= scsh88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-12-Knoten Scheibe/Torus
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start ebenes Balkenelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 13)
    {
    wtyd88j(k,13);

/*----------------------------------------------------------------------
* Balkenelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]]];
    yk[1] = y [koi[koffs[k]]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* Spannungsberechnung fuer ebenes Balkenelement
*---------------------------------------------------------------------*/
     if(ifnili == 0)
       {
       if(LANG == 1) fprintf(fo3,"\n\nElement #= " P5D " Typ= Balken in Ebene\
     Knoten " P5D "      Knoten " P5D,k,koi[koffs[k]],koi[koffs[k]+1]);

       if(LANG == 2) fprintf(fo3,"\n\nelement #= " P5D " type = beam in plane\
      node  " P5D "       node  " P5D,k,koi[koffs[k]],koi[koffs[k]+1]);

       fprintf(fo3,"\n    SIGXX                                    SIGZZ1\
            SIGZZ2");
       }

    mspan[1]= ioffs[koi[koffs[k]  ]] -1;
    mspan[2]= ioffs[koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 3;

    span88();
    seba88();
    
    goto L7000;

/*----------------------------------------------------------------------
* Ende ebenes Balkenelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 6-knoten Dreieck Scheibe/Torus, isop quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 14 || ityp[k]== 15)
    {
    if (ityp[k]== 14)
      {
      wtyd88j(k,14);
      ktyp= 2;
      }
    else
      {
      wtyd88j(k,15);
      ktyp= 0;
      }

/*----------------------------------------------------------------------
* isop 6-Knoten Dreieck Scheibe/Torus: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* Spannungen fuer iso-6-Knoten Dreieck Scheibe/Torus berechen
*---------------------------------------------------------------------*/
/*======================================================================
* ktyp=2: isopara Scheibenelement mit 6 Knoten
*=====================================================================*/  
    if(ktyp == 2 && ifnili == 0)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = " PD "     Typ = 6-K isop. Scheibe", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = " PD "     type= 6-n iso. plane stress", k);

      if(isflag == 0 || ninto == 0)                         /* keine VglSp */
        {
        if(kdflag == 1)                                     /* zus. sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY       TAUXY\
       RR         PHI        SIGRR       SIGTT       TAURT");
          }
        else                                               /* kein sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY\
       TAUXY");
          }
        }                                                  /* e if no VglSp */
      else                                                 /* ja, VglSp */
        {
        if(kdflag == 1)                                     /* zus. sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY       TAUXY\
       RR         PHI        SIGRR       SIGTT       TAURT       SIGV");
          }
        else                                               /* kein sigr */
          {
          fprintf(fo3,"\n XX         YY         SIGXX       SIGYY\
       TAUXY       SIGV");
          }
        }                                                  /* e if ja VglSp */
      }                                                    /* e if scheibe */
      
/*======================================================================
* ktyp=0: isopara Toruselement mit 6 Knoten
*=====================================================================*/  
    if(ktyp == 0 && ifnili == 0)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = " PD "     Typ = 6-K isop. Torus", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = " PD "     type =6-n isop. torus", k);

      if(isflag == 0 || ninto == 0)                         /* keine VglSp */
        {
        fprintf(fo3,"\n RR         ZZ         SIGRR       SIGZZ\
       TAURZ       SIGTE");
        }                                                  /* e if no VglSp */
      else                                                 /* ja, VglSp */
        {
        fprintf(fo3,"\n RR         ZZ         SIGRR       SIGZZ\
       TAURZ       SIGTE       SIGV");
        }                                                  /* e if ja VglSp */
      }                                                    /* e if torus */
      
/*======================================================================
* Rechnen
*=====================================================================*/  
    for(i = 1;i <= 6;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 6;
    mxfrei= 2;            
    
    span88();

    iret= siso88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-6-Knoten Dreieck Scheibe/Torus
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 10-Knoten Tetraeder, isoparametrischer quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 16)
    {
    wtyd88j(k,16);
 
/*----------------------------------------------------------------------
* isopara 10-Knoten Tetraeder: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 10;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* Spannungen fuer iso-10-Knoten Tetraeder berechen
*---------------------------------------------------------------------*/
    if(ifnili == 0)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = " PD "     Typ = 10-K Tetraeder", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = " PD "     type =10-n tetrahedron", k);
 
      if(isflag == 0 || ninto == 0)
        {
        fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX");
        }
      else
        {
        fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX       SIGV");
        }
      }

    for(i = 1;i <= 10;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 10;
    mxfrei= 3;            
    
    span88();

    iret= stet88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-10-Knoten Tetraeder
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 4-Knoten Tetraeder, linearer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 17)
    {
    wtyd88j(k,17);
 
/*----------------------------------------------------------------------
* 4-Knoten Tetraeder: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 4;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* Spannungen fuer 4-Knoten Tetraeder berechen
*---------------------------------------------------------------------*/
    if(ifnili == 0)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = " PD "     Typ = 4-K Tetraeder", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = " PD "     type =4-n tetrahedron", k);
 
      if(isflag == 0 || ninto == 0)
        {
        fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX");
        }
      else
        {
        fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX       SIGV");
        }
      }
  
    for(i = 1;i <= 4;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 4;
    mxfrei= 3;            
    
    span88();

    iret= sspu88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 4-Knoten Tetraeder
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 6-Knoten Reissner-Mindlin Platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 18)
    {
    wtyd88j(k,18);
 
/*----------------------------------------------------------------------
* isopara 6-Knoten Platte: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* Spannungen fuer iso-6-Knoten Platte berechen
*---------------------------------------------------------------------*/
    if(ifnili == 0)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = " PD "     Typ = 6-K Platte", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = " PD "     type =6-n plate", k);

      if(isflag == 0 || ninto == 0)
        {
        fprintf(fo3,"\n XX         YY         MXX         MYY\
         MXY         QYZ         QZX         SIGXX       SIGYY\
       TAUXY       TAUXZ(Z=0)  TAUYZ(Z=0)");
        }
      else
        {
        fprintf(fo3,"\n XX         YY         MXX         MYY\
         MXY         QYZ         QZX         SIGXX       SIGYY\
       TAUXY       TAUXZ(Z=0)  TAUYZ(Z=0)   SIGV");
        }
      }
  
    for(i = 1;i <= 6;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 6;
    mxfrei= 3;            
    
    span88();

    iret= sspl88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 6-Knoten Reissner-Mindlin Platte
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 16-Knoten Reissner-Mindlin Lagrange Platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 19)
    {
    wtyd88j(k,19);
 
/*----------------------------------------------------------------------
* isopara 16-Knoten Platte: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 16;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* Spannungen fuer iso-16-Knoten Platte berechen
*---------------------------------------------------------------------*/
    if(ifnili == 0)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = " PD "     Typ = 16-K Platte", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = " PD "     type =16-n plate", k);
 
      if(isflag == 0 || ninto == 0)
        {
        fprintf(fo3,"\n XX         YY         MXX         MYY\
         MXY         QYZ         QZX         SIGXX       SIGYY\
       TAUXY       TAUXZ(Z=0)  TAUYZ(Z=0)");
        }
      else
        {
        fprintf(fo3,"\n XX         YY         MXX         MYY\
         MXY         QYZ         QZX         SIGXX       SIGYY\
       TAUXY       TAUXZ(Z=0)  TAUYZ(Z=0)   SIGV");
        }
      }
  
    for(i = 1;i <= 16;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 16;
    mxfrei= 3;            
    
    span88();

    iret= shpl88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 16-Knoten Reissner-Mindlin Lagrange Platte
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 8-Knoten Reissner-Mindlin Serendipity Platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 20)
    {
    wtyd88j(k,20);
 
/*----------------------------------------------------------------------
* isopara 8-Knoten Platte: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* Spannungen fuer iso-8-Knoten Platte berechen
*---------------------------------------------------------------------*/
    if(ifnili == 0)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = " PD "     Typ = 8-K Platte", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = " PD "     type =8-n plate", k);
 
      if(isflag == 0 || ninto == 0)
        {
        fprintf(fo3,"\n XX         YY         MXX         MYY\
         MXY         QYZ         QZX         SIGXX       SIGYY\
       TAUXY       TAUXZ(Z=0)  TAUYZ(Z=0)");
        }
      else
        {
        fprintf(fo3,"\n XX         YY         MXX         MYY\
         MXY         QYZ         QZX         SIGXX       SIGYY\
       TAUXY       TAUXZ(Z=0)  TAUYZ(Z=0)   SIGV");
        }
      }
  
    for(i = 1;i <= 8;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 8;
    mxfrei= 3;            
    
    span88();

    iret= sapl88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 8-Knoten Reissner-Mindlin Serendipity Platte
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 16-Knoten Volumenschalenelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 21)
    {
    wtyd88j(k,21);
 
/*----------------------------------------------------------------------
* 16-Knoten Vol.Scha.ele.: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 16;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* Spannungen fuer 16-Knoten Vol.Scha.ele. berechen
*---------------------------------------------------------------------*/
    if(ifnili == 0)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = " PD "     Typ = 16-K Schale", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = " PD "     type =16-n shell", k);

      if(isflag == 0 || ninto == 0)
        {
        fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX");
        }
      else
        {
        fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX       SIGV");
        }
      }
  
    for(i = 1;i <= 16;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 16;
    mxfrei=  3;            
    
    span88();

    iret= sshq88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 16-Knoten Volumenschalenelement
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 12-Knoten Volumenschalenelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 22)
    {
    wtyd88j(k,22);
 
/*----------------------------------------------------------------------
* 12-Knoten Vol.Scha.ele.: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 12;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* Spannungen fuer 12-Knoten Vol.Scha.ele. berechen
*---------------------------------------------------------------------*/
    if(ifnili == 0)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = " PD "     Typ = 12-K Schale", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = " PD "     type =12-n shell", k);
 
      if(isflag == 0 || ninto == 0)
        {
        fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX");
        }
      else
        {
        fprintf(fo3,"\n XX         YY         ZZ         SIGXX       SIGYY\
       SIGZZ       TAUXY       TAUYZ       TAUZX       SIGV");
        }
      }
  
    for(i = 1;i <= 12;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 12;
    mxfrei=  3;            
    
    span88();

    iret= sshd88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 12-Knoten Volumenschalenelement
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 8-Knoten flache Schale
*---------------------------------------------------------------------*/
  else if(ityp[k]== 23)
    {
    wtyd88j(k,23);
 
/*----------------------------------------------------------------------
* 8-Knoten flache Schale: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* Spannungen fuer 8-Knoten flache Schale berechen
*---------------------------------------------------------------------*/
    if(ifnili == 0)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = " PD "     Typ = 8-K Schale", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = " PD "     type = 8-n shell", k);

      if(isflag == 0 || ninto == 0)
        {
        fprintf(fo3,"\n  XX         YY         ZZ         SIGXX       SIGYY\
       TAUXY");
        }
      else
        {
        fprintf(fo3,"\n  XX         YY         ZZ         SIGXX       SIGYY\
       TAUXY       SIGV");
        }
      }
  
    for(i = 1;i <= 8;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 8;
    mxfrei= 6;            
    
    span88();

    iret= sshv88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 8-Knoten flache Schale
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 6-Knoten flache Schale
*---------------------------------------------------------------------*/
  else if(ityp[k]== 24)
    {
    wtyd88j(k,24);
 
/*----------------------------------------------------------------------
* 6-Knoten flache Schale: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* Spannungen fuer 6-Knoten flache Schale berechen
*---------------------------------------------------------------------*/
    if(ifnili == 0)
      {
      if(LANG == 1)
        fprintf(fo3,"\n\nElement # = " PD "     Typ = 6-K Schale", k);
      if(LANG == 2)
        fprintf(fo3,"\n\nelement # = " PD "     type = 6-n shell", k);
 
      if(isflag == 0 || ninto == 0)
        {
        fprintf(fo3,"\n  XX         YY         ZZ         SIGXX       SIGYY\
       TAUXY");
        }
      else
        {
        fprintf(fo3,"\n  XX         YY         ZZ         SIGXX       SIGYY\
       TAUXY       SIGV");
        }
      }
  
    for(i = 1;i <= 6;i++)
      mspan[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 6;
    mxfrei= 6;            
    
    span88();

    iret= sshf88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 6-Knoten flache Schale
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start Balkenelement Nr.25
*---------------------------------------------------------------------*/
  else if(ityp[k]== 25)
    {
    wtyd88j(k,25);

/*----------------------------------------------------------------------

* Balkenelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]]];
    yk[1] = y [koi[koffs[k]]];
    zk[1] = z [koi[koffs[k]]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
    zk[2] = z [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* Spannungsberechnung fuer Balkenelement im Raum

*---------------------------------------------------------------------*/
    if(ifnili == 0)
      {
      if(LANG == 1) fprintf(fo3,"\n\nElement #= " P5D " Typ =3D-Balken Nr.25\
  Knoten " P5D "            Knoten " P5D,k,koi[koffs[k]],koi[koffs[k]+1]);
      if(LANG == 2) fprintf(fo3,"\n\nelement #= " P5D " type =3Dbeam no.25\
   node  " P5D "             node  " P5D,k,koi[koffs[k]],koi[koffs[k]+1]);

      fprintf(fo3,"\n    SIGXX       TAUXX       SIGZZ1\
      SIGYY1      SIGZZ2      SIGYY2");
      }

    mspan[1]= ioffs[koi[koffs[k]  ]] -1;
    mspan[2]= ioffs[koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 6;

    span88();
    stim88();
    
    goto L7000;

/*----------------------------------------------------------------------
* Ende Balkenelement Nr.25
*---------------------------------------------------------------------*/
    }


L7000:;
  
/***********************************************************************
* Ende der Schleife ueber alle Elemente
***********************************************************************/
  } 

/*----------------------------------------------------------------------
* Ende Z88D
*---------------------------------------------------------------------*/

/*======================================================================
* Spannungen addieren fuer alle Nicht-Balken
*=====================================================================*/
if((isflag == 1 || isflag == 2 || isflag == 3) && 
   !(ityp[1] == 2 || ityp[1] == 5 || ityp[1] == 13 || ityp[1] == 25))
  {

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Eckknoten mit Vergleichsspannungen in smwku addieren
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for(k= 1; k <= nkp; k++)
    {
    if(jsm[k] > 0) smw[k]/= jsm[k];
    smwku[k]+= smw[k];
    }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* mittlere Vergleichsspannungen pro Element in gmwku addieren
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for(k= 1; k <= ne; k++)
    gmwku[k]+= gmw[k];

  }

/*----------------------------------------------------------------------
* Dateien schliessen
*---------------------------------------------------------------------*/
if(noci == 1)
  {
  ale88r(AL_NOCI);
  wlog88r(0,LOG_NOCI);
  }

if(ifnili == 0) fprintf(fo3,"\n");

wrim88r(0,TX_EXITZ88D);
wlog88r(0,LOG_EXITZ88D);

return(0);
}

