/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows and
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
* man88o - liest Z88MAN.TXT und erste Zeile Z88I5.TXT
* 19.7.2011 Rieg 
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88o.h>
#include <stdio.h>    /* FILE,NULL,fopen,fclose,rewind */
#include <string.h>
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88o.h>
#include <stdio.h>    /* FILE,NULL,fopen,fclose,rewind */
#include <string.h>
#endif

/***********************************************************************
* Formate
***********************************************************************/
#ifdef FR_XINT
#define CFORMA "%s %d"
#define PDB "%d "
#define PDE "%d"
#endif

#ifdef FR_XLONG
#define CFORMA "%s %ld"
#define PDB "%ld "
#define PDE "%ld"
#endif

#ifdef FR_XLOLO
#define CFORMA "%s %lld"
#define PDB "%lld "
#define PDE "%lld"
#endif

#ifdef FR_XDOUB
#define CFORMA2 "%s %lg"
#define PGB "%lg "
#define PGE "%lg"
#endif

#ifdef FR_XQUAD
#define CFORMA2 "%s %Lg"
#define PGB "%Lg "
#define PGE "%Lg"
#endif

/****************************************************************************
*  Function-Declarationen
****************************************************************************/
int  ale88o(int);
int  wlog88o(FR_INT4,int);

/***********************************************************************
* hier beginnt Function man88o
***********************************************************************/
int man88o(void) 
{
extern FILE       *fman,*fi5,*fwlo;

extern FR_INT4    ibflag,ipflag,iqflag;

extern char       cman[],ci5[];

FR_INT4           jdummy;

char cdummy[256];
char cline[256];

/*----------------------------------------------------------------------
*  Manage-Datei z88man.txt oeffnen
*---------------------------------------------------------------------*/
fman = fopen(cman,"r");
if(fman == NULL)
  {
  wlog88o(0,LOG_NOMAN);
  fclose(fwlo);
  return(AL_NOMAN);
  }
rewind(fman);

/*----------------------------------------------------------------------
*  Sektion DYNAMIC lesen
*---------------------------------------------------------------------*/
fgets(cline,256,fman);

if( (strstr(cline,"DYNAMIC START"))!= NULL)   
  {
  do
    {
    fgets(cline,256,fman);

/*======================================================================
*  Sektion GLOBAL lesen
*=====================================================================*/
    if( (strstr(cline,"GLOBAL START"))!= NULL)    
      {
      do
        {
        fgets(cline,256,fman);
        if( (strstr(cline,"IBFLAG"))!= NULL)    
            sscanf(cline,CFORMA,cdummy,&ibflag);
        if( (strstr(cline,"IPFLAG"))!= NULL)      
          sscanf(cline,CFORMA,cdummy,&ipflag);
        }
      while( (strstr(cline,"GLOBAL END"))== NULL);
      }                                             
                         
    }
  while( (strstr(cline,"DYNAMIC END"))== NULL);     
    
  }                                                
else
  {
  wlog88o(0,LOG_WRONGMAN);
  fclose(fman);
  fclose(fwlo);
  return(AL_WRONGMAN);
  }  

fclose(fman);

/*----------------------------------------------------------------------
*  Flaechenlast-Datei z88i5.txt oeffnen, erste Zeile lesen --> iqflag
*---------------------------------------------------------------------*/
  fi5= fopen(ci5,"r");
  if(fi5 == NULL)
    {
    iqflag= 0;  
    goto L2000; 
    }
  
  rewind(fi5);

  fgets(cline,256,fi5);
  sscanf(cline,PDE,&jdummy);
  if(jdummy >= 0) iqflag = 1;
  fclose(fi5);    

L2000:;


return 0;
}


