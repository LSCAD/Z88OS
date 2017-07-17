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
* Function ale88n gibt Fehlermeldungen aus
* 3.8.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88n.h>
#include <windows.h>
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
* hier beginnt Function ale88n
***********************************************************************/
int ale88n(int ialert)
{
extern FR_INT4 MAXKSS,MAXESS,LANG;

char cmess[256];

switch(ialert)
  {
  case AL_NOLOG:
    if(LANG == 1) strcpy(cmess,"Kann Z88N.LOG nicht oeffnen !   STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88N.LOG !    STOP");
    MessageBox(NULL,cmess, "Z88N",MB_OK | MB_ICONHAND);
  break;

  case AL_NOACROBAT:
    if(LANG == 1) strcpy(cmess,"Kann PDF-Viewer nicht oeffnen !");
    if(LANG == 2) strcpy(cmess,"Cannot open PDF Viewer !");
    MessageBox(NULL,cmess, "Z88N",MB_OK | MB_ICONHAND);
  break;

  case AL_NODYN:
    if(LANG == 1) strcpy(cmess,"Kann Z88.DYN nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88.DYN !    STOP");
    MessageBox(NULL,cmess, "Z88N",MB_OK | MB_ICONHAND);
  break;

  case AL_WRONGDYN:
    if(LANG == 1) strcpy(cmess,"Z88.DYN ist nicht korrekt !    STOP");
    if(LANG == 2) strcpy(cmess,"Z88.DYN is invalid or wrong !    STOP");
    MessageBox(NULL,cmess, "Z88N",MB_OK | MB_ICONHAND);
  break;

  case AL_NOMEMY:
    if(LANG == 1) strcpy(cmess,"Nicht genug dynamischer Speicher !    STOP\
    Abhilfe: Eintraege in Z88.DYN erhoehen");
    if(LANG == 2) strcpy(cmess,"Dynamic memory exhausted !    STOP\
    Recover: increase entries in Z88.DYN");
    MessageBox(NULL,cmess, "Z88N",MB_OK | MB_ICONHAND);
  break;

  case AL_NONI:
    if(LANG == 1) strcpy(cmess,"Kann Z88NI.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88NI.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88N",MB_OK | MB_ICONHAND);
  break;

  case AL_NOI1:
    if(LANG == 1) strcpy(cmess,"Kann Z88I1.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88I1.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88N",MB_OK | MB_ICONHAND);
  break;

  case AL_EXSUPERK:
    if(LANG==1)sprintf(cmess,"Nur " PD " Superknoten zulaessig    STOP",MAXKSS);
    if(LANG==2)sprintf(cmess,"Only " PD " super nodes allowed    STOP",MAXKSS);
    MessageBox(NULL, cmess, "Z88N", MB_OK | MB_ICONHAND);
  break;

  case AL_EXSUPERE:
    if(LANG==1)sprintf(cmess,"Nur " PD " Superelemente zulaessig    STOP",MAXKSS);
    if(LANG==2)sprintf(cmess,"Only " PD " super elements allowed    STOP",MAXKSS);
    MessageBox(NULL, cmess, "Z88N", MB_OK | MB_ICONHAND);
  break;

  case AL_TOBIG1:
    if(LANG == 1) strcpy(cmess,
      "Zuwenig Speicher !    STOP    Abhilfe: MAXSE in Z88.DYN erhoehen");
    if(LANG == 2) strcpy(cmess,
      "Out of Memory !    STOP    Recover: Increase MAXSE in Z88.DYN");
    MessageBox(NULL,cmess, "Z88N",MB_OK | MB_ICONHAND);
  break;

  case AL_FEEXID:
    if(LANG == 1) strcpy(cmess,"Erzeugte Struktur zu gross fuer FE-Lauf !\
    ACHTUNG    Abhilfe: MAXK,MAXE,MAXNFG pruefen,ggf. in Z88.DYN erhoehen");
    if(LANG == 2) strcpy(cmess,"Generated mesh too large for a FEA run !\
    CAUTION    Recover: Check MAXSK,MAXE,MAXNFG and increase in Z88.DYN");
    MessageBox(NULL,cmess, "Z88N",MB_OK | MB_ICONINFORMATION);
  break;

  }
return(0);
}
  
