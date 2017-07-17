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
*  function ale88x gibt Fehlermeldungen aus
*  29.7.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88x.h>
#include <windows.h>    /* printf */
#endif

/***********************************************************************
*  hier beginnt Function ale88x
***********************************************************************/
int ale88x(int ialert)
{
extern FR_INT4 MAXKSS, MAXESS, LANG;

char cmess[256];

switch(ialert)
  {
  case AL_NOLOG:
    if(LANG == 1) strcpy(cmess,"Kann Z88X.LOG nicht oeffnen !   STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88X.LOG !    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_NODYN:
    if(LANG == 1) strcpy(cmess,"Kann Z88.DYN nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88.DYN !    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_WRONGDYN:
    if(LANG == 1) strcpy(cmess,"Z88.DYN ist nicht korrekt !    STOP");
    if(LANG == 2) strcpy(cmess,"Z88.DYN is invalid or wrong !    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_NOMEMY:
    if(LANG == 1) strcpy(cmess,"Nicht genug dynamischer Speicher !    STOP\
    Abhilfe: Eintraege in Z88.DYN erhoehen");
    if(LANG == 2) strcpy(cmess,"Dynamic memory exhausted !    STOP\
    Recover: increase entries in Z88.DYN");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_NOI1:
    if(LANG == 1) strcpy(cmess,"Kann Z88I1.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88I1.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_NOI2:
    if(LANG == 1) strcpy(cmess,"Kann Z88I2.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88I2.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_NOI5:
    if(LANG == 1) strcpy(cmess,"Kann Z88I5.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88I5.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_NONI:
    if(LANG == 1) strcpy(cmess,"Kann Z88NI.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88NI.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_NOX:
    if(LANG == 1) strcpy(cmess,"Kann Z88X.DXF nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88X.DXF !    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_WROIXI1:
    if(LANG == 1) strcpy(cmess,"Z88X.DXF fuer Z88I1.TXT: erste Eingabegruppe \
fehlt oder falsch    STOP");
    if(LANG == 2) strcpy(cmess,"Z88X.DXF for Z88I1.TXT: first Inputgroup \
missing or wrong    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_WROIXNI:
    if(LANG == 1) strcpy(cmess,"Z88X.DXF fuer Z88NI.TXT: erste Eingabegruppe \
fehlt oder falsch    STOP");
    if(LANG == 2) strcpy(cmess,"Z88X.DXF for Z88NI.TXT: first Inputgroup \
missing or wrong    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_WROIXKNO:
    if(LANG == 1) strcpy(cmess,"Z88X.DXF fuer Z88I1.TXT/Z88NI.TXT: gefundene \
Anzahl Knoten stimmt nicht    STOP");
    if(LANG == 2) strcpy(cmess,"Z88X.DXF for Z88I1.TXT/Z88NI.TXT: number of \
nodes found is wrong    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_WROIXELE:
    if(LANG == 1) strcpy(cmess,"Z88X.DXF fuer Z88I1.TXT/Z88NI.TXT: gefundene \
Anzahl Elemente stimmt nicht    STOP");
    if(LANG == 2) strcpy(cmess,"Z88X.DXF for Z88I1.TXT/Z88NI.TXT: number of \
elements found is wrong    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_WROIXKOI:
    if(LANG == 1) strcpy(cmess,"Z88X.DXF fuer Z88I1.TXT/Z88NI.TXT: identische \
Knoten in Element(en) gefunden    STOP");
    if(LANG == 2) strcpy(cmess,"Z88X.DXF for Z88I1.TXT/Z88NI.TXT: identical \
nodes in element(s) detected    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_WROIXI21Z:
    if(LANG == 1) strcpy(cmess,"Z88X.DXF fuer Z88I2.TXT: Anzahl \
Randbedingungen fehlt oder falsch     STOP");
    if(LANG == 2) strcpy(cmess,"Z88X.DXF for Z88I2.TXT: number of\
constraints missing or wrong    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_WROIXI2R:
    if(LANG == 1) strcpy(cmess,"Z88X.DXF fuer Z88I2.TXT: Falsche oder zuwenig \
Randbedingungen     STOP");
    if(LANG == 2) strcpy(cmess,"Z88X.DXF for Z88I2.TXT: Missing or wrong \
constraints    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_WROIXI51Z:
    if(LANG == 1) strcpy(cmess,"Z88X.DXF fuer Z88I5.TXT: Anzahl \
Flaechenlasten fehlt oder falsch     STOP");
    if(LANG == 2) strcpy(cmess,"Z88X.DXF for Z88I5.TXT: number of\
surface loads missing or wrong    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_WROIXI5R:
    if(LANG == 1) strcpy(cmess,"Z88X.DXF fuer Z88I5.TXT: Falsche oder zuwenig \
Flaechenlasten     STOP");
    if(LANG == 2) strcpy(cmess,"Z88X.DXF for Z88I5.TXT: Missing or wrong \
surface loads    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_WRONDIM:
    if(LANG == 1) strcpy(cmess,"Dimension falsch     STOP");
    if(LANG == 2) strcpy(cmess,"Dimension wrong    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_EXMAXK:
    if(LANG == 1) strcpy(cmess,"Zuviele Knoten     STOP    Abhilfe: MAXK \
in Z88.DYN erhoehen");
    if(LANG == 2) strcpy(cmess,"Too many nodes    STOP    Recover: \
Increase MAXK in Z88.DYN");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
    break;

  case AL_EXMAXE:
    if(LANG == 1) strcpy(cmess,"Zuviele Elemente     STOP    Abhilfe: \
MAXE in Z88.DYN erhoehen");
    if(LANG == 2) strcpy(cmess,"Too many elements    STOP    Recover: \
Increase MAXE in Z88.DYN");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
    break;

  case AL_EXMAXNFG:
    if(LANG == 1) strcpy(cmess,"Zuviele Freiheitsgrade     STOP    Abhilfe: \
MAXNFG in Z88.DYN erhoehen");
    if(LANG == 2) strcpy(cmess,"Too many DOF    STOP    Recover: \
Increase MAXNFG in Z88.DYN");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
    break;

  case AL_EXMAXPR:
    if(LANG == 1) strcpy(cmess,"Zuviele Flaechenlasten     STOP    Abhilfe: \
MAXPR in Z88.DYN erhoehen");
    if(LANG == 2) strcpy(cmess,"Too many surface loads    STOP    Recover: \
Increase MAXPR in Z88.DYN");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
    break;

  case AL_WROKFLAG:
    if(LANG == 1) strcpy(cmess,"Koordinatenflag KFLAG falsch     STOP");
    if(LANG == 2) strcpy(cmess,"Coordinate flag KFLAG wrong    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_WROETYPI1:
    if(LANG == 1) strcpy(cmess,"Unbekannter Elementtyp in Z88I1.TXT     STOP");
    if(LANG == 2) strcpy(cmess,"Unknown element type in Z88I1.TXT    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_WROETYPNI:
    if(LANG == 1) strcpy(cmess,"Unbekannter Elementtyp in Z88NI.TXT     STOP");
    if(LANG == 2) strcpy(cmess,"Unknown element type in Z88NI.TXT    STOP");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_EXKOI:
    if(LANG == 1) strcpy(cmess,"Zuwenig Speicher     STOP    Abhilfe: \
MAXKOI in Z88.DYN erhoehen");
    if(LANG == 2) strcpy(cmess,"Memory exhausted    STOP    Recover \
Increase MAXKOI in Z88.DYN");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  case AL_NOACROBAT:
    if(LANG == 1) strcpy(cmess,"PDF-Viewer konnte nicht gestartet werden");
    if(LANG == 2) strcpy(cmess,"Could not launch PDF Viewer");
    MessageBox(NULL,cmess, "Z88X",MB_OK | MB_ICONHAND);
  break;

  }
return(0);
}
  
