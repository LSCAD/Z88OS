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
* rea88x 
* 10.1.2012 Rieg 
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88x.h>
#include <stdio.h>    /* fopen,fclose,fprintf,fgets,sscanf */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88x.h>
#include <stdio.h>    /* fopen,fclose,fprintf,fgets,sscanf */
#endif

/***********************************************************************
* Formatbeschreiber
***********************************************************************/	
#define PC "%c"
#define PCB "%c "


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
#define PFB "%lf "
#define PF "%lf"
#endif

#ifdef FR_XQUAD
#define PFB "%Lf "
#define PF "%Lf"
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88x(FR_INT4,int);
int wlog88x(FR_INT4,int);
void stop88x(void);
int ale88x(int);

/***********************************************************************
* hier beginnt Function rea88x
* rea88x.c liest z88ni.txt oder z88i1.txt,ggf. z88i2.txt und z88i5.txt
* ein. Die Files Z88NI.TXT oder Z88I1.TXT,ggf. Z88I2.TXT und Z88I5.TXT
* oeffnen
***********************************************************************/
int rea88x(void)
{
extern FILE *fz88,*fwlo,*fi2,*fi5;
extern char ci1[],ci2[],ci5[],cni[];

extern FR_DOUBLEAY x;
extern FR_DOUBLEAY y;
extern FR_DOUBLEAY z;
extern FR_DOUBLEAY wert;
extern FR_DOUBLEAY pres;
extern FR_DOUBLEAY tr1;
extern FR_DOUBLEAY tr2;

extern FR_INT4AY koi;
extern FR_INT4AY ifrei; 
extern FR_INT4AY koffs;
extern FR_INT4AY ityp;
extern FR_INT4AY itypfe;
extern FR_INT4AY jel;
extern FR_INT4AY iel;
extern FR_INT4AY kel;
extern FR_INT4AY nkn;
extern FR_INT4AY ifg;
extern FR_INT4AY irflag;
extern FR_INT4AY noi;
extern FR_INT4AY noffs;
extern FR_INT4AY nep;

extern FR_CHARAY cjmode;
extern FR_CHARAY cimode;
extern FR_CHARAY ckmode;

extern FR_DOUBLE epsx,epsy,epsz;

extern FR_INT4 ndim,nkp,ne,nfg,kflagss,kflag,iqflag,niflag;
extern FR_INT4 nrb,npr;
extern FR_INT4 MAXNFG,MAXK,MAXE,MAXKOI,MAXPR;
extern FR_INT4 ICFLAG;

FR_DOUBLE radius,phi;
FR_INT4 i,idummy,kofold= 0,nofold= 0;

int iret;

char cline[256];

/*----------------------------------------------------------------------
* Start Function
*---------------------------------------------------------------------*/
wlog88x(0,LOG_BREA88);

/*----------------------------------------------------------------------
* Entweder Oeffnen Z88I1.TXT oder ..
*---------------------------------------------------------------------*/
if(ICFLAG == 1 || ICFLAG == 2)
  {
  wlog88x(0,LOG_FI1);
  wrim88x(0,TX_REAI1);
  fz88= fopen(ci1,"r");
  if(fz88 == NULL)
    {
    wlog88x(0,LOG_NOI1);
    fclose(fwlo);
    return(AL_NOI1);
    }
  rewind(fz88);
  }

/*----------------------------------------------------------------------
* .. oder Oeffnen Z88NI.TXT
*---------------------------------------------------------------------*/
if(ICFLAG == 3)
  {
  wlog88x(0,LOG_FNI);
  wrim88x(0,TX_REANI);
  fz88= fopen(cni,"r");
  if(fz88 == NULL)
    {
    wlog88x(0,LOG_NONI);
    fclose(fwlo);
    return(AL_NONI);
    }
  rewind(fz88);
  }

/*----------------------------------------------------------------------
* Einlesen der allgemeinen Strukturdaten
*---------------------------------------------------------------------*/
fgets(cline,256,fz88);
if(ICFLAG == 1 || ICFLAG == 2)
  sscanf(cline,PDB PDB PDB PDB PD,&ndim,&nkp,&ne,&nfg,&kflag);
else
  sscanf(cline,PDB PDB PDB PDB PDB PDB PD,&ndim,&nkp,&ne,&nfg,&kflagss,&niflag,&kflag);

/*----------------------------------------------------------------------
* Testen, ob innerhalb der zulaessigen Grenzen
*---------------------------------------------------------------------*/
if(!(ndim == 2 || ndim == 3))
  {
  wlog88x(ndim,LOG_WRONGDIM);
  fclose(fwlo);
  return(AL_WRONDIM);
  }

if(!(ndim == 2 || ndim == 3))
  {
  wlog88x(ndim,LOG_WRONGDIM);
  fclose(fwlo);
  return(AL_WRONDIM);
  }

if(nkp > MAXK)
  {
  wlog88x(MAXK,LOG_EXMAXK);
  fclose(fwlo);
  return(AL_EXMAXK);
  }

if(ne > MAXE)
  {
  wlog88x(MAXE,LOG_EXMAXE);
  fclose(fwlo);
  return(AL_EXMAXE);
  }

if((ne*20) > MAXKOI)
  {
  wlog88x(MAXKOI,LOG_EXMAXKOI);
  fclose(fwlo);
  return(AL_EXKOI);
  }

if(nfg > MAXNFG)
  {
  wlog88x(MAXNFG,LOG_EXMAXNFG);
  fclose(fwlo);
  return(AL_EXMAXNFG);
  }

if(!(kflag == 0 || kflag == 1))
  {
  wlog88x(kflag,LOG_WROKFLAG);
  fclose(fwlo);
  return(AL_WROKFLAG);
  }
/***********************************************************************
* Einlesen der Koordinaten
***********************************************************************/
wrim88x(0,TX_KOOR);
wlog88x(0,LOG_KOOR);

if(ndim== 3)
  {
  for(i= 1; i <= nkp; i++)
    {
    fgets(cline,256,fz88);
    sscanf(cline,PDB PDB PFB PFB PF,&idummy,&ifrei[i],&x[i],&y[i],&z[i]); 
    }
  }
else
  {
  for(i= 1; i <= nkp; i++)
    {
    fgets(cline,256,fz88);
    sscanf(cline,PDB PDB PFB PF,&idummy,&ifrei[i],&x[i],&y[i]); 
    }
  }

/***********************************************************************
* einlesen der koinzidenz
***********************************************************************/
wrim88x(0,TX_KOIN);
wlog88x(0,LOG_KOIN);

for(i= 1; i <= ne; i++)
  {
  fgets(cline,256,fz88);
  sscanf(cline,PDB PD,&idummy,&ityp[i]);         

/*----------------------------------------------------------------------
* den koinzidenzvektor koi & den zugehoerigen pointervektor koffs
* auffuellen
*---------------------------------------------------------------------*/
/*======================================================================
* elementtypen 1, 7, 8, 20, 23
*=====================================================================*/
  if(ityp[i]== 1  || ityp[i]== 7 || ityp[i]== 8 || 
     ityp[i]== 20 || ityp[i]== 23) 
    {
    if(i== 1)  koffs[1]= 1;
    else       koffs[i]= koffs[i-1] + kofold;

    fgets(cline,256,fz88);
    sscanf(cline,PDB PDB PDB PDB PDB PDB PDB PD,
    &koi[koffs[i]   ], &koi[koffs[i] +1], 
    &koi[koffs[i] +2], &koi[koffs[i] +3], 
    &koi[koffs[i] +4], &koi[koffs[i] +5], 
    &koi[koffs[i] +6], &koi[koffs[i] +7]); 

    kofold= 8;
    }
          
/*======================================================================
* elementtypen 2, 4, 5 , 9 & 13
*=====================================================================*/
  if(ityp[i]== 2 || ityp[i]== 4 || ityp[i]== 5 ||
     ityp[i]== 9 || ityp[i]== 13)
    {
    if(i== 1)  koffs[1]= 1;
    else       koffs[i]= koffs[i-1] + kofold;

    fgets(cline,256,fz88);
    sscanf(cline,PDB PD,
    &koi[koffs[i]   ], &koi[koffs[i] +1]); 
            
    kofold= 2;
    }
                  
/*======================================================================
* elementtypen 3, 14, 15, 18 & 24
*=====================================================================*/
  if(ityp[i]== 3  || ityp[i]== 14 || ityp[i]== 15  || 
     ityp[i]== 18 || ityp[i]== 24)
    {
    if(i== 1)  koffs[1]= 1;
    else       koffs[i]= koffs[i-1] + kofold;

    fgets(cline,256,fz88);
    sscanf(cline,PDB PDB PDB PDB PDB PD,
    &koi[koffs[i]   ], &koi[koffs[i] +1], 
    &koi[koffs[i] +2], &koi[koffs[i] +3], 
    &koi[koffs[i] +4], &koi[koffs[i] +5]); 
            
    kofold= 6;
    }
          
/*======================================================================
* elementtyp 6
*=====================================================================*/
  if(ityp[i]== 6)
    {
    if(i== 1)  koffs[1]= 1;
    else       koffs[i]= koffs[i-1] + kofold;

    fgets(cline,256,fz88);
    sscanf(cline,PDB PDB PD,
    &koi[koffs[i]], &koi[koffs[i]+1],&koi[koffs[i]+2]);
            
    kofold= 3;
    }

/*======================================================================
* elementtyp 16
*=====================================================================*/
  if(ityp[i]== 16)
    {
    if(i== 1)  koffs[1]= 1;
    else       koffs[i]= koffs[i-1] + kofold;

    fgets(cline,256,fz88);
    sscanf(cline,PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &koi[koffs[i]    ], &koi[koffs[i] + 1], 
    &koi[koffs[i] + 2], &koi[koffs[i] + 3], 
    &koi[koffs[i] + 4], &koi[koffs[i] + 5], 
    &koi[koffs[i] + 6], &koi[koffs[i] + 7], 
    &koi[koffs[i] + 8], &koi[koffs[i] + 9]); 

    kofold= 10;
    }

/*======================================================================
* elementtyp 17
*=====================================================================*/
  if(ityp[i]== 17)
    {
    if(i== 1)  koffs[1]= 1;
    else       koffs[i]= koffs[i-1] + kofold;

    fgets(cline,256,fz88);
    sscanf(cline,PDB PDB PDB PD,
    &koi[koffs[i]    ], &koi[koffs[i] + 1], 
    &koi[koffs[i] + 2], &koi[koffs[i] + 3]); 

    kofold= 4;
    }
          
/*======================================================================
* elementtyp 10
*=====================================================================*/
  if(ityp[i]== 10)
    {
    if(i== 1)  koffs[1]= 1;
    else       koffs[i]= koffs[i-1] + kofold;

    fgets(cline,256,fz88);
    sscanf(cline,PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB
 PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &koi[koffs[i]    ], &koi[koffs[i] + 1], 
    &koi[koffs[i] + 2], &koi[koffs[i] + 3], 
    &koi[koffs[i] + 4], &koi[koffs[i] + 5], 
    &koi[koffs[i] + 6], &koi[koffs[i] + 7], 
    &koi[koffs[i] + 8], &koi[koffs[i] + 9], 
    &koi[koffs[i] +10], &koi[koffs[i] +11], 
    &koi[koffs[i] +12], &koi[koffs[i] +13], 
    &koi[koffs[i] +14], &koi[koffs[i] +15], 
    &koi[koffs[i] +16], &koi[koffs[i] +17], 
    &koi[koffs[i] +18], &koi[koffs[i] +19]); 

    kofold= 20;
    }

/*======================================================================
* elementtypen 11 & 12 & 22
*=====================================================================*/
  if(ityp[i]== 11 || ityp[i]== 12 || ityp[i]== 22) 
    {
    if(i== 1)  koffs[1]= 1;
    else       koffs[i]= koffs[i-1] + kofold;

    fgets(cline,256,fz88);
    sscanf(cline,PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &koi[koffs[i]    ], &koi[koffs[i] + 1], 
    &koi[koffs[i] + 2], &koi[koffs[i] + 3], 
    &koi[koffs[i] + 4], &koi[koffs[i] + 5], 
    &koi[koffs[i] + 6], &koi[koffs[i] + 7], 
    &koi[koffs[i] + 8], &koi[koffs[i] + 9], 
    &koi[koffs[i] +10], &koi[koffs[i] +11]); 

    kofold= 12;
    }

/*======================================================================
* elementtypen 19 u. 21
*=====================================================================*/
  if(ityp[i]== 19 || ityp[i]== 21) 
    {
    if(i== 1)  koffs[1]= 1;
    else       koffs[i]= koffs[i-1] + kofold;

    fgets(cline,256,fz88);
    sscanf(cline,
    PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &koi[koffs[i]    ], &koi[koffs[i] + 1], 
    &koi[koffs[i] + 2], &koi[koffs[i] + 3], 
    &koi[koffs[i] + 4], &koi[koffs[i] + 5], 
    &koi[koffs[i] + 6], &koi[koffs[i] + 7], 
    &koi[koffs[i] + 8], &koi[koffs[i] + 9], 
    &koi[koffs[i] +10], &koi[koffs[i] +11],
    &koi[koffs[i] +12], &koi[koffs[i] +13],
    &koi[koffs[i] +14], &koi[koffs[i] +15]); 

    kofold= 16;
    }

  } 

/*----------------------------------------------------------------------
* wenn Z88NI.TXT: Zerlegungs-Infos einlesen
*---------------------------------------------------------------------*/
if(ICFLAG == 3)
  {
  wrim88x(0,TX_SINFO);
  wlog88x(0,LOG_SINFO);
  for(i= 1; i <= ne; i++)
    {
    fgets(cline,256,fz88);
    sscanf(cline,PDB PD,&idummy,&itypfe[i]);
    fgets(cline,256,fz88);

    if(ityp[i] == 1 || ityp[i] == 10 || ityp[i] == 21)
      {
      sscanf(cline,PDB PCB PDB PCB PDB PC,
      &jel[i],&cjmode[i],&iel[i],&cimode[i],&kel[i],&ckmode[i]);
      }
    else
      {
      sscanf(cline,PDB PCB PDB PC,
      &jel[i],&cjmode[i],&iel[i],&cimode[i]);
      }

    }
/*======================================================================
* ggf. neue Fangbereiche einlesen
*=====================================================================*/
  if(niflag == 1)
    {
    fgets(cline,256,fz88);
    sscanf(cline,PFB PFB PF,&epsx,&epsy,&epsz);
    }
  }

/*----------------------------------------------------------------------
* Z88I1.TXT bzw Z88NI.TXT schliessen 
*---------------------------------------------------------------------*/
fclose(fz88);

/*----------------------------------------------------------------------
* ggf. Oeffnen und Lesen von Z88I2.TXT und Z88I5.TXT
*---------------------------------------------------------------------*/
if(ICFLAG == 2)
  {
/*=====================================================================
* zunaechst Z88I2.TXT ..
*=====================================================================*/
  wlog88x(0,LOG_FI2);
  wrim88x(0,TX_REAI2);
  fi2= fopen(ci2,"r");
  if(fi2 == NULL)
    {
    wlog88x(0,LOG_NOI2);
    fclose(fwlo);
    return(AL_NOI2);
    }
  rewind(fi2);

  fgets(cline,256,fi2);
  sscanf(cline,PD,&nrb);

  for(i = 1;i <= nrb;i++)
    {
    fgets(cline,256,fi2);
    sscanf(cline,PDB PDB PDB PF,&nkn[i],&ifg[i],&irflag[i],&wert[i]);
    }

  fclose(fi2);

/*=====================================================================
* zum Schluss Z88I5.TXT ..
*=====================================================================*/
  wlog88x(0,LOG_FI5);
  wrim88x(0,TX_REAI5);
  fi5= fopen(ci5,"r");
  if(fi5 == NULL)
    {
    wlog88x(0,LOG_NOI5);
    fclose(fwlo);
    return(AL_NOI5);
    }
  rewind(fi5);

  fgets(cline,256,fi5);
  sscanf(cline,PD,&npr);

  if(npr > 0) iqflag= 1;
  else        iqflag= 0;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Wenn Flaechenlasten, dann
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  if(iqflag == 1)
    {

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Schleife ueber alle Elemente mit Flaechenlasten
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    for(i = 1;i <= npr;i++)
      {
      fgets(cline,256,fi5);
      sscanf(cline,PD,&nep[i]); 

/*======================================================================
* Elementtypen 7, 8, 14, 15
*=====================================================================*/
      if(ityp[nep[i]]== 7  || ityp[nep[i]]== 8 ||
         ityp[nep[i]]== 14 || ityp[nep[i]]== 15) 
        {
        if(i== 1)  noffs[1]= 1;
        else       noffs[i]= noffs[i-1] + nofold;
    
        sscanf(cline,PDB PFB PFB PDB PDB PD,
        &idummy,&pres[i],&tr1[i],
        &noi[noffs[i]   ],&noi[noffs[i] +1],&noi[noffs[i] +2]);  

        nofold= 3;
        }

/*======================================================================
* Elementtypen 10 u. 21
*=====================================================================*/
      if(ityp[nep[i]]== 10 || ityp[nep[i]]== 21) 
        {
        if(i== 1)  noffs[1]= 1;
        else       noffs[i]= noffs[i-1] + nofold;
    
        sscanf(cline,PDB PFB PFB PFB PDB PDB PDB PDB PDB PDB PDB PD,
        &idummy,&pres[i],&tr1[i],&tr2[i],
        &noi[noffs[i]   ], &noi[noffs[i] +1], 
        &noi[noffs[i] +2], &noi[noffs[i] +3], 
        &noi[noffs[i] +4], &noi[noffs[i] +5],
        &noi[noffs[i] +6], &noi[noffs[i] +7]); 

        nofold= 8;
        }

/*======================================================================
* Elementtyp 22
*=====================================================================*/
      if(ityp[nep[i]]== 22) 
        {
        if(i== 1)  noffs[1]= 1;
        else       noffs[i]= noffs[i-1] + nofold;
    
        sscanf(cline,PDB PFB PFB PFB PDB PDB PDB PDB PDB PD,
        &idummy,&pres[i],&tr1[i],&tr2[i],
        &noi[noffs[i]   ], &noi[noffs[i] +1], 
        &noi[noffs[i] +2], &noi[noffs[i] +3], 
        &noi[noffs[i] +4], &noi[noffs[i] +5]); 

        nofold= 6;
        }

/*======================================================================
* Elementtyp 1
*=====================================================================*/
      if(ityp[nep[i]]== 1) 
        {
        if(i== 1)  noffs[1]= 1;
        else       noffs[i]= noffs[i-1] + nofold;
    
        sscanf(cline,PDB PFB PFB PFB PDB PDB PDB PD,
        &idummy,&pres[i],&tr1[i],&tr2[i],
        &noi[noffs[i]   ], &noi[noffs[i] +1], 
        &noi[noffs[i] +2], &noi[noffs[i] +3]); 

        nofold= 4;
        }

/*======================================================================
* Elementtyp 16
*=====================================================================*/
      if(ityp[nep[i]]== 16) 
        {
        if(i== 1)  noffs[1]= 1;
        else       noffs[i]= noffs[i-1] + nofold;
    
        sscanf(cline,PDB PFB PDB PDB PDB PDB PDB PD,
        &idummy,&pres[i],
        &noi[noffs[i]   ], &noi[noffs[i] +1], 
        &noi[noffs[i] +2], &noi[noffs[i] +3], 
        &noi[noffs[i] +4], &noi[noffs[i] +5]); 

        nofold= 6;
        }

/*======================================================================
* Elementtyp 17
*=====================================================================*/
      if(ityp[nep[i]]== 17) 
        {
        if(i== 1)  noffs[1]= 1;
        else       noffs[i]= noffs[i-1] + nofold;
    
        sscanf(cline,PDB PFB PDB PDB PD,&idummy,&pres[i],
        &noi[noffs[i]],&noi[noffs[i]+1],&noi[noffs[i]+2]); 

        nofold= 3;
        }

/*======================================================================
* Elementtypen 11 und 12
*=====================================================================*/
      if(ityp[nep[i]]== 11 || ityp[nep[i]]== 12) 
        {
        if(i== 1)  noffs[1]= 1;
        else       noffs[i]= noffs[i-1] + nofold;
 
        sscanf(cline,PDB PFB PFB PDB PDB PDB PD,
        &idummy,&pres[i],&tr1[i],
        &noi[noffs[i]   ], &noi[noffs[i] +1], 
        &noi[noffs[i] +2], &noi[noffs[i] +3]); 

        nofold= 4;
        }

/*======================================================================
* Elementtyp 18,19,20,23 & 24
*=====================================================================*/
      if(ityp[nep[i]]== 18 || ityp[nep[i]]== 19 || ityp[nep[i]]== 20 ||
         ityp[nep[i]]== 23 || ityp[nep[i]]== 24) 
        {
        sscanf(cline,PDB PF,&idummy,&pres[i]); 
        }

      } /* Ende Schleife */

    fclose(fi5);
    } /* Ende iqflag */

  }  /* Ende ICFLAG */

wlog88x(0,LOG_EXITREA88);
return (0);
}


