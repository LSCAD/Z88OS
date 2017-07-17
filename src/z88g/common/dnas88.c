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
* DNAS88
* 21.7.2011 Rieg
* wandelt NASTRAN-Files aus Pro/MECHANICA (PTC, Pro/ENGINEER) 
* fuer Volumenelemente mit Druck - da ist alles anders
***********************************************************************/

/***********************************************************************
* Include-Files
***********************************************************************/
#ifdef FR_UNIX
#include <z88g.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#endif

#ifdef FR_WIN
#include <z88g.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#endif

/***********************************************************************
* Formatbeschreiber
***********************************************************************/	
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
#define PF10B "%10.4lf "
#define PF10 "%10.4lf"
#define PE13B "%+#13.5lE "
#define PE13 "%+#13.5lE"
#endif

#ifdef FR_XQUAD
#define PFB "%Lf "
#define PF "%Lf"
#define PF10B "%10.4Lf "
#define PF10 "%10.4Lf"
#define PE13B "%+#13.5LE "
#define PE13 "%+#13.5LE"
#endif

/****************************************************************************
*  Function-Declarationen
****************************************************************************/
int wrim88g(FR_INT4,int);
int wlog88g(FR_INT4,int);

/****************************************************************************
*  DNAS88
****************************************************************************/
int dnas88(void)
{
extern FILE        *fwlo,*fpro,*fin,*fi1,*fi2,*fi5;

extern FR_INT4     ICFLAG,LANG;

extern char        cnas[];
extern char        cin[];
extern char        ci1[];
extern char        ci2[];
extern char        ci5[];

FR_DOUBLEAY        x;
FR_DOUBLEAY        y;
FR_DOUBLEAY        z;
FR_DOUBLEAY        pres;

FR_DOUBLE          rdummy,sdummy,tdummy,fx,fy,fz,wert;

FR_INT4AY          koi; 
FR_INT4AY          koffs;
FR_INT4AY          nep;
FR_INT4AY          knn;

FR_INT4            ndim= 0,nkp= 0,ne= 0,nfg= 0;
FR_INT4            kflag= 0;
FR_INT4            nkn= 0,ityp= 0,ifrei= 0,ibis= 0;
FR_INT4            npr= 0, iflag1=0;
FR_INT4            ktyp16= 0,ktyp17= 0;
FR_INT4            inow= 0, nel= 0, nrb= 0;

FR_INT4            idummy,jdummy,kdummy,kofold,ispc,iload,ifg;
FR_INT4            i,j,k,n;
FR_INT4            k1,k2,k3,k4,k5,k6,k7,k8,k9,k10;
FR_INT4            n1,n2,n3,n4,n5,n6;

char               cstring[255],c2zeile[255],cdummy[80],cdummy2[80];

/*----------------------------------------------------------------------
* NASTRAN-File oeffnen
*---------------------------------------------------------------------*/	
if((fpro= fopen(cnas,"r"))== NULL)
  {
  wlog88g(0,LOG_NONAS);
  fclose(fwlo);
  return(AL_NONAS);
  }
else
  {
  wrim88g(0,TX_NASOPEN);
  }
	
rewind(fpro);

/*----------------------------------------------------------------------
* Zwischendatei Z88G.IN oeffnen
*---------------------------------------------------------------------*/	
if((fin= fopen(cin,"w+"))== NULL)
  {
  wlog88g(0,LOG_NOIN);
  fclose(fwlo);
  return(AL_NOIN);
  }
else
  {
  wrim88g(0,TX_INOPEN);
  }
	
rewind(fin);

/*----------------------------------------------------------------------
* jetzt die NASTRAN-Datei konvertieren
*---------------------------------------------------------------------*/
while((i= fgetc(fpro)) != EOF)
  {
  if(i == ',') i= ' ';
  fputc(i,fin);
  }

if(fpro)fclose(fpro);

/*----------------------------------------------------------------------
* Z88I1.TXT, Z88I2.TXT und Z88I5.TXT oeffnen
*---------------------------------------------------------------------*/	
if((fi1= fopen(ci1,"w"))== NULL)
  {
  wlog88g(0,LOG_NOI1);
  fclose(fwlo);
  return(AL_NOI1);
  }
else
  {
  wrim88g(0,TX_I1OPEN);
  }
	        
rewind(fi1);

if((fi2= fopen(ci2,"w"))== NULL)
  {
  wlog88g(0,LOG_NOI2);
  fclose(fwlo);
  return(AL_NOI2);
  }
else
  {
  wrim88g(0,TX_I2OPEN);
  }
	        
rewind(fi2);

if((fi5= fopen(ci5,"w"))== NULL)
  {
  wlog88g(0,LOG_NOI5);
  fclose(fwlo);
  return(AL_NOI5);
  }
else
  {
  wrim88g(0,TX_I5OPEN);
  }

rewind(fi5);

/*----------------------------------------------------------------------
* 1.Durchlauf: Lastfall und Kraftfall ausfiltern
*---------------------------------------------------------------------*/	
rewind(fin);	

/* Mustererkennung SUBCASE - SPC - ggf. LOAD */
while((fgets(cstring,254,fin))!= NULL) 
  {		
  if(strncmp(cstring,"SUBCASE",7)== 0)
    {
    fgets(c2zeile,254,fin);
    if(strncmp(c2zeile,"   SPC",6)== 0)    
      {
      sscanf(c2zeile,"%s %s " PD,cdummy,cdummy2,&ispc);
      wrim88g(ispc,TX_ISPC);
      wlog88g(ispc,LOG_ISPC);

      fgets(c2zeile,254,fin);
      if(strncmp(c2zeile,"   LOAD",7)== 0)
        {    
        sscanf(c2zeile,"%s %s " PD,cdummy,cdummy2,&iload);
        wrim88g(iload,TX_ILOAD);
        wlog88g(iload,LOG_ILOAD);
        }
      goto Lskip;
      }
    }
  }
Lskip:;

/*----------------------------------------------------------------------
* 2.Durchlauf: nkp,ne,npr aus NASTRAN Datei holen
*---------------------------------------------------------------------*/	
rewind(fin);

inow= 0; /* um den ganzen Schrott vorher auszufiltern */

while((fgets(cstring,254,fin))!= NULL) 
  {


/*======================================================================
* Elemente und Knoten
*=====================================================================*/
  if(strncmp(cstring,"GRID",  4) == 0) nkp++;
  if(strncmp(cstring,"CTETRA",6) == 0) ne++;

/*======================================================================
* Lager und Kraefte
*=====================================================================*/
  if(strncmp(cstring,"SPC",   3) == 0) 
    {
    sscanf(cstring,"%s " PD,cdummy,&idummy);
    if(idummy == ispc) nrb++;
    }

  if(strncmp(cstring,"FORCE", 5) == 0)
    {
    iflag1= 1;
    sscanf(cstring,"%s " PDB PDB PDB PFB PFB PFB PF,
           cdummy,&idummy,&nkn,&jdummy,&rdummy,&fx,&fy,&fz);

    if(idummy == iload)
      {
      if(FR_FABS(fx) > 1e-10) nrb++; /* FX */
      if(FR_FABS(fy) > 1e-10) nrb++; /* FY */
      if(FR_FABS(fz) > 1e-10) nrb++; /* FZ */
      }
    }

/*======================================================================
* Druecke - zum Abschaetzen des benoetigten dyn. Speichers
*=====================================================================*/
  if(strncmp(cstring,"PLOAD4",6) == 0)
    {
    sscanf(cstring,"%s " PDB PDB PFB PFB PFB PDB PD,
           cdummy,&idummy,&nel,&rdummy,&sdummy,&tdummy,&jdummy,&kdummy);

    if(idummy == iload) 
      {
      npr++;
      }
    }

/*======================================================================
* Dimension feststellen; 
*=====================================================================*/
  if(strncmp(cstring,"CTETRA",6)== 0) ndim= 3;
  } 

/*----------------------------------------------------------------------
* Werte andrucken
*---------------------------------------------------------------------*/

wrim88g(ndim,TX_DIMDET);
wrim88g(nkp, TX_NODDET);
wrim88g(ne , TX_ELEDET);
wrim88g(npr, TX_PELDET);

wlog88g(ndim,LOG_DIMDET);
wlog88g(nkp, LOG_NODDET);
wlog88g(ne , LOG_ELEDET);
wlog88g(npr, LOG_PELDET);

/*----------------------------------------------------------------------
* 1.Zeile Z88I1.TXT schreiben
*---------------------------------------------------------------------*/
nfg= nkp*3;
ifrei= 3;

if(LANG == 1)
  fprintf(fi1,
  PD5B PD5B PD5B PD5B PD5B " Z88I1.TXT,via Z88G V15OS NASTRAN\n",
  ndim,nkp,ne,nfg,kflag);

if(LANG == 2)
  fprintf(fi1,
  PD5B PD5B PD5B PD5B PD5B " Z88I1.TXT, by Z88G V15OS NASTRAN\n",
  ndim,nkp,ne,nfg,kflag);
  
  

/*----------------------------------------------------------------------
* 1.Zeile Z88I2.TXT schreiben
*---------------------------------------------------------------------*/
if(LANG == 1) fprintf(fi2,PD5B "  Z88I2.TXT,via Z88G V15OS NASTRAN\n",nrb);
if(LANG == 2) fprintf(fi2,PD5B "  Z88I2.TXT, by Z88G V15OS NASTRAN\n",nrb);


/*----------------------------------------------------------------------
* 3.Durchlauf:
* NASTRAN-Datei lesen und Z88I1.TXT und Z88I3.TXT schreiben
*---------------------------------------------------------------------*/
/*======================================================================
* Speicher kommen lassen
*=====================================================================*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Speicher fuer die Koordinaten: x, y, z
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
x= (FR_DOUBLEAY) FR_CALLOC(nkp+1,sizeof(FR_DOUBLE));
if(x == NULL)
  {
  wlog88g(1,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88g(1,LOG_ARRAYOK);

y= (FR_DOUBLEAY) FR_CALLOC(nkp+1,sizeof(FR_DOUBLE));
if(y == NULL)
  {
  wlog88g(2,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88g(2,LOG_ARRAYOK);

z= (FR_DOUBLEAY) FR_CALLOC(nkp+1,sizeof(FR_DOUBLE));
if(z == NULL)
  {
  wlog88g(3,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88g(3,LOG_ARRAYOK);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Speicher fuer die Koinzidenz: koi, koffs
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
koi= (FR_INT4AY) FR_CALLOC(ne*10+1,sizeof(FR_INT4));
if(koi == NULL)
  {
  wlog88g(4,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88g(4,LOG_ARRAYOK);

koffs= (FR_INT4AY) FR_CALLOC(ne+1,sizeof(FR_INT4));
if(koffs == NULL)
  {
  wlog88g(5,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88g(5,LOG_ARRAYOK);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Speicher fuer die PLOAD4s: nep, pres, knn
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
nep= (FR_INT4AY) FR_CALLOC(npr+1,sizeof(FR_INT4));
if(nep == NULL)
  {
  wlog88g(6,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88g(6,LOG_ARRAYOK);

pres= (FR_DOUBLEAY) FR_CALLOC(npr+1,sizeof(FR_DOUBLE));
if(pres == NULL)
  {
  wlog88g(7,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88g(7,LOG_ARRAYOK);

knn= (FR_INT4AY) FR_CALLOC(npr+1,sizeof(FR_INT4));
if(knn == NULL)
  {
  wlog88g(8,LOG_ARRAYNOTOK);
  fclose(fwlo);
  return(AL_NOMEMY);
  }
else
  wlog88g(8,LOG_ARRAYOK);

/*======================================================================
* ab in die Lese/Schreibschleife
*=====================================================================*/
wrim88g(0,TX_REAWRI);
wlog88g(0,LOG_REAWRI);

rewind(fin);  

i= 0;     /* fuer alle Elemente      */
j= 0;     /* fuer alle Knoten        */
n= 0;     /* fuer Elemente mit Druck */

inow= 0;  /* um den ganzen Schrott vorher auszufiltern */

while((fgets(cstring,254,fin)) != NULL)
  {
  if(strncmp(cstring,"GRID",4)== 0) inow= 1;

/*======================================================================
* Z88I1.TXT: Knoten
*=====================================================================*/
  if(strncmp(cstring,"GRID",4)== 0)
    {
    j++;
    sscanf(cstring,"%s " PDB PDB PFB PFB PF,
           cdummy,&nkn,&idummy,&x[j],&y[j],&z[j]);

    if(LANG == 1)
      fprintf(fi1,PD5B PD5B PE13B PE13B PE13B "  Knoten #" PD "\n", 
      nkn,ifrei,x[j],y[j],z[j],nkn);
    if(LANG == 2)
      fprintf(fi1,PD5B PD5B PE13B PE13B PE13B "  node #" PD "\n", 
      nkn,ifrei,x[j],y[j],z[j],nkn);
    }

/*======================================================================
* Z88I1.TXT: Elemente Typ 16
*=====================================================================*/
  if(strncmp(cstring,"CTETRA",6)== 0)
    {
    i++;

    if(i== 1)  koffs[1]= 1;
    else       koffs[i]= koffs[i-1] + kofold;
  
    koi[koffs[i] +4]= 0;

    sscanf(cstring,"%s " PDB PDB PDB PDB PDB PDB PDB PD,
           cdummy,&k,&idummy,
           &koi[koffs[i]   ], &koi[koffs[i] +1], 
           &koi[koffs[i] +2], &koi[koffs[i] +3], 
           &koi[koffs[i] +4], &koi[koffs[i] +5]); 

    if(koi[koffs[i] +4] != 0)
      {
      ityp= 16;
      ktyp16++;

      fgets(c2zeile,254,fin);   /* 2.Zeile */
      sscanf(c2zeile,PDB PDB PDB PD,
             &koi[koffs[i] +6], &koi[koffs[i] +9], 
             &koi[koffs[i] +7], &koi[koffs[i] +8]); 

      fprintf(fi1,PD5B PD5B " Element " PD5 "\n",k,ityp,k); 
      fprintf(fi1,PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5 "\n",
              koi[koffs[i]   ], koi[koffs[i] +1], 
              koi[koffs[i] +2], koi[koffs[i] +3], 
              koi[koffs[i] +4], koi[koffs[i] +5], 
              koi[koffs[i] +6], koi[koffs[i] +7], 
              koi[koffs[i] +8], koi[koffs[i] +9]); 

      kofold= 10;
      ibis= k;
      }

    else

/*======================================================================
* Z88I1.TXT: Elemente Typ 17
*=====================================================================*/
      {
      ityp= 17;
      ktyp17++;

      fprintf(fi1,PD5B PD5B " Element " PD5 "\n",k,ityp,k); 
      fprintf(fi1,PD5B PD5B PD5B PD5 "\n",
              koi[koffs[i]   ], koi[koffs[i] +1], 
              koi[koffs[i] +2], koi[koffs[i] +3]); 

      kofold= 4;
      ibis= k;
      }
    }

/*======================================================================
* Z88I2.TXT: Randbedingungen: Lager
*=====================================================================*/
  if(strncmp(cstring,"SPC",   3) == 0 && inow == 1)  
    {
    iflag1= 2;
    sscanf(cstring,"%s " PDB PDB PDB PF,cdummy,&idummy,&nkn,&ifg,&wert);

    if(idummy == ispc)
      fprintf(fi2,PD5B PD5B PD5B PF10 "\n",nkn,ifg,iflag1,wert); 
    }

/*======================================================================
* Z88I2.TXT: Randbedingungen: Kraefte
*=====================================================================*/
  if(strncmp(cstring,"FORCE", 5) == 0  && inow == 1)
    {
    iflag1= 1;
    sscanf(cstring,"%s " PDB PDB PDB PFB PFB PFB PF,
           cdummy,&idummy,&nkn,&jdummy,&rdummy,&fx,&fy,&fz);

    if(idummy == iload)
      {
      if(FR_FABS(fx) > 1e-10)  /* FX */
        {
        ifg= 1;
        fprintf(fi2,PD5B PD5B PD5B PF10 "\n",nkn,ifg,iflag1,fx);
        }
  
      if(FR_FABS(fy) > 1e-10)  /* FY */
        {
        ifg= 2;
        fprintf(fi2,PD5B PD5B PD5B PF10 "\n",nkn,ifg,iflag1,fy);
        }
  
      if(FR_FABS(fz) > 1e-10)  /* FZ */
        {
        ifg= 3;
        fprintf(fi2,PD5B PD5B PD5B PF10 "\n",nkn,ifg,iflag1,fz);
        }
      }
    }

/*======================================================================
* fuer Z88I5.TXT: Elemente mit Druck
*=====================================================================*/
  if(strncmp(cstring,"PLOAD4",6) == 0 && inow == 1)  
    {
    sscanf(cstring,"%s " PDB PDB PFB PFB PFB PDB PD,
           cdummy,&idummy,&nel,&rdummy,&sdummy,&tdummy,&jdummy,&kdummy);

    if(idummy == iload)
      {
      n++;
      nep[n] = nel;
      pres[n]= rdummy;
      knn[n] = kdummy;
      }
    }

  }  /* Ende while 3.Durchlauf */  

/*----------------------------------------------------------------------
* Ende 3.Durchlauf
*---------------------------------------------------------------------*/
wrim88g(nkp,   TX_NODDON);
wrim88g(ne ,   TX_ELEDON);
wrim88g(nrb,   TX_CONDON);
wrim88g(ktyp16,TX_16DET);
wrim88g(ktyp17,TX_17DET);

wlog88g(nkp,   LOG_NODDON);
wlog88g(ne ,   LOG_ELEDON);
wlog88g(nrb,   LOG_CONDON);
wlog88g(ktyp16,LOG_16DET);
wlog88g(ktyp17,LOG_17DET);


/*----------------------------------------------------------------------
* Files Z88I1.TXT und Z88I2.TXT schliessen
*---------------------------------------------------------------------*/
fclose(fi1);
fclose(fi2);

/*----------------------------------------------------------------------
* 4.Durchlauf:
* Z88I5.TXT
*---------------------------------------------------------------------*/
/*======================================================================
* Z88I5.TXT: erste Zeile
*=====================================================================*/
if(LANG == 1)
  fprintf(fi5,PD5 "   Z88I5.TXT,via Z88G V15OS NASTRAN\n",n);
if(LANG == 2)
  fprintf(fi5,PD5 "   Z88I5.TXT, by Z88G V15OS NASTRAN\n",n);

/*======================================================================
* fuer jedes Dreieck mit Druck Flaeche und Normalenvektor bestimmen
*=====================================================================*/
for(i= 1; i <= npr; i++)
  {
  k1= koi[koffs[nep[i]]  ];         /* die vier Eckknoten */
  k2= koi[koffs[nep[i]]+1];
  k3= koi[koffs[nep[i]]+2];
  k4= koi[koffs[nep[i]]+3];  
  if(ktyp16 > 0)
    {
    k5 = koi[koffs[nep[i]]+4];      /* die sechs Mittenknoten */
    k6 = koi[koffs[nep[i]]+5];
    k7 = koi[koffs[nep[i]]+6];
    k8 = koi[koffs[nep[i]]+7];  
    k9 = koi[koffs[nep[i]]+8];
    k10= koi[koffs[nep[i]]+9];  
    }

  if(knn[i] == k1)                  /* Dreieck 2-3-4-6-9-8 */
    {
    n1= k2;
    n2= k3;
    n3= k4;
    if(ktyp16 > 0)
      {
      n4= k6;
      n5= k9;
      n6= k8;
      }
    }  

  if(knn[i] == k2)                  /* Dreieck 1-4-3-10-9-7 */
    {
    n1= k1;
    n2= k4;
    n3= k3;
    if(ktyp16 > 0)
      {
      n4= k10;
      n5= k9;
      n6= k7;
      }
    }  

  if(knn[i] == k3)                  /* Dreieck 1-2-4-5-8-10 */
    {
    n1= k1;
    n2= k2;
    n3= k4;
    if(ktyp16 > 0)
      {
      n4= k5;
      n5= k8;
      n6= k10;
      }
    }  

  if(knn[i] == k4)                  /* Dreieck 1-3-2-7-6-5 */
    {
    n1= k1;
    n2= k3;
    n3= k2;
    if(ktyp16 > 0)
      {
      n4= k7;
      n5= k6;
      n6= k5;
      }
    }  

  if(ktyp17 > 0)
    fprintf(fi5,PD5B PE13B PD5B PD5B PD5 "\n",
    nep[i],pres[i],n1,n2,n3);
  if(ktyp16 > 0)
    fprintf(fi5,PD5B PE13B PD5B PD5B PD5B PD5B PD5B PD5 "\n",
    nep[i],pres[i],n1,n2,n3,n4,n5,n6);
  }

/*----------------------------------------------------------------------
* Files Z88G.IN und Z88I2.TXT schliessen und zurueck
*---------------------------------------------------------------------*/
fclose(fin);
fclose(fi5);

wrim88g(0,TX_Z88CS);
wlog88g(0,LOG_Z88CS);

return(0);
}



