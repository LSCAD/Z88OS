/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows & UNIX OS.
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
* RCOL88C fuer Z88COM-UNIX: Browser und Editor einlesen
* 14.8.2011 Rieg
***********************************************************************/

/***********************************************************************
* UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88com.h>
#include <stdio.h>   /* fopen,fclose,fgets */
#include <string.h>  /* strstr */
#endif

/***********************************************************************
* Functions
***********************************************************************/
int wlog88c(FR_INT4,int);

/***********************************************************************
* Start rcol88c
***********************************************************************/
int rcol88c(void)
{

FILE *fcol;

extern char CEDITOR[], CBROWSER[], CPREFIX[];

int  ipos1,ipos2;

char cline[256], cdummy[80];

/*----------------------------------------------------------------------
* Color- datei z88.fcd oeffnen
*---------------------------------------------------------------------*/
fcol= fopen("z88.fcd","rb"); /* fcd = fonts, colors, dimensions       */

if(fcol == NULL)
  {
  wlog88c(0,LOG_NOCOL);
  return(AL_NOCOL);
  }
rewind(fcol);

/*----------------------------------------------------------------------
* Color-datei z88.fcd lesen
*---------------------------------------------------------------------*/
do
  if(fgets(cline,256,fcol)== NULL) break;
while( (strstr(cline,"Z88COM START"))== NULL);

if( (strstr(cline,"Z88COM START"))!= NULL)              /* File */
  {
  do
    {
    fgets(cline,80,fcol);

    if( (strstr(cline,"WINDOW START"))!= NULL) 
      {
      do
        {
        fgets(cline,80,fcol);

        if( (strstr(cline,"CEDITOR"))!= NULL) 
	  {
	  if( (strstr(cline,"*"))!= NULL)
	    {
	    ipos1= strcspn(cline,"*");
	    strcpy(cdummy,&cline[ipos1+1]);
	    ipos2= strcspn(cdummy,"*");
	    strncpy(CEDITOR,cdummy,(size_t)ipos2);	    
	    }
	  else
	    {
	    sscanf(cline,"%s %s",cdummy,CEDITOR);
	    }
	  }
        if( (strstr(cline,"CBROWSER"))!= NULL) 
	  {
	  if( (strstr(cline,"*"))!= NULL)
	    {
	    ipos1= strcspn(cline,"*");
	    strcpy(cdummy,&cline[ipos1+1]);
	    ipos2= strcspn(cdummy,"*");
	    strncpy(CBROWSER,cdummy,(size_t)ipos2);	    
	    }
	  else
	    {
	    sscanf(cline,"%s %s",cdummy,CBROWSER);
	    }
	  }
        if( (strstr(cline,"CPREFIX"))!= NULL) 
          sscanf(cline,"%s %s",cdummy,CPREFIX);
        }
      while( (strstr(cline,"WINDOW END"))== NULL);
      }         

    }
  while( (strstr(cline,"Z88COM END"))== NULL);     
    
  }             
  else
  {
  wlog88c(0,LOG_WRONGCOL);
  return(AL_WRONGCOL);
  }  

/*----------------------------------------------------------------------
* korrekt gelesen, file fcol schliessen
*---------------------------------------------------------------------*/
fclose(fcol);
return (0);
}

