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
* wlog88n gibt Log-Datei-Meldungen aus (1 FR_INT4, 1 int)
* 25.11.2015 Rieg 
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88n.h>
#include <stdio.h>    /* printf */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88n.h>
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
* hier beginnt Function wlog88n
***********************************************************************/
int wlog88n(FR_INT4 i,int iatx)
{
extern FILE *fwlo;
extern FR_INT4 LANG;

switch(iatx)
  {
  case LOG_BZ88N:
    if(LANG == 1) fprintf(fwlo,"Start Z88N Version 15OS");
    if(LANG == 2) fprintf(fwlo,"start Z88N version 15OS");
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

  case LOG_EXITDYN88N:
    if(LANG == 1) fprintf(fwlo,"\nVerlassen Speichereinheit DYN288N");
    if(LANG == 2) fprintf(fwlo,"\nleaving storage function DYN288N");
    fflush(fwlo);
  break;

  case LOG_REANI:
    if(LANG == 1) fprintf(fwlo,"\nStart Leseeinheit RNI88");
    if(LANG == 2) fprintf(fwlo,"\nstart reading function RNI88");
    fflush(fwlo);
  break;

  case LOG_OPENNI:
    if(LANG == 1) fprintf(fwlo,"\nOeffnen der Datei Z88NI.TXT");
    if(LANG == 2) fprintf(fwlo,"\nopening file Z88NI.TXT");
    fflush(fwlo);
  break;

  case LOG_NONI:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88NI.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88NI.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_OPENI1:
    if(LANG == 1) fprintf(fwlo,"\nOeffnen der Datei Z88I1.TXT");
    if(LANG == 2) fprintf(fwlo,"\nopening file Z88I1.TXT");
    fflush(fwlo);
  break;

  case LOG_NOI1:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88I1.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88I1.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_EXITRNI88:
    if(LANG == 1) fprintf(fwlo,"\nVerlassen Leseeinheit RNI88: File Z88NI.TXT gelesen");
    if(LANG == 2) fprintf(fwlo,"\nleaving reading function RNI88: file Z88NI.TXT read");
    fflush(fwlo);
  break;

  case LOG_BERJOIN:
    if(LANG == 1) fprintf(fwlo,"\nBerechne Vektor JOIN");
    if(LANG == 2) fprintf(fwlo,"\ncomputing vector JOIN");
     fflush(fwlo);
  break;

  case LOG_EXITJOIN:
    if(LANG == 1) fprintf(fwlo,"\nEnde Berechnung JOIN");
    if(LANG == 2) fprintf(fwlo,"\nJOIN computed");
    fflush(fwlo);
  break;

  case LOG_SMC188N:
    if(LANG == 1)
      {
      fprintf(fwlo,"\nStarten MC188N: Typ 10 --> Typ 10");
      fprintf(fwlo,"\nKoordinaten berechnen");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\nstart MC188N: type 10 --> type 10");
      fprintf(fwlo,"\ncomputing coordinates");
      }
    fflush(fwlo);
  break;

  case LOG_SMC288N:
    if(LANG == 1)
      {
      fprintf(fwlo,"\nStarten MC288N: Typ 10 --> Typ 1");
      fprintf(fwlo,"\nKoordinaten berechnen");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\nstart MC288N: type 10 --> type 1");
      fprintf(fwlo,"\ncomputing coordinates");
      }
    fflush(fwlo);
  break;

  case LOG_SMC388N:
    if(LANG == 1)
      {
      fprintf(fwlo,"\nStarten MC388N: Typ 7/8 --> Typ 7/8");
      fprintf(fwlo,"\nKoordinaten berechnen");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\nstart MC388N: type 7/8 --> type 7/8");
      fprintf(fwlo,"\ncomputing coordinates");
      }
    fflush(fwlo);
  break;

  case LOG_SMC488N:
    if(LANG == 1)
      {
      fprintf(fwlo,"\nStarten MC488N: Typ 11/12 --> Typ 7/8");
      fprintf(fwlo,"\nKoordinaten berechnen");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\nstart MC488N: type 11/12 --> type 7/8");
      fprintf(fwlo,"\ncomputing coordinates");
      }
    fflush(fwlo);
  break;

  case LOG_SMC588N:
    if(LANG == 1)
      {
      fprintf(fwlo,"\nStarten MC588N: Typ 20 --> Typ 19");
      fprintf(fwlo,"\nKoordinaten berechnen");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\nstart MC588N: type 20 --> type 19");
      fprintf(fwlo,"\ncomputing coordinates");
      }
    fflush(fwlo);
  break;

  case LOG_SMC688N:
    if(LANG == 1)
      {
      fprintf(fwlo,"\nStarten MC688N: Typ 21 --> Typ 21");
      fprintf(fwlo,"\nKoordinaten berechnen");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\nstart MC688N: type 21 --> type 21");
      fprintf(fwlo,"\ncomputing coordinates");
      }
    fflush(fwlo);
  break;

  case LOG_SMC788N:
    if(LANG == 1)
      {
      fprintf(fwlo,"\nStarten MC788N: Typ 1 --> Typ 1");
      fprintf(fwlo,"\nKoordinaten berechnen");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\nstart MC788N: type 1 --> type 1");
      fprintf(fwlo,"\ncomputing coordinates");
      }
    fflush(fwlo);
  break;

  case LOG_SMC888N:
    if(LANG == 1)
      {
      fprintf(fwlo,"\nStarten MC888N: Typ 20 --> Typ 20");
      fprintf(fwlo,"\nKoordinaten berechnen");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\nstart MC888N: type 20 --> type 20");
      fprintf(fwlo,"\ncomputing coordinates");
      }
    fflush(fwlo);
  break;

  case LOG_BERKOIN:
    if(LANG == 1) fprintf(fwlo,"\nKoinzidenzvektor berechnen");
    if(LANG == 2) fprintf(fwlo,"\ncomputing element informations");
    fflush(fwlo);
  break;

  case LOG_WRII1:
    if(LANG == 1) fprintf(fwlo,"\nZ88I1.TXT beschreiben, Ende Z88N");
    if(LANG == 2) fprintf(fwlo,"\nwriting Z88I1.TXT, Z88N done");
    fflush(fwlo);
  break;

  case LOG_MAXSE:
    fprintf(fwlo,"\nMAXSE  = " PD,i);
    fflush(fwlo);
  break;

  case LOG_MAXESS:
    fprintf(fwlo,"\nMAXESS = " PD,i);
    fflush(fwlo);
  break;

  case LOG_MAXKSS:
    fprintf(fwlo,"\nMAXKSS = " PD,i);
    fflush(fwlo);
  break;
  }
return(0);
}
