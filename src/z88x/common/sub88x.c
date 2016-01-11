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
* sub88x.c : hilfswerte ausfiltern
* 29.7.2011 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88x.h>
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88x.h>
#endif

/***********************************************************************
*  Functions
***********************************************************************/

/***********************************************************************
* hier beginnt Function sub88x
***********************************************************************/
void sub88x(FR_INT4 i)
{
extern FR_INT4AY ityp;

extern FR_INT4 ianz,ifrej;

/***********************************************************************
* start function
***********************************************************************/
/*----------------------------------------------------------------------
* Anzahl Knoten
*---------------------------------------------------------------------*/
if     (ityp[i] == 1  || ityp[i] == 7  ||
        ityp[i] == 8  || ityp[i] == 20 ||
        ityp[i] == 23)                     ianz= 8;

else if(ityp[i] == 2  || ityp[i] == 4 ||
        ityp[i] == 5  || ityp[i] == 9 ||
        ityp[i] ==13)                      ianz= 2;

else if(ityp[i] == 3  || ityp[i] == 14 ||
        ityp[i] == 15 || ityp[i] == 18 ||
        ityp[i] == 24)                     ianz= 6;

else if(ityp[i] == 6)                      ianz= 3;

else if(ityp[i] == 10)                     ianz= 20;

else if(ityp[i] == 16)                     ianz= 10;

else if(ityp[i] == 17)                     ianz= 4;

else if(ityp[i] == 11 || ityp[i] == 12 ||
        ityp[i] == 22)                     ianz= 12;

else if(ityp[i] == 19 || ityp[i] == 21)    ianz= 16;

/*----------------------------------------------------------------------
* Anzahl Freiheitsgrade pro Knoten
*---------------------------------------------------------------------*/
if     (ityp[i] == 1  || ityp[i] == 4  || 
        ityp[i] == 10 || ityp[i] == 13 ||
        ityp[i] == 16 || ityp[i] == 17 ||
        ityp[i] == 18 || ityp[i] == 19 ||
        ityp[i] == 20 || ityp[i] == 21 ||
        ityp[i] == 22)                      ifrej= 3;

else if(ityp[i] == 2  || ityp[i] == 5  ||
        ityp[i] == 23 || ityp[i] == 24)     ifrej= 6; 

else                                        ifrej= 2;

return; 
}

