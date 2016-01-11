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
* V14.0 January 14, 2009
*
* Z88 should compile and run under any Windows OS and UNIX OS and 
* GTK+.
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
* forc88
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
* Fuer Windows & GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88r.h>
#endif

/***********************************************************************
* Start forc88
***********************************************************************/
int forc88(void)
{
extern FR_DOUBLEAY se;
extern FR_DOUBLEAY u;

extern FR_DOUBLE f[];
extern FR_DOUBLE ul[];

extern FR_INT4 mcomp[];

extern FR_INT4 mxknot,mxfrei,mxfe;

FR_INT4 j,j2,l,i,mcompj;
        
for(j = 1;j <= mxknot;j++)
  {
  for(j2 = 1;j2 <= mxfrei;j2++)
    {
    mcompj= mcomp[j] + j2;
    l= mxfrei*(j-1) + j2;
    ul[l]= u[mcompj];
    }
  }
            
for(i = 1;i <= mxfe;i++)
  {
  f[i]= 0.;
  for(j = 1;j <= mxfe;j++)
    f[i]= f[i] + se[i+ mxfe*(j-1)] * ul[j];
  }

return(0);
}
