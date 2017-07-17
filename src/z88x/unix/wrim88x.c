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
/***********************************************************************
* wrim88x gibt Texte aus (1 FR_INT4)
* 30.7.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88x.h>
#include <stdio.h>    /* printf */
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
*  hier beginnt Function wrim88x
***********************************************************************/
int wrim88x(FR_INT4 i,int iatx)
{
extern FR_INT4 LANG;
extern char cflag[];

switch(iatx)
  {
  case TX_Z88TX:
    if(LANG==1) printf("Start Z88TX: von Z88 nach DXF\n");
    if(LANG==2) printf("start Z88TX: from Z88 to DXF\n");
  break;

  case TX_CFLAG:
    if(LANG==1) printf("Steuerflag ist %s (interne Kennung " PD ")\n",cflag,i);
    if(LANG==2) printf("flag is %s (internal ID " PD ")\n",cflag,i);
  break;

  case TX_ELE:
      if(LANG==1) printf("\rElement " PD,i);
      if(LANG==2) printf("\relement " PD,i);
  break;

  case TX_REAI1:
    if(LANG==1) printf("Z88I1.TXT einlesen\n");
    if(LANG==2) printf("reading Z88I1.TXT\n");
  break;

  case TX_REAI2:
    if(LANG==1) printf("Z88I2.TXT einlesen\n");
    if(LANG==2) printf("reading Z88I2.TXT\n");
  break;

  case TX_REAI5:
    if(LANG==1) printf("Z88I5.TXT einlesen\n");
    if(LANG==2) printf("reading Z88I5.TXT\n");
  break;

  case TX_REANI:
    if(LANG==1) printf("Z88NI.TXT einlesen\n");
    if(LANG==2) printf("reading Z88NI.TXT\n");
  break;

  case TX_KOOR:
    if(LANG==1) printf("Koordinaten einlesen\n");
    if(LANG==2) printf("reading coordinates\n");
  break;

  case TX_POLAR:
    if(LANG==1) printf("Polar/Zylinder-Koordinaten umrechnen\n");
    if(LANG==2) printf("converting polar/cylinder coordinates\n");
  break;

  case TX_KOIN:
    if(LANG==1) printf("Koinzidenz einlesen\n");
    if(LANG==2) printf("reading element informations\n");
  break;

  case TX_SINFO:
    if(LANG==1) printf("Superelement-Informationen einlesen\n");
    if(LANG==2) printf("reading superelement informations\n");
  break;

  case TX_Z88FX:
    if(LANG==1) printf("Start Z88FX: von DXF nach Z88\n");
    if(LANG==2) printf("Start Z88FX: from DXF to Z88\n");
  break;

  case TX_FX:
    if(LANG==1) printf("Oeffnen Z88X.DXF\n");
    if(LANG==2) printf("opening Z88X.DXF\n");
  break;

  case TX_DEC1ZI1:
    if(LANG==1) printf("Decodieren Z88X.DXF, Z88I1.TXT 1.Zeile aufbauen\n");
    if(LANG==2) printf("decoding Z88X.DXF, Z88I1.TXT building first line\n");
  break;

  case TX_DEC1ZNI:
    if(LANG==1) printf("Decodieren Z88X.DXF, Z88NI.TXT 1.Zeile aufbauen\n");
    if(LANG==2) printf("decoding Z88X.DXF, Z88NI.TXT building first line\n");
  break;

  case TX_DECKNO:
    if(LANG==1) printf("Decodieren Z88X.DXF, Knoten aufbauen\n");
    if(LANG==2) printf("decoding Z88X.DXF, building nodes\n");
  break;

  case TX_FOUKNO:
    if(LANG==1) printf(PD " Knoten gefunden\n",i);
    if(LANG==2) printf(PD " nodes detected\n",i);
  break;

  case TX_DECELE:
    if(LANG==1) printf("Decodieren Z88X.DXF, Elemente aufbauen\n");
    if(LANG==2) printf("decoding Z88X.DXF, building elements\n");
  break;

  case TX_FOUFELE:
    if(LANG==1) printf(PD " Finite Elemente gefunden\n",i);
    if(LANG==2) printf(PD " finite elements detected\n",i);
  break;

  case TX_FOUSELE:
    if(LANG==1) printf(PD " Super-Elemente gefunden\n",i);
    if(LANG==2) printf(PD " superelements detected\n",i);
  break;

  case TX_DEC1ZI2:
    if(LANG==1) printf("Decodieren Z88X.DXF, Z88I2.TXT Anzahl Randbed. aufbauen\n");
    if(LANG==2) printf("decoding Z88X.DXF, Z88I2.TXT building no. of constraints\n");
  break;

  case TX_DECI2R:
    if(LANG==1) printf("Decodieren Z88X.DXF, Z88I2.TXT Randbedingungen aufbauen\n");
    if(LANG==2) printf("decoding Z88X.DXF, Z88I2.TXT building constraints\n");
  break;

  case TX_DEC1ZI5:
    if(LANG==1) printf("Decodieren Z88X.DXF, Z88I5.TXT Anzahl Flaechenlasten aufbauen\n");
    if(LANG==2) printf("decoding Z88X.DXF, Z88I5.TXT building no. of surface loads\n");
  break;

  case TX_DECI5R:
    if(LANG==1) printf("Decodieren Z88X.DXF, Z88I5.TXT Flaechenlasten aufbauen\n");
    if(LANG==2) printf("decoding Z88X.DXF, Z88I5.TXT building surface loads\n");
  break;

  case TX_REAIX:
    if(LANG==1) printf("Z88X.DXF einlesen\n");
    if(LANG==2) printf("reading Z88X.DXF\n");
  break;

  case TX_FAC:
    if(LANG==1) printf("Faktoren berechnen\n");
    if(LANG==2) printf("computing factors\n");
  break;

  case TX_SDXF:
    if(LANG==1) printf("DXF-Steuerwerte schreiben\n");
    if(LANG==2) printf("writing DXF main flags\n");
  break;

  case TX_SELE:
    if(LANG==1) printf("DXF-Entities schreiben\n");
    if(LANG==2) printf("writing DXF entities\n");
  break;

  case TX_EXITZ88TX:
    if(LANG==1) printf("Verlassen Z88TX\n");
    if(LANG==2) printf("leaving Z88TX\n");
  break;

  case TX_EXITZ88FX:
    if(LANG==1) printf("Verlassen Z88FX\n");
    if(LANG==2) printf("leaving Z88FX\n");
  break;

  case TX_EXITZ88X:
    if(LANG==1) printf("Ende Z88X\n");
    if(LANG==2) printf("Z88X finished\n");
  break;

  case TX_WRII1:
    if(LANG==1) printf("Beschreiben von Z88I1.TXT\n");
    if(LANG==2) printf("writing Z88I1.TXT\n");
  break;

  case TX_WRINI:
    if(LANG==1) printf("Beschreiben von Z88NI.TXT\n");
    if(LANG==2) printf("writing Z88NI.TXT\n");
  break;

  case TX_WRII2:
    if(LANG==1) printf("Beschreiben von Z88I2.TXT\n");
    if(LANG==2) printf("writing Z88I2.TXT\n");
  break;

  case TX_WRII5:
    if(LANG==1) printf("Beschreiben von Z88I5.TXT\n");
    if(LANG==2) printf("writing Z88I5.TXT\n");
  break;
  }
return(0);
}

