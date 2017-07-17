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
* V15.0  November 18 2015
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
* Function wrim88n gibt Texte aus
* 31.7.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88n.h>
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
* hier beginnt Function wrim88n
***********************************************************************/
int wrim88n(FR_INT4 i,int iatx)
{
extern HDC hDC;
extern FR_INT4 LANG;

size_t laenge;

char cline[80];

switch(iatx)
  {
  case TX_SUPERELE:
    if(LANG == 1) sprintf(cline,"Superelement " PD,i);
    if(LANG == 2) sprintf(cline,"super element " PD,i);
    laenge= strlen(cline);
    TextOut(hDC,250,110,cline,laenge);
  break;

  case TX_REANI:
    if(LANG == 1) TextOut(hDC,10,50,"Z88NI.TXT einlesen :",20);
    if(LANG == 2) TextOut(hDC,10,50,"reading Z88NI.TXT :",19);
  break;

  case TX_BERJOIN:
    if(LANG == 1) TextOut(hDC,10,70,"Vektor JOIN berechnen",21);
    if(LANG == 2) TextOut(hDC,10,70,"computing vector JOIN",21);
  break;

  case TX_BERKOOR:
    if(LANG == 1) TextOut(hDC,10,90,"Koordinaten berechnen",21);
    if(LANG == 2) TextOut(hDC,10,90,"computing coordinates",21);
  break;

  case TX_BERKOIN:
    if(LANG == 1) TextOut(hDC,10,110,"Koinzidenz berechnen",20);
    if(LANG == 2) TextOut(hDC,10,110,"computing element infos",23);
  break;

  case TX_WRII1:
    if(LANG == 1) TextOut(hDC,10,130,"Z88I1.TXT beschreiben, Ende Z88N",32);
    if(LANG == 2) TextOut(hDC,10,130,"writing Z88I1.TXT, Z88N done",28);
  break;

  }
return(0);
}

