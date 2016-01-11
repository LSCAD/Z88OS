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
* Diese Compilerunit umfasst:
* wrim88r gibt Texte aus (1 FR_INT4)
* wtya88j gibt Elementtypen aus (1 FR_INT4, 1 FR_INT4) : Z88A
* wtyp88j gibt Elementtypen aus (1 FR_INT4, 1 FR_INT4) : Z88BR
* wfor88i gibt kfoun beim Sortieren aus (1 FR_INT4, 1 FR_INT4)
* wran88j gibt Randbedingungen aus (1 FR_INT4, 1 FR_INT4)
* wtyd88j gibt Elementtypen aus (1 FR_INT4, 1 FR_INT4) : Z88DR
* wtye88j gibt Elementtypen aus (1 FR_INT4, 1 FR_INT4) : Z88ER
* 10.8.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <windows.h>
#include <string.h>   /* strlen  */
#include <stdio.h>    /* sprintf */
#include <stdlib.h>   /* ltoa    */
#endif

/***********************************************************************
* Formate
***********************************************************************/
#ifdef FR_XINT
#define PD "%d"
#define PD9 "%9d"
#endif

#ifdef FR_XLONG
#define PD "%ld"
#define PD9 "%9ld"
#endif

#ifdef FR_XLOLO
#define PD "%lld"
#define PD9 "%9lld"
#endif

#ifdef FR_XDOUB
#define PG "%lg"
#endif

#ifdef FR_XQUAD
#define PG "%Lg"
#endif

/***********************************************************************
*  hier beginnt Function wrim88r
***********************************************************************/
int wrim88r(FR_INT4 i,int iatx)
{
extern HDC       hDC;
extern FR_DOUBLE rpalpha,rpomega;
extern FR_INT4   LANG,isflag;

size_t laenge;

int j;

char cline[80];

switch(iatx)
  {

  case TX_IFNILI0:
    if(LANG == 1) sprintf(cline,"Z88R= Berechnung +");
    if(LANG == 2) sprintf(cline,"Z88R= computation +");
    laenge= strlen(cline);
    TextOut(hDC,70,30,cline,laenge);
  break;

  case TX_IFNILI9:
    if(LANG == 1) sprintf(cline,"= Testmode +");
    if(LANG == 2) sprintf(cline,"= test mode +");
    laenge= strlen(cline);
    TextOut(hDC,70,30,cline,laenge);
  break;

  case TX_ICFLAG0:
    if(LANG == 1) sprintf(cline,"Cholesky-Solver");
    if(LANG == 2) sprintf(cline,"Cholesky Solver");
    laenge= strlen(cline);
    TextOut(hDC,235,30,cline,laenge);
  break;

  case TX_ICFLAG1:
    if(LANG == 1) sprintf(cline,"SICCG-Solver");
    if(LANG == 2) sprintf(cline,"SICCG Solver");
    laenge= strlen(cline);
    TextOut(hDC,235,30,cline,laenge);
  break;

  case TX_ICFLAG2:
    if(LANG == 1) sprintf(cline,"SORCG-Solver");
    if(LANG == 2) sprintf(cline,"SORCG Solver");
    laenge= strlen(cline);
    TextOut(hDC,235,30,cline,laenge);
  break;

  case TX_REAI1:
    if(LANG == 1) TextOut(hDC,10,70,"Z88I1.TXT einlesen :",20);
    if(LANG == 2) TextOut(hDC,10,70,"Reading Z88I1.TXT : ",20);
  break;

  case TX_REAINT:
    if(LANG == 1) TextOut(hDC,10,70,"Z88INT.TXT einlesen:",20);
    if(LANG == 2) TextOut(hDC,10,70,"Reading Z88INT.TXT: ",20);
  break;

  case TX_REAELP:
    if(LANG == 1) TextOut(hDC,10,70,"Z88ELP.TXT einlesen:",20);
    if(LANG == 2) TextOut(hDC,10,70,"Reading Z88ELP.TXT: ",20);
  break;

  case TX_REAMAT:
    if(LANG == 1) TextOut(hDC,10,70,"Z88MAT.TXT einlesen:",20);
    if(LANG == 2) TextOut(hDC,10,70,"Reading Z88MAT.TXT: ",20);
  break;

  case TX_REAMAN:
    if(LANG == 1) TextOut(hDC,10,70,"Z88MAN.TXT einlesen:",20);
    if(LANG == 2) TextOut(hDC,10,70,"Reading Z88MAN.TXT: ",20);
  break;

  case TX_KOOR:
    if(LANG == 1) TextOut(hDC,290,70,"Koordinaten einlesen",20);
    if(LANG == 2) TextOut(hDC,290,70,"Reading coordinates ",20);
  break;

  case TX_POLAR:
    if(LANG == 1) TextOut(hDC,290,70,"Polar/Zylinder-Koordinaten",26);
    if(LANG == 2) TextOut(hDC,290,70,"Polar/cylinder coordinates",26);
  break;

  case TX_KOIN:
    if(LANG == 1) TextOut(hDC,10,70,"Koinzidenz einlesen",19);
    if(LANG == 2) TextOut(hDC,10,70,"Reading element infos",21);
  break;

  case TX_Z88A:
    TextOut(hDC,10,90,">>> Start Z88A: Pass 1 <<<",26);
  break;

  case TX_Z88AI:
    TextOut(hDC,10,90,">>> Start Z88AI: Pass 1 <<<",27);
  break;

  case TX_SUMMEMY:
    if(LANG == 1) sprintf(cline,"Programm hat " PD " MB statisch angefordert", i);
    if(LANG == 2) sprintf(cline,"Program allocated " PD " MB statically",i);
    laenge= strlen(cline);
    TextOut(hDC,10,110,cline,laenge);
  break;

  case TX_DYNMEMY:
    if(LANG == 1) sprintf(cline,"Programm hat " PD " MB dynamischen Speicher angefordert", i);
    if(LANG == 2) sprintf(cline,"program allocated " PD " MB dynamic memory",i);
    laenge= strlen(cline);
    TextOut(hDC,10,130,cline,laenge);
  break;

  case TX_GSSO:
    if(LANG == 1) sprintf(cline,">>> Alle Pointer assembliert <<<");
    if(LANG == 2) sprintf(cline,">>> All pointers assembled <<<");
    laenge= strlen(cline);
    for(j= 1; j <= 10; j++)
      TextOut(hDC,10,170,cline,laenge);
  break;

  case TX_WRIO0:
    if(LANG == 1) TextOut(hDC,290,170,"Z88O0.TXT beschreiben  ",23);
    if(LANG == 2) TextOut(hDC,290,170,"Writing Z88O0.TXT      ",23);
  break;

  case TX_GSERF:
    if(LANG == 1) sprintf(cline,"GS erfordert " PD " Elemente",i);
    if(LANG == 2) sprintf(cline,"GS needs " PD " elements",i);
    laenge= strlen(cline);
    TextOut(hDC,10,190,cline,laenge);
  break;

  case TX_KOIERF:
    if(LANG == 1) sprintf(cline,"KOI erfordert " PD " Elemente",i);
    if(LANG == 2) sprintf(cline,"KOI needs " PD " elements",i);
    laenge= strlen(cline);
    TextOut(hDC,290,190,cline,laenge);
  break;

  case TX_Z88B:
    TextOut(hDC,10,210,">>> Start Z88BR: Pass 2 <<<",27);
  break;

   case TX_REAI5:
    if(LANG == 1) TextOut(hDC,290,230,"Lastvektoren berechnen",22);
    if(LANG == 2) TextOut(hDC,290,230,"Computing Load Vectors",22);
  break;

  case TX_Z88CC:
    TextOut(hDC,10,250,">>> Start Z88CR: Pass 3 <<<",27);
  break;

  case TX_REAI2:
    if(LANG == 1) TextOut(hDC,290,270,"Lesen RB-File Z88I2.TXT",23);
    if(LANG == 2) TextOut(hDC,290,270,"Reading BC file Z88I2.TXT",25);
  break;

  case TX_REAI2P2:
    if(LANG == 1) TextOut(hDC,290,270,"Lesen RB-File Z88I2.TXT",23);
    if(LANG == 2) TextOut(hDC,290,270,"Reading BC file Z88I2.TXT",25);
  break;

  case TX_ERBPA:
    if(LANG == 1) sprintf(cline,"Einarbeiten der Randbed. Pass " PD,i);
    if(LANG == 2) sprintf(cline,"Incorporating constraints pass " PD,i);
    laenge= strlen(cline);
    TextOut(hDC,10,290,cline,laenge);
  break;

  case TX_WRIO1:
    if(LANG == 1) TextOut(hDC,10,310,"Z88O1.TXT beschreiben",21);
    if(LANG == 2) TextOut(hDC,10,310,"Writing Z88O1.TXT    ",21);
  break;

  case TX_SCAL88:
    TextOut(hDC,290,310,"Start SCAL88",12);
  break;


  case TX_CHOY88:
    if(LANG == 1) TextOut(hDC,10,330,"Start des Cholesky-Solvers",26);
    if(LANG == 2) TextOut(hDC,10,330,"Start of Cholesky Solver",24);
  break;

  case TX_NFG:
    if(LANG == 1) sprintf(cline,PD " x " PD " = Groesse Gleichungsystem",i,i);
    if(LANG == 2) sprintf(cline,PD " x " PD " = size of system of equations",i,i);
    laenge= strlen(cline);
    TextOut(hDC,10,350,cline,laenge);
  break;

  case TX_CHOJ:
    ltoa(i,cline,10);
    laenge= strlen(cline);
    TextOut(hDC,360,350,cline,laenge);
  break;

  case TX_SICCG88:
    if(LANG == 1) TextOut(hDC,10,330,">>> Start des Solvers SICCG <<<",31);
    if(LANG == 2) TextOut(hDC,10,330,">>> Start of Solver SICCG <<<",29);
  break;

  case TX_SORCG88:
    if(LANG == 1) TextOut(hDC,10,330,">>> Start des Solvers SORCG <<<",31);
    if(LANG == 2) TextOut(hDC,10,330,">>> Start of Solver SORCG <<<",29);
  break;

  case TX_PART88:
    if(LANG == 1) sprintf(cline,"par. Cholesky-Zerl. Nr." PD,i);
    if(LANG == 2) sprintf(cline,"inc. Cholesky deco. no." PD,i);
    laenge= strlen(cline);
    TextOut(hDC,360,330,cline,laenge);
  break;

  case TX_ITERA:
    sprintf(cline,PD " Iteration",i);
    laenge= strlen(cline);
    TextOut(hDC,10,370,cline,laenge);
  break;

  case TX_JACOOK:
    if(LANG == 1) sprintf(cline,"Residuenvektor < Eps, schaut gut aus!");
    if(LANG == 2) sprintf(cline,"Limit Eps reached, sounds good!");
    laenge= strlen(cline);
    TextOut(hDC,10,390,cline,laenge);
  break;

  case TX_JACONOTOK:
    if(LANG == 1) sprintf(cline,"Maxit erreicht, aber Eps nicht erreicht-leider!");
    if(LANG == 2) sprintf(cline,"Maxit reached but Eps not reached-sorry!");
    laenge= strlen(cline);
    TextOut(hDC,10,390,cline,laenge);
  break;

  case TX_WRIO2:
    if(LANG == 1) TextOut(hDC,10,410,"Z88O2.TXT beschreiben",21);
    if(LANG == 2) TextOut(hDC,10,410,"Writing Z88O2.TXT",18);
  break;

  case TX_SPANNU:
    TextOut(hDC,10,430,">>> Start Z88DR: Pass 4 <<<",27);
    if(LANG == 1 && isflag == 0) strcpy(cline,"Spannungen berechnen und schreiben, keine V-Spannungen");
    if(LANG == 2 && isflag == 0) strcpy(cline,"Computing and Writing Stresses, no reduced Stresses");
    if(LANG == 1 && isflag == 1) strcpy(cline,"Spannungen berechnen und schreiben, GEH V-Spannungen");
    if(LANG == 2 && isflag == 1) strcpy(cline,"Computing and Writing Stresses, v.Mises Stresses");
    if(LANG == 1 && isflag == 2) strcpy(cline,"Spannungen berechnen und schreiben, NH V-Spannungen");
    if(LANG == 2 && isflag == 2) strcpy(cline,"Computing and Writing Stresses, Principal Stresses");
    if(LANG == 1 && isflag == 3) strcpy(cline,"Spannungen berechnen und schreiben, SH V-Spannungen");
    if(LANG == 2 && isflag == 3) strcpy(cline,"Computing and Writing Stresses, Tresca Stresses");
    laenge= strlen(cline);
    TextOut(hDC,10,450,cline,laenge);
  break;

  case TX_KNOTENK:
    TextOut(hDC,10,490,">>> Start Z88ER: Pass 5 <<<",27);
    if(LANG == 1) TextOut(hDC,10,510,"Kraefte berechnen und schreiben :",33);
    if(LANG == 2) TextOut(hDC,10,510,"Computing & Writing Nodal Forces:",33);
  break;

  }

return(0);
}

/***********************************************************************
*  function wtya88j gibt Elementtypen in Z88A aus
***********************************************************************/ 
int wtya88j(FR_INT4 k,FR_INT4 i)
{
extern HDC hDC;
extern FR_INT4 LANG;

size_t laenge;

char cline[80];

if(LANG == 1) sprintf(cline,"Formatieren: Nr. " PD " Typ " PD,k,i);
if(LANG == 2) sprintf(cline,"formatting: no. " PD " type " PD,k,i);
laenge= strlen(cline);
TextOut(hDC,290,90,cline,laenge);

return(0);
}

/***********************************************************************
*  function wtyp88j gibt Elementtypen in Z88BR aus
***********************************************************************/ 
int wtyp88j(FR_INT4 k,FR_INT4 i)
{
extern HDC hDC;
extern FR_INT4 LANG;

size_t laenge;

char cline[80];

if(LANG == 1) sprintf(cline,"Compilation: Nr. " PD " Typ " PD,k,i);
if(LANG == 2) sprintf(cline,"compilation: no. " PD " type " PD,k,i);
laenge= strlen(cline);
TextOut(hDC,290,210,cline,laenge);

return(0);
}

/***********************************************************************
*  function wfor88i gibt kfoun beim Sortieren in Z88A1 aus
***********************************************************************/ 
int wfor88i(FR_INT4 k,FR_INT4 i)
{
extern HDC hDC;
extern FR_INT4 LANG;

size_t laenge;

char cline[80];

if(LANG == 1) sprintf(cline,"noch " PD9 " Schritte, Pointer IEZ = " PD9 "   ",k,i);
if(LANG == 2) sprintf(cline,"still " PD9 " steps, pointer IEZ = " PD9 "   ",k,i);
laenge= strlen(cline);
TextOut(hDC,10,150,cline,laenge);

return(0);
}

/***********************************************************************
*  function wran88j gibt Randbedingungen aus
***********************************************************************/ 
int wran88j(FR_INT4 k,FR_INT4 i)
{
extern HDC hDC;
extern FR_INT4 LANG;

size_t laenge;

char cline[80];

if(LANG == 1) sprintf(cline,"Randbedingung Nr. " PD " Typ " PD,k,i);
if(LANG == 2) sprintf(cline,"constraint no. " PD " type " PD,k,i);
laenge= strlen(cline);
TextOut(hDC,290,290,cline,laenge);

return(0);
}

/***********************************************************************
*  function wtyd88j gibt Elementtypen in Z88DR aus
***********************************************************************/ 
int wtyd88j(FR_INT4 k,FR_INT4 i)
{
extern HDC hDC;
extern FR_INT4 LANG;

size_t laenge;

char cline[80];


if(LANG == 1) sprintf(cline,"Element: Nr. " PD " Typ " PD,k,i);
if(LANG == 2) sprintf(cline,"element: no. " PD " type " PD,k,i);
laenge= strlen(cline);
laenge= strlen(cline);
TextOut(hDC,10,470,cline,laenge);

return(0);
}

/***********************************************************************
*  function wtye88j gibt Elementtypen in Z88ER aus
***********************************************************************/ 
int wtye88j(FR_INT4 k,FR_INT4 i)
{
extern HDC hDC;
extern FR_INT4 LANG;

size_t laenge;

char cline[80];


if(LANG == 1) sprintf(cline,"Element: Nr. " PD " Typ " PD,k,i);
if(LANG == 2) sprintf(cline,"element: no. " PD " type " PD,k,i);
laenge= strlen(cline);
laenge= strlen(cline);
TextOut(hDC,10,530,cline,laenge);

return(0);
}
