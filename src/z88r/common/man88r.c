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
* V15.0 November 18, 2015
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
* man88r - liest Z88MAN.TXT
* int88r - liest Z88INT.TXT
* elp88r - liest Z88ELP.TXT
* mat88r - liest Z88MAT.TXT + CSV-Dateien
*
* 2.12.2015 Rieg 
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>    /* FILE,NULL,fopen,fclose,rewind */
#include <string.h>
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <stdio.h>    /* FILE,NULL,fopen,fclose,rewind */
#include <string.h>
#endif

/***********************************************************************
* Formate
***********************************************************************/
#ifdef FR_XINT
#define CFORMA "%s %d"
#define PDB "%d "
#define PDE "%d"
#endif

#ifdef FR_XLONG
#define CFORMA "%s %ld"
#define PDB "%ld "
#define PDE "%ld"
#endif

#ifdef FR_XLOLO
#define CFORMA "%s %lld"
#define PDB "%lld "
#define PDE "%lld"
#endif

#ifdef FR_XDOUB
#define CFORMA2 "%s %lg"
#define PGB "%lg "
#define PGE "%lg"
#endif

#ifdef FR_XQUAD
#define CFORMA2 "%s %Lg"
#define PGB "%Lg "
#define PGE "%Lg"
#endif

/****************************************************************************
*  Function-Declarationen
****************************************************************************/
int  ale88r(int);
int  wrim88r(FR_INT4,int);
int  wlog88r(FR_INT4,int);

/***********************************************************************
* hier beginnt Function man88r
***********************************************************************/
int man88r(void) 
{
extern FILE       *fman,*fwlo;

extern FR_DOUBLE  eps,rpomega,rpalpha;

extern FR_INT4    ibflag,ipflag,ihflag,kdflag,isflag;
extern FR_INT4    maxit;

extern char       cman[];

char cdummy[256];
char cline[256];

/*----------------------------------------------------------------------
*  Manage-Datei z88man.txt oeffnen
*---------------------------------------------------------------------*/
fman = fopen(cman,"r");
if(fman == NULL)
  {
  wlog88r(0,LOG_NOMAN);
  fclose(fwlo);
  return(AL_NOMAN);
  }
rewind(fman);

wrim88r(0,TX_REAMAN);

/*----------------------------------------------------------------------
*  Sektion DYNAMIC lesen
*---------------------------------------------------------------------*/
fgets(cline,256,fman);

if( (strstr(cline,"DYNAMIC START"))!= NULL)   
  {
  do
    {
    fgets(cline,256,fman);

/*======================================================================
*  Sektion GLOBAL lesen
*=====================================================================*/
    if( (strstr(cline,"GLOBAL START"))!= NULL)    
      {
      do
        {
        fgets(cline,256,fman);
        if( (strstr(cline,"IBFLAG"))!= NULL)    
            sscanf(cline,CFORMA,cdummy,&ibflag);
        if( (strstr(cline,"IPFLAG"))!= NULL)      
          sscanf(cline,CFORMA,cdummy,&ipflag);
        if( (strstr(cline,"IHFLAG"))!= NULL)      
          sscanf(cline,CFORMA,cdummy,&ihflag);
        }
      while( (strstr(cline,"GLOBAL END"))== NULL);
      }                                             

/*======================================================================
*  Sektion SOLVER lesen
*=====================================================================*/
    if( (strstr(cline,"SOLVER START"))!= NULL)      
      {
      do
        {
        fgets(cline,256,fman);
        if( (strstr(cline,"MAXIT"))!= NULL)        
          sscanf(cline,CFORMA,cdummy,&maxit);
        if( (strstr(cline,"EPS"))!= NULL)         
          sscanf(cline,CFORMA2,cdummy,&eps);
        if( (strstr(cline,"RALPHA"))!= NULL)        
          sscanf(cline,CFORMA2,cdummy,&rpalpha);
        if( (strstr(cline,"ROMEGA"))!= NULL)       
          sscanf(cline,CFORMA2,cdummy,&rpomega);
        }
      while( (strstr(cline,"SOLVER END"))== NULL);
      }     

/*======================================================================
*  Sektion STRESS lesen
*=====================================================================*/
   if( (strstr(cline,"STRESS START"))!= NULL)    
      {
      do
        {
        fgets(cline,256,fman);
        if( (strstr(cline,"KDFLAG"))!= NULL)        
            sscanf(cline,CFORMA,cdummy,&kdflag);
        if( (strstr(cline,"ISFLAG"))!= NULL)      
          sscanf(cline,CFORMA,cdummy,&isflag);
        }
      while( (strstr(cline,"STRESS END"))== NULL);
      }                                             
                                        
    }
  while( (strstr(cline,"DYNAMIC END"))== NULL);     
  }                                                
else
  {
  wlog88r(0,LOG_WRONGMAN);
  fclose(fman);
  fclose(fwlo);
  return(AL_WRONGMAN);
  }  

fclose(fman);
return 0;
}

/***********************************************************************
* hier beginnt Function int88r
***********************************************************************/
int int88r(void) 
{
extern FILE       *fint,*fwlo;

extern FR_INT4AY  intord;
extern FR_INT4AY  intos;
extern FR_INT4AY  ivon_int;
extern FR_INT4AY  ibis_int;

extern FR_INT4    mint;

extern char       cint[];

int i;

char cline[256];

/*----------------------------------------------------------------------
*  Integrationsordnungs-Datei z88int.txt oeffnen
*---------------------------------------------------------------------*/
fint = fopen(cint,"r");
if(fint == NULL)
  {
  wlog88r(0,LOG_NOINT);
  fclose(fwlo);
  return(AL_NOINT);
  }
rewind(fint);

/*----------------------------------------------------------------------
*  Integrationsordnungs-Datei z88int.txt einlesen
*---------------------------------------------------------------------*/
fgets(cline,256,fint);
sscanf(cline,PDE,&mint);

wrim88r(mint,TX_REAINT);

for(i = 1; i <= mint; i++)
  {
  fgets(cline,256,fint);
  sscanf(cline,PDB PDB PDB PDE,
    &ivon_int[i],&ibis_int[i],&intord[i],&intos[i]);
  }

/*----------------------------------------------------------------------
*  Integrationsordnungs-Datei z88int.txt schliessen
*---------------------------------------------------------------------*/
fclose(fint);
return 0;
}

/***********************************************************************
* hier beginnt Function elp88r
***********************************************************************/
int elp88r(void) 
{
extern FILE        *felp,*fwlo;

extern FR_DOUBLEAY qpara;
extern FR_DOUBLEAY riyy;
extern FR_DOUBLEAY eyy;
extern FR_DOUBLEAY rizz;
extern FR_DOUBLEAY ezz;
extern FR_DOUBLEAY rit;
extern FR_DOUBLEAY wt;
extern FR_DOUBLEAY xcp;
extern FR_DOUBLEAY ycp;
extern FR_DOUBLEAY zcp;
extern FR_DOUBLEAY rkap;

extern FR_INT4AY  ivon_elp;
extern FR_INT4AY  ibis_elp;
extern FR_INT4AY  ifbeti;

extern FR_INT4    melp;

extern char       celp[];

int i;

char cline[256];

/*----------------------------------------------------------------------
*  Elementparameter-Datei z88elp.txt oeffnen
*---------------------------------------------------------------------*/
felp = fopen(celp,"r");
if(felp == NULL)
  {
  wlog88r(0,LOG_NOELP);
  fclose(fwlo);
  return(AL_NOELP);
  }
rewind(felp);

/*----------------------------------------------------------------------
*  Elementparameter-Datei z88elp.txt einlesen
*---------------------------------------------------------------------*/
fgets(cline,256,felp);
sscanf(cline,PDE,&melp);

wrim88r(melp,TX_REAELP);

for(i = 1; i <= melp; i++)
  {
  fgets(cline,256,felp);
  sscanf(cline,PDB PDB PGB PGB PGB PGB PGB PGB PGB PDB PGB PGB PGB PGE,
    &ivon_elp[i],&ibis_elp[i],
    &qpara[i],&riyy[i],&eyy[i],&rizz[i],&ezz[i],&rit[i],&wt[i],
    &ifbeti[i],
    &xcp[i],&ycp[i],&zcp[i],&rkap[i]);
  }

/*----------------------------------------------------------------------
*  Elementparameter-Datei z88elp.txt schliessen
*---------------------------------------------------------------------*/
fclose(felp);
return 0;
}

/***********************************************************************
* hier beginnt Function mat88r
***********************************************************************/
int mat88r(void) 
{
extern FILE         *fmat,*fwlo;

extern FR_DOUBLEAY  emod;
extern FR_DOUBLEAY  rnue;

extern FR_INT4AY    ivon_mat;
extern FR_INT4AY    ibis_mat;

extern FR_INT4      mmat;

extern char         cmat[];

FILE *fcsv;

int i,j;

char cline[256];
char ccsv[256];

/*----------------------------------------------------------------------
*  Material-Datei z88mat.txt oeffnen
*---------------------------------------------------------------------*/
fmat = fopen(cmat,"r");
if(fmat == NULL)
  {
  wlog88r(0,LOG_NOMAT);
  fclose(fwlo);
  return(AL_NOMAT);
  }
rewind(fmat);

/*----------------------------------------------------------------------
*  Material-Datei z88mat.txt und einzelne ?.txt einlesen
*---------------------------------------------------------------------*/
fgets(cline,256,fmat);
sscanf(cline,PDE,&mmat);

wrim88r(mmat,TX_REAMAT);

for(i = 1; i <= mmat; i++)
  {
  fgets(cline,256,fmat);
  sscanf(cline,PDB PDB "%s",&ivon_mat[i],&ibis_mat[i],ccsv);

  fcsv= fopen(ccsv,"r");
  if (fcsv == NULL) 
    {
    wlog88r(0,LOG_NOMATCSV);
    fclose(fwlo);
    return(AL_NOMATCSV);
    }
  rewind(fcsv);

  fgets(cline,256,fcsv);
  sscanf(cline,PGE PGE,&emod[i],&rnue[i]);

  fclose (fcsv);
  }

/*----------------------------------------------------------------------
*  Material-Datei z88mat.txt schliessen
*---------------------------------------------------------------------*/
fclose(fmat);
return 0;
}


