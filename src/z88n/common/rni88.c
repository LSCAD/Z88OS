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
* rni88.c liest Z88NI.TXT ein
* hier werden die Files Z88NI.TXT und Z88I1.TXT geoeffnet
* 21.7.2011 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88n.h>
#include <stdio.h>   /* FILE,NULL,fopen,rewind,fclose */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88n.h>
#include <stdio.h>   /* FILE,NULL,fopen,rewind,fclose */
#endif

/***********************************************************************
* Formatbeschreiber
***********************************************************************/	
#define PCB "%c "
#define PC "%c"

#ifdef FR_XINT
#define PDB "%d "
#define PD "%d"
#define PD5B "%5d "
#define PD5 "%5d"
#define PD2B "%2d "
#define PD2 "%2d"
#endif

#ifdef FR_XLONG
#define PDB "%ld "
#define PD "%ld"
#define PD5B "%5ld "
#define PD5 "%5ld"
#define PD2B "%2ld "
#define PD2 "%2ld"
#endif

#ifdef FR_XLOLO
#define PDB "%lld "
#define PD "%lld"
#define PD5B "%5lld "
#define PD5 "%5lld"
#define PD2B "%2lld "
#define PD2 "%2lld"
#endif

#ifdef FR_XDOUB
#define PFB "%lf "
#define PF "%lf"
#define PE13B "%+#13.5lE "
#define PE13 "%+#13.5lE"
#endif

#ifdef FR_XQUAD
#define PFB "%Lf "
#define PF "%Lf"
#define PE13B "%+#13.5LE "
#define PE13 "%+#13.5LE"
#endif

/***********************************************************************
* Functions
***********************************************************************/
int wrim88n(FR_INT4,int);
int wlog88n(FR_INT4,int);

/***********************************************************************
* hier beginnt Function rni88
***********************************************************************/
int rni88(void)
{
extern FILE *fni,*fi1,*fwlo;
extern char cni[];
extern char ci1[];

extern FR_DOUBLEAY xss;
extern FR_DOUBLEAY yss;
extern FR_DOUBLEAY zss;

extern FR_INT4AY koffss;
extern FR_INT4AY koiss;
extern FR_INT4AY jel;
extern FR_INT4AY iel;
extern FR_INT4AY kel;

extern FR_CHARAY cjmode;
extern FR_CHARAY cimode;
extern FR_CHARAY ckmode;

extern FR_DOUBLE epsx,epsy,epsz;

extern FR_INT4 MAXKSS,MAXESS;
extern FR_INT4 ndim,nkpss,ness,nfreis;
extern FR_INT4 kflagss,niflag,kflag;
extern FR_INT4 itypss,ityp,ifrei;

FR_DOUBLE radius,phi;
FR_INT4 i,idummy;

char cline[256];

/*----------------------------------------------------------------------
* Start Function
*---------------------------------------------------------------------*/
wrim88n(0,TX_REANI);
wlog88n(0,LOG_REANI);

/*----------------------------------------------------------------------
* Oeffnen Z88NI.TXT
*---------------------------------------------------------------------*/
wlog88n(0,LOG_OPENNI);
fni= fopen(cni,"r");
if(fni == NULL)
  {
  wlog88n(0,LOG_NONI);
  fclose(fwlo);
  return(AL_NONI);
  }
rewind(fni);

/*----------------------------------------------------------------------
* Oeffnen Z88I1.TXT
*---------------------------------------------------------------------*/
wlog88n(0,LOG_OPENI1);
fi1= fopen(ci1,"w+");
if(fi1 == NULL)
  {
  wlog88n(0,LOG_NOI1);
  fclose(fwlo);
  return(AL_NOI1);
  }
rewind(fi1);

/*----------------------------------------------------------------------
* Einlesen der allgemeinen Strukturdaten
*---------------------------------------------------------------------*/
fgets(cline,256,fni);
sscanf(cline,PDB PDB PDB PDB PDB PDB PD,
       &ndim,&nkpss,&ness,&nfreis,&kflagss,&niflag,&kflag);

/***********************************************************************
* Einlesen der Koordinaten der Superelemente
***********************************************************************/
if(ndim== 3)
  {
  for(i= 1; i <= nkpss; i++)
    {
    fgets(cline,256,fni);
    sscanf(cline,PDB PDB PFB PFB PF,&idummy,&ifrei,&xss[i],&yss[i],&zss[i]); 
    }
  }
else
  {
  for(i= 1; i <= nkpss; i++)
    {
    fgets(cline,256,fni);
    sscanf(cline,PDB PDB PFB PF,&idummy,&ifrei,&xss[i],&yss[i]); 
    }
  }

/*----------------------------------------------------------------------
* ggf auf kartesische Koordinaten umrechnen
*---------------------------------------------------------------------*/
if(kflagss == 1) 
  {
  for(i= 1; i <= nkpss; i++)
     {
     radius= xss[i];
     phi= 3.141593/180.* yss[i];
     xss[i]= radius*FR_COS(phi);
     yss[i]= radius*FR_SIN(phi);
     }
   }

/***********************************************************************
* Einlesen der Koinzidenz der Superelemente
***********************************************************************/
for(i= 1; i <= ness; i++)
  {
  fgets(cline,256,fni);
  sscanf(cline,PDB PD,&idummy,&itypss); 
          
/*----------------------------------------------------------------------
* den Koinzidenzvektor koi & den zugehoerigen Pointervektor koffs
* auffuellen
*---------------------------------------------------------------------*/
/*======================================================================
* Elementtypen 1,7,8 & 20
*=====================================================================*/
  if(itypss== 1 || itypss== 7 || itypss== 8 || itypss== 20) 
    {
    if(i== 1) koffss[1]= 1;
    else      koffss[i]= koffss[i-1] + 8;

    fgets(cline,256,fni);
    sscanf(cline,PDB PDB PDB PDB PDB PDB PDB PD,
    &koiss[koffss[i]   ], &koiss[koffss[i] +1], 
    &koiss[koffss[i] +2], &koiss[koffss[i] +3], 
    &koiss[koffss[i] +4], &koiss[koffss[i] +5], 
    &koiss[koffss[i] +6], &koiss[koffss[i] +7]); 
    }
          
/*======================================================================
* Elementtypen 10
*=====================================================================*/
  if(itypss== 10)
    {
    if(i== 1) koffss[1]= 1;
    else      koffss[i]= koffss[i-1] + 20;

    fgets(cline,256,fni);
    sscanf(cline,PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB
 PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &koiss[koffss[i]   ],  &koiss[koffss[i] +1], 
    &koiss[koffss[i] +2],  &koiss[koffss[i] +3], 
    &koiss[koffss[i] +4],  &koiss[koffss[i] +5], 
    &koiss[koffss[i] +6],  &koiss[koffss[i] +7], 
    &koiss[koffss[i] +8],  &koiss[koffss[i] +9], 
    &koiss[koffss[i] +10], &koiss[koffss[i] +11], 
    &koiss[koffss[i] +12], &koiss[koffss[i] +13], 
    &koiss[koffss[i] +14], &koiss[koffss[i] +15], 
    &koiss[koffss[i] +16], &koiss[koffss[i] +17], 
    &koiss[koffss[i] +18], &koiss[koffss[i] +19]); 
    }

/*======================================================================
* Elementtypen 21
*=====================================================================*/
  if(itypss== 21)
    {
    if(i== 1) koffss[1]= 1;
    else      koffss[i]= koffss[i-1] + 16;

    fgets(cline,256,fni);
    sscanf(cline,PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB
 PDB PDB PDB PDB PDB PD,
    &koiss[koffss[i]   ],  &koiss[koffss[i] +1], 
    &koiss[koffss[i] +2],  &koiss[koffss[i] +3], 
    &koiss[koffss[i] +4],  &koiss[koffss[i] +5], 
    &koiss[koffss[i] +6],  &koiss[koffss[i] +7], 
    &koiss[koffss[i] +8],  &koiss[koffss[i] +9], 
    &koiss[koffss[i] +10], &koiss[koffss[i] +11], 
    &koiss[koffss[i] +12], &koiss[koffss[i] +13], 
    &koiss[koffss[i] +14], &koiss[koffss[i] +15]); 
    }

/*======================================================================
* Elementtypen 11 & 12
*=====================================================================*/
  if(itypss== 11 || itypss== 12) 
    {
    if(i== 1) koffss[1]= 1;
    else      koffss[i]= koffss[i-1] + 12;

    fgets(cline,256,fni);
    sscanf(cline,PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &koiss[koffss[i]    ], &koiss[koffss[i] + 1], 
    &koiss[koffss[i] + 2], &koiss[koffss[i] + 3], 
    &koiss[koffss[i] + 4], &koiss[koffss[i] + 5], 
    &koiss[koffss[i] + 6], &koiss[koffss[i] + 7], 
    &koiss[koffss[i] + 8], &koiss[koffss[i] + 9], 
    &koiss[koffss[i] +10], &koiss[koffss[i] +11]); 
    }

  }  /* ende schleife ness */

/*----------------------------------------------------------------------
* join & jel & iel der Superelemente einlesen
*---------------------------------------------------------------------*/
for(i= 1; i <= ness; i++)
  {
  fgets(cline,256,fni);
  sscanf(cline,PDB PD,&idummy,&ityp);
  fgets(cline,256,fni);
  sscanf(cline,PDB PCB PDB PCB PDB PC,
  &jel[i],&cjmode[i],&iel[i],&cimode[i],&kel[i],&ckmode[i]);
  }

/*----------------------------------------------------------------------
* ggf. neue Fangbereiche einlesen 
*---------------------------------------------------------------------*/
if(niflag == 1)
  {
  fgets(cline,256,fni);
  sscanf(cline,PFB PFB PF,&epsx,&epsy,&epsz);
  }

/*----------------------------------------------------------------------
* Z88NI.TXT schliessen 
*---------------------------------------------------------------------*/
fclose(fni);

wlog88n(0,LOG_EXITRNI88);
return (0);
}

