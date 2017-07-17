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
* Z88 should compile and run under any Windows OS and UNIX OS and 
* GTK+.
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
*  function dypa88 und laesst memory erneut kommen fuer GS,rs,ip,iez
*  16.4.2009 Rieg 
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88j.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets,sscanf */
#include <string.h>  /* strstr */
#include <stdlib.h>  /* FR_CALLOC */
#endif

/***********************************************************************
* Fuer Windows 95
***********************************************************************/
#ifdef FR_WIN95
#include <z88j.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets,sscanf */
#include <string.h>  /* strstr */
#include <stdlib.h>  /* FR_CALLOC */
#endif

/***********************************************************************
* Fuer Windows & GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88j.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets,sscanf */
#include <string.h>  /* strstr */
#include <stdlib.h>  /* FR_CALLOC */
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wlog88j(FR_INT4,int);

/***********************************************************************
* hier beginnt Function dypa88
***********************************************************************/
int dypa88(void)
{
extern FILE *fwlo;

extern FR_DOUBLEAY GS;
extern FR_DOUBLEAY rs;

extern FR_INT4AY ip;
extern FR_INT4AY iez;

extern FR_INT4 MAXGS,MAXNFG,MAXIEZ;

/*======================================================================
*  memory fuer GS
*=====================================================================*/
if(GS) free(GS);

GS= (FR_DOUBLEAY) FR_CALLOC((MAXGS+1),sizeof(FR_DOUBLE));
if(GS == NULL)
  {
  wlog88j(1,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88j(1,LOG_ARRAYOK);

/*======================================================================
*  memory fuer rs
*=====================================================================*/
if(rs) free(rs);

rs= (FR_DOUBLEAY) FR_CALLOC((MAXNFG+1),sizeof(FR_DOUBLE));
if(rs == NULL)
  {
  wlog88j(11,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88j(11,LOG_ARRAYOK);

/*======================================================================
*  memory fuer iez
*=====================================================================*/
if(iez) free(iez);

iez= (FR_INT4AY) FR_CALLOC((MAXIEZ+1),sizeof(FR_INT4));
if(iez == NULL)
  {
  wlog88j(50,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88j(50,LOG_ARRAYOK);

/*======================================================================
*  memory fuer ip
*=====================================================================*/
if(ip) free(ip);

ip= (FR_INT4AY) FR_CALLOC((MAXNFG+1),sizeof(FR_INT4));
if(ip == NULL)
  {
  wlog88j(60,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88j(60,LOG_ARRAYOK);

return(0);
}
