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
* wria88r.c beschreibt Z88O0.TXT, oeffnet und schliesst dieses File
* 14.12.2015 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fprintf,fwrite */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fprintf,fwrite */
#endif

/***********************************************************************
* Fuer Windows und GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88r.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fprintf,fwrite */
#endif

/***********************************************************************
* Leseformate
***********************************************************************/
#define NLB "\n "
#define NLE "\n"

#ifdef FR_XINT
#define PDB "%5d "
#define PD2B "%5d  "
#define PDE "%5d"
#define B22D "  %2d"
#define P2DB "%2d "
#define PD "%d"
#define PDL "%d "
#endif

#ifdef FR_XLONG
#define PDB "%5ld "
#define PD2B "%5ld  "
#define PDE "%5ld"
#define B22D "  %2ld"
#define P2DB "%2ld "
#define PD "%ld"
#define PDL "%ld "
#endif

#ifdef FR_XLOLO
#define PDB "%5lld "
#define PD2B "%5lld  "
#define PDE "%5lld"
#define B22D "  %2lld"
#define P2DB "%2lld "
#define PD "%lld"
#define PDL "%lld "
#endif

#ifdef FR_XDOUB
#define P13E "   %+#13.5lE"
#define B213E "  %+#13.5lE"
#define B513E "     %+#13.5lE"
#define P13EB "%+#13.5lE "
#define P11EB "%+#11.3lE "
#define PGB "%lg "
#endif

#ifdef FR_XQUAD
#define P13E "   %+#13.5LE"
#define B213E "  %+#13.5LE"
#define B513E "     %+#13.5LE"
#define P13EB "%+#13.5LE "
#define P11EB "%+#11.3LE "
#define PGB "%Lg "
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88r(FR_INT4,int);
int wlog88r(FR_INT4,int);

/***********************************************************************
* hier beginnt Function wria88r
***********************************************************************/
int wria88r(void)
{
extern FILE *fo0,*fwlo;
extern char co0[];

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

extern FR_INT4AY koi;
extern FR_INT4AY ip;
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
extern FR_INT4AY intord;
extern FR_INT4AY intos;

extern FR_INT4 ndim,nkp,ne,nfg,kflag,ibflag,ipflag,iqflag,ihflag;
extern FR_INT4 LANG,ifnili,mmat,mint,melp;

FR_INT4 i,nkoi;

/*----------------------------------------------------------------------
* Start Function: Oeffnen File
*---------------------------------------------------------------------*/
wlog88r(0,LOG_BWRIA88F);

fo0= fopen(co0,"w+");
if(fo0 == NULL)
  {
  wlog88r(0,LOG_NOO0);
  fclose(fwlo);
  return(AL_NOO0);
  }

rewind(fo0);

/***********************************************************************
* nkoi ist Anzahl der echt benutzten Elemente in koi; 19 geht immer
***********************************************************************/
nkoi= koffs[ne] + 19;

/***********************************************************************
* Beschreiben des Files Z88O0.TXT
***********************************************************************/
wrim88r(0,TX_WRIO0);
wlog88r(0,LOG_WRIO0);

/*----------------------------------------------------------------------
* Allgemeine Strukturdaten
*---------------------------------------------------------------------*/
if(LANG == 1)
{
fprintf(fo0,"Ausgabedatei Z88O0.TXT: Strukturdaten, erzeugt mit Z88R V15OS\n");
fprintf(fo0,"                        *************\n");

fprintf(fo0,"\nStrukturdaten: Dimension=" PD " Knoten=" PD " Elemente=" PD " FG=" PD " KFLAG=" PD, ndim,nkp,ne,nfg,kflag);

fprintf(fo0,"\nSteuerflags: IBFLAG=" PD " IPFLAG=" PD " IQFLAG=" PD " IHFLAG=" PD,
  ibflag,ipflag,iqflag,ihflag);
}

if(LANG == 2)
{
fprintf(fo0,"output file Z88O0.TXT: structure info, produced by Z88R V15OS\n");
fprintf(fo0,"                       **************\n");

fprintf(fo0,"\nstructure data: Dimension=" PD " nodes=" PD " elements=" PD " DOF=" PD " KFLAG=" PD, ndim,nkp,ne,nfg,kflag);

fprintf(fo0,"\nflags: IBFLAG=" PD " IPFLAG=" PD " IQFLAG=" PD " IHFLAG=" PD,
  ibflag,ipflag,iqflag,ihflag);
}

/*----------------------------------------------------------------------
* Koordinaten
*---------------------------------------------------------------------*/
if(LANG == 1)
{
fprintf(fo0,"\n\nKoordinaten :");
fprintf(fo0,
"\n\nKnoten    FG          X               Y               Z");
}

if(LANG == 2)
{
fprintf(fo0,"\n\ncoordinates :");
fprintf(fo0,
"\n\nnode      DOF         X               Y               Z");
}

for(i = 1;i <= nkp;i++)
  {
  fprintf(fo0,NLB PDB PD2B P13E P13E P13E,i,ifrei[i],x[i],y[i],z[i]);
  }


if(LANG == 1)
{
fprintf(fo0,"\n\nKoinzidenz (2 Zeilen pro Element) :");
fprintf(fo0,"\n\nE- Nr.   Typ");
}

if(LANG == 2)
{
fprintf(fo0,"\n\nelement information (2 lines per element) :");
fprintf(fo0,"\n\ne- no.   type");
}

fprintf(fo0,
"\n    i1    i2    i3    i4    i5    i6    i7    i8    i9   i10\
   i11   i12   i13   i14   i15   i16   i17   i18   i19   i20");

/*----------------------------------------------------------------------
* Koinzidenz
*---------------------------------------------------------------------*/
for(i = 1;i <= ne;i++)
  {
        
/*----------------------------------------------------------------------
* Ausschreiben Koinzidenz fuer Elemente 1,7,8,20 & 23
*---------------------------------------------------------------------*/
  if(ityp[i] == 1  || ityp[i] == 7 || ityp[i] == 8 ||
     ityp[i] == 20 || ityp[i] == 23)
    {
    fprintf(fo0,NLB PDB PDB NLB PDB PDB PDB PDB PDB PDB PDB PDB NLE,
    i,ityp[i],
    koi[koffs[i]  ],koi[koffs[i]+1],
    koi[koffs[i]+2],koi[koffs[i]+3],
    koi[koffs[i]+4],koi[koffs[i]+5],
    koi[koffs[i]+6],koi[koffs[i]+7]); 
    }
    
/*----------------------------------------------------------------------
* Ausschreiben Koinzidenz fuer Elemente 2, 4, 5 , 9 , 13 & 25
*---------------------------------------------------------------------*/
  if(ityp[i] == 2 || ityp[i] == 4  || ityp[i] == 5 ||
     ityp[i] == 9 || ityp[i] == 13 || ityp[i] == 25)
    { 
    fprintf(fo0,NLB PDB PDB NLB PDB PDB NLE,i,ityp[i],
    koi[koffs[i]  ],koi[koffs[i]+1]);
    }
    
/*----------------------------------------------------------------------
* Ausschreiben Koinzidenz fuer Element 3, 14, 15, 18 & 24
*---------------------------------------------------------------------*/
  if(ityp[i] == 3  || ityp[i] == 14 || ityp[i]== 15 || 
     ityp[i] == 18 || ityp[i] == 24)
    {
    fprintf(fo0,NLB PDB PDB NLB PDB PDB PDB PDB PDB PDB NLE,
    i,ityp[i],
    koi[koffs[i]  ],koi[koffs[i]+1],
    koi[koffs[i]+2],koi[koffs[i]+3],
    koi[koffs[i]+4],koi[koffs[i]+5]);
    }
    
/*----------------------------------------------------------------------
* Ausschreiben Koinzidenz fuer Element 6
*---------------------------------------------------------------------*/
  if(ityp[i] == 6)
    {
    fprintf(fo0,NLB PDB PDB NLB PDB PDB PDB NLE,
    i,ityp[i],
    koi[koffs[i]  ],koi[koffs[i]+1],
    koi[koffs[i]+2]);
    }

/*----------------------------------------------------------------------
* Ausschreiben Koinzidenz fuer Element 21
*---------------------------------------------------------------------*/
  if(ityp[i] == 21)
    {
    fprintf(fo0,NLB PDB PDB NLB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB,
    i,ityp[i],
    koi[koffs[i]  ],koi[koffs[i]+1],
    koi[koffs[i]+2],koi[koffs[i]+3],
    koi[koffs[i]+4],koi[koffs[i]+5],
    koi[koffs[i]+6],koi[koffs[i]+7], 
    koi[koffs[i]+8],koi[koffs[i]+9]); 

    fprintf(fo0,
    PDB PDB PDB PDB PDB PDB NLE,
    koi[koffs[i]+10],koi[koffs[i]+11], 
    koi[koffs[i]+12],koi[koffs[i]+13], 
    koi[koffs[i]+14],koi[koffs[i]+15]); 
    }

/*----------------------------------------------------------------------
* Ausschreiben Koinzidenz fuer Element 10
*---------------------------------------------------------------------*/
  if(ityp[i] == 10)
    {
    fprintf(fo0,NLB PDB PDB NLB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB,
    i,ityp[i],
    koi[koffs[i]  ],koi[koffs[i]+1],
    koi[koffs[i]+2],koi[koffs[i]+3],
    koi[koffs[i]+4],koi[koffs[i]+5],
    koi[koffs[i]+6],koi[koffs[i]+7], 
    koi[koffs[i]+8],koi[koffs[i]+9]); 

    fprintf(fo0,
    PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB NLE,
    koi[koffs[i]+10],koi[koffs[i]+11], 
    koi[koffs[i]+12],koi[koffs[i]+13], 
    koi[koffs[i]+14],koi[koffs[i]+15], 
    koi[koffs[i]+16],koi[koffs[i]+17], 
    koi[koffs[i]+18],koi[koffs[i]+19]); 
    }
    
/*----------------------------------------------------------------------
* Ausschreiben Koinzidenz fuer Elemente 11 & 12 & 22
*---------------------------------------------------------------------*/
  if(ityp[i] == 11 || ityp[i] == 12 || ityp[i] == 22)
    {
    fprintf(fo0,NLB PDB PDB NLB PDB PDB PDB PDB PDB PDB,
    i,ityp[i],
    koi[koffs[i]  ],koi[koffs[i]+1],
    koi[koffs[i]+2],koi[koffs[i]+3],
    koi[koffs[i]+4],koi[koffs[i]+5]);

    fprintf(fo0,PDB PDB PDB PDB PDB PDB NLE,
    koi[koffs[i]+6],koi[koffs[i]+7], 
    koi[koffs[i]+8],koi[koffs[i]+9], 
    koi[koffs[i]+10],koi[koffs[i]+11]); 
    }

/*----------------------------------------------------------------------
* Ausschreiben Koinzidenz fuer Elemente 16
*---------------------------------------------------------------------*/
  if(ityp[i] == 16)
    {
    fprintf(fo0,NLB PDB PDB NLB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB NLE,
    i,ityp[i],
    koi[koffs[i]  ],koi[koffs[i]+1],
    koi[koffs[i]+2],koi[koffs[i]+3],
    koi[koffs[i]+4],koi[koffs[i]+5],
    koi[koffs[i]+6],koi[koffs[i]+7], 
    koi[koffs[i]+8],koi[koffs[i]+9]); 
    }

/*----------------------------------------------------------------------
* Ausschreiben Koinzidenz fuer Elemente 17
*---------------------------------------------------------------------*/
  if(ityp[i] == 17)
    {
    fprintf(fo0,NLB PDB PDB NLB PDB PDB PDB PDB NLE,i,ityp[i],
    koi[koffs[i]  ],koi[koffs[i]+1],
    koi[koffs[i]+2],koi[koffs[i]+3]);
    }
    
/*----------------------------------------------------------------------
* Ausschreiben Koinzidenz fuer Element 19
*---------------------------------------------------------------------*/
  if(ityp[i] == 19)
    {
    fprintf(fo0,NLB PDB PDB NLB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB,
    i,ityp[i],
    koi[koffs[i]  ],koi[koffs[i]+1],
    koi[koffs[i]+2],koi[koffs[i]+3],
    koi[koffs[i]+4],koi[koffs[i]+5],
    koi[koffs[i]+6],koi[koffs[i]+7], 
    koi[koffs[i]+8],koi[koffs[i]+9]); 

    fprintf(fo0,PDB PDB PDB PDB PDB PDB NLE,
    koi[koffs[i]+10],koi[koffs[i]+11], 
    koi[koffs[i]+12],koi[koffs[i]+13], 
    koi[koffs[i]+14],koi[koffs[i]+15]); 
    }

  }

fprintf(fo0,"\n");

/*----------------------------------------------------------------------
* Werkstoff- und Elementdaten, Integrationsordnungen
*---------------------------------------------------------------------*/
if(LANG == 1)
{
fprintf(fo0,"\nMaterial-Saetze=" PD,mmat);
for(i = 1; i <= mmat; i++)
  fprintf(fo0,"\nvon=" PD " bis=" PD " E-Modul=" PGB " nue=" PGB,
    ivon_mat[i],ibis_mat[i],emod[i],rnue[i]);

fprintf(fo0,"\n\nIntegrationsordnungs-Saetze=" PD,mint);
for(i = 1; i <= mint; i++)
  fprintf(fo0,"\nvon=" PD " bis=" PD " INTORD=" PD " INTOS=" PD,
    ivon_int[i],ibis_int[i],intord[i],intos[i]);

fprintf(fo0,"\n\nElementparameter-Saetze=" PD,melp);
for(i = 1; i <= melp; i++)
  fprintf(fo0,"\nvon=" PD " bis=" PD " QPARA=" PGB " IYY=" PGB " EYY=" PGB " IZZ=" PGB
  " EZZ=" PGB " IT=" PGB " WT=" PGB " IFBETI=" PDL " XCP=" PGB " YCP=" PGB " ZCP=" PGB "RKAP=" PGB,
    ivon_elp[i],ibis_elp[i],qpara[i],riyy[i],eyy[i],rizz[i],
    ezz[i],rit[i],wt[i],ifbeti[i],xcp[i],ycp[i],zcp[i],rkap[i]);
}

if(LANG == 2)
{
fprintf(fo0,"\nmaterial sets=" PD,mmat);
for(i = 1; i <= mmat; i++)
  fprintf(fo0,"\nfrom=" PD " to=" PD " E-Modul=" PGB " nue=" PGB,
    ivon_mat[i],ibis_mat[i],emod[i],rnue[i]);

fprintf(fo0,"\n\norder of integration sets=" PD,mint);
for(i = 1; i <= mint; i++)
  fprintf(fo0,"\nfrom=" PD " to=" PD " INTORD=" PD " INTOS=" PD,
    ivon_int[i],ibis_int[i],intord[i],intos[i]);

fprintf(fo0,"\n\nelement parameter sets=" PD,melp);
for(i = 1; i <= melp; i++)
    fprintf(fo0,"\nfrom=" PD " to=" PD " QPARA=" PGB " IYY=" PGB " EYY=" PGB " IZZ=" PGB
  " EZZ=" PGB " IT=" PGB " WT=" PGB " IFBETI=" PDL " XCP=" PGB " YCP=" PGB " ZCP=" PGB "RKAP=" PGB,
    ivon_elp[i],ibis_elp[i],qpara[i],riyy[i],eyy[i],rizz[i],
    ezz[i],rit[i],wt[i],ifbeti[i],xcp[i],ycp[i],zcp[i],rkap[i]);
}

fprintf(fo0,"\n");
  
/**********************************************************************
* erforderliche Dimensionierung anzeigen
**********************************************************************/
wrim88r(ip[nfg],TX_GSERF);
wrim88r(nkoi,TX_KOIERF);
wlog88r(ip[nfg],LOG_GSERF);
wlog88r(nkoi,LOG_KOIERF);

/**********************************************************************
* Schliessen des Files
**********************************************************************/
fclose(fo0);

wlog88r(0,LOG_EXITWRIA88F);
return(0);
}

