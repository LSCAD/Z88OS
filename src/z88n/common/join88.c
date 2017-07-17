/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the UNIX and
* the Windows OS.
*
* Composed and edited and copyright by 
* Professor Dr.-Ing. Frank Rieg, University of Bayreuth, Germany
*
* eMail: 
* frank.rieg@uni-bayreuth.de
* dr.frank.rieg@t-online.de
* 
* V15.0  November 18 2015
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
* Function join88 berechnet Vektor join
* 21.7.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88n.h>
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88n.h>
#endif

/***********************************************************************
* Functions
***********************************************************************/
int wrim88n(FR_INT4,int);
int wlog88n(FR_INT4,int);

/***********************************************************************
* hier beginnt Function join88
***********************************************************************/
int join88(void)
{
extern FR_INT4AY join;
extern FR_INT4AY koiss;
extern FR_INT4AY koffss;

extern FR_INT4 MAXAN;
extern FR_INT4 ness,itypss;

FR_INT4 i,kneck,joffs,iss,k,itreff,j,kaktue,kvergl,l;

/***********************************************************************
* Schleife ueber alle Superelemente fuer Nachbarelemente
***********************************************************************/
wrim88n(0,TX_BERJOIN);
wlog88n(0,LOG_BERJOIN);

/*----------------------------------------------------------------------
* join vorbelegen, dabei wird angenommen, dass maximal MAXAN
* Elemente anschliessen (MAXAN via Z88.DYN)
*---------------------------------------------------------------------*/ 
for(i = 1; i <= (MAXAN*ness); i++)
  join[i]= 0; 
          
/*----------------------------------------------------------------------
* Anzahl Eckknoten festlegen
*---------------------------------------------------------------------*/
if(itypss == 10 || itypss == 1) kneck= 8;
else                            kneck= 4;
        
/*----------------------------------------------------------------------
* Schleife ueber alle Elemente ausser #1 (nicht noetig)
*---------------------------------------------------------------------*/ 
for(iss = 2; iss <= ness; iss++)
  {
  joffs= MAXAN*(iss-1);
/*======================================================================
* 1.Element bis vorletztes aktuelles Element
*=====================================================================*/
  for (k = 1; k <= (iss-1); k++)
    {
    itreff= 0;
                
    for(j = 1; j <= kneck; j++)
      {
      kaktue= koiss[koffss[iss] + j-1];
      for(i = 1; i <= kneck; i++)
        {
        kvergl= koiss[koffss[k] + i-1];
        if(kaktue == kvergl) itreff= 1;
        }
      /* getroffen ? */
      if(itreff == 1)
        {
        for(l = 1; l <= MAXAN; l++)
          {
          if (join[joffs+l] == 0)
            {
            join[joffs+l]= k;
            goto L90;
            }
          }
         }
      }
L90:;                
    }
  }
wlog88n(0,LOG_EXITJOIN);
return (0);
}
