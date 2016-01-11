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
* V14.0 January 14, 2011
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
*  function dyn88r liest z88.dyn aus und laesst memory kommen
*  hier wird File Z88.DYN erneut geoeffnet (vorher schon in lan88r)
*  25.7.2011 Rieg 
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets,sscanf */
#include <string.h>  /* strstr */
#include <stdlib.h>  /* FR_CALLOC */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <stdio.h>   /* FILE,NULL,fopen,fclose,fgets,sscanf */
#include <string.h>  /* strstr */
#include <stdlib.h>  /* FR_CALLOC */
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wlog88r(FR_INT4,int);

/***********************************************************************
* hier beginnt Function dyn88r
***********************************************************************/
int dyn88r(void)
{
extern FR_DOUBLEAY GS;
extern FR_DOUBLEAY CI;
extern FR_DOUBLEAY se;
extern FR_DOUBLEAY rs;
extern FR_DOUBLEAY xi;
extern FR_DOUBLEAY xa;
extern FR_DOUBLEAY v;
extern FR_DOUBLEAY pk;
extern FR_DOUBLEAY zz;
extern FR_DOUBLEAY fak;
extern FR_DOUBLEAY x;
extern FR_DOUBLEAY y;
extern FR_DOUBLEAY z;
extern FR_DOUBLEAY emod;
extern FR_DOUBLEAY rnue;
extern FR_DOUBLEAY qpara;
extern FR_DOUBLEAY riyy;
extern FR_DOUBLEAY eyy;
extern FR_DOUBLEAY rizz;
extern FR_DOUBLEAY ezz;
extern FR_DOUBLEAY rit;
extern FR_DOUBLEAY wt;
extern FR_DOUBLEAY pres;
extern FR_DOUBLEAY tr1;
extern FR_DOUBLEAY tr2;
extern FR_DOUBLEAY smw;
extern FR_DOUBLEAY smwku;
extern FR_DOUBLEAY gmw;
extern FR_DOUBLEAY gmwku;
extern FR_DOUBLEAY fsum1;
extern FR_DOUBLEAY fsum2;
extern FR_DOUBLEAY fsum3;
extern FR_DOUBLEAY fsum4;
extern FR_DOUBLEAY fsum5;
extern FR_DOUBLEAY fsum6;
extern FR_DOUBLEAY sigvku;
extern FR_DOUBLEAY sdu;
extern FR_DOUBLEAY tmt;
extern FR_DOUBLEAY tm;
extern FR_DOUBLEAY zm;

extern FR_INT4AY ip;
extern FR_INT4AY iez;
extern FR_INT4AY koi;
extern FR_INT4AY ifrei; 
extern FR_INT4AY ioffs;
extern FR_INT4AY koffs;
extern FR_INT4AY ityp;
extern FR_INT4AY ivon_mat;
extern FR_INT4AY ibis_mat;
extern FR_INT4AY ivon_elp;
extern FR_INT4AY ibis_elp;
extern FR_INT4AY ivon_int;
extern FR_INT4AY ibis_int;
extern FR_INT4AY intord;
extern FR_INT4AY intos;
extern FR_INT4AY nep;
extern FR_INT4AY noi;
extern FR_INT4AY noffs;
extern FR_INT4AY jsm;

extern FILE *fdyn,*fwlo;
extern char cdyn[];

extern FR_INT4 IDYNMEM,ICFLAG,MAXGP,MAXTRA,MAXPEL,MAXJNT,MAXGS;
extern FR_INT4 MAXNFG,MAXK,MAXE,MAXKOI,MAXESM,MAXMAT,MAXPR,MAXIEZ;

double RDYNMEM;
char   cline[256], cdummy[80];
   
/*----------------------------------------------------------------------
*  Eintragungen in Z88R.LOG
*---------------------------------------------------------------------*/
if(ICFLAG == 0) wlog88r(0,LOG_CFLAG0);
if(ICFLAG == 1) wlog88r(1,LOG_CFLAG1);
if(ICFLAG == 2) wlog88r(2,LOG_CFLAG2);

/*----------------------------------------------------------------------
*  Dyn-Datei z88.dyn oeffnen
*---------------------------------------------------------------------*/
wlog88r(0,LOG_OPENZ88DYN);

fdyn= fopen(cdyn,"r");
if(fdyn == NULL)
  {
  wlog88r(0,LOG_NODYN);
  fclose(fwlo);
  return(AL_NODYN);
  }

rewind(fdyn);

/*----------------------------------------------------------------------
*  Dyn-Datei z88.dyn lesen
*---------------------------------------------------------------------*/
#ifdef FR_XINT
#define CFORMA "%s %d"
#endif
#ifdef FR_XLONG
#define CFORMA "%s %ld"
#endif
#ifdef FR_XLOLO
#define CFORMA "%s %lld"
#endif

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
        if( (strstr(cline,"MAXGS"))!= NULL)         /* Lesen MAXGS */
          sscanf(cline,CFORMA,cdummy,&MAXGS);
        if( (strstr(cline,"MAXKOI"))!= NULL)        /* Lesen MAXKOI */
          sscanf(cline,CFORMA,cdummy,&MAXKOI);
        if( (strstr(cline,"MAXK"))!= NULL)          /* Lesen MAXK */
          sscanf(cline,CFORMA,cdummy,&MAXK);
        if( (strstr(cline,"MAXE"))!= NULL)          /* Lesen MAXE */
          sscanf(cline,CFORMA,cdummy,&MAXE);
        if( (strstr(cline,"MAXNFG"))!= NULL)        /* Lesen MAXNFG */
          sscanf(cline,CFORMA,cdummy,&MAXNFG);
        if( (strstr(cline,"MAXMAT"))!= NULL)        /* Lesen MAXMAT */
          sscanf(cline,CFORMA,cdummy,&MAXMAT);
        if( (strstr(cline,"MAXPEL"))!= NULL)        /* Lesen MAXPEL */
          sscanf(cline,CFORMA,cdummy,&MAXPEL);
        if( (strstr(cline,"MAXJNT"))!= NULL)        /* Lesen MAXJNT */
          sscanf(cline,CFORMA,cdummy,&MAXJNT);
        if( (strstr(cline,"MAXPR"))!= NULL)         /* Lesen MAXPR */
          sscanf(cline,CFORMA,cdummy,&MAXPR);
        if( (strstr(cline,"MAXIEZ"))!= NULL)        /* Lesen MAXIEZ */
          sscanf(cline,CFORMA,cdummy,&MAXIEZ);
        if( (strstr(cline,"MAXGP"))!= NULL)         /* Lesen MAXGP */
          sscanf(cline,CFORMA,cdummy,&MAXGP);
        }
      while( (strstr(cline,"COMMON END"))== NULL);
      }                                             /* end if COMMON START */

    }
  while( (strstr(cline,"DYNAMIC END"))== NULL);     
    
  }                                                 /* end if DYNAMIC START */
else
  {
  wlog88r(0,LOG_WRONGDYN);
  fclose(fwlo);
  return(AL_WRONGDYN);
  }  

if(MAXGS <= 0  || MAXKOI <= 0 || MAXK <= 0   || MAXE <= 0  || MAXNFG <= 0 ||
   MAXMAT <= 0 || MAXPEL <= 0 || MAXJNT <= 0 || MAXPR <= 0 || MAXIEZ <= 0)
  {
  wlog88r(0,LOG_WRONGDYN);
  fclose(fwlo);
  return(AL_WRONGDYN);
  }  

/*----------------------------------------------------------------------
*  korrekt gelesen, file fdyn schliessen
*---------------------------------------------------------------------*/
fclose(fdyn);

wlog88r(MAXGS,LOG_MAXGS);
wlog88r(MAXKOI,LOG_MAXKOI);
wlog88r(MAXK,LOG_MAXK);
wlog88r(MAXE,LOG_MAXE);
wlog88r(MAXNFG,LOG_MAXNFG);
wlog88r(MAXMAT,LOG_MAXMAT);
wlog88r(MAXPEL,LOG_MAXPEL);
wlog88r(MAXJNT,LOG_MAXINT);
wlog88r(MAXESM,LOG_MAXESM);
wlog88r(MAXPR,LOG_MAXPR);
wlog88r(MAXPR,LOG_MAXIEZ);

wlog88r(0,LOG_OKDYN);

/*----------------------------------------------------------------------
*  memory kommen lassen ..
*---------------------------------------------------------------------*/
wlog88r(0,LOG_ALLOCMEMY);

/*======================================================================
*  memory fuer GS und CI (nur fuer SICCG88)
*=====================================================================*/
GS= (FR_DOUBLEAY) FR_CALLOC((MAXGS+1),sizeof(FR_DOUBLE));
if(GS == NULL)
  {
  wlog88r(1,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(1,LOG_ARRAYOK);

if(ICFLAG == 1)
  {
  CI= (FR_DOUBLEAY) FR_CALLOC((MAXGS+1),sizeof(FR_DOUBLE));
  if(CI == NULL)
    {
    wlog88r(2,LOG_ARRAYNOTOK);
    fclose(fwlo);
    return(AL_NOMEMY);
    }
  else
    wlog88r(2,LOG_ARRAYOK);
  }

/*======================================================================
*  memory fuer se,rs,fak
*=====================================================================*/
se= (FR_DOUBLEAY) FR_CALLOC((MAXESM+1),sizeof(FR_DOUBLE));
if(se == NULL)
  {
  wlog88r(10,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(10,LOG_ARRAYOK);

rs= (FR_DOUBLEAY) FR_CALLOC((MAXNFG+1),sizeof(FR_DOUBLE));
if(rs == NULL)
  {
  wlog88r(11,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(11,LOG_ARRAYOK);

fak= (FR_DOUBLEAY) FR_CALLOC((MAXNFG+1),sizeof(FR_DOUBLE));
if(fak == NULL)
  {
  wlog88r(16,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(16,LOG_ARRAYOK);

/*======================================================================
*  memory xi,xa,v,pk,zz (nur SICCG und SORCG)
*=====================================================================*/
if(ICFLAG == 1 || ICFLAG == 2)
  {
  xi= (FR_DOUBLEAY) FR_CALLOC((MAXNFG+1),sizeof(FR_DOUBLE));
  if(xi == NULL)
    {
    wlog88r(20,LOG_ARRAYNOTOK);
    fclose(fwlo);
    return(AL_NOMEMY);
    }
  else
    wlog88r(20,LOG_ARRAYOK);

  xa= (FR_DOUBLEAY) FR_CALLOC((MAXNFG+1),sizeof(FR_DOUBLE));
  if(xa == NULL)
    {
    wlog88r(21,LOG_ARRAYNOTOK);
    fclose(fwlo);
    return(AL_NOMEMY);
    }
  else
    wlog88r(21,LOG_ARRAYOK);

  v= (FR_DOUBLEAY) FR_CALLOC((MAXNFG+1),sizeof(FR_DOUBLE));
  if(v == NULL)
    {
    wlog88r(22,LOG_ARRAYNOTOK);
    fclose(fwlo);
    return(AL_NOMEMY);
    }
  else
    wlog88r(22,LOG_ARRAYOK);

  pk= (FR_DOUBLEAY) FR_CALLOC((MAXNFG+1),sizeof(FR_DOUBLE));
  if(pk == NULL)
    {
    wlog88r(23,LOG_ARRAYNOTOK);
    fclose(fwlo);
    return(AL_NOMEMY);
    }
  else
    wlog88r(23,LOG_ARRAYOK);

  zz= (FR_DOUBLEAY) FR_CALLOC((MAXNFG+1),sizeof(FR_DOUBLE));
  if(zz == NULL)
    {
    wlog88r(24,LOG_ARRAYNOTOK);
    fclose(fwlo);
    return(AL_NOMEMY);
    }
  else
    wlog88r(24,LOG_ARRAYOK);
  }

/*======================================================================
*  memory fuer x,y,z
*=====================================================================*/
x= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(x == NULL)
  {
  wlog88r(30,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(30,LOG_ARRAYOK);

y= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(y == NULL)
  {
  wlog88r(31,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(31,LOG_ARRAYOK);

z= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(z == NULL)
  {
  wlog88r(32,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(32,LOG_ARRAYOK);

/*======================================================================
*  memory fuer emod,rnue,ivon_mat,ibis_mat
*=====================================================================*/
emod= (FR_DOUBLEAY) FR_CALLOC((MAXMAT+1),sizeof(FR_DOUBLE));
if(emod == NULL)
  {
  wlog88r(40,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(40,LOG_ARRAYOK);

rnue= (FR_DOUBLEAY) FR_CALLOC((MAXMAT+1),sizeof(FR_DOUBLE));
if(rnue == NULL)
  {
  wlog88r(41,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(41,LOG_ARRAYOK);

ivon_mat= (FR_INT4AY) FR_CALLOC((MAXMAT+1),sizeof(FR_INT4));
if(ivon_mat == NULL)
  {
  wlog88r(42,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(42,LOG_ARRAYOK);

ibis_mat= (FR_INT4AY) FR_CALLOC((MAXMAT+1),sizeof(FR_INT4));
if(ibis_mat == NULL)
  {
  wlog88r(43,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(43,LOG_ARRAYOK);

/*======================================================================
*  memory fuer iez (nur CFLAG != 0)
*=====================================================================*/
if(ICFLAG != 0)
  {
  iez= (FR_INT4AY) FR_CALLOC((MAXIEZ+1),sizeof(FR_INT4));
  if(iez == NULL)
    {
    wlog88r(50,LOG_ARRAYNOTOK);
    fclose(fwlo);
    return(AL_NOMEMY);
    }
  else
    wlog88r(50,LOG_ARRAYOK);
  }

/*======================================================================
*  memory fuer ip,koi,ifrei,ioffs,koffs,ityp
*=====================================================================*/
ip= (FR_INT4AY) FR_CALLOC((MAXNFG+1),sizeof(FR_INT4));
if(ip == NULL)
  {
  wlog88r(60,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(60,LOG_ARRAYOK);

koi= (FR_INT4AY) FR_CALLOC((MAXKOI+1),sizeof(FR_INT4));
if(koi == NULL)
  {
  wlog88r(61,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(61,LOG_ARRAYOK);

ifrei= (FR_INT4AY) FR_CALLOC((MAXK+1),sizeof(FR_INT4));
if(ifrei == NULL)
  {
  wlog88r(62,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(62,LOG_ARRAYOK);

ioffs= (FR_INT4AY) FR_CALLOC((MAXK+1),sizeof(FR_INT4));
if(ioffs == NULL)
  {
  wlog88r(632,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(63,LOG_ARRAYOK);

koffs= (FR_INT4AY) FR_CALLOC((MAXE+1),sizeof(FR_INT4));
if(koffs == NULL)
  {
  wlog88r(64,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(64,LOG_ARRAYOK);

ityp= (FR_INT4AY) FR_CALLOC((MAXE+1),sizeof(FR_INT4));
if(ityp == NULL)
  {
  wlog88r(65,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(65,LOG_ARRAYOK);

/*======================================================================
*  memory fuer ivon_int,ibis_int,intord,intos
*=====================================================================*/
ivon_int= (FR_INT4AY) FR_CALLOC((MAXJNT+1),sizeof(FR_INT4));
if(ivon_int == NULL)
  {
  wlog88r(70,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(70,LOG_ARRAYOK);
  
ibis_int= (FR_INT4AY) FR_CALLOC((MAXJNT+1),sizeof(FR_INT4));
if(ibis_int == NULL)
  {
  wlog88r(71,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(71,LOG_ARRAYOK);

intord= (FR_INT4AY) FR_CALLOC((MAXJNT+1),sizeof(FR_INT4));
if(intord == NULL)
  {
  wlog88r(72,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(72,LOG_ARRAYOK);

intos= (FR_INT4AY) FR_CALLOC((MAXJNT+1),sizeof(FR_INT4));
if(intos == NULL)
  {
  wlog88r(73,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(73,LOG_ARRAYOK);

/*======================================================================
*  memory fuer ivon_elp,ibis_elp,qpara,riyy,eyy,rizz,ezz,rit,wt
*=====================================================================*/
ivon_elp= (FR_INT4AY) FR_CALLOC((MAXPEL+1),sizeof(FR_INT4));
if(ivon_elp == NULL)
  {
  wlog88r(80,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(80,LOG_ARRAYOK);

ibis_elp= (FR_INT4AY) FR_CALLOC((MAXPEL+1),sizeof(FR_INT4));
if(ibis_elp == NULL)
  {
  wlog88r(81,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(81,LOG_ARRAYOK);

qpara= (FR_DOUBLEAY) FR_CALLOC((MAXPEL+1),sizeof(FR_DOUBLE));
if(qpara == NULL)
  {
  wlog88r(82,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(82,LOG_ARRAYOK);

riyy= (FR_DOUBLEAY) FR_CALLOC((MAXPEL+1),sizeof(FR_DOUBLE));
if(riyy == NULL)
  {
  wlog88r(83,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(83,LOG_ARRAYOK);

eyy= (FR_DOUBLEAY) FR_CALLOC((MAXPEL+1),sizeof(FR_DOUBLE));
if(eyy == NULL)
  {
  wlog88r(84,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(84,LOG_ARRAYOK);

rizz= (FR_DOUBLEAY) FR_CALLOC((MAXPEL+1),sizeof(FR_DOUBLE));
if(rizz == NULL)
  {
  wlog88r(85,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(85,LOG_ARRAYOK);

ezz= (FR_DOUBLEAY) FR_CALLOC((MAXPEL+1),sizeof(FR_DOUBLE));
if(ezz == NULL)
  {
  wlog88r(86,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(86,LOG_ARRAYOK);

rit= (FR_DOUBLEAY) FR_CALLOC((MAXPEL+1),sizeof(FR_DOUBLE));
if(rit == NULL)
  {
  wlog88r(87,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(87,LOG_ARRAYOK);

wt= (FR_DOUBLEAY) FR_CALLOC((MAXPEL+1),sizeof(FR_DOUBLE));
if(wt == NULL)
  {
  wlog88r(88,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(88,LOG_ARRAYOK);

/*======================================================================
*  memory fuer pres,tr1,tr2,nep,noi,noffs
*  Annahme: max. 8 Knoten pro Oberflaeche
*=====================================================================*/
pres= (FR_DOUBLEAY) FR_CALLOC((MAXPR+1),sizeof(FR_DOUBLE));
if(pres == NULL)
  {
  wlog88r(90,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(91,LOG_ARRAYOK);

tr1= (FR_DOUBLEAY) FR_CALLOC((MAXPR+1),sizeof(FR_DOUBLE));
if(tr1 == NULL)
  {
  wlog88r(92,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(92,LOG_ARRAYOK);

tr2= (FR_DOUBLEAY) FR_CALLOC((MAXPR+1),sizeof(FR_DOUBLE));
if(tr2 == NULL)
  {
  wlog88r(93,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(93,LOG_ARRAYOK);

nep= (FR_INT4AY) FR_CALLOC((MAXPR+1),sizeof(FR_INT4));
if(nep == NULL)
  {
  wlog88r(94,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(94,LOG_ARRAYOK);

noi= (FR_INT4AY) FR_CALLOC((MAXPR*8+1),sizeof(FR_INT4));
if(noi == NULL)
  {
  wlog88r(95,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(95,LOG_ARRAYOK);

noffs= (FR_INT4AY) FR_CALLOC((MAXPR+1),sizeof(FR_INT4));
if(noffs == NULL)
  {
  wlog88r(96,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(96,LOG_ARRAYOK);

/*======================================================================
*  memory fuer smw,jsm,smwku
*=====================================================================*/
smw= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(smw == NULL)
  {
  wlog88r(100,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(100,LOG_ARRAYOK);

jsm= (FR_INT4AY) FR_CALLOC((MAXK+1),sizeof(FR_INT4));
if(jsm == NULL)
  {
  wlog88r(101,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(101,LOG_ARRAYOK);

smwku= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(smwku == NULL)
  {
  wlog88r(102,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(102,LOG_ARRAYOK);

/*======================================================================
*  memory fuer gmw,gmwku
*=====================================================================*/
gmw= (FR_DOUBLEAY) FR_CALLOC((MAXE+1),sizeof(FR_DOUBLE));
if(gmw == NULL)
  {
  wlog88r(103,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(103,LOG_ARRAYOK);

gmwku= (FR_DOUBLEAY) FR_CALLOC((MAXE+1),sizeof(FR_DOUBLE));
if(gmwku == NULL)
  {
  wlog88r(104,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(104,LOG_ARRAYOK);

/*======================================================================
*  memory fuer sigvku
*=====================================================================*/
sigvku= (FR_DOUBLEAY) FR_CALLOC((MAXGP+1),sizeof(FR_DOUBLE));
if(sigvku == NULL)
  {
  wlog88r(105,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(105,LOG_ARRAYOK);

/*======================================================================
*  memory fuer fsum1 - fsum6
*=====================================================================*/
fsum1= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(fsum1 == NULL)
  {
  wlog88r(110,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(110,LOG_ARRAYOK);

fsum2= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(fsum2 == NULL)
  {
  wlog88r(111,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(111,LOG_ARRAYOK);
  
fsum3= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(fsum3 == NULL)
  {
  wlog88r(112,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(112,LOG_ARRAYOK);

fsum4= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(fsum4 == NULL)
  {
  wlog88r(113,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(113,LOG_ARRAYOK);
  
fsum5= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(fsum5 == NULL)
  {
  wlog88r(114,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(114,LOG_ARRAYOK);
  
fsum6= (FR_DOUBLEAY) FR_CALLOC((MAXK+1),sizeof(FR_DOUBLE));
if(fsum6 == NULL)
  {
  wlog88r(115,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(115,LOG_ARRAYOK);

/*======================================================================
*  memory fuer sdu,tmt,tm,zm
*=====================================================================*/
sdu= (FR_DOUBLEAY) FR_CALLOC((MAXTRA+1),sizeof(FR_DOUBLE));
if(sdu == NULL)
  {
  wlog88r(120,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(120,LOG_ARRAYOK);

tmt= (FR_DOUBLEAY) FR_CALLOC((MAXTRA+1),sizeof(FR_DOUBLE));
if(tmt == NULL)
  {
  wlog88r(121,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(121,LOG_ARRAYOK);

tm = (FR_DOUBLEAY) FR_CALLOC((MAXTRA+1),sizeof(FR_DOUBLE));
if(tm == NULL)
  {
  wlog88r(122,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(122,LOG_ARRAYOK);

zm = (FR_DOUBLEAY) FR_CALLOC((MAXTRA+1),sizeof(FR_DOUBLE));
if(zm == NULL)
  {
  wlog88r(123,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88r(123,LOG_ARRAYOK);
 
/***********************************************************************
* alles o.k. 
***********************************************************************/
RDYNMEM =   ((double)MAXGS+1.) *sizeof(FR_DOUBLE);     /* GS */

if(ICFLAG ==1)
  RDYNMEM+=   ((double)MAXGS+1.) *sizeof(FR_DOUBLE);   /* CI */

RDYNMEM+=   ((double)MAXESM+1.)*sizeof(FR_DOUBLE);     /* se */
RDYNMEM+= 2*((double)MAXNFG+1.)*sizeof(FR_DOUBLE);     /* rs,fak */

if(ICFLAG == 1 || ICFLAG == 2)
  RDYNMEM+= 5*((double)MAXNFG+1.)*sizeof(FR_DOUBLE);   /* xi,xa,v,pk,zz*/

RDYNMEM+= 6*((double)MAXK+1.)  *sizeof(FR_DOUBLE);     /* x,y,z,xsik,ysik,zsik */

RDYNMEM+= 2*((double)MAXMAT+1.)*sizeof(FR_DOUBLE);     /* emod,rnue */
RDYNMEM+= 2*((double)MAXMAT+1.)*sizeof(FR_INT4);       /* ivon_mat,ibis_mat */

RDYNMEM+= 2*((double)MAXPEL+1.)*sizeof(FR_INT4);       /* ivon_elp,ibis_elp */
RDYNMEM+= 7*((double)MAXPEL+1.)*sizeof(FR_DOUBLE);     /* qpara,riyy,eyy,rizz,ezz,rit,wt */

RDYNMEM+= 4*((double)MAXJNT+1.)*sizeof(FR_INT4);       /* ivon_int,ibis_int,intord,intos */

if(ICFLAG != 0)
  RDYNMEM+=   ((double)MAXIEZ+1.)*sizeof(FR_INT4);     /* iez */

RDYNMEM+=   ((double)MAXNFG+1.)*sizeof(FR_INT4);       /* ip */
RDYNMEM+=   ((double)MAXKOI+1.)*sizeof(FR_INT4);       /* koi */
RDYNMEM+= 2*((double)MAXK+1.)  *sizeof(FR_INT4);       /* ifrei,ioffs */
RDYNMEM+= 2*((double)MAXE+1.)  *sizeof(FR_INT4);       /* koffs,ityp */

RDYNMEM+= 3*((double)MAXPR+1.) *sizeof(FR_DOUBLE);     /* pres,tr1,tr2 */
RDYNMEM+=10*((double)MAXPR+1.) *sizeof(FR_INT4);       /* nep,noi,noffs */

RDYNMEM+= 3*((double)MAXK+1.)  *sizeof(FR_DOUBLE);     /* smw,jsm,smwku */
RDYNMEM+= 2*((double)MAXE+1.)  *sizeof(FR_DOUBLE);     /* gmw,gmwku */
RDYNMEM+=   ((double)MAXGP+1.) *sizeof(FR_DOUBLE);     /* sigvku */
RDYNMEM+= 6*((double)MAXK+1.)  *sizeof(FR_DOUBLE);     /* fsum1 - fsum6 */
RDYNMEM+= 4*((double)MAXTRA+1.)*sizeof(FR_DOUBLE);     /* sdu,tmt,tm,zm */

IDYNMEM= (FR_INT4) (RDYNMEM/1048576.);
wlog88r(IDYNMEM,LOG_SUMMEMY);
wlog88r(0,LOG_EXITDYN88J);

return(0);
}
