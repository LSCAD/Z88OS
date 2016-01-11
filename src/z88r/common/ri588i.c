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
* V14.0 January 14, 2011
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
* ri588i
* 17.7.2011 Rieg 
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>    /* fopen,fclose,fprintf,fgets,sscanf */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <stdio.h>    /* fopen,fclose,fprintf,fgets,sscanf */
#endif

/***********************************************************************
* Fuer Windows und GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88r.h>
#include <stdio.h>    /* fopen,fclose,fprintf,fgets,sscanf */
#endif

/***********************************************************************
* Leseformate
***********************************************************************/
#define NL "\n"

#ifdef FR_XINT
#define PD "%d"
#define BPD " %d"
#endif

#ifdef FR_XLONG
#define PD "%ld"
#define BPD " %ld"
#endif

#ifdef FR_XLOLO
#define PD "%lld"
#define BPD " %lld"
#endif

#ifdef FR_XDOUB
#define BPG " %lg"
#endif

#ifdef FR_XQUAD
#define BPG " %Lg"
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88r(FR_INT4,int);
int wlog88r(FR_INT4,int);

/***********************************************************************
* hier beginnt Function ri588i
* ri588i.c liest z88i5.txt ein
* hier wird File z88i5.txt geoeffnet 
***********************************************************************/
int ri588i(void)
{
extern FILE *fi5,*fwlo;
extern char ci5[];

extern FR_DOUBLEAY pres;
extern FR_DOUBLEAY tr1;
extern FR_DOUBLEAY tr2;

extern FR_INT4AY noi;
extern FR_INT4AY noffs;
extern FR_INT4AY ityp;
extern FR_INT4AY nep;

extern FR_INT4 npr;
extern FR_INT4 MAXPR;

FR_INT4 i,idummy,nofold= 0;

char cline[256];

/*----------------------------------------------------------------------
* Start Function
*---------------------------------------------------------------------*/
wrim88r(0,TX_REAI5);

/*----------------------------------------------------------------------
* Oeffnen Z88I5.TXT
*---------------------------------------------------------------------*/
wlog88r(0,LOG_BRI588);
fi5= fopen(ci5,"r");
if(fi5 == NULL)
  {
  wlog88r(0,LOG_NOI5);
  fclose(fwlo);
  return(AL_NOI5);
  }

rewind(fi5);

/*----------------------------------------------------------------------
* Einlesen der Anzahl der Flaechenlasten npr
*---------------------------------------------------------------------*/
fgets(cline,256,fi5);
sscanf(cline,PD,&npr);

if(npr >= MAXPR-1)
  {
  wlog88r(MAXPR,LOG_EXMAXPR);
  fclose(fwlo);
  return(AL_EXMAXPR);
  }

/***********************************************************************
* Einlesen des Lastvektors
***********************************************************************/
for(i= 1; i <= npr; i++)
  {
  fgets(cline,256,fi5);
  sscanf(cline,PD,&nep[i]); 

/*----------------------------------------------------------------------
* den koinzidenzvektor noi & den zugehoerigen pointervektor noffs
* auffuellen
*---------------------------------------------------------------------*/

/*======================================================================
* Elementtypen 7, 8, 14, 15
*=====================================================================*/
  if(ityp[nep[i]]== 7  || ityp[nep[i]]== 8 ||
     ityp[nep[i]]== 14 || ityp[nep[i]]== 15) 
    {
    if(i== 1)  noffs[1]= 1;
    else       noffs[i]= noffs[i-1] + nofold;
    
    sscanf(cline,PD BPG BPG BPD BPD BPD,&idummy,&pres[i],&tr1[i],
    &noi[noffs[i]],&noi[noffs[i]+1],&noi[noffs[i]+2]);  
    
    nofold= 3;
    }

/*======================================================================
* Elementtyp 17
*=====================================================================*/
  if(ityp[nep[i]]== 17) 
    {
    if(i== 1)  noffs[1]= 1;
    else       noffs[i]= noffs[i-1] + nofold;
    
    sscanf(cline,PD BPG BPD BPD BPD,&idummy,&pres[i],
    &noi[noffs[i]],&noi[noffs[i]+1],&noi[noffs[i]+2]); 

    nofold= 3;
    }
          
/*======================================================================
* Elementtyp 16 && 22
*=====================================================================*/
  if(ityp[nep[i]]== 16 || ityp[nep[i]]== 22) 
    {
    if(i== 1)  noffs[1]= 1;
    else       noffs[i]= noffs[i-1] + nofold;
    
    sscanf(cline,PD BPG BPD BPD BPD BPD BPD BPD,
    &idummy,&pres[i],
    &noi[noffs[i]  ], &noi[noffs[i]+1], 
    &noi[noffs[i]+2], &noi[noffs[i]+3], 
    &noi[noffs[i]+4], &noi[noffs[i]+5]); 

    nofold= 6;
    }

/*======================================================================
* Elementtyp 10 && 21
*=====================================================================*/
  if(ityp[nep[i]]== 10 || ityp[nep[i]]== 21) 
    {
    if(i== 1)  noffs[1]= 1;
    else       noffs[i]= noffs[i-1] + nofold;
    
    sscanf(cline,PD BPG BPG BPG BPD BPD BPD BPD BPD BPD BPD BPD,
    &idummy,&pres[i],&tr1[i],&tr2[i],
    &noi[noffs[i]  ], &noi[noffs[i]+1], 
    &noi[noffs[i]+2], &noi[noffs[i]+3], 
    &noi[noffs[i]+4], &noi[noffs[i]+5],
    &noi[noffs[i]+6], &noi[noffs[i]+7]); 

    nofold= 8;
    }

/*======================================================================
* Elementtyp 1
*=====================================================================*/
  if(ityp[nep[i]]== 1) 
    {
    if(i== 1)  noffs[1]= 1;
    else       noffs[i]= noffs[i-1] + nofold;
    
    sscanf(cline,PD BPG BPG BPG BPD BPD BPD BPD,
    &idummy,&pres[i],&tr1[i],&tr2[i],
    &noi[noffs[i]  ], &noi[noffs[i]+1], 
    &noi[noffs[i]+2], &noi[noffs[i]+3]); 

    nofold= 4;
    }

/*======================================================================
* Elementtypen 11 und 12
*=====================================================================*/
  if(ityp[nep[i]]== 11 || ityp[nep[i]]== 12) 
    {
    if(i== 1)  noffs[1]= 1;
    else       noffs[i]= noffs[i-1] + nofold;
    
    sscanf(cline,PD BPG BPG BPD BPD BPD BPD,
    &idummy,&pres[i],&tr1[i],
    &noi[noffs[i]  ], &noi[noffs[i]+1], 
    &noi[noffs[i]+2], &noi[noffs[i]+3]); 

    nofold= 4;
    }

/*======================================================================
* Elementtyp 18,19,20,23 und 24
*=====================================================================*/
  if(ityp[nep[i]]== 18 || ityp[nep[i]]== 19 || 
     ityp[nep[i]]== 20 || ityp[nep[i]]== 23 || ityp[nep[i]]== 24) 
    {
    sscanf(cline,PD BPG,&idummy,&pres[i]); 
    }

  } /* Ende Schleife ueber alle Flaechenlasten */

/*----------------------------------------------------------------------
* Z88I5.TXT schliessen 
*---------------------------------------------------------------------*/
fclose(fi5);

wlog88r(0,LOG_EXITRI188);
return (0);
}
