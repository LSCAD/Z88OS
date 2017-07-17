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
* Z88G
* 18.11.2015 Rieg
* wandelt COSMOS-Files oder NASTRAN-Files 
* aus Pro/MESH (PTC, Pro/ENGINEER) 
* in Z88I*.TXT- Files fuer die Z88- Elementtypen:
* * Scheiben  Nr. 7 ( 8 Knoten) und Nr.14 (6 Knoten)
* * Tetraeder Nr.16 (10 Knoten) und Nr.17 (4 Knoten)
* * Platten   Nr.20 ( 8 Knoten) und Nr.18 (6 Knoten)
* * Tori      Nr. 8 ( 8 Knoten) und Nr.15 (6 Knoten)
* * Schalen   Nr.24 ( 6 Knoten)
***********************************************************************/

/***********************************************************************
* Include- Files
***********************************************************************/
#ifdef FR_UNIX
#include <z88g.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#endif

/****************************************************************************
*  Function-Declarationen
****************************************************************************/
int who88g(void);
int lan88g(void);
int cosm88(void);
int nast88(void);
int dnas88(void);
int ale88g(int);
void stop88g(void);
int wrim88g(FR_INT4,int);
int wlog88g(FR_INT4,int);

/****************************************************************************
*  globale Variable
****************************************************************************/
/*--------------------------------------------------------------------------
* Files
*-------------------------------------------------------------------------*/
FILE *fdyn,*fwlo,*fpro,*fin,*fi1,*fi2,*fi5;

/*  
**   fdyn= z88.dyn
**   fwlo= z88g.log
**   fpro= z88g.cos oder z88g.nas
**   fin = z88g.in
**   fi1=  z88i1.txt
**   fi2=  z88i2.txt
**   fi5=  z88i5.txt
*/ 

char cdyn[8] = "z88.dyn";
char clgd[9] = "z88g.log";
char ccco[9] = "z88g.cos";
char cnas[9] = "z88g.nas";
char cin[8]  = "z88g.in";
char ci1[10] = "z88i1.txt";
char ci2[10] = "z88i2.txt";
char ci5[10] = "z88i5.txt";

/*--------------------------------------------------------------------------
* Variable
*-------------------------------------------------------------------------*/

FR_INT4 IFFLAG=0,ICFLAG= 0,LANG;

/***********************************************************************
* Hauptprogramm
***********************************************************************/
int main(void)
{               
extern FILE *fdyn,*fwlo,*fpro,*fin,*fi1,*fi2,*fi5;

extern FR_INT4 LANG,ICFLAG;

FR_INT4 iret;

/*---------------------------------------------------------------------------
*  Die Sprache feststellen
*--------------------------------------------------------------------------*/
LANG = 0;
iret= lan88g();

if(iret != 0)
  {
  ale88g(iret);
  stop88g();
  }

/*---------------------------------------------------------------------------
*  Ueberschrift
*--------------------------------------------------------------------------*/
who88g();

/*----------------------------------------------------------------------
* COSMOS oder NASTRAN ? Scheiben oder Platten ?
*---------------------------------------------------------------------*/	
wlog88g(0,LOG_BZ88);

Lfagain:;
  wrim88g(0,TX_COSNAS);
  scanf("%ld",&IFFLAG);
  if(!(IFFLAG == 1 || IFFLAG == 2 )) goto Lfagain; 

wrim88g(IFFLAG,TX_FILEF);
wlog88g(IFFLAG,LOG_FILEF);

Lcagain:;
  if(IFFLAG == 1) wrim88g(0,TX_CHOICOS);
  if(IFFLAG == 2) wrim88g(0,TX_CHOINAS);
  scanf("%ld",&ICFLAG);
  if(IFFLAG == 1)
    {
    if(!(ICFLAG == 1 || ICFLAG == 2 || 
         ICFLAG == 3 || ICFLAG == 4 )) goto Lcagain;
    } 
  if(IFFLAG == 2)
    {
    if(!(ICFLAG == 2 || ICFLAG == 3 || 
         ICFLAG == 4 || ICFLAG == 5 || 
         ICFLAG == 6))                 goto Lcagain;
    } 


wrim88g(ICFLAG,TX_SHEIPLA);
wlog88g(ICFLAG,LOG_SHEIPLA);

/*----------------------------------------------------------------------
* Umsetzen
*---------------------------------------------------------------------*/
if(IFFLAG == 1)   iret= cosm88();
if(IFFLAG == 2)
  {
  if(ICFLAG != 5) iret= nast88();
  else            iret= dnas88();
  }

if(iret != 0)
  {
  ale88g(iret);
  stop88g();              
  } 
          	
/*----------------------------------------------------------------------
* Fertig
*---------------------------------------------------------------------*/
wrim88g(0,TX_Z88DONE);
wlog88g(0,LOG_Z88DONE);

return 0;
}


