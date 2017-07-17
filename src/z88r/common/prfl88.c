/************************************************************************
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
* prfl88 schreibt Flaechenlasten als Kontrolle in Z88O1.TXT
* 17.7.2011 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <stdio.h>
#endif

/***********************************************************************
* Fuer Windows und GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88r.h>
#include <stdio.h>
#endif

/***********************************************************************
* Formate
***********************************************************************/
#define NL "\n"

#ifdef FR_XINT
#define PD "%d"
#define B5D " %5d"
#endif

#ifdef FR_XLONG
#define PD "%ld"
#define B5D " %5ld"
#endif

#ifdef FR_XLOLO
#define PD "%lld"
#define B5D " %5lld"
#endif

#ifdef FR_XDOUB
#define B13E " %+#13.5lE"
#endif

#ifdef FR_XQUAD
#define B13E " %+#13.5LE"
#endif

/***********************************************************************
* hier beginnt Function prfl88
***********************************************************************/
int prfl88(void)
{
extern FILE *fo1;

extern FR_DOUBLEAY pres;
extern FR_DOUBLEAY tr1;
extern FR_DOUBLEAY tr2;

extern FR_INT4AY ityp;
extern FR_INT4AY noi;
extern FR_INT4AY noffs; 
extern FR_INT4AY nep;

extern FR_INT4 npr,LANG;

FR_INT4 j;

/*---------------------------------------------------------------------*
* Beschreiben Z88O1.TXT, Ueberschrift
*---------------------------------------------------------------------*/
fprintf(fo1,"\n");

if(LANG == 1)
{
fprintf(fo1,"Ausgabedatei Z88O1.TXT  Flaechenlasten\n");
fprintf(fo1,"                        **************\n\n");
fprintf(fo1,"Anzahl gegebene Flaechenlasten: " PD "\n\n",npr);
}

if(LANG == 2)
{
fprintf(fo1,"output file Z88O1.TXT : surface loads\n");
fprintf(fo1,"                        *************\n\n");
fprintf(fo1,"number of given surface loads: " PD "\n\n",npr);
}

/*---------------------------------------------------------------------*
* Schleife
*---------------------------------------------------------------------*/
for(j= 1; j <= npr; j++)
  {
/*======================================================================
* Elementtypen 7, 8, 14, 15
*=====================================================================*/
  if(ityp[nep[j]]== 7  || ityp[nep[j]]==  8 ||
     ityp[nep[j]]== 14 || ityp[nep[j]]== 15) 
    {
    if(LANG == 1)
      fprintf(fo1,"Element#" B5D "   Normallast" B13E "   Schub r" B13E\
"   Knoten" B5D B5D B5D NL,nep[j],pres[j],tr1[j],
      noi[noffs[j]],noi[noffs[j]+1],noi[noffs[j]+2]); 
    if(LANG == 2)
      fprintf(fo1,"element#" B5D "   normal load" B13E "  shear r" B13E\
"   nodes"  B5D B5D B5D NL,nep[j],pres[j],tr1[j],
      noi[noffs[j]],noi[noffs[j]+1],noi[noffs[j]+2]); 
    }

/*======================================================================
* Elementtyp 17
*=====================================================================*/
  if(ityp[nep[j]]== 17) 
    {
    if(LANG == 1)
      fprintf(fo1,"Element#" B5D "   Druck" B13E "   Knoten" B5D B5D B5D NL,
      nep[j],pres[j],noi[noffs[j]],noi[noffs[j]+1],noi[noffs[j]+2]); 
    if(LANG == 2)
      fprintf(fo1,"element#" B5D "   pressure" B13E "   nodes" B5D B5D B5D NL,
      nep[j],pres[j],noi[noffs[j]],noi[noffs[j]+1],noi[noffs[j]+2]); 
    }

/*======================================================================
* Elementtyp 16 und 22
*=====================================================================*/
  if(ityp[nep[j]]== 16 || ityp[nep[j]]== 22) 
    {
    if(LANG == 1)
      fprintf(fo1,"Element#" B5D "   Druck" B13E\
"   Knoten" B5D B5D B5D B5D B5D B5D NL,nep[j],pres[j],
      noi[noffs[j]  ],noi[noffs[j]+1],noi[noffs[j]+2],
      noi[noffs[j]+3],noi[noffs[j]+4],noi[noffs[j]+5]); 
    if(LANG == 2)
      fprintf(fo1,"element#" B5D "   pressure " B13E\
"   nodes" B5D B5D B5D B5D B5D B5D NL,nep[j],pres[j],
      noi[noffs[j]  ],noi[noffs[j]+1],noi[noffs[j]+2],
      noi[noffs[j]+3],noi[noffs[j]+4],noi[noffs[j]+5]); 
    }

/*======================================================================
* Elementtyp 10 u. 21
*=====================================================================*/
  if(ityp[nep[j]]== 10 || ityp[nep[j]]== 21) 
    {
    if(LANG == 1)
      fprintf(fo1,
      "Element#" B5D "   Druck" B13E "   Schub r" B13E "   Schub s" B13E\
"   Knoten" B5D B5D B5D B5D B5D B5D B5D B5D NL,
      nep[j],pres[j],tr1[j],tr2[j],
      noi[noffs[j]  ],noi[noffs[j]+1],noi[noffs[j]+2],noi[noffs[j]+3],
      noi[noffs[j]+4],noi[noffs[j]+5],noi[noffs[j]+6],noi[noffs[j]+7]); 
    if(LANG == 2)
      fprintf(fo1,
      "Element#" B5D "   pressure" B13E "   shear r" B13E "   shear s" B13E\
"   nodes" B5D B5D B5D B5D B5D B5D B5D B5D NL,
      nep[j],pres[j],tr1[j],tr2[j],
      noi[noffs[j]  ],noi[noffs[j]+1],noi[noffs[j]+2],noi[noffs[j]+3],
      noi[noffs[j]+4],noi[noffs[j]+5],noi[noffs[j]+6],noi[noffs[j]+7]); 
    }

/*======================================================================
* Elementtyp 1
*=====================================================================*/
  if(ityp[nep[j]]== 1) 
    {
    if(LANG == 1)
      fprintf(fo1,
      "Element#" B5D "   Druck" B13E "   Schub r" B13E "   Schub s" B13E\
"   Knoten" B5D B5D B5D B5D NL,
      nep[j],pres[j],tr1[j],tr2[j],
      noi[noffs[j]  ],noi[noffs[j]+1],noi[noffs[j]+2],noi[noffs[j]+3]);
    if(LANG == 2)
      fprintf(fo1,
      "Element#" B5D "   pressure" B13E "   shear r" B13E "   shear s" B13E\
"   nodes" B5D B5D B5D B5D NL,
      nep[j],pres[j],tr1[j],tr2[j],
      noi[noffs[j]  ],noi[noffs[j]+1],noi[noffs[j]+2],noi[noffs[j]+3]); 
    }

/*======================================================================
* Elementtypen 11 und 12
*=====================================================================*/
  if(ityp[nep[j]]== 11  || ityp[nep[j]]== 12) 
    {
    if(LANG == 1)
      fprintf(fo1,"Element#" B5D "   Normallast" B13E "   Schub r" B13E\
"   Knoten" B5D B5D B5D B5D NL,nep[j],pres[j],tr1[j],
      noi[noffs[j]],noi[noffs[j]+1],noi[noffs[j]+2],noi[noffs[j]+3]); 
    if(LANG == 2)
      fprintf(fo1,"element#" B5D "   normal load" B13E "  shear r" B13E\
"   nodes" B5D B5D B5D B5D NL,nep[j],pres[j],tr1[j],
      noi[noffs[j]],noi[noffs[j]+1],noi[noffs[j]+2],noi[noffs[j]+3]); 
    }

/*======================================================================
* Elementtyp 18,19,20,23 und 24
*=====================================================================*/
  if(ityp[nep[j]]== 18 || ityp[nep[j]]== 19 || ityp[nep[j]]== 20 ||
     ityp[nep[j]]== 23 || ityp[nep[j]]== 24) 
    {
    if(LANG == 1)
      fprintf(fo1,"Element#" B5D "   Druck" B13E NL,nep[j],pres[j]);
    if(LANG == 2)
      fprintf(fo1,"Element#" B5D "   pressure" B13E NL,nep[j],pres[j]); 
    }

  }  /* Ende Schleife */

return(0);
}
