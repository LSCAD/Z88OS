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
*  function ale88h gibt Fehlermeldungen aus
*  21.7.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88h.h>
#include <stdio.h>    /* printf */
#endif

/***********************************************************************
*  hier beginnt Function ale88h
***********************************************************************/
int ale88h(int ialert)
{
extern FR_INT4 LANG;

switch(ialert)
  {
  case AL_NOLOG:
    if(LANG == 1) printf("### kann Z88H.LOG nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88H.LOG ..stop ###\n");
    break;
  case AL_NODYN:
    if(LANG == 1) printf("### kann Z88.DYN nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88.DYN ..stop ###\n");
    break;
  case AL_WRONGDYN:
    if(LANG == 1) printf("### File Z88.DYN ist nicht korrekt ..Stop ###\n");
    if(LANG == 2) printf("### file Z88.DYN is not correct ..stop ###\n");
    break;
  case AL_NOIN:
    if(LANG == 1) printf("### kann Z88H.IN nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88H.IN ..stop ###\n");
    break;
  case AL_NOI1:
    if(LANG == 1) printf("### kann Z88I1.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88I1.TXT ..stop ###\n");
    break;
  case AL_NOI2:
    if(LANG == 1) printf("### kann Z88I2.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88I2.TXT ..stop ###\n");
    break;
  case AL_NOI5:
    if(LANG == 1) printf("### kann Z88I5.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88I5.TXT ..stop ###\n");
    break;
  case AL_NOOUT:
    if(LANG == 1) printf("### kann Z88H.OUT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88H.OUT ..stop ###\n");
    break;
  case AL_NOMEM:
    if(LANG == 1) printf("### kann Memory nicht anlegen ..Stop ###\n");
    if(LANG == 2) printf("### cannot allocate memory ..stop ###\n");
    break;
  case AL_1STOP:
    if(LANG == 1) printf("### MAXGRA ueberschritten ..Stop ###\n");
    if(LANG == 2) printf("### MAXGRA exceeded ..stop ###\n");
    break;
  }
return(0);
}
