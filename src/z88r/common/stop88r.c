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
****************************************************************************/  
/****************************************************************************
*  Funtion stop88r.c
*  2.1.2010 Rieg
****************************************************************************/

/****************************************************************************
* Fuer UNIX
****************************************************************************/
#ifdef FR_UNIX
#include <stdlib.h> /* exit */
void stop88r(void)
{
exit(1);
}
#endif

/****************************************************************************
* Fuer Windows
****************************************************************************/
#ifdef FR_WIN
#include <stdlib.h> /* exit */
void stop88r(void)
{
exit(1);
}
#endif

/****************************************************************************
* Fuer Windows + GTK+
****************************************************************************/
#ifdef FR_GTKWIN
#include <stdlib.h> /* exit */
void stop88r(void)
{
exit(1);
}
#endif

