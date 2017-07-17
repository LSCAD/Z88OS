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
* Composed and edited by 
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
* wlog88c gibt Log-Datei-Meldungen aus (1 FR_INT4, 1 int)
* 25.11.2015 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88com.h>
#include <stdio.h>   /* FILE,fprintf,fflush */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88com.h>
#include <stdio.h>   /* FILE,fprintf,fflush */
#endif

/***********************************************************************
*  hier beginnt Function wlog88c
***********************************************************************/
int wlog88c(FR_INT4 i,int iatx)
{
extern FILE *fwlo;
extern FR_INT4 LANG;

switch(iatx)
  {
  case LOG_BZ88COM:
    if(LANG == 1) fprintf(fwlo,"Start Z88COM Version 15OS");
    if(LANG == 2) fprintf(fwlo,"start Z88COM version 15OS");
    fflush(fwlo);
  break;

  case LOG_OPENDYN:
    if(LANG == 1) fprintf(fwlo,"\nOeffnen der Datei Z88.DYN");
    if(LANG == 2) fprintf(fwlo,"\nopening file Z88.DYN");
    fflush(fwlo);
  break;

  case LOG_LADETECT:
    if(LANG == 1) fprintf(fwlo,"\nSprache Deutsch in Z88.DYN endeckt");
    if(LANG == 2) fprintf(fwlo,"\nlanguage English in Z88.DYN detected");
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

  case LOG_NOCFG:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88COM.CFG nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88COM.CFG ..stop ###");
    fflush(fwlo);
  break;

  case LOG_WRONGCFG:
    if(LANG == 1) fprintf(fwlo,"\n### File Z88COM.CFG ist nicht korrekt ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### file Z88COM.CFG is not correct ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOWRICFG:
    if(LANG == 1) fprintf(fwlo,"\n### Fehler beim Schreiben von Z88COM.CFG ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### error when writing Z88COM.CFG ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOZ88G:
    if(LANG == 1) fprintf(fwlo,"\n??? Z88G konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch Z88G ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOZ88H:
    if(LANG == 1) fprintf(fwlo,"\n??? Z88H konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch Z88H ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOZ88X:
    if(LANG == 1) fprintf(fwlo,"\n??? Z88X konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch Z88X ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOZ88N:
    if(LANG == 1) fprintf(fwlo,"\n??? Z88N konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch Z88N ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOZ88R:
    if(LANG == 1) fprintf(fwlo,"\n??? Z88R konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch Z88R ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOZ88O:
    if(LANG == 1) fprintf(fwlo,"\n??? Z88O konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch Z88O ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOEDDYN:
    if(LANG == 1) fprintf(fwlo,"\n??? Editor mit Z88.DYN konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch your editor loading Z88.DYN ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOEDFCD:
    if(LANG == 1) fprintf(fwlo,"\n??? Editor mit Z88.FCD konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch your editor loading Z88.FCD ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOEDOGL:
    if(LANG == 1) fprintf(fwlo,"\n??? Editor mit Z88O.OGL konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch your editor loading Z88O.OGL ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOEDNI:
    if(LANG == 1) fprintf(fwlo,"\n??? Editor mit Z88NI.TXT konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch your editor loading Z88NI.TXT ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOEDI1:
    if(LANG == 1) fprintf(fwlo,"\n??? Editor mit Z88I1.TXT konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch your editor loading Z88I1.TXT ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOEDI2:
    if(LANG == 1) fprintf(fwlo,"\n??? Editor mit Z88I2.TXT konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch your editor loading Z88I2.TXT ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOEDMAN:
    if(LANG == 1) fprintf(fwlo,"\n??? Editor mit Z88MAN.TXT konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch your editor loading Z88MAN.TXT ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOEDMAT:
    if(LANG == 1) fprintf(fwlo,"\n??? Editor mit Z88MAT.TXT konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch your editor loading Z88MAT.TXT ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOEDELP:
    if(LANG == 1) fprintf(fwlo,"\n??? Editor mit Z88ELP.TXT konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch your editor loading Z88ELP.TXT ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOEDINT:
    if(LANG == 1) fprintf(fwlo,"\n??? Editor mit Z88INT.TXT konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch your editor loading Z88INT.TXT ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOEDI5:
    if(LANG == 1) fprintf(fwlo,"\n??? Editor mit Z88I5.TXT konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch your editor loading Z88I5.TXT ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOEDO0:
    if(LANG == 1) fprintf(fwlo,"\n??? Editor mit Z88O0.TXT konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch your editor loading Z88O0.TXT ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOEDO1:
    if(LANG == 1) fprintf(fwlo,"\n??? Editor mit Z88O1.TXT konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch your editor loading Z88O1.TXT ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOEDO2:
    if(LANG == 1) fprintf(fwlo,"\n??? Editor mit Z88O2.TXT konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch your editor loading Z88O2.TXT ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOEDO3:
    if(LANG == 1) fprintf(fwlo,"\n??? Editor mit Z88O3.TXT konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch your editor loading Z88O3.TXT ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOEDO4:
    if(LANG == 1) fprintf(fwlo,"\n??? Editor mit Z88O4.TXT konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch your editor loading Z88O4.TXT ..continue ???");
    fflush(fwlo);
  break;

  case LOG_NOACROBAT:
    if(LANG == 1) fprintf(fwlo,"\n??? PDF-Viewer konnte nicht gestartet werden ..weiter ???");
    if(LANG == 2) fprintf(fwlo,"\n??? could not launch PDF-Viewer ..continue ???");
    fflush(fwlo);
  break;

  }
return(0);
}

