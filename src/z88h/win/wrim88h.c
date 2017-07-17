/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows OS.
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
* wrim88h gibt Texte aus (1 FR_INT4)
* 30.7.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer Windows 
***********************************************************************/
#ifdef FR_WIN
#include <z88h.h>
#include <windows.h>
#include <string.h>   /* strlen  */
#include <stdio.h>    /* sprintf */
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
extern HDC hDC;
extern FR_INT4 LANG;

size_t laenge;

char cline[80];

switch(iatx)
  {
  case TX_INOPEN:
    if(LANG == 1) TextOut(hDC,10,50,"Puffer Z88H.IN geoeffnet",24);
    if(LANG == 2) TextOut(hDC,10,50,"buffer Z88H.IN opened",21);
  break;

  case TX_I1OPEN:
    if(LANG == 1) TextOut(hDC,200,50,"Z88I1.TXT geoeffnet",19);
    if(LANG == 2) TextOut(hDC,200,50,"Z88I1.TXT opened",16);
  break;

  case TX_I2OPEN:
    if(LANG == 1) TextOut(hDC,10,70,"Z88I2.TXT geoeffnet",19);
    if(LANG == 2) TextOut(hDC,10,70,"Z88I2.TXT opened",16);
  break;

  case TX_I5OPEN:
    if(LANG == 1) TextOut(hDC,200,70,"Z88I5.TXT geoeffnet",19);
    if(LANG == 2) TextOut(hDC,200,70,"Z88I5.TXT opened",16);
  break;

  case TX_OUTOPEN:
    if(LANG == 1) TextOut(hDC,10,70,"Puffer Z88H.OUT geoeffnet",25);
    if(LANG == 2) TextOut(hDC,10,70,"buffer Z88H.OUT opened",22);
  break;

  case TX_MEMOK:
    if(LANG == 1) TextOut(hDC,10,90,"Memory angelegt",15);
    if(LANG == 2) TextOut(hDC,10,90,"memory allocated",16);
  break;

  case TX_1STOP:
    if(LANG == 1) sprintf(cline,"Grad = " PD ", zu hoch",i);
    if(LANG == 2) sprintf(cline,"grade = " PD ",too big",i);
    laenge= strlen(cline);
    TextOut(hDC,200,90,cline,laenge);
  break;

  case TX_MAXGR:
    if(LANG == 1) sprintf(cline,"Max. Grad = " PD,i);
    if(LANG == 2) sprintf(cline,"max. grade= " PD,i);
    laenge= strlen(cline);
    TextOut(hDC,10,110,cline,laenge);
  break;

  case TX_STARTNUM:
    if(LANG == 1) sprintf(cline,"Startnummer = " PD,i);
    if(LANG == 2) sprintf(cline,"start number= " PD,i);
    laenge= strlen(cline);
    TextOut(hDC,200,110,cline,laenge);
  break;

  case TX_LEVEL:
    if(LANG == 1) sprintf(cline,"Level = " PD,i);
    if(LANG == 2) sprintf(cline,"level = " PD,i);
    laenge= strlen(cline);
    TextOut(hDC,10,130,cline,laenge);
  break;

  case TX_STOPERM:
    if(i == 1)
      {
      if(LANG == 1) sprintf(cline,"Abspeichern Permutationsvektor, umkehrter CM");
      if(LANG == 2) sprintf(cline,"storing permutation vector, reverse CM");
      }
    if(i == 2)
      {
      if(LANG == 1) sprintf(cline,"Abspeichern Permutationsvektor, normaler CM");
      if(LANG == 2) sprintf(cline,"storing permutation vector, normal CM");
      }
    laenge= strlen(cline);
    TextOut(hDC,10,150,cline,laenge);
  break;

  case TX_UMSPEI:
    if(LANG == 1) sprintf(cline,"Umspeichern der Files");
    if(LANG == 2) sprintf(cline,"storing files");
    laenge= strlen(cline);
    TextOut(hDC,200,130,cline,laenge);
  break;

  case TX_NPRCM:
    if(LANG == 1) sprintf(cline,"Profil = " PD,i);
    if(LANG == 2) sprintf(cline,"profile= " PD,i);
    laenge= strlen(cline);
    TextOut(hDC,10,170,cline,laenge);
  break;

  case TX_NPRRCM:
    if(LANG == 1) sprintf(cline,"Umgekehrtes Profil = " PD,i);
    if(LANG == 2) sprintf(cline,"reverse profile= " PD,i);
    laenge= strlen(cline);
    TextOut(hDC,200,170,cline,laenge);
  break;

  case TX_TXT2OLD:
    if(LANG == 1) sprintf(cline,"Bisherige Z88I*.TXT in Z88I*.OLD sichern");
    if(LANG == 2) sprintf(cline,"copying existing Z88I*.TXT into Z88I*.OLD");
    laenge= strlen(cline);
    TextOut(hDC,10,190,cline,laenge);
  break;

  case TX_WRII1:
    if(LANG == 1) sprintf(cline,"Nun Z88I1.TXT erzeugen");
    if(LANG == 2) sprintf(cline,"now building Z88I1.TXT");
    laenge= strlen(cline);
    TextOut(hDC,10,210,cline,laenge);
  break;

  case TX_WRII2:
    if(LANG == 1) sprintf(cline,"nun Z88I2.TXT erzeugen");
    if(LANG == 2) sprintf(cline,"now building Z88I2.TXT");
    laenge= strlen(cline);
    TextOut(hDC,200,210,cline,laenge);
  break;

  case TX_WRII5:
    if(LANG == 1) sprintf(cline,"nun Z88I5.TXT erzeugen");
    if(LANG == 2) sprintf(cline,"now building Z88I5.TXT");
    laenge= strlen(cline);
    TextOut(hDC,10,230,cline,laenge);
  break;

  case TX_Z88DONE:
    if(LANG == 1) TextOut(hDC,10,250,"Alle Dateien geschlossen. Ende Z88H",35);
    if(LANG == 2) TextOut(hDC,10,250,"All files closed. Z88H done",27);
  break;
  }
return(0);
}

