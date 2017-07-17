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
* V15.0  November 18, 2015
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
* z88tx.c : von Z88 nach DXF
* 14.12.2015 Rieg 
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88x.h>
#include <stdio.h>      /* fopen, fprintf, fclose */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88x.h>
#include <stdio.h>      /* fopen, fprintf, fclose */
#endif

/***********************************************************************
* Schreib/Leseformate
***********************************************************************/
#define NLB "\n "
#define NL "\n"

#define PC "%c"
#define PCB "%c "

#define PS "%s"
#define PSB "%s "

#ifdef FR_XINT
#define PDB "%d "
#define PD "%d"
#define PD5B "%5d "
#define PD5 "%5d"
#define PD2B "%2d "
#define PD2 "%2d"
#endif

#ifdef FR_XLONG
#define PDB "%ld "
#define PD "%ld"
#define PD5B "%5ld "
#define PD5 "%5ld"
#define PD2B "%2ld "
#define PD2 "%2ld"
#endif

#ifdef FR_XLOLO
#define PDB "%lld "
#define PD "%lld"
#define PD5B "%5lld "
#define PD5 "%5lld"
#define PD2B "%2lld "
#define PD2 "%2lld"
#endif

#ifdef FR_XDOUB
#define PFB "%lf "
#define PF "%lf"
#define PG "%lg"
#define PGB "%lg "
#define PE13B "%+#13.5lE "
#define PE13 "%+#13.5lE"
#endif

#ifdef FR_XQUAD
#define PFB "%Lf "
#define PF "%Lf"
#define PG "%Lg"
#define PGB "%Lg "
#define PE13B "%+#13.5LE "
#define PE13 "%+#13.5LE"
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88x(FR_INT4,int);
int wlog88x(FR_INT4,int);

/***********************************************************************
* hier beginnt Function z88tx
***********************************************************************/
int z88tx(void)
{
extern FILE *fdxf,*fwlo;

extern FR_DOUBLEAY x;
extern FR_DOUBLEAY y;
extern FR_DOUBLEAY z;
extern FR_DOUBLEAY wert;
extern FR_DOUBLEAY pres;
extern FR_DOUBLEAY tr1;
extern FR_DOUBLEAY tr2;

extern FR_INT4AY koi;
extern FR_INT4AY koffs;
extern FR_INT4AY ityp;
extern FR_INT4AY itypfe;
extern FR_INT4AY jel;
extern FR_INT4AY iel;
extern FR_INT4AY kel;
extern FR_INT4AY nkn;
extern FR_INT4AY ifg;
extern FR_INT4AY irflag;
extern FR_INT4AY noi;
extern FR_INT4AY noffs;
extern FR_INT4AY nep;

extern FR_CHARAY cjmode;
extern FR_CHARAY cimode;
extern FR_CHARAY ckmode;

extern FR_DOUBLE epsx,epsy,epsz;
extern FR_DOUBLE texts;

extern FR_INT4 ndim,nkp,ne,nfg,kflagss,kflag,iqflag,niflag;
extern FR_INT4 nrb,npr;
extern FR_INT4 ICFLAG,ITSFLAG;

extern char cxx[];

FR_DOUBLE px[21], py[21], pz[21];

FR_DOUBLE xmin,xmax,ymin,ymax,zmin,zmax;
FR_DOUBLE xlimin,xlimax,ylimin,ylimax;
FR_DOUBLE pxele,pyele,pzele;
FR_DOUBLE fackno;

FR_INT4 i1point[] = {0,1,2,3,4,5,6,7,8,1,2,3,4};
FR_INT4 j1point[] = {0,2,3,4,1,6,7,8,5,5,6,7,8};

FR_INT4 i3point[] = {0,1,4,2,5,3,6};
FR_INT4 j3point[] = {0,4,2,5,3,6,1};

FR_INT4 i6point[] = {0,1,2,3};
FR_INT4 j6point[] = {0,2,3,1};

FR_INT4 i7point[] = {0,1,5,2,6,3,7,4,8};
FR_INT4 j7point[] = {0,5,2,6,3,7,4,8,1};

FR_INT4 i10point[]= { 0, 1, 9, 2,10, 3,11, 4,12, 5,13, 6,14, 7,15, 8,16,
                      1,17, 2,18, 3,19, 4,20};
FR_INT4 j10point[]= { 0, 9, 2,10, 3,11, 4,12, 1,13, 6,14, 7,15, 8,16, 5,
                     17, 5,18, 6,19, 7,20, 8};

FR_INT4 i11point[]= {0,1,5,6,2,7,8,3,9 ,10, 4,11,12};
FR_INT4 j11point[]= {0,5,6,2,7,8,3,9,10, 4,11,12, 1};

FR_INT4 i19point[] = {0,1,2,3,4,5,6,7,8,9, 10,11,12,13,14,15,16};
FR_INT4 j19point[] = {0,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16, 1};

FR_INT4 i21point[]= { 0,1,5,2,6,3,7,4,8,  9,13,10,14,11,15,12,16, 1, 2, 3, 4};
FR_INT4 j21point[]= { 0,5,2,6,3,7,4,8,1, 13,10,14,11,15,12,16, 9, 9,10,11,12};

FR_INT4 i22point[]= { 0,1,4,2,5,3,6,  7,10, 8,11, 9,12, 1,2,3};
FR_INT4 j22point[]= { 0,4,2,5,3,6,1, 10, 8,11, 9,12, 7, 7,8,9};

FR_INT4 i17point[]= { 0,1,2,3, 2, 3, 1};
FR_INT4 j17point[]= { 0,2,3,1, 4, 4, 4};

FR_INT4 i16point[]= { 0,1,5,2,6,3,7, 2,8, 3,9,  1,10};
FR_INT4 j16point[]= { 0,5,2,6,3,7,1, 8,4, 9,4, 10, 4};


FR_INT4 i,j,k;
 
/***********************************************************************
* start function
***********************************************************************/
wrim88x(0,TX_Z88TX);
wlog88x(0,LOG_Z88TX);

/***********************************************************************
* file fdxf = Z88X.DXF oeffnen
***********************************************************************/
wlog88x(0,LOG_FX);
wrim88x(0,TX_FX);
fdxf= fopen(cxx,"w");
if(fdxf == NULL)
  {
  wlog88x(0,LOG_NOX);
  fclose(fwlo);
  return(AL_NOX);
  }
rewind(fdxf);

/***********************************************************************
* faktoren fuer textsize definieren
***********************************************************************/
wlog88x(0,LOG_FAC);
wrim88x(0,TX_FAC);

fackno= 0.01;

/***********************************************************************
* wenn 2d, z[i] null setzen
***********************************************************************/
if(ndim == 2)
  for(i= 1; i <= nkp; i++) z[i]= 0.0;

zmin= 0.0;
zmax= 0.0;

/***********************************************************************
* groesstwerte,limits,textsize ermitteln
***********************************************************************/
if (ndim == 2)
  {
/*---------------------------------------------------------------------
* 2d: kleinste & groesste werte x,y ermitteln
*--------------------------------------------------------------------*/
  xmin= x[1];
  xmax= x[1];
  ymin= y[1];
  ymax= y[1];

  for(i= 1; i <= nkp; i++)
    {
    if( x[i] < xmin) xmin= x[i];
    if( x[i] > xmax) xmax= x[i];
    if( y[i] < ymin) ymin= y[i];
    if( y[i] > ymax) ymax= y[i];
    }

/*---------------------------------------------------------------------
* 2d: textgroessen isele und iskno festlegen
*--------------------------------------------------------------------*/
  if(ITSFLAG == 0)
    texts= fackno*0.5*((xmax-xmin)+(ymax-ymin));

/*---------------------------------------------------------------------
* 2d: limits ermitteln
*--------------------------------------------------------------------*/
  xlimin= xmin - 0.25*(xmax-xmin);
  ylimin= ymin - 0.25*(ymax-ymin);
  xlimax= xmax + 0.25*(xmax-xmin);
  ylimax= ymax + 0.25*(ymax-ymin);
  }
else
  {
/*---------------------------------------------------------------------
* 3d: kleinste & groesste werte x,y,z ermitteln
*--------------------------------------------------------------------*/
  xmin= x[1];
  xmax= x[1];
  ymin= y[1];
  ymax= y[1];
  zmin= z[1];
  zmax= z[1];

  for(i= 1; i <= nkp; i++)
    {
    if( x[i] < xmin) xmin= x[i];
    if( x[i] > xmax) xmax= x[i];
    if( y[i] < ymin) ymin= y[i];
    if( y[i] > ymax) ymax= y[i];
    if( z[i] < zmin) zmin= z[i];
    if( z[i] > zmax) zmax= z[i];
    }

/*---------------------------------------------------------------------
* 3d: textgroesse texts festlegen
*--------------------------------------------------------------------*/
  if(ITSFLAG == 0)
    texts= fackno*0.333*((xmax-xmin)+(ymax-ymin)+(zmax-zmin));

/*---------------------------------------------------------------------
* 3d: limits ermitteln
*--------------------------------------------------------------------*/
  xlimin= xmin - 0.5*(xmax-xmin);
  ylimin= ymin - 0.5*(ymax-ymin);
  xlimax= xmax + 0.5*(xmax-xmin);
  ylimax= ymax + 0.5*(ymax-ymin);
  }

/***********************************************************************
* Z88X.DXF : bis section entities auffuellen
***********************************************************************/
wlog88x(0,LOG_SDXF);
wrim88x(0,TX_SDXF);

fprintf(fdxf,"  0\nSECTION"); /* start section header */
fprintf(fdxf,"\n  2\nHEADER");

fprintf(fdxf,"\n  9\n$ACADVER\n  1\nAC1009");
fprintf(fdxf,"\n  9\n$INSBASE\n 10\n0.0\n 20\n0.0\n 30\n0.0");

fprintf(fdxf,"\n  9\n$EXTMIN");
fprintf(fdxf,"\n 10\n" PG,xmin);
fprintf(fdxf,"\n 20\n" PG,ymin);
fprintf(fdxf,"\n 30\n" PG,zmin);

fprintf(fdxf,"\n  9\n$EXTMAX");
fprintf(fdxf,"\n 10\n" PG,xmax);
fprintf(fdxf,"\n 20\n" PG,ymax);
fprintf(fdxf,"\n 30\n" PG,zmax);

fprintf(fdxf,"\n  9\n$LIMMIN");
fprintf(fdxf,"\n 10\n" PG,xlimin);
fprintf(fdxf,"\n 20\n" PG,ylimin);

fprintf(fdxf,"\n  9\n$LIMMAX");
fprintf(fdxf,"\n 10\n" PG,xlimax);
fprintf(fdxf,"\n 20\n" PG,ylimax);

fprintf(fdxf,"\n  9\n$CLAYER\n  8\nZ88NET");

fprintf(fdxf,"\n  9\n$PDMODE\n 70\n     3"); /* schraege kreuze */
fprintf(fdxf,"\n  9\n$PDSIZE\n 40\n-3.0");   /* 3 % groesse */

fprintf(fdxf,"\n  0\nENDSEC"); /* ende section header */

fprintf(fdxf,"\n  0\nSECTION"); /* start section tables */
fprintf(fdxf,"\n  2\nTABLES");

fprintf(fdxf,"\n  0\nTABLE"); /* start table ltype */

fprintf(fdxf,"\n  2\nLTYPE\n 70\n     1"); /* 1 linientyp */

fprintf(fdxf,"\n  0\nLTYPE\n  2\nCONTINUOUS\n 70\n    64\n  3");
fprintf(fdxf,"\nSolid line\n 72\n    65\n 73\n     0\n 40\n0.0");

fprintf(fdxf,"\n  0\nENDTAB"); /* ende table ltype */

fprintf(fdxf,"\n  0\nTABLE");  /* start table layer */

fprintf(fdxf,"\n  2\nLAYER\n 70\n     6"); /* 6 layer ausser 0 */

fprintf(fdxf,"\n  0\nLAYER\n  2\n0\n 70\n    64\n 62\n    -7");
fprintf(fdxf,"\n  6\nCONTINUOUS"); /* weiss, ausgeschaltet */

fprintf(fdxf,"\n  0\nLAYER\n  2\nZ88NET\n 70\n    64\n 62\n     5");
fprintf(fdxf,"\n  6\nCONTINUOUS"); /* blau, eingeschaltet */

fprintf(fdxf,"\n  0\nLAYER\n  2\nZ88EIO\n 70\n    64\n 62\n     5");
fprintf(fdxf,"\n  6\nCONTINUOUS"); /* blau, eingeschaltet */

fprintf(fdxf,"\n  0\nLAYER\n  2\nZ88KNR\n 70\n    64\n 62\n     1");
fprintf(fdxf,"\n  6\nCONTINUOUS"); /* rot, eingeschaltet */

fprintf(fdxf,"\n  0\nLAYER\n  2\nZ88RBD\n 70\n    64\n 62\n     6");
fprintf(fdxf,"\n  6\nCONTINUOUS"); /* magenta, eingeschaltet */

fprintf(fdxf,"\n  0\nLAYER\n  2\nZ88FLA\n 70\n    64\n 62\n     6");
fprintf(fdxf,"\n  6\nCONTINUOUS"); /* magenta, eingeschaltet */

fprintf(fdxf,"\n  0\nLAYER\n  2\nZ88GEN\n 70\n    64\n 62\n     6");
fprintf(fdxf,"\n  6\nCONTINUOUS"); /* magenta, eingeschaltet */

fprintf(fdxf,"\n  0\nLAYER\n  2\nZ88PKT\n 70\n    64\n 62\n     1");
fprintf(fdxf,"\n  6\nCONTINUOUS"); /* rot, eingeschaltet */

fprintf(fdxf,"\n  0\nENDTAB"); /* ende table layer */

fprintf(fdxf,"\n  0\nENDSEC"); /* ende section tables */

fprintf(fdxf,"\n  0\nSECTION"); /* start section entities */
fprintf(fdxf,"\n  2\nENTITIES");

/***********************************************************************
* allgemeine datei-informationen schreiben
***********************************************************************/
/*---------------------------------------------------------------------
* linke obere ecke
*--------------------------------------------------------------------*/
pxele= xlimin;
pyele= ylimax-1.5*texts;

/*---------------------------------------------------------------------
* grundsatz-infos schreiben
*--------------------------------------------------------------------*/
fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88GEN");
fprintf(fdxf,"\n 10\n" PG,pxele);
fprintf(fdxf,"\n 20\n" PG,pyele);
fprintf(fdxf,"\n 30\n0.0");
fprintf(fdxf,"\n 40\n" PG,texts);

if (ICFLAG == 1 || ICFLAG == 2)
  {
  fprintf(fdxf,"\n  1\nZ88I1.TXT " PDB PDB PDB PDB PD,ndim,nkp,ne,nfg,kflag);
  }
else
  {
  fprintf(fdxf,"\n  1\nZ88NI.TXT " PDB PDB PDB PDB PDB PDB PD,ndim,nkp,ne,nfg,kflagss,niflag,kflag);
  }

pyele+= -1.5 * texts;

/*---------------------------------------------------------------------
* ggf. neue fangbereiche bei Z88NI.TXT
*--------------------------------------------------------------------*/
if (ICFLAG == 3 && niflag == 1)
  {
  fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88GEN");
  fprintf(fdxf,"\n 10\n" PG,pxele);
  fprintf(fdxf,"\n 20\n" PG,pyele);
  fprintf(fdxf,"\n 30\n0.0");
  fprintf(fdxf,"\n 40\n" PG,texts);
  if(ndim == 2)
    fprintf(fdxf,"\n  1\nD " PGB PG,epsx,epsy);
  else
    fprintf(fdxf,"\n  1\nD " PGB PGB PG,epsx,epsy,epsz);
  pyele+= -1.5 * texts;
  }

pyele+= -1.5 * texts;

/*---------------------------------------------------------------------
* randbedingungen z88i2.txt
*--------------------------------------------------------------------*/
if (ICFLAG == 2)
  {
  fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88RBD");
  fprintf(fdxf,"\n 10\n" PG,pxele);
  fprintf(fdxf,"\n 20\n" PG,pyele);
  fprintf(fdxf,"\n 30\n0.0");
  fprintf(fdxf,"\n 40\n" PG,texts);
  fprintf(fdxf,"\n  1\nZ88I2.TXT " PD,nrb);
  pyele+= -1.5 * texts;

  for(i= 1;i <= nrb;i++)
    { 
    fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88RBD");
    fprintf(fdxf,"\n 10\n" PG,pxele);
    fprintf(fdxf,"\n 20\n" PG,pyele);
    fprintf(fdxf,"\n 30\n0.0");
    fprintf(fdxf,"\n 40\n" PG,texts);
    fprintf(fdxf,"\n  1\nRBD " PDB PDB PDB PDB PG,i,nkn[i],ifg[i],irflag[i],wert[i]);
    pyele+= -1.5 * texts;
    }
  }

pyele+= -3.0 * texts;

/*---------------------------------------------------------------------
* flaechenlasten z88i5.txt
*--------------------------------------------------------------------*/
if (ICFLAG == 2)
  {
  fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88FLA");
  fprintf(fdxf,"\n 10\n" PG,pxele);
  fprintf(fdxf,"\n 20\n" PG,pyele);
  fprintf(fdxf,"\n 30\n0.0");
  fprintf(fdxf,"\n 40\n" PG,texts);
  fprintf(fdxf,"\n  1\nZ88I5.TXT " PD,npr);
  pyele+= -1.5 * texts;

  if(iqflag == 1)
    {
    for(j= 1;j <= npr;j++)
      { 
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88FLA");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 40\n" PG,texts);

/*======================================================================
* Elementtypen 7, 8, 14, 15
*=====================================================================*/
      if(ityp[nep[j]]== 7  || ityp[nep[j]]== 8 ||
         ityp[nep[j]]== 14 || ityp[nep[j]]== 15) 
        {
        fprintf(fdxf,"\n  1\nFLA " PDB PDB PGB PGB PDB PDB PD,
        j,nep[j],pres[j],tr1[j],
        noi[noffs[j]   ],noi[noffs[j] +1],noi[noffs[j] +2]);  
        }

/*======================================================================
* Elementtyp 10 u. 21
*=====================================================================*/
      if(ityp[nep[j]]== 10 || ityp[nep[j]]== 21) 
        {
        fprintf(fdxf,"\n  1\nFLA " PDB PDB PGB PGB PGB PDB PDB PDB PDB PDB PDB PDB PD,
        j,nep[j],pres[j],tr1[j],tr2[j],
        noi[noffs[j]   ], noi[noffs[j] +1], 
        noi[noffs[j] +2], noi[noffs[j] +3], 
        noi[noffs[j] +4], noi[noffs[j] +5],
        noi[noffs[j] +6], noi[noffs[j] +7]); 
        }

/*======================================================================
* Elementtyp 22
*=====================================================================*/
      if(ityp[nep[j]]== 22) 
        {
        fprintf(fdxf,"\n  1\nFLA "  PDB PDB PGB PGB PGB PDB PDB PDB PDB PDB PD,
        j,nep[j],pres[j],tr1[j],tr2[j],
        noi[noffs[j]   ], noi[noffs[j] +1], 
        noi[noffs[j] +2], noi[noffs[j] +3], 
        noi[noffs[j] +4], noi[noffs[j] +5]); 
        }

/*======================================================================
* Elementtyp 1
*=====================================================================*/
      if(ityp[nep[j]]== 1) 
        {
        fprintf(fdxf,"\n  1\nFLA " PDB PDB PGB PGB PGB PDB PDB PDB PD,
        j,nep[j],pres[j],tr1[j],tr2[j],
        noi[noffs[j]   ], noi[noffs[j] +1], 
        noi[noffs[j] +2], noi[noffs[j] +3]); 
        }

/*======================================================================
* Elementtyp 17
*=====================================================================*/
      if(ityp[nep[j]]== 17) 
        {
        fprintf(fdxf,"\n  1\nFLA " PDB PDB PGB PDB PDB PD,
        j,nep[j],pres[j],
        noi[noffs[j]   ], noi[noffs[j] +1], noi[noffs[j] +2]); 
        }

/*======================================================================
* Elementtyp 16
*=====================================================================*/
      if(ityp[nep[j]]== 16) 
        {
        fprintf(fdxf,"\n  1\nFLA "  PDB PDB PGB PDB PDB PDB PDB PDB PD,
        j,nep[j],pres[j],
        noi[noffs[j]   ], noi[noffs[j] +1], 
        noi[noffs[j] +2], noi[noffs[j] +3], 
        noi[noffs[j] +4], noi[noffs[j] +5]); 
        }

/*======================================================================
* Elementtypen 11 und 12
*=====================================================================*/
      if(ityp[nep[j]]== 11 || ityp[nep[j]]== 12) 
        {
        fprintf(fdxf,"\n  1\nFLA " PDB PDB PGB PGB PDB PDB PDB PD,
        j,nep[j],pres[j],tr1[j],
        noi[noffs[j]   ], noi[noffs[j] +1], 
        noi[noffs[j] +2], noi[noffs[j] +3]); 
        }

/*======================================================================
* Elementtyp 18,19,20,23 und 24
*=====================================================================*/
      if(ityp[nep[j]]== 18 || ityp[nep[j]]== 19 || ityp[nep[j]]== 20 ||
         ityp[nep[j]]== 23 || ityp[nep[j]]== 24) 
        {
        fprintf(fdxf,"\n  1\nFLA " PDB PDB PG,j,nep[j],pres[j]); 
        }

      pyele+= -1.5 * texts;
      }  // Ende Flaechenlastschleife
    }  // Ende iqflag == 1
  }

/***********************************************************************
* punkte setzen
***********************************************************************/
for(i= 1; i <= nkp; i++)
  {
  fprintf(fdxf,"\n  0\nPOINT\n  8\nZ88PKT");
  fprintf(fdxf,"\n 10\n" PG,x[i]);
  fprintf(fdxf,"\n 20\n" PG,y[i]);
  fprintf(fdxf,"\n 30\n" PG,z[i]);

  fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88KNR");
  fprintf(fdxf,"\n 10\n" PG,x[i]);
  fprintf(fdxf,"\n 20\n" PG,y[i]);
  fprintf(fdxf,"\n 30\n" PG,z[i]);
  fprintf(fdxf,"\n 40\n" PG,texts);
  fprintf(fdxf,"\n  1\nP " PD,i);
  }

/***********************************************************************
* grosse elementschleife fuer element-infos
***********************************************************************/
wlog88x(0,LOG_SELE);
wrim88x(0,TX_SELE);

for(k= 1; k <= ne; k++)
  {
 
/*---------------------------------------------------------------------
* 8 punkte fuer 8-k hexaeder
*--------------------------------------------------------------------*/
  if(ityp[k] == 1)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 8; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.5*(px[1]+px[7]);
      pyele= 0.5*(py[1]+py[7]);
      pzele= 0.5*(pz[1]+pz[7]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n" PG,pzele);
      fprintf(fdxf,"\n 40\n" PG,texts);
      fprintf(fdxf,"\n  1\nFE " PDB PD,k,ityp[k]);
      }

    }

/*---------------------------------------------------------------------
* 20 punkte fuer 20-k hexaeder
*--------------------------------------------------------------------*/
  else if(ityp[k] == 10)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 20; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   entweder element-infos  schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.5*(px[1]+px[7]);
      pyele= 0.5*(py[1]+py[7]);
      pzele= 0.5*(pz[1]+pz[7]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n" PG,pzele);
      fprintf(fdxf,"\n 40\n" PG,texts);
      fprintf(fdxf,"\n  1\nFE " PDB PD,k,ityp[k]);
      }

/*=====================================================================
*   .. oder superelement-infos knoten schreiben (Z88NI.TXT)
*====================================================================*/
    else
      {
      pxele= 0.5*(px[1]+px[7]);
      pyele= 0.5*(py[1]+py[7]);
      pzele= 0.5*(pz[1]+pz[7]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n" PG,pzele);
      fprintf(fdxf,"\n 40\n" PG,texts);
      fprintf(fdxf,"\n  1\nSE " PDB PDB PDB PDB PCB PDB PCB PDB PC,
      k,ityp[k],itypfe[k],jel[k],cjmode[k],iel[k],cimode[k],kel[k],ckmode[k]);
      }

    }

/*---------------------------------------------------------------------
* 16 punkte fuer 16-k Volumenschalenelement
*--------------------------------------------------------------------*/
  else if(ityp[k] == 21)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 16; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   entweder element-infos  schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.5*(px[1]+px[7]);
      pyele= 0.5*(py[1]+py[7]);
      pzele= 0.5*(pz[1]+pz[7]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n" PG,pzele);
      fprintf(fdxf,"\n 40\n" PG,texts);
      fprintf(fdxf,"\n  1\nFE " PDB PD,k,ityp[k]);
      }

/*=====================================================================
*   .. oder superelement-infos knoten schreiben (Z88NI.TXT)
*====================================================================*/
    else
      {
      pxele= 0.5*(px[1]+px[11]);
      pyele= 0.5*(py[1]+py[11]);
      pzele= 0.5*(pz[1]+pz[11]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n" PG,pzele);
      fprintf(fdxf,"\n 40\n" PG,texts);
      fprintf(fdxf,"\n  1\nSE " PDB PDB PDB PDB PCB PDB PCB PDB PC,
      k,ityp[k],itypfe[k],jel[k],cjmode[k],iel[k],cimode[k],kel[k],ckmode[k]);
      }
    }

/*---------------------------------------------------------------------
* 12 punkte fuer 12-k Volumenschalenelement
*--------------------------------------------------------------------*/
  else if(ityp[k] == 22)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 12; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   entweder element-infos  schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.5*(px[1]+px[11]);
      pyele= 0.5*(py[1]+py[11]);
      pzele= 0.5*(pz[1]+pz[11]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n" PG,pzele);
      fprintf(fdxf,"\n 40\n" PG,texts);
      fprintf(fdxf,"\n  1\nFE " PDB PD,k,ityp[k]);
      }
    }

/*----------------------------------------------------------------------
* 2 punkte fuer ebenen stab, ebener balken
*---------------------------------------------------------------------*/
  else if(ityp[k]== 9 || ityp[k]== 13)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 2; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.5*(px[1]+px[2]);
      pyele= 0.5*(py[1]+py[2]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 40\n" PG,texts);
      fprintf(fdxf,"\n  1\nFE " PDB PD,k,ityp[k]);
      }

    }

/*----------------------------------------------------------------------
* 2 punkte fuer raeuml stab, welle, raeuml balken
*---------------------------------------------------------------------*/
  else if(ityp[k]== 2 || ityp[k]== 4 || ityp[k]== 5 || ityp[k]== 25)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 2; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.5*(px[1]+px[2]);
      pyele= 0.5*(py[1]+py[2]);
      pzele= 0.5*(pz[1]+pz[2]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n" PG,pzele);
      fprintf(fdxf,"\n 40\n" PG,texts);
      fprintf(fdxf,"\n  1\nFE " PDB PD,k,ityp[k]);
      }

    }

/*----------------------------------------------------------------------
* 6 punkte fuer 6-k scheibe bzw. platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 3  || ityp[k]== 14 || ityp[k]== 15 ||  ityp[k]== 18)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 6; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.333*(px[1]+px[2]+px[3]);
      pyele= 0.333*(py[1]+py[2]+py[3]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 40\n" PG,texts);
      fprintf(fdxf,"\n  1\nFE " PDB PD,k,ityp[k]);
      }

    }

/*----------------------------------------------------------------------
* 6 punkte fuer 6-k schale
*---------------------------------------------------------------------*/
  else if(ityp[k]== 24)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 6; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.333*(px[1]+px[2]+px[3]);
      pyele= 0.333*(py[1]+py[2]+py[3]);
      pzele= 0.333*(pz[1]+pz[2]+pz[3]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n" PG,pzele);
      fprintf(fdxf,"\n 40\n" PG,texts);
      fprintf(fdxf,"\n  1\nFE " PDB PD,k,ityp[k]);
      }

    }

/*----------------------------------------------------------------------
* 3 punkte fuer 3-k torus 
*---------------------------------------------------------------------*/
  else if(ityp[k]== 6)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 3; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.333*(px[1]+px[2]+px[3]);
      pyele= 0.333*(py[1]+py[2]+py[3]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 40\n" PG,texts);
      fprintf(fdxf,"\n  1\nFE " PDB PD,k,ityp[k]);
      }

    }

/*---------------------------------------------------------------------
* 8 punkte fuer 8-k serendipity-scheibe & -torus bzw. platte
*--------------------------------------------------------------------*/
  else if(ityp[k] == 7 || ityp[k] == 8 || ityp[k] == 20)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 8; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   entweder element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.5*(px[1]+px[3]);
      pyele= 0.5*(py[1]+py[3]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 40\n" PG,texts);
      fprintf(fdxf,"\n  1\nFE " PDB PD,k,ityp[k]);
      }

/*=====================================================================
*   .. oder superelement-infos schreiben (Z88NI.TXT)
*====================================================================*/
    else
      {
      pxele= 0.5*(px[1]+px[3]);
      pyele= 0.5*(py[1]+py[3]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 40\n" PG,texts);
      fprintf(fdxf,"\n  1\nSE " PDB PDB PDB PDB PCB PDB PC,
      k,ityp[k],itypfe[k],jel[k],cjmode[k],iel[k],cimode[k]);
      }

    }

/*---------------------------------------------------------------------
* 8 punkte fuer 8-k schale
*--------------------------------------------------------------------*/
  else if(ityp[k] == 23)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 8; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   entweder element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.5*(px[1]+px[3]);
      pyele= 0.5*(py[1]+py[3]);
      pzele= 0.5*(pz[1]+pz[3]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n" PG,pzele);
      fprintf(fdxf,"\n 40\n" PG,texts);
      fprintf(fdxf,"\n  1\nFE " PDB PD,k,ityp[k]);
      }

    }

/*----------------------------------------------------------------------
* 12 punkte fuer 12-k serendipity-scheibe & -torus
*---------------------------------------------------------------------*/
  else if(ityp[k]== 11 || ityp[k]== 12)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 12; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   entweder element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.5*(px[1]+px[3]);
      pyele= 0.5*(py[1]+py[3]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 40\n" PG,texts);
      fprintf(fdxf,"\n  1\nFE " PDB PD,k,ityp[k]);
      }

/*=====================================================================
*   .. oder superelement-infos schreiben (Z88NI.TXT)
*====================================================================*/
    else
      {
      pxele= 0.5*(px[1]+px[3]);
      pyele= 0.5*(py[1]+py[3]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 40\n" PG,texts);
      fprintf(fdxf,"\n  1\nSE " PDB PDB PDB PDB PCB PDB PC,
      k,ityp[k],itypfe[k],jel[k],cjmode[k],iel[k],cimode[k]);
      }

    }

/*----------------------------------------------------------------------
* 16 punkte fuer 16-k platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 19)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 16; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.5*(px[1]+px[16]);
      pyele= 0.5*(py[1]+py[16]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 40\n" PG,texts);
      fprintf(fdxf,"\n  1\nFE " PDB PD,k,ityp[k]);
      }

    }

/*----------------------------------------------------------------------
* 4 punkte fuer 4-k tetraeder
*---------------------------------------------------------------------*/
  else if(ityp[k]== 17)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 4; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.25*(px[1]+px[2]+px[3]+px[4]);
      pyele= 0.25*(py[1]+py[2]+py[3]+py[4]);
      pzele= 0.25*(pz[1]+pz[2]+pz[3]+pz[4]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n" PG,pzele);
      fprintf(fdxf,"\n 40\n" PG,texts);
      fprintf(fdxf,"\n  1\nFE " PDB PD,k,ityp[k]);
      }

    }

/*----------------------------------------------------------------------
* 10 punkte fuer 10-k tetraeder
*---------------------------------------------------------------------*/
  else if(ityp[k]== 16)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 10; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   element-infos schreiben (Z88I1.TXT)
*====================================================================*/
    if(ICFLAG == 1 || ICFLAG == 2)
      {
      pxele= 0.25*(px[1]+px[2]+px[3]+px[4]);
      pyele= 0.25*(py[1]+py[2]+py[3]+py[4]);
      pzele= 0.25*(pz[1]+pz[2]+pz[3]+pz[4]);
      fprintf(fdxf,"\n  0\nTEXT\n  8\nZ88EIO");
      fprintf(fdxf,"\n 10\n" PG,pxele);
      fprintf(fdxf,"\n 20\n" PG,pyele);
      fprintf(fdxf,"\n 30\n" PG,pzele);
      fprintf(fdxf,"\n 40\n" PG,texts);
      fprintf(fdxf,"\n  1\nFE " PDB PD,k,ityp[k]);
      }

    }

  }

/***********************************************************************
* grosse elementschleife fuer linien
***********************************************************************/
for(k= 1; k <= ne; k++)
  {
 
/*---------------------------------------------------------------------
* 8 punkte fuer 8-k hexaeder
*--------------------------------------------------------------------*/
  if(ityp[k] == 1)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 8; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 12; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n" PG,px[i1point[j]]);
      fprintf(fdxf,"\n 20\n" PG,py[i1point[j]]);
      fprintf(fdxf,"\n 30\n" PG,pz[i1point[j]]);
      fprintf(fdxf,"\n 11\n" PG,px[j1point[j]]);
      fprintf(fdxf,"\n 21\n" PG,py[j1point[j]]);
      fprintf(fdxf,"\n 31\n" PG,pz[j1point[j]]);
      }

    }

/*---------------------------------------------------------------------
* 20 punkte fuer 20-k hexaeder
*--------------------------------------------------------------------*/
  else if(ityp[k] == 10)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 20; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 24; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n" PG,px[i10point[j]]);
      fprintf(fdxf,"\n 20\n" PG,py[i10point[j]]);
      fprintf(fdxf,"\n 30\n" PG,pz[i10point[j]]);
      fprintf(fdxf,"\n 11\n" PG,px[j10point[j]]);
      fprintf(fdxf,"\n 21\n" PG,py[j10point[j]]);
      fprintf(fdxf,"\n 31\n" PG,pz[j10point[j]]);
      }

    }

/*---------------------------------------------------------------------
* 16 punkte fuer 16-k volumenschalenelement
*--------------------------------------------------------------------*/
  else if(ityp[k] == 21)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 16; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 20; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n" PG,px[i21point[j]]);
      fprintf(fdxf,"\n 20\n" PG,py[i21point[j]]);
      fprintf(fdxf,"\n 30\n" PG,pz[i21point[j]]);
      fprintf(fdxf,"\n 11\n" PG,px[j21point[j]]);
      fprintf(fdxf,"\n 21\n" PG,py[j21point[j]]);
      fprintf(fdxf,"\n 31\n" PG,pz[j21point[j]]);
      }

    }

/*---------------------------------------------------------------------
* 12 punkte fuer 12-k volumenschalenelement
*--------------------------------------------------------------------*/
  else if(ityp[k] == 22)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 12; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 15; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n" PG,px[i22point[j]]);
      fprintf(fdxf,"\n 20\n" PG,py[i22point[j]]);
      fprintf(fdxf,"\n 30\n" PG,pz[i22point[j]]);
      fprintf(fdxf,"\n 11\n" PG,px[j22point[j]]);
      fprintf(fdxf,"\n 21\n" PG,py[j22point[j]]);
      fprintf(fdxf,"\n 31\n" PG,pz[j22point[j]]);
      }
    }

/*----------------------------------------------------------------------
* 2 punkte fuer ebenen stab, ebener balken
*---------------------------------------------------------------------*/
  else if(ityp[k]== 9 || ityp[k]== 13)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 2; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
    fprintf(fdxf,"\n 10\n" PG,px[1]);
    fprintf(fdxf,"\n 20\n" PG,py[1]);
    fprintf(fdxf,"\n 30\n0.0");
    fprintf(fdxf,"\n 11\n" PG,px[2]);
    fprintf(fdxf,"\n 21\n" PG,py[2]);
    fprintf(fdxf,"\n 31\n0.0");

    }

/*----------------------------------------------------------------------
* 2 punkte fuer raeuml stab, welle, raeuml balken
*---------------------------------------------------------------------*/
  else if(ityp[k]== 2 || ityp[k]== 4 || ityp[k]== 5 || ityp[k]== 25)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 2; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
    fprintf(fdxf,"\n 10\n" PG,px[1]);
    fprintf(fdxf,"\n 20\n" PG,py[1]);
    fprintf(fdxf,"\n 30\n" PG,pz[1]);
    fprintf(fdxf,"\n 11\n" PG,px[2]);
    fprintf(fdxf,"\n 21\n" PG,py[2]);
    fprintf(fdxf,"\n 31\n" PG,pz[2]);

    }

/*----------------------------------------------------------------------
* 6 punkte fuer 6-k scheibe bzw. platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 3 || ityp[k]== 14 || ityp[k]== 15 || ityp[k]== 18)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 6; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 6; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n" PG,px[i3point[j]]);
      fprintf(fdxf,"\n 20\n" PG,py[i3point[j]]);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 11\n" PG,px[j3point[j]]);
      fprintf(fdxf,"\n 21\n" PG,py[j3point[j]]);
      fprintf(fdxf,"\n 31\n0.0");
      }

    }

/*----------------------------------------------------------------------
* 6 punkte fuer 6-k schale
*---------------------------------------------------------------------*/
  else if(ityp[k]== 24)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 6; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 6; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n" PG,px[i3point[j]]);
      fprintf(fdxf,"\n 20\n" PG,py[i3point[j]]);
      fprintf(fdxf,"\n 30\n" PG,pz[i3point[j]]);
      fprintf(fdxf,"\n 11\n" PG,px[j3point[j]]);
      fprintf(fdxf,"\n 21\n" PG,py[j3point[j]]);
      fprintf(fdxf,"\n 31\n" PG,pz[j3point[j]]);
      }

    }

/*----------------------------------------------------------------------
* 3 punkte fuer 3-k torus 
*---------------------------------------------------------------------*/
  else if(ityp[k]== 6)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 3; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 3; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n" PG,px[i6point[j]]);
      fprintf(fdxf,"\n 20\n" PG,py[i6point[j]]);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 11\n" PG,px[j6point[j]]);
      fprintf(fdxf,"\n 21\n" PG,py[j6point[j]]);
      fprintf(fdxf,"\n 31\n0.0");
      }

    }

/*---------------------------------------------------------------------
* 8 punkte fuer 8-k serendipity-scheibe & -torus bzw. platte
*--------------------------------------------------------------------*/
  else if(ityp[k] == 7 || ityp[k] == 8 || ityp[k]== 20)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 8; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 8; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n" PG,px[i7point[j]]);
      fprintf(fdxf,"\n 20\n" PG,py[i7point[j]]);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 11\n" PG,px[j7point[j]]);
      fprintf(fdxf,"\n 21\n" PG,py[j7point[j]]);
      fprintf(fdxf,"\n 31\n0.0");
      }

    }

/*---------------------------------------------------------------------
* 8 punkte fuer 8-k schale
*--------------------------------------------------------------------*/
  else if(ityp[k] == 23)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 8; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 8; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n" PG,px[i7point[j]]);
      fprintf(fdxf,"\n 20\n" PG,py[i7point[j]]);
      fprintf(fdxf,"\n 30\n" PG,pz[i7point[j]]);
      fprintf(fdxf,"\n 11\n" PG,px[j7point[j]]);
      fprintf(fdxf,"\n 21\n" PG,py[j7point[j]]);
      fprintf(fdxf,"\n 31\n" PG,pz[j7point[j]]);
      }

    }

/*----------------------------------------------------------------------
* 12 punkte fuer 12-k serendipity-scheibe & -torus
*---------------------------------------------------------------------*/
  else if(ityp[k]== 11 || ityp[k]== 12)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 12; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 12; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n" PG,px[i11point[j]]);
      fprintf(fdxf,"\n 20\n" PG,py[i11point[j]]);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 11\n" PG,px[j11point[j]]);
      fprintf(fdxf,"\n 21\n" PG,py[j11point[j]]);
      fprintf(fdxf,"\n 31\n0.0");
      }

    }

/*---------------------------------------------------------------------
* 16 punkte fuer 16-k lagrange platte
*--------------------------------------------------------------------*/
  else if(ityp[k] == 19)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 16; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 16; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n" PG,px[i19point[j]]);
      fprintf(fdxf,"\n 20\n" PG,py[i19point[j]]);
      fprintf(fdxf,"\n 30\n0.0");
      fprintf(fdxf,"\n 11\n" PG,px[j19point[j]]);
      fprintf(fdxf,"\n 21\n" PG,py[j19point[j]]);
      fprintf(fdxf,"\n 31\n0.0");
      }

    }

/*---------------------------------------------------------------------
* 4 punkte fuer 4-k tetraeder
*--------------------------------------------------------------------*/
  if(ityp[k] == 17)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 4; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 6; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n" PG,px[i17point[j]]);
      fprintf(fdxf,"\n 20\n" PG,py[i17point[j]]);
      fprintf(fdxf,"\n 30\n" PG,pz[i17point[j]]);
      fprintf(fdxf,"\n 11\n" PG,px[j17point[j]]);
      fprintf(fdxf,"\n 21\n" PG,py[j17point[j]]);
      fprintf(fdxf,"\n 31\n" PG,pz[j17point[j]]);
      }

    }

/*---------------------------------------------------------------------
* 10 punkte fuer 10-k tetraeder
*--------------------------------------------------------------------*/
  if(ityp[k] == 16)
    {

/*=====================================================================
*   koordinaten holen
*====================================================================*/
    for(i= 1; i <= 10; i++)
      {
      px[i]= x[koi[koffs[k]+i-1]];
      py[i]= y[koi[koffs[k]+i-1]];
      pz[i]= z[koi[koffs[k]+i-1]];
      }

/*=====================================================================
*   linien ziehen
*====================================================================*/
    for(j= 1; j <= 12; j++)
      {
      fprintf(fdxf,"\n  0\nLINE\n  8\nZ88NET");
      fprintf(fdxf,"\n 10\n" PG,px[i16point[j]]);
      fprintf(fdxf,"\n 20\n" PG,py[i16point[j]]);
      fprintf(fdxf,"\n 30\n" PG,pz[i16point[j]]);
      fprintf(fdxf,"\n 11\n" PG,px[j16point[j]]);
      fprintf(fdxf,"\n 21\n" PG,py[j16point[j]]);
      fprintf(fdxf,"\n 31\n" PG,pz[j16point[j]]);
      }

    }


  } // Ende Elementschleife

/***********************************************************************
* file schliessen
***********************************************************************/
fprintf(fdxf,"\n  0\nENDSEC\n  0\nEOF\n");
fclose(fdxf);
 
/***********************************************************************
* Ende Z88TX
***********************************************************************/
wlog88x(0,LOG_EXITZ88TX);
wrim88x(0,TX_EXITZ88TX);
return(0);
}

