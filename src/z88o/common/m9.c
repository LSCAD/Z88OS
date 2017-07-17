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
/**********************************************************
*  Compilerunit M9.C enthaelt:
*  ri2x88
*  ro2x88
*  ro8x88
*  ro5x88
*  stro88
*  snow88
*  spgp88
*  vfx88
*  vfy88
*  vfz88
*  31.7.2011 RIEG
**********************************************************/

/*----------------------------------------------------------------------
* Windows
*---------------------------------------------------------------------*/
#ifdef FR_WIN
#include <z88o.h>
#include <stdio.h>    /* fprintf,fgets,sscanf */
#endif

/*----------------------------------------------------------------------
* UNIX
*---------------------------------------------------------------------*/
#ifdef FR_UNIX
#include <z88o.h>
#include <stdio.h>    /* fprintf,fgets,sscanf */
#endif

/***********************************************************************
* Leseformate
***********************************************************************/
#ifdef FR_XINT
#define PDB "%d "
#define PD "%d"
#endif

#ifdef FR_XLONG
#define PDB "%ld "
#define PD "%ld"
#endif

#ifdef FR_XLOLO
#define PDB "%lld "
#define PD "%lld"
#endif

#ifdef FR_XDOUB
#define PGB "%lg "
#define PG "%lg"
#endif

#ifdef FR_XQUAD
#define PGB "%Lg "
#define PG "%Lg"
#endif

/***********************************************************************
* Functions
***********************************************************************/
int wlog88o(FR_INT4,int);

/***********************************************************************
* hier beginnt Function ri2x88
***********************************************************************/
int ri2x88(void)
{
extern FILE        *fi2;
 
extern FR_DOUBLEAY rwert;

extern FR_INT4AY   nkn;
extern FR_INT4AY   ifg;
extern FR_INT4AY   iflag1;

extern FR_INT4     MAXRBD,nrb;

FR_INT4            i;

char               cline[256];

/*----------------------------------------------------------------------
* Eintrag in z88o.log
*---------------------------------------------------------------------*/
wlog88o(0,LOG_REAI2);

/*----------------------------------------------------------------------
* Datei lesen
*---------------------------------------------------------------------*/
fgets(cline,256,fi2);
sscanf(cline,PD,&nrb);

if(nrb >= MAXRBD)
  {
  wlog88o(MAXRBD,LOG_EXMAXRBD);
  return(AL_EXMAXRBD);
  }

for(i = 1;i <= nrb;i++)
  {  
  fgets(cline,256,fi2);
  sscanf(cline,PDB PDB PDB PG,&nkn[i],&ifg[i],&iflag1[i],&rwert[i]);
  }

wlog88o(0,LOG_REAI2OK);
return 0;
}

/***********************************************************************
* hier beginnt Function ro2x88
***********************************************************************/
int ro2x88(void)
{
extern FILE        *fo2;
 
extern FR_DOUBLEAY ux;
extern FR_DOUBLEAY uy;
extern FR_DOUBLEAY uz;

extern FR_INT4     nkp,ipflag;

FR_INT4            i,idummy;

char               cline[256];

/*----------------------------------------------------------------------
* Eintrag in z88o.log
*---------------------------------------------------------------------*/
wlog88o(0,LOG_REAO2);
        
/*----------------------------------------------------------------------
* 5 zeilen leerlesen
*---------------------------------------------------------------------*/
for(i= 0; i < 5; i++) fgets(cline,256,fo2);
          
/*----------------------------------------------------------------------
* Verschiebungen einlesen, nur translatorisch erforderlich
*---------------------------------------------------------------------*/
/*======================================================================
* alles ausser Platten
*=====================================================================*/
if(ipflag == 0)
  {
  for(i= 1; i <= nkp; i++)
    {
    fgets(cline,256,fo2);
    sscanf(cline,PDB PGB PGB PG,&idummy,&ux[i],&uy[i],&uz[i]);
    }
  }

/*======================================================================
* Platten brauchen Sonderbehandlung
*=====================================================================*/
else
  {
  for(i= 1; i <= nkp; i++)
    {
    ux[i]= 0.;
    uy[i]= 0.;
    fgets(cline,256,fo2);
    sscanf(cline,PDB PG,&idummy,&uz[i]);
    }
  }

wlog88o(0,LOG_REAO2OK);
return 0;
}

/***********************************************************************
* hier beginnt subroutine ro8x88
***********************************************************************/
int ro8x88(void)
{
extern FILE        *fo8;        

extern FR_DOUBLEAY sep;
extern FR_DOUBLEAY sne;

extern FR_INT4AY   iep;

extern FR_INT4     isflag,iepanz,ne;

FR_INT4            i,idummy;

char               cline[256];

/*----------------------------------------------------------------------
* Eintrag in z88o.log
*---------------------------------------------------------------------*/
wlog88o(0,LOG_REAO8);

/*----------------------------------------------------------------------
* Anzahl der Eckknoten einlesen
*---------------------------------------------------------------------*/
fgets(cline,256,fo8);
sscanf(cline,PDB PD,&iepanz,&isflag);

/*----------------------------------------------------------------------
* Spannungen fuer die Eckknoten einlesen
*---------------------------------------------------------------------*/
for(i= 1; i <= iepanz; i++)
  {
  fgets(cline,256,fo8);
  sscanf(cline,PDB PDB PG,&iep[i],&idummy,&sep[i]);
  }

/*----------------------------------------------------------------------
* Anzahl der Elemente einlesen
*---------------------------------------------------------------------*/
fgets(cline,256,fo8);
sscanf(cline,PD,&idummy);

/*----------------------------------------------------------------------
* Spannungen pro Element einlesen
*---------------------------------------------------------------------*/
for(i= 1; i <= ne; i++)
  {
  fgets(cline,256,fo8);
  sscanf(cline,PDB PG,&idummy,&sne[i]);
  }

wlog88o(0,LOG_REAO8OK);
return 0;
}

/***********************************************************************
* hier beginnt subroutine ro5x88
***********************************************************************/
int ro5x88(void)
{
extern FILE *fo5;        

extern FR_DOUBLEAY xgp;
extern FR_DOUBLEAY ygp;
extern FR_DOUBLEAY zgp;
extern FR_DOUBLEAY siggp;
extern FR_DOUBLE spamin,spamax,spainc;

extern FR_INT4 MAXGP;
extern FR_INT4 isflag,igpanz;

FR_INT4 ndimi,ninto,i;

char cline[256];

/***********************************************************************
* Einlesen des Fileheaders
***********************************************************************/
wlog88o(0,LOG_REAO5);

fgets(cline,256,fo5);
sscanf(cline,PDB PDB PD,&ndimi,&ninto,&isflag);

/***********************************************************************
* Pruefen, ob auch korrekterweise in Gausspunkten geplottet werden kann
***********************************************************************/
if(ninto== 0)
  {
  wlog88o(0,LOG_NINT0);
  return(AL_NINT0);
  }           

/***********************************************************************
* Einlesen 2 oder 3-dimensional
***********************************************************************/
if(ndimi == 2) 
  {
  i= 1;
  while( (fgets(cline,256,fo5)) != NULL)
    {
    sscanf(cline,PGB PGB PG,&xgp[i],&ygp[i],&siggp[i]);
    i++;
    if(i == MAXGP-1)
      {
      wlog88o(MAXGP,LOG_EXMAXGP);
      return(AL_EXMAXGP);
      }
    }              
  }
else
  {
  i= 1;
  while( (fgets(cline,256,fo5)) != NULL)
    {
    sscanf(cline,PGB PGB PGB PG,&xgp[i],&ygp[i],&zgp[i],&siggp[i]);
    i++;
    if(i == MAXGP-1)
      {
      wlog88o(MAXGP,LOG_EXMAXGP);
      return(AL_EXMAXGP);
      }
    }              
  }

igpanz= i-1; 
       
wlog88o(0,LOG_REAO5OK);
return 0;
}

/***********************************************************************
* hier beginnt subroutine stro88: Farben fuer Spannungen in "Eckknoten"
***********************************************************************/
int stro88(void)
{
extern FR_DOUBLEAY sep;

extern FR_DOUBLE   fspa[];

extern FR_DOUBLE   sigmin,sigmax,siginc;

extern FR_INT4AY   iep;
extern FR_INT4AY   ifarbe;

extern FR_INT4     iepanz,nkp;

FR_DOUBLE          sigz;

FR_INT4            i;

/*----------------------------------------------------------------------
* Farbregister auf Null 
*---------------------------------------------------------------------*/
for(i= 1; i <= nkp; i++)
  ifarbe[i]= 0;

/*----------------------------------------------------------------------
* Minimal- und Maximalwerte feststellen
*---------------------------------------------------------------------*/
for(i= 1; i <= iepanz; i++)
  if(sep[i] > sigmax) sigmax= sep[i];

sigmin= sigmax;

for(i= 1; i <= iepanz; i++)
  if(sep[i] < sigmin) sigmin= sep[i];

/*----------------------------------------------------------------------
* Spannungsstufen berechnen
*---------------------------------------------------------------------*/
siginc= (sigmax-sigmin)/11.;

fspa[1]=  sigmin;
fspa[2]=  fspa[1]  + siginc;
fspa[3]=  fspa[2]  + siginc;
fspa[4]=  fspa[3]  + siginc;
fspa[5]=  fspa[4]  + siginc;
fspa[6]=  fspa[5]  + siginc;
fspa[7]=  fspa[6]  + siginc;
fspa[8]=  fspa[7]  + siginc;
fspa[9]=  fspa[8]  + siginc;
fspa[10]= fspa[9]  + siginc;
fspa[11]= fspa[10] + siginc;
fspa[12]= sigmax;

for(i= 1; i <= iepanz; i++)
  {
  sigz= sep[i];
  if      (sigz >= fspa[1] && sigz <  fspa[2]) ifarbe[iep[i]]= 1;
  else if (sigz >= fspa[2] && sigz <  fspa[3]) ifarbe[iep[i]]= 2;
  else if (sigz >= fspa[3] && sigz <  fspa[4]) ifarbe[iep[i]]= 3;
  else if (sigz >= fspa[4] && sigz <  fspa[5]) ifarbe[iep[i]]= 4;
  else if (sigz >= fspa[5] && sigz <  fspa[6]) ifarbe[iep[i]]= 5;
  else if (sigz >= fspa[6] && sigz <  fspa[7]) ifarbe[iep[i]]= 6;
  else if (sigz >= fspa[7] && sigz <  fspa[8]) ifarbe[iep[i]]= 7;
  else if (sigz >= fspa[8] && sigz <  fspa[9]) ifarbe[iep[i]]= 8;
  else if (sigz >= fspa[9] && sigz <  fspa[10])ifarbe[iep[i]]= 9;
  else if (sigz >= fspa[10]&& sigz <  fspa[11])ifarbe[iep[i]]=10;
  else if (sigz >= fspa[11]&& sigz <= fspa[12])ifarbe[iep[i]]=11;
  }

return 0;
}

/***********************************************************************
* hier beginnt subroutine snow88: Farben fuer Spannungen pro Element
***********************************************************************/
int snow88(void)
{
extern FR_DOUBLEAY sne;

extern FR_DOUBLE   fspa[];

extern FR_DOUBLE   snemin,snemax,sneinc;

extern FR_INT4AY   jfarbe;

extern FR_INT4     ne;

FR_DOUBLE          sigz;

FR_INT4            i;

/*----------------------------------------------------------------------
* Farbregister auf Null 
*---------------------------------------------------------------------*/
for(i= 1; i <= ne; i++)
  jfarbe[i]= 0;

/*----------------------------------------------------------------------
* Minimal- und Maximalwerte feststellen
*---------------------------------------------------------------------*/
for(i= 1; i <= ne; i++)
  if(sne[i] > snemax) snemax= sne[i];

snemin= snemax;

for(i= 1; i <= ne; i++)
  if(sne[i] < snemin) snemin= sne[i];

/*----------------------------------------------------------------------
* Spannungsstufen berechnen
*---------------------------------------------------------------------*/
sneinc= (snemax-snemin)/11.;

fspa[1] = snemin;
fspa[2] = fspa[1]  + sneinc;
fspa[3] = fspa[2]  + sneinc;
fspa[4] = fspa[3]  + sneinc;
fspa[5] = fspa[4]  + sneinc;
fspa[6] = fspa[5]  + sneinc;
fspa[7] = fspa[6]  + sneinc;
fspa[8] = fspa[7]  + sneinc;
fspa[9] = fspa[8]  + sneinc;
fspa[10]= fspa[9]  + sneinc;
fspa[11]= fspa[10] + sneinc;
fspa[12]= snemax;

for(i= 1; i <= ne; i++)
  {
  sigz= sne[i];
  if      (sigz >= fspa[1] && sigz <  fspa[2]) jfarbe[i]= 1;
  else if (sigz >= fspa[2] && sigz <  fspa[3]) jfarbe[i]= 2;
  else if (sigz >= fspa[3] && sigz <  fspa[4]) jfarbe[i]= 3;
  else if (sigz >= fspa[4] && sigz <  fspa[5]) jfarbe[i]= 4;
  else if (sigz >= fspa[5] && sigz <  fspa[6]) jfarbe[i]= 5;
  else if (sigz >= fspa[6] && sigz <  fspa[7]) jfarbe[i]= 6;
  else if (sigz >= fspa[7] && sigz <  fspa[8]) jfarbe[i]= 7;
  else if (sigz >= fspa[8] && sigz <  fspa[9]) jfarbe[i]= 8;
  else if (sigz >= fspa[9] && sigz <  fspa[10])jfarbe[i]= 9;
  else if (sigz >= fspa[10]&& sigz <  fspa[11])jfarbe[i]=10;
  else if (sigz >= fspa[11]&& sigz <= fspa[12])jfarbe[i]=11;
  }

return 0;
}

/***********************************************************************
* hier beginnt subroutine spgp88: Farben fuer Spannungen in Gausspunkten
***********************************************************************/
int spgp88(void)
{
extern FR_DOUBLEAY siggp;

extern FR_DOUBLE   fspa[];

extern FR_DOUBLE   spamin,spamax,spainc;

extern FR_INT4AY   kfarbe;

extern FR_INT4     igpanz;

FR_DOUBLE          sigz;

FR_INT4            i;

/*----------------------------------------------------------------------
* Farbregister auf Null 
*---------------------------------------------------------------------*/
for(i= 1; i <= igpanz; i++)
  kfarbe[i]= 0;

/*----------------------------------------------------------------------
* Minimal- und Maximalwerte feststellen
*---------------------------------------------------------------------*/
for(i= 1; i <= igpanz; i++)
  if(siggp[i] > spamax) spamax= siggp[i];

spamin= spamax;

for(i= 1; i <= igpanz; i++)
  if(siggp[i] < spamin) spamin= siggp[i];

/*----------------------------------------------------------------------
* Spannungsstufen berechnen
*---------------------------------------------------------------------*/
spainc= (spamax-spamin)/11.;

fspa[1]=  spamin;
fspa[2]=  fspa[1]  + spainc;
fspa[3]=  fspa[2]  + spainc;
fspa[4]=  fspa[3]  + spainc;
fspa[5]=  fspa[4]  + spainc;
fspa[6]=  fspa[5]  + spainc;
fspa[7]=  fspa[6]  + spainc;
fspa[8]=  fspa[7]  + spainc;
fspa[9]=  fspa[8]  + spainc;
fspa[10]= fspa[9]  + spainc;
fspa[11]= fspa[10] + spainc;
fspa[12]= spamax;

for(i= 1; i <= igpanz; i++)
  {
  sigz= siggp[i];
  if      (sigz >= fspa[1] && sigz <  fspa[2]) kfarbe[i]= 1;
  else if (sigz >= fspa[2] && sigz <  fspa[3]) kfarbe[i]= 2;
  else if (sigz >= fspa[3] && sigz <  fspa[4]) kfarbe[i]= 3;
  else if (sigz >= fspa[4] && sigz <  fspa[5]) kfarbe[i]= 4;
  else if (sigz >= fspa[5] && sigz <  fspa[6]) kfarbe[i]= 5;
  else if (sigz >= fspa[6] && sigz <  fspa[7]) kfarbe[i]= 6;
  else if (sigz >= fspa[7] && sigz <  fspa[8]) kfarbe[i]= 7;
  else if (sigz >= fspa[8] && sigz <  fspa[9]) kfarbe[i]= 8;
  else if (sigz >= fspa[9] && sigz <  fspa[10])kfarbe[i]= 9;
  else if (sigz >= fspa[10]&& sigz <  fspa[11])kfarbe[i]=10;
  else if (sigz >= fspa[11]&& sigz <= fspa[12])kfarbe[i]=11;
  }

return 0;
}

/***********************************************************************
* hier beginnt Function fvx88
***********************************************************************/
int fvx88(void)
{
extern FR_DOUBLEAY ux;
extern FR_DOUBLE   fspa[];

extern FR_DOUBLE   fxmin,fxmax,fxinc;

extern FR_INT4AY   ifarbe;
extern FR_INT4     nkp,ipflag;

FR_DOUBLE          valx;

FR_INT4            i;

/*----------------------------------------------------------------------
* Farbregister auf Null 
*---------------------------------------------------------------------*/
for(i= 1; i <= nkp; i++)
  ifarbe[i]= 0;

/*----------------------------------------------------------------------
* Minimal- und Maximalwerte feststellen
*---------------------------------------------------------------------*/
/*======================================================================
* alles ausser Platten
*=====================================================================*/
if(ipflag == 0)
  {
  for(i= 1; i <= nkp; i++)
    if(ux[i] > fxmax) fxmax= ux[i];

  fxmin= fxmax;

  for(i= 1; i <= nkp; i++)
    if(ux[i] < fxmin) fxmin= ux[i];
  }

/*======================================================================
* Platten brauchen Sonderbehandlung
*=====================================================================*/
else
  {
  fxmin= 0.;
  fxmax= 0.;
  }

/*----------------------------------------------------------------------
* Farbstufen fuer die X- Verschiebungen berechnen
*---------------------------------------------------------------------*/
fxinc= (fxmax-fxmin)/11.;

fspa[1]=  fxmin;
fspa[2]=  fspa[1] + fxinc;
fspa[3]=  fspa[2] + fxinc;
fspa[4]=  fspa[3] + fxinc;
fspa[5]=  fspa[4] + fxinc;
fspa[6]=  fspa[5] + fxinc;
fspa[7]=  fspa[6] + fxinc;
fspa[8]=  fspa[7] + fxinc;
fspa[9]=  fspa[8] + fxinc;
fspa[10]= fspa[9] + fxinc;
fspa[11]= fspa[10]+ fxinc;
fspa[12]= fxmax;

for(i= 1; i <= nkp; i++)
  {
  valx= ux[i];
  if      (valx >= fspa[1] && valx <  fspa[2]) ifarbe[i]= 1;
  else if (valx >= fspa[2] && valx <  fspa[3]) ifarbe[i]= 2;
  else if (valx >= fspa[3] && valx <  fspa[4]) ifarbe[i]= 3;
  else if (valx >= fspa[4] && valx <  fspa[5]) ifarbe[i]= 4;
  else if (valx >= fspa[5] && valx <  fspa[6]) ifarbe[i]= 5;
  else if (valx >= fspa[6] && valx <  fspa[7]) ifarbe[i]= 6;
  else if (valx >= fspa[7] && valx <  fspa[8]) ifarbe[i]= 7;
  else if (valx >= fspa[8] && valx <  fspa[9]) ifarbe[i]= 8;
  else if (valx >= fspa[9] && valx <  fspa[10])ifarbe[i]= 9;
  else if (valx >= fspa[10]&& valx <  fspa[11])ifarbe[i]=10;
  else if (valx >= fspa[11]&& valx <= fspa[12])ifarbe[i]=11;
  }

return 0;
}

/***********************************************************************
* hier beginnt Function fvy88
***********************************************************************/
int fvy88(void)
{
extern FR_DOUBLEAY uy;
extern FR_DOUBLE   fspa[];

extern FR_DOUBLE   fymin,fymax,fyinc;

extern FR_INT4AY   ifarbe;
extern FR_INT4     nkp,ipflag;

FR_DOUBLE          valy;

FR_INT4            i;

/*----------------------------------------------------------------------
* Farbregister auf Null 
*---------------------------------------------------------------------*/
for(i= 1; i <= nkp; i++)
  ifarbe[i]= 0;

/*----------------------------------------------------------------------
* Minimal- und Maximalwerte feststellen
*---------------------------------------------------------------------*/
/*======================================================================
* alles ausser Platten
*=====================================================================*/
if(ipflag == 0)
  {
  for(i= 1; i <= nkp; i++)
    if(uy[i] > fymax) fymax= uy[i];

  fymin= fymax;

  for(i= 1; i <= nkp; i++)
    if(uy[i] < fymin) fymin= uy[i];
  }

/*======================================================================
* Platten brauchen Sonderbehandlung
*=====================================================================*/
else
  {
  fymin= 0.;
  fymax= 0.;
  }

/*----------------------------------------------------------------------
* Farbstufen fuer die Y- Verschiebungen berechnen
*---------------------------------------------------------------------*/
fyinc= (fymax-fymin)/11.;

fspa[1]=  fymin;
fspa[2]=  fspa[1]  + fyinc;
fspa[3]=  fspa[2]  + fyinc;
fspa[4]=  fspa[3]  + fyinc;
fspa[5]=  fspa[4]  + fyinc;
fspa[6]=  fspa[5]  + fyinc;
fspa[7]=  fspa[6]  + fyinc;
fspa[8]=  fspa[7]  + fyinc;
fspa[9]=  fspa[8]  + fyinc;
fspa[10]= fspa[9]  + fyinc;
fspa[11]= fspa[10] + fyinc;
fspa[12]= fymax;

for(i= 1; i <= nkp; i++)
  {
  valy= uy[i];
  if      (valy >= fspa[1] && valy <  fspa[2]) ifarbe[i]= 1;
  else if (valy >= fspa[2] && valy <  fspa[3]) ifarbe[i]= 2;
  else if (valy >= fspa[3] && valy <  fspa[4]) ifarbe[i]= 3;
  else if (valy >= fspa[4] && valy <  fspa[5]) ifarbe[i]= 4;
  else if (valy >= fspa[5] && valy <  fspa[6]) ifarbe[i]= 5;
  else if (valy >= fspa[6] && valy <  fspa[7]) ifarbe[i]= 6;
  else if (valy >= fspa[7] && valy <  fspa[8]) ifarbe[i]= 7;
  else if (valy >= fspa[8] && valy <  fspa[9]) ifarbe[i]= 8;
  else if (valy >= fspa[9] && valy <  fspa[10])ifarbe[i]= 9;
  else if (valy >= fspa[10]&& valy <  fspa[11])ifarbe[i]=10;
  else if (valy >= fspa[11]&& valy <= fspa[12])ifarbe[i]=11;
  }

return 0;
}

/***********************************************************************
* hier beginnt Function fvz88
***********************************************************************/
int fvz88(void)
{
extern FR_DOUBLEAY uz;
extern FR_DOUBLE   fspa[];

extern FR_DOUBLE   fzmin,fzmax,fzinc;

extern FR_INT4AY   ifarbe;
extern FR_INT4     nkp;

FR_DOUBLE          valz;

FR_INT4            i;

/*----------------------------------------------------------------------
* Farbregister auf Null 
*---------------------------------------------------------------------*/
for(i= 1; i <= nkp; i++)
  ifarbe[i]= 0;

/*----------------------------------------------------------------------
* Minimal- und Maximalwerte feststellen
*---------------------------------------------------------------------*/
for(i= 1; i <= nkp; i++)
  if(uz[i] > fzmax) fzmax= uz[i];

fzmin= fzmax;

for(i= 1; i <= nkp; i++)
  if(uz[i] < fzmin) fzmin= uz[i];

/*----------------------------------------------------------------------
* Farbstufen fuer die X- Verschiebungen berechnen
*---------------------------------------------------------------------*/
fzinc= (fzmax-fzmin)/11.;

fspa[1] = fzmin;
fspa[2] = fspa[1]  + fzinc;
fspa[3] = fspa[2]  + fzinc;
fspa[4] = fspa[3]  + fzinc;
fspa[5] = fspa[4]  + fzinc;
fspa[6] = fspa[5]  + fzinc;
fspa[7] = fspa[6]  + fzinc;
fspa[8] = fspa[7]  + fzinc;
fspa[9] = fspa[8]  + fzinc;
fspa[10]= fspa[9]  + fzinc;
fspa[11]= fspa[10] + fzinc;
fspa[12]= fzmax;

for(i= 1; i <= nkp; i++)
  {
  valz= uz[i];
  if      (valz >= fspa[1] && valz <  fspa[2]) ifarbe[i]= 1;
  else if (valz >= fspa[2] && valz <  fspa[3]) ifarbe[i]= 2;
  else if (valz >= fspa[3] && valz <  fspa[4]) ifarbe[i]= 3;
  else if (valz >= fspa[4] && valz <  fspa[5]) ifarbe[i]= 4;
  else if (valz >= fspa[5] && valz <  fspa[6]) ifarbe[i]= 5;
  else if (valz >= fspa[6] && valz <  fspa[7]) ifarbe[i]= 6;
  else if (valz >= fspa[7] && valz <  fspa[8]) ifarbe[i]= 7;
  else if (valz >= fspa[8] && valz <  fspa[9]) ifarbe[i]= 8;
  else if (valz >= fspa[9] && valz <  fspa[10])ifarbe[i]= 9;
  else if (valz >= fspa[10]&& valz <  fspa[11])ifarbe[i]=10;
  else if (valz >= fspa[11]&& valz <= fspa[12])ifarbe[i]=11;
  }

return 0;
}

