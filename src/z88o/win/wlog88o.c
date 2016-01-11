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
* wlog88o gibt Log-Datei-Meldungen aus (1 FR_INT4, 1 int)
* 3.8.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88o.h>
#include <stdio.h>  /* fprintf, fflush */
#endif

/***********************************************************************
* Leseformate
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
* hier beginnt Function wlog88o
***********************************************************************/
int wlog88o(FR_INT4 i,int iatx)
{
extern FILE *fwlo;

extern FR_INT4 LANG;

switch(iatx)
  {
  case LOG_BZ88OWIN:
    if(LANG == 1) fprintf(fwlo,"Start Z88O Version 14OS");
    if(LANG == 2) fprintf(fwlo,"start Z88O version 14OS");
    fflush(fwlo);
  break;

  case LOG_OPENDYN:
    if(LANG == 1) fprintf(fwlo,"\nOeffnen der Datei Z88.DYN");
    if(LANG == 2) fprintf(fwlo,"\nopening file Z88.DYN");
    fflush(fwlo);
  break;

  case LOG_NODYN:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88.DYN nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88.DYN ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOACROBAT:
    if(LANG == 1) fprintf(fwlo,"\n??? kann PDF-Viewer nicht oeffnen ???");
    if(LANG == 2) fprintf(fwlo,"\n??? cannot open PDF Viewer ???");
    fflush(fwlo);
  break;

  case LOG_WRONGDYN:
    if(LANG == 1) fprintf(fwlo,"\n### File Z88.DYN ist nicht korrekt ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### file Z88.DYN is not correct ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOMAN:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88MAN.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88MAN.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_WRONGMAN:
    if(LANG == 1) fprintf(fwlo,"\n### File Z88MAN.TXT ist nicht korrekt ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### file Z88MAN.TXT is not correct ..stop ###");
    fflush(fwlo);
  break;


  case LOG_NOOGL:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88O.OGL nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88O.OGL ..stop ###");
    fflush(fwlo);
  break;

  case LOG_WRONGOGL:
    if(LANG == 1) fprintf(fwlo,"\n### File Z88O.OGL ist nicht korrekt ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### file Z88O.OGL is not correct ..stop ###");
    fflush(fwlo);
  break;

  case LOG_MAXKOI:
    fprintf(fwlo,"\nMAXKOI = " PD,i);
    fflush(fwlo);
  break;

  case LOG_MAXK:
    fprintf(fwlo,"\nMAXK   = " PD,i);
    fflush(fwlo);
  break;

  case LOG_MAXE:
    fprintf(fwlo,"\nMAXE   = " PD,i);
    fflush(fwlo);
  break;

  case LOG_OKDYN:
    if(LANG == 1) fprintf(fwlo,"\nDatei Z88.DYN gelesen..scheint formal o.k. zu sein");
    if(LANG == 2) fprintf(fwlo,"\nfile Z88.DYN read ..seems to be o.k.");
    fflush(fwlo);
  break;

  case LOG_ALLOCMEMY:
    if(LANG == 1) fprintf(fwlo,"\nDynamisches Memory anlegen:");
    if(LANG == 2) fprintf(fwlo,"\nallocating dynamic memory:");
    fflush(fwlo);
  break;

  case LOG_ARRAYNOTOK:
    if(LANG == 1) fprintf(fwlo,"\n### Memory Kennung " PD " nicht o.k. ..Stop ###",i);
    if(LANG == 2) fprintf(fwlo,"\n### memory id " PD " is not o.k. ..stop ###",i);
    fflush(fwlo);
  break;

  case LOG_ARRAYOK:
    if(LANG == 1) fprintf(fwlo,"\nMemory Kennung " PD " angelegt",i);
    if(LANG == 2) fprintf(fwlo,"\nmemory id " PD " allocated",i);
    fflush(fwlo);
  break;

  case LOG_SUMMEMY:
    if(LANG == 1) fprintf(fwlo,"\nDynamisches Memory total angefordert: " PD " Bytes",i);
    if(LANG == 2) fprintf(fwlo,"\ndynamic memory totally allocated: " PD " Bytes",i);
    fflush(fwlo);
  break;

  case LOG_EXITDYN88O:
    if(LANG == 1) fprintf(fwlo,"\nVerlassen Speichereinheit DYN88O");
    if(LANG == 2) fprintf(fwlo,"\nleaving storage function DYN88O");
    fflush(fwlo);
  break;

  case LOG_REAI2:
    if(LANG == 1) fprintf(fwlo,"\nStart Lesen Z88I2.TXT");
    if(LANG == 2) fprintf(fwlo,"\nstart reading Z88I2.TXT");
    fflush(fwlo);
  break;
 
  case LOG_REAI2OK:
    if(LANG == 1) fprintf(fwlo,"\nZ88I2.TXT fertig eingelesen");
    if(LANG == 2) fprintf(fwlo,"\nZ88I2.TXT totally read");
    fflush(fwlo);
  break;

  case LOG_REAO2:
    if(LANG == 1) fprintf(fwlo,"\nStart Lesen Z88O2.TXT");
    if(LANG == 2) fprintf(fwlo,"\nstart reading Z88O2.TXT");
    fflush(fwlo);
  break;
 
  case LOG_REAO2OK:
    if(LANG == 1) fprintf(fwlo,"\nZ88O2.TXT fertig eingelesen");
    if(LANG == 2) fprintf(fwlo,"\nZ88O2.TXT totally read");
    fflush(fwlo);
  break;

  case LOG_REAO8:
    if(LANG == 1) fprintf(fwlo,"\nStart Lesen Z88O8.TXT");
    if(LANG == 2) fprintf(fwlo,"\nstart reading Z88O8.TXT");
    fflush(fwlo);
  break;

  case LOG_REAO5:
    if(LANG == 1) fprintf(fwlo,"\nStart Lesen Z88O5.TXT");
    if(LANG == 2) fprintf(fwlo,"\nstart reading Z88O5.TXT");
    fflush(fwlo);
  break;

  case LOG_REAO8OK:
    if(LANG == 1) fprintf(fwlo,"\nZ88O8.TXT fertig eingelesen");
    if(LANG == 2) fprintf(fwlo,"\nZ88O8.TXT totally read");
    fflush(fwlo);
    break;

  case LOG_REAO5OK:
    if(LANG == 1) fprintf(fwlo,"\nZ88O5.TXT fertig eingelesen");
    if(LANG == 2) fprintf(fwlo,"\nZ88O5.TXT totally read");
    fflush(fwlo);
    break;

  case LOG_BRI588:
    if(LANG == 1) fprintf(fwlo,"\nStart Lesen Z88I5.TXT");
    if(LANG == 2) fprintf(fwlo,"\nstart reading Z88I5.TXT");
    fflush(fwlo);
  break;

  case LOG_EXITRI588:
    if(LANG == 1) fprintf(fwlo,"\nZ88I5.TXT fertig eingelesen");
    if(LANG == 2) fprintf(fwlo,"\nZ88I5.TXT totally read");
    fflush(fwlo);
    break;

  case LOG_NONINT0:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n### Integrationsordnung ist nicht Null        ###");
      fprintf(fwlo,"\n### Waehle Integrationsordnung 0 in Z88I3.TXT ###");
      fprintf(fwlo,"\n### Dann neuer Lauf Z88D ..Stop               ###");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### Integration constant is not zero           ###");
      fprintf(fwlo,"\n### Choose integration constant 0 in Z88I3.TXT ###");
      fprintf(fwlo,"\n### Then start an new Z88D run ..stop          ###");
      }
    fflush(fwlo);
  break;

  case LOG_REAI1:
    if(LANG == 1) fprintf(fwlo,"\nStart Lesen Z88I1.TXT");
    if(LANG == 2) fprintf(fwlo,"\nstart reading Z88I1.TXT");
    fflush(fwlo);
  break;

  case LOG_REAI1OK:
    if(LANG == 1) fprintf(fwlo,"\nZ88I1.TXT fertig eingelesen");
    if(LANG == 2) fprintf(fwlo,"\nZ88I1.TXT totally read");
    fflush(fwlo);
    break;

  case LOG_NOSTRFI:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n??? Versuchte Strukturfile zu laden   ???");
      fprintf(fwlo,"\n??? aber File nicht gefunden ..weiter ???");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n??? tried to load structure file        ???");
      fprintf(fwlo,"\n??? but could not find file  ..continue ???");
      }
    fflush(fwlo);
  break;

  case LOG_NOI2:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n??? Versuchte Z88I2.TXT zu laden      ???");
      fprintf(fwlo,"\n??? aber File nicht gefunden ..weiter ???");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n??? tried to load Z88I2.TXT            ???");
      fprintf(fwlo,"\n??? but could not find file ..continue ???");
      }
    fflush(fwlo);
  break;

  case LOG_NOO2:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n??? Versuchte Z88O2.TXT zu laden      ???");
      fprintf(fwlo,"\n??? aber File nicht gefunden ..weiter ???");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n??? tried to load Z88O2.TXT            ???");
      fprintf(fwlo,"\n??? but could not find file ..continue ???");
      }
    fflush(fwlo);
  break;

  case LOG_NOI5:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n??? Versuchte Z88I5.TXT zu laden      ???");
      fprintf(fwlo,"\n??? aber File nicht gefunden ..weiter ???");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n??? tried to load Z88I5.TXT            ???");
      fprintf(fwlo,"\n??? but could not find file ..continue ???");
      }
    fflush(fwlo);
  break;

  case LOG_NOO8:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n??? Versuchte Z88O8.TXT zu laden      ???");
      fprintf(fwlo,"\n??? aber File nicht gefunden ..weiter ???");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n??? tried to load Z88O8.TXT            ???");
      fprintf(fwlo,"\n??? but could not find file ..continue ???");
      }
    fflush(fwlo);
  break;

  case LOG_NOO5:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n??? Versuchte Z88O5.TXT zu laden      ???");
      fprintf(fwlo,"\n??? aber File nicht gefunden ..weiter ???");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n??? tried to load Z88O5.TXT            ???");
      fprintf(fwlo,"\n??? but could not find file ..continue ???");
      }
    fflush(fwlo);
  break;

  case LOG_EXMAXK:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n### Mehr als " PD " Knoten, zuwenig Memory ###",i);
      fprintf(fwlo,"\n### Abhilfe: MAXK in Z88.DYN erhoehen..Stop ###");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### more than " PD " nodes, memory exhausted ###",i);
      fprintf(fwlo,"\n### recover: increase MAXK in Z88.DYN..stop ###");
      }
    fflush(fwlo);
  break;

  case LOG_EXMAXKOI:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n### " PD " ueberschreitet MAXKOI, zuwenig Memory ###",i);
      fprintf(fwlo,"\n### Abhilfe: MAXKOI in Z88.DYN erhoehen..Stop ###");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### more than " PD " for MAXKOI, memory exhausted ###",i);
      fprintf(fwlo,"\n### recover: increase MAXKOI in Z88.DYN..stop  ###");
      }
    fflush(fwlo);
  break;

  case LOG_EXMAXE:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n### Mehr als " PD " Elemente, zuwenig Memory ###",i);
      fprintf(fwlo,"\n### Abhilfe: MAXE in Z88.DYN erhoehen..Stop ###");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### more than " PD " elements, memory exhausted ###",i);
      fprintf(fwlo,"\n### recover: increase MAXE in Z88.DYN..stop ###");
      }
    fflush(fwlo);
  break;

  case LOG_EXMAXPR:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n### Zuviele Drucklasten, zuwenig Memory ###");
      fprintf(fwlo,"\n### Abhilfe: MAXPR in Z88.DYN erhoehen..Stop ###");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### too many pressure loads, memory exhausted ###");
      fprintf(fwlo,"\n### recover: increase MAXPR in Z88.DYN..stop ###");
      }
    fflush(fwlo);
  break;

  case LOG_EXMAXRBD:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n### Zuviele Randbedingungen, zuwenig Memory ###");
      fprintf(fwlo,"\n### Abhilfe: MAXRBD in Z88.DYN erhoehen..Stop ###");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### too many boundary conditions, memory exhausted ###");
      fprintf(fwlo,"\n### recover: increase MAXRBD in Z88.DYN..stop ###");
      }
    fflush(fwlo);
  break;

  case LOG_WRONGDIM:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n### Falsche Dimension in Z88I1.TXT bzw. Z88NI.TXT ###");
      fprintf(fwlo,"\n### Abhilfe : Dimension 2 oder 3 waehlen ..Stop   ###");
      }   
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### wrong dimension in Z88I1.TXT or Z88NI.TXT ###");
      fprintf(fwlo,"\n### recover: choose dimension 2 or 3 ..stop   ###");
      }   
    fflush(fwlo);
  break;

  case LOG_NINT0:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n### Integrationsordnung ist Null, d.h. Eckknoten  ###");
      fprintf(fwlo,"\n### Waehle Integrationsordnung 1..4 in Z88INT.TXT ###");
      fprintf(fwlo,"\n### Dann neuer Lauf Z88R ..Stop                   ###");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### Integration constant is zero, corner node      ###");
      fprintf(fwlo,"\n### Choose integration constant 1..4 in Z88INT.TXT ###");
      fprintf(fwlo,"\n### Then start an new Z88R run ..stop              ###");
      }
    fflush(fwlo);
  break;

  case LOG_EXMAXGP:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n### Mehr als " PD " Gausspunkte fuer Spannungen  ###",i);
      fprintf(fwlo,"\n### Abhilfe: MAXGP in Z88.DYN erhoehen ..Stop ###");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### More than " PD " Gauss points for stresses   ###",i);
      fprintf(fwlo,"\n### Recover: increase MAXGP in Z88.DYN ..Stop ###");
      }
    fflush(fwlo);
  break;
  }
return(0);
}

