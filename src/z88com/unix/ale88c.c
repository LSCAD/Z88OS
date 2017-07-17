/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows & UNIX OS.
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
* ale88c gibt Alert-Boxen aus (1 int)
* Fuer UNIX
* 1.8.2011 Rieg
***********************************************************************/ 
/***********************************************************************
* UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88com.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

/***********************************************************************
* hier beginnt Function ale88c
***********************************************************************/
int ale88c(int ialert)
{
extern GtkWidget *HWND; 
extern FR_INT4    LANG;

GtkWidget        *MB_ALERT;
char              cmess[256];

switch(ialert)
  {
  case AL_NOHELP:
    if(LANG == 1) strcpy(cmess,"Kann Browser nicht starten!\nEinstellungen in Z88.FCD pruefen.");
    if(LANG == 2) strcpy(cmess,"Cannot launch Browser!\nCheck your entries in Z88.FCD.");
  break;

  case AL_NOLOG:
    if(LANG == 1) strcpy(cmess,"Kann Z88COM.LOG nicht oeffnen!");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88COM.LOG!");
  break;

  case AL_NOEDDYN:
    if(LANG == 1) strcpy(cmess,"Kann Z88.DYN oder Editor nicht oeffnen!\nZ88.FCD pruefen.");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88.DYN or Editor!\nCheck Z88.FCD");
  break;

  case AL_NOEDFCD:
    if(LANG == 1) strcpy(cmess,"Kann Z88.FCD oder Editor nicht oeffnen!\nZ88.FCD pruefen.");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88.FCD or Editor!\nCheck Z88.FCD");
  break;

  case AL_WRONGDYN:
    if(LANG == 1) strcpy(cmess,"Z88.DYN ist falsch!");
    if(LANG == 2) strcpy(cmess,"Z88.DYN is  wrong!");
  break;

  case AL_NOEDNI:
    if(LANG == 1) strcpy(cmess,"Kann Z88NI.TXT oder Editor nicht oeffnen!\nZ88.FCD pruefen.");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88NI.TXT or Editor!\nCheck Z88.FCD");
  break;

  case AL_NOEDI1:
    if(LANG == 1) strcpy(cmess,"Kann Z88I1.TXT oder Editor nicht oeffnen!\nZ88.FCD pruefen.");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88I1.TXT or Editor!\nCheck Z88.FCD");
  break;

  case AL_NOEDI2:
    if(LANG == 1) strcpy(cmess,"Kann Z88I2.TXT oder Editor nicht oeffnen!\nZ88.FCD pruefen.");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88I2.TXT or Editor!\nCheck Z88.FCD");
  break;

  case AL_NOEDMAN:
    if(LANG == 1) strcpy(cmess,"Kann Z88MAN.TXT oder Editor nicht oeffnen!\nZ88.FCD pruefen.");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88MAN.TXT or Editor!\nCheck Z88.FCD");
  break;

  case AL_NOEDMAT:
    if(LANG == 1) strcpy(cmess,"Kann Z88MAT.TXT oder Editor nicht oeffnen!\nZ88.FCD pruefen.");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88MAT.TXT or Editor!\nCheck Z88.FCD");
  break;

  case AL_NOEDELP:
    if(LANG == 1) strcpy(cmess,"Kann Z88ELP.TXT oder Editor nicht oeffnen!\nZ88.FCD pruefen.");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88ELP.TXT or Editor!\nCheck Z88.FCD");
  break;

  case AL_NOEDINT:
    if(LANG == 1) strcpy(cmess,"Kann Z88INT.TXT oder Editor nicht oeffnen!\nZ88.FCD pruefen.");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88INT.TXT or Editor!\nCheck Z88.FCD");
  break;

  case AL_NOEDI5:
    if(LANG == 1) strcpy(cmess,"Kann Z88I5.TXT oder Editor nicht oeffnen!\nZ88.FCD pruefen.");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88I5.TXT or Editor!\nCheck Z88.FCD");
  break;

  case AL_NOEDO0:
    if(LANG == 1) strcpy(cmess,"Kann Z88O0.TXT oder Editor nicht oeffnen!\nZ88.FCD pruefen.");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O0.TXT or Editor!\nCheck Z88.FCD");
  break;

  case AL_NOEDO1:
    if(LANG == 1) strcpy(cmess,"Kann Z88O1.TXT oder Editor nicht oeffnen!\nZ88.FCD pruefen.");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O1.TXT or Editor!\nCheck Z88.FCD");
  break;

  case AL_NOEDO2:
    if(LANG == 1) strcpy(cmess,"Kann Z88O2.TXT oder Editor nicht oeffnen!\nZ88.FCD pruefen.");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O2.TXT or Editor!\nCheck Z88.FCD");
  break;

  case AL_NOEDO3:
    if(LANG == 1) strcpy(cmess,"Kann Z88O3.TXT oder Editor nicht oeffnen!\nZ88.FCD pruefen.");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O3.TXT or Editor!\nCheck Z88.FCD");
  break;

  case AL_NOEDO4:
    if(LANG == 1) strcpy(cmess,"Kann Z88O4.TXT oder Editor nicht oeffnen!\nZ88.FCD pruefen.");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O4.TXT or Editor!\nCheck Z88.FCD");
  break;

  case AL_NOZ88R:
    if(LANG == 1) strcpy(cmess,"Kann Z88R nicht starten!");
    if(LANG == 2) strcpy(cmess,"Cannot lauch Z88R!");
  break;

  case AL_NOZ88X:
    if(LANG == 1) strcpy(cmess,"Kann Z88X nicht starten!");
    if(LANG == 2) strcpy(cmess,"Cannot launch Z88X!");
  break;

  case AL_NOZ88G:
    if(LANG == 1) strcpy(cmess,"Kann Z88G nicht starten!");
    if(LANG == 2) strcpy(cmess,"Cannot launch Z88G!");
  break;

  case AL_NOZ88H:
    if(LANG == 1) strcpy(cmess,"Kann Z88H nicht starten!");
    if(LANG == 2) strcpy(cmess,"Cannot launch Z88H!");
  break;

  case AL_NOZ88O:
    if(LANG == 1) strcpy(cmess,"Kann Z88O nicht starten!");
    if(LANG == 2) strcpy(cmess,"Cannot launch Z88O!");
  break;

  case AL_NOACROBAT:
    if(LANG == 1) strcpy(cmess,"Kann PDF-Viewer nicht starten!");
    if(LANG == 2) strcpy(cmess,"Cannot launch PDF Viewer!");
  break;
  }

/*----------------------------------------------------------------------
* nun die Questionbox
*---------------------------------------------------------------------*/
MB_ALERT= gtk_message_dialog_new(GTK_WINDOW(HWND),
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,cmess);
gtk_dialog_run(GTK_DIALOG(MB_ALERT));
gtk_widget_destroy(MB_ALERT);

return 0;
}  

