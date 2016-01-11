/****************************************************************************
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
* V14.0 February 14, 2011
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
****************************************************************************/
/**************************************************************************** 
*  Programm z88r.c - der lineare Universal-Solver - OpenSource-Version
*  24.5.2012 Rieg
****************************************************************************/
/****************************************************************************
* Fuer UNIX
****************************************************************************/
#ifdef FR_UNIX
#include <z88r.h>  
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#endif

/****************************************************************************
* Formate
****************************************************************************/
#define NL "\n"

#ifdef FR_XINT
#define PD "%d"
#define PDB "%d "
#define B5D " %5d"
#define B1D " %1d"
#define P5DB "%5d "
#define P7DB "%7d  "
#endif

#ifdef FR_XLONG
#define PD "%ld"
#define PDB "%ld "
#define B5D " %5ld"
#define B1D " %1ld"
#define P5DB "%5ld "
#define P7DB "%7ld  "
#endif

#ifdef FR_XLOLO
#define PD "%lld"
#define PDB "%lld "
#define B5D " %5lld"
#define B1D " %1lld"
#define P5DB "%5lld "
#define P7DB "%7lld  "
#endif

#ifdef FR_XDOUB
#define PG "%lg"
#define PF "%lf"
#define PFB "%lf "
#define P15E "%+#15.7lE"
#define B315E "   %+#15.7lE"
#define B213E "  %+#13.5lE"
#define P11E "%+#11.3lE"
#endif

#ifdef FR_XQUAD
#define PG "%Lg"
#define PF "%Lf"
#define PFB "%Lf "
#define P15E "%+#15.7LE"
#define B315E "   %+#15.7LE"
#define B213E "  %+#13.5LE"
#define P11E "%+#11.3LE"
#endif

/****************************************************************************
*  Function-Declarationen
****************************************************************************/
int  dyn88r(void);
int  ale88r(int);
int  ri188r(void);
int  z88a(void);
int  z88ai(void);
int  wria88r(void);
int  lan88r(void);
int  wrim88r(FR_INT4,int);
int  wlog88r(FR_INT4,int);
int  z88br(void);
int  z88cr(void);
int  z88dr(void);
int  z88er(void);
void dro288(void);
void fnul88(void);
void fio888(void);
int  wryd88(void);
int  man88r(void);
int  int88r(void);
int  elp88r(void);
int  mat88r(void);

/****************************************************************************
*  globale Variable
****************************************************************************/
/*--------------------------------------------------------------------------
* Files
*-------------------------------------------------------------------------*/
FILE *fdyn,*fwlo,*fi1,*fi2,*fi3,*fi4,*fi5,*felp,*fint,*fmat,*fman;
FILE *fo0,*fo1,*fo2,*fo3,*fo4,*fo5,*fo8;

char cdyn[8]  = "z88.dyn";
char cl1[10]  = "z88r.log";
char ci1[10]  = "z88i1.txt";
char ci2[10]  = "z88i2.txt";
char ci5[10]  = "z88i5.txt";
char celp[12] = "z88elp.txt";
char cint[12] = "z88int.txt";
char cmat[12] = "z88mat.txt";
char cman[12] = "z88man.txt";

char co0[10] = "z88o0.txt";
char co1[10] = "z88o1.txt";
char co2[10] = "z88o2.txt";
char co3[10] = "z88o3.txt";
char co4[10] = "z88o4.txt";
char co5[10] = "z88o5.txt";
char co8[10] = "z88o8.txt";  
  
/*--------------------------------------------------------------------------
* Pointer
*-------------------------------------------------------------------------*/
FR_DOUBLEAY GS;
FR_DOUBLEAY CI;
FR_DOUBLEAY se;
FR_DOUBLEAY rs;
FR_DOUBLEAY u;     /* bekommt keinen eigenen Speicher, gemappt auf rs */
FR_DOUBLEAY xi;
FR_DOUBLEAY xa;
FR_DOUBLEAY v;
FR_DOUBLEAY pk;
FR_DOUBLEAY zz;
FR_DOUBLEAY fak;
FR_DOUBLEAY x;
FR_DOUBLEAY y;
FR_DOUBLEAY z;
FR_DOUBLEAY emod;
FR_DOUBLEAY rnue;
FR_DOUBLEAY qpara;
FR_DOUBLEAY riyy;
FR_DOUBLEAY eyy;
FR_DOUBLEAY rizz;
FR_DOUBLEAY ezz;
FR_DOUBLEAY rit;
FR_DOUBLEAY wt;
FR_DOUBLEAY pres;
FR_DOUBLEAY tr1;
FR_DOUBLEAY tr2;
FR_DOUBLEAY smw;
FR_DOUBLEAY smwku;
FR_DOUBLEAY gmw;
FR_DOUBLEAY gmwku;
FR_DOUBLEAY fsum1;
FR_DOUBLEAY fsum2;
FR_DOUBLEAY fsum3;
FR_DOUBLEAY fsum4;
FR_DOUBLEAY fsum5;
FR_DOUBLEAY fsum6;
FR_DOUBLEAY sigvku;
FR_DOUBLEAY sdu;
FR_DOUBLEAY tmt;
FR_DOUBLEAY tm;
FR_DOUBLEAY zm;

FR_INT4AY ip;
FR_INT4AY iez;
FR_INT4AY koi;
FR_INT4AY ifrei; 
FR_INT4AY ioffs;
FR_INT4AY koffs;
FR_INT4AY ityp;
FR_INT4AY ivon_elp;
FR_INT4AY ibis_elp;
FR_INT4AY ivon_int;
FR_INT4AY ibis_int;
FR_INT4AY ivon_mat;
FR_INT4AY ibis_mat;
FR_INT4AY intord;
FR_INT4AY intos;
FR_INT4AY nep;
FR_INT4AY noi;
FR_INT4AY noffs;
FR_INT4AY jsm;

/*--------------------------------------------------------------------------
* Arrays
*-------------------------------------------------------------------------*/
/* Diese Arrays werden in HEXA88,LQUA88,QSHE88 u. CSHE88 etc. verwendet */

FR_DOUBLE xk[21], yk[21], zk[21];      /* 21 ist MAXPA , HEXA88 */
FR_DOUBLE h[21];                       /* 21 ist MAXPA , HEXA88 */
FR_DOUBLE b[361];                      /* ist 6 x 60 +1, HEXA88 */
FR_DOUBLE xx[61];                      /* ist 3 x 20 +1, HEXA88 */
FR_DOUBLE d[37];                       /* ist 6 x 6  +1, HEXA88 */
FR_DOUBLE ds[37];                      /* fuer Schalenberech.   */
FR_DOUBLE dp[37];                      /* fuer Schalenberech.   */
FR_DOUBLE p[61];                       /* ist 3 x 20 +1, HEXA88 */

/* fuer Plattenberechnung */
FR_DOUBLE be[49];                      /* fuer 16-Knoten Platte  */
FR_DOUBLE hi[49];
FR_DOUBLE hj[49];
FR_DOUBLE hk[49];
FR_DOUBLE bbi[145];
FR_DOUBLE bsv[97];
FR_DOUBLE dbi[10];
FR_DOUBLE dsv[5];

FR_DOUBLE ul[61];                     /* 61 ist 20 x 3 +1 */
FR_DOUBLE f[61];                      /* 61 ist MAXFE */

/* fuer Schalenberechnung */
FR_DOUBLE xc[9];
FR_DOUBLE yc[9];
FR_DOUBLE zc[9];

FR_INT4 mcomp[21];                    /* 21 ist MAXPA */
FR_INT4 mspan[21];                    /* 21 ist MAXPA */
FR_INT4 jetyp[25];                    /* 24 Elementtypen */

/*--------------------------------------------------------------------------
* Variable
*-------------------------------------------------------------------------*/
FR_DOUBLE emode,rnuee,qparae,riyye,eyye,rizze,ezze,rite,wte,eps,rp;
FR_DOUBLE pree,tr1e,tr2e,rpomega,rpalpha;

FR_INT4   intore,nel,ktyp,maxit,kfoun,jelem,ngau,nrb,mmat,mint,melp;
FR_INT4   LANG,IDYNMEM,jpri,ifnili,icore,idumpmax,ihflag;
FR_INT4   ndim,nkp,ne,nfg,nfgp1,nkoi,kflag,ibflag,ipflag,npr,iqflag;
FR_INT4   mxknot,mxfrei,ninto,kc,isflag,mxfe,kdflag,kch1,kch2,kch3;

char      cline[256];

/*--------------------------------------------------------------------------
* vorbelegte Variable
*-------------------------------------------------------------------------*/
FR_INT4 MAXIEZ=0,MAXGS=0,MAXNFG=0,MAXK=0,MAXE=0,MAXKOI=0;
FR_INT4 MAXESM=3600,MAXPR=0,MAXGP=0,MAXTRA=2305,MAXRBD=0;
FR_INT4 MAXPEL=0,MAXMAT=0;
FR_INT4 MAXJNT=0;  /* nicht MAXINT bei Windows! */
FR_INT4 ICFLAG=1;  /* SICCG-Solver mit Sparse-Speicherung */
FR_INT4 noci=0,iquiet=0;

/*****************************************************************************
* hauptprogramm
*****************************************************************************/
int main(int argc,char *argv[])
{
FR_INT4 i,k;
int     iret;
char    cflag[10],cflagul[10];

/****************************************************************************
* Sprache feststellen
****************************************************************************/
LANG = 0;
iret= lan88r();

if(iret != 0)
  {
  ale88r(iret);
  stop88r();
  }

/****************************************************************************
* Ueberschrift
****************************************************************************/
who88r();

/****************************************************************************
* Die Flags abfragen
****************************************************************************/
if(argc <= 2)
  {
  ale88r(AL_NOCFLAG); 
  stop88r();              
  }

/*===========================================================================
* 1.Flag
*==========================================================================*/
ifnili= 0;

strcpy(cflagul,argv[1]);  
for(i= 0; i < 6; i++)
  cflag[i]= toupper(cflagul[i]);
  
if     (strcmp("-C",cflag) == 0)       /* Berechnung */
  ifnili= 0;
else if(strcmp("-T",cflag) == 0)       /* Testmode */
  ifnili= 9;
else if(strcmp("-BDOF",cflag) == 0)
  printf("\n140655\n\n");
else
  { 
  ale88r(AL_WROCFLAG); 
  stop88r();              
  }   

/*===========================================================================
* 2.Flag
*==========================================================================*/
ICFLAG = 0;

strcpy(cflagul,argv[2]);  
for(i= 0; i < 7; i++)
  cflag[i]= toupper(cflagul[i]);
  
if     (strcmp("-CHOLY",cflag) == 0)   /* Cholesky-Solver */
  ICFLAG= 0;
else if(strcmp("-SICCG",cflag) == 0)   /* SICCG-Solver */
  ICFLAG= 1;
else if(strcmp("-SORCG",cflag) == 0)   /* SORCG-Solver */
  ICFLAG= 2;
else
  { 
  ale88r(AL_WROCFLAG); 
  stop88r();              
  }      

/****************************************************************************
* Modes ausschreiben
****************************************************************************/
        if(ICFLAG == 0) wrim88r(0,TX_ICFLAG0); /* Cholesky-Solver */
        if(ICFLAG == 1) wrim88r(0,TX_ICFLAG1); /* SICCG-Solver */
        if(ICFLAG == 2) wrim88r(0,TX_ICFLAG2); /* SORCG-Solver */

        if(ifnili == 9) wrim88r(0,TX_IFNILI9); /* Testmode */
        if(ifnili == 0) wrim88r(0,TX_IFNILI0); /* Berechnung */

/****************************************************************************
* Berechnung: IFNILI= 0 oder Testmode: IFNILI = 9
****************************************************************************/
        jpri=  1;                  /* Z88O1.TXT und andere andrucken */

/*===========================================================================
* Einlesen Z88MAN.TXT. Oeffnen & schliessen erfolgt in MAN88R.C
*==========================================================================*/
        iret= man88r();
        if(iret != 0)
          {
          ale88r(iret);
          stop88r();              
          }    

/*===========================================================================
* dynamischen Speicher kommen lassen
*==========================================================================*/
        iret= dyn88r();
        if(iret != 0)
          {
          ale88r(iret);
          stop88r();              
          }    

/*===========================================================================
* Einlesen Z88I1.TXT
*==========================================================================*/
        iret= ri188r();
        if(iret != 0)
          {
          ale88r(iret);
          stop88r();              
          }     

/*===========================================================================
* Einlesen Z88INT.TXT
*==========================================================================*/
        iret= int88r();
        if(iret != 0)
          {
          ale88r(iret);
          stop88r();              
          } 

/*===========================================================================
* Einlesen Z88ELP.TXT
*==========================================================================*/
        iret= elp88r();
        if(iret != 0)
          {
          ale88r(iret);
          stop88r();              
          }   

/*===========================================================================
* Einlesen Z88MAT.TXT
*==========================================================================*/
        iret= mat88r();
        if(iret != 0)
          {
          ale88r(iret);
          stop88r();              
          }                                               

/*===========================================================================
* die Files oeffnen: Z88I2.TXT, Z88I5.TXT und
* Z88O1.TXT, Z88O2.TXT, Z88O3.TXT, Z88O4.TXT, Z88O5.TXT, Z88O8.TXT
*==========================================================================*/
/*---------------------------------------------------------------------------
* die Eingabefiles
*--------------------------------------------------------------------------*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88I2.TXT Randbedingungen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        fi2= fopen(ci2,"r");
        if(fi2 == NULL)
          {
          wlog88r(0,LOG_NOI2);
          fclose(fwlo);
          return(AL_NOI2);
          }
        rewind(fi2);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88I5.TXT Flaechenlasten: Hier nur iqflag feststellen. 
* Ansonsten sind Z88BR --> RI588I fuers Oeffnen und Schliessen zustaendig.
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        fi5= fopen(ci5,"r");
        if(fi5 == NULL) goto L1000; 
        rewind(fi5);

        fgets(cline,256,fi5);
        sscanf(cline,PD,&npr);
        if(npr == 0) iqflag = 0;
        else         iqflag = 1;
        fclose(fi5);    
L1000:;

/*---------------------------------------------------------------------------
* die Ausgabefiles
*--------------------------------------------------------------------------*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88O1.TXT aufbereitete Randbedingungen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        fo1= fopen(co1,"w+");
        if(fo1 == NULL)
          {
          wlog88r(0,LOG_NOO1);
          fclose(fwlo);
          return(AL_NOO1);
          }
        rewind(fo1);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88O2.TXT Verschiebungen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        fo2= fopen(co2,"w+");
        if(fo2 == NULL)
          {
          wlog88r(0,LOG_NOO2);
          fclose(fwlo);
          return(AL_NOO2);
          }
        rewind(fo2);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88O3.TXT Spannungen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        fo3= fopen(co3,"w+");
        if(fo3 == NULL)
          {
          wlog88r(0,LOG_NOO3);
          fclose(fwlo);
          ale88r(AL_NOO3);
          stop88r();              
          }
        rewind(fo3);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88O4.TXT Knotenkraefte
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        fo4= fopen(co4,"w+");
        if(fo4 == NULL)
          {
          wlog88r(0,LOG_NOO4);
          fclose(fwlo);
          ale88r(AL_NOO4);
          stop88r();              
          }
        rewind(fo4);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88O5.TXT fuer Z88O: Spannungen in den Gausspunkten
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        fo5= fopen(co5,"w+");
        if(fo5 == NULL)
          {
          wlog88r(0,LOG_NOO5);
          fclose(fwlo);
          ale88r(AL_NOO5);
          stop88r();              
          }
        rewind(fo5);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88O8.TXT fuer Z88O: Spannungen in den Eckknoten und mittlere Spannungen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        fo8= fopen(co8,"w+");
        if(fo8 == NULL)
          {
          wlog88r(0,LOG_NOO8);
          fclose(fwlo);
          ale88r(AL_NOO8);
          stop88r();              
          }
        rewind(fo8);

/*===========================================================================
* Z88A fuer Cholesky-Solver; Jennings
*==========================================================================*/
        if(ICFLAG == 0)
          {
          iret= z88a();
          if(iret != 0)
            {
            ale88r(iret);
            stop88r();              
            } 
          }

/*===========================================================================
* Z88AI fuer SICCG- und SORCG-Solver; Sparsematrix
*==========================================================================*/
        if(ICFLAG != 0)
          {
          iret= z88ai();
          if(iret != 0)
            {
            ale88r(iret);
            stop88r();              
            } 
          }        

/*===========================================================================
* Z88O0.TXT und Anfos fuer GS und koi andrucken
*==========================================================================*/
        iret= wria88r();  /* oeffnet und schliesst fo0 */
        if(iret != 0)
          {
          ale88r(iret);
          stop88r();              
          } 

/*===========================================================================
* Testmode? Dann Absprung, bei Berechnung weitermachen
*==========================================================================*/
        if(ifnili == 9) goto L2000;

/*===========================================================================
* z88br : Compilation + Lastvektoren
*==========================================================================*/
        iret= z88br();
        if(iret != 0)
          {
          ale88r(iret);
          stop88r();              
          }           

/*===========================================================================
* z88cr: Solver
*==========================================================================*/
        iret= z88cr();
        if(iret != 0)
          {
          ale88r(iret);
          stop88r();              
          }   

/*===========================================================================
* z88cr: Spannungsberechnung
*==========================================================================*/                         
        fnul88();           /* fsum1 ~ fsum6 = 0, smwku,gmwku,sigvku = 0   */
        u= rs;              /* z88bc liefert rs                            */
                            /* Z88ER,Z88DR+DRO288 brauchen "historisch" u  */
        z88dr();     

/*===========================================================================
* z88er: Knotenkraft-Berechnung
*==========================================================================*/   
        z88er();

/****************************************************************************
* Z88O2.TXT und Z88O8.TXT andrucken
****************************************************************************/
        dro288();           /* Z88O2.TXT andrucken */
        fio888();           /* Z88O8.TXT beschreiben */

/****************************************************************************
* Dateien schliessen und Ende
****************************************************************************/
L2000:; /* Einsprung fuer Testmode */
        fclose(fi2);
        fclose(fo1);
        fclose(fo2);
        fclose(fo3);
        fclose(fo4);
        fclose(fo5);
        fclose(fo8);
        
return;
}

/***********************************************************************
* FNUL88: Summations-Speicher nullen fuer z88er und z88dr
***********************************************************************/
void fnul88(void)
{
extern FR_DOUBLEAY fsum1;
extern FR_DOUBLEAY fsum2;
extern FR_DOUBLEAY fsum3;
extern FR_DOUBLEAY fsum4;
extern FR_DOUBLEAY fsum5;
extern FR_DOUBLEAY fsum6;
extern FR_DOUBLEAY sigvku;
extern FR_DOUBLEAY smwku;
extern FR_DOUBLEAY gmwku;

extern FR_INT4     ne,nkp,MAXGP;

FR_INT4 i;

for(i= 1;i <= nkp;i++) 
  {
  fsum1[i]= 0.;
  fsum2[i]= 0.;
  fsum3[i]= 0.;
  fsum4[i]= 0.;
  fsum5[i]= 0.;
  fsum6[i]= 0.;
  }

for(i= 1; i <= MAXGP; i++)
  sigvku[i] = 0.;

for(i= 1;i <= nkp;i++) 
  smwku[i]= 0.;

for(i= 1; i <= ne; i++)
  gmwku[i] = 0.;

return;
}

/**************************************************************************
* DRO288: Z88O2.TXT andrucken
**************************************************************************/
void dro288(void)
{
extern FILE        *fo2;
extern FR_DOUBLEAY u;
extern FR_INT4     LANG,nkp;

FR_INT4 i,k;

wrim88r(0,TX_WRIO2);
wlog88r(0,LOG_WRIO2);

if(LANG == 1)
  {
  fprintf(fo2,"Ausgabedatei Z88O2.TXT: Verschiebungen, erzeugt mit Z88R V14OS\n");
  fprintf(fo2,"                        **************\n");
  fprintf(fo2,"Lastfall: 1");
  fprintf(fo2,
  "\nKnoten         U(1)              U(2)              U(3)\
              U(4)              U(5)              U(6)\n");
  }

if(LANG == 2)
  {
  fprintf(fo2,"output file Z88O2.TXT: displacements, computed by Z88R V14OS\n");
  fprintf(fo2,"                       *************\n");
  fprintf(fo2,"Loadcase: 1");
  fprintf(fo2,
  "\nnode           U(1)              U(2)              U(3)\
              U(4)              U(5)              U(6)\n");
  }

/*----------------------------------------------------------------------
* Schleife ueber alle Knoten
*---------------------------------------------------------------------*/
k= 1;

for(i = 1;i <= nkp;i++)
  {
          
/*======================================================================
* 2 Freiheitsgrade:
*=====================================================================*/
  if (ifrei[i] == 2)
    {
    fprintf(fo2,NL B5D B315E B315E,i,u[k],u[k+1]);
    k+= 2;
    }

/*======================================================================
* 3 Freiheitsgrade:
*=====================================================================*/
  if (ifrei[i] == 3)
    {
    fprintf(fo2,NL B5D B315E B315E B315E,
    i,u[k],u[k+1],u[k+2]);
    k+= 3;
    }

/*======================================================================
* 6 Freiheitsgrade:
*=====================================================================*/
  if (ifrei[i] == 6)
    {
    fprintf(fo2,NL B5D B315E B315E B315E B315E B315E B315E,
    i,u[k],u[k+1],u[k+2],u[k+3],u[k+4],u[k+5]);
    k+= 6;
    }

/*---------------------------------------------------------------------
* Ende Schleife ueber alle Knoten
*--------------------------------------------------------------------*/
  }

fprintf(fo2,"\n");

return;
}

/**************************************************************************
* FIO888: Beschreiben von Z88O8.TXT
**************************************************************************/
void fio888(void)
{
extern FR_DOUBLEAY smw;
extern FR_DOUBLEAY gmw;

extern FR_INT4AY ityp;
extern FR_INT4AY jsm;

extern FR_INT4 isflag,nkp;

FR_INT4 k,i,janz;

/*======================================================================
* ggf. Ausschreiben von Z88O8.TXT fuer alle Nicht-Balken
*=====================================================================*/
if((isflag == 1 || isflag == 2 || isflag == 3) && 
   !(ityp[1] == 2 || ityp[1] == 5 || ityp[1] == 13))
  {

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Wieviel "Eckknoten" ? Dazu ISFLAG als Kennung fuer Z88O
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  janz= 0;
  for(k= 1; k <= nkp; k++)
    if(jsm[k] > 0) janz++;

  if(LANG == 1) fprintf(fo8," " PDB PD,janz,isflag);
  if(LANG == 2) fprintf(fo8," " PDB PD,janz,isflag);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Eckknoten mit Vergleichsspannungen in Z88O8.TXT ausschreiben
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for(k= 1; k <= nkp; k++)
    {
    if(jsm[k] > 0)
      {
      fprintf(fo8,NL P7DB P7DB P11E,k,jsm[k],smwku[k]);
      }
    }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Wieviel Elemente fuer Z88O8.TXT?
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  fprintf(fo8,NL " " PD,ne);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* mittlere Vergleichsspannungen pro Element in Z88O8.TXT ausschreiben
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for(k= 1; k <= ne; k++)
    fprintf(fo8,NL P7DB P11E,k,gmwku[k]);

  }

fprintf(fo5,"\n");
fprintf(fo8,"\n");
return;
}





