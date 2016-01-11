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
* wrim88g gibt Texte aus (1 FR_INT4)
* 30.7.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88g.h>
#include <stdio.h>    /* printf */
#endif

/***********************************************************************
* Formatbeschreiber
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
*  hier beginnt Function wrim88g
***********************************************************************/
int wrim88g(FR_INT4 i,int iatx)
{
extern FR_INT4 LANG;

switch(iatx)
  {
  case TX_COSOPEN:
    if(LANG == 1) printf("COSMOS-Datei Z88G.COS geoeffnet\n");
    if(LANG == 2) printf("COSMOS file Z88G.COS opened\n");
  break;

  case TX_NASOPEN:
    if(LANG == 1) printf("NASTRAN-Datei Z88G.NAS geoeffnet\n");
    if(LANG == 2) printf("NASTRAN file Z88G.NAS opened\n");
  break;

  case TX_INOPEN:
    if(LANG == 1) printf("Zwischendatei Z88G.IN geoeffnet\n");
    if(LANG == 2) printf("Buffer file Z88G.IN opened\n");
  break;

  case TX_I1OPEN:
    if(LANG == 1) printf("Z88I1.TXT geoeffnet\n");
    if(LANG == 2) printf("Z88I1.TXT opened\n");
  break;

  case TX_I2OPEN:
    if(LANG == 1) printf("Z88I2.TXT geoeffnet\n");
    if(LANG == 2) printf("Z88I2.TXT opened\n");
  break;

  case TX_COSNAS:
    if(LANG == 1) 
      {
      printf("Welche Datei soll eingelesen werden ?\n");
      printf("1   COSMOS- Datei Z88G.COS\n");
      printf("2   NASTRAN-Datei Z88G.NAS\n");
      printf("Ihre Wahl: ");
      }
    if(LANG == 2)
      {
      printf("Open what file ?\n");
      printf("1   COSMOS  file Z88G.COS\n");
      printf("2   NASTRAN file Z88G.NAS\n");
      printf("Your choice: ");
      }
  break;

  case TX_CHOICOS:
    if(LANG == 1) 
      {
      printf("Welche Elemente sollen erzeugt werden ?\n");
      printf("1   Tetraeder mit Kraeften (keine Druecke)\n");
      printf("2   Scheibenelemente\n");
      printf("3   Plattenelemente\n");
      printf("4   Axialsymmetrische Elemente\n");
      printf("Ihre Wahl: ");
      }
    if(LANG == 2)
      {
      printf("Type of elements to be generated ?\n");
      printf("1   Tetrahedrons with forces (no pressure loads)\n");
      printf("2   Plane stress elements\n");
      printf("3   Plate elements\n");
      printf("4   Axisymmetric elements\n");
      printf("Your choice: ");
      }
  break;

  case TX_CHOINAS:
    if(LANG == 1) 
      {
      printf("Welche Elemente sollen erzeugt werden ?\n");
      printf("2   Scheibenelemente\n");
      printf("3   Plattenelemente\n");
      printf("4   Axialsymmetrische Elemente\n");
      printf("5   Tetraeder mit Kraeften und/oder Druecken\n");
      printf("6   Schalenelemente\n");
      printf("Ihre Wahl: ");
      }
    if(LANG == 2)
      {
      printf("Type of elements to be generated ?\n");
      printf("2   Plane stress elements\n");
      printf("3   Plate elements\n");
      printf("4   Axisymmetric elements\n");
      printf("5   Tetrahedrons with pressure loads and/or forces\n");
      printf("6   Shell elements\n");
      printf("Your choice: ");
      }
  break;

  case TX_FILEF:
    if(i == 1)
      {
      if(LANG == 1) printf("COSMOS-Datei gewaehlt\n");
      if(LANG == 2) printf("COSMOS file chosen\n");
      }
    if(i == 2)
      {
      if(LANG == 1) printf("NASTRAN-Datei gewaehlt\n");
      if(LANG == 2) printf("NASTRAN file chosen\n");
      }
  break;


  case TX_SHEIPLA:
    if(i == 1 || i == 5)
      {
      if(LANG == 1) printf("Tetraeder-Erzeugung\n");
      if(LANG == 2) printf("Tetrahedron generation\n");
      }
    if(i == 2)
      {
      if(LANG == 1) printf("Scheiben-Erzeugung\n");
      if(LANG == 2) printf("Plane stress element generation\n");
      }
    if(i == 3)
      {
      if(LANG == 1) printf("Platten-Erzeugung\n");
      if(LANG == 2) printf("Plate element generation\n");
      }
    if(i == 4)
      {
      if(LANG == 1) printf("Torus-Erzeugung\n");
      if(LANG == 2) printf("axisym. element generation\n");
      }
    if(i == 6)
      {
      if(LANG == 1) printf("Schalen-Erzeugung\n");
      if(LANG == 2) printf("Shell element generation\n");
      }
  break;

  case TX_DIMDET:
    if(LANG == 1) printf(PD "-D Struktur entdeckt\n",i);
    if(LANG == 2) printf(PD "-D structure detected\n",i);
  break;

  case TX_ISPC:
    if(LANG == 1) printf("Lagerfall " PD " entdeckt\n",i);
    if(LANG == 2) printf("constraint case " PD " detected\n",i);
  break;

  case TX_ILOAD:
    if(LANG == 1) printf("Lastfall " PD " entdeckt\n",i);
    if(LANG == 2) printf("load case " PD " detected\n",i);
  break;

  case TX_NODDET:
    if(LANG == 1) printf(PD " Knoten entdeckt\n",i);
    if(LANG == 2) printf(PD " nodes detected\n",i);
  break;

  case TX_ELEDET:
    if(LANG == 1) printf(PD " Elemente entdeckt\n",i);
    if(LANG == 2) printf(PD " elements detected\n",i);
  break;

  case TX_CONDET:
    if(LANG == 1) printf(PD " Randbedingungen entdeckt\n",i);
    if(LANG == 2) printf(PD " boundary conditions detected\n",i);
  break;

  case TX_PELDET:
    if(LANG == 1) printf(PD " Elemente mit Drucklasten entdeckt\n",i);
    if(LANG == 2) printf(PD " elements with pressure loads detected\n",i);
  break;

  case TX_REAWRI:
    if(LANG == 1) printf("Z88G.COS/IN lesen und Z88I*.TXT schreiben ...\n");
    if(LANG == 2) printf("reading Z88G.COS/IN and writing Z88I*.TXT ...\n");
  break;

  case TX_NODDON:
    if(LANG == 1) printf(PD " Knoten erledigt\n",i);
    if(LANG == 2) printf(PD " nodes done\n",i);
  break;

  case TX_ELEDON:
    if(LANG == 1) printf(PD " Elemente erledigt\n",i);
    if(LANG == 2) printf(PD " elements done\n",i);
  break;

  case TX_CONDON:
    if(LANG == 1) printf(PD " Randbedingungen erledigt\n",i);
    if(LANG == 2) printf(PD " boundary conditions done\n",i);
  break;

  case TX_16DET:
    if(LANG == 1) printf(PD " Tetraeder Nr.16 (10 Knoten) entdeckt\n",i);
    if(LANG == 2) printf(PD " tetrahedrons No.16 (10 nodes) detected\n",i);
  break;

  case TX_17DET:
    if(LANG == 1) printf(PD " Tetraeder Nr.17 (4 Knoten) entdeckt\n",i);
    if(LANG == 2) printf(PD " tetrahedrons No.17 (4 nodes) detected\n",i);
  break;

  case TX_7DET:
    if(LANG == 1) printf(PD " Scheiben Nr.7 (8 Knoten) entdeckt\n",i);
    if(LANG == 2) printf(PD " plane stress ele. No.7 (8 nodes) detected\n",i);
  break;

  case TX_14DET:
    if(LANG == 1) printf(PD " Scheiben Nr.14 (6 Knoten) entdeckt\n",i);
    if(LANG == 2) printf(PD " plane stress ele. No.14 (6 nodes) detected\n",i);
  break;

  case TX_18DET:
    if(LANG == 1) printf(PD " Platten Nr.18 (6 Knoten) entdeckt\n",i);
    if(LANG == 2) printf(PD " plate ele. No.18 (6 nodes) detected\n",i);
  break;

  case TX_20DET:
    if(LANG == 1) printf(PD " Platten Nr.20 (8 Knoten) entdeckt\n",i);
    if(LANG == 2) printf(PD " plate ele. No.20 (8 nodes) detected\n",i);
  break;

  case TX_8DET:
    if(LANG == 1) printf(PD " Tori Nr.8 (8 Knoten) entdeckt\n",i);
    if(LANG == 2) printf(PD " torus ele. No.8 (8 nodes) detected\n",i);
  break;

  case TX_15DET:
    if(LANG == 1) printf(PD " Torus Nr.15 (6 Knoten) entdeckt\n",i);
    if(LANG == 2) printf(PD " torus ele. No.15 (6 nodes) detected\n",i);
  break;

  case TX_23DET:
    if(LANG == 1) printf(PD " Schalen Nr.23 (8 Knoten) entdeckt\n",i);
    if(LANG == 2) printf(PD " shell ele. No.23 (8 nodes) detected\n",i);
  break;

  case TX_24DET:
    if(LANG == 1) printf(PD " Schalen Nr.24 (6 Knoten) entdeckt\n",i);
    if(LANG == 2) printf(PD " shell ele. No.24 (6 nodes) detected\n",i);
  break;

  case TX_Z88CS:
    if(LANG == 1) printf("Z88-Daten berechnet und gespeichert\n");
    if(LANG == 2) printf("Z88 data computed and stored\n");
  break;

  case TX_Z88DONE:
    if(LANG == 1) printf("Alle Dateien geschlossen. Z88G fertig.\n");
    if(LANG == 2) printf("All files closed. Z88G done\n");
  break;
  }
return(0);
}

