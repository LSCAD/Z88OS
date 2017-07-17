/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the UNIX OS.
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
/****************************************************************************
* Programm z88n.c
* 21.7.2011 Rieg
****************************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88n.h>  
#include <stdio.h>    /* FILE */
#endif

/****************************************************************************
* Function-Declarationen
****************************************************************************/
int dyn88n(void);
int ale88n(int);
int who88n(void);
int rni88(void);
int join88(void);
int mc188n(void);
int mc288n(void);
int mc388n(void);
int mc488n(void);
int mc588n(void);
int mc688n(void);
int mc788n(void);
int mc888n(void);
void stop88n(void);
int lan88n(void);

/****************************************************************************
* globale Variable
****************************************************************************/
/*--------------------------------------------------------------------------
* Files
*-------------------------------------------------------------------------*/
FILE *fdyn,*fwlo,*fni,*fi1;

/*  
**   fdyn= z88.dyn
**   fwlo= z88n.log
**   fni=  z88ni.txt
**   fi1=  z88i1.txt
*/ 

char cdyn[8] = "z88.dyn";
char clgd[9] = "z88n.log";
char cni[10] = "z88ni.txt";
char ci1[10] = "z88i1.txt";
  
/*--------------------------------------------------------------------------
* Pointer
*-------------------------------------------------------------------------*/
FR_DOUBLEAY x;
FR_DOUBLEAY y;
FR_DOUBLEAY z;
FR_DOUBLEAY xss;
FR_DOUBLEAY yss;
FR_DOUBLEAY zss;

FR_INT4AY koima;
FR_INT4AY join; 
FR_INT4AY koiss;
FR_INT4AY ioffss;
FR_INT4AY koffss;
FR_INT4AY jel;
FR_INT4AY iel;
FR_INT4AY kel;

FR_CHARAY cjmode;
FR_CHARAY cimode;
FR_CHARAY ckmode;

/*--------------------------------------------------------------------------
* Arrays
*-------------------------------------------------------------------------*/
FR_DOUBLE h[21];

FR_INT4 jhxsta[21]= {0,1,3,3,1,1,3,3,1,2,3,2,1,2,3,2,1,1,3,3,1};
FR_INT4 ihxsta[21]= {0,1,1,3,3,1,1,3,3,1,2,3,2,1,2,3,2,1,1,3,3};
FR_INT4 khxsta[21]= {0,1,1,1,1,3,3,3,3,1,1,1,1,3,3,3,3,2,2,2,2};
FR_INT4 jlqsta[9] = {0,1,2,2,1,1,2,2,1};
FR_INT4 ilqsta[9] = {0,1,1,2,2,1,1,2,2};
FR_INT4 klqsta[9] = {0,1,1,1,1,2,2,2,2};
FR_INT4 jcssta[9] = {0,1,3,3,1,2,3,2,1};
FR_INT4 icssta[9] = {0,1,1,3,3,1,2,3,2};
FR_INT4 jklsta[17]= {0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4};
FR_INT4 iklsta[17]= {0,1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4};
FR_INT4 j21sta[17]= {0,1,3,3,1,2,3,2,1, 1,3,3,1,2,3,2,1};
FR_INT4 i21sta[17]= {0,1,1,3,3,1,2,3,2, 1,1,3,3,1,2,3,2};
FR_INT4 k21sta[17]= {0,1,1,1,1,1,1,1,1, 2,2,2,2,2,2,2,2};

/*--------------------------------------------------------------------------
* Variable
*-------------------------------------------------------------------------*/
FR_INT4 IDYNMEM,LANG;
FR_INT4 ndim,nkpss,ness,nfreis,ifrei,itypss,ityp;
/*--------------------------------------------------------------------------
* vorbelegte Variable
*-------------------------------------------------------------------------*/
FR_DOUBLE epsx=  0.01;
FR_DOUBLE epsy=  0.01;
FR_DOUBLE epsz=  0.01;

FR_INT4 MAXSE=0,MAXESS=0,MAXKSS=0,MAXK=0,MAXE=0,MAXNFG=0,MAXAN=0;

FR_INT4 kflagss= 0,kflag= 0,niflag= 0,idyn= 2;

/*****************************************************************************
* Hauptprogramm
*****************************************************************************/
int main(void)
{
int iret;

/*---------------------------------------------------------------------------
*  Die Sprache feststellen
*--------------------------------------------------------------------------*/
LANG = 0;
iret= lan88n();

if(iret != 0)
  {
  ale88n(iret);
  stop88n();
  }

/*---------------------------------------------------------------------------
* Ueberschrift
*--------------------------------------------------------------------------*/
who88n();
     
/*---------------------------------------------------------------------------
* dyn88n starten: anfordern dynamic memory
*--------------------------------------------------------------------------*/
iret= dyn88n();
if(iret != 0)
  {
  ale88n(iret);
  stop88n();              
  }           

/*---------------------------------------------------------------------------
* Einlesen Z88NI.TXT
*--------------------------------------------------------------------------*/
iret= rni88();
if(iret != 0)
  {
  ale88n(iret);
  stop88n();              
  }           

/*---------------------------------------------------------------------------
* join berechnen
*--------------------------------------------------------------------------*/
join88();

/*---------------------------------------------------------------------------
* Entscheiden, welche Function mcX88n
*--------------------------------------------------------------------------*/
if( itypss == 10 && ityp == 10 ) 
  {
  iret= mc188n();
  if(iret != 0)
    {
    ale88n(iret);
    stop88n();              
    }           
  }

if( itypss == 10 && ityp == 1 ) 
  {
  iret= mc288n();
  if(iret != 0)
    {
    ale88n(iret);
    stop88n();              
    }           
  }

if( itypss == 1 && ityp == 1 ) 
  {
  iret= mc788n();
  if(iret != 0)
    {
    ale88n(iret);
    stop88n();              
    }           
  }

if( (itypss == 7 || itypss == 8) && (ityp == 7 || ityp == 8) ) 
  {
  iret= mc388n();
  if(iret != 0)
    {
    ale88n(iret);
    stop88n();              
    }           
  }

if( (itypss == 11 || itypss == 12) && (ityp == 7 || ityp == 8)) 
  {
  iret= mc488n();
  if(iret != 0)
    {
    ale88n(iret);
    stop88n();              
    }           
  }
  
if( itypss == 20 && ityp == 19) 
  {
  iret= mc588n();
  if(iret != 0)
    {
    ale88n(iret);
    stop88n();              
    }           
  }

if( itypss == 21 && ityp == 21 ) 
  {
  iret= mc688n();
  if(iret != 0)
    {
    ale88n(iret);
    stop88n();              
    }           
  }

if( itypss == 20 && ityp == 20 )
  {
  iret= mc888n();
  if(iret != 0)
    {
    ale88n(iret);
    stop88n();              
    }           
  }

return(0);
}
