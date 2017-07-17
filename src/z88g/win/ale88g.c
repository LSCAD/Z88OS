/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows 
* and the UNIX OS.
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
* Function ale88g gibt Fehlermeldungen aus
* 29.7.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88g.h>
#include <windows.h>
#include <stdio.h>    /* printf */
#endif


/***********************************************************************
*  hier beginnt Function ale88g
***********************************************************************/
int ale88g(int ialert)
{
extern FR_INT4 LANG;

char cmess[256];

switch(ialert)
  {
  case AL_NOLOG:
    if(LANG == 1) strcpy(cmess,"Kann Z88G.LOG nicht oeffnen !   STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88G.LOG !    STOP");
    MessageBox(NULL,cmess, "Z88G",MB_OK | MB_ICONHAND);
  break;

  case AL_NODYN:
    if(LANG == 1) strcpy(cmess,"Kann Z88.DYN nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88.DYN !    STOP");
    MessageBox(NULL,cmess, "Z88G",MB_OK | MB_ICONHAND);
  break;

  case AL_WRONGDYN:
    if(LANG == 1) strcpy(cmess,"Z88.DYN ist nicht korrekt !    STOP");
    if(LANG == 2) strcpy(cmess,"Z88.DYN is invalid or wrong !    STOP");
    MessageBox(NULL,cmess, "Z88G",MB_OK | MB_ICONHAND);
  break;

  case AL_NOCOS:
    if(LANG == 1) strcpy(cmess,"Kann Z88G.COS nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88G.COS !    STOP");
    MessageBox(NULL,cmess, "Z88G",MB_OK | MB_ICONHAND);
  break;

  case AL_NONAS:
    if(LANG == 1) strcpy(cmess,"Kann Z88G.NAS nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88G.NAS !    STOP");
    MessageBox(NULL,cmess, "Z88G",MB_OK | MB_ICONHAND);
  break;

  case AL_NOIN:
    if(LANG == 1) strcpy(cmess,"Kann Z88G.IN nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88G.IN !    STOP");
    MessageBox(NULL,cmess, "Z88G",MB_OK | MB_ICONHAND);
  break;

  case AL_NOI1:
    if(LANG == 1) strcpy(cmess,"Kann Z88I1.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88I1.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88G",MB_OK | MB_ICONHAND);
  break;

  case AL_NOI2:
    if(LANG == 1) strcpy(cmess,"Kann Z88I2.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88I2.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88G",MB_OK | MB_ICONHAND);
  break;

  case AL_NOMEMY:
    if(LANG == 1) strcpy(cmess,"Nicht genuegend dynamisches Memory !    STOP");
    if(LANG == 2) strcpy(cmess,"insufficient dynamic memory !    STOP");
    MessageBox(NULL,cmess, "Z88G",MB_OK | MB_ICONHAND);
  break;

  case AL_NOACROBAT:
    if(LANG == 1) strcpy(cmess,"PDF-Viewer konnte nicht gestartet werden");
    if(LANG == 2) strcpy(cmess,"could not launch PDF Viewer");
    MessageBox(NULL,cmess, "Z88G",MB_OK | MB_ICONHAND);
  break;
  }
return(0);
}

