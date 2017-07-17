/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows & UNIX OS.
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
* ri1x88
* 18.11.2015 Rieg
***********************************************************************/

/*----------------------------------------------------------------------
* Windows
*---------------------------------------------------------------------*/
#ifdef FR_WIN
#include <z88o.h>
#include <stdio.h>           /* fprintf,fgets,sscanf */
#endif

/*----------------------------------------------------------------------
* UNIX
*---------------------------------------------------------------------*/
#ifdef FR_UNIX
#include <z88o.h>
#include <stdio.h>           /* fprintf,fgets,sscanf */
#endif

/***********************************************************************
* Leseformate
***********************************************************************/
#ifdef FR_XINT
#define PDB "%d "
#define PD "%d"
#endif

#ifdef FR_XLONG
#define PDB "%ld "
#define PD "%ld"
#endif

#ifdef FR_XLOLO
#define PDB "%lld "
#define PD "%lld"
#endif

#ifdef FR_XDOUB
#define PGB "%lg "
#define PG "%lg"
#endif

#ifdef FR_XQUAD
#define PGB "%Lg "
#define PG "%Lg"
#endif

/***********************************************************************
* Functions
***********************************************************************/
int wlog88o(FR_INT4,int);

/***********************************************************************
* Function ri1x88
***********************************************************************/
int ri1x88(void)
{
extern FILE *fi1;

extern FR_DOUBLEAY x;
extern FR_DOUBLEAY y;
extern FR_DOUBLEAY z;

extern FR_INT4AY ityp;
extern FR_INT4AY koffs;
extern FR_INT4AY koi;
extern FR_INT4AY ivon;
extern FR_INT4AY ibis;

extern FR_INT4 MAXE,MAXK,MAXKOI;
extern FR_INT4 ndim,nkp,ne,nfg,kflag,ipflag;

FR_DOUBLE radius,phi;

FR_INT4 i,idummy,jdummy,kofold;

char cline[256];

kflag= 0;  /* sicherheitshalber */
                 
/***********************************************************************
* Eintrag in z88o.log
***********************************************************************/
wlog88o(0,LOG_REAI1);

/***********************************************************************
* Einlesen der allgemeinen Strukturdaten
***********************************************************************/
fgets(cline,256,fi1);
sscanf(cline,PDB PDB PDB PDB PD,&ndim,&nkp,&ne,&nfg,&kflag);

/***********************************************************************
* Speicher und Dimension checken
***********************************************************************/
if(nkp >= MAXK-1)
  {
  wlog88o(MAXK,LOG_EXMAXK);
  return(AL_EXMAXK);
  }

if(ne >= MAXE-1)
  {
  wlog88o(MAXE,LOG_EXMAXE);
  return(AL_EXMAXE);
  }

if(ndim < 2 || ndim > 3)
  {
  wlog88o(0,LOG_WRONGDIM);
  return(AL_WRONGDIM);
  }

/***********************************************************************
* Einlesen der Koordinaten
***********************************************************************/
if(ndim== 3)
  {
  for(i= 1; i <= nkp; i++)
    {
    fgets(cline,256,fi1);
    sscanf(cline,PDB PDB PGB PGB PG,&idummy,&jdummy,&x[i],&y[i],&z[i]); 
    }
  }
else
  {
  for(i= 1; i <= nkp; i++)
    {
    fgets(cline,256,fi1);
    sscanf(cline,PDB PDB PGB PG,&idummy,&jdummy,&x[i],&y[i]); 
    }
  }
          
/*----------------------------------------------------------------------
* ggf auf kartesische Koordinaten umrechnen
*---------------------------------------------------------------------*/
if(kflag == 1) 
  {
  for(i= 1; i <= nkp; i++)
     {
     radius= x[i];
     phi= 3.141593/180.* y[i];
     x[i]= radius*FR_COS(phi);
     y[i]= radius*FR_SIN(phi);
     }
   }
      
/*----------------------------------------------------------------------
* wenn Platten, dann z-Koordinaten beistellen und ndim auf 3 setzen
*---------------------------------------------------------------------*/
if(ipflag != 0) 
  {
  ndim= 3;
  for(i= 1; i <= nkp; i++)
    z[i]= 0.;
  }

/***********************************************************************
* Einlesen der Koinzidenz
***********************************************************************/
for(i= 1; i <= ne; i++)
  {
  fgets(cline,256,fi1);
  sscanf(cline,PDB PD,&idummy,&ityp[i]); 
          
/*----------------------------------------------------------------------
* den Koinzidenzvektor koi & den zugehoerigen Pointervektor koffs
* auffuellen
*---------------------------------------------------------------------*/
/*======================================================================
* Elementtypen 1, 7, 8 & 20 & 23
*=====================================================================*/
  if(ityp[i]== 1  || ityp[i]== 7 || ityp[i]== 8 || 
     ityp[i]== 20 || ityp[i]== 23) 
    {
    if(i== 1)  koffs[1]= 1;
    else       koffs[i]= koffs[i-1] + kofold;

    if(koffs[i]+8 >= MAXKOI-1) 
      {
      wlog88o(MAXKOI,LOG_EXMAXKOI);
      return(AL_EXMAXKOI);
      }

    fgets(cline,256,fi1);
    sscanf(cline,PDB PDB PDB PDB PDB PDB PDB PD,
    &koi[koffs[i]   ], &koi[koffs[i] +1], 
    &koi[koffs[i] +2], &koi[koffs[i] +3], 
    &koi[koffs[i] +4], &koi[koffs[i] +5], 
    &koi[koffs[i] +6], &koi[koffs[i] +7]); 

    kofold= 8;
    }
          
/*======================================================================
* Elementtypen 2, 4, 5 , 9 & 13, 25
*=====================================================================*/
  if(ityp[i]== 2 || ityp[i]== 4  || ityp[i]== 5 ||
     ityp[i]== 9 || ityp[i]== 13 || ityp[i]== 25)
    {
    if(i== 1)  koffs[1]= 1;
    else       koffs[i]= koffs[i-1] + kofold;

    if(koffs[i]+2 >= MAXKOI-1) 
      {
      wlog88o(MAXKOI,LOG_EXMAXKOI);
      return(AL_EXMAXKOI);
      }

    fgets(cline,256,fi1);
    sscanf(cline,PDB PD,
    &koi[koffs[i]   ], &koi[koffs[i] +1]); 
            
    kofold= 2;
    }
                  
/*======================================================================
* Elementtyp 3, 14,15,18 & 24
*=====================================================================*/
  if(ityp[i]== 3  || ityp[i]== 14 || ityp[i]== 15 || 
     ityp[i]== 18 || ityp[i]== 24)
    {
    if(i== 1)  koffs[1]= 1;
    else       koffs[i]= koffs[i-1] + kofold;

    if(koffs[i]+6 >= MAXKOI-1) 
      {
      wlog88o(MAXKOI,LOG_EXMAXKOI);
      return(AL_EXMAXKOI);
      }

    fgets(cline,256,fi1);
    sscanf(cline,PDB PDB PDB PDB PDB PD,
    &koi[koffs[i]   ], &koi[koffs[i] +1], 
    &koi[koffs[i] +2], &koi[koffs[i] +3], 
    &koi[koffs[i] +4], &koi[koffs[i] +5]); 
            
    kofold= 6;
    }
          
/*======================================================================
* Elementtyp 6
*=====================================================================*/
  if(ityp[i]== 6)
    {
    if(i== 1)  koffs[1]= 1;
    else       koffs[i]= koffs[i-1] + kofold;

    if(koffs[i]+3 >= MAXKOI-1) 
      {
      wlog88o(MAXKOI,LOG_EXMAXKOI);
      return(AL_EXMAXKOI);
      }

    fgets(cline,256,fi1);
    sscanf(cline,PDB PDB PD,
    &koi[koffs[i]   ], &koi[koffs[i] +1], 
    &koi[koffs[i] +2]);
            
    kofold= 3;
    }
   
/*======================================================================
* Elementtypen 10
*=====================================================================*/
  if(ityp[i]== 10)
    {
    if(i== 1)  koffs[1]= 1;
    else       koffs[i]= koffs[i-1] + kofold;

    if(koffs[i]+20 >= MAXKOI-1) 
      {
      wlog88o(MAXKOI,LOG_EXMAXKOI);
      return(AL_EXMAXKOI);
      }

    fgets(cline,256,fi1);
    sscanf(cline,PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &koi[koffs[i]    ], &koi[koffs[i]  +1], 
    &koi[koffs[i]  +2], &koi[koffs[i]  +3], 
    &koi[koffs[i]  +4], &koi[koffs[i]  +5], 
    &koi[koffs[i]  +6], &koi[koffs[i]  +7], 
    &koi[koffs[i]  +8], &koi[koffs[i]  +9], 
    &koi[koffs[i] +10], &koi[koffs[i] +11], 
    &koi[koffs[i] +12], &koi[koffs[i] +13], 
    &koi[koffs[i] +14], &koi[koffs[i] +15], 
    &koi[koffs[i] +16], &koi[koffs[i] +17], 
    &koi[koffs[i] +18], &koi[koffs[i] +19]); 

    kofold= 20;
    }

/*======================================================================
* Elementtypen 11 & 12 & 22
*=====================================================================*/
  if(ityp[i]== 11 || ityp[i]== 12 || ityp[i]== 22) 
    {
    if(i== 1)  koffs[1]= 1;
    else       koffs[i]= koffs[i-1] + kofold;

    if(koffs[i]+12 >= MAXKOI-1) 
      {
      wlog88o(MAXKOI,LOG_EXMAXKOI);
      return(AL_EXMAXKOI);
      }

    fgets(cline,256,fi1);
    sscanf(cline,PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &koi[koffs[i]    ], &koi[koffs[i] + 1], 
    &koi[koffs[i] + 2], &koi[koffs[i] + 3], 
    &koi[koffs[i] + 4], &koi[koffs[i] + 5], 
    &koi[koffs[i] + 6], &koi[koffs[i] + 7], 
    &koi[koffs[i] + 8], &koi[koffs[i] + 9], 
    &koi[koffs[i] +10], &koi[koffs[i] +11]); 

    kofold= 12;
    }

/*======================================================================
* Elementtypen 16
*=====================================================================*/
  if(ityp[i]== 16)
    {
    if(i== 1)  koffs[1]= 1;
    else       koffs[i]= koffs[i-1] + kofold;

    if(koffs[i]+10 >= MAXKOI-1) 
      {
      wlog88o(MAXKOI,LOG_EXMAXKOI);
      return(AL_EXMAXKOI);
      }

    fgets(cline,256,fi1);
    sscanf(cline,PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &koi[koffs[i]   ], &koi[koffs[i] +1], 
    &koi[koffs[i] +2], &koi[koffs[i] +3], 
    &koi[koffs[i] +4], &koi[koffs[i] +5], 
    &koi[koffs[i] +6], &koi[koffs[i] +7], 
    &koi[koffs[i] +8], &koi[koffs[i] +9]); 

    kofold= 10;
    }

/*======================================================================
* Elementtypen 17
*=====================================================================*/
  if(ityp[i]== 17)
    {
    if(i== 1)  koffs[1]= 1;
    else       koffs[i]= koffs[i-1] + kofold;

    if(koffs[i]+4 >= MAXKOI-1) 
      {
      wlog88o(MAXKOI,LOG_EXMAXKOI);
      return(AL_EXMAXKOI);
      }

    fgets(cline,256,fi1);
    sscanf(cline,PDB PDB PDB PD,
    &koi[koffs[i]   ], &koi[koffs[i] +1], 
    &koi[koffs[i] +2], &koi[koffs[i] +3]); 

    kofold= 4;
    }

/*======================================================================
* Elementtypen 19 u. 21
*=====================================================================*/
  if(ityp[i]== 19 || ityp[i]== 21)
    {
    if(i== 1)  koffs[1]= 1;
    else       koffs[i]= koffs[i-1] + kofold;

    if(koffs[i]+16 >= MAXKOI-1) 
      {
      wlog88o(MAXKOI,LOG_EXMAXKOI);
      return(AL_EXMAXKOI);
      }

    fgets(cline,256,fi1);
    sscanf(cline,PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &koi[koffs[i]    ], &koi[koffs[i]  +1], 
    &koi[koffs[i]  +2], &koi[koffs[i]  +3], 
    &koi[koffs[i]  +4], &koi[koffs[i]  +5], 
    &koi[koffs[i]  +6], &koi[koffs[i]  +7], 
    &koi[koffs[i]  +8], &koi[koffs[i]  +9], 
    &koi[koffs[i] +10], &koi[koffs[i] +11], 
    &koi[koffs[i] +12], &koi[koffs[i] +13], 
    &koi[koffs[i] +14], &koi[koffs[i] +15]); 

    kofold= 16;
    }

  } /* ende Koinzidenz */

wlog88o(0,LOG_REAI1OK);
return 0;
}
