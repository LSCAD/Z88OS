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
/***********************************************************************
* Z88H
* 14.12.2015 Rieg
* Cuthill-McKee Algorithmus fuer Z88I1.TXT, Z88I2.TXT und Z88I5.TXT.
***********************************************************************/

/***********************************************************************
* Includes UNIX
***********************************************************************/	
#ifdef FR_UNIX
#include <z88h.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

/***********************************************************************
* Formatbeschreiber
***********************************************************************/	
#ifdef FR_XINT
#define CFORMA "%s %d"
#define PDB "%d "
#define PD "%d"
#define PD9B "%9d "
#define PD9 "%9d"
#endif

#ifdef FR_XLONG
#define CFORMA "%s %ld"
#define PDB "%ld "
#define PD "%ld"
#define PD9B "%9ld "
#define PD9 "%9ld"
#endif

#ifdef FR_XLOLO
#define CFORMA "%s %lld"
#define PDB "%lld "
#define PD "%lld"
#define PD9B "%9lld "
#define PD9 "%9lld"
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

/****************************************************************************
*  globale Variable
****************************************************************************/
/*--------------------------------------------------------------------------
* Files
*-------------------------------------------------------------------------*/
FILE *fdyn,*fwlo;

char cdyn[8] = "z88.dyn";
char clgd[9] = "z88h.log";

/*--------------------------------------------------------------------------
* Variable
*-------------------------------------------------------------------------*/
FR_INT4 ICFLAG=1;   /* Reverse Cuthill-McKee fest eingestellt */
FR_INT4 LANG;
FR_INT4 MAXGRA,MAXNDL;
FR_INT4 iqflag;

/***********************************************************************
* Functions
***********************************************************************/	
int who88h(void);
int z882cut(void);
int cut88(void);
int cut2z88(void);
int rdy88h(void);
int ale88h(int);
int wrim88h(FR_INT4,int);
int wlog88h(FR_INT4,int);
int lan88h(void);
void stop88h(void);
FR_INT4 max(FR_INT4,FR_INT4);
FR_INT4 min(FR_INT4,FR_INT4);

/***********************************************************************
* Typen
***********************************************************************/
typedef  int  BOOL;

#define TRUE 1
#define FALSE 0

/***********************************************************************
* Main
***********************************************************************/	
int main(void)
{
int iret;

/*---------------------------------------------------------------------------
*  Die Sprache feststellen
*--------------------------------------------------------------------------*/
LANG = 0;
iret= lan88h();

if(iret != 0)
  {
  ale88h(iret);
  stop88h();
  }

/*---------------------------------------------------------------------------
*  Ueberschrift
*--------------------------------------------------------------------------*/
who88h();

/*---------------------------------------------------------------------------
*  Hauptroutine
*--------------------------------------------------------------------------*/
              iret= z882cut();    /* Z88I1.TXT in Z88H.IN */
if(iret == 0) iret= cut88();      /* Cuthill-McKee --> Z88H.OUT */
if(iret == 0) iret= cut2z88();    /* Z88I1.TXT + Z88I2.TXT umbauen */ 

return iret;
}

/***********************************************************************
* Z882CUT
***********************************************************************/	
int z882cut(void)
{
extern FR_INT4 iqflag;

FILE *fz88i1,*fcut,*fz88i5;

FR_INT4 nkp,ndim,ne,newnum,ianz,nfg,kflag,npr;
FR_INT4 koi[21];
FR_INT4 idummy,ityp;
FR_INT4 i;

char cstring[255];
char cfcut[]="z88h.in";
char cfi1[]= "z88i1.txt";
char cfi5[]= "z88i5.txt";

/*----------------------------------------------------------------------
* Files oeffnen
*---------------------------------------------------------------------*/
/*======================================================================
* Z88H.IN
*=====================================================================*/
if ((fcut=fopen(cfcut,"w"))==NULL)
  {
  ale88h(AL_NOIN);
  wlog88h(0,LOG_NOIN);
  return 1;
  }
else
  wrim88h(0,TX_INOPEN);
    
rewind(fcut);

/*======================================================================
* Z88I1.TXT
*=====================================================================*/	
if ((fz88i1=fopen(cfi1,"r"))==NULL)
  {
  ale88h(AL_NOI1);
  return 1;
  }
else
  wrim88h(0,TX_I1OPEN);
 
rewind(fz88i1);

/*======================================================================
* Z88I5.TXT
*=====================================================================*/
if ((fz88i5=fopen(cfi5,"r"))==NULL)
  {
  ale88h(AL_NOI5);
  return 1;
  }
else
  wrim88h(0,TX_I5OPEN);
  
rewind(fz88i5);
   	        
/*----------------------------------------------------------------------
* Vorbereiten
*---------------------------------------------------------------------*/
newnum= -1;                            /* nur eine Startnummer */

fgets(cstring,254,fz88i1);
sscanf(cstring,PDB PDB PDB PD,&ndim,&nkp,&ne,&nfg);

fprintf(fcut,PD9B PD9 "\n",nkp,newnum);
	
fgets(cstring,254,fz88i5);
sscanf(cstring,PD,&npr);

if(npr > 0) iqflag= 1;
else        iqflag= 0;
	
/*----------------------------------------------------------------------
* 1. Durchlauf: Rewind, Leerlesen Koordinaten, Elementtyp feststellen
*---------------------------------------------------------------------*/	
rewind(fz88i1);

fgets(cstring,254,fz88i1);             /* leerlesen 1. Zeile */ 

for(i = 1;i <= nkp; i++)               /* leerlesen Koordinaten */
  fgets(cstring,254,fz88i1); 
  
fgets(cstring,254,fz88i1);
sscanf(cstring,PDB PD,&idummy,&ityp); /* Typ des 1.Elements */

/*----------------------------------------------------------------------
* 2. Durchlauf: Rewind, Leerlesen Koordinaten
*---------------------------------------------------------------------*/	
rewind(fz88i1);

fgets(cstring,254,fz88i1);             /* leerlesen 1. Zeile */ 

for(i = 1;i <= nkp; i++)               /* leerlesen Koordinaten */
  fgets(cstring,254,fz88i1); 

/*----------------------------------------------------------------------
* Schreiben der Elemente Nr.1, Nr.7, Nr.8, Nr.20 und Nr.23
*---------------------------------------------------------------------*/	
if (ityp == 1 || ityp == 7 || ityp == 8 || ityp == 20 || ityp == 23)
  {
  ianz= 8;
  fprintf(fcut,PD "\n",ianz);
  	
  for (i = 1; i <= ne; i++)
    {
    fgets (cstring,254,fz88i1);
    sscanf(cstring,PDB PD,&idummy,&ityp);
    fgets (cstring,254,fz88i1);         
		
    sscanf(cstring,PDB PDB PDB PDB PDB PDB PDB PDB PDB PD, 
    &koi[1],&koi[2],&koi[3],&koi[4],&koi[5],&koi[6],&koi[7],&koi[8],&koi[9],&koi[10]);
	
    fprintf(fcut,PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9 "\n",
    koi[1],koi[2],koi[3],koi[4],koi[5],koi[6],koi[7],koi[8],koi[9],koi[10]);
    } 
  fprintf(fcut, "-1 0 0 0 0 0 0 0 0 0\n");
  goto L999;
  }

/*----------------------------------------------------------------------
* Schreiben der Balken Nr.2, 13, 25, Welle Nr.5, Stab Nr.4, Nr.9
*---------------------------------------------------------------------*/	
if (ityp == 2 || ityp == 4  || ityp == 5 
 || ityp == 9 || ityp == 13 || ityp == 25)
  {
  ianz= 2;
  fprintf(fcut,PD "\n",ianz);
	
  for (i = 1; i <= ne; i++)
    {
    fgets (cstring,254,fz88i1);
    sscanf(cstring,PDB PD,&idummy,&ityp);
    fgets (cstring,254,fz88i1);         
		
    sscanf(cstring,PDB PD,&koi[1],&koi[2]);

    fprintf(fcut,PD9B PD9 "\n",koi[1],koi[2]);
    } 
  fprintf(fcut, "-1 0\n");
  goto L999;
  }

/*----------------------------------------------------------------------
* Schreiben der Dreiecke Nr.3, 14, 15, 18 und 24
*---------------------------------------------------------------------*/	
if (ityp == 3 || ityp == 14 || ityp == 15 || ityp == 18 || ityp == 24)
  {
  ianz= 6;
  fprintf(fcut,PD "\n",ianz);
	
  for (i = 1; i <= ne; i++)
    {
    fgets (cstring,254,fz88i1);
    sscanf(cstring,PDB PD,&idummy,&ityp);
    fgets (cstring,254,fz88i1);         
		
    sscanf(cstring,PDB PDB PDB PDB PDB PD, 
    &koi[1],&koi[2],&koi[3],&koi[4],&koi[5],&koi[6]);
	
    fprintf(fcut,PD9B PD9B PD9B PD9B PD9B PD9 "\n",
    koi[1],koi[2],koi[3],koi[4],koi[5],koi[6]);
    } 
  fprintf(fcut, "-1 0 0 0 0 0\n");
  goto L999;
  }
	
/*----------------------------------------------------------------------
* Schreiben der Torus Nr.6
*---------------------------------------------------------------------*/	
if (ityp == 6)
  {
  ianz= 3;
  fprintf(fcut,PD "\n",ianz);
	
  for (i = 1; i <= ne; i++)
    {
    fgets (cstring,254,fz88i1);
    sscanf(cstring,PDB PD,&idummy,&ityp);
    fgets (cstring,254,fz88i1);         
		
    sscanf(cstring,PDB PDB PD,&koi[1],&koi[2],&koi[3]);
	
    fprintf(fcut,PD9B PD9B PD9 "\n",koi[1],koi[2],koi[3]);
    } 
  fprintf(fcut, "-1 0 0 0 0 0\n");
  goto L999;
  }
	
/*----------------------------------------------------------------------
* Schreiben der Hexaeder Typ 10
*---------------------------------------------------------------------*/	
if (ityp == 10)
  {
  ianz= 20;
  fprintf(fcut,PD "\n",ianz);
	
  for (i = 1; i <= ne; i++)
    {
    fgets (cstring,254,fz88i1);
    sscanf(cstring,PDB PD,&idummy,&ityp);
    fgets (cstring,254,fz88i1);         
		
    sscanf(cstring,
    PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &koi[ 1],&koi[ 2],&koi[ 3],&koi[ 4],&koi[ 5],
    &koi[ 6],&koi[ 7],&koi[ 8],&koi[ 9],&koi[10],
    &koi[11],&koi[12],&koi[13],&koi[14],&koi[15],
    &koi[16],&koi[17],&koi[18],&koi[19],&koi[20]);
	
    fprintf(fcut,PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B
 PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9 "\n",
    koi[ 1],koi[ 2],koi[ 3],koi[ 4],koi[ 5],
    koi[ 6],koi[ 7],koi[ 8],koi[ 9],koi[10],
    koi[11],koi[12],koi[13],koi[14],koi[15],
    koi[16],koi[17],koi[18],koi[19],koi[20]);
    } 
  fprintf(fcut, "-1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n");
  goto L999;
  }

/*----------------------------------------------------------------------
* Schreiben der Platte Typ 19 und der Volumenschale 21
*---------------------------------------------------------------------*/	
if (ityp == 19 || ityp == 21)
  {
  ianz= 16;
  fprintf(fcut,PD "\n",ianz);
	
  for (i = 1; i <= ne; i++)
    {
    fgets (cstring,254,fz88i1);
    sscanf(cstring,PDB PD,&idummy,&ityp);
    fgets (cstring,254,fz88i1);         
		
    sscanf(cstring,PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &koi[ 1],&koi[ 2],&koi[ 3],&koi[ 4],&koi[ 5],&koi[ 6],&koi[ 7],&koi[ 8],
    &koi[ 9],&koi[10],&koi[11],&koi[12],&koi[13],&koi[14],&koi[15],&koi[16]);
	
    fprintf(fcut,PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B
 PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9 "\n",
    koi[ 1],koi[ 2],koi[ 3],koi[ 4],koi[ 5],koi[ 6],koi[ 7],koi[ 8],
    koi[ 9],koi[10],koi[11],koi[12],koi[13],koi[14],koi[15],koi[16]);
    } 
  fprintf(fcut, "-1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n");
  goto L999;
  }
	
/*----------------------------------------------------------------------
* Schreiben der Scheiben Nr.11,Torus Nr.12 u. Volumenschale 22
*---------------------------------------------------------------------*/	
if (ityp == 11 || ityp == 12 || ityp == 22)
  {
  ianz= 12;
  fprintf(fcut,PD "\n",ianz);
	
  for (i = 1; i <= ne; i++)
    {
    fgets (cstring,254,fz88i1);
    sscanf(cstring,PDB PD,&idummy,&ityp);
    fgets (cstring,254,fz88i1);         
		
    sscanf(cstring,PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &koi[ 1],&koi[ 2],&koi[ 3],&koi[ 4],&koi[ 5], &koi[ 6],
    &koi[ 7],&koi[ 8],&koi[ 9],&koi[10],&koi[11],&koi[12]);
	
    fprintf(fcut,PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9 "\n",
    koi[ 1],koi[ 2],koi[ 3],koi[ 4],koi[ 5],koi[ 6],
    koi[ 7],koi[ 8],koi[ 9],koi[10],koi[11],koi[12]);
    } 
  fprintf(fcut, "-1 0 0 0 0 0 0 0 0 0 0 0\n");
  goto L999;
  }
		
/*----------------------------------------------------------------------
* Schreiben der Tetraeder Nr.16
*---------------------------------------------------------------------*/	
if (ityp == 16)
  {
  ianz= 10;
  fprintf(fcut,PD "\n",ianz);
	
  for (i = 1; i <= ne; i++)
    {
    fgets (cstring, 254,fz88i1);
    sscanf(cstring,PDB PD,&idummy,&ityp);
    fgets (cstring,254,fz88i1);         
		
    sscanf(cstring,PDB PDB PDB PDB PDB PDB PDB PDB PDB PD, 
    &koi[1],&koi[2],&koi[3],&koi[4],&koi[5],
    &koi[6],&koi[7],&koi[8],&koi[9],&koi[10]);
	
    fprintf(fcut,PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9 "\n",
    koi[1],koi[2],koi[3],koi[4],koi[5],
    koi[6],koi[7],koi[8],koi[9],koi[10]);
    } 
  fprintf(fcut, "-1 0 0 0 0 0 0 0 0 0\n");
  goto L999;
  }
		
/*----------------------------------------------------------------------
* Schreiben der Tetraeder Nr.17
*---------------------------------------------------------------------*/	
if (ityp == 17)
  {
  ianz= 4;
  fprintf(fcut,PD "\n",ianz);

  for (i = 1; i <= ne; i++)
    {
    fgets (cstring,254,fz88i1);
    sscanf(cstring,PDB PD,&idummy,&ityp);
    fgets (cstring,254,fz88i1);         
		
    sscanf(cstring,PDB PDB PDB PD,&koi[1],&koi[2],&koi[3],&koi[4]);
    fprintf(fcut,PD9B PD9B PD9B PD9 "\n",koi[1],koi[2],koi[3],koi[4]);
    } 
  fprintf(fcut, "-1 0 0 0\n");
  goto L999;
  }
	
/*----------------------------------------------------------------------
* Files schliessen
*---------------------------------------------------------------------*/	
L999:;

fprintf(fcut, "-1\n");
fclose(fz88i1);
fclose(fz88i5);
fclose(fcut);
 
return 0;
}

/***********************************************************************
* CUT88
***********************************************************************/
int cut88(void)
{
extern FR_INT4 MAXGRA,MAXNDL;

FILE *fcut,*fpermdat;   

FR_INT4 *igraph,*igrad,*istart;
FR_INT4 *neu,*irneu,*neuin,*irneuin;
FR_INT4 *level,*ipermb,*iperme;

FR_INT4 np[21];

FR_INT4 nkp,maxgr,ndl;
FR_INT4 igradzp,ifcm,ifrcm,krcm;
FR_INT4 isizegr,neunum,nknot,izeile= 0;
FR_INT4 i,j,k,is,nzp,nnp,maxgd,mingd;
FR_INT4 nstart,levs,leve,nlev,l;
FR_INT4 mingr,m,nprcm,nprrcm,nzprcm,iflag=0;

int iret;

BOOL *num;

char cpermdat[]="z88h.out";
char cutfile[]= "z88h.in";
char cstring[255];

/*----------------------------------------------------------------------
* File- Operationen
*---------------------------------------------------------------------*/
if((fpermdat=fopen(cpermdat,"w"))==NULL)
  {
  ale88h(AL_NOOUT);;
  return 1;
  }
else
  wrim88h(0,TX_OUTOPEN);
  
rewind(fpermdat);

if((fcut=fopen(cutfile,"r"))==NULL)
  {
  ale88h(AL_NOIN);
  return 1;
  }
else
  wrim88h(0,TX_INOPEN);

rewind(fcut);

/*----------------------------------------------------------------------
* max. Groesse maxgr und ndl
*---------------------------------------------------------------------*/
iret= rdy88h();
if(iret != 0)
  {
  ale88h(iret);
#ifdef FR_WIN
  return(iret);    
#endif
#ifdef FR_UNIX
  stop88h();
#endif       
  }           

maxgr= MAXGRA;
ndl=   MAXNDL;

/*----------------------------------------------------------------------
* File- Operationen
*---------------------------------------------------------------------*/
fgets(cstring,254,fcut);
sscanf(cstring,PDB PD,&nkp,&neunum); /* neunum = -1 */
        
isizegr= (maxgr+1)*(nkp+1);            /* +1 wg. FORTAN 77 */

/*----------------------------------------------------------------------
* Memory anlegen
*---------------------------------------------------------------------*/
if(((igraph =(FR_INT4 *)calloc((size_t)isizegr,sizeof(FR_INT4)))==NULL) ||
   ((igrad  =(FR_INT4 *)calloc((size_t)(nkp+1),sizeof(FR_INT4)))==NULL) ||
   ((istart =(FR_INT4 *)calloc((size_t)(nkp+1),sizeof(FR_INT4)))==NULL) ||
   ((neu    =(FR_INT4 *)calloc((size_t)(nkp+1),sizeof(FR_INT4)))==NULL) ||
   ((irneu  =(FR_INT4 *)calloc((size_t)(nkp+1),sizeof(FR_INT4)))==NULL) ||
   ((neuin  =(FR_INT4 *)calloc((size_t)(nkp+1),sizeof(FR_INT4)))==NULL) ||
   ((irneuin=(FR_INT4 *)calloc((size_t)(nkp+1),sizeof(FR_INT4)))==NULL) ||
   ((level  =(FR_INT4 *)calloc((size_t)(ndl+1),sizeof(FR_INT4)))==NULL) ||
   ((ipermb =(FR_INT4 *)calloc((size_t)(nkp+1),sizeof(FR_INT4)))==NULL) ||
   ((iperme =(FR_INT4 *)calloc((size_t)(nkp+1),sizeof(FR_INT4)))==NULL) ||
   ((num    =(BOOL *)   calloc((size_t)(nkp+1),sizeof(BOOL   )))==NULL) )  
  {
  ale88h(AL_NOMEM);
  wlog88h(0,LOG_NOMEM);
  return 1; 
  }

wrim88h(0,TX_MEMOK);
	
/*----------------------------------------------------------------------
* Aufbau des Graphen auf Grund Knotennummern der Elemente
*---------------------------------------------------------------------*/	
L30:;

fgets(cstring,254,fcut);
sscanf(cstring,PD,&nknot);
	
if (nknot > 0)
  {
  L40:; 
  fgets(cstring,254,fcut);
  izeile++;
		
  if (nknot == 2)
    sscanf(cstring,PDB PD,&np[1],&np[2]);
   
  if (nknot == 3)
    sscanf(cstring,PDB PDB PD,&np[1],&np[2],&np[3]);

  if (nknot == 4)
    sscanf(cstring,PDB PDB PDB PD,&np[1],&np[2],&np[3],&np[4]);

  if (nknot == 6)
    sscanf(cstring,PDB PDB PDB PDB PDB PD,
    &np[1],&np[2],&np[3],&np[4],&np[5],&np[6]);
			       
  if (nknot == 8)
    sscanf(cstring,PDB PDB PDB PDB PDB PDB PDB PD,&np[1],&np[2],&np[3],
    &np[4],&np[5],&np[6],&np[7],&np[8]);

  if (nknot == 10)
    sscanf(cstring,PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &np[1],&np[2],&np[3],&np[4],&np[5],
    &np[6],&np[7],&np[8],&np[9],&np[10]);

  if (nknot == 12)
    sscanf(cstring,PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &np[ 1],&np[ 2],&np[ 3],&np[ 4],&np[ 5],&np[ 6],
    &np[ 7],&np[ 8],&np[ 9],&np[10],&np[11],&np[12]);

  if (nknot == 16)
    sscanf(cstring,PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &np[ 1],&np[ 2],&np[ 3],&np[ 4],&np[ 5],&np[ 6],&np[ 7],&np[ 8],
    &np[ 9],&np[10],&np[11],&np[12],&np[13],&np[14],&np[15],&np[16]);

  if (nknot == 20)
    sscanf(cstring,
    PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &np[ 1],&np[ 2],&np[ 3],&np[ 4],&np[ 5],&np[ 6],&np[ 7],&np[ 8],&np[ 9],&np[10],
    &np[11],&np[12],&np[13],&np[14],&np[15],&np[16],&np[17],&np[18],&np[19],&np[20]);
			       
  if (np[1] <= 0) goto L30;

  for (i = 1; i <= nknot-1; i++) 
    {
    nzp = np[i];
    for (j= i+1; j <= nknot; j++) 
      {
      nnp = np[j];
      for (k = 1; k <= maxgr; k++) 
        {
	if (igraph[(k-1)*nkp + nzp] == nnp) goto L80;
	if (igraph[(k-1)*nkp + nzp] > 0 )   continue;
	igraph[(k-1)*nkp + nzp] = nnp;
	igrad[nzp]++;
	goto L60;
	} 

      wlog88h(igrad[nzp],LOG_1STOP);
      wrim88h(igrad[nzp],TX_1STOP);
      ale88h(AL_1STOP);
      return 1;

L60:;
      igrad[nnp]++;
      if (igrad[nnp] <= maxgr) goto L70;
      wlog88h(igrad[nzp],LOG_1STOP);
      wrim88h(igrad[nzp],TX_1STOP);
      ale88h(AL_1STOP);
      return 1;
L70:;
      igraph[(igrad[nnp]-1)*nkp + nnp]= nzp;
L80:;		
      } 
    }  

  goto L40;
  }
	
maxgd= igrad[1];
mingd= igrad[1];
	
for (i = 2; i <= nkp; i++)
  {
  maxgd= max(maxgd,igrad[i]);
  mingd= min(mingd,igrad[i]);
  }

wrim88h(maxgd,TX_MAXGR);

/*----------------------------------------------------------------------
* Vorgabe bzw. Bestimmung der Startpunkte
*---------------------------------------------------------------------*/	
if (neunum > 0)
  {
  for (i = 1; i <= neunum; i++)
    fscanf(fcut,PD,&istart[i]);
  }
else
  {
  neunum= -neunum;
  k=0;
  
L110:;

  for (i = 1; i <= nkp; i++) 
    {
    if (igrad[i]== mingd)
      {
      k++;
      istart[k]= i;
      if (k >= neunum) goto L130;
      }
    } 
  mingd++;
  goto L110;

L130:;

  for (i = 1; i <= neunum; i++) 
    wrim88h(istart[i],TX_STARTNUM);
  }

/*----------------------------------------------------------------------
* Neunummerierung der Knotenpunkte
*---------------------------------------------------------------------*/	
for(is = 1; is <= neunum; is++) 
  {
  nstart= istart[is];
  neu[1]= nstart;
  neuin[nstart]	= 1;
  irneu[nkp]= nstart;
  irneuin[nstart]= nkp;

  for(i = 1; i <= nkp; i++) num[i] = FALSE;

  num[nstart]= TRUE;
  level[1]= 1;
  levs= 1;
  leve= 1;
  nlev= 1;
  l= 1;

L150:;	

  for (j = levs; j <= leve; j++) 
    {
    nzp= neu[j];
    igradzp= igrad[nzp];

L160:;

    mingr= maxgr;
    k= 0;

    for (i = 1; i <= igradzp; i++)
      {
      nnp= igraph[(i-1)*nkp + nzp];
      if (num[nnp] || igrad[nnp] > mingr) continue;
      mingr = igrad[nnp];
      k = nnp;
      }

    if (k == 0) goto L180;
    l++;
    neu[l]= k;
    neuin[k]= l;
    irneu[nkp-l+1]= k;
    irneuin[k]= nkp-l+1;
    num[k]= TRUE;
    goto L160;

L180:;
  } 
		
  levs+= level[nlev];
  nlev++;
  wrim88h(nlev,TX_LEVEL);
  level[nlev] = l - levs + 1;
  leve+= level[nlev];
  if (leve < nkp) goto L150;

/*----------------------------------------------------------------------
* Bandbreite m und Profil nprcm der Neunumerierung
*---------------------------------------------------------------------*/	
  m=      0;
  nprcm=  0;
  nprrcm= 0;

  for (i = 1; i <= nkp; i++)
    {
    nzp=      neuin[i];
    nzprcm=   irneuin[i];
    ifcm=     nzp;
    ifrcm=    nzprcm;
    igradzp=  igrad[i];
  
    for (j = 1; j <= igradzp; j++)
      {
      k=    neuin[igraph[(j-1)*nkp + i]];
      m=    max(m, abs(k-nzp));
      ifcm= min(ifcm, k);
      krcm= irneuin[igraph[(j-1)*nkp + i]];
      ifrcm=min(ifrcm, krcm);
      }

    nprcm= nprcm + nzp - ifcm + 1;
    nprrcm= nprrcm + nzprcm - ifrcm + 1;
    }

  wrim88h(nprcm,TX_NPRCM);
  wrim88h(nprrcm,TX_NPRRCM);

  if (ICFLAG == 1)                 /* reverse Cuthill-McKee */
    {
    iflag=  1;
    for (i = 1; i <= nkp; i++) iperme[i]= irneuin[i];
    }  

  if (ICFLAG == 2)                 /* normaler Cuthill-McKee */
    {
    iflag=  2;
    for (i = 1; i <= nkp; i++) iperme[i]= neuin[i];
    }  

  }
	
/*----------------------------------------------------------------------
* Abspeichern des Permutationsvektors
*---------------------------------------------------------------------*/	
wrim88h(iflag,TX_STOPERM);

j= 1;
for (i = 1; i <= nkp; i++)
  {
  if (j < 10)
    {
    fprintf(fpermdat,PD9,iperme[i]);
    j++;
    }
  else
    {
    fprintf(fpermdat,PD9 "\n",iperme[i]);
    j= 1;
    }
  }

/*----------------------------------------------------------------------
* Files schliessen, Speicher freigeben fuer CUT2Z88
*---------------------------------------------------------------------*/	
fclose(fcut);
fclose(fpermdat);

free(igraph);
free(igrad);
free(istart);
free(neu);
free(irneu);
free(neuin);
free(irneuin);
free(level);
free(ipermb);
free(iperme);
free(num);  

return 0;
}

/***********************************************************************
* max
***********************************************************************/
FR_INT4 max(FR_INT4 i, FR_INT4 j)
{
if (i > j) return i;
else       return j;
}

/***********************************************************************
* min
***********************************************************************/
FR_INT4 min(FR_INT4 i, FR_INT4 j)
{
if (i < j) return i;
else       return j;
}

/***********************************************************************
* CUT2Z88
***********************************************************************/
int cut2z88(void)
{
extern FR_INT4 iqflag;

FILE *fpermdat,*fz88i1old,*fz88i2old,*fz88i5old,*fz88i1,*fz88i2,*fz88i5;

FR_DOUBLE *x,*y,*z;
FR_DOUBLE *wert;
FR_DOUBLE pree,tr1e,tr2e;

FR_INT4   *iperm;
FR_INT4   koi[21];

FR_INT4   i,j;
FR_INT4   nkp=0,ne=0,ndim=0,nfg=0,ifrei=0,idummy=0,ityp=0;

FR_INT4   nrb,npr,jele;
FR_INT4   k1,k2,k3,k4,k5,k6,k7,k8;

FR_INT4   *node;
FR_INT4   *kfrei;
FR_INT4   *iflag;
FR_INT4   *ktyp;

char cpermdat[]= "z88h.out";
char cz88i1[]=   "z88i1.txt";
char cz88i2[]=   "z88i2.txt";
char cz88i5[]=   "z88i5.txt";
char cz88i1old[]="z88i1.old";
char cz88i2old[]="z88i2.old";
char cz88i5old[]="z88i5.old";

char cstring[255];

/*----------------------------------------------------------------------
* Vektor koi loeschen
*---------------------------------------------------------------------*/
wrim88h(0,TX_UMSPEI);

for(i = 0;i <= 20; i++) koi[i]= 0;

/*----------------------------------------------------------------------
* File- Operationen: Z88I1.TXT, Z88I2.TXT, Z88I5.TXT -> 
*                    Z88I1.OLD, Z88I2.OLD, Z88I5.OLD
*---------------------------------------------------------------------*/
if ((fz88i1old= fopen(cz88i1old,"r")) != NULL)
  {
  fclose(fz88i1old);
  remove(cz88i1old);
  }

if ((fz88i2old= fopen(cz88i2old,"r")) != NULL)
  {
  fclose(fz88i2old);
  remove(cz88i2old);
  }

if(iqflag == 1)
  {
  if ((fz88i5old= fopen(cz88i5old,"r")) != NULL)
    {
    fclose(fz88i5old);
    remove(cz88i5old);
    }
  }

rename(cz88i1,cz88i1old);
rename(cz88i2,cz88i2old);
if(iqflag == 1) rename(cz88i5,cz88i5old);

fpermdat= fopen(cpermdat,"r");
	
fz88i1old= fopen(cz88i1old,"r");
fz88i2old= fopen(cz88i2old,"r");
if(iqflag == 1) fz88i5old= fopen(cz88i5old,"r");

fz88i1=    fopen(cz88i1,"w");
fz88i2=    fopen(cz88i2,"w");
if(iqflag == 1) fz88i5=    fopen(cz88i5,"w");
	
wrim88h(0,TX_TXT2OLD);

/*----------------------------------------------------------------------
* Z88I1.TXT
*---------------------------------------------------------------------*/

/*======================================================================
* 1.Zeile
*=====================================================================*/
fgets(cstring,254,fz88i1old);
fputs(cstring,fz88i1);
	
sscanf(cstring,PDB PDB PDB PD,&ndim,&nkp,&ne,&nfg);
	
/*======================================================================
* Memory anlegen
*=====================================================================*/
if(((iperm= (FR_INT4 *)   calloc((size_t)nkp+1,sizeof(FR_INT4  )))==NULL) || 
   ((  x  = (FR_DOUBLE *) calloc((size_t)nkp+1,sizeof(FR_DOUBLE)))==NULL) ||
   ((  y  = (FR_DOUBLE *) calloc((size_t)nkp+1,sizeof(FR_DOUBLE)))==NULL) ||
   ((  z  = (FR_DOUBLE *) calloc((size_t)nkp+1,sizeof(FR_DOUBLE)))==NULL) ||
   ((ktyp = (FR_INT4 *)   calloc((size_t)ne+1, sizeof(FR_INT4  )))==NULL))
  {
  ale88h(AL_NOMEM);
  wlog88h(0,LOG_NOMEM);
  return 1; 
  }

wrim88h(0,TX_MEMOK);
	
/*======================================================================
* Knoten
*=====================================================================*/
wrim88h(0,TX_WRII1);

for(i = 1; i <= nkp; i++)
  fscanf(fpermdat,PD,&iperm[i]);

for(i = 1; i <= nkp; i++)
  {
  fgets(cstring,254,fz88i1old);
  sscanf(cstring,PDB PDB PFB PFB PF,
  &idummy,&ifrei,&x[iperm[i]],&y[iperm[i]],&z[iperm[i]]);
  }

for(i = 1; i <= nkp; i++)
  fprintf(fz88i1,PD9B PD9B PE13B PE13B PE13 "\n",i,ifrei,x[i],y[i],z[i]);

/*======================================================================
* Koinzidenz
*=====================================================================*/
for(i = 1; i <= ne; i++)
  {
  fgets (cstring,254,fz88i1old);
  sscanf(cstring,PDB PD,&idummy,&ityp);
  fputs (cstring,fz88i1);

  ktyp[i]= ityp;

  fgets (cstring,254,fz88i1old);
		
  if(ityp == 1 || ityp == 7 || ityp == 8 || ityp == 20 || ityp == 23)
    {
    sscanf(cstring,PDB PDB PDB PDB PDB PDB PDB PD,
    &koi[1],&koi[2],&koi[3],&koi[4],&koi[5],&koi[6],&koi[7],&koi[8]);

    fprintf(fz88i1,PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9 "\n",
    iperm[koi[1]],iperm[koi[2]],iperm[koi[3]],iperm[koi[4]],
    iperm[koi[5]],iperm[koi[6]],iperm[koi[7]],iperm[koi[8]]);
    }

  if(ityp == 2 || ityp == 4 || ityp == 5 || ityp == 9 || ityp == 13 || ityp == 25)
    {
    sscanf(cstring,PDB PD,&koi[1],&koi[2]);

    fprintf(fz88i1,PD9B PD9 "\n",iperm[koi[1]],iperm[koi[2]]);
    }

  if(ityp == 3 || ityp == 14 || ityp == 15 || ityp == 18 || ityp == 24)
    {
    sscanf(cstring,PDB PDB PDB PDB PDB PD,
    &koi[1],&koi[2],&koi[3],&koi[4],&koi[5],&koi[6]);

    fprintf(fz88i1,PD9B PD9B PD9B PD9B PD9B PD9 "\n",
    iperm[koi[1]],iperm[koi[2]],iperm[koi[3]],
    iperm[koi[4]],iperm[koi[5]],iperm[koi[6]]);
    }

  if(ityp == 6)
    {
    sscanf(cstring,PDB PDB PD,&koi[1],&koi[2],&koi[3]);

    fprintf(fz88i1,PD9B PD9B PD9 "\n",
    iperm[koi[1]],iperm[koi[2]],iperm[koi[3]]);
    }

  if(ityp == 10)
    {
    sscanf(cstring,
    PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &koi[ 1],&koi[ 2],&koi[ 3],&koi[ 4],&koi[ 5],
    &koi[ 6],&koi[ 7],&koi[ 8],&koi[ 9],&koi[10],
    &koi[11],&koi[12],&koi[13],&koi[14],&koi[15],
    &koi[16],&koi[17],&koi[18],&koi[19],&koi[20]);

    fprintf(fz88i1,
    PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B
 PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9 "\n",
    iperm[koi[ 1]],iperm[koi[ 2]],iperm[koi[ 3]],iperm[koi[ 4]],iperm[koi[ 5]],
    iperm[koi[ 6]],iperm[koi[ 7]],iperm[koi[ 8]],iperm[koi[ 9]],iperm[koi[10]],
    iperm[koi[11]],iperm[koi[12]],iperm[koi[13]],iperm[koi[14]],iperm[koi[15]],
    iperm[koi[16]],iperm[koi[17]],iperm[koi[18]],iperm[koi[19]],iperm[koi[20]]);
    }

  if(ityp == 19 || ityp == 21)
    {
    sscanf(cstring,
    PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &koi[ 1],&koi[ 2],&koi[ 3],&koi[ 4],&koi[ 5],
    &koi[ 6],&koi[ 7],&koi[ 8],&koi[ 9],&koi[10],
    &koi[11],&koi[12],&koi[13],&koi[14],&koi[15],
    &koi[16]);

    fprintf(fz88i1,
    PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9 "\n",
    iperm[koi[ 1]],iperm[koi[ 2]],iperm[koi[ 3]],iperm[koi[ 4]],iperm[koi[ 5]],
    iperm[koi[ 6]],iperm[koi[ 7]],iperm[koi[ 8]],iperm[koi[ 9]],iperm[koi[10]],
    iperm[koi[11]],iperm[koi[12]],iperm[koi[13]],iperm[koi[14]],iperm[koi[15]],
    iperm[koi[16]]);
    }

  if(ityp == 11 || ityp == 12 || ityp == 22)
    {
    sscanf(cstring,PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &koi[ 1],&koi[ 2],&koi[ 3],&koi[ 4],&koi[ 5],&koi[ 6],
    &koi[ 7],&koi[ 8],&koi[ 9],&koi[10],&koi[11],&koi[12]);

    fprintf(fz88i1,PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9 "\n",
    iperm[koi[ 1]],iperm[koi[ 2]],iperm[koi[ 3]],iperm[koi[ 4]],
    iperm[koi[ 5]],iperm[koi[ 6]],iperm[koi[ 7]],iperm[koi[ 8]],
    iperm[koi[ 9]],iperm[koi[10]],iperm[koi[11]],iperm[koi[12]]);
    }

  if(ityp == 16)
    {
    sscanf(cstring,PDB PDB PDB PDB PDB PDB PDB PDB PDB PD,
    &koi[1],&koi[2],&koi[3],&koi[4],&koi[5],
    &koi[6],&koi[7],&koi[8],&koi[9],&koi[10]);

    fprintf(fz88i1,PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9 "\n",
    iperm[koi[1]],iperm[koi[2]],iperm[koi[3]],iperm[koi[4]],iperm[koi[5]],
    iperm[koi[6]],iperm[koi[7]],iperm[koi[8]],iperm[koi[9]],iperm[koi[10]]);
    }

  if(ityp == 17)
    {
    sscanf(cstring,PDB PDB PDB PD,&koi[1],&koi[2],&koi[3],&koi[4]);

    fprintf(fz88i1,PD9B PD9B PD9B PD9 "\n",
    iperm[koi[1]],iperm[koi[2]],iperm[koi[3]],iperm[koi[4]]);
    }
  }
		
/*======================================================================
* Files schliessen
*=====================================================================*/
fclose(fz88i1);
fclose(fz88i1old);
fclose(fpermdat);  
	    	
/*----------------------------------------------------------------------
* Z88I2.TXT
*---------------------------------------------------------------------*/
/*======================================================================
* Anzahl Randbedingungen
*=====================================================================*/
fgets(cstring,254,fz88i2old);
sscanf(cstring,PD,&nrb);
fputs(cstring,fz88i2);

/*======================================================================
* Memory anlegen
*=====================================================================*/
if(
((node = (FR_INT4 *)calloc((size_t)nrb+1,sizeof(FR_INT4)))==NULL) ||
((kfrei= (FR_INT4 *)calloc((size_t)nrb+1,sizeof(FR_INT4)))==NULL) ||
((iflag= (FR_INT4 *)calloc((size_t)nrb+1,sizeof(FR_INT4)))==NULL) ||
((wert = (FR_DOUBLE  *)calloc((size_t)nrb+1,sizeof(FR_DOUBLE )))==NULL))
  {
  ale88h(AL_NOMEM);
  wlog88h(0,LOG_NOMEM);
  return 1; 
  }

wrim88h(0,TX_MEMOK);
wrim88h(0,TX_WRII2);

for(i = 1; i <= nrb; i++)
  {
  fgets(cstring,254,fz88i2old);
  sscanf(cstring,PDB PDB PDB PF,&node[i],&kfrei[i],&iflag[i],&wert[i]);
  }
	
for (i = 1; i <= nkp; i++)
  {
  for (j = 1; j <= nrb; j++)
    {
    if(i == iperm[node[j]])
      fprintf(fz88i2,PD9B PD9B PD9B PE13 "\n",i,kfrei[j],iflag[j],wert[j]);			
    }
  }

/*======================================================================
* Files schliessen
*=====================================================================*/
fclose(fz88i2);  
fclose(fz88i2old);  

/*----------------------------------------------------------------------
* Z88I5.TXT
*---------------------------------------------------------------------*/
/*======================================================================
* Anzahl Elemente mit Lasten
*=====================================================================*/
if(iqflag == 1)
  {
  fgets(cstring,254,fz88i5old);
  sscanf(cstring,PD,&npr);
  fputs(cstring,fz88i5);

  wrim88h(0,TX_MEMOK);
  wrim88h(0,TX_WRII5);

  for(j = 1; j <= npr; j++)
    {
    fgets(cstring,254,fz88i5old);
    sscanf(cstring,PD,&jele);

/*======================================================================
* Elemente 7,8,14 und 15: 
*=====================================================================*/
    if(ktyp[jele]== 7  || ktyp[jele]== 8 || 
       ktyp[jele]== 14 || ktyp[jele]== 15)
      { 
      sscanf(cstring,PDB PFB PFB PDB PDB PD,&jele,&pree,&tr1e,&k1,&k2,&k3);
      fprintf(fz88i5,PD9B PE13B PE13B PD9B PD9B PD9 "\n",
        jele,pree,tr1e,iperm[k1],iperm[k2],iperm[k3]);
      }  

/*======================================================================
* Element 17: 
*=====================================================================*/
    if(ktyp[jele]== 17)
      { 
      sscanf(cstring,PDB PFB PDB PDB PD,&jele,&pree,&k1,&k2,&k3);
      fprintf(fz88i5,PD9B PE13B PD9B PD9B PD9 "\n",
        jele,pree,iperm[k1],iperm[k2],iperm[k3]);
      }  

/*======================================================================
* Elemente 11 und 12:
*=====================================================================*/
    if(ktyp[jele]== 11 || ktyp[jele]== 12)
      { 
      sscanf(cstring,PDB PFB PFB PDB PDB PDB PD,&jele,&pree,&tr1e,&k1,&k2,&k3,&k4);
      fprintf(fz88i5,PD9B PE13B PE13B PD9B PD9B PD9B PD9 "\n",
        jele,pree,tr1e,iperm[k1],iperm[k2],iperm[k3],iperm[k4]);
      }  

/*======================================================================
* Element 1:
*=====================================================================*/
    if(ktyp[jele]== 1)
      { 
      sscanf(cstring,PDB PFB PFB PFB PDB PDB PDB PD,
        &jele,&pree,&tr1e,&tr2e,&k1,&k2,&k3,&k4);
      fprintf(fz88i5,PD9B PE13B PE13B PE13B PD9B PD9B PD9B PD9 "\n",
        jele,pree,tr1e,tr2e,iperm[k1],iperm[k2],iperm[k3],iperm[k4]);
      }  

/*======================================================================
* Element 16
*=====================================================================*/
    if(ktyp[jele]== 16)
      { 
      sscanf(cstring,PDB PFB PDB PDB PDB PDB PDB PD,
        &jele,&pree,&k1,&k2,&k3,&k4,&k5,&k6);
      fprintf(fz88i5,PD9B PE13B PD9B PD9B PD9B PD9B PD9B PD9 "\n",
        jele,pree,iperm[k1],iperm[k2],iperm[k3],iperm[k4],iperm[k5],iperm[k6]);
      }

/*======================================================================
* Element 10 u. 21:
*=====================================================================*/
    if(ktyp[jele]== 10 || ktyp[jele]== 21)
      { 
      sscanf(cstring,PDB PFB PFB PFB PDB PDB PDB PDB PDB PDB PDB PD,
        &jele,&pree,&tr1e,&tr2e,&k1,&k2,&k3,&k4,&k5,&k6,&k7,&k8);
      fprintf(fz88i5,
        PD9B PE13B PE13B PE13B PD9B PD9B PD9B PD9B PD9B PD9B PD9B PD9 "\n",
        jele,pree,tr1e,tr2e,iperm[k1],iperm[k2],iperm[k3],iperm[k4],
        iperm[k5],iperm[k6],iperm[k7],iperm[k8]);
      }  

/*======================================================================
* Element 22:
*=====================================================================*/
    if(ktyp[jele]== 22)
      { 
      sscanf(cstring,PDB PFB PFB PFB PDB PDB PDB PDB PDB PD,
        &jele,&pree,&tr1e,&tr2e,&k1,&k2,&k3,&k4,&k5,&k6);
      fprintf(fz88i5,
        PD9B PE13B PE13B PE13B PD9B PD9B PD9B PD9B PD9B PD9 "\n",
        jele,pree,tr1e,tr2e,iperm[k1],iperm[k2],iperm[k3],iperm[k4],
        iperm[k5],iperm[k6]);
      }  

/*======================================================================
* die drei Plattenelemente 18,19 und 20 und Schalen 23 & 24
*=====================================================================*/
    if(ktyp[jele]== 18 || ktyp[jele]== 19 || ktyp[jele]== 20 ||
       ktyp[jele]== 23 || ktyp[jele]== 24)
      { 
      sscanf(cstring,PDB PF,&jele,&pree);
      fprintf(fz88i5,PD9B PE13 "\n",jele,pree);
      }

    }

  fclose(fz88i5);   
  fclose(fz88i5old);   
  }
  	
/*----------------------------------------------------------------------
* Ende Z88H
*---------------------------------------------------------------------*/
wrim88h(0,TX_Z88DONE);

return 0;
}
