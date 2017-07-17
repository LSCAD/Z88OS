/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows
* and UNIX OS.
*
* Composed and edited and copyright by 
* Professor Dr.-Ing. Frank Rieg, University of Bayreuth, Germany
*
* eMail: 
* frank.rieg@uni-bayreuth.de
* dr.frank.rieg@t-online.de
* 
* V15.0 November 18, 2015
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
* wlog88r gibt Log-Datei-Meldungen aus (1 FR_INT4, 1 int)
* 2.12.2015 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>   /* FILE,fprintf,fflush */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <stdio.h>   /* FILE,fprintf,fflush */
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
*  hier beginnt Function wlog88r
***********************************************************************/
int wlog88r(FR_INT4 i,int iatx)
{
extern FILE *fwlo;
extern FR_INT4 LANG;

switch(iatx)
  {
  case LOG_BZ88R:
    if(LANG == 1) fprintf(fwlo,"Start Z88R Version 15OS");
    if(LANG == 2) fprintf(fwlo,"start Z88R version 15OS");
    fflush(fwlo);
  break;

  case LOG_OPENZ88DYN:
    if(LANG == 1) fprintf(fwlo,"\nOeffnen der Datei Z88.DYN");
    if(LANG == 2) fprintf(fwlo,"\nopening file Z88.DYN");
    fflush(fwlo);
  break;

  case LOG_NODYN:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88.DYN nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88.DYN ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOACROBAT:
    if(LANG == 1) fprintf(fwlo,"\n??? kann PDF-Viewer nicht oeffnen ???");
    if(LANG == 2) fprintf(fwlo,"\n??? cannot open PDF Viewer ???");
    fflush(fwlo);
  break;

  case LOG_WRONGDYN:
    if(LANG == 1) fprintf(fwlo,"\n### File Z88.DYN ist nicht korrekt ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### file Z88.DYN is not correct ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOMAN:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88MAN.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88MAN.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_WRONGMAN:
    if(LANG == 1) fprintf(fwlo,"\n### File Z88MAN.TXT ist nicht korrekt ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### file Z88MAN.TXT is not correct ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOELP:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88ELP.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88ELP.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOMAT:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88MAT.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88MAT.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOMATCSV:
    if(LANG == 1) fprintf(fwlo,"\n### kann *.CSV nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open *.CSV ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOINT:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88INT.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88INT.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_MAXKOI:
    fprintf(fwlo,"\nMAXKOI  = " PD,i);
    fflush(fwlo);
  break;

  case LOG_MAXIEZ:
    fprintf(fwlo,"\nMAXIEZ  = " PD,i);
    fflush(fwlo);
  break;

  case LOG_MAXGS:
    fprintf(fwlo,"\nMAXGS   = " PD,i);
    fflush(fwlo);
  break;

  case LOG_MAXK:
    fprintf(fwlo,"\nMAXK    = " PD,i);
    fflush(fwlo);
  break;

  case LOG_MAXE:
    fprintf(fwlo,"\nMAXE    = " PD,i);
    fflush(fwlo);
  break;

  case LOG_MAXNFG:
    fprintf(fwlo,"\nMAXNFG  = " PD,i);
    fflush(fwlo);
  break;

  case LOG_MAXMAT:
    fprintf(fwlo,"\nMAXMAT  = " PD,i);
    fflush(fwlo);
  break;

  case LOG_MAXPEL:
    fprintf(fwlo,"\nMAXPEL  = " PD,i);
    fflush(fwlo);
  break;

  case LOG_MAXINT:
    fprintf(fwlo,"\nMAXINT  = " PD,i);
    fflush(fwlo);
  break;

  case LOG_MAXESM:
    fprintf(fwlo,"\nMAXESM = " PD,i);
    fflush(fwlo);
  break;

  case LOG_MAXPR:
    fprintf(fwlo,"\nMAXPR = " PD,i);
    fflush(fwlo);
  break;

 case LOG_OKDYN:
    if(LANG == 1) fprintf(fwlo,"\nDatei Z88.DYN gelesen..scheint formal o.k. zu sein");
    if(LANG == 2) fprintf(fwlo,"\nfile Z88.DYN read ..seems to be o.k.");
    fflush(fwlo);
  break;

  case LOG_ALLOCMEMY:
    if(LANG == 1) fprintf(fwlo,"\nDynamisches Memory anlegen:");
    if(LANG == 2) fprintf(fwlo,"\nallocating dynamic memory:");
    fflush(fwlo);
  break;

  case LOG_ARRAYNOTOK:
    if(LANG == 1) fprintf(fwlo,"\n### Memory Kennung " PD " nicht o.k. ..Stop ###",i);
    if(LANG == 2) fprintf(fwlo,"\n### memory id " PD " is not o.k. ..stop ###",i);
    fflush(fwlo);
  break;

  case LOG_ARRAYOK:
    if(LANG == 1) fprintf(fwlo,"\nMemory Kennung " PD " angelegt",i);
    if(LANG == 2) fprintf(fwlo,"\nmemory id " PD " allocated",i);
    fflush(fwlo);
  break;

  case LOG_SUMMEMY:
    if(LANG == 1) fprintf(fwlo,"\nDynamisches Memory vollstaendig angefordert: " PD " MB",i);
    if(LANG == 2) fprintf(fwlo,"\ndynamic memory totally allocated: " PD " MB",i);
    fflush(fwlo);
  break;

  case LOG_EXITDYN88J:
    if(LANG == 1) fprintf(fwlo,"\nVerlassen Speichereinheit DYN88R");
    if(LANG == 2) fprintf(fwlo,"\nleaving storage function DYN88R");
    fflush(fwlo);
  break;

  case LOG_BRI188:
    if(LANG == 1) fprintf(fwlo,"\nStart Leseeinheit RI188I\nEinlesen von Z88I1.TXT");
    if(LANG == 2) fprintf(fwlo,"\nstart reading function RI188I\nreading Z88I1.TXT");
    fflush(fwlo);
  break;

  case LOG_NOI1:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88I1.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88I1.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_WRONGDIM:
    if(LANG == 1) fprintf(fwlo,"\n### Dimension " PD " falsch ..Stop ###",i);
    if(LANG == 2) fprintf(fwlo,"\n### dimension " PD " wrong ..stop ###",i);
    fflush(fwlo);
  break;

  case LOG_EXMAXK:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n### Nur " PD " Knoten in Z88.DYN definiert ..Stop ###",i);
      fprintf(fwlo,"\n### Abhilfe: MAXK in Z88.DYN erhoehen ###");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### only " PD " nodes in Z88.DYN defined ..stop ###",i);
      fprintf(fwlo,"\n### recover: increase MAXK in Z88.DYN ###");
      }
    fflush(fwlo);
  break;

  case LOG_EXMAXE:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n### Nur " PD " Elemente in Z88.DYN definiert ..Stop ###",i);
      fprintf(fwlo,"\n### Abhilfe: MAXE in Z88.DYN erhoehen ###");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### only " PD " elements in Z88.DYN defined ..stop ###",i);
      fprintf(fwlo,"\n### recover: increase MAXE in Z88.DYN ###");
      }
    fflush(fwlo);
  break;

  case LOG_EXMAXKOI:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n### Nur MAXKOI= " PD " in Z88.DYN definiert ..Stop ###",i);
      fprintf(fwlo,"\n### Abhilfe: MAXKOI in Z88.DYN erhoehen ###");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### only MAXKOI= " PD " in Z88.DYN defined ..stop ###",i);
      fprintf(fwlo,"\n### recover: increase MAXKOI in Z88.DYN ###");
      }
    fflush(fwlo);
  break;

  case LOG_EXMAXNFG:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n### Nur " PD " FG in Z88.DYN definiert ..Stop ###",i);
      fprintf(fwlo,"\n### Abhilfe: MAXNFG in Z88.DYN erhoehen ###");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### only " PD " DOF in Z88.DYN defined ..stop ###",i);
      fprintf(fwlo,"\n### recover: increase MAXNFG in Z88.DYN ###");
      }
    fflush(fwlo);
  break;

  case LOG_EXMAXIEZ:
    if(LANG == 1)
      {
      fprintf(fwlo,"\n### Pointer IEZ zu klein ..Stop         ###");
      fprintf(fwlo,"\n### Abhilfe: MAXIEZ in Z88.DYN erhoehen ###");
      }
    if(LANG == 2)
      {
      fprintf(fwlo,"\n### Pointer IEZ exhausted ..stop          ###");
      fprintf(fwlo,"\n### recover: increase MAXIEZ in Z88.DYN   ###");
      }
    fflush(fwlo);
  break;

  case LOG_WROKFLAG:
    if(LANG == 1) fprintf(fwlo,"\n### KFLAG " PD " falsch ..Stop ###",i);
    if(LANG == 2) fprintf(fwlo,"\n### KFLAG " PD " wrong ..stop ###",i);
    fflush(fwlo);
  break;

  case LOG_KOOR:
    if(LANG == 1) fprintf(fwlo,"\nEinlesen der Koordinaten");
    if(LANG == 2) fprintf(fwlo,"\nreading coordinates");
    fflush(fwlo);
  break;

  case LOG_KOIN:
    if(LANG == 1) fprintf(fwlo,"\nEinlesen der Koinzidenz");
    if(LANG == 2) fprintf(fwlo,"\nreading element information");
    fflush(fwlo);
  break;

  case LOG_EXITRI188:
    if(LANG == 1) fprintf(fwlo,"\nZ88I1.TXT eingelesen, Verlassen Leseeinheit RI188R");
    if(LANG == 2) fprintf(fwlo,"\nZ88I1.TXT read, leaving reading function RI188R");
    fflush(fwlo);
  break;

  case LOG_BWRIA88F:
    if(LANG == 1) fprintf(fwlo,"\nStart Schreibeinheit WRIA88R");
    if(LANG == 2) fprintf(fwlo,"\nstart writing function WRIA88R");
    fflush(fwlo);
  break;

  case LOG_NOO0:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88O0.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88O0.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOO1:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88O1.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88O1.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_WRIO0:
    if(LANG == 1) fprintf(fwlo,"\nBeschreiben von Z88O0.TXT");
    if(LANG == 2) fprintf(fwlo,"\nwriting Z88O0.TXT");
    fflush(fwlo);
  break;

  case LOG_WRIO1:
    if(LANG == 1) fprintf(fwlo,"\nBeschreiben von Z88O1.TXT");
    if(LANG == 2) fprintf(fwlo,"\nwriting Z88O1.TXT");
    fflush(fwlo);
  break;

  case LOG_GSERF:
    if(LANG == 1) fprintf(fwlo,"\nVektor GS braucht " PD " Elemente",i);
    if(LANG == 2) fprintf(fwlo,"\nvector GS needs " PD " Elemente",i);
    fflush(fwlo);
  break;

  case LOG_KOIERF:
    if(LANG == 1) fprintf(fwlo,"\nVektor KOI braucht " PD " Elemente",i);
    if(LANG == 2) fprintf(fwlo,"\nvector KOI needs " PD " Elemente",i);
    fflush(fwlo);
  break;

  case LOG_EXITWRIA88F:
    if(LANG == 1) fprintf(fwlo,"\nVerlassen Schreibeinheit WRIA88R");
    if(LANG == 2) fprintf(fwlo,"\nleaving writing function WRIA88R");
    fflush(fwlo);
  break;

  case LOG_Z88A:
    if(LANG == 1) fprintf(fwlo,"\nStart Z88A");
    if(LANG == 2) fprintf(fwlo,"\nstart Z88A");
    fflush(fwlo);
  break;

  case LOG_Z88AI:
    if(LANG == 1) fprintf(fwlo,"\nStart Z88AI");
    if(LANG == 2) fprintf(fwlo,"\nstart Z88AI");
    fflush(fwlo);
  break;

  case LOG_WROETYP:
    if(LANG == 1) fprintf(fwlo,"\n### Falschen Elementtyp " PD " entdeckt ..Stop ###",i);
    if(LANG == 2) fprintf(fwlo,"\n### wrong element type " PD " detected ..stop ###",i);
    fflush(fwlo);
  break;

  case LOG_EXITZ88A:
    if(LANG == 1) fprintf(fwlo,"\nVerlassen Z88A");
    if(LANG == 2) fprintf(fwlo,"\nleaving Z88A");
    fflush(fwlo);
  break;

  case LOG_EXITZ88AI:
    if(LANG == 1) fprintf(fwlo,"\nVerlassen Z88AI");
    if(LANG == 2) fprintf(fwlo,"\nleaving Z88AI");
    fflush(fwlo);
  break;

  case LOG_CFLAG0:
    fprintf(fwlo,"\nSolver Cholesky, ICFLAG = " PD,i);
    fflush(fwlo);
  break;

  case LOG_CFLAG1:
    fprintf(fwlo,"\nSolver SICCG, ICFLAG = " PD,i);
    fflush(fwlo);
  break;

  case LOG_CFLAG2:
    fprintf(fwlo,"\nSolver SORCG, ICFLAG = " PD,i);
    fflush(fwlo);
  break;

  case LOG_Z88B:
    if(LANG == 1) fprintf(fwlo,"\nStart Z88BR");
    if(LANG == 2) fprintf(fwlo,"\nstart Z88BR");
    fflush(fwlo);
  break;

  case LOG_EXGS:
    if(LANG == 1) fprintf(fwlo,
"\n### IP = " PD ",.. ueberschreitet MAXGS ###\
\n### Struktur zu gross fuer Z88 ..Stop       ###\
\n### Abhilfe: MAXGS hoeher setzen in Z88.DYN ###",i);
    if(LANG == 2) fprintf(fwlo,
"\n### IP = " PD ",.. exceeds MAXGS ###\
\n### system of equations too large ..stop ###\
\n### recover: increase MAXGS in Z88.DYN   ###",i);
    fflush(fwlo);
  break;

  case LOG_EXKOI:
    if(LANG == 1) fprintf(fwlo,
"\n### NKOI = " PD ",.. ueberschreitet MAXKOI ###\
\n### Struktur zu gross fuer Z88 ..Stop       ###\
\n### Abhilfe: MAXKOI hoeher setzen in Z88.DYN ###",i);
    if(LANG == 2) fprintf(fwlo,
"\n### NKOI = " PD ",.. exceeds MAXKOI ###\
\n### system of equations too large ..stop ###\
\n### recover: increase MAXKOI in Z88.DYN  ###",i);
    fflush(fwlo);
  break;

  case LOG_EXMAXPR:
    if(LANG == 1) fprintf(fwlo,
"\n### NKOI = " PD ",.. ueberschreitet MAXPR ###\
\n### Lastvektor zu gross fuer Z88 ..Stop       ###\
\n### Abhilfe: MAXPR hoeher setzen in Z88.DYN ###",i);
    if(LANG == 2) fprintf(fwlo,
"\n### NKOI = " PD ",.. exceeds MAXPR ###\
\n### load vektor too large ..stop ###\
\n### recover: increase MAXPR in Z88.DYN  ###",i);
    fflush(fwlo);
  break;

  case LOG_COMPI:
    if(LANG == 1) fprintf(fwlo,"\n*** Compilation ***");
    if(LANG == 2) fprintf(fwlo,"\n*** compilation ***");
    fflush(fwlo);
  break;

  case LOG_EXITZ88B:
    if(LANG == 1) fprintf(fwlo,"\nVerlassen Z88BR");
    if(LANG == 2) fprintf(fwlo,"\nleaving Z88BR");
    fflush(fwlo);
  break;

  case LOG_Z88CC:
    if(LANG == 1) fprintf(fwlo,"\nStart Z88CR");
    if(LANG == 2) fprintf(fwlo,"\nstart Z88CR");
    fflush(fwlo);
  break;

  case LOG_NOI2:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88I2.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88I2.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOI5:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88I5.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88I5.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOO2:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88O2.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88O2.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOO3:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88O3.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88O3.TXT ..stop ###");
    fflush(fwlo);
  break;



  case LOG_REAI2:
    if(LANG == 1) fprintf(fwlo,"\nEinlesen Z88I2.TXT");
    if(LANG == 2) fprintf(fwlo,"\nreading Z88I2.TXT");
    fflush(fwlo);
  break;

  case LOG_BRI588:
    if(LANG == 1) fprintf(fwlo,"\nEinlesen von Z88I5.TXT");
    if(LANG == 2) fprintf(fwlo,"\nreading Z88I5.TXT");
    fflush(fwlo);
  break;

  case LOG_EXITRI588:
    if(LANG == 1) fprintf(fwlo,"\nZ88I5.TXT fertig eingelesen");
    if(LANG == 2) fprintf(fwlo,"\nZ88I5.TXT totally read");
    fflush(fwlo);
  break;

  case LOG_MAXIT:
    fprintf(fwlo,"\nMAXIT  = " PD,i);
    fflush(fwlo);
  break;

  case LOG_ERBPA:
    if(LANG == 1) fprintf(fwlo,"\nEinarbeiten der Randbedingungen Pass " PD,i);
    if(LANG == 2) fprintf(fwlo,"\nincorporating constraints pass " PD,i);
    fflush(fwlo);
  break;

  case LOG_SCAL88:
    if(LANG == 1) fprintf(fwlo,"\nStart SCAL88");
    if(LANG == 2) fprintf(fwlo,"\nstart SCAL88");
    fflush(fwlo);
  break;

  case LOG_CHOY88:
    if(LANG == 1) fprintf(fwlo,"\nStart CHOY88");
    if(LANG == 2) fprintf(fwlo,"\nstart CHOY88");
    fflush(fwlo);
  break;

  case LOG_SICCG88:
    if(LANG == 1) fprintf(fwlo,"\nStart SICCG88");
    if(LANG == 2) fprintf(fwlo,"\nstart SICCG88");
    fflush(fwlo);
  break;

  case LOG_SORCG88:
    if(LANG == 1) fprintf(fwlo,"\nStart SORCG88");
    if(LANG == 2) fprintf(fwlo,"\nstart SORCG88");
    fflush(fwlo);
  break;

  case LOG_WRIO2:
    if(LANG == 1) fprintf(fwlo,"\nBeschreiben von Z88O2.TXT");
    if(LANG == 2) fprintf(fwlo,"\nwriting Z88O2.TXT");
    fflush(fwlo);
  break;

  case LOG_ITERA:
    if(LANG == 1) fprintf(fwlo,"\n " PD " Iterationen ausgefuehrt",i);
    if(LANG == 2) fprintf(fwlo,"\n " PD " iterations done",i);
    fflush(fwlo);
  break;

  case LOG_EXITZ88CC:
    if(LANG == 1) fprintf(fwlo,"\nVerlassen Z88CR");
    if(LANG == 2) fprintf(fwlo,"\nleaving Z88CR");
    fflush(fwlo);
  break;

  case LOG_DIAGNULL:
    if(LANG == 1) 
      {
      fprintf(fwlo,"\n### Diagonalelement " PD " Null oder negativ ..Stop ###",i);
      fprintf(fwlo,"\n### liegt oft an fehlenden oder falschen Randbedingungen ###");
      fprintf(fwlo,"\n### Abhilfe: Randbedingungen pruefen (statisch unterbestimmt ?) ###");
      }    
    if(LANG == 2) 
      {
      fprintf(fwlo,"\n### diagonal element " PD " zero or negative ..stop ###",i);
      fprintf(fwlo,"\n### often caused by missing or wrong constraints ###");
      fprintf(fwlo,"\n### recover: check constraints (underdefined ?)  ###");
      }
    fflush(fwlo);
  break;

  case LOG_JACNEG:
    if(LANG == 1) 
      {
      fprintf(fwlo, "\n### Element " PD " ###",i);
      fprintf(fwlo, "\n### Jacobi- Determinante Null oder negativ ..Stop            ###");
      fprintf(fwlo, "\n### Elementnumerierung falsch, nicht mathematisch positiv    ###");
      fprintf(fwlo, "\n### Abhilfe: Siehe Online Hilfe oder Handbuch zum Elementtyp ###");
      }    
    if(LANG == 2) 
      {
      fprintf(fwlo,"\n### Element " PD " ###",i);
      fprintf(fwlo,"\n### Jacobi determinant zero or negative ..stop     ###");
      fprintf(fwlo,"\n### element numbering wrong, not counter-clockwise ###");
      fprintf(fwlo,"\n### Recover:renumber wrong elements(consult manual)###");
      }
    fflush(fwlo);
  break;

  case LOG_JACLOA:
    if(LANG == 1) 
      {
      fprintf(fwlo,"\n### Lastvektor " PD " ###",i);
      fprintf(fwlo,"\n### Jacobi- Determinante Null oder negativ ..Stop            ###");
      fprintf(fwlo,"\n### Elementnumerierung falsch, nicht mathematisch positiv    ###");
      fprintf(fwlo,"\n### Abhilfe: Siehe Online Hilfe oder Handbuch zum Elementtyp ###");
      }    
    if(LANG == 2) 
      {
      fprintf(fwlo,"\n### Load vector " PD " ###",i);
      fprintf(fwlo,"\n### Jacobi determinant zero or negative ..stop     ###");
      fprintf(fwlo,"\n### element numbering wrong, not counter-clockwise ###");
      fprintf(fwlo,"\n### Recover:renumber wrong elements(consult manual)###");
      }
    fflush(fwlo);
  break;

  case LOG_BZ88D:
    if(LANG == 1) fprintf(fwlo,"Start Z88DR Version 15OS");
    if(LANG == 2) fprintf(fwlo,"start Z88DR version 15OS");
    fflush(fwlo);
  break;

  case LOG_NOO5:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88O5.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88O5.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOO8:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88O8.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88O8.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_SPANNU:
    if(LANG == 1) fprintf(fwlo,"\nSpannungen berechnen");
    if(LANG == 2) fprintf(fwlo,"\ncomputing stresses");
    fflush(fwlo);
  break;

  case LOG_NOCI:
    if(LANG == 1) fprintf(fwlo,"\nKonnte nicht alle GEH/NH/SH-Vergleichsspannungen berechnen");
    if(LANG == 2) fprintf(fwlo,"\ncould not compute all Mises/principal/Tresca stresses");
    fflush(fwlo);
  break;

  case LOG_EXITZ88D:
    if(LANG == 1) fprintf(fwlo,"\nEnde Z88DR");
    if(LANG == 2) fprintf(fwlo,"\nZ88DR done");
    fflush(fwlo);
  break;

  case LOG_BZ88E:
    if(LANG == 1) fprintf(fwlo,"Start Z88ER Version 15OS");
    if(LANG == 2) fprintf(fwlo,"start Z88ER version 15OS");
    fflush(fwlo);
  break;

  case LOG_NOO4:
    if(LANG == 1) fprintf(fwlo,"\n### kann Z88O4.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2) fprintf(fwlo,"\n### cannot open Z88O4.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_KNOTENK:
    if(LANG == 1) fprintf(fwlo,"\nKnotenkraefte berechnen");
    if(LANG == 2) fprintf(fwlo,"\ncomputing nodal forces");
    fflush(fwlo);
  break;

  case LOG_EXITZ88E:
    if(LANG == 1) fprintf(fwlo,"\nEnde Z88ER");
    if(LANG == 2) fprintf(fwlo,"\nZ88ER done");
    fflush(fwlo);
  break;

  }
return(0);
}
