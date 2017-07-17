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
*  function ale88g gibt Fehlermeldungen aus
*  21.7.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88g.h>
#include <stdio.h>    /* printf */
#endif

/***********************************************************************
*  hier beginnt Function ale88g
***********************************************************************/
int ale88g(int ialert)
{
extern FR_INT4 LANG;

switch(ialert)
  {
  case AL_NOLOG:
    if(LANG == 1) printf("### kann Z88G.LOG nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88G.LOG ..stop ###\n");
  break;

  case AL_NODYN:
    if(LANG == 1) printf("### kann Z88.DYN nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88.DYN ..stop ###\n");
  break;

  case AL_WRONGDYN:
    if(LANG == 1) printf("### File Z88.DYN ist nicht korrekt ..Stop ###\n");
    if(LANG == 2) printf("### file Z88.DYN is not correct ..stop ###\n");
  break;

  case AL_NOCOS:
    if(LANG == 1) printf("### kann Z88G.COS nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88G.COS ..stop ###\n");
  break;

  case AL_NONAS:
    if(LANG == 1) printf("### kann Z88G.NAS nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88G.NAS ..stop ###\n");
  break;

  case AL_NOIN:
    if(LANG == 1) printf("### kann Z88G.IN nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88G.IN ..stop ###\n");
  break;

  case AL_NOI1:
    if(LANG == 1) printf("### kann Z88I1.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88I1.TXT ..stop ###\n");
  break;

  case AL_NOI2:
    if(LANG == 1) printf("### kann Z88I2.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88I2.TXT ..stop ###\n");
  break;

  case AL_NOMEMY:
    if(LANG == 1)printf("### nicht genuegend dynamisches Memory ..Stop ###\n");
    if(LANG == 2)printf("### insufficient dynamic memory ..stop ###\n");
  break;
  }
return(0);
}
