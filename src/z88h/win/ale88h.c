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
* Function ale88h gibt Fehlermeldungen aus
* 3.8.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88h.h>
#include <windows.h>
#include <stdio.h>    /* printf */
#endif


/***********************************************************************
*  hier beginnt Function ale88h
***********************************************************************/
int ale88h(int ialert)
{
extern FR_INT4 LANG;

char cmess[256];

switch(ialert)
  {
  case AL_NOLOG:
    if(LANG == 1) strcpy(cmess,"Kann Z88H.LOG nicht oeffnen !   STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88H.LOG !    STOP");
    MessageBox(NULL,cmess, "Z88H",MB_OK | MB_ICONHAND);
  break;

  case AL_NOACROBAT:
    if(LANG == 1) strcpy(cmess,"Kann PDF-Viewer nicht oeffnen !");
    if(LANG == 2) strcpy(cmess,"Cannot open PDF Viewer !");
    MessageBox(NULL,cmess, "Z88H",MB_OK | MB_ICONHAND);
  break;

  case AL_NODYN:
    if(LANG == 1) strcpy(cmess,"Kann Z88.DYN nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88.DYN !    STOP");
    MessageBox(NULL,cmess, "Z88H",MB_OK | MB_ICONHAND);
  break;

  case AL_WRONGDYN:
    if(LANG == 1) strcpy(cmess,"Z88.DYN ist nicht korrekt !    STOP");
    if(LANG == 2) strcpy(cmess,"Z88.DYN is invalid or wrong !    STOP");
    MessageBox(NULL,cmess, "Z88H",MB_OK | MB_ICONHAND);
  break;

  case AL_NOIN:
    if(LANG == 1) strcpy(cmess,"Kann Z88H.IN nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88H.IN !    STOP");
    MessageBox(NULL,cmess, "Z88H",MB_OK | MB_ICONHAND);
  break;

  case AL_NOI1:
    if(LANG == 1) strcpy(cmess,"Kann Z88I1.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88I1.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88H",MB_OK | MB_ICONHAND);
  break;

  case AL_NOI2:
    if(LANG == 1) strcpy(cmess,"Kann Z88I2.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88I2.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88H",MB_OK | MB_ICONHAND);
  break;

  case AL_NOI5:
    if(LANG == 1) strcpy(cmess,"Kann Z88I5.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88I5.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88H",MB_OK | MB_ICONHAND);
  break;

  case AL_NOOUT:
    if(LANG == 1) strcpy(cmess,"Kann Z88H.OUT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88H.OUT !    STOP");
    MessageBox(NULL,cmess, "Z88H",MB_OK | MB_ICONHAND);
  break;

  case AL_NOMEM:
    if(LANG == 1) strcpy(cmess,"Kann Memory nicht anlegen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot allocate memory !    STOP");
    MessageBox(NULL,cmess, "Z88H",MB_OK | MB_ICONHAND);
  break;

  case AL_1STOP:
    if(LANG == 1) strcpy(cmess,"MAXGRA ueberschritten !    STOP");
    if(LANG == 2) strcpy(cmess,"MAXGRA exceeded !    STOP");
    MessageBox(NULL,cmess, "Z88H",MB_OK | MB_ICONHAND);
  break;
  }
return(0);
}

