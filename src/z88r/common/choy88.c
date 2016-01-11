/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows
* and the UNIX OS.
*
* Composed and edited and copyright by 
* Professor Dr.-Ing. Frank Rieg, University of Bayreuth, Germany
*
* eMail: 
* frank.rieg@uni-bayreuth.de
* dr.frank.rieg@t-online.de
* 
* V14.0  January 14, 2009
*
* Z88 should compile and run under any Windows or any UNIX OS and GTK+.
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
* Diese Compilerunit enthaelt:
* scal88f
* choy88 mit Jennings- Speicherung
* Skalierung und Gleichungsloeser nach H.R.Schwarz
* 2.1.2010 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#endif

/***********************************************************************
* Fuer Windows und GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88r.h>
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wrim88r(FR_INT4,int);
int wlog88r(FR_INT4,int);

/***********************************************************************
* hier beginnt Function scal88f
***********************************************************************/
int scal88f(void)
{
extern FR_DOUBLEAY GS;
extern FR_DOUBLEAY rs;
extern FR_DOUBLEAY fak;

extern FR_INT4AY ip;

extern FR_INT4 nfg;

FR_INT4 i,j,k,jstart,jstop;

/*----------------------------------------------------------------------
* Start Function
*---------------------------------------------------------------------*/

/***********************************************************************
* Scalierungsfaktoren berechnen, rechte Seite umrechnen, Matrix skal.
***********************************************************************/
for(i = 1;i <= nfg;i++)
  {
  if(GS[ip[i]] <= 0.) 
    {
    wlog88r(i,LOG_DIAGNULL);
    return(AL_DIAGNULL);
    }
  fak[i]= 1. / FR_SQRT( GS[ip[i]] );
  rs[i] *= fak[i];
  GS[ip[i]]= 1.;
  
  if(i == 1) continue;
  
  jstart=ip[i-1] + 1; /* Start der inversen Skyline in der Zeile i */
  jstop= ip[i]   - 1; /* Zeile bis Diagonalelement der Zeile i */

  k= jstart - jstop + i - 1;
  
  for(j= jstart; j <= jstop; j++)
    {
    GS[j] *= fak[i] * fak[k];
    k++; 
    }  
  }

/**********************************************************************/
return(0);
}
 
/***********************************************************************
* Function choy88 loest Gleichungssysteme nach der Methode von
* Cholesky mit in-situ Speicherung
***********************************************************************/ 
/***********************************************************************
* hier beginnt Function choy88
***********************************************************************/
int choy88(void)
{
extern FR_DOUBLEAY GS;
extern FR_DOUBLEAY rs;

extern FR_INT4AY ip;

extern FR_INT4 nfg;

FR_DOUBLE sum;
FR_INT4 j,i,m,k,i0,j0,li,lj;

/*----------------------------------------------------------------------
* Start Function
*---------------------------------------------------------------------*/

/***********************************************************************
* Cholesky-Zerlegung
***********************************************************************/
GS[1]= FR_SQRT(GS[1]);

for(i = 2;i <= nfg;i++)
  {
  wrim88r(i,TX_CHOJ);
  i0= ip[i] - i;
  li= ip[i-1] + 1 - i0;
  for(j = li;j <= i;j++)
    {
    j0= ip[j] - j;
    sum=  GS[i0+j];
    lj= 1;

    if(j > 1) 
      lj= ip[j-1] - j0 + 1;
      
    if(li >= lj) m= li;
    else         m= lj;
       
    for(k = m;k <= j-1;k++) 
      sum -= GS[i0+k] * GS[j0+k];
      
    if(j < i)
      GS[i0+j]= sum / GS[ip[j]];
    else
      GS[ip[i]]= FR_SQRT(sum);    
    }
  }

/***********************************************************************
* Vorwaertseinsetzen
***********************************************************************/
wrim88r(0,TX_VORW);
wlog88r(0,LOG_VORW);

rs[1]/= GS[1];
for(i= 2;i <= nfg;i++)
  {
  sum= rs[i];
  i0= ip[i] - i;
  li= ip[i-1] + 1 - i0;
  for(j= li;j <= i-1;j++)
    sum -= GS[i0+j] * rs[j];
  rs[i]= sum / GS[ip[i]];    
  }
 
/***********************************************************************
* Ruechwaertseinsetzen
***********************************************************************/
wrim88r(0,TX_RUECKW);
wlog88r(0,LOG_RUECKW);

for(i= nfg;i >= 2;i--)
  {
  rs[i]/= GS[ip[i]];
  i0= ip[i] - i;
  li= ip[i-1] + 1 - i0;
  for(j= li;j <= i-1;j++)
    rs[j] -= GS[i0+j] * rs[i];
  }
rs[1]/= GS[1];

return(0);
}
