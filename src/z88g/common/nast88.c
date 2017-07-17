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
* NAST88
* 21.7.2011 Rieg
* wandelt NASTRAN-Files aus Pro/MECHANICA (PTC, Pro/ENGINEER) 
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
*  NAST88
****************************************************************************/
int nast88(void)
{
extern FILE        *fwlo,*fpro,*fin,*fi1,*fi2,*fi5;

extern FR_INT4     ICFLAG,LANG;

extern char        cnas[];
extern char        cin[];
extern char        ci1[];
extern char        ci2[];

FR_DOUBLEAY        druck;

FR_DOUBLE          x= 0.,y= 0.,z= 0.;
FR_DOUBLE          wert= 0.;
FR_DOUBLE          fl= 0.; 
FR_DOUBLE          rdummy,fx,fy,fz;

FR_INT4AY          id; 

FR_INT4            koi[11];

FR_INT4            ndim= 0,nkp= 0,ne= 0,nfg= 0,kflag= 0;
FR_INT4            nkn= 0,ityp= 0,ifrei= 0,ibis= 0;
FR_INT4            nrb= 0,nfl= 0,iflag1= 0,ifg= 0;
FR_INT4            ktyp16= 0,ktyp17= 0,ktyp7= 0,ktyp14= 0,ktyp18= 0;
FR_INT4            ktyp20= 0,ktyp8= 0,ktyp15= 0,ktyp23= 0,ktyp24= 0;
FR_INT4            inow= 0;

FR_INT4            idummy,jdummy,ipuf,ispc,iload;
FR_INT4            i,j,k;

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
* jetzt die NASTRAN- Datei konvertieren
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
if((fi1= fopen("z88i1.txt","w"))== NULL)
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

if((fi2= fopen("z88i2.txt","w"))== NULL)
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
	        
if((fi5= fopen("z88i5.txt","w"))== NULL)
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
* 2.Durchlauf: nkp,ne,nrb aus NASTRAN Datei holen
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
  if(strncmp(cstring,"CTRIA6",6) == 0) ne++;
  if(strncmp(cstring,"CQUAD8",6) == 0) ne++;


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
* Platten und Schalen: Anzahl E-Gesetze feststellen; 
*=====================================================================*/
  if(ICFLAG == 3 || ICFLAG == 6)
    {
    if(strncmp(cstring,"PLOAD",5) == 0)
      {
      sscanf(cstring,"%s " PDB PDB PF,cdummy,&idummy,&jdummy,&rdummy);
      if(idummy == iload) 
        {
        nfl++;
        }
      }
    }


/*======================================================================
* Dimension feststellen; 
*=====================================================================*/
  if(strncmp(cstring,"CTETRA",6)== 0) ndim= 3;
  if(strncmp(cstring,"CTRIA6",6)== 0) ndim= 2;
  if(strncmp(cstring,"CQUAD8",6)== 0) ndim= 2;

  if(strncmp(cstring,"CTRIA6",6)== 0 && ICFLAG == 6) ndim= 3;/* Shell */
  if(strncmp(cstring,"CQUAD8",6)== 0 && ICFLAG == 6) ndim= 3;/* Shell */
  } 

/*----------------------------------------------------------------------
* Werte andrucken
*---------------------------------------------------------------------*/

wrim88g(ndim,TX_DIMDET);
wrim88g(nkp, TX_NODDET);
wrim88g(ne , TX_ELEDET);
wrim88g(nrb, TX_CONDET);
if(ICFLAG == 3 || ICFLAG == 6) wrim88g(nfl, TX_PELDET);

wlog88g(ndim,LOG_DIMDET);
wlog88g(nkp, LOG_NODDET);
wlog88g(ne , LOG_ELEDET);
wlog88g(nrb, LOG_CONDET);
if(ICFLAG == 3  || ICFLAG == 6) wlog88g(nfl, LOG_PELDET);

/*----------------------------------------------------------------------
* 1.Zeile Z88I1.TXT schreiben
*---------------------------------------------------------------------*/
if(ICFLAG == 1 || ICFLAG == 3) /* Volumen und Platten */
  {
  nfg= nkp*3;
  ifrei= 3;
  }

if(ICFLAG == 2 || ICFLAG == 4) /* Scheiben und Tori */
  {
  nfg= nkp*2;
  ifrei= 2;
  }

if(ICFLAG == 6) /* Schalen */
  {
  nfg= nkp*6;
  ifrei= 6;
  }

if(LANG == 1)
  fprintf(fi1,
  PD5B PD5B PD5B PD5B PD5B "  Z88I1.TXT,via Z88G V15OS NASTRAN\n",
  ndim,nkp,ne,nfg,kflag);

if(LANG == 2)
  fprintf(fi1,
  PD5B PD5B PD5B PD5B PD5B "  Z88I1.TXT, by Z88G V15OS NASTRAN\n",
  ndim,nkp,ne,nfg,kflag);

/*----------------------------------------------------------------------
* 1.Zeile Z88I2.TXT schreiben
*---------------------------------------------------------------------*/
if(LANG == 1) fprintf(fi2,PD5B "  Z88I2.TXT,via Z88G V15 NASTRAN\n",nrb);
if(LANG == 2) fprintf(fi2,PD5B "  Z88I2.TXT, by Z88G V15 NASTRAN\n",nrb);

/*----------------------------------------------------------------------
* 3.Durchlauf:
* NASTRAN Datei lesen und Z88I1.TXT, Z88I2.TXT und Z88I5.TXT schreiben
*---------------------------------------------------------------------*/
wrim88g(0,TX_REAWRI);
wlog88g(0,LOG_REAWRI);

rewind(fin);  

inow= 0;  /* um den ganzen Schrott vorher auszufiltern */

while((fgets(cstring,254,fin)) != NULL)
  {
  if(strncmp(cstring,"GRID",4)== 0) inow= 1;

/*======================================================================
* Z88I1.TXT: Knoten
*=====================================================================*/
  if(strncmp(cstring,"GRID",4)== 0)
    {
    sscanf(cstring,"%s " PDB PDB PFB PFB PFB,
           cdummy,&nkn,&idummy,&x,&y,&z);

    if(LANG == 1)
      fprintf(fi1,PD5B PD5B PE13B PE13B PE13B "  Knoten #" PD "\n", 
      nkn,ifrei,x,y,z,nkn);
    if(LANG == 2)
      fprintf(fi1,PD5B PD5B PE13B PE13B PE13B "  node #" PD "\n", 
      nkn,ifrei,x,y,z,nkn);
    }

/*======================================================================
* Z88I1.TXT: Elemente Typ 16
*=====================================================================*/
  if(strncmp(cstring,"CTETRA",6)== 0)
    {
    koi[4]= 0;
    sscanf(cstring,"%s " PDB PDB PDB PDB PDB PDB PDB PD,
           cdummy,&k,&idummy,
           &koi[0],&koi[1],&koi[2],&koi[3],&koi[4],&koi[5]);

    if(koi[4] != 0)
      {
      ityp= 16;
      ktyp16++;

      fgets(c2zeile,254,fin);   /* 2.Zeile */
      sscanf(c2zeile,PDB PDB PDB PD,&koi[6],&koi[7],&koi[8],&koi[9]);      

      fprintf(fi1,PD5B PD5B " Element " PD5 "\n",k,ityp,k); 
      fprintf(fi1,PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5 "\n",
              koi[0],koi[1],koi[2],koi[3],koi[4],
              koi[5],koi[6],koi[8],koi[9],koi[7]);
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
      fprintf(fi1,PD5B PD5B PD5B PD5 "\n",koi[0],koi[1],koi[2],koi[3]);
      ibis= k;
      }
    }

/*======================================================================
* Z88I1.TXT: Elemente Typ 7,8,20 und 23
*=====================================================================*/
  if(strncmp(cstring,"CQUAD8",6)== 0)
    {
    if(ICFLAG == 2) 
      {
      ityp= 7;
      ktyp7++;
      }

    if(ICFLAG == 3) 
      {
      ityp= 20;
      ktyp20++;
      }

    if(ICFLAG == 4) 
      {
      ityp= 8;
      ktyp8++;
      }

    if(ICFLAG == 6) 
      {
      ityp= 23;
      ktyp23++;
      }

    sscanf(cstring,"%s " PDB PDB PDB PDB PDB PDB PDB PD,
           cdummy,&k,&idummy,
           &koi[0],&koi[1],&koi[2],&koi[3],&koi[4],&koi[5]);

    fgets(c2zeile,254,fin);   /* 2.Zeile */
    sscanf(c2zeile,PDB PD,&koi[6],&koi[7]);   
			
    fprintf(fi1,PD5B PD5B " Element " PD5 "\n",k,ityp,k); 
    fprintf(fi1,PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5 "\n",
    koi[0],koi[1],koi[2],koi[3],koi[4],koi[5],koi[6],koi[7]);
    ibis= k;
    }

/*======================================================================
* Z88I1.TXT: Elemente Typ 14 und Typ 18 und Typ 15 & Typ 24
*=====================================================================*/
  if(strncmp(cstring,"CTRIA6",6)== 0)
    {
    if(ICFLAG == 2) 
      {
      ityp= 14;
      ktyp14++;
      }

    if(ICFLAG == 3) 
      {
      ityp= 18;
      ktyp18++;
      }

    if(ICFLAG == 4) 
      {
      ityp= 15;
      ktyp15++;
      }

    if(ICFLAG == 6) 
      {
      ityp= 24;
      ktyp24++;
      }

    sscanf(cstring,"%s " PDB PDB PDB PDB PDB PDB PDB PD,
           cdummy,&k,&idummy,
           &koi[0],&koi[1],&koi[2],&koi[3],&koi[4],&koi[5]);
			
    fprintf(fi1,PD5B PD5B " Element " PD5 "\n",k,ityp,k); 
    fprintf(fi1,PD5B PD5B PD5B PD5B PD5B PD5 "\n",
    koi[0],koi[1],koi[2],koi[3],koi[4],koi[5]);
    ibis= k;
    }

/*======================================================================
* Z88I2.TXT: Randbedingungen: Lager
*=====================================================================*/
  if(strncmp(cstring,"SPC",   3) == 0 && inow == 1)  
    {
    iflag1= 2;
    sscanf(cstring,"%s " PDB PDB PDB PF,cdummy,&idummy,&nkn,&ipuf,&wert);

    if(idummy == ispc)
      {
      if(ipuf == 1)    ifg= 1;
      if(ipuf == 2)    ifg= 2;
      if(ipuf == 3) 
        {
        if(ICFLAG== 3) ifg= 1;
        else           ifg= 3;
        }         		
      if(ipuf == 4) 
        {
        if(ICFLAG== 3) ifg= 2;
        if(ICFLAG== 6) ifg= 4;
        }
      if(ipuf == 5) 
        {
        if(ICFLAG== 3) ifg= 3;
        if(ICFLAG== 6) ifg= 5;
        }

      fprintf(fi2,PD5B PD5B PD5B PF10 "\n",nkn,ifg,iflag1,wert); 
      }
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
  
  }  /* Ende while 3.Durchlauf */  

wrim88g(nkp,   TX_NODDON);
wrim88g(ne ,   TX_ELEDON);
wrim88g(nrb,   TX_CONDON);
if(ICFLAG == 1)
  {
  wrim88g(ktyp16,TX_16DET);
  wrim88g(ktyp17,TX_17DET);
  }
if(ICFLAG == 2)
  {
  wrim88g(ktyp7, TX_7DET);
  wrim88g(ktyp14,TX_14DET);
  }
if(ICFLAG == 3)
  {
  wrim88g(ktyp20,TX_20DET);
  wrim88g(ktyp18,TX_18DET);
  }
if(ICFLAG == 4)
  {
  wrim88g(ktyp8, TX_8DET);
  wrim88g(ktyp15,TX_15DET);
  }
if(ICFLAG == 6)
  {
  wrim88g(ktyp23,TX_23DET);
  wrim88g(ktyp24,TX_24DET);
  }

wlog88g(nkp,   LOG_NODDON);
wlog88g(ne ,   LOG_ELEDON);
wlog88g(nrb,   LOG_CONDON);
if(ICFLAG == 1)
  {
  wlog88g(ktyp16,LOG_16DET);
  wlog88g(ktyp17,LOG_17DET);
  }
if(ICFLAG == 2)
  {
  wlog88g(ktyp7, LOG_7DET);
  wlog88g(ktyp14,LOG_14DET);
  }
if(ICFLAG == 3)
  {
  wlog88g(ktyp20,LOG_20DET);
  wlog88g(ktyp18,LOG_18DET);
  }
if(ICFLAG == 4)
  {
  wlog88g(ktyp8, LOG_8DET);
  wlog88g(ktyp15,LOG_15DET);
  }
if(ICFLAG == 6)
  {
  wlog88g(ktyp23,LOG_23DET);
  wlog88g(ktyp24,LOG_24DET);
  }

/*======================================================================
* Z88I5.TXT schreiben:
*=====================================================================*/
if(LANG == 1)
  {
  fprintf(fi5,PD5B "  Z88I5.TXT, via Z88G V15OS NASTRAN\n",nfl);
  }
  
if(LANG == 2)
  {
  fprintf(fi5,PD5B "  Z88I5.TXT, by Z88G V15OS NASTRAN\n",nfl);
  }

/*----------------------------------------------------------------------
* ggf. 4.Durchlauf fuer Platten, wenn Flaechenlasten vorhanden
* Z88I1.TXT: E-Gesetz
*---------------------------------------------------------------------*/
if((ICFLAG == 3 || ICFLAG == 6) && nfl > 0)
  {
  rewind(fin);  

/*======================================================================
* Speicher kommen lassen
*=====================================================================*/
  druck= (FR_DOUBLEAY) FR_CALLOC(nfl+1,sizeof(FR_DOUBLE));
  if(druck == NULL)
    {
    wlog88g(1,LOG_ARRAYNOTOK);
    fclose(fwlo);
    return(AL_NOMEMY);
    }
  else
    wlog88g(1,LOG_ARRAYOK);

  id= (FR_INT4AY) FR_CALLOC(nfl+1,sizeof(FR_INT4));
  if(id == NULL)
    {
    wlog88g(2,LOG_ARRAYNOTOK);
    fclose(fwlo);
    return(AL_NOMEMY);
    }
  else
    wlog88g(2,LOG_ARRAYOK);

/*======================================================================
* Vektoren fuer Druck und Element-Nummer belegen
*=====================================================================*/
  i= 0;
  while((fgets(cstring,254,fin)) != NULL)
    {
    if(strncmp(cstring,"PLOAD",5)== 0)
      {
      sscanf(cstring,"%s " PDB PDB PF,cdummy,&idummy,&jdummy,&rdummy);
      if(idummy == iload) 
        {
        i++;
        nkn= jdummy;
        fl= -rdummy;

        druck[i]= fl;
        id[i]   = nkn;
        }
      }
    }
    
    
  
  for (j=1;j<=i;j++)
  {
    fprintf(fi5,PD5B PE13 "\n",id[j],druck[j]);
  }


/*======================================================================
* Vektoren freigeben
*=====================================================================*/
  if(druck) free (druck);
  if(id)    free (id);

  } /* Ende ICFLAG == 3 */

/*----------------------------------------------------------------------
* Files schliessen und zurueck
*---------------------------------------------------------------------*/
fclose(fin);
fclose(fi1);
fclose(fi2);
fclose(fi5);

wrim88g(0,TX_Z88CS);
wlog88g(0,LOG_Z88CS);

return(0);
}

