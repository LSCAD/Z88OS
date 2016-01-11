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
* wlog88g gibt Log-Datei-Meldungen aus (1 FR_INT4, 1 int)
* 29.7.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88g.h>
#include <stdio.h>   /* FILE,fprintf,fflush */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88g.h>
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
*  hier beginnt Function wlog88g
***********************************************************************/
int wlog88g(FR_INT4 i,int iatx)
{
extern FILE *fwlo;
extern FR_INT4 LANG;

switch(iatx)
  {
  case LOG_BZ88:
    if(LANG == 1) fprintf(fwlo,"Start Z88G Version 14OS");
    if(LANG == 2) fprintf(fwlo,"start Z88G version 14OS");
    fflush(fwlo);
  break;

  case LOG_OPENZ88DYN:
    if(LANG == 1) fprintf(fwlo,"\nOeffnen der Datei Z88.DYN");
    if(LANG == 2) fprintf(fwlo,"\nopening file Z88.DYN");
    fflush(fwlo);
  break;

  case LOG_NODYN:
    if(LANG == 1)
    fprintf(fwlo,"\n### kann Z88.DYN nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### cannot open Z88.DYN ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOCOS:
    if(LANG == 1)
    fprintf(fwlo,"\n### kann Z88G.COS nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### cannot open Z88G.COS ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NONAS:
    if(LANG == 1)
    fprintf(fwlo,"\n### kann Z88G.NAS nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### cannot open Z88G.NAS ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOIN:
    if(LANG == 1)
    fprintf(fwlo,"\n### kann Z88G.IN nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### cannot open Z88G.IN ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOI1:
    if(LANG == 1)
    fprintf(fwlo,"\n### kann Z88I1.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### cannot open Z88I1.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_NOI2:
    if(LANG == 1)
    fprintf(fwlo,"\n### kann Z88I2.TXT nicht oeffnen ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### cannot open Z88I2.TXT ..stop ###");
    fflush(fwlo);
  break;

  case LOG_ARRAYNOTOK:
    if(LANG == 1)
    fprintf(fwlo,"\n### Memory Kennung " PD " nicht o.k. ..Stop ###",i);
    if(LANG == 2)
    fprintf(fwlo,"\n### memory id " PD " is not o.k. ..stop ###",i);
    fflush(fwlo);
  break;

  case LOG_ARRAYOK:
    if(LANG == 1) fprintf(fwlo,"\nMemory Kennung " PD " angelegt",i);
    if(LANG == 2) fprintf(fwlo,"\nmemory id " PD " allocated",i);
    fflush(fwlo);
  break;

  case LOG_FILEF:
    if(i == 1)
      {
      if(LANG == 1) fprintf(fwlo,"\nCOSMOS-Datei gewaehlt");
      if(LANG == 2) fprintf(fwlo,"\nCOSMOS file chosen");
      fflush(fwlo);
      }
    if(i == 2)
      {
      if(LANG == 1) fprintf(fwlo,"\nNASTRAN-Datei gewaehlt");
      if(LANG == 2) fprintf(fwlo,"\nNASTRAN file chosen");
      fflush(fwlo);
      }
  break;

  case LOG_SHEIPLA:
    if(i == 1 || i == 5)
      {
      if(LANG == 1) fprintf(fwlo,"\nTetraederErzeugung");
      if(LANG == 2) fprintf(fwlo,"\ntetrahedron generation");
      fflush(fwlo);
      }
    if(i == 2)
      {
      if(LANG == 1) fprintf(fwlo,"\nScheiben-Erzeugung");
      if(LANG == 2) fprintf(fwlo,"\nplane stress element generation");
      fflush(fwlo);
      }
    if(i == 3)
      {
      if(LANG == 1) fprintf(fwlo,"\nPlatten-Erzeugung");
      if(LANG == 2) fprintf(fwlo,"\nplate element generation");
      fflush(fwlo);
      }
    if(i == 4)
      {
      if(LANG == 1) fprintf(fwlo,"\nTorus-Erzeugung");
      if(LANG == 2) fprintf(fwlo,"\ntorus element generation");
      fflush(fwlo);
      }
    if(i == 6)
      {
      if(LANG == 1) fprintf(fwlo,"\nSchalen-Erzeugung");
      if(LANG == 2) fprintf(fwlo,"\nshell element generation");
      fflush(fwlo);
      }
  break;

  case LOG_WRONGDYN:
    if(LANG == 1)
    fprintf(fwlo,"\n### File Z88.DYN ist nicht korrekt ..Stop ###");
    if(LANG == 2)
    fprintf(fwlo,"\n### file Z88.DYN is not correct ..stop ###");
    fflush(fwlo);
  break;

  case LOG_DIMDET:
    if(LANG == 1) fprintf(fwlo,"\n" PD "-D Struktur entdeckt",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD "-D structure detected",i);
    fflush(fwlo);
  break;

  case LOG_ISPC:
    if(LANG == 1) fprintf(fwlo,"\nLagerfall " PD " entdeckt",i);
    if(LANG == 2) fprintf(fwlo,"\nconstraint case " PD " detected",i);
    fflush(fwlo);
  break;

  case LOG_ILOAD:
    if(LANG == 1) fprintf(fwlo,"\nLastfall " PD " entdeckt",i);
    if(LANG == 2) fprintf(fwlo,"\nload case " PD " detected",i);
    fflush(fwlo);
  break;

  case LOG_NODDET:
    if(LANG == 1) fprintf(fwlo,"\n" PD " Knoten entdeckt",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD " nodes detected",i);
    fflush(fwlo);
  break;

  case LOG_ELEDET:
    if(LANG == 1) fprintf(fwlo,"\n" PD " Elemente entdeckt",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD " elements detected",i);
    fflush(fwlo);
  break;

  case LOG_CONDET:
    if(LANG == 1) fprintf(fwlo,"\n" PD " Randbedingungen entdeckt",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD " boundary conditions detected",i);
    fflush(fwlo);
  break;

  case LOG_PELDET:
    if(LANG == 1) fprintf(fwlo,"\n" PD " Elemente mit Drucklasten entdeckt",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD " elements with pressure loads detected",i);
    fflush(fwlo);
  break;

  case LOG_REAWRI:
    if(LANG == 1) fprintf(fwlo,"\nZ88G.COS/IN lesen und Z88I*.TXT schreiben");
    if(LANG == 2) fprintf(fwlo,"\nreading Z88G.COS/IN and writing Z88I*.TXT");
    fflush(fwlo);
  break;

  case LOG_NODDON:
    if(LANG == 1) fprintf(fwlo,"\n" PD " Knoten erledigt",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD " nodes done",i);
    fflush(fwlo);
  break;

  case LOG_ELEDON:
    if(LANG == 1) fprintf(fwlo,"\n" PD " Elemente erledigt",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD " elements done",i);
    fflush(fwlo);
  break;

  case LOG_CONDON:
    if(LANG == 1) fprintf(fwlo,
                  "\n" PD " Randbedingungen (=Lager und Kraefte) erledigt",i);
    if(LANG == 2) fprintf(fwlo,
                  "\n" PD " boundary conditions (=forces and constraints) done",i);
    fflush(fwlo);
  break;

  case LOG_16DET:
    if(LANG == 1) fprintf(fwlo,"\n" PD " Tetraeder Nr.16 (10 Knoten) entdeckt",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD " tetrahed. No.16 (10 nodes) detected",i);
    fflush(fwlo);
  break;

  case LOG_17DET:
    if(LANG == 1) fprintf(fwlo,"\n" PD " Tetraeder Nr.17 (4 Knoten) entdeckt",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD " tetrahed. No.17 (4 nodes) detected",i);
    fflush(fwlo);
  break;

  case LOG_7DET:
    if(LANG == 1) fprintf(fwlo,"\n" PD "Scheiben Nr.7 (8 Knoten) entdeckt",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD " plane stress No.7 (8 nodes) detected",i);
    fflush(fwlo);
  break;

  case LOG_14DET:
    if(LANG == 1) fprintf(fwlo,"\n" PD " Scheiben Nr.14 (6 Knoten) entdeckt",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD " plane stress No.14 (6 nodes) detected",i);
    fflush(fwlo);
  break;

  case LOG_18DET:
    if(LANG == 1) fprintf(fwlo,"\n" PD " Platten Nr.18 (6 Knoten) entdeckt",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD " plate No.18 (6 nodes) detected",i);
    fflush(fwlo);
  break;

  case LOG_20DET:
    if(LANG == 1) fprintf(fwlo,"\n" PD " Platten Nr.20 (8 Knoten) entdeckt",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD " plate No.20 (8 nodes) detected",i);
    fflush(fwlo);
  break;

  case LOG_8DET:
    if(LANG == 1) fprintf(fwlo,"\n" PD " Torus Nr.8 (8 Knoten) entdeckt",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD " torus No.8 (8 nodes) detected",i);
    fflush(fwlo);
  break;

  case LOG_15DET:
    if(LANG == 1) fprintf(fwlo,"\n" PD " Torus Nr.15 (6 Knoten) entdeckt",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD " torus No.15 (6 nodes) detected",i);
    fflush(fwlo);
  break;

  case LOG_23DET:
    if(LANG == 1) fprintf(fwlo,"\n" PD " Schalen Nr.23 (8 Knoten) entdeckt",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD " shell No.23 (8 nodes) detected",i);
    fflush(fwlo);
  break;

  case LOG_24DET:
    if(LANG == 1) fprintf(fwlo,"\n" PD " Schalen Nr.24 (6 Knoten) entdeckt",i);
    if(LANG == 2) fprintf(fwlo,"\n" PD " shell No.24 (6 nodes) detected",i);
    fflush(fwlo);
  break;

  case LOG_Z88CS:
    if(LANG == 1) fprintf(fwlo,"\nZ88-Daten berechnet und gespeichert");
    if(LANG == 2) fprintf(fwlo,"\nZ88 data computed and stored");
    fflush(fwlo);
  break;

  case LOG_Z88DONE:
    if(LANG == 1) fprintf(fwlo,"\nFiles geschlossen. Z88G fertig.");
    if(LANG == 2) fprintf(fwlo,"\nFiles closed. Z88G done.");
    fflush(fwlo);
  break;

  case LOG_NOACROBAT:
    if(LANG == 1) fprintf(fwlo,"\nPDF-Viewer konnte nicht gestartet werden");
    if(LANG == 2) fprintf(fwlo,"\ncould not launch PDF Viewer");
    fflush(fwlo);
  break;

  }
return(0);
}
