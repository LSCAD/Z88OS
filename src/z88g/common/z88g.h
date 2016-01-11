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
* z88g.h, fuer UNIX und Windows
* 29.7.2011 Rieg
***********************************************************************/

/***********************************************************************
* Datentypen Windows und UNIX 
***********************************************************************/
#define FR_INT4AY long *               /* Pointer auf long        */
#define FR_INT4 long                   /* long                    */
#define FR_CALLOC calloc               /* calloc */
#define FR_SIZERW size_t               /* Size fuer fread, fwrite */

#ifdef FR_XDOUB
#define FR_DOUBLEAY double *           /* Pointer auf double      */
#define FR_DOUBLE double               /* double                  */
#define FR_FABS fabs                   /* fabs                    */
#endif

#include <z88math.h>

/***********************************************************************
* Icon
***********************************************************************/
#define ICO_Z88G                       10

/***********************************************************************
* Cursor
***********************************************************************/
#define CUR_Z88G                       20

/***********************************************************************
* Toolbar
***********************************************************************/
#define BMP_Z88G                       30

/***********************************************************************
* Menue-IDs
***********************************************************************/
#define IDM_WER                        100
#define IDM_XIT                        110
#define IDM_VOLU                       120
#define IDM_SHEI                       130
#define IDM_PLAT                       140
#define IDM_TORU                       150
#define IDM_SHEL                       160
#define IDM_GO                         170
#define IDM_NAST                       180
#define IDM_COSM                       190

/***********************************************************************
* Toolbar-IDs
***********************************************************************/
#define ITC_GO                         200
#define ITC_VOLU                       210
#define ITC_SHEI                       220
#define ITC_PLAT                       230
#define ITC_TORU                       240
#define ITC_SHEL                       250
#define ITC_HELP                       260
#define ITC_NAST                       270
#define ITC_COSM                       280
#define ITC_XIT                        290

/***********************************************************************
* Alerts
***********************************************************************/
#define AL_NOLOG 3000                  /* kein Z88G.LOG */ 
#define AL_NODYN 3010                  /* kein Z88.DYN */
#define AL_WRONGDYN 3020               /* Fehler in Z88.DYN */
#define AL_NOCOS 3030                  /* kein z88g.cos */
#define AL_NONAS 3033                  /* kein z88g.nas */
#define AL_NOIN 3035                   /* kein z88g.in */
#define AL_NOI1 3040                   /* Fehler Oeffnen z88i1.txt */
#define AL_NOI2 3050                   /* Fehler Oeffnen z88i2.txt */
#define AL_NOI5 3060                   /* Fehler Oeffnen z88i3.txt */
#define AL_NOMEMY 3070                 /* nicht genug Speicher */
#define AL_NOACROBAT 3080              /* kein Acrobat-Reader  */

/***********************************************************************
* Texte
***********************************************************************/
#define TX_COSOPEN 3500                /* Z88G.COS geoeffnet */
#define TX_NASOPEN 3510                /* Z88G.NAS geoeffnet */
#define TX_INOPEN  3520                /* Z88G.IN geoeffnet */
#define TX_I1OPEN  3530                /* Z88I1.TXT geoeffnet */
#define TX_I2OPEN  3540                /* Z88I2.TXT geoeffnet */
#define TX_I5OPEN  3550                /* Z88I5.TXT geoeffnet */
#define TX_DIMDET  3560                /* Dimension entdeckt */
#define TX_NODDET  3570                /* i Knoten entdeckt */
#define TX_ELEDET  3580                /* i Elemente entdeckt */
#define TX_CONDET  3590                /* i Randbed. entdeckt */
#define TX_PELDET  3600                /* i Elemente mit Druck entd. */
#define TX_REAWRI  3610                /* abw. Lesen und Schreiben */
#define TX_NODDON  3620                /* i Knoten fertig */
#define TX_ELEDON  3630                /* i Elemente fertig */
#define TX_CONDON  3640                /* i Randbed. fertig */
#define TX_16DET   3650                /* i Elemente Nr.16 entdeckt */  
#define TX_17DET   3660                /* i Elemente Nr.17 entdeckt */  
#define TX_7DET    3670                /* i Elemente Nr.7 entdeckt */  
#define TX_14DET   3680                /* i Elemente Nr.14 entdeckt */  
#define TX_18DET   3690                /* i Elemente Nr.18 entdeckt */  
#define TX_20DET   3700                /* i Elemente Nr.20 entdeckt */  
#define TX_8DET    3720                /* i Elemente Nr.8 entdeckt */  
#define TX_15DET   3730                /* i Elemente Nr.15 entdeckt */  
#define TX_23DET   3740                /* i Elemente Nr.23 entdeckt */  
#define TX_24DET   3750                /* i Elemente Nr.24 entdeckt */  
#define TX_Z88CS   3760                /* Z88 Daten fertig */
#define TX_Z88DONE 3770                /* Z88 fertig */
#define TX_SHEIPLA 3780                /* gewaehlter Elementtyp */
#define TX_CHOICOS 3790                /* Auswahl Elementtyp COSMOS */
#define TX_CHOINAS 3800                /* Auswahl Elementtyp COSMOS */
#define TX_COSNAS  3810                /* Auswahl COSMOS oder NASTRAN */
#define TX_FILEF   3820                /* File COSMOS oder NASTRAN */
#define TX_ISPC    3830                /* Lagerfall bei NASTRAN */
#define TX_ILOAD   3840                /* Lastfall bei NASTRAN */

/***********************************************************************
* Log
***********************************************************************/
#define LOG_BZ88 4000                  /* Beginn Z88G */
#define LOG_OPENZ88DYN 4010            /* Oeffnen Z88.DYN */
#define LOG_NODYN 4020                 /* kann Z88.DYN nicht oeffnen */
#define LOG_WRONGDYN 4030              /* Z88.DYN nicht o.k. */
#define LOG_NOCOS 4040                 /* kein Z88G.COS */  
#define LOG_NONAS 4050                 /* kein Z88G.NAS */  
#define LOG_NOIN 4060                  /* kein Z88G.IN */  
#define LOG_NOI1 4070                  /* kein Z88I1.TXT */
#define LOG_NOI2 4080                  /* kein Z88I2.TXT */
#define LOG_NOI5 4090                  /* kein Z88I5.TXT */
#define LOG_DIMDET 4100                /* Dimension entdeckt */
#define LOG_NODDET 4110                /* i Knoten entdeckt */
#define LOG_ELEDET 4120                /* i Elemente entdeckt */
#define LOG_CONDET 4130                /* i Randbed. entdeckt */
#define LOG_PELDET 4140                /* i Ele mit Druck entdeckt */
#define LOG_REAWRI 4150                /* abw. Lesen und Schreiben */
#define LOG_NODDON 4160                /* i Knoten fertig */
#define LOG_ELEDON 4170                /* i Elemente fertig */
#define LOG_CONDON 4180                /* i Randbed. fertig */
#define LOG_16DET 4190                 /* i Elemente Nr.16 entdeckt */  
#define LOG_17DET 4200                 /* i Elemente Nr.17 entdeckt */  
#define LOG_7DET 4210                  /* i Elemente Nr.7 entdeckt */  
#define LOG_14DET 4220                 /* i Elemente Nr.14 entdeckt */  
#define LOG_18DET 4230                 /* i Elemente Nr.18 entdeckt */  
#define LOG_20DET 4240                 /* i Elemente Nr.20 entdeckt */  
#define LOG_8DET 4250                  /* i Elemente Nr.8 entdeckt */  
#define LOG_15DET 4260                 /* i Elemente Nr.15 entdeckt */ 
#define LOG_23DET 4270                 /* i Elemente Nr.23 entdeckt */   
#define LOG_24DET 4280                 /* i Elemente Nr.24 entdeckt */   
#define LOG_Z88CS 4290                 /* Z88 Daten fertig */
#define LOG_Z88DONE 4300               /* Z88 fertig */
#define LOG_SHEIPLA 4310               /* Platte oder Scheibe */
#define LOG_FILEF 4320                 /* COSMOS oder NASTRAN */
#define LOG_ARRAYOK 4330               /* Speicher ok */
#define LOG_ARRAYNOTOK 4340            /* Speicher nicht ok */
#define LOG_ISPC 4350                  /* Lagerfall bei NASTRAN */
#define LOG_ILOAD 4360                 /* Lastfall bei NASTRAN */
#define LOG_NOACROBAT 4370             /* kein Acrobat-Reader  */

