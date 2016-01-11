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
* wlog88h gibt Log-Datei-Meldungen aus (1 FR_INT4, 1 int)
* 3.8.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88h.h>
#include <stdio.h>   /* FILE,fprintf,fflush */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88h.h>
#include <stdio.h>   /* FILE,fprintf,fflush */
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
*  hier beginnt Function wlog88h
***********************************************************************/
int wlog88h(FR_INT4 i,int iatx)
{
extern FILE *fwlo;
extern FR_INT4 LANG;

switch(iatx)
  {
  case LOG_BZ88:
    if(LANG == 1) fprintf(fwlo,"Start Z88H Version 14OS");
    if(LANG == 2) fprintf(fwlo,"start Z88H version 14OS");
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

  case LOG_NOIN:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88H.IN nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88H.IN ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOI1:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88I1.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88I1.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOI2:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88I2.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88I2.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOI5:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88I5.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88I5.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOOUT:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88H.OUT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88H.OUT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_WRONGDYN:
    if(LANG == 1) fprintf(fwlo,"\n### File Z88.DYN ist nicht korrekt ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### file Z88.DYN is not correct ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOMEM:
    if(LANG == 1)fprintf(fwlo,"\n### kann Memory nicht anlegen ..Stop ###");
    if(LANG == 2)fprintf(fwlo,"\n### cannot allocate memory ..stop ###");
    fflush(fwlo);
  break;

  case LOG_1STOP:
    if(LANG == 1) fprintf(fwlo,"\n### MAXGRA ueberschritten mit " PD " ..Stop ###",i);
    if(LANG == 2) fprintf(fwlo,"\n### MAXGRA exceeded with " PD " ..stop ###",i);
    fflush(fwlo);
  break;

  case LOG_OKDYN:
    if(LANG == 1) fprintf(fwlo,"\n File Z88.DYN gelesen, o.k.");
    if(LANG == 2) fprintf(fwlo,"\nfile Z88.DYN read, o.k.");
    fflush(fwlo);
  break;

  case LOG_Z88DONE:
    if(LANG == 1) fprintf(fwlo,"\nFiles geschlossen. Z88H fertig.");
    if(LANG == 2) fprintf(fwlo,"\nFiles closed. Z88H done.");
    fflush(fwlo);
  break;

  }
return(0);
}

