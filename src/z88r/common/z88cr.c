/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows & 
* UNIX OS.
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
* z88cr.c
* Einbau der Randbedingungen basiert gedanklich auf
* einem FORTRAN-Programm von H.R.Schwarz, Uni Zuerich. 
* 2.12.2015 Rieg 
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>    /* FILE,NULL,fopen,fclose,rewind */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <stdio.h>    /* FILE,NULL,fopen,fclose,rewind */
#endif

/***********************************************************************
* Formate
***********************************************************************/
#define NL "\n"

#ifdef FR_XINT
#define PD "%d"
#define PDB "%d "
#define B5D " %5d"
#define B1D " %1d"
#endif

#ifdef FR_XLONG
#define PD "%ld"
#define PDB "%ld "
#define B5D " %5ld"
#define B1D " %1ld"
#endif

#ifdef FR_XLOLO
#define PD "%lld"
#define PDB "%lld "
#define B5D " %5lld"
#define B1D " %1lld"
#endif

#ifdef FR_XDOUB
#define PG "%lg"
#define PF "%lf"
#define P15E "%+#15.7lE"
#define B315E "   %+#15.7lE"
#endif

#ifdef FR_XQUAD
#define PG "%Lg"
#define PF "%Lf"
#define P15E "%+#15.7LE"
#define B315E "   %+#15.7LE"
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88r(FR_INT4,int);
int wlog88r(FR_INT4,int);
int wran88j(FR_INT4,FR_INT4);
int scal88i(void);
int scal88f(void);
int choy88(void);
int siccg88(void);
int sorcg88(void);
int prfl88(void);

/***********************************************************************
* hier beginnt Function z88cr
***********************************************************************/
int z88cr(void)
{
extern FILE *fi2,*fo1,*fwlo;
extern char ci2[],co1[],co2[],co6[];

extern FR_DOUBLEAY GS;
extern FR_DOUBLEAY rs;
extern FR_DOUBLEAY fak;
extern FR_DOUBLEAY x;
extern FR_DOUBLEAY y;
extern FR_DOUBLEAY z;

extern FR_INT4AY ip;
extern FR_INT4AY iez;
extern FR_INT4AY ioffs; 
extern FR_INT4AY ifrei; 

extern FR_DOUBLE  eps,rp,rpomega,rpalpha;
extern FR_INT4 kfoun,nkp,nfg,maxit,iqflag,ifnili;
extern FR_INT4 MAXNFG,LANG,ICFLAG,jpri;

FR_DOUBLE wert;

FR_INT4 i,nrb,k,nkn,ifg,iflag1,jndex,j,istart,istop;

int iret;

char cline[256];

/*----------------------------------------------------------------------
* Start Function
*---------------------------------------------------------------------*/
wrim88r(0,TX_Z88CC);
wlog88r(0,LOG_Z88CC);

/***********************************************************************
* ICFLAG != 0: Lesen Randbedingungsfile und Einarbeiten der RB, Pass 1
***********************************************************************/
if(ICFLAG != 0)
  {
  rewind(fi2);

  wrim88r(0,TX_REAI2);
  wrim88r(1,TX_ERBPA);
  wlog88r(0,LOG_REAI2);
  wlog88r(1,LOG_ERBPA);
  
  fgets(cline,256,fi2);
  sscanf(cline,PD,&nrb);

  for(k = 1;k <= nrb;k++)
    {

    fgets(cline,256,fi2);
    sscanf(cline,PDB PDB PDB PG,&nkn,&ifg,&iflag1,&wert);

    jndex= ioffs[nkn]-1+ifg;

/*----------------------------------------------------------------------
* Verzweigen, ob Kraft oder Verschiebung
*---------------------------------------------------------------------*/
/*======================================================================
* Kraft vorgegeben
*=====================================================================*/
    if (iflag1 == 1) rs[jndex]+= wert;     

/*======================================================================
* Verschiebung vorgegeben
*=====================================================================*/
    if(iflag1 == 2)
      {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verschiebung != 0
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/ 
      if(FR_FABS(wert) >=  1e-8)
        {
        rs[jndex]= wert;
        GS[ip[jndex]]= 1.;

        if(jndex == 1) goto L30; 

        for(i= ip[jndex-1]+1; i <= ip[jndex]-1; i++)
          {
          rs[iez[i]]-= wert * GS[i];
          GS[i]= 0.;
          }  

        L30: if(jndex == nfg) break;

        for(j= jndex+1; j <= nfg; j++)
          {
          for(i= ip[j-1]+1; i <= ip[j]; i++)
            {
            if(iez[i] > jndex) break;
            if(iez[i] < jndex) continue;
            rs[j]-= wert * GS[i];
            GS[i]= 0.;
            break;
            }
          } 
        } /* Ende inhomogene RB */
      else
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verschiebung == 0 
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/ 
        {
        GS[ip[jndex]]= 1.;

        if(jndex == 1) goto L40; 

        for(i= ip[jndex-1]+1; i <= ip[jndex]-1; i++)
          GS[i]= 0.;

        L40: if(jndex == nfg) break;

        for(j= jndex+1; j <= nfg; j++)
          {
          for(i= ip[j-1]+1; i <= ip[j]; i++)
            {
            if(iez[i] > jndex) break;
            if(iez[i] < jndex) continue;
            GS[i]= 0.;
            break;
            }
          } 
        } /* Ende homogene RB */
      } /* Ende Weg vorgeben */
    } /* Ende Schleife Randbedingungen */
  } /* Ende ICFLAG != 0 */

/***********************************************************************
* ICFLAG == 0: Lesen Randbedingungsfile und Einarbeiten der RB, Pass 1
***********************************************************************/
if(ICFLAG == 0)
  {
  rewind(fi2);

  wrim88r(0,TX_REAI2);
  wrim88r(1,TX_ERBPA);
  wlog88r(0,LOG_REAI2);
  wlog88r(1,LOG_ERBPA);

  fgets(cline,256,fi2);
  sscanf(cline,PD,&nrb);

  for(k = 1;k <= nrb;k++)
    {

    fgets(cline,256,fi2);
    sscanf(cline,PDB PDB PDB PG,&nkn,&ifg,&iflag1,&wert);

    jndex= ioffs[nkn]-1+ifg;

    wran88j(k,iflag1);

/*----------------------------------------------------------------------
* Verzweigen, ob Kraft oder Verschiebung
*---------------------------------------------------------------------*/
/*======================================================================
* Kraft vorgegeben
*=====================================================================*/
    if (iflag1 == 1) rs[jndex]+= wert;     

/*======================================================================
* Verschiebung vorgegeben
*=====================================================================*/
    if(iflag1 == 2)
      {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verschiebung != 0
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/ 
      if(FR_FABS(wert) >=  1e-8)
        {
        rs[jndex]= wert;    /* Rechte Seite mit wert belegen */
        GS[ip[jndex]]= 1.;  /* Diagonalelemente auf 1 */

        if(jndex == 1) goto L50;  /* weil's ip[0] nicht gibt */
      
        istart=ip[jndex-1] + 1; /* Start der Skyline in der Zeile jndex */
        istop= ip[jndex]   - 1; /* Ende der Zeile vor Diagonalele.jndex */
        for(i= istart; i <= istop; i++)
          {
          j= jndex + i - istop -1;
          rs[j]-= wert * GS[i];
          GS[i]= 0.;         /* Zeile jndex 0 setzen */
          }  

        L50: if(jndex == nfg) continue;

        for(j= jndex+1; j <= nfg; j++)
          {
          if((ip[j-1] - ip[j] + j + 1) > jndex) continue;
          i= ip[j] - j + jndex;
          rs[j]-= wert * GS[i];
          GS[i]= 0.;         /* Spalte 0 setzen */ 
          } 
        } /* Ende inhomogene RB */
      else
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verschiebung == 0 
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/ 
        {
        GS[ip[jndex]]= 1.;  /* Diagonalelemente auf 1 */

        if(jndex == 1) goto L60;  /* weil's ip[0] nicht gibt */
      
        istart=ip[jndex-1] + 1; /* Start der Skyline in der Zeile jndex */
        istop= ip[jndex]   - 1; /* Ende der Zeile vor Diagonalele.jndex */
        for(i= istart; i <= istop; i++)
          GS[i]= 0.;         /* Zeile jndex 0 setzen */

        L60: if(jndex == nfg) continue;

        for(j= jndex+1; j <= nfg; j++)
          {
          if((ip[j-1] - ip[j] + j + 1) > jndex) continue;
          i= ip[j] - j + jndex;
          GS[i]= 0.;         /* Spalte 0 setzen */ 
          } 
        } /* Ende homogene RB */
      } /* Ende Weg vorgeben */
    } /* Ende Einbau RB */
  }  /* Ende ICFLAG == 0 */

/***********************************************************************
* gilt fuer alle ICFLAG: Lesen des Randbedingungsfiles und Einarbeiten 
* der RB, Pass 2. Gleichzeitig Kontrollfile Z88O1.TXT beschreiben
***********************************************************************/
wrim88r(0,TX_REAI2P2);
wrim88r(2,TX_ERBPA);
wrim88r(0,TX_WRIO1);
wlog88r(0,LOG_REAI2);
wlog88r(2,LOG_ERBPA);
wlog88r(0,LOG_WRIO1);

rewind(fi2);

fgets(cline,256,fi2);
sscanf(cline,PD,&nrb);

if(jpri == 1)
  {
  if(LANG == 1)
    {
    fprintf(fo1,"Ausgabedatei Z88O1.TXT  Randbedingungen, erzeugt mit Z88R V15OS\n");
    fprintf(fo1,"                        ***************\n\n");
    fprintf(fo1,"Anzahl gegebene Randbedingungen: " PD "\n\n",nrb);
    }

  if(LANG == 2)
    {
    fprintf(fo1,"output file Z88O1.TXT : constraints, produced by Z88R V15OS\n");
    fprintf(fo1,"                        ***********\n\n");
    fprintf(fo1,"number of given constraints: " PD "\n\n",nrb);
    }
  }

for(k = 1;k <= nrb;k++)
  {
  fgets(cline,256,fi2);
  sscanf(cline,PDB PDB PDB PG,&nkn,&ifg,&iflag1,&wert);

  jndex= ioffs[nkn]-1+ifg;
  if(iflag1 == 2) rs[jndex]= wert;

  if(jpri == 1)
    {
    if(iflag1 == 1)
      {
      if(LANG == 1)
      fprintf(fo1, "Knoten#" B5D "   FG" B1D "   Steuerflag" B1D "   Last         " P15E NL,
      nkn,ifg,iflag1,wert);

      if(LANG == 2)
      fprintf(fo1, "  node#" B5D "   DOF" B1D "  lo/di flag" B1D "   load         " P15E NL,
      nkn,ifg,iflag1,wert);
      }
    
    if(iflag1 == 2)
      {
      if(LANG == 1)
      fprintf(fo1, "Knoten#" B5D "   FG" B1D "   Steuerflag" B1D "   Verschiebung " P15E NL,
      nkn,ifg,iflag1,wert);

      if(LANG == 2)
      fprintf(fo1,"  node#" B5D "   DOF" B1D "  lo/di flag" B1D "   displacement " P15E NL,
      nkn,ifg,iflag1,wert);
      }
    }
  }

/*----------------------------------------------------------------------
* ggf. Flaechenlasten nach Z88O1.TXT ausschreiben
*---------------------------------------------------------------------*/
if(iqflag == 1 && jpri == 1) prfl88();

/***********************************************************************
* Gleichungssystem skalieren mit SCAL88
***********************************************************************/
wrim88r(0,TX_SCAL88);
wlog88r(0,LOG_SCAL88);

if(ICFLAG != 0) iret= scal88i();
if(ICFLAG == 0) iret= scal88f();

if(iret != 0) return(iret);

/***********************************************************************
* Ab die Post: Loesen des Gleichungssystems mit CHOY88
***********************************************************************/
if(ICFLAG == 0)
  {
  wrim88r(0,TX_CHOY88);
  wlog88r(0,LOG_CHOY88);
  wrim88r(nfg,TX_NFG);
  choy88();
  }

/***********************************************************************
* Ab die Post: Loesen des Gleichungssystems mit SICCG88 oder SORCG88
***********************************************************************/
if(ICFLAG == 1)
  {
  wrim88r(0,TX_SICCG88);
  wlog88r(0,LOG_SICCG88);
  wrim88r(nfg,TX_NFG);
  siccg88();
  }

if(ICFLAG == 2)
  {
  wrim88r(0,TX_SORCG88);
  wlog88r(0,LOG_SORCG88);
  wrim88r(nfg,TX_NFG);
  sorcg88();
  }

/***********************************************************************
* Scalierung rueckgaengig machen
***********************************************************************/
for(i = 1;i <= nfg;i++)
  rs[i]*= fak[i];

/***********************************************************************
* Ende, andrucken in Z88R
***********************************************************************/
wlog88r(0,LOG_EXITZ88CC);
return(0);
}


