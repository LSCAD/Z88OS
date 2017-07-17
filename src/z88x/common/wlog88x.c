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
* wlog88x gibt Log-Datei-Meldungen aus (1 FR_INT4, 1 int)
* 25.11.2015 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88x.h>
#include <stdio.h>   /* FILE,fprintf,fflush */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88x.h>
#include <stdio.h>   /* FILE,fprintf,fflush */
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
*  hier beginnt Function wlog88x
***********************************************************************/
int wlog88x(FR_INT4 i,int iatx)
{
extern FILE *fwlo;
extern FR_INT4 LANG;

switch(iatx)
  {
  case LOG_BZ88X:
    fprintf(fwlo,"Start Z88X Version 15OS");
    fflush(fwlo);
  break;

  case LOG_CFLAGI1TX:
    if(LANG == 1) fprintf(fwlo,"\nSteuerflag CFLAG fuer Z88X ist -I1TX, ICFLAG = " PD,i);
    if(LANG == 2) fprintf(fwlo,"\nflag CFLAG for Z88X is -I1TX, ICFLAG = " PD,i);
    fflush(fwlo);
  break;

  case LOG_CFLAGIATX:
    if(LANG == 1) fprintf(fwlo,"\nSteuerflag CFLAG fuer Z88X ist -IATX, ICFLAG = " PD,i);
    if(LANG == 2) fprintf(fwlo,"\nflag CFLAG for Z88X is -IATX, ICFLAG = " PD,i);
    fflush(fwlo);
  break;

  case LOG_CFLAGNITX:
    if(LANG == 1) fprintf(fwlo,"\nSteuerflag CFLAG fuer Z88X ist -NITX, ICFLAG = " PD,i);
    if(LANG == 2) fprintf(fwlo,"\nflag CFLAG for Z88X is -NITX, ICFLAG = " PD,i);
    fflush(fwlo);
  break;

  case LOG_CFLAGI1FX:
    if(LANG == 1) fprintf(fwlo,"\nSteuerflag CFLAG fuer Z88X ist -I1FX, ICFLAG = " PD,i);
    if(LANG == 2) fprintf(fwlo,"\nflag CFLAG for Z88X is -I1FX, ICFLAG = " PD,i);
    fflush(fwlo);
  break;

  case LOG_CFLAGIAFX:
    if(LANG == 1) fprintf(fwlo,"\nSteuerflag CFLAG fuer Z88X ist -IAFX, ICFLAG = " PD,i);
    if(LANG == 2) fprintf(fwlo,"\nflag CFLAG for Z88X is -IAFX, ICFLAG = " PD,i);
    fflush(fwlo);
  break;

  case LOG_CFLAGNIFX:
    if(LANG == 1) fprintf(fwlo,"\nSteuerflag CFLAG fuer Z88X ist -NIFX, ICFLAG = " PD,i);
    if(LANG == 2) fprintf(fwlo,"\nflag CFLAG for Z88X is -NIFX, ICFLAG = " PD,i);
    fflush(fwlo);
  break;

  case LOG_OPENZ88DYN:
    if(LANG == 1) fprintf(fwlo,"\nOeffnen der Datei Z88.DYN");
    if(LANG == 2) fprintf(fwlo,"\nopening file Z88.DYN");
    fflush(fwlo);
  break;

  case LOG_NODYN:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88.DYN nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88.DYN ..stop ###");
    fflush(fwlo);
  break;

  case LOG_WRONGDYN:
    if(LANG == 1) fprintf(fwlo,"\n### File Z88.DYN ist nicht korrekt ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### file Z88.DYN is not correct ..stop ###");
    fflush(fwlo);
  break;

  case LOG_MAXKOI:
    fprintf(fwlo,"\nMAXKOI = " PD,i);
    fflush(fwlo);
  break;

  case LOG_MAXK:
    fprintf(fwlo,"\nMAXK   =  " PD,i);
    fflush(fwlo);
  break;

  case LOG_MAXE:
    fprintf(fwlo,"\nMAXE   = " PD,i);
    fflush(fwlo);
  break;

  case LOG_MAXNFG:
    fprintf(fwlo,"\nMAXNFG = " PD,i);
    fflush(fwlo);
  break;

  case LOG_MAXPR:
    fprintf(fwlo,"\nMAXPR = " PD,i);
    fflush(fwlo);
  break;

  case LOG_OKDYN:
    if(LANG == 1) fprintf(fwlo,"\nDatei Z88.DYN gelesen..scheint formal o.k. zu sein");
    if(LANG == 2) fprintf(fwlo,"\nfile Z88.DYN read .. seems to be o.k.");
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
    if(LANG == 1) fprintf(fwlo,"\nDynamisches Memory vollstaendig angefordert: " PD " Bytes",i);
    if(LANG == 2) fprintf(fwlo,"\ndynamic memory totally allocated: " PD " Bytes",i);
    fflush(fwlo);
  break;

  case LOG_EXITDYN88X:
    if(LANG == 1) fprintf(fwlo,"\nVerlassen Speichereinheit DYN88X");
    if(LANG == 2) fprintf(fwlo,"\nleaving memory function DYN88X");
    fflush(fwlo);
  break;

  case LOG_Z88TX:
    fprintf(fwlo,"\nStart Z88TX");
    fflush(fwlo);
  break;

  case LOG_BREA88:
    if(LANG == 1) fprintf(fwlo,"\nStart Leseeinheit REA88X");
    if(LANG == 2) fprintf(fwlo,"\nstart reading function REA88X");
    fflush(fwlo);
  break;

  case LOG_FI1:
    if(LANG == 1) fprintf(fwlo,"\nEinlesen von Z88I1.TXT");
    if(LANG == 2) fprintf(fwlo,"\nreading Z88I1.TXT");
    fflush(fwlo);
  break;

  case LOG_NOI1:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88I1.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88I1.TXT  ..stop ###");
    fflush(fwlo);
  break;

  case LOG_FI2:
    if(LANG == 1) fprintf(fwlo,"\nEinlesen von Z88I2.TXT");
    if(LANG == 2) fprintf(fwlo,"\nreading Z88I2.TXT");
    fflush(fwlo);
  break;

  case LOG_NOI2:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88I2.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88I2.TXT  ..stop ###");
    fflush(fwlo);
  break;

  case LOG_FI5:
    if(LANG == 1) fprintf(fwlo,"\nEinlesen von Z88I5.TXT");
    if(LANG == 2) fprintf(fwlo,"\nreading Z88I5.TXT");
    fflush(fwlo);
  break;

  case LOG_NOI5:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88I5.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88I5.TXT  ..stop ###");
    fflush(fwlo);
  break;

  case LOG_FNI:
    if(LANG == 1) fprintf(fwlo,"\nEinlesen von Z88NI.TXT");
    if(LANG == 2) fprintf(fwlo,"\nreading Z88NI.TXT");
    fflush(fwlo);
  break;

  case LOG_NONI:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88NI.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88NI.TXT  ..stop ###");
    fflush(fwlo);
  break;

  case LOG_WRONGDIM:
    if(LANG == 1) fprintf(fwlo,"\n### Dimension " PD " falsch ..Stop ###",i);
    if(LANG == 2) fprintf(fwlo,"\n### dimension " PD " wrong ..stop ###",i);
    fflush(fwlo);
  break;

  case LOG_EXMAXK:
    if(LANG == 1)
     {
     fprintf(fwlo,"\n### Nur " PD " Knoten im Speicher zulaessig ..Stop ###",i);
     fprintf(fwlo,"\n### Abhilfe: MAXK in Z88.DYN erhoehen ###");
     }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### only " PD " nodes in memory allowed ..stop ###",i);
      fprintf(fwlo,"\n### recover: increase MAXK in Z88.DYN ###");
      }
    fflush(fwlo);
  break;

  case LOG_EXMAXE:
    if(LANG == 1)
     {
     fprintf(fwlo,"\n### Nur " PD " Elemente im Speicher zulaessig ..Stop ###",i);
     fprintf(fwlo,"\n### Abhilfe: MAXE in Z88.DYN erhoehen ###");
     }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### only " PD " elements in memory allowed ..stop ###",i);
      fprintf(fwlo,"\n### recover: increase MAXE in Z88.DYN ###");
      }
    fflush(fwlo);
  break;

  case LOG_EXMAXKOI:
    if(LANG == 1) fprintf(fwlo,"\n### MAXKOI= " PD ", zu klein, in Z88.DYN hoeher setzen ..Stop ###",i);
    if(LANG == 2) fprintf(fwlo,"\n### MAXKOI= " PD ", too small, increase value in Z88.DYN ..stop ###",i);
    fflush(fwlo);
  break;

  case LOG_EXMAXNFG:
    if(LANG == 1)
     {
     fprintf(fwlo,"\n### Nur " PD " FG im Speicher zulaessig ..Stop ###",i);
     fprintf(fwlo,"\n### Abhilfe: MAXNFG in Z88.DYN erhoehen ###");
     }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### only " PD " DOF in memory allowed ..stop ###",i);
      fprintf(fwlo,"\n### recover: increase MAXNFG in Z88.DYN ###");
      }
    fflush(fwlo);
  break;

  case LOG_EXMAXPR:
    if(LANG == 1)
     {
     fprintf(fwlo,"\n### Nur " PD " Flaechenlasten im Speicher zulaessig ..Stop ###",i);
     fprintf(fwlo,"\n### Abhilfe: MAXPR in Z88.DYN erhoehen ###");
     }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### only " PD " surface loads in memory allowed ..stop ###",i);
      fprintf(fwlo,"\n### recover: increase MAXPR in Z88.DYN ###");
      }
    fflush(fwlo);
  break;

  case LOG_WROKFLAG:
    if(LANG == 1) fprintf(fwlo,"\n### KFLAG " PD " falsch ..Stop ###",i);
    if(LANG == 2) fprintf(fwlo,"\n### KFLAG " PD " wrong ..stop ###",i);
    fflush(fwlo);
  break;

  case LOG_KOOR:
    if(LANG == 1) fprintf(fwlo,"\nEinlesen der Koordinaten");
    if(LANG == 2) fprintf(fwlo,"\nreading coordinates");
    fflush(fwlo);
  break;

  case LOG_KOIN:
    if(LANG == 1) fprintf(fwlo,"\nEinlesen der Koinzidenz");
    if(LANG == 2) fprintf(fwlo,"\nreading element informations");
    fflush(fwlo);
  break;

  case LOG_SINFO:
    if(LANG == 1) fprintf(fwlo,"\nEinlesen der Superelement-Infos");
    if(LANG == 2) fprintf(fwlo,"\nreading superelement informations");
    fflush(fwlo);
  break;

  case LOG_EXITREA88:
    if(LANG == 1) fprintf(fwlo,"\nZ88- Datei eingelesen, Verlassen Leseeinheit REA88X");
    if(LANG == 2) fprintf(fwlo,"\nZ88- file read, leaving reading function REA88X");
    fflush(fwlo);
  break;

  case LOG_WROETYP:
    if(LANG == 1) fprintf(fwlo,"\n### Falschen Elementtyp " PD " entdeckt ..Stop ###",i);
    if(LANG == 2) fprintf(fwlo,"\n### wrong elementtype " PD " detected ..stop ###",i);
    fflush(fwlo);
  break;

  case LOG_FX:
    if(LANG == 1) fprintf(fwlo,"\nOeffnen von Z88X.DXF");
    if(LANG == 2) fprintf(fwlo,"\nopening Z88X.DXF");
    fflush(fwlo);
  break;

  case LOG_NOX:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88X.DXF nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88X.DXF  ..stop ###");
    fflush(fwlo);
  break;

  case LOG_REAIX:
    if(LANG == 1) fprintf(fwlo,"\nZ88X.DXF einlesen");
    if(LANG == 2) fprintf(fwlo,"\nZ88X.DXF read");
    fflush(fwlo);
  break;

  case LOG_FAC:
    if(LANG == 1) fprintf(fwlo,"\nFaktoren berechnen");
    if(LANG == 2) fprintf(fwlo,"\ncomputing factors");
    fflush(fwlo);
  break;

  case LOG_SDXF:
    if(LANG == 1) fprintf(fwlo,"\nDXF-Steuerwerte schreiben");
    if(LANG == 2) fprintf(fwlo,"\nwriting DXF main flags");
    fflush(fwlo);
  break;

  case LOG_SELE:
    if(LANG == 1) fprintf(fwlo,"\nDXF-Entities schreiben");
    if(LANG == 2) fprintf(fwlo,"\nwriting DXF entities");
    fflush(fwlo);
  break;

  case LOG_EXITZ88TX:
    if(LANG == 1) fprintf(fwlo,"\nVerlassen Z88TX");
    if(LANG == 2) fprintf(fwlo,"\nleaving Z88TX");
    fflush(fwlo);
  break;

  case LOG_Z88FX:
    fprintf(fwlo,"\nStart Z88FX");
    fflush(fwlo);
  break;

  case LOG_DEC1ZI1:
    if(LANG == 1) fprintf(fwlo,"\nDecodieren von Z88X.DXF, Z88I1.TXT 1.Zeile aufbauen");
    if(LANG == 2) fprintf(fwlo,"\ndecoding Z88X.DXF, Z88I1.TXT building first line");
    fflush(fwlo);
  break;

  case LOG_DEC1ZNI:
    if(LANG == 1) fprintf(fwlo,"\nDecodieren von Z88X.DXF, Z88NI.TXT 1.Zeile aufbauen");
    if(LANG == 2) fprintf(fwlo,"\ndecoding Z88X.DXF, Z88NI.TXT building first line");
    fflush(fwlo);
  break;

  case LOG_DECKNO:
    if(LANG == 1) fprintf(fwlo,"\nDecodieren von Z88X.DXF, Knoten aufbauen");
    if(LANG == 2) fprintf(fwlo,"\ndecoding Z88X.DXF, building nodes");
    fflush(fwlo);
  break;

  case LOG_FOUKNO:
    if(LANG == 1) fprintf(fwlo,"\n" PD " Knoten gefunden",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD " nodes detected",i);
    fflush(fwlo);
  break;

  case LOG_DECELE:
    if(LANG == 1) fprintf(fwlo,"\nDecodieren von Z88X.DXF, Elemente aufbauen");
    if(LANG == 2) fprintf(fwlo,"\ndecoding Z88X.DXF, building elements");
    fflush(fwlo);
  break;

  case LOG_FOUFELE:
    if(LANG == 1) fprintf(fwlo,"\n" PD " Finite Elemente gefunden",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD " finite elements detected",i);
    fflush(fwlo);
  break;

  case LOG_FOUSELE:
    if(LANG == 1) fprintf(fwlo,"\n" PD " Super-Elemente gefunden",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD " superelements detected",i);
    fflush(fwlo);
  break;

  case LOG_DEC1ZI2:
    if(LANG == 1) fprintf(fwlo,
    "\nDecodieren von Z88X.DXF, Z88I2.TXT Anzahl Randbed. aufbauen");
    if(LANG == 2) fprintf(fwlo,
    "\ndecoding Z88X.DXF, building number of constraints");
    fflush(fwlo);
  break;

  case LOG_DECI2R:
    if(LANG == 1) fprintf(fwlo,
    "\nDecodieren von Z88X.DXF, Z88I2.TXT Randbedingungen aufbauen");
    if(LANG == 2) fprintf(fwlo,
    "\ndecoding Z88X.DXF, building constraints");
    fflush(fwlo);
  break;

  case LOG_DEC1ZI5:
    if(LANG == 1) fprintf(fwlo,
    "\nDecodieren von Z88X.DXF, Z88I5.TXT Anzahl Flaechenlasten aufbauen");
    if(LANG == 2) fprintf(fwlo,
    "\ndecoding Z88X.DXF, building number of surface loads");
    fflush(fwlo);
  break;

  case LOG_DECI5R:
    if(LANG == 1) fprintf(fwlo,
    "\nDecodieren von Z88X.DXF, Z88I5.TXT Flaechenlasten aufbauen");
    if(LANG == 2) fprintf(fwlo,
    "\ndecoding Z88X.DXF, building surface loads");
    fflush(fwlo);
  break;

  case LOG_WROIXI1:
    if(LANG == 1)
    {
    fprintf(fwlo,"\n### Z88X.DXF fuer Z88I1.TXT falsch:              ###");
    fprintf(fwlo,"\n### erste Eingabegruppe fehlt oder falsch ..Stop ###");
    }
    if(LANG == 2)
    {
    fprintf(fwlo,"\n### Z88X.DXF wrong for Z88I1.TXT:             ###");
    fprintf(fwlo,"\n### first input group missing or wrong ..stop ###");
    }
    fflush(fwlo);
  break;

  case LOG_WROIXNI:
    if(LANG == 1)
    {
    fprintf(fwlo,"\n### Z88X.DXF fuer Z88NI.TXT falsch:              ###");
    fprintf(fwlo,"\n### erste Eingabegruppe fehlt oder falsch ..Stop ###");
    }
    if(LANG == 2)
    {
    fprintf(fwlo,"\n### Z88X.DXF wrong for Z88NI.TXT:             ###");
    fprintf(fwlo,"\n### first input group missing or wrong ..stop ###");
    }
    fflush(fwlo);
  break;

  case LOG_WROIXKNO:
    if(LANG == 1)
    {
    fprintf(fwlo,"\n### Z88X.DXF fuer Z88I1.TXT/Z88NI.TXT falsch:   ###");
    fprintf(fwlo,"\n### Gefundene Anzahl Knoten stimmt nicht ..Stop ###");
    }
    if(LANG == 2)
    {
    fprintf(fwlo,"\n### Z88X.DXF wrong for Z88I1.TXT/Z88NI.TXT: ###");
    fprintf(fwlo,"\n### impossible number of nodes found ..stop ###");
    }
    fflush(fwlo);
  break;

  case LOG_WROIXELE:
    if(LANG == 1)
    {
    fprintf(fwlo,"\n### Z88X.DXF fuer Z88I1.TXT/Z88NI.TXT falsch:     ###");
    fprintf(fwlo,"\n### Gefundene Anzahl Elemente stimmt nicht ..Stop ###");
    }
    if(LANG == 2)
    {
    fprintf(fwlo,"\n### Z88X.DXF wrong for Z88I1.TXT/Z88NI.TXT:    ###");
    fprintf(fwlo,"\n### impossible number of elements found ..stop ###");
    }
    fflush(fwlo);
  break;

  case LOG_WROIXKOI:
    if(LANG == 1)
    {
    fprintf(fwlo,"\n### Z88X.DXF fuer Z88I1.TXT/Z88NI.TXT falsch:###");
    fprintf(fwlo,"\n### identische Knoten in Element " PD " ..Stop ###",i);
    }
    if(LANG == 2)
    {
    fprintf(fwlo,"\n### Z88X.DXF wrong for Z88I1.TXT/Z88NI.TXT:      ###");
    fprintf(fwlo,"\n### identical nodes in element " PD " found ..stop ###",i);
    }
    fflush(fwlo);
  break;

  case LOG_WROIXM:
    if(LANG == 1)
    {
    fprintf(fwlo,"\n### Z88X.DXF fuer Z88I1.TXT/Z88NI.TXT falsch:###");
    fprintf(fwlo,"\n### E-Gesetze fehlen oder falsch ..Stop      ###");
    }
    if(LANG == 2)
    {
    fprintf(fwlo,"\n### Z88X.DXF wrong for Z88I1.TXT/Z88NI.TXT:       ###");
    fprintf(fwlo,"\n### material informations missing or wrong ..stop ###");
    }
    fflush(fwlo);
  break;

  case LOG_WROIXI21Z:
    if(LANG == 1)
    {
    fprintf(fwlo,"\n### Z88X.DXF fuer Z88I2.TXT.TXT falsch:             ###");
    fprintf(fwlo,"\n### Anzahl Randbedingungen fehlt oder falsch ..Stop ###");
    }
    if(LANG == 2)
    {
    fprintf(fwlo,"\n### Z88X.DXF wrong for Z88I2.TXT:                 ###");
    fprintf(fwlo,"\n### number of constraints missing or wrong ..stop ###");
    }
    fflush(fwlo);
  break;

  case LOG_WROIXI2R:
    if(LANG == 1)
    {
    fprintf(fwlo,"\n### Z88X.DXF fuer Z88I2.TXT.TXT falsch:          ###");
    fprintf(fwlo,"\n### Falsche oder zuwenig Randbedingungen  ..Stop ###");
    }
    if(LANG == 2)
    {
    fprintf(fwlo,"\n### Z88X.DXF wrong for Z88I2.TXT:        ###");
    fprintf(fwlo,"\n### wrong or too few constraints  ..stop ###");
    }
    fflush(fwlo);
  break;

  case LOG_WROIXI51Z:
    if(LANG == 1)
    {
    fprintf(fwlo,"\n### Z88X.DXF fuer Z88I5.TXT.TXT falsch:            ###");
    fprintf(fwlo,"\n### Anzahl Flaechenlasten fehlt oder falsch ..Stop ###");
    }
    if(LANG == 2)
    {
    fprintf(fwlo,"\n### Z88X.DXF wrong for Z88I5.TXT:                   ###");
    fprintf(fwlo,"\n### number of surface loads missing or wrong ..stop ###");
    }
    fflush(fwlo);
  break;

  case LOG_WROIXI5R:
    if(LANG == 1)
    {
    fprintf(fwlo,"\n### Z88X.DXF fuer Z88I5.TXT.TXT falsch:         ###");
    fprintf(fwlo,"\n### Falsche oder zuwenig Flaechenlasten  ..Stop ###");
    }
    if(LANG == 2)
    {
    fprintf(fwlo,"\n### Z88X.DXF wrong for Z88I2.TXT:          ###");
    fprintf(fwlo,"\n### wrong or too few surface loads  ..stop ###");
    }
    fflush(fwlo);
  break;

  case LOG_EXITZ88FX:
    if(LANG == 1) fprintf(fwlo,"\nVerlassen Z88FX");
    if(LANG == 2) fprintf(fwlo,"\nleaving Z88FX");
    fflush(fwlo);
  break;

  case LOG_EXITZ88X:
    if(LANG == 1) fprintf(fwlo,"\nEnde Z88X");
    if(LANG == 2) fprintf(fwlo,"\nZ88X done");
    fflush(fwlo);
  break;

  case LOG_WRII1:
    if(LANG == 1) fprintf(fwlo,"\nBeschreiben von Z88I1.TXT");
    if(LANG == 2) fprintf(fwlo,"\nwriting Z88I1.TXT");
    fflush(fwlo);
  break;

  case LOG_WRINI:
    if(LANG == 1) fprintf(fwlo,"\nBeschreiben von Z88NI.TXT");
    if(LANG == 2) fprintf(fwlo,"\nwriting Z88NI.TXT");
    fflush(fwlo);
  break;

  case LOG_WRII2:
    if(LANG == 1) fprintf(fwlo,"\nBeschreiben von Z88I2.TXT");
    if(LANG == 2) fprintf(fwlo,"\nwriting Z88I2.TXT");
    fflush(fwlo);
  break;

  case LOG_WRII5:
    if(LANG == 1) fprintf(fwlo,"\nBeschreiben von Z88I5.TXT");
    if(LANG == 2) fprintf(fwlo,"\nwriting Z88I5.TXT");
    fflush(fwlo);
  break;

  case LOG_TOOFEW:
    if(LANG == 1)
    {
    fprintf(fwlo,"\n### Z88X.DXF von CAD falsch:                       ###");
    fprintf(fwlo,"\n### Falsche oder zuwenig Linien auf Z88NET  ..Stop ###");
    }
    if(LANG == 2)
    {
    fprintf(fwlo,"\n### Z88X.DXF from CAD wrong:                 ###");
    fprintf(fwlo,"\n### wrong or too few lines on Z88NET  ..stop ###");
    }
    fflush(fwlo);
  break;

  case LOG_NOPOINTS:
    if(LANG == 1)
    {
    fprintf(fwlo,"\n### Z88X.DXF von CAD falsch:                         ###");
    fprintf(fwlo,"\n### Knoten nicht richtig definiert (P Nummer) ..Stop ###");
    }
    if(LANG == 2)
    {
    fprintf(fwlo,"\n### Z88X.DXF from CAD wrong:                      ###");
    fprintf(fwlo,"\n### nodes not properly defined (P number)  ..stop ###");
    }
    fflush(fwlo);
  break;

  case LOG_NOLAYNET:
    if(LANG == 1)
    {
    fprintf(fwlo,"\n### Z88X.DXF von CAD falsch:                        ###");
    fprintf(fwlo,"\n### Keine o. zuwenig Objekte auf Layer Z88NET..Stop ###");
    }
    if(LANG == 2)
    {
    fprintf(fwlo,"\n### Z88X.DXF from CAD wrong:                      ###");
    fprintf(fwlo,"\n### no or too few objects on layer Z88NET  ..stop ###");
    }
    fflush(fwlo);
  break;

  case LOG_NOACROBAT:
    if(LANG == 1) fprintf(fwlo,"\nPDF-Viewer konnte nicht gestartet werden");
    if(LANG == 2) fprintf(fwlo,"\ncould not launch PDF Viewer");
    fflush(fwlo);
  break;

  }
return(0);
}
