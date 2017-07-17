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
* wria88x.c beschreibt Z88I1.TXT,Z88NI.TXT,Z88I2.TXT und Z88I3.TXT
* und oeffnet und schliesst diese Files
* 14.12.2015 Rieg 
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88x.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fprintf,fwrite */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88x.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fprintf,fwrite */
#endif

/***********************************************************************
* Schreib/Leseformate
***********************************************************************/
#define NLB "\n "
#define NL "\n"

#define PC "%c"
#define PCB "%c "

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
#define PE13B "%+#13.5lE "
#define PE13 "%+#13.5lE"
#endif

#ifdef FR_XQUAD
#define PFB "%Lf "
#define PF "%Lf"
#define PE13B "%+#13.5LE "
#define PE13 "%+#13.5LE"
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88x(FR_INT4,int);
int wlog88x(FR_INT4,int);

/***********************************************************************
* hier beginnt Function wria88x
***********************************************************************/
int wria88x(void)
{
extern FILE *fz88,*fi2,*fi5,*fwlo;

extern FR_DOUBLEAY x;
extern FR_DOUBLEAY y;
extern FR_DOUBLEAY z;
extern FR_DOUBLEAY wert;
extern FR_DOUBLEAY pres;
extern FR_DOUBLEAY tr1;
extern FR_DOUBLEAY tr2;

extern FR_INT4AY koi;
extern FR_INT4AY koffs;
extern FR_INT4AY ifrei;
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

extern FR_INT4 ndim,nkp,ne,nfg,kflagss,kflag,iqflag,niflag;
extern FR_INT4 nrb,npr;
extern FR_INT4 LANG,ICFLAG;

extern char ci1[];
extern char ci2[];
extern char ci5[];
extern char cni[];

FR_INT4 i,j;

/*---------------------------------------------------------------------*
* Beschreiben Z88I1.TXT
*---------------------------------------------------------------------*/
if(ICFLAG == 4 || ICFLAG == 5)
  {
  wlog88x(0,LOG_WRII1);
  wrim88x(0,TX_WRII1);

/*---------------------------------------------------------------------*
* Oeffnen Z88I1.TXT
*---------------------------------------------------------------------*/
  fz88= fopen(ci1,"w");
  if(fz88 == NULL)
    {
    wlog88x(0,LOG_NOI1);
    fclose(fwlo);
    return(AL_NOI1);
    }
  rewind(fz88);

/*---------------------------------------------------------------------*
* Beschreiben Z88I1.TXT, erste Zeile
*---------------------------------------------------------------------*/
  if(LANG == 1)
  fprintf(fz88,PDB PDB PDB PDB PD "  Z88I1.TXT,erzeugt von Z88X V15OS\n",
  ndim,nkp,ne,nfg,kflag);


  if(LANG == 2)
  fprintf(fz88,PDB PDB PDB PDB PD "  Z88I1.TXT,produced by Z88X V15OS\n",
  ndim,nkp,ne,nfg,kflag);
  }

/*---------------------------------------------------------------------*
* Beschreiben Z88NI.TXT
*---------------------------------------------------------------------*/
if(ICFLAG == 6)
  {
  wlog88x(0,LOG_WRINI);
  wrim88x(0,TX_WRINI);

/*---------------------------------------------------------------------*
* Oeffnen Z88NI.TXT
*---------------------------------------------------------------------*/
  fz88= fopen(cni,"w");
  if(fz88 == NULL)
    {
    wlog88x(0,LOG_NONI);
    fclose(fwlo);
    return(AL_NONI);
    }
  rewind(fz88);

/*---------------------------------------------------------------------*
* Beschreiben Z88NI.TXT, erste Zeile
*---------------------------------------------------------------------*/
  if(LANG == 1)
  fprintf(fz88,PDB PDB PDB PDB PDB PDB PD "  Z88NI.TXT,erzeugt von Z88X V15OS\n",
  ndim,nkp,ne,nfg,kflagss,niflag,kflag);

  if(LANG == 2)
  fprintf(fz88,PDB PDB PDB PDB PDB PDB PD "  Z88NI.TXT,produced by Z88X V15OS\n",
  ndim,nkp,ne,nfg,kflagss,niflag,kflag);
  }

/*---------------------------------------------------------------------*
* Beschreiben Z88I1.TXT bzw. Z88NI.TXT, Koordinaten
*---------------------------------------------------------------------*/
for(i= 1; i<= nkp;i++)
  fprintf(fz88,PD5B PD2B PE13B PE13B PE13 NL,i,ifrei[i],x[i],y[i],z[i]);

/*---------------------------------------------------------------------*
* Beschreiben Z88I1.TXT bzw. Z88NI.TXT, Koinzidenz
*---------------------------------------------------------------------*/
for(i= 1; i <= ne; i++)
  {
  fprintf(fz88,PD5B PD5 NL,i,ityp[i]);

/*=====================================================================*
* Ele 1
*=====================================================================*/
  if(ityp[i] == 1)
    {
    fprintf(fz88,PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5 NL,
    koi[koffs[i]   ], koi[koffs[i] +1],
    koi[koffs[i] +2], koi[koffs[i] +3],
    koi[koffs[i] +4], koi[koffs[i] +5],
    koi[koffs[i] +6], koi[koffs[i] +7]);
    }

/*=====================================================================*
* Ele 10
*=====================================================================*/
  if(ityp[i] == 10)
    {
    fprintf(fz88,PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B
 PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5 NL,
    koi[koffs[i]    ], koi[koffs[i] + 2],
    koi[koffs[i] + 4], koi[koffs[i] + 6],
    koi[koffs[i] + 8], koi[koffs[i] +10],
    koi[koffs[i] +12], koi[koffs[i] +14],
    koi[koffs[i] + 1], koi[koffs[i] + 3],
    koi[koffs[i] + 5], koi[koffs[i] + 7],
    koi[koffs[i] + 9], koi[koffs[i] +11],
    koi[koffs[i] +13], koi[koffs[i] +15],
    koi[koffs[i] +16], koi[koffs[i] +17],
    koi[koffs[i] +18], koi[koffs[i] +19]);
    }

/*=====================================================================*
* Ele 21
*=====================================================================*/
  if(ityp[i] == 21)
    {
    fprintf(fz88,PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B
 PD5B PD5B PD5B PD5B PD5B PD5 NL,
    koi[koffs[i]    ], koi[koffs[i] + 2],
    koi[koffs[i] + 4], koi[koffs[i] + 6],
    koi[koffs[i] + 1], koi[koffs[i] + 3],
    koi[koffs[i] + 5], koi[koffs[i] + 7],
    koi[koffs[i] + 8], koi[koffs[i] +10],
    koi[koffs[i] +12], koi[koffs[i] +14],
    koi[koffs[i] + 9], koi[koffs[i] +11],
    koi[koffs[i] +13], koi[koffs[i] +15]);
    }

/*=====================================================================*
* Ele 22
*=====================================================================*/
  if(ityp[i] == 22)
    {
    fprintf(fz88,PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B
 PD5B PD5 NL,
    koi[koffs[i]    ], koi[koffs[i] + 2],
    koi[koffs[i] + 4], koi[koffs[i] + 1],
    koi[koffs[i] + 3], koi[koffs[i] + 5],
    koi[koffs[i] + 6], koi[koffs[i] + 8],
    koi[koffs[i] +10], koi[koffs[i] + 7],
    koi[koffs[i] + 9], koi[koffs[i] +11]);
    }

/*=====================================================================*
* Ele 17
*=====================================================================*/
  if(ityp[i] == 17)
    {
    fprintf(fz88,PD5B PD5B PD5B PD5 NL,
    koi[koffs[i]    ], koi[koffs[i] + 1],
    koi[koffs[i] + 2], koi[koffs[i] + 3]);
    }

/*=====================================================================*
* Ele 16
*=====================================================================*/
  if(ityp[i] == 16)
    {
    fprintf(fz88,PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5 NL,
    koi[koffs[i]    ], koi[koffs[i] + 2],
    koi[koffs[i] + 4], koi[koffs[i] + 9],
    koi[koffs[i] + 1], koi[koffs[i] + 3],
    koi[koffs[i] + 5], koi[koffs[i] + 6],
    koi[koffs[i] + 7], koi[koffs[i] + 8]);
    }

/*=====================================================================*
* Ele 7,8,20,23
*=====================================================================*/
  if(ityp[i] == 7 || ityp[i] == 8 || ityp[i] == 20  || ityp[i] == 23)
    {
    fprintf(fz88,PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5 NL,
    koi[koffs[i]   ], koi[koffs[i] +2],
    koi[koffs[i] +4], koi[koffs[i] +6],
    koi[koffs[i] +1], koi[koffs[i] +3],
    koi[koffs[i] +5], koi[koffs[i] +7]);
    }

/*=====================================================================*
* Ele 11,12
*=====================================================================*/
  if(ityp[i] == 11 || ityp[i] == 12)
    {
    fprintf(fz88,PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B
 PD5B PD5 NL,
    koi[koffs[i]    ], koi[koffs[i] + 3],
    koi[koffs[i] + 6], koi[koffs[i] + 9],
    koi[koffs[i] + 1], koi[koffs[i] + 2],
    koi[koffs[i] + 4], koi[koffs[i] + 5],
    koi[koffs[i] + 7], koi[koffs[i] + 8],
    koi[koffs[i] +10], koi[koffs[i] +11]);
    }

/*=====================================================================*
* Ele 2,4,5,9,13,25
*=====================================================================*/
  if(ityp[i] == 2 || ityp[i] == 4  || ityp[i] == 5 ||
     ityp[i] == 9 || ityp[i] == 13 || ityp[i] == 25)
    {
    fprintf(fz88,PD5B PD5 NL,koi[koffs[i]], koi[koffs[i] +1]);
    }

/*=====================================================================*
* Ele 3,14,15,18,24
*=====================================================================*/
  if(ityp[i] == 3  || ityp[i] == 14 || ityp[i] == 15 || 
     ityp[i] == 18 || ityp[i] == 24)
      {
    fprintf(fz88,PD5B PD5B PD5B PD5B PD5B PD5 NL,
    koi[koffs[i]   ], koi[koffs[i] +2], koi[koffs[i] +4],
    koi[koffs[i] +1], koi[koffs[i] +3], koi[koffs[i] +5]);
    }

/*=====================================================================*
* Ele 6
*=====================================================================*/
  if(ityp[i] == 6)
    {
    fprintf(fz88,PD5B PD5B PD5 NL,
    koi[koffs[i]   ], koi[koffs[i] +1], koi[koffs[i] +2]);
    }

/*=====================================================================*
* Ele 19
*=====================================================================*/
  if(ityp[i] == 19)
    {
    fprintf(fz88,PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B
 PD5B PD5B PD5B PD5B PD5B PD5 NL,
    koi[koffs[i]    ], koi[koffs[i] + 1],
    koi[koffs[i] + 2], koi[koffs[i] + 3],
    koi[koffs[i] + 4], koi[koffs[i] + 5],
    koi[koffs[i] + 6], koi[koffs[i] + 7],
    koi[koffs[i] + 8], koi[koffs[i] + 9],
    koi[koffs[i] +10], koi[koffs[i] +11],
    koi[koffs[i] +12], koi[koffs[i] +13],
    koi[koffs[i] +14], koi[koffs[i] +15]);
    }
  }

/*---------------------------------------------------------------------*
* Z88NI.TXT: Zerlegungs-Infos schreiben
*---------------------------------------------------------------------*/
if(ICFLAG == 6)
  {
  for(i= 1; i <= ne; i++)
    {
    if(LANG == 1)
    fprintf(fz88,
    PD5B PD5 "   Superele. Nr." PD ",Typ "PD ", --> Finites Ele. Typ " PD NL,
    i,itypfe[i],i,ityp[i],itypfe[i]);

    if(LANG == 2)
    fprintf(fz88,
    PD5B PD5 "  superele. no." PD ",type " PD ", --> finite ele. type " PD NL,
    i,itypfe[i],i,ityp[i],itypfe[i]);

    if(ityp[i] == 1 || ityp[i] == 10 || ityp[i] == 21)
      {
      fprintf(fz88,PD5B PCB PD5B PCB PD5B PC NL,
      jel[i],cjmode[i],iel[i],cimode[i],kel[i],ckmode[i]);
      }
    else
      {
      fprintf(fz88,PD5B PCB PD5B PC NL,
      jel[i],cjmode[i],iel[i],cimode[i]);
      }
    }

  if(niflag == 1)
    {
    if(ityp[i] == 1 || ityp[i] == 10 || ityp[i] == 21)
      {
      fprintf(fz88,PE13B PE13B PE13 NL,epsx,epsy,epsz);
      }
    else
      {
      fprintf(fz88,PE13B PE13 NL,epsx,epsy);
      }
    }
  }

fclose(fz88);

/*---------------------------------------------------------------------*
* Beschreiben Z88I2.TXT
*---------------------------------------------------------------------*/
if(ICFLAG == 5)
  {
  wlog88x(0,LOG_WRII2);
  wrim88x(0,TX_WRII2);

/*---------------------------------------------------------------------*
* Oeffnen Z88I2.TXT
*---------------------------------------------------------------------*/
  fi2= fopen(ci2,"w");
  if(fi2 == NULL)
    {
    wlog88x(0,LOG_NOI2);
    fclose(fwlo);
    return(AL_NOI2);
    }
  rewind(fi2);

/*---------------------------------------------------------------------*
* Beschreiben Z88I2.TXT, komplett
*---------------------------------------------------------------------*/
  if(LANG == 1) fprintf(fi2,PD5 "    Z88I2.TXT,erzeugt von Z88X V15OS\n",nrb);
  if(LANG == 2) fprintf(fi2,PD5 "    Z88I2.TXT,produced by Z88X V15OS\n",nrb);

  for(j= 1; j <= nrb; j++)
    fprintf(fi2,PD5B PD5B PD5B PE13 NL,nkn[j],ifg[j],irflag[j],wert[j]);

  fclose(fi2);
  }

/*---------------------------------------------------------------------*
* Beschreiben Z88I5.TXT
*---------------------------------------------------------------------*/
if(ICFLAG == 5)
  {
  wlog88x(0,LOG_WRII5);
  wrim88x(0,TX_WRII5);

/*---------------------------------------------------------------------*
* Oeffnen Z88I5.TXT
*---------------------------------------------------------------------*/
  fi5= fopen(ci5,"w");
  if(fi5 == NULL)
    {
    wlog88x(0,LOG_NOI5);
    fclose(fwlo);
    return(AL_NOI5);
    }
  rewind(fi5);

/*---------------------------------------------------------------------*
* Beschreiben Z88I5.TXT
*---------------------------------------------------------------------*/
  if(LANG == 1) fprintf(fi5,PD "    Z88I5.TXT,erzeugt von Z88X V15OS\n",npr);
  if(LANG == 2) fprintf(fi5,PD "    Z88I5.TXT,produced by Z88X V15OS\n",npr);

/*---------------------------------------------------------------------*
* nur wenn npr > 0 ist, dann Schleife
*---------------------------------------------------------------------*/
  if(iqflag == 1)
    {

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*
* nur wenn npr > 0 ist, dann Schleife
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(j= 1; j <= npr; j++)
      {

/*======================================================================
* Elementtypen 7, 8, 14, 15
*=====================================================================*/
      if(ityp[nep[j]]== 7  || ityp[nep[j]]== 8 ||
         ityp[nep[j]]== 14 || ityp[nep[j]]== 15) 
        {
        fprintf(fi5,PD5B PE13B PE13B PD5B PD5B PD5 NL,
        nep[j],pres[j],tr1[j],
        noi[noffs[j]   ],noi[noffs[j] +1],noi[noffs[j] +2]);  
        }

/*======================================================================
* Elementtyp 10 u. 21
*=====================================================================*/
      if(ityp[nep[j]]== 10 || ityp[nep[j]]== 21) 
        {
        fprintf(fi5,PD5B PE13B PE13B PE13B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5 NL,
        nep[j],pres[j],tr1[j],tr2[j],
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
        fprintf(fi5,PD5B PE13B PE13B PE13B PD5B PD5B PD5B PD5B PD5B PD5 NL,
        nep[j],pres[j],tr1[j],tr2[j],
        noi[noffs[j]   ], noi[noffs[j] +1], 
        noi[noffs[j] +2], noi[noffs[j] +3], 
        noi[noffs[j] +4], noi[noffs[j] +5]); 
        }

/*======================================================================
* Elementtyp 1
*=====================================================================*/
      if(ityp[nep[j]]== 1) 
        {
        fprintf(fi5,PD5B PE13B PE13B PE13B PD5B PD5B PD5B PD5 NL,
        nep[j],pres[j],tr1[j],tr2[j],
        noi[noffs[j]   ], noi[noffs[j] +1], 
        noi[noffs[j] +2], noi[noffs[j] +3]); 
        }

/*======================================================================
* Elementtyp 17
*=====================================================================*/
      if(ityp[nep[j]]== 17) 
        {
        fprintf(fi5,PD5B PE13B PD5B PD5B PD5 NL,
        nep[j],pres[j],
        noi[noffs[j]   ], noi[noffs[j]+ 1], noi[noffs[j] +2]); 
        }

/*======================================================================
* Elementtyp 16
*=====================================================================*/
      if(ityp[nep[j]]== 16) 
        {
        fprintf(fi5,PD5B PE13B PD5B PD5B PD5B PD5B PD5B PD5 NL,
        nep[j],pres[j],
        noi[noffs[j]   ], noi[noffs[j] +1], 
        noi[noffs[j] +2], noi[noffs[j] +3], 
        noi[noffs[j] +4], noi[noffs[j] +5]); 
        }

/*======================================================================
* Elementtypen 11 und 12
*=====================================================================*/
      if(ityp[nep[j]]== 11 || ityp[nep[j]]== 12) 
        {
        fprintf(fi5,PD5B PE13B PE13B PD5B PD5B PD5B PD5 NL,
        nep[j],pres[j],tr1[j],
        noi[noffs[j]   ], noi[noffs[j] +1], 
        noi[noffs[j] +2], noi[noffs[j] +3]); 
        }

/*======================================================================
* Elementtyp 18,19,20,23,24
*=====================================================================*/
      if(ityp[nep[j]]== 18 || ityp[nep[j]]== 19 || ityp[nep[j]]== 20 ||
         ityp[nep[j]]== 23 || ityp[nep[j]]== 24) 
        {
        fprintf(fi5,PD5B PE13 NL,nep[j],pres[j]); 
        }

      } /* Ende Schleife */
    } /* Ende iqflag */

  fclose(fi5);
  }

return(0);
}

