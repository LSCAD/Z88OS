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
*  function dyn88o
*  31.7.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88o.h>
#include <stdio.h>   /* fopen,fclose,fgets,fprintf,sscanf */
#include <string.h>  /* strstr */
#include <stdlib.h>  /* FR_CALLOC */
#endif

/***********************************************************************
* Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88o.h>
#include <stdio.h>   /* fopen,fclose,fgets,fprintf,sscanf */
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
int wlog88o(FR_INT4,int);

/***********************************************************************
* dyn88o
***********************************************************************/
int dyn88o(void)
{
extern FILE *fdyn, *fwlo;
extern char cdyn[];

extern FR_DOUBLEAY x;
extern FR_DOUBLEAY y;
extern FR_DOUBLEAY z;
extern FR_DOUBLEAY ux;
extern FR_DOUBLEAY uy;
extern FR_DOUBLEAY uz;
extern FR_DOUBLEAY xv;
extern FR_DOUBLEAY yv;
extern FR_DOUBLEAY zv;
extern FR_DOUBLEAY sep;
extern FR_DOUBLEAY sne;
extern FR_DOUBLEAY rwert;
extern FR_DOUBLEAY xgp;
extern FR_DOUBLEAY ygp;
extern FR_DOUBLEAY zgp;
extern FR_DOUBLEAY xgpo;
extern FR_DOUBLEAY ygpo;
extern FR_DOUBLEAY zgpo;
extern FR_DOUBLEAY siggp;

extern FR_INT4AY   ityp;
extern FR_INT4AY   koi;
extern FR_INT4AY   koffs;
extern FR_INT4AY   iep;
extern FR_INT4AY   ifarbe;
extern FR_INT4AY   jfarbe;
extern FR_INT4AY   kfarbe;
extern FR_INT4AY   nkn;
extern FR_INT4AY   ifg;
extern FR_INT4AY   iflag1;
extern FR_INT4AY   nep;
extern FR_INT4AY   noi;
extern FR_INT4AY   noffs;

extern FR_INT4 MAXKOI,MAXE,MAXK,MAXRBD,MAXPR,MAXGP;
extern FR_INT4 IDYNMEM;

FR_DOUBLE      RDYNMEM;

char cline[256], cdummy[80];
  
/*----------------------------------------------------------------------
* Dyn-Datei z88.dyn oeffnen
*---------------------------------------------------------------------*/
wlog88o(0,LOG_OPENDYN);
fdyn= fopen(cdyn,"r");
if(fdyn == NULL)
  {
  wlog88o(0,LOG_NODYN);
  fclose(fwlo);
  return(AL_NODYN);
  }
rewind(fdyn);

/*----------------------------------------------------------------------
* Dyn- datei z88.dyn lesen
*---------------------------------------------------------------------*/
fgets(cline,256,fdyn);

if( (strstr(cline,"DYNAMIC START"))!= NULL)         /* Lesen File */
  {
  do
    {
    fgets(cline,256,fdyn);

    if( (strstr(cline,"COMMON START"))!= NULL)      /* Lesen COMMON */
      {
      do
        {
        fgets(cline,256,fdyn);
        if( (strstr(cline,"MAXKOI"))!= NULL)        /* Lesen MAXKOI */
          sscanf(cline,"%s " PD,cdummy,&MAXKOI);
        if( (strstr(cline,"MAXE"))!= NULL)          /* Lesen MAXE */
          sscanf(cline,"%s " PD,cdummy,&MAXE);
        if( (strstr(cline,"MAXK"))!= NULL)          /* Lesen MAXK */
          sscanf(cline,"%s " PD,cdummy,&MAXK);
        if( (strstr(cline,"MAXRBD"))!= NULL)        /* Lesen MAXRBD */
          sscanf(cline,"%s " PD,cdummy,&MAXRBD);
        if( (strstr(cline,"MAXPR"))!= NULL)         /* Lesen MAXPR */
          sscanf(cline,"%s " PD,cdummy,&MAXPR);
        if( (strstr(cline,"MAXGP"))!= NULL)         /* Lesen MAXGP */
          sscanf(cline,"%s " PD,cdummy,&MAXGP);
        }
      while( (strstr(cline,"COMMON END"))== NULL);
      }

    }
  while( (strstr(cline,"DYNAMIC END"))== NULL);     
    
  }                                                 /* end if DYNAMIC START */
else
  {
  wlog88o(0,LOG_WRONGDYN);
  fclose(fwlo);
  return(AL_WRONGDYN);
  }  

if(MAXKOI <= 0 || MAXE <= 0 || MAXK <= 0 || MAXRBD <= 0 ||
   MAXPR <= 0 || MAXGP <= 0)
  {
  wlog88o(0,LOG_WRONGDYN);
  fclose(fwlo);
  return(AL_WRONGDYN);
  }  

/*----------------------------------------------------------------------
* korrekt gelesen, file fdyn schliessen
*---------------------------------------------------------------------*/
fclose(fdyn);

wlog88o(MAXKOI,LOG_MAXKOI);
wlog88o(MAXE,LOG_MAXE);
wlog88o(MAXK,LOG_MAXK);

wlog88o(0,LOG_OKDYN);

/*----------------------------------------------------------------------
* Memory kommen lassen ..
*---------------------------------------------------------------------*/
wlog88o(0,LOG_ALLOCMEMY);

/*======================================================================
* Memory fuer x, y, z: 1,2,3
*=====================================================================*/
x= (FR_DOUBLEAY) FR_CALLOC(MAXK,sizeof(FR_DOUBLE));
if(x == NULL)
  {
  wlog88o(1,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(1,LOG_ARRAYOK);

y= (FR_DOUBLEAY) FR_CALLOC(MAXK,sizeof(FR_DOUBLE));
if(y == NULL)
  {
  wlog88o(2,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(2,LOG_ARRAYOK);

z= (FR_DOUBLEAY) FR_CALLOC(MAXK,sizeof(FR_DOUBLE));
if(z == NULL)
  {
  wlog88o(3,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(3,LOG_ARRAYOK);

/*======================================================================
* Memory fuer ux, uy, uz: 4,5,6
*=====================================================================*/
ux= (FR_DOUBLEAY) FR_CALLOC(MAXK,sizeof(FR_DOUBLE));
if(ux == NULL)
  {
  wlog88o(4,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(4,LOG_ARRAYOK);

uy= (FR_DOUBLEAY) FR_CALLOC(MAXK,sizeof(FR_DOUBLE));
if(uy == NULL)
  {
  wlog88o(5,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(5,LOG_ARRAYOK);

uz= (FR_DOUBLEAY) FR_CALLOC(MAXK,sizeof(FR_DOUBLE));
if(uz == NULL)
  {
  wlog88o(6,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(6,LOG_ARRAYOK);

/*======================================================================
* Memory fuer xv, yv, zv, sep: 7,8,9,10
*=====================================================================*/
xv= (FR_DOUBLEAY) FR_CALLOC(MAXK,sizeof(FR_DOUBLE));
if(xv == NULL)
  {
  wlog88o(7,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(7,LOG_ARRAYOK);

yv= (FR_DOUBLEAY) FR_CALLOC(MAXK,sizeof(FR_DOUBLE));
if(yv == NULL)
  {
  wlog88o(8,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(8,LOG_ARRAYOK);

zv= (FR_DOUBLEAY) FR_CALLOC(MAXK,sizeof(FR_DOUBLE));
if(zv == NULL)
  {
  wlog88o(9,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(9,LOG_ARRAYOK);

sep= (FR_DOUBLEAY) FR_CALLOC(MAXK,sizeof(FR_DOUBLE));
if(sep == NULL)
  {
  wlog88o(10,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(10,LOG_ARRAYOK);

/*======================================================================
* Memory fuer ityp, koffs: 11,12
*=====================================================================*/
ityp= (FR_INT4AY) FR_CALLOC(MAXE,sizeof(FR_INT4));
if(ityp == NULL)
  {
  wlog88o(11,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(11,LOG_ARRAYOK);

koffs= (FR_INT4AY) FR_CALLOC(MAXE,sizeof(FR_INT4));
if(koffs == NULL)
  {
  wlog88o(12,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(12,LOG_ARRAYOK);

/*======================================================================
* Memory fuer koi: 13
*=====================================================================*/
koi= (FR_INT4AY) FR_CALLOC(MAXKOI,sizeof(FR_INT4));
if(koi == NULL)
  {
  wlog88o(13,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(13,LOG_ARRAYOK);

/*======================================================================
*  memory fuer iep, ifarbe: 14,15
*=====================================================================*/
iep= (FR_INT4AY) FR_CALLOC(MAXK,sizeof(FR_INT4));
if(iep == NULL)
  {
  wlog88o(14,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(14,LOG_ARRAYOK);

ifarbe= (FR_INT4AY) FR_CALLOC(MAXK,sizeof(FR_INT4));
if(ifarbe == NULL)
  {
  wlog88o(15,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(15,LOG_ARRAYOK);

/*======================================================================
*  memory fuer sne, jfarbe: 16,17
*=====================================================================*/
sne= (FR_DOUBLEAY) FR_CALLOC(MAXE,sizeof(FR_DOUBLE));
if(sne == NULL)
  {
  wlog88o(16,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(16,LOG_ARRAYOK);

jfarbe= (FR_INT4AY) FR_CALLOC(MAXE,sizeof(FR_INT4));
if(jfarbe == NULL)
  {
  wlog88o(17,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(17,LOG_ARRAYOK);

/*======================================================================
*  memory fuer rwert, nkn, ifg, iflag1: 18,19,20,21
*=====================================================================*/
rwert= (FR_DOUBLEAY) FR_CALLOC(MAXRBD,sizeof(FR_DOUBLE));
if(rwert == NULL)
  {
  wlog88o(18,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(18,LOG_ARRAYOK);

nkn= (FR_INT4AY) FR_CALLOC(MAXRBD,sizeof(FR_INT4));
if(nkn == NULL)
  {
  wlog88o(19,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(19,LOG_ARRAYOK);

ifg= (FR_INT4AY) FR_CALLOC(MAXRBD,sizeof(FR_INT4));
if(ifg == NULL)
  {
  wlog88o(20,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(20,LOG_ARRAYOK);

iflag1= (FR_INT4AY) FR_CALLOC(MAXRBD,sizeof(FR_INT4));
if(iflag1 == NULL)
  {
  wlog88o(21,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(21,LOG_ARRAYOK);

/*======================================================================
*  memory fuer nep, noi, noffs: 22,23,24
*=====================================================================*/
nep= (FR_INT4AY) FR_CALLOC((MAXPR+1),sizeof(FR_INT4));
if(nep == NULL)
  {
  wlog88o(22,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(22,LOG_ARRAYOK);

noi= (FR_INT4AY) FR_CALLOC((MAXPR*8+1),sizeof(FR_INT4));
if(noi == NULL)
  {
  wlog88o(23,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(23,LOG_ARRAYOK);

noffs= (FR_INT4AY) FR_CALLOC((MAXPR+1),sizeof(FR_INT4));
if(noffs == NULL)
  {
  wlog88o(24,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(24,LOG_ARRAYOK);

/*======================================================================
* Memory fuer xgp,ygp,zgp,xgpo,ygpo,zgpo,siggp,kfarbe: 27,28,29,30,31,32,33,34
*=====================================================================*/
xgp= (FR_DOUBLEAY) FR_CALLOC(MAXGP+1,sizeof(FR_DOUBLE));
if(xgp == NULL)
  {
  wlog88o(27,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(27,LOG_ARRAYOK);

ygp= (FR_DOUBLEAY) FR_CALLOC(MAXGP+1,sizeof(FR_DOUBLE));
if(ygp == NULL)
  {
  wlog88o(28,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(28,LOG_ARRAYOK);

zgp= (FR_DOUBLEAY) FR_CALLOC(MAXGP+1,sizeof(FR_DOUBLE));
if(zgp == NULL)
  {
  wlog88o(29,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(29,LOG_ARRAYOK);

xgpo= (FR_DOUBLEAY) FR_CALLOC(MAXGP+1,sizeof(FR_DOUBLE));
if(xgpo == NULL)
  {
  wlog88o(30,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(30,LOG_ARRAYOK);

ygpo= (FR_DOUBLEAY) FR_CALLOC(MAXGP+1,sizeof(FR_DOUBLE));
if(ygpo == NULL)
  {
  wlog88o(31,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(31,LOG_ARRAYOK);

zgpo= (FR_DOUBLEAY) FR_CALLOC(MAXGP+1,sizeof(FR_DOUBLE));
if(zgpo == NULL)
  {
  wlog88o(32,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(32,LOG_ARRAYOK);

siggp= (FR_DOUBLEAY) FR_CALLOC(MAXGP+1,sizeof(FR_DOUBLE));
if(siggp == NULL)
  {
  wlog88o(33,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(33,LOG_ARRAYOK);

kfarbe= (FR_INT4AY) FR_CALLOC(MAXGP+1,sizeof(FR_INT4));
if(kfarbe == NULL)
  {
  wlog88o(34,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88o(34,LOG_ARRAYOK);

/***********************************************************************
* alles o.k. 
***********************************************************************/
RDYNMEM = 3*(double)(MAXK+1.)*  sizeof(FR_DOUBLE);   /* x,y,z */
RDYNMEM+= 3*(double)(MAXK+1.)*  sizeof(FR_DOUBLE);   /* ux,uy,uz */
RDYNMEM+= 4*(double)(MAXK+1.)*  sizeof(FR_DOUBLE);   /* xv,yv,zv,sep */
RDYNMEM+= 3*(double)(MAXE+1.)*  sizeof(FR_INT4);     /* ityp,koffs,jfarbe */  
RDYNMEM+=   (double)(MAXKOI+1.)*sizeof(FR_INT4);     /* koi */
RDYNMEM+= 2*(double)(MAXK+1.)*  sizeof(FR_INT4);     /* iep,ifarbe */
RDYNMEM+=   (double)(MAXE+1.)*  sizeof(FR_DOUBLE);   /* sne */
RDYNMEM+=   (double)(MAXRBD+1.)*sizeof(FR_DOUBLE);   /* rwert */
RDYNMEM+= 3*(double)(MAXRBD+1.)*sizeof(FR_INT4);     /* nkn,ifg,iflag1 */
RDYNMEM+=10*(double)(MAXPR+1.) *sizeof(FR_INT4);     /* nep,noi,noffs */
RDYNMEM+= 7*(double)(MAXGP+1.)* sizeof(FR_DOUBLE);   /* xgp(o,ygp(o,zgp(o,siggp */
RDYNMEM+=   (double)(MAXGP+1.)* sizeof(FR_INT4);     /* kfarbe */

IDYNMEM= (FR_INT4) (RDYNMEM/1048576.);
wlog88o(IDYNMEM,LOG_SUMMEMY);
wlog88o(0,LOG_EXITDYN88O);

return 0;
}

