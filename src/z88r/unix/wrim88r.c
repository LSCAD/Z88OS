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
* Diese Compilerunit umfasst:
* wrim88j gibt Texte aus (1 FR_INT4)
* wtyp88j gibt Elementtypen aus (1 FR_INT4, 1 FR_INT4)
* wtya88j gibt Elementtypen aus (1 FR_INT4, 1 FR_INT4)   Z88A
* wtyd88j gibt Elementtypen aus (1 FR_INT4, 1 FR_INT4)   Z88DR
* wtye88j gibt Elementtypen aus (1 FR_INT4, 1 FR_INT4)   Z88ER
* wfor88i gibt kfoun beim Sortieren aus (1 FR_INT4, 1 FR_INT4)
* wran88i gibt Randbedingungen aus (1 FR_INT4, 1 FR_INT4)
* 25.7.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>    /* printf */
#endif

/***********************************************************************
* Formate
***********************************************************************/
#ifdef FR_XINT
#define PD "%d"
#define PD9 "%9d"
#define P5D "%5d"
#endif

#ifdef FR_XLONG
#define PD "%ld"
#define PD9 "%9ld"
#define P5D "%5ld"
#endif

#ifdef FR_XLOLO
#define PD "%lld"
#define PD9 "%9lld"
#define P5D "%5lld"
#endif

/***********************************************************************
*  hier beginnt Function wrim88r
***********************************************************************/
int wrim88r(FR_INT4 i,int iatx)
{
extern FR_INT4 LANG,isflag;

switch(iatx)
  {
  case TX_IFNILI0:
    if(LANG == 1) printf("*** lineare Berechnung ***\n");
    if(LANG == 2) printf("*** computing linear structure ***\n");
  break;

  case TX_IFNILI9:
    if(LANG == 1) printf("*** Testmode ***\n");
    if(LANG == 2) printf("*** test mode ***\n");
  break;

  case TX_ICFLAG0:
    if(LANG == 1) printf("*** Cholesky-Solver mit Jennings-Speicherung ***\n");
    if(LANG == 2) printf("*** Cholesky solver with Jennings storing ***\n");
  break;

  case TX_ICFLAG1:
    if(LANG == 1) printf("*** SICCG-Solver mit Sparsematrix-Speicherung ***\n");
    if(LANG == 2) printf("*** SICCG solver with sparse matrix storing ***\n");
  break;

  case TX_ICFLAG2:
    if(LANG == 1) printf("*** SORCG-Solver mit Sparsematrix-Speicherung ***\n");
    if(LANG == 2) printf("*** SORCG solver with sparse matrix storing ***\n");
  break;

  case TX_CR:
    printf("\n");
  break;

  case TX_ITERA:
    printf("\r" PD ". Iteration",i);
    fflush(stdout);
  break;  
 
  case TX_CHOJ:
    printf("\r" PD,i);
  break;

  case TX_VORW:
    if(LANG == 1) printf("\nVorwaertseinsetzen\n");
    if(LANG == 2) printf("\nforward-substitution\n");
  break;

  case TX_RUECKW:
    if(LANG == 1) printf("Rueckwaertseinsetzen\n");
    if(LANG == 2) printf("back-substitution\n");
  break;

  case TX_ELE:
    if(LANG == 1) printf("\rElement " PD,i);
    if(LANG == 2) printf("\relement " PD,i);
  break;

  case TX_NFG:
    if(LANG == 1) printf(PD " x " PD " = Groesse Gleichungsystem \n",i,i);
    if(LANG == 2) printf(PD " x " PD " = size of system of equations\n",i,i);
  break;

  case TX_SUMMEMY:
    if(LANG == 1) printf("Programm hat " PD " MB fix angefordert\n", i);
    if(LANG == 2) printf("program allocated " PD " MB memory\n",i);
  break;

  case TX_DYNMEMY:
    if(LANG == 1) printf("\nProgramm hat " PD " MB dynamischen Speicher angefordert\n", i);
    if(LANG == 2) printf("\nprogram allocated " PD " MB dynamic memory\n",i);
  break;

  case TX_REAI1:
    if(LANG == 1) printf("Einlesen der Strukturdaten Z88I1.TXT\n");
    if(LANG == 2) printf("reading structure data file Z88I1.TXT\n");
  break;

  case TX_REAI2:
    if(LANG == 1) printf("Einlesen von Randbedingungsfile Z88I2.TXT\n");
    if(LANG == 2) printf("reading constraint file Z88I2.TXT\n");
  break;

  case TX_REAI5:
    if(LANG == 1) printf ("\n***** Lastvektoren berechnen *****");
    if(LANG == 2) printf ("\n***** computing load vectors *****");
  break;

  case TX_REAINT:
    if(LANG == 1) printf("Einlesen der Integrationsordnungen Z88INT.TXT\n");
    if(LANG == 2) printf("reading integration order data file Z88INT.TXT\n");
  break;

  case TX_REAELP:
    if(LANG == 1) printf("Einlesen der Elementparameter Z88ELP.TXT\n");
    if(LANG == 2) printf("reading element parameters data file Z88ELP.TXT\n");
  break;

  case TX_REAMAT:
    if(LANG == 1) printf("Einlesen der Materialgesetze Z88MAT.TXT\n");
    if(LANG == 2) printf("reading material data file Z88MAT.TXT\n");
  break;

  case TX_REAMAN:
    if(LANG == 1) printf("Einlesen der Solversteuerdatei Z88MAN.TXT\n");
    if(LANG == 2) printf("reading solver data file Z88MAN.TXT\n");
  break;

  case TX_KOOR:
    if(LANG == 1) printf("Koordinaten einlesen\n");
    if(LANG == 2) printf("reading coordinates\n");
  break;

  case TX_POLAR:
    if(LANG == 1) printf("Polar/Zylinder-Koordinaten umrechnen\n");
    if(LANG == 2) printf("converting polar/cylinder coordinates\n");
  break;

  case TX_KOIN:
    if(LANG == 1) printf("Koinzidenz einlesen\n");
    if(LANG == 2) printf("reading element informations\n");
  break;

  case TX_EGES:
    if(LANG == 1) printf("Elastizitaetsgesetze einlesen\n");
    if(LANG == 2) printf("reading material informations\n");
  break;

  case TX_Z88A:
    if(LANG == 1) printf(">>> Start Z88A <<<\n");
    if(LANG == 2) printf(">>> start Z88A <<<\n");
  break;

  case TX_Z88AI:
    if(LANG == 1) printf(">>> Start Z88AI <<<\n");
    if(LANG == 2) printf(">>> start Z88AI <<<\n");
  break;

  case TX_EXITZ88A:
    if(LANG == 1) printf(">>> Ende Z88A <<<\n");
    if(LANG == 2) printf(">>> Z88A finished <<<\n");
  break;

  case TX_EXITZ88AI:
    if(LANG == 1) printf(">>> Ende Z88AI <<<\n");
    if(LANG == 2) printf(">>> Z88AI finished <<<\n");
  break;

  case TX_NONZ:
    if(LANG == 1) printf("\n" PD " Elemente in IJ entdeckt\n", i);
    if(LANG == 2) printf("\n" PD " elements in IJ detected\n",i);
  break;

  case TX_GSSO:
    if(LANG == 1) printf(">>> alle Pointer assembliert <<<\n");
    if(LANG == 2) printf(">>> pointers assembled <<<\n");
  break;

  case TX_Z88B:
    if(LANG == 1) printf(">>> Start Z88BR <<<\n");
    if(LANG == 2) printf(">>> start Z88BR <<<\n");
  break;

  case TX_FORMA:
    if(LANG == 1) printf("***** Formatieren *****\n");
    if(LANG == 2) printf("***** formatting *****\n");
  break;

  case TX_WRIO0:
    if(LANG == 1) printf("Z88O0.TXT beschreiben\n");
    if(LANG == 2) printf("writing Z88O0.TXT\n");
  break;

  case TX_WRIO1:
    if(LANG == 1) printf("Z88O1.TXT beschreiben\n");
    if(LANG == 2) printf("writing Z88O1.TXT\n");
  break;

  case TX_GSERF:
    if(LANG == 1) printf("Vektor GS erfordert " PD " Elemente\n",i);
    if(LANG == 2) printf("vector GS needs " PD " elements\n",i);
  break;

  case TX_KOIERF:
    if(LANG == 1) printf("Vektor KOI erfordert " PD " Elemente\n",i);
    if(LANG == 2) printf("vector KOI needs " PD " elements\n",i);
  break;

  case TX_COMPI:
    if(LANG == 1) printf("***** Compilation *****\n");
    if(LANG == 2) printf("***** compilation *****\n");
  break;

  case TX_Z88CC:
    if(LANG == 1) printf("\n>>> Start Z88CR <<<\n");
    if(LANG == 2) printf("\n>>> start Z88CR <<<\n");
  break;

  case TX_ERBPA:
    if(LANG == 1) printf("Einarbeiten der Randbedingungen Pass " PD "\n",i);
    if(LANG == 2) printf("incorporating constraints pass " PD "\n",i);
  break;

  case TX_SCAL88:
    if(LANG == 1) printf("Start SCAL88\n");
    if(LANG == 2) printf("start SCAL88\n");
  break;

  case TX_PART88:
    if(LANG == 1) printf("\rpartielle Cholesky-Zerlegung Nr." PD,i);
    if(LANG == 2) printf("\rincomplete Cholesky decomposition no." PD,i);
    fflush(stdout);
  break;

  case TX_CHOY88:
    if(LANG == 1) printf("***** Start des Cholesky Solvers CHOY88 *****\n");
    if(LANG == 2) printf("***** start of Cholesky solver CHOY88 *****\n");
  break;

  case TX_SICCG88:
    if(LANG == 1) printf("***** Start des SICCG88 Solvers *****\n");
    if(LANG == 2) printf("***** start of solver SICCG88 *****\n");
  break;

  case TX_SORCG88:
    if(LANG == 1) printf("***** Start des SORCG88 Solvers *****\n");
    if(LANG == 2) printf("***** start of solver SORCG88 *****\n");
  break;

  case TX_JACOOK:
    if(LANG == 1) printf("\nResiduenvektor < Eps, alles okay!\n");
    if(LANG == 2) printf("\nlimit Eps reached, sounds good!\n");
  break;

  case TX_JACONOTOK:
    if(LANG == 1) printf("\nEps nicht erreicht, maxit erreicht -leider!\n");
    if(LANG == 2) printf("\neps not reached, maxit reached, sorry!\n");
  break;

  case TX_WRIO2:
    if(LANG == 1) printf("Z88O2.TXT beschreiben, Ende Z88R\n");
    if(LANG == 2) printf("writing Z88O2.TXT, Z88R done\n");
  break;

  case TX_SPANNU:
    if(LANG == 1 && isflag == 0) printf("***** Spannungen *****\n");
    if(LANG == 2 && isflag == 0) printf("***** stresses *****\n");
    if(LANG == 1 && isflag == 1) printf("***** Spannungen (GEH) *****\n");
    if(LANG == 2 && isflag == 1) printf("***** stresses (v.Mises) *****\n");
    if(LANG == 1 && isflag == 2) printf("***** Spannungen (NH) *****\n");
    if(LANG == 2 && isflag == 2) printf("***** stresses (principal) *****\n");
    if(LANG == 1 && isflag == 3) printf("***** Spannungen (SH) *****\n");
    if(LANG == 2 && isflag == 3) printf("***** stresses (Tresca) *****\n");
  break;

  case TX_EXITZ88D:
    if(LANG == 1) printf("\nEnde Z88DR\n");
    if(LANG == 2) printf("\nZ88DR done\n");
  break;

  case TX_KNOTENK:
    if(LANG == 1) printf("***** Knotenkraefte *****\n");
    if(LANG == 2) printf("***** nodal forces *****\n");
  break;

  case TX_EXITZ88E:
    if(LANG == 1) printf("\nEnde Z88ER\n");
    if(LANG == 2) printf("\nZ88ER done\n");
  break;

  }
return(0);
}

/***********************************************************************
*  function wtyp88j gibt Elementtypen aus
***********************************************************************/ 
int wtyp88j(FR_INT4 k,FR_INT4 i)
{
extern FR_INT4 LANG;

if(LANG == 1) printf("\rNr. " PD " Typ " PD "                         ",k,i);
if(LANG == 2) printf("\rno. " PD " type " PD "                        ",k,i);

return(0);
}

/***********************************************************************
*  function wtya88j gibt Elementtypen aus: Z88A
***********************************************************************/ 
int wtya88j(FR_INT4 k,FR_INT4 i)
{
extern FR_INT4 LANG;

if(LANG == 1) printf("\rNr. " PD " Typ " PD "                         ",k,i);
if(LANG == 2) printf("\rno. " PD " type " PD "                        ",k,i);

return(0);
}

/***********************************************************************
*  function wtyd88j gibt Elementtypen aus: Z88DJ
***********************************************************************/ 
int wtyd88j(FR_INT4 k,FR_INT4 i)
{
extern FR_INT4 LANG;

if(LANG == 1) printf("\rNr. " PD " Typ " PD "                         ",k,i);
if(LANG == 2) printf("\rno. " PD " type " PD "                        ",k,i);

return(0);
}

/***********************************************************************
*  function wtye88j gibt Elementtypen aus: Z88EJ
***********************************************************************/ 
int wtye88j(FR_INT4 k,FR_INT4 i)
{
extern FR_INT4 LANG;

if(LANG == 1) printf("\rNr. " PD " Typ " PD "                         ",k,i);
if(LANG == 2) printf("\rno. " PD " type " PD "                        ",k,i);

return(0);
}

/***********************************************************************
*  function wfor88i gibt kfoun beim Sortieren in Z88I1 aus
***********************************************************************/ 
int wfor88i(FR_INT4 k,FR_INT4 i)
{
extern FR_INT4 LANG;

if(LANG == 1) printf("\rnoch " PD9 " Schritte, Pointer IEZ = " PD9,k,i);
if(LANG == 2) printf("\rstill " PD9 " steps, pointer IEZ = " PD9,k,i);

return(0);
}

/***********************************************************************
*  function wran88j gibt Randbedingungen aus
***********************************************************************/ 
int wran88j(FR_INT4 k,FR_INT4 i)
{
extern FR_INT4 LANG;

if(LANG == 1) printf("\rRandbedingung Nr. " PD " Typ " PD,k,i);
if(LANG == 2) printf("\rconstraint no. " PD " type " PD,k,i);

fflush(stdout);
return(0);
}


