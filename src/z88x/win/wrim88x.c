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
* V14.0  February 14, 2011
*
* Z88 should compile and run under any Windows release, starting
* with Windows95.
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
* wrim88x gibt Texte aus (1 FR_INT4)
* 30.7.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88x.h>
#include <windows.h>
#include <string.h>   /* strlen  */
#include <stdio.h>    /* sprintf */
#include <stdlib.h>   /* ltoa    */
#endif

/***********************************************************************
* Formatbeschreiber
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
*  hier beginnt Function wrim88f
***********************************************************************/
int wrim88x(FR_INT4 i,int iatx)
{
extern HDC hDC;
extern FR_INT4 LANG;

size_t laenge;

char cline[80];

switch(iatx)
  {
/*---------------------------------------------------------------------
* fuer Z88TX
*--------------------------------------------------------------------*/
  case TX_REAI1:
    if(LANG == 1) TextOut(hDC,10,50,"Z88I1.TXT einlesen",18);
    if(LANG == 2) TextOut(hDC,10,50,"Reading Z88I1.TXT",17);
  break;

  case TX_REANI:
    if(LANG == 1) TextOut(hDC,10,50,"Z88NI.TXT einlesen",18);
    if(LANG == 2) TextOut(hDC,10,50,"Reading Z88NI.TXT",17);
  break;

  case TX_KOOR:
    if(LANG == 1) TextOut(hDC,10,70,"Koordinaten einlesen",20);
    if(LANG == 2) TextOut(hDC,10,70,"Reading coordinates",19);
  break;

  case TX_POLAR:
    if(LANG == 1) 
      TextOut(hDC,10,90,"Polar- auf kartesische Koordinaten umrechnen",42);
    if(LANG == 2) 
      TextOut(hDC,10,90,"Converting polar to cartesian coordinates",39);
  break;

  case TX_KOIN:
    if(LANG == 1) TextOut(hDC,10,110,"Koinzidenz einlesen",19);
    if(LANG == 2) TextOut(hDC,10,110,"Reading element infos",21);
  break;

  case TX_SINFO:
    if(LANG == 1) TextOut(hDC,10,150,"und Superelement-Infos einlesen",31);
    if(LANG == 2) TextOut(hDC,10,150,"and reading superelement infos",30);
  break;

  case TX_REAI2:
    if(LANG == 1) TextOut(hDC,10,170,"Z88I2.TXT einlesen",18);
    if(LANG == 2) TextOut(hDC,10,170,"Reading Z88I2.TXT",17);
  break;

  case TX_REAI5:
    if(LANG == 1) TextOut(hDC,10,210,"Z88I5.TXT einlesen",18);
    if(LANG == 2) TextOut(hDC,10,210,"Reading Z88I5.TXT",17);
  break;

  case TX_Z88TX:
    if(LANG == 1) TextOut(hDC,10,230,"Start Z88TX: von Z88 nach DXF",29);
    if(LANG == 2) TextOut(hDC,10,230,"Start Z88TX: from Z88 to DXF",28);
  break;

  case TX_FX:
    if(LANG == 1) TextOut(hDC,10,250,"Oeffnen Z88X.DXF",16);
    if(LANG == 2) TextOut(hDC,10,250,"Opening Z88X.DXF",16);
  break;

  case TX_FAC:
    if(LANG == 1) TextOut(hDC,10,270,"Faktoren berechnen",18);
    if(LANG == 2) TextOut(hDC,10,270,"Computing factors",17);
  break;

  case TX_SDXF:
    if(LANG == 1) TextOut(hDC,10,290,"DXF-Steuerwerte schreiben",25);
    if(LANG == 2) TextOut(hDC,10,290,"Writing DXF main flags",22);
  break;

  case TX_SELE:
    if(LANG == 1) TextOut(hDC,10,310,"DXF-Entities schreiben",22);
    if(LANG == 2) TextOut(hDC,10,310,"Writing DXF entities",20);
  break;

  case TX_EXITZ88TX:
    if(LANG == 1) TextOut(hDC,10,330,"Verlassen Z88TX, Z88X fertig",28);
    if(LANG == 2) TextOut(hDC,10,330,"Leaving Z88TX, Z88X done",24);
  break;

/*---------------------------------------------------------------------
* fuer Z88FX
*--------------------------------------------------------------------*/
  case TX_Z88FX:
    if(LANG == 1) TextOut(hDC,10,50,"Start Z88FX: von DXF nach Z88",29);
    if(LANG == 2) TextOut(hDC,10,50,"Start Z88FX: from DXF to Z88",28);
  break;

  /* case TX_FX, gibts es schon oben */

  case TX_REAIX:
    if(LANG == 1) TextOut(hDC,10,70,"Z88X.DXF einlesen",17);
    if(LANG == 2) TextOut(hDC,10,70,"Reading Z88X.DXF",16);
  break;

  case TX_DEC1ZI1:
    if(LANG == 1) 
      TextOut(hDC,10,90,"Decodieren DXF, 1.Zeile .. (Z88I1.TXT)",38);
    if(LANG == 2) 
      TextOut(hDC,10,90,"Decoding DXF, first line ..(Z88I1.TXT)",38);
  break;

  case TX_DEC1ZNI:
    if(LANG == 1) 
      TextOut(hDC,10,90,"Decodieren DXF, 1.Zeile .. (Z88NI.TXT)",38);
    if(LANG == 2) 
      TextOut(hDC,10,90,"Decoding DXF, first line ..(Z88NI.TXT)",38);
  break;

  case TX_DECKNO:
    if(LANG == 1) TextOut(hDC,10,110,"Decodieren DXF, Knoten ..",25);
    if(LANG == 2) TextOut(hDC,10,110,"Decoding DXF, nodes .....",25);
  break;

  case TX_FOUKNO:
    if(LANG == 1) sprintf(cline,PD " Knoten gefunden",i);
    if(LANG == 2) sprintf(cline,PD " nodes detected",i);
    laenge= strlen(cline);
    TextOut(hDC,200,110,cline,laenge);
  break;

  case TX_DECELE:
    if(LANG == 1) TextOut(hDC,10,130,"Decodieren DXF, Elemente ..",27);
    if(LANG == 2) TextOut(hDC,10,130,"Decoding DXF, elements ....",27);
  break;

  case TX_FOUSELE:
    if(LANG == 1) sprintf(cline,PD " Super-Ele. gefunden",i);
    if(LANG == 2) sprintf(cline,PD " super ele. detected",i);
    laenge= strlen(cline);
    TextOut(hDC,210,130,cline,laenge);
  break;

  case TX_FOUFELE:
    if(LANG == 1) sprintf(cline,PD " Finite Ele. gefunden",i);
    if(LANG == 2) sprintf(cline,PD " finite ele. detected",i);
    laenge= strlen(cline);
    TextOut(hDC,210,130,cline,laenge);
  break;

  case TX_DEC1ZI2:
    if(LANG == 1) 
      TextOut(hDC,10,170,"Decodieren DXF, # Randbed... (Z88I2.TXT)",40);
    if(LANG == 2) 
      TextOut(hDC,10,170,"Decoding DXF, # constraints..(Z88I2.TXT)",40);
  break;

  case TX_DECI2R:
    if(LANG == 1) 
      TextOut(hDC,10,190,"Decodieren DXF,Randbeding... (Z88I2.TXT)",40);
    if(LANG == 2) 
      TextOut(hDC,10,190,"Decoding DXF, constraints... (Z88I2.TXT)",40);
  break;

  case TX_DEC1ZI5:
    if(LANG == 1) 
      TextOut(hDC,10,230,"Decodieren DXF, # Flaechenl..(Z88I5.TXT)",40);
    if(LANG == 2) 
      TextOut(hDC,10,230,"Decoding DXF, # surface loads(Z88I5.TXT)",40);
  break;

  case TX_DECI5R:
    if(LANG == 1) 

      TextOut(hDC,10,250,"Decodieren DXF,Flaechenlasten(Z88I2.TXT)",40);
    if(LANG == 2) 
      TextOut(hDC,10,250,"Decoding DXF, surface loads  (Z88I2.TXT)",40);
  break;

  case TX_WRII1:
    if(LANG == 1) TextOut(hDC,10,270,"Z88I1.TXT beschreiben",21);
    if(LANG == 2) TextOut(hDC,10,270,"Now writing Z88I1.TXT",21);
  break;

  case TX_WRINI:
    if(LANG == 1) TextOut(hDC,10,270,"Z88NI.TXT beschreiben",21);
    if(LANG == 2) TextOut(hDC,10,270,"Now writing Z88NI.TXT",21);
  break;

  case TX_WRII2:
    if(LANG == 1) TextOut(hDC,10,290,"Z88I2.TXT beschreiben",21);
    if(LANG == 2) TextOut(hDC,10,290,"Now writing Z88I2.TXT",21);
  break;

  case TX_WRII5:
    if(LANG == 1) TextOut(hDC,10,330,"Z88I5.TXT beschreiben",21);
    if(LANG == 2) TextOut(hDC,10,330,"Now writing Z88I5.TXT",21);
  break;

  case TX_EXITZ88FX:
    if(LANG == 1) TextOut(hDC,10,350,"Verlassen Z88FX, Z88X fertig",28);
    if(LANG == 2) TextOut(hDC,10,350,"Leaving Z88FX, Z88X done",24);
  break;

  }
return(0);
}

