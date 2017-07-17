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
* koi88x.c : Koinzidenz je nach Typ erkennen
* 14.12.2015 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <stdio.h>
#include <string.h>
#include <z88x.h>
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <stdio.h>
#include <string.h>
#include <z88x.h>
#endif

/***********************************************************************
*  Lese/Schreibformate
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

/***********************************************************************
* hier beginnt Function koi88x
***********************************************************************/
int koi88x(FR_INT4 i)
{
extern FILE *fdxf,*fwlo;

extern FR_DOUBLEAY x;
extern FR_DOUBLEAY y;
extern FR_DOUBLEAY z;

extern FR_INT4AY koi;
extern FR_INT4AY koffs;
extern FR_INT4AY ityp;

extern FR_INT4 ianz,nkp;

FR_DOUBLE xk[21],yk[21],zk[21];
FR_DOUBLE xmin,xmax,ymin,ymax,zmin,zmax,eps;

FR_INT4 j,k,index;

char cline[256];

/***********************************************************************
* start function
***********************************************************************/
eps= 0.0001;

/*---------------------------------------------------------------------*
* Typen 3,6,7,8,11,12,14,15,18,19,20,23,24
*---------------------------------------------------------------------*/
if(ityp[i] ==  3 || ityp[i] ==  6 ||
   ityp[i] ==  7 || ityp[i] ==  8 ||
   ityp[i] == 11 || ityp[i] == 12 ||
   ityp[i] == 14 || ityp[i] == 15 ||
   ityp[i] == 18 || ityp[i] == 19 || ityp[i] == 20 ||
   ityp[i] == 23 || ityp[i] == 24)
  {
  for(j= 1; j <= ianz; j++)
    {
    do
      {
      fgets(cline,256,fdxf);
      if((strstr(cline,"EOF")) != NULL) return(AL_TOOFEW);
      }
    while ((strstr(cline," 10"))== NULL);        /* Aufsetzpunkt "10" */

    fgets(cline,256,fdxf);                       /* xk erfassen    */
    sscanf(cline,PF,&xk[j]);                     /* xk lesen       */

    fgets(cline,256,fdxf);                       /* "20" leerlesen */
    fgets(cline,256,fdxf);                       /* yk erfassen    */
    sscanf(cline,PF,&yk[j]);                     /* yk lesen       */

    fgets(cline,256,fdxf);                       /* "30" leerlesen */
    fgets(cline,256,fdxf);                       /* zk erfassen    */
    sscanf(cline,PF,&zk[j]);                     /* zk lesen       */

    for(index= 1; index <= nkp; index++)
      {
      xmax= x[index] + eps; xmin= x[index] - eps; 
      ymax= y[index] + eps; ymin= y[index] - eps; 
      zmax= z[index] + eps; zmin= z[index] - eps;
      if(xk[j] >= xmin && xk[j] <= xmax &&
         yk[j] >= ymin && yk[j] <= ymax &&
         zk[j] >= zmin && zk[j] <= zmax)
        {
        fprintf(fwlo,"\nELE " PDB "#" PDB "J=" PDB "XK=" PGB "YK=" PGB "ZK=" PG,
        i,index,j,xk[j],yk[j],zk[j]);
        fflush(fwlo);
        koi[koffs[i]+j-1]= index;
        goto L100;
        }
      }
      L100:;
    }  
  }

/*---------------------------------------------------------------------*
* Typen 2,4,5,9,13,25
*---------------------------------------------------------------------*/
else if(ityp[i] ==  2 || ityp[i] ==  4 || ityp[i] ==  5 ||
        ityp[i] ==  9 || ityp[i] == 13 || ityp[i] == 25)
  {
  do
    {
    fgets(cline,256,fdxf);
    if((strstr(cline,"EOF")) != NULL) return(AL_TOOFEW);
    }
  while ((strstr(cline," 10"))== NULL);          /* Aufsetzpunkt "10" */

  fgets(cline,256,fdxf);                         /* xk1 erfassen   */
  sscanf(cline,PF,&xk[1]);                       /* xk1 lesen      */

  fgets(cline,256,fdxf);                         /* "20" leerlesen */
  fgets(cline,256,fdxf);                         /* yk1 erfassen   */
  sscanf(cline,PF,&yk[1]);                       /* yk1 lesen      */

  fgets(cline,256,fdxf);                         /* "30" leerlesen */
  fgets(cline,256,fdxf);                         /* zk1 erfassen   */
  sscanf(cline,PF,&zk[1]);                       /* zk1 lesen      */

  fgets(cline,256,fdxf);                         /* "11" leerlesen */
  fgets(cline,256,fdxf);                         /* xk2 erfassen   */
  sscanf(cline,PF,&xk[2]);                       /* xk2 lesen      */

  fgets(cline,256,fdxf);                         /* "21" leerlesen */
  fgets(cline,256,fdxf);                         /* yk2 erfassen   */
  sscanf(cline,PF,&yk[2]);                       /* yk2 lesen      */

  fgets(cline,256,fdxf);                         /* "31" leerlesen */
  fgets(cline,256,fdxf);                         /* zk2 erfassen   */
  sscanf(cline,PF,&zk[2]);                       /* zk2 lesen      */

  for(j= 1; j <= ianz; j++)
    {
    for(index= 1; index <= nkp; index++)
      {
      xmax= x[index] + eps; xmin= x[index] - eps; 
      ymax= y[index] + eps; ymin= y[index] - eps; 
      zmax= z[index] + eps; zmin= z[index] - eps;
      if(xk[j] >= xmin && xk[j] <= xmax &&
         yk[j] >= ymin && yk[j] <= ymax &&
         zk[j] >= zmin && zk[j] <= zmax)
        {
        fprintf(fwlo,"\nELE " PDB "#" PDB "J=" PDB "XK=" PGB "YK=" PGB "ZK=" PG,
        i,index,j,xk[j],yk[j],zk[j]);
        fflush(fwlo);
        koi[koffs[i]+j-1]= index;
        goto L200;
        }
      }
      L200:;
    }  
  }

/*---------------------------------------------------------------------*
* Hexaeder Nr. 1
*---------------------------------------------------------------------*/
else if(ityp[i] == 1)
  {
  for(j= 1; j <= ianz; j++)
    {
    do
      {
      fgets(cline,256,fdxf);
      if((strstr(cline,"EOF")) != NULL) return(AL_TOOFEW);
      }
    while ((strstr(cline," 10"))== NULL);        /* Aufsetzpunkt "10" */

    fgets(cline,256,fdxf);                       /* xk erfassen    */
    sscanf(cline,PF,&xk[j]);                     /* xk lesen       */

    fgets(cline,256,fdxf);                       /* "20" leerlesen */
    fgets(cline,256,fdxf);                       /* yk erfassen    */
    sscanf(cline,PF,&yk[j]);                     /* yk lesen       */

    fgets(cline,256,fdxf);                       /* "30" leerlesen */
    fgets(cline,256,fdxf);                       /* zk erfassen    */
    sscanf(cline,PF,&zk[j]);                     /* zk lesen       */

    for(index= 1; index <= nkp; index++)
      {
      xmax= x[index] + eps; xmin= x[index] - eps; 
      ymax= y[index] + eps; ymin= y[index] - eps; 
      zmax= z[index] + eps; zmin= z[index] - eps;
      if(xk[j] >= xmin && xk[j] <= xmax &&
         yk[j] >= ymin && yk[j] <= ymax &&
         zk[j] >= zmin && zk[j] <= zmax)
        {
        fprintf(fwlo,"\nELE " PDB "#" PDB "J=" PDB "XK=" PGB "YK=" PGB "ZK=" PG,
        i,index,j,xk[j],yk[j],zk[j]);
        fflush(fwlo);
        koi[koffs[i]+j-1]= index;
        goto L300;
        }
      }
      L300:;
    }
/*---------- die vier Seitenlinien ueberspringen ---------------------*/
  for(k= 1; k <= 4; k++)                        
    {
    do
      {
      fgets(cline,256,fdxf);
      if((strstr(cline,"EOF")) != NULL) return(AL_TOOFEW);
      }
    while ((strstr(cline," 10"))== NULL);        /* Aufsetzpunkt "10" */
    }
  }

/*---------------------------------------------------------------------*
* Hexaeder Nr. 10
*---------------------------------------------------------------------*/
else if(ityp[i] == 10)
  {
/*=====================================================================*
* die beiden Deckflaechen
*=====================================================================*/
  for(j= 1; j <= 16; j++)
    {
    do
      {
      fgets(cline,256,fdxf);
      if((strstr(cline,"EOF")) != NULL) return(AL_TOOFEW);
      }
    while ((strstr(cline," 10"))== NULL);        /* Aufsetzpunkt "10" */

    fgets(cline,256,fdxf);                       /* xk erfassen    */
    sscanf(cline,PF,&xk[j]);                     /* xk lesen       */

    fgets(cline,256,fdxf);                       /* "20" leerlesen */
    fgets(cline,256,fdxf);                       /* yk erfassen    */
    sscanf(cline,PF,&yk[j]);                     /* yk lesen       */

    fgets(cline,256,fdxf);                       /* "30" leerlesen */
    fgets(cline,256,fdxf);                       /* zk erfassen    */
    sscanf(cline,PF,&zk[j]);                     /* zk lesen       */

    for(index= 1; index <= nkp; index++)
      {
      xmax= x[index] + eps; xmin= x[index] - eps; 
      ymax= y[index] + eps; ymin= y[index] - eps; 
      zmax= z[index] + eps; zmin= z[index] - eps;
      if(xk[j] >= xmin && xk[j] <= xmax &&
         yk[j] >= ymin && yk[j] <= ymax &&
         zk[j] >= zmin && zk[j] <= zmax)
        {
        fprintf(fwlo,"\nELE " PDB "#" PDB "J=" PDB "XK=" PGB "YK=" PGB "ZK=" PG,
        i,index,j,xk[j],yk[j],zk[j]);
        fflush(fwlo);
        koi[koffs[i]+j-1]= index;
        goto L400;
        }
      }
      L400:;
    }

/*=====================================================================*
* die vier Seitenlinien
*=====================================================================*/
  for(j= 17; j <= 20; j++)
    {
/*---------- die ersten Teil- Seitenlinien ueberspringen -------------*/
/*----------------- also von 1-17, 2-18, 3-19, 4-20  -----------------*/
    do
      {
      fgets(cline,256,fdxf);
      if((strstr(cline,"EOF")) != NULL) return(AL_TOOFEW);
      }
    while ((strstr(cline," 10"))== NULL);

/*------------- die zweiten Teil- Seitenlinien scannen ---------------*/
    do
      {
      fgets(cline,256,fdxf);
      if((strstr(cline,"EOF")) != NULL) return(AL_TOOFEW);
      }
    while ((strstr(cline," 10"))== NULL);        /* Aufsetzpunkt "10" */
 
    fgets(cline,256,fdxf);                       /* xk erfassen    */
    sscanf(cline,PF,&xk[j]);                     /* xk lesen       */

    fgets(cline,256,fdxf);                       /* "20" leerlesen */
    fgets(cline,256,fdxf);                       /* yk erfassen    */
    sscanf(cline,PF,&yk[j]);                     /* yk lesen       */

    fgets(cline,256,fdxf);                       /* "30" leerlesen */
    fgets(cline,256,fdxf);                       /* zk erfassen    */
    sscanf(cline,PF,&zk[j]);                     /* zk lesen       */

    for(index= 1; index <= nkp; index++)
      {
      xmax= x[index] + eps; xmin= x[index] - eps; 
      ymax= y[index] + eps; ymin= y[index] - eps; 
      zmax= z[index] + eps; zmin= z[index] - eps;
      if(xk[j] >= xmin && xk[j] <= xmax &&
         yk[j] >= ymin && yk[j] <= ymax &&
         zk[j] >= zmin && zk[j] <= zmax)
        {
        fprintf(fwlo,"\nELE " PDB "#" PDB "J=" PDB "XK=" PGB "YK=" PGB "ZK=" PG,
        i,index,j,xk[j],yk[j],zk[j]);
        fflush(fwlo);
        koi[koffs[i]+j-1]= index;
        goto L500;
        }
      }
    L500:;
    }
  }

/*---------------------------------------------------------------------*
* Volumenschalenelement Nr. 21
*---------------------------------------------------------------------*/
else if(ityp[i] == 21)
  {
/*---------- die beiden Deckflaechen ---------------------------------*/
  for(j= 1; j <= ianz; j++)
    {
    do
      {
      fgets(cline,256,fdxf);
      if((strstr(cline,"EOF")) != NULL) return(AL_TOOFEW);
      }
    while ((strstr(cline," 10"))== NULL);        /* Aufsetzpunkt "10" */

    fgets(cline,256,fdxf);                       /* xk erfassen    */
    sscanf(cline,PF,&xk[j]);                     /* xk lesen       */

    fgets(cline,256,fdxf);                       /* "20" leerlesen */
    fgets(cline,256,fdxf);                       /* yk erfassen    */
    sscanf(cline,PF,&yk[j]);                     /* yk lesen       */

    fgets(cline,256,fdxf);                       /* "30" leerlesen */
    fgets(cline,256,fdxf);                       /* zk erfassen    */
    sscanf(cline,PF,&zk[j]);                     /* zk lesen       */

    for(index= 1; index <= nkp; index++)
      {
      xmax= x[index] + eps; xmin= x[index] - eps; 
      ymax= y[index] + eps; ymin= y[index] - eps; 
      zmax= z[index] + eps; zmin= z[index] - eps;
      if(xk[j] >= xmin && xk[j] <= xmax &&
         yk[j] >= ymin && yk[j] <= ymax &&
         zk[j] >= zmin && zk[j] <= zmax)
        {
        fprintf(fwlo,"\nELE " PDB "#" PDB "J=" PDB "XK=" PGB "YK=" PGB "ZK=" PG,
        i,index,j,xk[j],yk[j],zk[j]);
        fflush(fwlo);
        koi[koffs[i]+j-1]= index;
        goto L600;
        }
      }
      L600:;
    }
/*---------- die vier Seitenlinien ueberspringen ---------------------*/
  for(k= 1; k <= 4; k++)                        
    {
    do
      {
      fgets(cline,256,fdxf);
      if((strstr(cline,"EOF")) != NULL) return(AL_TOOFEW);
      }
    while ((strstr(cline," 10"))== NULL);        /* Aufsetzpunkt "10" */
    }
  }

/*---------------------------------------------------------------------*
* Volumenschalenelement Nr. 22
*---------------------------------------------------------------------*/
else if(ityp[i] == 22)
  {
/*---------- die beiden Deckflaechen ---------------------------------*/
  for(j= 1; j <= ianz; j++)
    {
    do
      {
      fgets(cline,256,fdxf);
      if((strstr(cline,"EOF")) != NULL) return(AL_TOOFEW);
      }
    while ((strstr(cline," 10"))== NULL);        /* Aufsetzpunkt "10" */

    fgets(cline,256,fdxf);                       /* xk erfassen    */
    sscanf(cline,PF,&xk[j]);                     /* xk lesen       */

    fgets(cline,256,fdxf);                       /* "20" leerlesen */
    fgets(cline,256,fdxf);                       /* yk erfassen    */
    sscanf(cline,PF,&yk[j]);                     /* yk lesen       */

    fgets(cline,256,fdxf);                       /* "30" leerlesen */
    fgets(cline,256,fdxf);                       /* zk erfassen    */
    sscanf(cline,PF,&zk[j]);                     /* zk lesen       */

    for(index= 1; index <= nkp; index++)
      {
      xmax= x[index] + eps; xmin= x[index] - eps; 
      ymax= y[index] + eps; ymin= y[index] - eps; 
      zmax= z[index] + eps; zmin= z[index] - eps;
      if(xk[j] >= xmin && xk[j] <= xmax &&
         yk[j] >= ymin && yk[j] <= ymax &&
         zk[j] >= zmin && zk[j] <= zmax)
        {
        fprintf(fwlo,"\nELE " PDB "#" PDB "J=" PDB "XK=" PGB "YK=" PGB "ZK=" PG,
        i,index,j,xk[j],yk[j],zk[j]);
        fflush(fwlo);
        koi[koffs[i]+j-1]= index;
        goto L700;
        }
      }
      L700:;
    }
/*---------- die drei Seitenlinien ueberspringen ---------------------*/
  for(k= 1; k <= 3; k++)                        
    {
    do
      {
      fgets(cline,256,fdxf);
      if((strstr(cline,"EOF")) != NULL) return(AL_TOOFEW);
      }
    while ((strstr(cline," 10"))== NULL);        /* Aufsetzpunkt "10" */
    }
  }

/*---------------------------------------------------------------------*
* Tetraeder Nr. 17
*---------------------------------------------------------------------*/
else if(ityp[i] == 17)
  {

/*=====================================================================*
* die XY-Ebene: Linien 1-2, 2-3 und 3-1
*=====================================================================*/
  for(j= 1; j <= 3; j++)
    {
    do
      {
      fgets(cline,256,fdxf);
      if((strstr(cline,"EOF")) != NULL) return(AL_TOOFEW);
      }
    while ((strstr(cline," 10"))== NULL);        /* Aufsetzpunkt "10" */

    fgets(cline,256,fdxf);                       /* xk erfassen    */
    sscanf(cline,PF,&xk[j]);                     /* xk lesen       */

    fgets(cline,256,fdxf);                       /* "20" leerlesen */
    fgets(cline,256,fdxf);                       /* yk erfassen    */
    sscanf(cline,PF,&yk[j]);                     /* yk lesen       */

    fgets(cline,256,fdxf);                       /* "30" leerlesen */
    fgets(cline,256,fdxf);                       /* zk erfassen    */
    sscanf(cline,PF,&zk[j]);                     /* zk lesen       */

    for(index= 1; index <= nkp; index++)
      {
      xmax= x[index] + eps; xmin= x[index] - eps; 
      ymax= y[index] + eps; ymin= y[index] - eps; 
      zmax= z[index] + eps; zmin= z[index] - eps;
      if(xk[j] >= xmin && xk[j] <= xmax &&
         yk[j] >= ymin && yk[j] <= ymax &&
         zk[j] >= zmin && zk[j] <= zmax)
        {
        fprintf(fwlo,"\nELE " PDB "#" PDB "J=" PDB "XK=" PGB "YK=" PGB "ZK=" PG,
        i,index,j,xk[j],yk[j],zk[j]);
        fflush(fwlo);
        koi[koffs[i]+j-1]= index;
        goto L900;
        }
      }
      L900:;
    }

/*=====================================================================*
* die drei Seitenlinien, die Knoten 4 bilden
*=====================================================================*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*
* den ersten Punkt der Seitenlinie 2-4 wegwerfen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  do
    {
    fgets(cline,256,fdxf);
    if((strstr(cline,"EOF")) != NULL) return(AL_TOOFEW);
    }
  while ((strstr(cline," 10"))== NULL);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*
* den zweiten Punkt der Seitenlinie 2-4 scannen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  j= 4;
  do
    {
    fgets(cline,256,fdxf);
    if((strstr(cline,"EOF")) != NULL) return(AL_TOOFEW);
    }
  while ((strstr(cline," 11"))== NULL);        /* Aufsetzpunkt "10" */
 
  fgets(cline,256,fdxf);                       /* xk erfassen    */
  sscanf(cline,PF,&xk[j]);                     /* xk lesen       */

  fgets(cline,256,fdxf);                       /* "21" leerlesen */
  fgets(cline,256,fdxf);                       /* yk erfassen    */
  sscanf(cline,PF,&yk[j]);                     /* yk lesen       */

  fgets(cline,256,fdxf);                       /* "31" leerlesen */
  fgets(cline,256,fdxf);                       /* zk erfassen    */
  sscanf(cline,PF,&zk[j]);                     /* zk lesen       */

  for(index= 1; index <= nkp; index++)
    {
    xmax= x[index] + eps; xmin= x[index] - eps; 
    ymax= y[index] + eps; ymin= y[index] - eps; 
    zmax= z[index] + eps; zmin= z[index] - eps;
    if(xk[j] >= xmin && xk[j] <= xmax &&
       yk[j] >= ymin && yk[j] <= ymax &&
       zk[j] >= zmin && zk[j] <= zmax)
      {
      fprintf(fwlo,"\nELE " PDB "#" PDB "J=" PDB "XK=" PGB "YK=" PGB "ZK=" PG,
      i,index,j,xk[j],yk[j],zk[j]);
      fflush(fwlo);
      koi[koffs[i]+j-1]= index;
      goto L1000;
      }
    }
    L1000:;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*
* den restlichen Seitenlinie, also 1-4 und 3-4 wegwerfen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for(k= 1; k <= 2; k++)                        
    {
    do
      {
      fgets(cline,256,fdxf);
      if((strstr(cline,"EOF")) != NULL) return(AL_TOOFEW);
      }
    while ((strstr(cline," 10"))== NULL);        /* Aufsetzpunkt "10" */
    }
  }  /* Ende Tetraeder 17 */

/*---------------------------------------------------------------------*
* Tetraeder Nr. 16
*---------------------------------------------------------------------*/
else if(ityp[i] == 16)
  {
/*=====================================================================*
* die XY-Ebene: Linien 1-5,5-2,2-6,6-3,3-7 und 7-1. Knoten 4 nicht hier.
*=====================================================================*/
  for(j= 1; j <= 6; j++)
    {
    do
      {
      fgets(cline,256,fdxf);
      if((strstr(cline,"EOF")) != NULL) return(AL_TOOFEW);
      }
    while ((strstr(cline," 10"))== NULL);        /* Aufsetzpunkt "10" */

    fgets(cline,256,fdxf);                       /* xk erfassen    */
    sscanf(cline,PF,&xk[j]);                     /* xk lesen       */

    fgets(cline,256,fdxf);                       /* "20" leerlesen */
    fgets(cline,256,fdxf);                       /* yk erfassen    */
    sscanf(cline,PF,&yk[j]);                     /* yk lesen       */

    fgets(cline,256,fdxf);                       /* "30" leerlesen */
    fgets(cline,256,fdxf);                       /* zk erfassen    */
    sscanf(cline,PF,&zk[j]);                     /* zk lesen       */

    for(index= 1; index <= nkp; index++)
      {
      xmax= x[index] + eps; xmin= x[index] - eps; 
      ymax= y[index] + eps; ymin= y[index] - eps; 
      zmax= z[index] + eps; zmin= z[index] - eps;
      if(xk[j] >= xmin && xk[j] <= xmax &&
         yk[j] >= ymin && yk[j] <= ymax &&
         zk[j] >= zmin && zk[j] <= zmax)
        {
        fprintf(fwlo,"\nELE " PDB "#" PDB "J=" PDB "XK=" PGB "YK=" PGB "ZK=" PG,
        i,index,j,xk[j],yk[j],zk[j]);
        fflush(fwlo);
        koi[koffs[i]+j-1]= index;
        goto L1100;
        }
      }
      L1100:;
    }

/*=====================================================================*
* die drei Seitenlinien, die Knoten 4 bilden: 2-8-4,3-9-4 und 1-10-4
*=====================================================================*/
  for(j= 7; j <= 9; j++)
    {
/*---------- die ersten Teil-Seitenlinien ueberspringen --------------*/
/*----------------- also von 2-8, 3-9, 1-10 --------------------------*/
    do
      {
      fgets(cline,256,fdxf);
      if((strstr(cline,"EOF")) != NULL) return(AL_TOOFEW);
      }
    while ((strstr(cline," 10"))== NULL);

/*------------- die zweiten Teil-Seitenlinien scannen ----------------*/
    do
      {
      fgets(cline,256,fdxf);
      if((strstr(cline,"EOF")) != NULL) return(AL_TOOFEW);
      }
    while ((strstr(cline," 10"))== NULL);        /* Aufsetzpunkt "10" */
 
    fgets(cline,256,fdxf);                       /* xk erfassen    */
    sscanf(cline,PF,&xk[j]);                     /* xk lesen       */

    fgets(cline,256,fdxf);                       /* "20" leerlesen */
    fgets(cline,256,fdxf);                       /* yk erfassen    */
    sscanf(cline,PF,&yk[j]);                     /* yk lesen       */

    fgets(cline,256,fdxf);                       /* "30" leerlesen */
    fgets(cline,256,fdxf);                       /* zk erfassen    */
    sscanf(cline,PF,&zk[j]);                     /* zk lesen       */

    for(index= 1; index <= nkp; index++)
      {
      xmax= x[index] + eps; xmin= x[index] - eps; 
      ymax= y[index] + eps; ymin= y[index] - eps; 
      zmax= z[index] + eps; zmin= z[index] - eps;
      if(xk[j] >= xmin && xk[j] <= xmax &&
         yk[j] >= ymin && yk[j] <= ymax &&
         zk[j] >= zmin && zk[j] <= zmax)
        {
        fprintf(fwlo,"\nELE " PDB "#" PDB "J=" PDB "XK=" PGB "YK=" PGB "ZK=" PG,
        i,index,j,xk[j],yk[j],zk[j]);
        fflush(fwlo);
        koi[koffs[i]+j-1]= index;
        goto L1200;
        }
      }
    L1200:;

    if(j == 9) // den Knoten 4 finden als zweiten Knoten der Linie 1-10-4
      {
      do
        {
        fgets(cline,256,fdxf);
        if((strstr(cline,"EOF")) != NULL) return(AL_TOOFEW);
        }
      while ((strstr(cline," 11"))== NULL);        /* Aufsetzpunkt "11" */
 
      fgets(cline,256,fdxf);                       /* xk erfassen    */
      sscanf(cline,PF,&xk[4]);                     /* xk lesen       */

      fgets(cline,256,fdxf);                       /* "21" leerlesen */
      fgets(cline,256,fdxf);                       /* yk erfassen    */
      sscanf(cline,PF,&yk[4]);                     /* yk lesen       */

      fgets(cline,256,fdxf);                       /* "31" leerlesen */
      fgets(cline,256,fdxf);                       /* zk erfassen    */
      sscanf(cline,PF,&zk[4]);                     /* zk lesen       */

      for(index= 1; index <= nkp; index++)
        {
        xmax= x[index] + eps; xmin= x[index] - eps; 
        ymax= y[index] + eps; ymin= y[index] - eps; 
        zmax= z[index] + eps; zmin= z[index] - eps;
        if(xk[4] >= xmin && xk[4] <= xmax &&
           yk[4] >= ymin && yk[4] <= ymax &&
           zk[4] >= zmin && zk[4] <= zmax)
          {
          fprintf(fwlo,"\nELE " PDB "#" PDB "J=" PDB "XK=" PGB "YK=" PGB "ZK=" PG,
          i,index,j,xk[4],yk[4],zk[4]);
          fflush(fwlo);
          koi[koffs[i]+10-1]= index;
          goto L1300;
          }
        }
      L1300:;    

      }
    } // Ende Schleife j
 
  }  // Ende Tetraeder 16

return 0; 
}

