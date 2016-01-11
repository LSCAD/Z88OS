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
* z88h.h fuer UNIX und Windows
* 3.8.2011 Rieg
***********************************************************************/

/***********************************************************************
* Datentypen Windows und UNIX
***********************************************************************/
#define FR_INT4 long                   /* 4 Bytes Integer         */

#ifdef FR_XDOUB
#define FR_DOUBLE double               /* double                  */
#endif

#include <z88math.h>

/***********************************************************************
* Icon
***********************************************************************/
#define ICO_Z88H                       10

/***********************************************************************
* Cursor
***********************************************************************/
#define CUR_Z88H                       20

/***********************************************************************
* Toolbar
***********************************************************************/
#define BMP_Z88H                       30

/***********************************************************************
* Menue-IDs
***********************************************************************/
#define IDM_WER                        100
#define IDM_XIT                        110
#define IDM_GO                         120

/***********************************************************************
* Toolbar-IDs
***********************************************************************/
#define ITC_GO                         130
#define ITC_HELP                       140
#define ITC_XIT                        150

/***********************************************************************
* Alerts
***********************************************************************/
#define AL_NOLOG 3000                  /* kein Z88H.LOG */ 
#define AL_NODYN 3010                  /* kein Z88.DYN */
#define AL_WRONGDYN 3020               /* Fehler in Z88.DYN */
#define AL_NOI1 3030                   /* Fehler Oeffnen z88i1.txt */
#define AL_NOI2 3040                   /* Fehler Oeffnen z88i2.txt */
#define AL_NOI5 3045                   /* Fehler Oeffnen z88i5.txt */
#define AL_NOIN 3050                   /* Fehler Oeffnen z88h.in */
#define AL_NOOUT 3060                  /* Fehler Oeffnen z88h.out */
#define AL_NOMEM 3070                  /* kein Memory fuer CUT88 */
#define AL_1STOP 3080                  /* Abbruchpunkte */
#define AL_NOACROBAT 3090              /* kein PDF-Viewer */

/***********************************************************************
* Texte
***********************************************************************/
#define TX_INOPEN  3500                /* Z88H.IN geoeffnet */
#define TX_I1OPEN  3510                /* Z88I1.TXT geoeffnet */
#define TX_I2OPEN  3520                /* Z88I2.TXT geoeffnet */
#define TX_I5OPEN  3525                /* Z88I5.TXT geoeffnet */
#define TX_OUTOPEN 3530                /* Z88H.OUT geoeffnet */
#define TX_Z88DONE 3540                /* Z88 fertig */
#define TX_MEMOK   3550                /* Memory fuer CUT88 o.k. */
#define TX_1STOP   3560                /* Abbruchpunkte */
#define TX_MAXGR   3570                /* max. Grad ist */
#define TX_STARTNUM 3580               /* Startnummer */
#define TX_LEVEL   3590                /* Level */
#define TX_STOPERM 3600                /* Abspeichern Permutationsv.*/
#define TX_UMSPEI  3610                /* Umspeichern */
#define TX_NPRCM   3620                /* Wert nprcm */
#define TX_NPRRCM  3630                /* Wert nprrcm */
#define TX_TXT2OLD 3640                /* Z88I*.TXT --> Z88I*.OLD */
#define TX_WRII1   3650                /* Schreiben Z88I1.TXT */
#define TX_WRII2   3660                /* Schreiben Z88I2.TXT */
#define TX_WRII5   3665                /* Schreiben Z88I5.TXT */
 
/***********************************************************************
* Log
***********************************************************************/
#define LOG_BZ88 4000                  /* Beginn Z88H */
#define LOG_OPENDYN 4010               /* Oeffnen Z88.DYN */
#define LOG_NODYN 4020                 /* kann Z88.DYN nicht oeffnen */
#define LOG_WRONGDYN 4030              /* Z88.DYN nicht o.k. */
#define LOG_OKDYN 4040                 /* Z88.DYN o.k. */
#define LOG_NOIN 4050                  /* kein Z88H.IN */  
#define LOG_NOI1 4060                  /* kein Z88I1.TXT */
#define LOG_NOI2 4070                  /* kein Z88I2.TXT */
#define LOG_NOI5 4075                  /* kein Z88I5.TXT */
#define LOG_NOOUT 4080                 /* kein Z88H.OUT */
#define LOG_Z88DONE 4090               /* Z88 fertig */
#define LOG_NOMEM 4100                 /* Memory fuer CUT88 nicht o.k. */
#define LOG_1STOP 4110                 /* Abbruchpunkte */
#define LOG_NOACROBAT 4120             /* kein PDF-Viewer */




