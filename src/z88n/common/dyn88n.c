/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the UNIX and
* the Windows OS.
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
/***********************************************************************
* Function dyn88n liest z88.dyn aus und laesst memory kommen
* hier wird File Z88.DYN geoffnet
* 31.7.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88n.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets */
#include <string.h>  /* strstr */
#include <stdlib.h>  /* FR_CALLOC */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88n.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets */
#include <string.h>  /* strstr */
#include <stdlib.h>  /* FR_CALLOC */
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
* Functions
***********************************************************************/
int wlog88n(FR_INT4,int);

/***********************************************************************
* hier beginnt Function dyn88n
***********************************************************************/
int dyn88n(void)
{
extern FILE *fdyn, *fwlo;
extern char cdyn[];

extern FR_DOUBLEAY x;
extern FR_DOUBLEAY y;
extern FR_DOUBLEAY z;
extern FR_DOUBLEAY xss;
extern FR_DOUBLEAY yss;
extern FR_DOUBLEAY zss;

extern FR_INT4AY koima;
extern FR_INT4AY join; 
extern FR_INT4AY koiss;
extern FR_INT4AY ioffss;
extern FR_INT4AY koffss;
extern FR_INT4AY jel;
extern FR_INT4AY iel;
extern FR_INT4AY kel;

extern FR_INT4 MAXSE,MAXESS,MAXKSS,MAXK,MAXE,MAXNFG,MAXAN;
extern FR_INT4 IDYNMEM;

extern FR_CHARAY cjmode;
extern FR_CHARAY cimode;
extern FR_CHARAY ckmode;

char cline[256], cdummy[80];
  
/*----------------------------------------------------------------------
* Dyn- Datei z88.dyn oeffnen
*---------------------------------------------------------------------*/
wlog88n(0,LOG_OPENDYN);
fdyn= fopen(cdyn,"r");
if(fdyn == NULL)
  {
  wlog88n(0,LOG_NODYN);
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

    if( (strstr(cline,"NET START"))!= NULL)         /* Lesen NET */
      {
      do
        {
        fgets(cline,256,fdyn);
        if( (strstr(cline,"MAXSE"))!= NULL)         /* Lesen MAXSE */
          sscanf(cline,"%s " PD,cdummy,&MAXSE);
        if( (strstr(cline,"MAXESS"))!= NULL)        /* Lesen MAXESS */
          sscanf(cline,"%s " PD,cdummy,&MAXESS);
        if( (strstr(cline,"MAXKSS"))!= NULL)        /* Lesen MAXKSS */
          sscanf(cline,"%s " PD,cdummy,&MAXKSS);
        if( (strstr(cline,"MAXAN"))!= NULL)        /* Lesen MAXAN */
          sscanf(cline,"%s " PD,cdummy,&MAXAN);
        }
      while( (strstr(cline,"NET END"))== NULL);
      }

    if( (strstr(cline,"COMMON START"))!= NULL)      /* Lesen COMMON */
      {
      do
        {
        fgets(cline,256,fdyn);
        if( (strstr(cline,"MAXK"))!= NULL)          /* Lesen MAXK */
          sscanf(cline,"%s " PD,cdummy,&MAXK);
        if( (strstr(cline,"MAXE"))!= NULL)          /* Lesen MAXE */
          sscanf(cline,"%s " PD,cdummy,&MAXE);
        if( (strstr(cline,"MAXNFG"))!= NULL)        /* Lesen MAXNFG */
          sscanf(cline,"%s " PD,cdummy,&MAXNFG);
        }
      while( (strstr(cline,"COMMON END"))== NULL);
      }                                             /* end if COMMON START */

    }
  while( (strstr(cline,"DYNAMIC END"))== NULL);     
    
  }                                                 /* end if DYNAMIC START */
else
  {
  wlog88n(0,LOG_WRONGDYN);
  fclose(fwlo);
  return(AL_WRONGDYN);
  }  

if(MAXSE <= 0 || MAXESS <= 0 || MAXKSS <= 0 || MAXK <= 0 ||
    MAXE <= 0 || MAXNFG <= 0 || MAXAN <= 0)
  {
  wlog88n(0,LOG_WRONGDYN);
  fclose(fwlo);
  return(AL_WRONGDYN);
  }  

/*----------------------------------------------------------------------
* korrekt gelesen, File fdyn schliessen
*---------------------------------------------------------------------*/
fclose(fdyn);

wlog88n(MAXSE,LOG_MAXSE);
wlog88n(MAXESS,LOG_MAXESS);
wlog88n(MAXKSS,LOG_MAXKSS);
wlog88n(MAXAN,LOG_MAXAN);
wlog88n(MAXK,LOG_MAXK);
wlog88n(MAXE,LOG_MAXE);
wlog88n(MAXNFG,LOG_MAXNFG);
 
wlog88n(0,LOG_OKDYN);

/*----------------------------------------------------------------------
* Memory kommen lassen ..
*---------------------------------------------------------------------*/
wlog88n(0,LOG_ALLOCMEMY);

/*======================================================================
* Memory fuer x, y, z : 1,2,3
*=====================================================================*/
x= (FR_DOUBLEAY) FR_CALLOC(MAXSE,sizeof(FR_DOUBLE));
if(x == NULL)
  {
  wlog88n(1,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88n(1,LOG_ARRAYOK);

y= (FR_DOUBLEAY) FR_CALLOC(MAXSE,sizeof(FR_DOUBLE));
if(y == NULL)
  {
  wlog88n(2,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88n(2,LOG_ARRAYOK);

z= (FR_DOUBLEAY) FR_CALLOC(MAXSE,sizeof(FR_DOUBLE));
if(z == NULL)
  {
  wlog88n(3,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88n(3,LOG_ARRAYOK);

/*======================================================================
* Memory fuer xss, yss, zss: 4,5,6
*=====================================================================*/
xss= (FR_DOUBLEAY) FR_CALLOC(MAXKSS,sizeof(FR_DOUBLE));
if(xss == NULL)
  {
  wlog88n(4,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88n(4,LOG_ARRAYOK);

yss= (FR_DOUBLEAY) FR_CALLOC(MAXKSS,sizeof(FR_DOUBLE));
if(yss == NULL)
  {
  wlog88n(5,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88n(5,LOG_ARRAYOK);

zss= (FR_DOUBLEAY) FR_CALLOC(MAXKSS,sizeof(FR_DOUBLE));
if(zss == NULL)
  {
  wlog88n(6,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88n(6,LOG_ARRAYOK);

/*======================================================================
* Memory fuer koima, join, koiss: 10,11,12
*=====================================================================*/
koima= (FR_INT4AY) FR_CALLOC(MAXSE,sizeof(FR_INT4));
if(koima == NULL)
  {
  wlog88n(10,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88n(10,LOG_ARRAYOK);

join= (FR_INT4AY) FR_CALLOC((MAXESS*MAXAN),sizeof(FR_INT4));
if(join == NULL)
  {
  wlog88n(11,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88n(11,LOG_ARRAYOK);

koiss= (FR_INT4AY) FR_CALLOC((MAXESS*20),sizeof(FR_INT4));
if(koiss == NULL)
  {
  wlog88n(12,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88n(12,LOG_ARRAYOK);

/*======================================================================
* Memory fuer ioffss, koffss, jel, iel, kel: 13,14,15,16,17
*=====================================================================*/
ioffss= (FR_INT4AY) FR_CALLOC(MAXESS,sizeof(FR_INT4));
if(ioffss == NULL)
  {
  wlog88n(13,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88n(13,LOG_ARRAYOK);

koffss= (FR_INT4AY) FR_CALLOC(MAXESS,sizeof(FR_INT4));
if(koffss == NULL)
  {
  wlog88n(14,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88n(14,LOG_ARRAYOK);

jel= (FR_INT4AY) FR_CALLOC(MAXESS,sizeof(FR_INT4));
if(jel == NULL)
  {
  wlog88n(15,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88n(15,LOG_ARRAYOK);

iel= (FR_INT4AY) FR_CALLOC(MAXESS,sizeof(FR_INT4));
if(iel == NULL)
  {
  wlog88n(16,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88n(16,LOG_ARRAYOK);

kel= (FR_INT4AY) FR_CALLOC(MAXESS,sizeof(FR_INT4));
if(kel == NULL)
  {
  wlog88n(17,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88n(17,LOG_ARRAYOK);

/*======================================================================
* Memory fuer cjmode, cimode, ckmode: 23,24,25
*=====================================================================*/
cjmode= (FR_CHARAY) FR_CALLOC(MAXESS,sizeof(char));
if(cjmode == NULL)
  {
  wlog88n(23,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88n(23,LOG_ARRAYOK);

cimode= (FR_CHARAY) FR_CALLOC(MAXESS,sizeof(char));
if(cimode == NULL)
  {
  wlog88n(24,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88n(24,LOG_ARRAYOK);

ckmode= (FR_CHARAY) FR_CALLOC(MAXESS,sizeof(char));
if(ckmode == NULL)
  {
  wlog88n(25,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88n(25,LOG_ARRAYOK);

/***********************************************************************
* alles o.k. 
***********************************************************************/
IDYNMEM = 3*MAXSE*sizeof(FR_DOUBLE);
IDYNMEM+= 3*MAXKSS*sizeof(FR_DOUBLE);
IDYNMEM+=   MAXSE *sizeof(FR_INT4);
IDYNMEM+=   MAXESS*MAXAN*sizeof(FR_INT4);
IDYNMEM+=   MAXESS*20*sizeof(FR_INT4);
IDYNMEM+= 5*MAXESS*sizeof(FR_INT4);
IDYNMEM+= 3*MAXESS*sizeof(char);

wlog88n(IDYNMEM,LOG_SUMMEMY);
wlog88n(0,LOG_EXITDYN88N);

return(0);
}
