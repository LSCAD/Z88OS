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
* ale88o gibt Alert-Boxen aus (1 int)
* Fuer UNIX
* 18.11.2015 Rieg
***********************************************************************/ 
/***********************************************************************
* UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88o.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

/***********************************************************************
* hier beginnt Function ale88o
***********************************************************************/
int ale88o(int ialert)
{
extern GtkWidget *H_WIN; 
extern FR_INT4    LANG;
extern int        ifverf,if3d;

GtkWidget        *MB_ALERT;
int               idiag=2;
gint              iret;
char              cmess[256];

if(LANG == 1) strcpy(cmess,"Unbekannten Fehler endeckt!");
if(LANG == 2) strcpy(cmess,"Unknown Error detected!");

switch(ialert)
  {
  case AL_NOMAN:
    if(LANG == 1) strcpy(cmess,"Kann Z88MAN.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88MAN.TXT !    STOP");
  break;

  case AL_WRONGMAN:
    if(LANG == 1) strcpy(cmess,"Z88MAN.TXT ist nicht korrekt !    STOP");
    if(LANG == 2) strcpy(cmess,"Z88MAN.TXT is invalid or wrong !    STOP");
  break;

  case AL_NOHELP:
    if(LANG == 1) strcpy(cmess,"Kann Browser nicht starten!\nEinstellungen in Z88.FCD pruefen.");
    if(LANG == 2) strcpy(cmess,"Cannot launch Browser!\nCheck your entries in Z88.FCD.");
    idiag= 2;
  break;

  case AL_NOLOG:
    if(LANG == 1) strcpy(cmess,"Kann Z88O.LOG nicht oeffnen!");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O.LOG!");
    idiag= 1;
  break;

  case AL_NODYN:
    if(LANG == 1) strcpy(cmess,"Kann Z88.DYN nicht oeffnen!");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88.DYN!");
    idiag= 1;
  break;

  case AL_WRONGDYN:
    if(LANG == 1) strcpy(cmess,"Z88.DYN ist falsch!");
    if(LANG == 2) strcpy(cmess,"Z88.DYN is  wrong!");
    idiag= 1;
  break;

  case AL_NOMEMY:
    if(LANG == 1) strcpy(cmess,"Nicht genug dynamischer Speicher!\n\
Abhilfe: Eintraege in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Dynamic memory exhausted!\n\
Recover: increase entries in Z88.DYN.");
    idiag= 1;
  break;

  case AL_NOSTRFI:
    if(LANG == 1) strcpy(cmess,"Strukturfile nicht gefunden!\n\
Anderes Strukturfile angeben.");
    if(LANG == 2) strcpy(cmess,"Structure file not found!\n\
Enter a valid filename.");
    idiag= 2;
  break;   

  case AL_NOI2:
    if(LANG == 1) strcpy(cmess,"Z88I2.TXT nicht gefunden!\n\
Daher keine Anzeige der Randbedingungen.");
    if(LANG == 2) strcpy(cmess,"Z88I2.TXT not found!\n\
Thus no view of boundary conditions.");
    idiag= 1;
  break;

  case AL_NOI5:
    if(LANG == 1) strcpy(cmess,"Z88I5.TXT nicht gefunden!\n\
Daher keine Anzeige der Flaechenlasten.");
    if(LANG == 2) strcpy(cmess,"Z88I5.TXT not found!\n\
Thus no view of surface loads.");
    idiag= 2;
  break;

  case AL_NOO2:
    if(LANG == 1) strcpy(cmess,"Z88O2.TXT nicht gefunden!\n\
Daher keine Anzeige der verformten Struktur.\n\
Zuerst Verformungsrechnung mit Z88F oder Z88I1/Z88I2 oder Z88I1/Z88PAR.");
    if(LANG == 2) strcpy(cmess,"Z88O2.TXT not found!\n\
Thus no view of deflected structure.\n\
Start a solver run with Z88F or Z88I1/Z88I2 or Z88I1/Z88PAR first.");
    idiag= 2;
    ifverf= IDM_UNVERFORMT;
    if3d  = IDM_LIGHT;
  break;
    
  case AL_NOO5:
    if(LANG == 1) strcpy(cmess,"Z88O5.TXT nicht gefunden!\n\
Daher keine Anzeige der Vergleichsspannungen (GEH,NH,SH).\n\
Zuerst Spannungsberechnung mit Z88D.");
    if(LANG == 2) strcpy(cmess,"Z88O5.TXT not found !\n\
Thus no view of effective stresses (v.Mises,Rankine,Tresca).\n\
Start a stress computation with Z88D first");
    idiag= 2;
    if3d= IDM_LIGHT;
  break;    

  case AL_NOO8:
    if(LANG == 1) strcpy(cmess,"Z88O8.TXT nicht gefunden!\n\
Daher keine Anzeige der Vergleichsspannungen(GEH,NH,SH).\n\
Zuerst Spannungsberechnung mit Z888");
    if(LANG == 2) strcpy(cmess,"Z88O8.TXT not found !\n\
Thus no view of effective stresses (v.Mises,Rankine,Tresca).\n\
Start a stress computation with Z88D first");
    idiag= 2;
    if3d= IDM_LIGHT;
  break;    

  case AL_NINT0:
    if(LANG == 1) strcpy(cmess,"Integrationsordnung 0! Abhilfe: NINT > 0 in Z88INT.TXT, Z88R starten");
    if(LANG == 2) strcpy(cmess,"integration order 0! Recover: NINT > 0 in Z88INT.TXT, run Z88R again");
    idiag= 2;
    if3d= IDM_LIGHT;
  break;    

  case AL_NONINT0:
    if(LANG == 1) strcpy(cmess,"Integrationsordnung ist nicht Null! Neuer Lauf Z88R mit NINT=0 in Z88INT.TXT.");
    if(LANG == 2) strcpy(cmess,"Integration constant is not Zero! Run Z88R again, enter NINT=0 in Z88INT.TXT .");
    idiag= 2;
    if3d= IDM_LIGHT;
  break;    

  case AL_EXMAXK:
    if(LANG == 1) strcpy(cmess,"Speicher fuer Knoten ueberschritten ! STOP !\n\
Abhilfe: MAXK oder MFACCOMMON in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for nodes exhausted ! STOP !\n\
Recover: increase MAXK or MFACCOMMON in Z88.DYN .");
    idiag= 1;
  break;

  case AL_EXMAXKOI:
    if(LANG == 1) strcpy(cmess,"Speicher fuer Koinzidenzvektor ueberschritten ! STOP !\n\
Abhilfe: MAXKOI in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for coincidence vector exhausted ! STOP\n\
Recover: increase MAXKOI in Z88.DYN .");
    idiag= 1;
  break;

  case AL_EXMAXE:
    if(LANG == 1) strcpy(cmess,"Speicher fuer Elemente ueberschritten !\n\
STOP ! Abhilfe: MAXE in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for elements exhausted ! STOP !\n\
Recover: increase MAXE in Z88.DYN .");
    idiag= 1;
  break;

  case AL_EXMAXGP:
    if(LANG == 1) strcpy(cmess,"zuviele Gausspunkte! STOP ! Abhilfe: MAXGP in Z88.DYN erhoehen");
    if(LANG == 2) strcpy(cmess,"too many Gauss points! STOP ! Recover: increase MAXGP in Z88.DYN");
    idiag= 1;
  break;

  case AL_EXMAXPR:
    if(LANG == 1) strcpy(cmess,"Speicher fuer Drucklasten ueberschritten! STOP ! Abhilfe: MAXPR in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for pressure loads exhausted! STOP ! Recover: increase MAXPR in Z88.DYN.");
    idiag= 1;
  break;

  case AL_EXMAXRBD:
    if(LANG == 1) strcpy(cmess,"Speicher fuer Randbedingungen ueberschritten! STOP ! Abhilfe: MAXRBD in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for boundary conditions exhausted! STOP ! Recover: increase MAXRBD in Z88.DYN .");
    idiag= 1;
  break;

  case AL_WRONGDIM:
    if(LANG == 1) strcpy(cmess,"Falsche Dimension im Structurfile ! STOP !\n\
Abhilfe: Im Strukturfile 2 oder 3 fuer Dimension waehlen.");
    if(LANG == 2) strcpy(cmess,"Wrong dimension in structur file ! STOP !\n\
Recover: enter 2 or 3 for dimension in structure file.");
    idiag= 1;
  break;
  }

/*----------------------------------------------------------------------
* nun die Questionbox
*---------------------------------------------------------------------*/
if(idiag == 1) MB_ALERT= gtk_message_dialog_new(GTK_WINDOW(H_WIN),
                         GTK_DIALOG_DESTROY_WITH_PARENT,
                         GTK_MESSAGE_ERROR,GTK_BUTTONS_OK,cmess);

if(idiag == 2) MB_ALERT= gtk_message_dialog_new(GTK_WINDOW(H_WIN),
                         GTK_DIALOG_DESTROY_WITH_PARENT,
                         GTK_MESSAGE_INFO,GTK_BUTTONS_OK,cmess);

iret= gtk_dialog_run(GTK_DIALOG(MB_ALERT));
if(idiag == 1) gtk_main_quit();   /* du bist terminiert */
ialert= 0;                        /* neue Chance */
gtk_widget_destroy(MB_ALERT);

return 0;
}  

