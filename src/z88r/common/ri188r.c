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
* ri188r - Einlesen von Z88I1.TXT fuer Z88R
* 17.7.2011 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX 
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>    /* fopen,fclose,fprintf,fgets,sscanf */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <stdio.h>    /* fopen,fclose,fprintf,fgets,sscanf */
#endif

/***********************************************************************
* Fuer Windows und GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88r.h>
#include <stdio.h>    /* fopen,fclose,fprintf,fgets,sscanf */
#endif

/***********************************************************************
* Leseformate
***********************************************************************/
#ifdef FR_XINT
#define PDB "%d "
#define PDE "%d"
#endif

#ifdef FR_XLONG
#define PDB "%ld "
#define PDE "%ld"
#endif

#ifdef FR_XLOLO
#define PDB "%lld "
#define PDE "%lld"
#endif

#ifdef FR_XDOUB
#define PGB "%lg "
#define PGE "%lg"
#endif

#ifdef FR_XQUAD
#define PGB "%Lg "
#define PGE "%Lg"
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88r(FR_INT4,int);
int wlog88r(FR_INT4,int);

/***********************************************************************
* hier beginnt Function ri188r
* ri188r.c liest z88i1.txt ein
* hier wird File z88i1.txt geoeffnet 
***********************************************************************/
int ri188r(void)
{
  extern FILE *fi1,*fwlo;
  extern char ci1[];

  extern FR_DOUBLEAY x;
  extern FR_DOUBLEAY y;
  extern FR_DOUBLEAY z;

  extern FR_INT4AY koi;
  extern FR_INT4AY ifrei; 
  extern FR_INT4AY koffs;
  extern FR_INT4AY ityp;

  extern FR_INT4   jetyp[];

  extern FR_INT4 ndim,nkp,ne,nfg,kflag;
  extern FR_INT4 MAXNFG,MAXK,MAXE,MAXKOI;

  FR_DOUBLE radius,phi;
  FR_INT4 i,idummy,kofold= 0;

  int iret;

  char cline[256];

  /*----------------------------------------------------------------------
  * Start Function
  *---------------------------------------------------------------------*/
  wrim88r(0,TX_REAI1);

  /*----------------------------------------------------------------------
  * jetyp[] nullen
  *---------------------------------------------------------------------*/
  for(i= 1; i <= 24; i++)
    jetyp[i]= 0;

  /*----------------------------------------------------------------------
  * Oeffnen Z88I1.TXT
  *---------------------------------------------------------------------*/
  wlog88r(0,LOG_BRI188);
  fi1= fopen(ci1,"r");
  if(fi1 == NULL)
  {
    wlog88r(0,LOG_NOI1);
    fclose(fwlo);
    return(AL_NOI1);
  }

  rewind(fi1);

  /*----------------------------------------------------------------------
  * Einlesen der allgemeinen Strukturdaten
  *---------------------------------------------------------------------*/
  fgets(cline,256,fi1);
  sscanf(cline,PDB PDB PDB PDB PDB,&ndim,&nkp,&ne,&nfg,&kflag);

  /*----------------------------------------------------------------------
  * Testen, ob innerhalb der zulaessigen Grenzen
  *---------------------------------------------------------------------*/
  if(!(ndim == 2 || ndim == 3))
  {
    wlog88r(ndim,LOG_WRONGDIM);
    fclose(fwlo);
    return(AL_WRONDIM);
  }

  if(nkp > MAXK)
  {
    wlog88r(MAXK,LOG_EXMAXK);
    fclose(fwlo);
    return(AL_EXMAXK);
  }

  if(ne > MAXE)
  {
    wlog88r(MAXE,LOG_EXMAXE);
    fclose(fwlo);
    return(AL_EXMAXE);
  }

  if(nfg > MAXNFG)
  {
    wlog88r(MAXNFG,LOG_EXMAXNFG);
    fclose(fwlo);
    return(AL_EXMAXNFG);
  }

  if(!(kflag == 0 || kflag == 1))
  {
    wlog88r(kflag,LOG_WROKFLAG);
    fclose(fwlo);
    return(AL_WROKFLAG);
  }

  /***********************************************************************
  * Einlesen der Koordinaten
  ***********************************************************************/
  wrim88r(0,TX_KOOR);
  wlog88r(0,LOG_KOOR);

  if(ndim == 3)
  {
    for(i= 1; i <= nkp; i++)
    {
      fgets(cline,256,fi1);
      sscanf(cline,PDB PDB PGB PGB PGE,&idummy,&ifrei[i],&x[i],&y[i],&z[i]);
    }
  }
  else
  {
    for(i= 1; i <= nkp; i++)
    {
      fgets(cline,256,fi1);
      sscanf(cline,PDB PDB PGB PGE,&idummy,&ifrei[i],&x[i],&y[i]);
    }
  }

  /*----------------------------------------------------------------------
  * ggf auf kartesische koordinaten umrechnen
  *---------------------------------------------------------------------*/
  if(kflag == 1) 
  {
    wrim88r(0,TX_POLAR);
    for(i= 1; i <= nkp; i++)
    {
      radius= x[i];
      phi= 3.141593/180.* y[i];
      x[i]= radius*FR_COS(phi);
      y[i]= radius*FR_SIN(phi);
    }
  }

  /***********************************************************************
  * einlesen der koinzidenz
  ***********************************************************************/
  wrim88r(0,TX_KOIN);
  wlog88r(0,LOG_KOIN);

  for(i= 1; i <= ne; i++)
  {
    fgets(cline,256,fi1);
    sscanf(cline,PDB PDE,&idummy,&ityp[i]); 

    /*----------------------------------------------------------------------
    * den elementtyp-summationsvektor jetyp fuellen
    *---------------------------------------------------------------------*/
    if(ityp[i] >= 1 && ityp[i] <= 24) 
      jetyp[ityp[i]]++;

    /*----------------------------------------------------------------------
    * den koinzidenzvektor koi & den zugehoerigen pointervektor koffs
    * auffuellen
    *---------------------------------------------------------------------*/
    /*======================================================================
    * elementtypen 1, 7, 8, 20 und 23
    *=====================================================================*/
    if(ityp[i]== 1  || ityp[i]== 7 || ityp[i]== 8 || 
       ityp[i]== 20 || ityp[i]== 23) 
    {
      if(i== 1)  
        koffs[1]= 1;
      else       
        koffs[i]= koffs[i-1] + kofold;
      
      if(koffs[i]+8 >= MAXKOI-1)
      {
        wlog88r(MAXKOI,LOG_EXKOI);
        fclose(fwlo);
        return(AL_EXKOI);
      }
   
      fgets(cline,256,fi1);

      sscanf(cline,PDB PDB PDB PDB PDB PDB PDB PDE,
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
      if(i== 1)  
        koffs[1]= 1;
      else       
        koffs[i]= koffs[i-1] + kofold;

      if(koffs[i]+2 >= MAXKOI-1)
      {
        wlog88r(MAXKOI,LOG_EXKOI);
        fclose(fwlo);
        return(AL_EXKOI);
      }

      fgets(cline,256,fi1);

      sscanf(cline,PDB PDE,
      &koi[koffs[i]   ], &koi[koffs[i] +1]); 
              
      kofold= 2;
    }
                    
    /*======================================================================
    * elementtyp 3, 14,15,18 & 24
    *=====================================================================*/
    if(ityp[i]== 3  || ityp[i]== 14 || ityp[i]== 15 || 
       ityp[i]== 18 || ityp[i]== 24)
    {
      if(i== 1)  
        koffs[1]= 1;
      else       
        koffs[i]= koffs[i-1] + kofold;

      if(koffs[i]+6 >= MAXKOI-1)
      {
        wlog88r(MAXKOI,LOG_EXKOI);
        fclose(fwlo);
        return(AL_EXKOI);
      }

      fgets(cline,256,fi1);

      sscanf(cline,PDB PDB PDB PDB PDB PDE,
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
      if(i== 1)  
        koffs[1]= 1;
      else       
        koffs[i]= koffs[i-1] + kofold;

      if(koffs[i]+3 >= MAXKOI-1)
      {
        wlog88r(MAXKOI,LOG_EXKOI);
        fclose(fwlo);
        return(AL_EXKOI);
      }

      fgets(cline,256,fi1);

      sscanf(cline,PDB PDB PDE,
      &koi[koffs[i]   ], &koi[koffs[i] +1], 
      &koi[koffs[i] +2]);
              
      kofold= 3;
    }
            
    /*======================================================================
    * elementtyp 10
    *=====================================================================*/
    if(ityp[i]== 10)
    {
      if(i== 1)  
        koffs[1]= 1;
      else       
        koffs[i]= koffs[i-1] + kofold;

      if(koffs[i]+20 >= MAXKOI-1)
      {
        wlog88r(MAXKOI,LOG_EXKOI);
        fclose(fwlo);
        return(AL_EXKOI);
      }

      fgets(cline,256,fi1);

      sscanf(cline,PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB\
              PDB PDB PDB PDB PDB PDB PDB PDB PDB PDE,
      &koi[koffs[i]    ], &koi[koffs[i]  +1], 
      &koi[koffs[i]  +2], &koi[koffs[i]  +3], 
      &koi[koffs[i]  +4], &koi[koffs[i]  +5], 
      &koi[koffs[i]  +6], &koi[koffs[i]  +7], 
      &koi[koffs[i]  +8], &koi[koffs[i]  +9], 
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
      if(i== 1)  
        koffs[1]= 1;
      else       
        koffs[i]= koffs[i-1] + kofold;

      if(koffs[i]+12 >= MAXKOI-1)
      {
        wlog88r(MAXKOI,LOG_EXKOI);
        fclose(fwlo);
        return(AL_EXKOI);
      }

      fgets(cline,256,fi1);

      sscanf(cline,PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDE,
      &koi[koffs[i]    ], &koi[koffs[i] + 1], 
      &koi[koffs[i] + 2], &koi[koffs[i] + 3], 
      &koi[koffs[i] + 4], &koi[koffs[i] + 5], 
      &koi[koffs[i] + 6], &koi[koffs[i] + 7], 
      &koi[koffs[i] + 8], &koi[koffs[i] + 9], 
      &koi[koffs[i] +10], &koi[koffs[i] +11]);

      kofold= 12;
    }

    /*======================================================================
    * elementtypen 16
    *=====================================================================*/
    if(ityp[i]== 16)
    {
      if(i== 1)  
        koffs[1]= 1;
      else       
        koffs[i]= koffs[i-1] + kofold;

      if(koffs[i]+10 >= MAXKOI-1)
      {
        wlog88r(MAXKOI,LOG_EXKOI);
        fclose(fwlo);
        return(AL_EXKOI);
      }

      fgets(cline,256,fi1);

      sscanf(cline,PDB PDB PDB PDB PDB PDB PDB PDB PDB PDE,
      &koi[koffs[i]   ], &koi[koffs[i] +1], 
      &koi[koffs[i] +2], &koi[koffs[i] +3], 
      &koi[koffs[i] +4], &koi[koffs[i] +5], 
      &koi[koffs[i] +6], &koi[koffs[i] +7], 
      &koi[koffs[i] +8], &koi[koffs[i] +9]); 

      kofold= 10;
    }

    /*======================================================================
    * elementtyp 17
    *=====================================================================*/
    if(ityp[i]== 17)
    {
      if(i== 1)  
        koffs[1]= 1;
      else       
        koffs[i]= koffs[i-1] + kofold;

      if(koffs[i]+4 >= MAXKOI-1)
      {
        wlog88r(MAXKOI,LOG_EXKOI);
        fclose(fwlo);
        return(AL_EXKOI);
      }

      fgets(cline,256,fi1);

      sscanf(cline,PDB PDB PDB PDE,
      &koi[koffs[i]   ], &koi[koffs[i] +1], 
      &koi[koffs[i] +2], &koi[koffs[i] +3]); 

      kofold= 4;
    }

    /*======================================================================
    * elementtyp 19 u. 21
    *=====================================================================*/
    if(ityp[i]== 19 || ityp[i]== 21)
    {
      if(i== 1)  
        koffs[1]= 1;
      else       
        koffs[i]= koffs[i-1] + kofold;

      if(koffs[i]+16 >= MAXKOI-1)
      {
        wlog88r(MAXKOI,LOG_EXKOI);
        fclose(fwlo);
        return(AL_EXKOI);
      }

      fgets(cline,256,fi1);

      sscanf(cline,PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB\
            PDB PDB PDB PDB PDB PDE,
      &koi[koffs[i]    ], &koi[koffs[i]  +1], 
      &koi[koffs[i]  +2], &koi[koffs[i]  +3], 
      &koi[koffs[i]  +4], &koi[koffs[i]  +5], 
      &koi[koffs[i]  +6], &koi[koffs[i]  +7], 
      &koi[koffs[i]  +8], &koi[koffs[i]  +9], 
      &koi[koffs[i] +10], &koi[koffs[i] +11], 
      &koi[koffs[i] +12], &koi[koffs[i] +13], 
      &koi[koffs[i] +14], &koi[koffs[i] +15]); 

      kofold= 16;
    }
  }  // Ende Elementschleife


  /*----------------------------------------------------------------------
  * Z88I1.TXT schliessen 
  *---------------------------------------------------------------------*/
  fclose(fi1);

  wlog88r(0,LOG_EXITRI188);
  return (0);
}

