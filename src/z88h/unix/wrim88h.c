/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the UNIX and
* the Windows OS.
*
* Composed and edited by 
* Professor Dr.-Ing. Frank Rieg, University of Bayreuth, Germany
*
* eMail: 
* frank.rieg@uni-bayreuth.de
* dr.frank.rieg@t-online.de
* 
* V14.0  February 14, 2011
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
* wrim88h gibt Texte aus (1 FR_INT4)
* 1.8.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88h.h>
#include <stdio.h>    /* printf */
#endif

/***********************************************************************
* Formate
***********************************************************************/
#ifdef FR_XINT
#define PD "%d"
#endif

#ifdef FR_XLONG
#define PD "%ld"
#endif

#ifdef FR_XLOLO
#define PD "%lld"
#endif

/***********************************************************************
*  hier beginnt Function wrim88h
***********************************************************************/
int wrim88h(FR_INT4 i,int iatx)
{
extern FR_INT4 LANG;

switch(iatx)
  {
  case TX_INOPEN:
    if(LANG == 1) printf("Zwischendatei Z88H.IN geoeffnet\n");
    if(LANG == 2) printf("buffer file Z88H.IN opened\n");
  break;

  case TX_I1OPEN:
    if(LANG == 1) printf("Z88I1.TXT geoeffnet\n");
    if(LANG == 2) printf("Z88I1.TXT opened\n");
  break;

  case TX_I2OPEN:
    if(LANG == 1) printf("Z88I2.TXT geoeffnet\n");
    if(LANG == 2) printf("Z88I2.TXT opened\n");
  break;

  case TX_I5OPEN:
    if(LANG == 1) printf("Z88I5.TXT geoeffnet\n");
    if(LANG == 2) printf("Z88I5.TXT opened\n");
  break;

  case TX_OUTOPEN:
    if(LANG == 1) printf("Zwischendatei Z88H.OUT geoeffnet\n");
    if(LANG == 2) printf("buffer file Z88H.OUT opened\n");
  break;

  case TX_MEMOK:
    if(LANG == 1) printf("Memory angelegt\n");
    if(LANG == 2) printf("memory allocated\n");
  break;

  case TX_1STOP:
    if(LANG == 1) printf("Grad = " PD ", zu hoch\n",i);
    if(LANG == 2) printf("grade = " PD ", to big\n",i);
  break;

  case TX_STARTNUM:
    if(LANG == 1) ("  Startnummer = " PD "\n",i);
    if(LANG == 2) ("  start number = " PD "\n",i);
  break;

  case TX_LEVEL:
    if(LANG == 1) ("\rLevel=" PD,i);
    if(LANG == 2) ("\rlevel=" PD,i);
  break;

  case TX_MAXGR:
    if(LANG == 1) printf("Max. Grad = " PD,i);
    if(LANG == 2) printf("max. grade = " PD,i);
  break;

  case TX_STOPERM:
    if(i == 1)
      {
      if(LANG == 1) printf("\nAbspeichern Permutationsvektor, umkehrter CM\n");
      if(LANG == 2) printf("\nstoring permutation vector, reverse CM\n");
      }
    if(i == 2)
      {
      if(LANG == 1) printf("\Abspeichern Permutationsvektor, normaler CM\n");
      if(LANG == 2) printf("\nstoring permutation vector, normal CM\n");
      }
  break;

  case TX_UMSPEI:
    if(LANG == 1) printf("Umspeichern der Files\n");
    if(LANG == 2) printf("storing files\n");
  break;

  case TX_NPRCM:
    if(LANG == 1) ("  Profil = " PD "\n",i);
    if(LANG == 2) ("  profile = " PD "\n",i);
  break;

  case TX_NPRRCM:
    if(LANG == 1) ("  Umgekehrtes Profil = " PD "\n",i);
    if(LANG == 2) ("  reverse profile = " PD "\n",i);
  break;

  case TX_TXT2OLD:
    if(LANG == 1) printf("Bisherige Z88I*.TXT in Z88I*.OLD sichern\n");
    if(LANG == 2) printf("copying existing Z88I*.TXT into Z88I*.OLD\n");
  break;

  case TX_WRII1:
    if(LANG == 1) printf("Nun Z88I1.TXT erzeugen\n");
    if(LANG == 2) printf("now building Z88I1.TXT\n");
  break;

  case TX_WRII2:
    if(LANG == 1) printf("Nun Z88I2.TXT erzeugen\n");
    if(LANG == 2) printf("now building Z88I2.TXT\n");
  break;

  case TX_WRII5:
    if(LANG == 1) printf("Nun Z88I5.TXT erzeugen\n");
    if(LANG == 2) printf("now building Z88I5.TXT\n");
  break;

  case TX_Z88DONE:
    if(LANG == 1) printf("Alle Dateien geschlossen. Z88H fertig.\n");
    if(LANG == 2) printf("All files closed. Z88H done\n");
  break;
  }
return(0);
}

