/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the UNIX OS.
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
/****************************************************************************
*  Programm z88x.c
*  10.1.2012 Rieg
****************************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88x.h>  
#include <stdio.h>    /* FILE */
#include <ctype.h>    /* toupper */
#include <string.h>   /* strcpy,strcmp */
#include <stdlib.h>     /* atof */
#endif

/***********************************************************************
* Schreib/Leseformate
***********************************************************************/
#define NL "\n"

#ifdef FR_XDOUB
#define PG "%lg"
#endif

#ifdef FR_XQUAD
#define PG "%Lg"
#endif

/****************************************************************************
*  Function-Declarationen
****************************************************************************/
int lan88x(void);
int dyn88x(void);
int ale88x(int);
int who88x(void);
int rea88x(void);
int rdxf88x(void);
int z88tx(void);
int z88fx(void);
int wrim88x(FR_INT4,int);
int wlog88x(FR_INT4,int);
void stop88x(void);
void sub88x(FR_INT4);

/****************************************************************************
*  globale Variable
****************************************************************************/
/*--------------------------------------------------------------------------
* Files
*-------------------------------------------------------------------------*/
FILE *fdyn,*fwlo,*fz88,*fdxf,*fi2,*fi5;

/*  
**   fdyn= z88.dyn
**   fwlo= z88x.log
**   fz88= z88ni.txt oder z88i1.txt
**   fdxf= z88x.dxf oder z88x.dxf
**   fi2 = z88i2.txt
**   fi5 = z88i5.txt
*/ 

char cdyn[8] = "z88.dyn";
char clgd[9] = "z88x.log";
char ci1[10] = "z88i1.txt";
char ci2[10] = "z88i2.txt";
char ci5[10] = "z88i5.txt";
char cni[10] = "z88ni.txt";
char cxx[10] = "z88x.dxf";
  
/*--------------------------------------------------------------------------
* Pointer
*-------------------------------------------------------------------------*/
FR_DOUBLEAY x;
FR_DOUBLEAY y;
FR_DOUBLEAY z;
FR_DOUBLEAY wert;
FR_DOUBLEAY pres;
FR_DOUBLEAY tr1;
FR_DOUBLEAY tr2;

FR_INT4AY koi;
FR_INT4AY ifrei; 
FR_INT4AY ioffs;
FR_INT4AY koffs;
FR_INT4AY ityp;
FR_INT4AY itypfe;
FR_INT4AY jel;
FR_INT4AY iel;
FR_INT4AY kel;
FR_INT4AY nkn;
FR_INT4AY ifg;
FR_INT4AY irflag;
FR_INT4AY nep;
FR_INT4AY noi;
FR_INT4AY noffs;

FR_CHARAY cjmode;
FR_CHARAY cimode;
FR_CHARAY ckmode;

/*--------------------------------------------------------------------------
* Variable
*-------------------------------------------------------------------------*/
FR_DOUBLE epsx,epsy,epsz;
FR_DOUBLE texts;

FR_INT4 intore,nel,ktyp;
FR_INT4 LANG,IDYNMEM,ICFLAG;
FR_INT4 ndim,nkp,ne,nfg,nkoi,kflagss,kflag,iqflag,niflag;
FR_INT4 nrb,npr,ninto;
FR_INT4 ianz,ifrej;

char cflag[10];

/*--------------------------------------------------------------------------
* vorbelegte Variable
*-------------------------------------------------------------------------*/
FR_INT4 MAXNFG=0,MAXK=0,MAXE=0,MAXKOI=0,MAXPR=0;
FR_INT4 ITSFLAG= 0;

/*****************************************************************************
* hauptprogramm
*****************************************************************************/
int main(int argc,char *argv[])
{
int iret,i;
char cflagul[10], cftexts[10], cfts[10];

/*---------------------------------------------------------------------------
*  Die Sprache feststellen
*--------------------------------------------------------------------------*/
LANG = 0;
iret= lan88x();

if(iret != 0)
  {
  ale88x(iret);
  stop88x();
  }

/*---------------------------------------------------------------------------
*  Ueberschrift
*--------------------------------------------------------------------------*/
who88x();

/*---------------------------------------------------------------------------
*  Die Flags abfragen
*--------------------------------------------------------------------------*/
ICFLAG= 0;

if(argc <= 1)
  {
  ale88x(AL_NOCFLAG); 
  stop88x();              
  }

/*==========================================================================
* Steuerflag
*=========================================================================*/
strcpy(cflagul,argv[1]);  
for(i= 0; i < 6; i++)
  cflag[i]= toupper(cflagul[i]);
  
if     (strcmp("-I1TX",cflag) == 0)
  ICFLAG= 1;
else if(strcmp("-IATX",cflag) == 0)
  ICFLAG= 2;
else if(strcmp("-NITX",cflag) == 0)
  ICFLAG= 3;
else if(strcmp("-I1FX",cflag) == 0)
  ICFLAG= 4;
else if(strcmp("-IAFX",cflag) == 0)
  ICFLAG= 5;
else if(strcmp("-NIFX",cflag) == 0)
  ICFLAG= 6;
else if(strcmp("-BDOF",cflag) == 0)
  printf("\n140655\n");
else
  { 
  wrim88x(ICFLAG,TX_CFLAG);
  ale88x(AL_WROCFLAG); 
  stop88x();              
  }      

wrim88x(ICFLAG,TX_CFLAG);

/*==========================================================================
* Textgroesse
*=========================================================================*/
if(argc == 4)
  {
  strcpy(cftexts,argv[2]);  
  for(i= 0; i < 4; i++)
    cfts[i]= toupper(cftexts[i]);
  
  if(strcmp("-TS",cfts) == 0)
    {
    ITSFLAG= 1;
    texts= (FR_DOUBLE) atof(argv[3]);
    printf("-ts " PG NL,texts);
    }
  }

/*---------------------------------------------------------------------------
* dyn88x starten: anfordern dynamic memory
*--------------------------------------------------------------------------*/
iret= dyn88x();
if(iret != 0)
  {
  ale88x(iret);
  stop88x();              
  }           

/*---------------------------------------------------------------------------
* Entscheiden, welcher Berechnungsgang
*--------------------------------------------------------------------------*/
if(ICFLAG == 1 || ICFLAG == 2)
  {                                    /* Start -I1TX oder -IATX */ 

/*---------------------------------------------------------------------------
* Berechnungsgang 1: von Z88I1.TXT nach Z88X.DXF
* Berechnungsgang 2: von Z88I1.TXT, Z88I2.TXT,Z88I5.TXT nach Z88X.DXF
*--------------------------------------------------------------------------*/
/*===========================================================================
* Einlesen Z88I1.TXT
*==========================================================================*/
  iret= rea88x();
  if(iret != 0)
    {
    ale88x(iret);
    stop88x();              
    }           
  
/*===========================================================================
* Rechnen
*==========================================================================*/
  iret= z88tx();
  if(iret != 0)
    {
    ale88x(iret);
    stop88x();              
    }           

  wrim88x(0,TX_EXITZ88X);
  return(0);
  }                                    /* Ende -I1TX und -IATX */
/*---------------------------------------------------------------------------
* Ende Berechnungsgang 1 und 2
*--------------------------------------------------------------------------*/

if(ICFLAG == 3)
  {                                    /* Start -NITX */ 

/*---------------------------------------------------------------------------
* Berechnungsgang 3: von Z88NI.TXT nach Z88X.DXF
*--------------------------------------------------------------------------*/
/*===========================================================================
* Einlesen Z88NI.TXT
*==========================================================================*/
  iret= rea88x();
  if(iret != 0)
    {
    ale88x(iret);
    stop88x();              
    }           
  
/*===========================================================================
* Rechnen
*==========================================================================*/
  iret= z88tx();
  if(iret != 0)
    {
    ale88x(iret);
    stop88x();              
    }           

  wrim88x(0,TX_EXITZ88X);
  return(0);
  }                                    /* Ende -NITX */
/*---------------------------------------------------------------------------
* Ende Berechnungsgang 3
*--------------------------------------------------------------------------*/

if(ICFLAG == 4 || ICFLAG == 5)
  {                                    /* Start -I1FX oder -IAFX */ 

/*---------------------------------------------------------------------------
* Berechnungsgang 4: von Z88X.DXF nach Z88I1.TXT
* Berechnungsgang 5: von Z88X.DXF nach Z88I1.TXT, Z88I2.TXT, Z88I5.TXT
*--------------------------------------------------------------------------*/
/*===========================================================================
* Rechnen
*==========================================================================*/
  iret= z88fx();
  if(iret != 0)
    {
    ale88x(iret);
    stop88x();              
    }           

  wrim88x(0,TX_EXITZ88X);
  return(0);
  }                                    /* Ende -I1FX oder -IAFX */
/*---------------------------------------------------------------------------
* Ende Berechnungsgang 4 und 5
*--------------------------------------------------------------------------*/

if(ICFLAG == 6)
  {                                    /* Start -NIFX */ 

/*---------------------------------------------------------------------------
* Berechnungsgang 6: von Z88X.DXF nach Z88NI.TXT
*--------------------------------------------------------------------------*/
/*===========================================================================
* Rechnen
*==========================================================================*/
  iret= z88fx();
  if(iret != 0)
    {
    ale88x(iret);
    stop88x();              
    }           

  wrim88x(0,TX_EXITZ88X);
  return(0);
  }                                    /* Ende -NIFX */
/*---------------------------------------------------------------------------
* Ende Berechnungsgang 6
*--------------------------------------------------------------------------*/

return(0);
}


