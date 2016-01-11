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
* Function ale88n gibt Fehlermeldungen aus
* 31.7.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88n.h>
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

switch(ialert)
  {
  case AL_NOLOG:
    if(LANG == 1) printf("### kann Z88N.LOG nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88N.LOG ..stop ###\n");
    break;
  case AL_NODYN:
    if(LANG == 1) printf("### kann Z88.DYN nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88.DYN ..stop ###\n");
    break;
  case AL_WRONGDYN:
    if(LANG == 1) printf("### File Z88.DYN ist nicht korrekt ..Stop ###\n");
    if(LANG == 2) printf("### file Z88.DYN is not correct ..stop ###\n");
    break;
  case AL_NOMEMY:
    if(LANG == 1)printf("### nicht genuegend dynamisches Memory ..Stop ###\n");
    if(LANG == 2)printf("### insufficient dynamic memory ..Stop ###\n");
    break;
  case AL_NONI:
    if(LANG == 1) printf("### kann Z88NI.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88NI.TXT ..stop ###\n");
    break;
  case AL_NOI1:
    if(LANG == 1) printf("### kann Z88I1.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88I1.TXT ..stop ###\n");
    break;
  case AL_EXSUPERK:
    if(LANG == 1)
      {
      printf("### nur " PD " Superknoten zulaessig ..Stop ###\n",MAXKSS);
      printf("### Abhilfe: MAXKSS in Z88.DYN erhoehen  ###\n");
      }
    if(LANG == 2)
      {
      printf("### only " PD " super nodes allowed ..stop ###\n",MAXKSS);
      printf("### recover: increase MAXKSS in Z88.DYN ###\n");
      }
    break;
  case AL_EXSUPERE:
    if(LANG == 1)
      {
      printf("### nur " PD " Superelemente zulaessig ..Stop ###\n",MAXESS);
      printf("### Abhilfe: MAXESS in Z88.DYN erhoehen    ###\n");
      }
    if(LANG == 2)
      {
      printf("### only " PD " super elements allowed ..stop ###\n",MAXESS);
      printf("### recover: increase MAXESS in Z88.DYN    ###\n");
      }
    break;
  case AL_TOBIG1:
    if(LANG == 1)
      {
      printf("### Dynamischer Speicher erschoepft.. Stop ###\n");
      printf("### Abhilfe: kleinere Struktur anfordern   ###\n");
      printf("### oder MAXSE in Z88.DYN erhoehen         ###\n");
      }
    if(LANG == 2)
      {
      printf("### dynamic memory exhausted.. Stop ###\n");
      printf("### recover: generate a smaller net ###\n");
      printf("### or increase MAXSE in Z88.DYN    ###\n");
      }
    break;
  case AL_FEEXID:
    if(LANG == 1)
      {
      printf("### Achtung!                                 ###\n");
      printf("### Erzeugte Struktur zu gross fuer FE-Lauf  ###\n");
      printf("### MAXK,MAXE und MAXNFG in Z88.DYN erhoehen ###\n");
      }
    if(LANG == 2)
      {
      printf("### Warning! just generated net is too        ###\n");
      printf("### heavy for a solver run ! recover:         ###\n");
      printf("### increase MAXK,MAXE und MAXNFG in Z88.DYN  ###\n");
      }
    break;
  }
return(0);
}
