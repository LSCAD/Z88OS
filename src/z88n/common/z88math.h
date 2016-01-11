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
*  z88math.h fuer UNIX und Windows
*  16.7.2011 Rieg
***********************************************************************/

/***********************************************************************
* Datentypen - double precision oder quad precision 
***********************************************************************/
#ifdef FR_WIN
  #include <math.h>
#endif

#ifdef FR_LINUX
  #include <math.h>
#endif

#ifdef FR_SGI_XDOUB
  #include <math.h>
#endif 

#ifdef FR_SUN_XDOUB
  #include <math.h>
#endif   

#ifdef FR_SGI_XQUAD
  extern long double sqrtl(long double);
  extern long double powl(long double, long double);
  extern long double fabsl(long double);
  extern long double sinl(long double);
  extern long double cosl(long double);
  extern long double atanl(long double);
#endif   

#ifdef FR_SUN_XQUAD
  extern long double sqrtl(long double);
  extern long double powl(long double, long double);
  extern long double fabsl(long double);
  extern long double sinl(long double);
  extern long double cosl(long double);
  extern long double atanl(long double);
#endif   

