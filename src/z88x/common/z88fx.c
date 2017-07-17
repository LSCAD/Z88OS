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
* z88fx.c : von DXF nach Z88
* 10.1.2012 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88x.h>
#include <stdio.h>      /* fopen, fprintf, fclose */
#include <string.h>     /* strstr */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88x.h>
#include <stdio.h>      /* fopen, fprintf, fclose */
#include <string.h>     /* strstr */
#endif

/***********************************************************************
* Schreib/Leseformate
***********************************************************************/
#define NLB "\n "
#define NL "\n"

#define PC "%c"
#define PCB "%c "

#define PS "%s"
#define PSB "%s "

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
#define PG "%lg"
#define PGB "%lg "
#define PE13B "%+#13.5lE "
#define PE13 "%+#13.5lE"
#endif

#ifdef FR_XQUAD
#define PFB "%Lf "
#define PF "%Lf"
#define PG "%Lg"
#define PGB "%Lg "
#define PE13B "%+#13.5LE "
#define PE13 "%+#13.5LE"
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88x(FR_INT4,int);
int wlog88x(FR_INT4,int);
int ale88x(int);
void sub88x(FR_INT4);
int koi88x(FR_INT4);
int wria88x(void);
void stop88x(void);

/***********************************************************************
* hier beginnt Function z88fx
***********************************************************************/
int z88fx(void)
{
extern FILE *fdxf,*fwlo;

extern FR_DOUBLEAY x;
extern FR_DOUBLEAY y;
extern FR_DOUBLEAY z;
extern FR_DOUBLEAY wert;
extern FR_DOUBLEAY pres;
extern FR_DOUBLEAY tr1;
extern FR_DOUBLEAY tr2;

extern FR_INT4AY koi;
extern FR_INT4AY koffs;
extern FR_INT4AY ifrei;
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

extern FR_INT4 MAXNFG,MAXK,MAXE,MAXKOI,MAXPR;
extern FR_INT4 ndim,nkp,ne,nfg,kflagss,kflag,iqflag,niflag;
extern FR_INT4 nrb,npr;
extern FR_INT4 ianz,ifrej;
extern FR_INT4 ICFLAG;

extern char cxx[];

char cline[256],ctext[256],cfese[10];

FR_DOUBLE xp,yp,zp;

FR_INT4 i,j,k,kofold,nofold,idummy,jdummy,IKFLAG,ip_entities,ip_z88net;

int iret;

/***********************************************************************
* start function
***********************************************************************/
wrim88x(0,TX_Z88FX);
wlog88x(0,LOG_Z88FX);

j= 0;
k= 0;
idummy= 0;
jdummy= 0;

xp= 0.;
yp= 0.;
zp= 0.;

kofold= 0; /* nur wg. compiler warnings */

/***********************************************************************
* file fdxf = Z88X.DXF oeffnen
***********************************************************************/
wlog88x(0,LOG_FX);
wrim88x(0,TX_FX);
fdxf= fopen(cxx,"r");
if(fdxf == NULL)
  {
  wlog88x(0,LOG_NOX);
  fclose(fwlo);
  return(AL_NOX);
  }
rewind(fdxf);

wlog88x(0,LOG_REAIX);
wrim88x(0,TX_REAIX);

/***********************************************************************
* Z88I1.TXT bzw. Z888NI.TXT ausfiltern
***********************************************************************/
/*---------------------------------------------------------------------*
* 1. Zeile Z88I1.TXT oder Z88NI.TXT ausfiltern
*---------------------------------------------------------------------*/
if(ICFLAG == 4 || ICFLAG == 5)
  {
  wlog88x(0,LOG_DEC1ZI1);
  wrim88x(0,TX_DEC1ZI1);
  }

if(ICFLAG == 6)
  {
  wlog88x(0,LOG_DEC1ZNI);
  wrim88x(0,TX_DEC1ZNI);
  }

IKFLAG= 0;

/*=====================================================================*
* DXF-Version feststellen
*=====================================================================*/
do
  {
  fgets(cline,256,fdxf);
  if((strstr(cline,"AC10")) != NULL) break;      /* AC10xx gefunden */
  }
while ((strstr(cline,"EOF"))== NULL);

if(strstr(cline,"AC1009")) fprintf(fwlo,"\nAC1009");
if(strstr(cline,"AC1012")) fprintf(fwlo,"\nAC1012");
if(strstr(cline,"AC1014")) fprintf(fwlo,"\nAC1014");
if(strstr(cline,"AC1015")) fprintf(fwlo,"\nAC1015");
if(strstr(cline,"AC1018")) fprintf(fwlo,"\nAC1018");
if(strstr(cline,"AC1021")) fprintf(fwlo,"\nAC1021");
if(strstr(cline,"AC1024")) fprintf(fwlo,"\nAC1024");

rewind(fdxf);

/*=====================================================================*
* Aufsetzpunkt ENTITIES finden
*=====================================================================*/
ip_entities= 0;

do
  {  
  fgets(cline,256,fdxf);
  ip_entities++;
  }
while ((strstr(cline,"ENTITIES"))== NULL);

fprintf(fwlo,"\nip_entities=" PD,ip_entities);
fflush(fwlo);

/*=====================================================================*
* Z88I1.TXT oder Z88NI.TXT ?
*=====================================================================*/
do
  {
  fgets(cline,256,fdxf);

  if((strstr(cline,"Z88I1.TXT")) != NULL)
    {
    sscanf(cline,PSB PDB PDB PDB PDB PD,ctext,&ndim,&nkp,&ne,&nfg,&kflag);
    fprintf(fwlo,"\nZ88I1.TXT  " PDB PDB PDB PDB PD,ndim,nkp,ne,nfg,kflag);
    fflush(fwlo);
    IKFLAG= 1;
    goto L100;
    }
  
  if((strstr(cline,"Z88NI.TXT")) != NULL)
    {
    sscanf(cline,PSB PDB PDB PDB PDB PDB PDB PD,ctext,&ndim,&nkp,&ne,&nfg,&kflagss,&niflag,&kflag);
    fprintf(fwlo,"\nZ88NI.TXT " PDB PDB PDB PDB PDB PDB PD,ndim,nkp,ne,nfg,kflagss,niflag,kflag);
    fflush(fwlo);
    IKFLAG= 2;
    goto L100;
    }
  }
while ((strstr(cline,"EOF"))== NULL);

L100:;

if((ICFLAG== 4 || ICFLAG== 5) && IKFLAG != 1)
  {
  wlog88x(0,LOG_WROIXI1);
  return(AL_WROIXI1);
  }

if(ICFLAG== 6 && IKFLAG != 2)
  {
  wlog88x(0,LOG_WROIXNI);
  return(AL_WROIXNI);
  }

/*======================================================================
* Testen, ob innerhalb der zulaessigen Grenzen
*=====================================================================*/
if(!(ndim == 2 || ndim == 3))
  {
  wlog88x(ndim,LOG_WRONGDIM);
  fclose(fwlo);
  return(AL_WRONDIM);
  }

if(!(kflag == 0 || kflag == 1))
  {
  wlog88x(kflag,LOG_WROKFLAG);
  fclose(fwlo);
  return(AL_WROKFLAG);
  }

rewind(fdxf);

/*---------------------------------------------------------------------*
* Knoten ausfiltern
*---------------------------------------------------------------------*/
wlog88x(0,LOG_DECKNO);
wrim88x(0,TX_DECKNO);

j= 0;                                            /* Anzahl Knoten */

for(i= 1; i <= ip_entities; i++)                 /* Aufsetzpunkt ENTITIES */
  fgets(cline,256,fdxf);

do
  {
  fgets(cline,256,fdxf);

  if((strstr(cline,"Z88KNR")) != NULL)
    {
    do
      fgets(cline,256,fdxf);
    while ((strstr(cline," 10"))== NULL);        /* Aufsetzpunkt "10" */
    
    fgets(cline,256,fdxf);                       /* x lesen */
    sscanf(cline,PF,&xp);
    
    fgets(cline,256,fdxf);                       /* "20" leerlesen */
    fgets(cline,256,fdxf);                       /* y lesen */
    sscanf(cline,PF,&yp);
    
    fgets(cline,256,fdxf);                       /* "30" leerlesen */
    fgets(cline,256,fdxf);                       /* z lesen */
    sscanf(cline,PF,&zp);

    do
      {
      fgets(cline,256,fdxf);
      if((strstr(cline,"EOF")) != NULL) return(AL_NOPOINTS);
      }
    while ((strstr(cline,"P "))== NULL);         /* Aufsetzpunkt "P " */

    sscanf(cline,PSB PD,ctext,&k);               /* k lesen */

    x[k]= xp;                                    /* umspeichern */
    y[k]= yp;
    z[k]= zp;

    j++;                                         /* Knoten hochzaehlen */
    } 
  }
while ((strstr(cline,"EOF"))== NULL);

/*=====================================================================
* gefundene Knoten in Z88X.LOG zur Kontrolle schreiben
*====================================================================*/
for(i=1; i<= j;i++)
  {
  fprintf(fwlo,NL PDB "X=" PG "Y=" PG "Z=" PG,i,x[i],y[i],z[i]);
  fflush(fwlo);
  }

/*=====================================================================
* Kontrolle und Ausschrieb, Rewind
*====================================================================*/
if(j != nkp)                                     /* falsche Anzahl Knoten */
  {
  wlog88x(0,LOG_WROIXKNO);
  return(AL_WROIXKNO);
  }

wrim88x(j,TX_FOUKNO);
wlog88x(j,LOG_FOUKNO);

rewind(fdxf);

/*---------------------------------------------------------------------*
* Elemente ausfiltern
*---------------------------------------------------------------------*/
wlog88x(0,LOG_DECELE);
wrim88x(0,TX_DECELE);

IKFLAG= 0;

if(ICFLAG== 6)
  strcpy(cfese,"SE ");
else
  strcpy(cfese,"FE ");

for(i= 1; i <= ip_entities; i++)                 /* Aufsetzpunkt ENTITIES */
  fgets(cline,256,fdxf);

do
  {
  fgets(cline,256,fdxf);
  if((strstr(cline,cfese)) != NULL)
    {
    sscanf(cline,PSB PD,ctext,&k);
    sscanf(cline,PSB PDB PD,ctext,&idummy,&ityp[k]);
    if(ICFLAG != 6)
      {
      fprintf(fwlo,NL PDB "FE=" PD,k,ityp[k]);
      fflush(fwlo);
      }

    if(ICFLAG == 6)
      {
      if(ityp[k] == 1 || ityp[k] == 10 || ityp[k] == 21)
        {
        sscanf(cline,PSB PDB PDB PDB PDB PCB PDB PCB PDB PC,
        ctext,&idummy,&jdummy,&itypfe[k],
        &jel[k],&cjmode[k],&iel[k],&cimode[k],&kel[k],&ckmode[k]);
        fprintf(fwlo,NL PDB "SE=" PDB "FE=" PDB PDB PCB PDB PCB PDB PC,
        k,ityp[k],itypfe[k],jel[k],cjmode[k],iel[k],cimode[k],kel[k],ckmode[k]);
        fflush(fwlo);
        }
      else
        {
        sscanf(cline,PSB PDB PDB PDB PDB PCB PDB PC,
        ctext,&idummy,&jdummy,&itypfe[k],&jel[k],&cjmode[k],&iel[k],&cimode[k]);
        fprintf(fwlo,NL PDB "SE=" PDB "FE=" PDB PDB PCB PDB PC,
        k,ityp[k],itypfe[k],jel[k],cjmode[k],iel[k],cimode[k]);
        fflush(fwlo);
        }
      }
    IKFLAG++;
    } 
  }
while ((strstr(cline,"EOF"))== NULL);


/*=====================================================================
* Kontrolle und Ausschrieb, Rewind
*====================================================================*/
if(IKFLAG != ne)                                 /* falsche Anzahl Elemente */
  {
  wlog88x(0,LOG_WROIXELE);
  return(AL_WROIXELE);
  }

if(ICFLAG == 6)
  {
  wrim88x(IKFLAG,TX_FOUSELE);
  wlog88x(IKFLAG,LOG_FOUSELE);
  }
else
  {
  wrim88x(IKFLAG,TX_FOUFELE);
  wlog88x(IKFLAG,LOG_FOUFELE);
  }

rewind(fdxf);

/*=====================================================================
* aufsetzpunkt fuer koinzidenz finden
*====================================================================*/
for(i= 1; i <= ip_entities; i++)                 /* Aufsetzpunkt ENTITIES */
  fgets(cline,256,fdxf);

ip_z88net = ip_entities;

do                                               /* dann 1. LINE finden */
  {  
  fgets(cline,256,fdxf);
  if((strstr(cline,"EOF")) != NULL) return(AL_NOLAYNET);
  ip_z88net++;
  }
while ((strstr(cline,"Z88NET"))== NULL);

fprintf(fwlo,"\nip_z88net=" PD,ip_z88net);
fflush(fwlo);

/*====================================================================-
* grosse elementschleife
*====================================================================*/
for(i= 1; i <= ne; i++)
  {
  if(i== 1) koffs[1]= 1;
  else      koffs[i]= koffs[i-1] + kofold;

  sub88x(i);                                     /* Anzahl Knoten liefern */
  iret= koi88x(i);                               /* Elemente scannen */
  if(iret != 0)
    {
    wlog88x(0,LOG_TOOFEW);
    return(AL_TOOFEW);
    }

  kofold= ianz;
  }

/*====================================================================-
* ueberpruefen je element, ob 2 gleiche knoten
*====================================================================*/
for(i= 1; i <= ne; i++)
  {
  sub88x(i);

  for(j= 2; j <= ianz; j++)
    {
    for(k= 1; k < j; k++)
       {
       if(koi[koffs[i]+k-1] == koi[koffs[i]+j-1])
         {
         wlog88x(i,LOG_WROIXKOI);
         return(AL_WROIXKOI);
         }
       } 
    }
  }  

/*====================================================================-
* vektor ifrei belegen
*====================================================================*/
for(i= 1; i <= nkp; i++)
  ifrei[i]= 0;

for(i= 1; i <= ne; i++)
  {
  sub88x(i);
  for(j= 1; j <= ianz; j++)
    {
    if(ifrej > ifrei[koi[koffs[i]+j-1]])
      {
      ifrei[koi[koffs[i]+j-1]]= ifrej;
      }
    }
  }

rewind(fdxf);

/***********************************************************************
* Randbedingungen Z88I2.TXT ausfiltern
***********************************************************************/
if(ICFLAG == 5)
  {
/*---------------------------------------------------------------------*
* Randbedingungen Z88I2.TXT: 1.Zeile ausfiltern
*---------------------------------------------------------------------*/
  wlog88x(0,LOG_DEC1ZI2);
  wrim88x(0,TX_DEC1ZI2);

  IKFLAG= 0;

  for(i= 1; i <= ip_entities; i++)               /* Aufsetzpunkt ENTITIES */
    fgets(cline,256,fdxf);

  do
    {
    fgets(cline,256,fdxf);
    if((strstr(cline,"Z88I2.TXT")) != NULL)
      {
      sscanf(cline,PSB PD,ctext,&nrb);
      fprintf(fwlo,"\nZ88I2.TXT " PD,nrb);
      fflush(fwlo);
      IKFLAG= 1;
      goto L200;
      }
    }
  while ((strstr(cline,"EOF"))== NULL);

  if(IKFLAG != 1)
    {
    wlog88x(0,LOG_WROIXI21Z);
    return(AL_WROIXI21Z);
    }

  L200:;
  rewind(fdxf);

/*---------------------------------------------------------------------*
* Randbedingungen Z88I2.TXT: Randbedingungen
*---------------------------------------------------------------------*/
  wlog88x(0,LOG_DECI2R);
  wrim88x(0,TX_DECI2R);

  IKFLAG= 0;

  for(i= 1; i <= ip_entities; i++)              /* Aufsetzpunkt ENTITIES */
    fgets(cline,256,fdxf);

  do
    {
    fgets(cline,256,fdxf);
    if((strstr(cline,"RBD ")) != NULL)
      {
      sscanf(cline,PSB PD,ctext,&j);
      sscanf(cline,PSB PDB PDB PDB PDB PF,ctext,&idummy,&nkn[j],&ifg[j],&irflag[j],&wert[j]);
      fprintf(fwlo,"\nRBD " PDB PDB PDB PDB PG,j,nkn[j],ifg[j],irflag[j],wert[j]);
      fflush(fwlo);
      IKFLAG++;
      }
    }
  while ((strstr(cline,"EOF"))== NULL);

  if(IKFLAG != nrb)                              /* falsche Anzahl RBD */
    {
    wlog88x(0,LOG_WROIXI2R);
    return(AL_WROIXI2R);
    }

  rewind(fdxf);
  }

/***********************************************************************
* Flaechenlasten Z88I5.TXT ausfiltern
***********************************************************************/
if(ICFLAG == 5)
  {
/*---------------------------------------------------------------------*
* Randbedingungen Z88I5.TXT: 1.Zeile ausfiltern
*---------------------------------------------------------------------*/
  wlog88x(0,LOG_DEC1ZI5);
  wrim88x(0,TX_DEC1ZI5);

  IKFLAG= 0;

  for(i= 1; i <= ip_entities; i++)               /* Aufsetzpunkt ENTITIES */
    fgets(cline,256,fdxf);

  do
    {
    fgets(cline,256,fdxf);
    if((strstr(cline,"Z88I5.TXT")) != NULL)
      {
      sscanf(cline,PSB PD,ctext,&npr);
      fprintf(fwlo,"\nZ88I5.TXT " PD,npr);
      fflush(fwlo);
      IKFLAG= 1;
      goto L300;
      }
    }
  while ((strstr(cline,"EOF"))== NULL);

  if(IKFLAG != 1)
    {
    wlog88x(0,LOG_WROIXI51Z);
    return(AL_WROIXI51Z);
    }

  L300:;
  rewind(fdxf);

/*---------------------------------------------------------------------*
* iqflag?
*---------------------------------------------------------------------*/
  if(npr > 0) iqflag = 1;
  else        iqflag = 0;

  if(iqflag == 0) goto L1000;  // keine Flaechenlasten: do umspringen

/*---------------------------------------------------------------------*
* Flaechenlasten Z88I5.TXT: Flaechenlasten
*---------------------------------------------------------------------*/
  wlog88x(0,LOG_DECI5R);
  wrim88x(0,TX_DECI5R);

  IKFLAG= 0;

  for(i= 1; i <= ip_entities; i++)              /* Aufsetzpunkt ENTITIES */
    fgets(cline,256,fdxf);

  do
    {
    fgets(cline,256,fdxf);
    if((strstr(cline,"FLA ")) != NULL)
      {
      sscanf(cline,PSB PD,ctext,&j);
      sscanf(cline,PSB PDB PD,ctext,&idummy,&nep[j]);

/*======================================================================
* Elementtypen 7, 8, 14, 15
*=====================================================================*/
      if(ityp[nep[j]]== 7  || ityp[nep[j]]== 8 ||
         ityp[nep[j]]== 14 || ityp[nep[j]]== 15) 
        {
        if(j== 1)  noffs[1]= 1;
        else       noffs[j]= noffs[j-1] + nofold;
    
        sscanf(cline,PSB PDB PDB PFB PFB PDB PDB PD,ctext,&idummy,&jdummy,
        &pres[j],&tr1[j],&noi[noffs[j]],&noi[noffs[j]+1],&noi[noffs[j]+2]);  

        nofold= 3;

        fprintf(fwlo,"\nFLA " PDB PDB PGB PGB PDB PDB PD,
        j,nep[j],pres[j],tr1[j],noi[noffs[j]],noi[noffs[j]+1],noi[noffs[j]+2]);

        fflush(fwlo);
        IKFLAG++;
        }

/*======================================================================
* Elementtyp 10 u. 21
*=====================================================================*/
      if(ityp[nep[j]]== 10 || ityp[nep[j]]== 21) 
        {
        if(j== 1)  noffs[1]= 1;
        else       noffs[j]= noffs[j-1] + nofold;
    
        sscanf(cline,PSB PDB PDB PFB PFB PFB PDB PDB PDB PDB PDB PDB PDB PD,
        ctext,&idummy,&jdummy,&pres[j],&tr1[j],&tr2[j],
        &noi[noffs[j]   ], &noi[noffs[j] +1], 
        &noi[noffs[j] +2], &noi[noffs[j] +3], 
        &noi[noffs[j] +4], &noi[noffs[j] +5],
        &noi[noffs[j] +6], &noi[noffs[j] +7]); 

        nofold= 8;

        fprintf(fwlo,"\nFLA " PDB PDB PGB PGB PGB PDB PDB PDB PDB PDB PDB PDB PD,
        j,nep[j],pres[j],tr1[j],tr2[j],
        noi[noffs[j]   ], noi[noffs[j] +1], 
        noi[noffs[j] +2], noi[noffs[j] +3], 
        noi[noffs[j] +4], noi[noffs[j] +5],
        noi[noffs[j] +6], noi[noffs[j] +7]); 
        fflush(fwlo);
        IKFLAG++;
        }

/*======================================================================
* Elementtyp 16
*=====================================================================*/
      if(ityp[nep[j]]== 16) 
        {
        if(j== 1)  noffs[1]= 1;
        else       noffs[j]= noffs[j-1] + nofold;
    
        sscanf(cline,PSB PDB PDB PFB PDB PDB PDB PDB PDB PD,
        ctext,&idummy,&jdummy,&pres[j],
        &noi[noffs[j]   ], &noi[noffs[j] +1], 
        &noi[noffs[j] +2], &noi[noffs[j] +3], 
        &noi[noffs[j] +4], &noi[noffs[j] +5]); 

        nofold= 6;

        fprintf(fwlo,"\nFLA " PDB PDB PGB PDB PDB PDB PDB PDB PD,
        j,nep[j],pres[j],
        noi[noffs[j]   ], noi[noffs[j] +1], 
        noi[noffs[j] +2], noi[noffs[j] +3], 
        noi[noffs[j] +4], noi[noffs[j] +5]); 
        fflush(fwlo);
        IKFLAG++;
        }

/*======================================================================
* Elementtyp 17
*=====================================================================*/
      if(ityp[nep[j]]== 17) 
        {
        if(j== 1)  noffs[1]= 1;
        else       noffs[j]= noffs[j-1] + nofold;
    
        sscanf(cline,PSB PDB PDB PFB PDB PDB PD,
        ctext,&idummy,&jdummy,&pres[j],
        &noi[noffs[j]   ], &noi[noffs[j] +1], &noi[noffs[j] +2]); 

        nofold= 4;

        fprintf(fwlo,"\nFLA " PDB PDB PGB PDB PDB PD,
        j,nep[j],pres[j],
        noi[noffs[j]   ], noi[noffs[j] +1], noi[noffs[j] +2]); 
        fflush(fwlo);
        IKFLAG++;
        }

/*======================================================================
* Elementtyp 22
*=====================================================================*/
      if(ityp[nep[j]]== 22) 
        {
        if(j== 1)  noffs[1]= 1;
        else       noffs[j]= noffs[j-1] + nofold;
    
        sscanf(cline,PSB PDB PDB PFB PFB PFB PDB PDB PDB PDB PDB PD,
        ctext,&idummy,&jdummy,&pres[j],&tr1[j],&tr2[j],
        &noi[noffs[j]   ], &noi[noffs[j] +1], 
        &noi[noffs[j] +2], &noi[noffs[j] +3], 
        &noi[noffs[j] +4], &noi[noffs[j] +5]); 

        nofold= 6;

        fprintf(fwlo,"\nFLA " PDB PDB PGB PGB PGB PDB PDB PDB PDB PDB PD,
        j,nep[j],pres[j],tr1[j],tr2[j],
        noi[noffs[j]   ], noi[noffs[j] +1], 
        noi[noffs[j] +2], noi[noffs[j] +3], 
        noi[noffs[j] +4], noi[noffs[j] +5]); 
        fflush(fwlo);
        IKFLAG++;
        }


/*======================================================================
* Elementtyp 1
*=====================================================================*/
      if(ityp[nep[j]]== 1) 
        {
        if(j== 1)  noffs[1]= 1;
        else       noffs[j]= noffs[j-1] + nofold;
    
        sscanf(cline,PSB PDB PDB PFB PFB PFB PDB PDB PDB PD,
        ctext,&idummy,&jdummy,&pres[j],&tr1[j],&tr2[j],
        &noi[noffs[j]   ], &noi[noffs[j] +1], 
        &noi[noffs[j] +2], &noi[noffs[j] +3]); 

        nofold= 4;

        fprintf(fwlo,"\nFLA " PDB PDB PGB PGB PGB PDB PDB PDB PD,
        j,nep[j],pres[j],tr1[j],tr2[j],
        noi[noffs[j]   ], noi[noffs[j] +1], 
        noi[noffs[j] +2], noi[noffs[j] +3]); 
        fflush(fwlo);
        IKFLAG++;
        }

/*======================================================================
* Elementtypen 11 und 12
*=====================================================================*/
      if(ityp[nep[j]]== 11 || ityp[nep[j]]== 12) 
        {
        if(j== 1)  noffs[1]= 1;
        else       noffs[j]= noffs[j-1] + nofold;
    
        sscanf(cline,PSB PDB PDB PFB PFB PDB PDB PDB PD,
        ctext,&idummy,&jdummy,&pres[j],&tr1[j],
        &noi[noffs[j]   ], &noi[noffs[j] +1], 
        &noi[noffs[j] +2], &noi[noffs[j] +3]); 

        nofold= 4;

        fprintf(fwlo,"\nFLA " PDB PDB PGB PGB PDB PDB PDB PD,
        j,nep[j],pres[j],tr1[j],
        noi[noffs[j]   ], noi[noffs[j] +1], 
        noi[noffs[j] +2], noi[noffs[j] +3]); 
        fflush(fwlo);
        IKFLAG++;
        }

/*======================================================================
* Elementtyp 18,19,20,23 und 24
*=====================================================================*/
      if(ityp[nep[j]]== 18 || ityp[nep[j]]== 19 || ityp[nep[j]]== 20 ||
         ityp[nep[j]]== 23 || ityp[nep[j]]== 24) 
        {
        sscanf(cline,PSB PDB PDB PF,ctext,&idummy,&jdummy,&pres[j]); 

        fprintf(fwlo,"\nFLA " PDB PDB PG,j,nep[j],pres[j]); 
        fflush(fwlo);
        IKFLAG++;
        }

      }
    }
  while ((strstr(cline,"EOF"))== NULL);

  if(IKFLAG != npr)                              /* falsche Anzahl FLA */
    {
    wlog88x(0,LOG_WROIXI5R);
    return(AL_WROIXI5R);
    }

  rewind(fdxf);
  }

/***********************************************************************
* Beschreiben der Z88-Files
***********************************************************************/
L1000:;

iret= wria88x();

/***********************************************************************
* Ende Z88FX
***********************************************************************/
wlog88x(0,LOG_EXITZ88FX);
wrim88x(0,TX_EXITZ88FX);

return(iret);
}

