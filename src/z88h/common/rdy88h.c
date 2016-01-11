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
* Function rdy88h liest z88.dyn aus und definiert MAXGRA und MAXNDL
* hier wird File Z88.DYN geoffnet
* 30.7.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88h.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets */
#include <string.h>  /* strstr */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88h.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets */
#include <string.h>  /* strstr */
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
* Functions
***********************************************************************/
int wlog88h(FR_INT4,int);

/***********************************************************************
* hier beginnt Function rdy88h
***********************************************************************/
int rdy88h(void)
{
extern FILE *fdyn, *fwlo;
extern char cdyn[];

extern FR_INT4 MAXGRA,MAXNDL;

char cline[256], cdummy[80];
  
/*----------------------------------------------------------------------
* Dyn- Datei z88.dyn oeffnen
*---------------------------------------------------------------------*/
wlog88h(0,LOG_OPENDYN);
fdyn= fopen(cdyn,"r");
if(fdyn == NULL)
  {
  wlog88h(0,LOG_NODYN);
  fclose(fwlo);
  return(AL_NODYN);
  }
rewind(fdyn);

/*----------------------------------------------------------------------
* Dyn- Datei z88.dyn lesen
*---------------------------------------------------------------------*/
fgets(cline,256,fdyn);

if( (strstr(cline,"DYNAMIC START"))!= NULL)         /* Lesen File */
  {
  do
    {
    fgets(cline,256,fdyn);

    if( (strstr(cline,"CUTKEE START"))!= NULL)      /* Lesen CUTKEE */
      {
      do
        {
        fgets(cline,256,fdyn);
        if( (strstr(cline,"MAXGRA"))!= NULL)        /* Lesen MAXGRA */
          sscanf(cline,"%s " PD,cdummy,&MAXGRA);
        if( (strstr(cline,"MAXNDL"))!= NULL)        /* Lesen MAXNDL */
          sscanf(cline,"%s " PD,cdummy,&MAXNDL);
        }
      while( (strstr(cline,"CUTKEE END"))== NULL);
      }

    }
  while( (strstr(cline,"DYNAMIC END"))== NULL);     
    
  }                                                 /* end if DYNAMIC START */
else
  {
  wlog88h(0,LOG_WRONGDYN);
  fclose(fwlo);
  return(AL_WRONGDYN);
  }  

if(MAXGRA <= 0 || MAXNDL <= 0 )
  {
  wlog88h(0,LOG_WRONGDYN);
  fclose(fwlo);
  return(AL_WRONGDYN);
  }  

/*----------------------------------------------------------------------
* korrekt gelesen, File fdyn schliessen
*---------------------------------------------------------------------*/
fclose(fdyn);

wlog88h(0,LOG_OKDYN);

return(0);
}
