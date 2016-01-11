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
* COSM88
* 21.7.2011 Rieg
* wandelt COSMOS-Files aus Pro/MESH (PTC,Pro/ENGINEER) 
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
*  COSM88
****************************************************************************/
int cosm88(void)
{
extern FILE        *fwlo,*fpro,*fi1,*fi2,*fi5;

extern FR_INT4     ICFLAG,LANG;

extern char        ccos[];
extern char        ci1[];
extern char        ci2[];

FR_DOUBLEAY        druck;

FR_DOUBLE          x= 0.,y= 0.,z= 0.;
FR_DOUBLE          wert= 0.;
FR_DOUBLE          fl= 0.; 

FR_INT4AY          id; 

FR_INT4            koi[11];

FR_INT4            ndim= 0,nkp= 0,ne= 0,nfg= 0,kflag= 0;
FR_INT4            nkn= 0,ityp= 0,ifrei= 0,ibis= 0;
FR_INT4            nrb= 0,nfl= 0,iflag1= 0,ifg= 0;
FR_INT4            ktyp16= 0,ktyp17= 0,ktyp7= 0,ktyp14= 0;
FR_INT4            ktyp18= 0,ktyp20= 0,ktyp8= 0,ktyp15= 0;

FR_INT4            i,j,k;

char               cstring[255];
char               csep[]= ",";
char               *cteils;


/*----------------------------------------------------------------------
* COSMOS- File oeffnen
*---------------------------------------------------------------------*/	
if((fpro= fopen(ccos,"r"))== NULL)
  {
  wlog88g(0,LOG_NOCOS);
  fclose(fwlo);
  return(AL_NOCOS);
  }
else
  {
  wrim88g(0,TX_COSOPEN);
  }
	
rewind(fpro);
	
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
* 1.Durchlauf:
* nkp,ne,nrb aus COSMOS Datei ermitteln
*---------------------------------------------------------------------*/	
while((fgets(cstring,254,fpro))!= NULL)
  {

  if(strncmp(cstring,"ND", 2) == 0) nkp++;
  if(strncmp(cstring,"EL", 2) == 0) ne++;
  if(strncmp(cstring,"DND",3) == 0) nrb++;
  if(strncmp(cstring,"FND",3) == 0) nrb++;

/*======================================================================
* Platten: Anzahl E-Gesetze feststellen; 
*=====================================================================*/
  if(ICFLAG == 3)
    {
    if(strncmp(cstring,"PEL",3) == 0)
      {
      nfl++;
      }
    }

  if((strncmp(cstring,"EL",2)== 0)&&(strstr(cstring,"VL,0,10"))) ndim= 3;
  if((strncmp(cstring,"EL",2)== 0)&&(strstr(cstring,"VL,0,4")))  ndim= 3;
  if((strncmp(cstring,"EL",2)== 0)&&(strstr(cstring,"SF,0,8")))  ndim= 2;  
  if((strncmp(cstring,"EL",2)== 0)&&(strstr(cstring,"SF,0,6")))  ndim= 2;

  } /* 1.Durchlauf fertig */


wrim88g(ndim,TX_DIMDET);
wrim88g(nkp, TX_NODDET);
wrim88g(ne , TX_ELEDET);
wrim88g(nrb, TX_CONDET);
if(ICFLAG == 3) wrim88g(nfl, TX_PELDET);

wlog88g(ndim,LOG_DIMDET);
wlog88g(nkp, LOG_NODDET);
wlog88g(ne , LOG_ELEDET);
wlog88g(nrb, LOG_CONDET);
if(ICFLAG == 3) wlog88g(nfl, LOG_PELDET);

/*----------------------------------------------------------------------
* 1.Zeile Z88I1.TXT schreiben
*---------------------------------------------------------------------*/
if(ICFLAG == 1 || ICFLAG == 3)
  {
  nfg= nkp*3;
  ifrei= 3;
  }

if(ICFLAG == 2 || ICFLAG == 4)
  {
  nfg= nkp*2;
  ifrei= 2;
  }

if(LANG == 1)
  fprintf(fi1,PD5B PD5B PD5B PD5B PD5B "  Z88I1.TXT,via Z88G V14OS COSMOS\n",
  ndim,nkp,ne,nfg,kflag);

if(LANG == 2)
  fprintf(fi1,PD5B PD5B PD5B PD5B PD5B "  Z88I1.TXT, by Z88G V14OS COSMOS\n",
  ndim,nkp,ne,nfg,kflag);

/*----------------------------------------------------------------------
* 1.Zeile Z88I2.TXT schreiben
*---------------------------------------------------------------------*/
if(LANG == 1) fprintf(fi2,PD5B "  Z88I2.TXT,via Z88G V14OS COSMOS\n",nrb);
if(LANG == 2) fprintf(fi2,PD5B "  Z88I2.TXT, by Z88G V14OS COSMOS\n",nrb);

/*----------------------------------------------------------------------
* 2.Durchlauf:
* COSMOS Datei lesen und Z88I1.TXT und Z88I2.TXT schreiben
*---------------------------------------------------------------------*/
wrim88g(0,TX_REAWRI);
wlog88g(0,LOG_REAWRI);

rewind(fpro);  

fgets(cstring,254,fpro);

while((fgets(cstring,254,fpro)) != NULL)
  {
/*======================================================================
* Z88I1.TXT: Knoten
*=====================================================================*/
  if(strncmp(cstring,"ND",2)== 0)
    {
    cteils= strtok(cstring,csep);
    cteils= strtok(NULL,csep);
    nkn= atoi(cteils);

    cteils= strtok(NULL,csep);
    x= atof(cteils);

    cteils= strtok(NULL,csep);
    y= atof(cteils); 

    if(ndim == 3)
      {
      cteils= strtok(NULL,csep);
      z= atof(cteils); 
      }

    if(LANG == 1)
      fprintf(fi1,PD5B PD5B PE13B PE13B PE13B "  Knoten #" PD "\n", 
      nkn,ifrei,x,y,z,nkn);
    if(LANG == 2)
      fprintf(fi1,PD5B PD5B PE13B PE13B PE13B "  node #" PD "\n", 
      nkn,ifrei,x,y,z,nkn);
    }

/*======================================================================
* Z88I1.TXT: Elemente
* Typ 16
*=====================================================================*/
  if((strncmp(cstring,"EL",2)== 0) && (strstr(cstring,"VL,0,10")))
    {
    ityp= 16;
    ktyp16++;
    cteils= strtok(cstring,csep);
    cteils= strtok(NULL,csep);
    k= atoi(cteils);

    for(i = 1;i <= 3;i++) cteils= strtok(NULL, csep);

    for(i = 0;i < 10;i++)
      {
      cteils= strtok(NULL,csep);
      koi[i] = atoi(cteils);
      }
			
    fprintf(fi1,PD5B PD5B " Element " PD5B "\n",k,ityp,k); 
    fprintf(fi1,PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5 "\n",
            koi[0],koi[1],koi[2],koi[3],koi[4],
            koi[5],koi[6],koi[8],koi[9],koi[7]);
    ibis= k;
    }

/*======================================================================
* Z88I1.TXT: Elemente
* Typ 17
*=====================================================================*/
  if((strncmp(cstring,"EL",2)== 0) && (strstr(cstring,"VL,0,4")))
    {
    ityp= 17;
    ktyp17++;
    cteils= strtok(cstring,csep);
    cteils= strtok(NULL,csep);
    k= atoi(cteils);

    for(i = 1;i <= 3;i++) cteils= strtok(NULL, csep);

    for(i = 0;i < 4;i++)
      {
      cteils= strtok(NULL,csep);
      koi[i] = atoi(cteils);
      }
			
    fprintf(fi1,PD5B PD5B " Element " PD5B "\n",k,ityp,k); 
    fprintf(fi1,PD5B PD5B PD5B PD5B "\n",koi[0],koi[1],koi[2],koi[3]);
    ibis= k;
    }

/*======================================================================
* Z88I1.TXT: Elemente Typ 7 und Typ 20 und Typ 8
*=====================================================================*/
  if((strncmp(cstring,"EL",2)== 0) && (strstr(cstring,"SF,0,8")))
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

    cteils= strtok(cstring,csep);
    cteils= strtok(NULL,csep);
    k= atoi(cteils);

    for(i = 1;i <= 3;i++) cteils= strtok(NULL, csep);

    for(i = 0;i < 8;i++)
      {
      cteils= strtok(NULL,csep);
      koi[i] = atoi(cteils);
      }
			
    fprintf(fi1,PD5B PD5B " Element " PD5 "\n",k,ityp,k); 
    fprintf(fi1,PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5 "\n",
    koi[0],koi[1],koi[2],koi[3],koi[4],koi[5],koi[6],koi[7]);
    ibis= k;
    }

/*======================================================================
* Z88I1.TXT: Elemente Typ 14 und Typ 18 und Typ 15
*=====================================================================*/
  if((strncmp(cstring,"EL",2)== 0) && (strstr(cstring,"SF,0,6")))
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

    cteils= strtok(cstring,csep);
    cteils= strtok(NULL,csep);
    k= atoi(cteils);

    for(i = 1;i <= 3;i++) cteils= strtok(NULL, csep);

    for(i = 0;i < 6;i++)
      {
      cteils= strtok(NULL,csep);
      koi[i] = atoi(cteils);
      }
			
    fprintf(fi1,PD5B PD5B " Element " PD5 "\n",k,ityp,k); 
    fprintf(fi1,PD5B PD5B PD5B PD5B PD5B PD5 "\n",
    koi[0],koi[1],koi[2],koi[3],koi[4],koi[5]);
    ibis= k;
    }
		
/*======================================================================
* Z88I2.TXT: Randbedingungen: Lager
*=====================================================================*/
  if(strncmp(cstring,"DND",3)== 0)
    {
    iflag1= 2;
    cteils= strtok(cstring,csep);
    cteils= strtok(NULL,csep);
    nkn= atoi(cteils);

    cteils= strtok(NULL,csep);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verschiebungen gleich Null
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(cteils[0]== 'U')
      {
      if(cteils[1]== 'X') ifg= 1;
      if(cteils[1]== 'Y') ifg= 2;
      if(cteils[1]== 'Z') 
        {
        if(ICFLAG== 3)    ifg= 1;
        else              ifg= 3;
        }
      }                 		

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Rotationen gleich Null bei Platten
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(cteils[0]== 'R' && ICFLAG == 3)
      {
      if(cteils[1]== 'X') ifg= 2;
      if(cteils[1]== 'Y') ifg= 3;
      if(cteils[1]== 'Z') goto Lneu;  /* gibt's gar nicht */
      }                 		

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* ..und ausschreiben
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    cteils= strtok(NULL,csep);
    wert= atof(cteils);
			
    fprintf(fi2,PD5B PD5B PD5B PF10 "\n",nkn,ifg,iflag1,wert);
    }
		
/*======================================================================
* Z88I2.TXT: Randbedingungen: Kraefte
*=====================================================================*/
  if(strncmp(cstring,"FND",3)== 0)
    {
    iflag1= 1;
    cteils= strtok(cstring,csep);
    cteils= strtok(NULL,csep);
    nkn= atoi(cteils);	

    cteils= strtok(NULL,csep);
    if(cteils[1]== 'X') ifg= 1;
    if(cteils[1]== 'Y') ifg= 2;
    if(cteils[1]== 'Z') ifg= 3;
                        		
    cteils= strtok(NULL,csep);
    wert= atof(cteils);

    fprintf(fi2,PD5B PD5B PD5B PF10 "\n",nkn,ifg,iflag1,wert);
    }
  
Lneu:;
  }  /* Ende while 2.Durchlauf */  

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


/*======================================================================
* Z88I5.TXT: erste Zeile
*=====================================================================*/
if(LANG == 1)
  fprintf(fi5,PD5B "  Z88I5.TXT,via Z88G V14OS NASTRAN\n",nfl);
if(LANG == 2)
  fprintf(fi5,PD5B "  Z88I5.TXT, by Z88G V14OS NASTRAN\n",nfl);

/*----------------------------------------------------------------------
* ggf. 3.Durchlauf fuer Platten, wenn Flaechenlasten vorhanden
* Z88I5.TXT: Druecke
*---------------------------------------------------------------------*/
if(ICFLAG == 3 && nfl > 0)
  {
  rewind(fpro);

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
  while((fgets(cstring,254,fpro)) != NULL)
    {
    if(strncmp(cstring,"PEL",3)== 0)
      {
      i++;

      cteils= strtok(cstring,csep);
      cteils= strtok(NULL,csep);
      nkn= atoi(cteils);

      cteils= strtok(NULL,csep);
      fl= atof(cteils);

      druck[i]= fl;
      id[i]   = nkn;
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
fclose(fpro);
fclose(fi1);
fclose(fi2);
fclose(fi5);

wrim88g(0,TX_Z88CS);
wlog88g(0,LOG_Z88CS);

return(0);
}
