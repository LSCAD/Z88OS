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
*  function ale88c gibt Fehlermeldungen aus
*  26.7.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88com.h>
#include <windows.h>    /* printf */
#endif

/***********************************************************************
*  hier beginnt Function ale88c
***********************************************************************/
int ale88c(int ialert)
{
extern FR_INT4 LANG;

char cmess[256];

switch(ialert)
  {
  case AL_NOLOG:
    if(LANG == 1) strcpy(cmess,"Kann Z88COM.LOG nicht oeffnen !   STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88COM.LOG !    STOP");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONHAND);
  break;

  case AL_NODYN:
    if(LANG == 1) strcpy(cmess,"Kann Z88.DYN nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88.DYN !    STOP");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONHAND);
  break;

  case AL_WRONGDYN:
    if(LANG == 1) strcpy(cmess,"Z88.DYN ist nicht korrekt !    STOP");
    if(LANG == 2) strcpy(cmess,"Z88.DYN is invalid or wrong !    STOP");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONHAND);
  break;

  case AL_NOCFG:
    if(LANG == 1) strcpy(cmess,"Kann Z88COM.CFG nicht oeffnen !   STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88COM.CFG !    STOP");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONHAND);
  break;

  case AL_WRONGCFG:
    if(LANG == 1) strcpy(cmess,"Z88COM.CFG ist nicht korrekt !    STOP");
    if(LANG == 2) strcpy(cmess,"Z88COM.CFG is invalid or wrong !    STOP");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONHAND);
  break;

  case AL_NOWRICFG:
    if(LANG == 1) strcpy(cmess,
      "Fehler beim Schreiben von Z88COM.CFG !    STOP");
    if(LANG == 2) strcpy(cmess,"Error when writing Z88COM.CFG !    STOP");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONHAND);
  break;

  case AL_NOZ88G:
    if(LANG == 1) strcpy(cmess,
      "Z88G konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch Z88G !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOZ88H:
    if(LANG == 1) strcpy(cmess,
      "Z88H konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch Z88H !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOZ88X:
    if(LANG == 1) strcpy(cmess,
      "Z88X konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch Z88X !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOZ88N:
    if(LANG == 1) strcpy(cmess,
      "Z88N konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch Z88N !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOZ88R:
    if(LANG == 1) strcpy(cmess,
      "Z88R konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch Z88R !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDDYN:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88.DYN konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88.DYN !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDOGL:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88O.OGL konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88O.OGL !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDNI:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88NI.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88NI.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDI1:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88I1.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88I1.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDI2:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88I2.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88I2.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDMAN:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88MAN.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88MAN.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDMAT:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88MAT.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88MAT.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDELP:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88ELP.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88ELP.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDINT:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88INT.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88INT.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDI5:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88I5.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88I5.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDO0:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88O0.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88O0.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDO1:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88O1.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88O1.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDO2:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88O2.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88O2.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDO3:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88O3.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88O3.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOEDO4:
    if(LANG == 1) strcpy(cmess,
      "Ihr Editor mit Z88O4.TXT konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,
      "Could not launch your editor loading Z88O4.TXT !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOZ88O:
    if(LANG == 1) strcpy(cmess,
      "Z88O konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch Z88O !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  case AL_NOACROBAT:
    if(LANG == 1) strcpy(cmess,
    "PDF-Viewer konnte nicht gestartet werden !    WEITER");
    if(LANG == 2) strcpy(cmess,"Could not launch PDF-Viewer !    CONTINUE");
    MessageBox(NULL,cmess, "Z88COM",MB_OK | MB_ICONEXCLAMATION);
  break;

  }
return(0);
}

