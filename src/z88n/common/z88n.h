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
*  z88n.h fuer UNIX und Windows
*  3.8.2011 Rieg
***********************************************************************/

/***********************************************************************
* Datentypen - double precision oder quad precision 
***********************************************************************/
#define FR_CALLOC calloc               /* calloc */
#define FR_SIZERW size_t               /* Size fuer fread, fwrite */
#define FR_CHARAY char *               /* Pointer auf char */

#ifdef FR_XINT
#define FR_INT4AY int *                /* Pointer auf int         */
#define FR_INT4 int                    /* int                     */
#endif

#ifdef FR_XLONG
#define FR_INT4AY long *               /* Pointer auf long        */
#define FR_INT4 long                   /* long                    */
#endif

#ifdef FR_XLOLO
#define FR_INT4AY long long *          /* Pointer auf long long   */
#define FR_INT4 long long              /* long long               */
#endif

#ifdef FR_XDOUB
#define FR_SQRT sqrt                   /* sqrt                    */
#define FR_POW pow                     /* pow                     */
#define FR_FABS fabs                   /* fabs                    */
#define FR_SIN sin                     /* sin                     */
#define FR_COS cos                     /* cos                     */
#define FR_ATAN2 atan2                 /* atan2                   */
#define FR_DOUBLEAY double *           /* Pointer auf double      */
#define FR_DOUBLE double               /* double                  */
#endif

#ifdef FR_XQUAD
#define FR_SQRT sqrtl                  /* sqrtl                   */
#define FR_POW powl                    /* powl                    */
#define FR_FABS fabsl                  /* fabsl                   */
#define FR_SIN sinl                    /* sinl                    */
#define FR_COS cosl                    /* cosl                    */
#define FR_ACOS acosl                  /* acos                    */
#define FR_ATAN atanl                  /* atanl                   */
#define FR_DOUBLEAY long double *      /* Pointer auf long double */
#define FR_DOUBLE long double          /* long double             */
#endif

#include <z88math.h>

/***********************************************************************
* Icon
***********************************************************************/
#define ICO_Z88N                       10

/***********************************************************************
* Cursor
***********************************************************************/
#define CUR_Z88N                       20

/***********************************************************************
* Toolbar
***********************************************************************/
#define BMP_Z88N                       30

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
#define AL_NOLOG 3000                  /* kein Z88N.LOG */ 
#define AL_NODYN 3010                  /* kein Z88.DYN */
#define AL_WRONGDYN 3020               /* Fehler in Z88.DYN */
#define AL_NOMEMY 3030                 /* nicht genug Memory */
#define AL_NOI1 3040                   /* Fehler Oeffnen z88i1.txt */
#define AL_NONI 3050                   /* Fehler Oeffnen z88ni.txt */
#define AL_EXSUPERK 3060               /* zuviele Superknoten */
#define AL_EXSUPERE 3070               /* zuviele Superelemente */
#define AL_TOBIG1 3080                 /* Struktur > MAXSE */
#define AL_FEEXID 3090                 /* zu grosse Struktur erz. */
#define AL_NOFCD 3100                  /* Fehler in Z88.FCD */
#define AL_NOACROBAT 3110              /* kein PDF-Viewer */

/***********************************************************************
* Texte
***********************************************************************/
#define TX_REANI 3500                  /* Z88NI.TXT einlesen */
#define TX_BERJOIN 3510                /* join berechnen */
#define TX_BERKOOR 3520                /* Koordinaten berechnen */
#define TX_SUPERELE 3530               /* Superelement I */
#define TX_BERKOIN 3540                /* Koinzidenz berechnen */
#define TX_WRII1 3550                  /* Z88I1.TXT beschreiben */

/***********************************************************************
* Log- Eintraege
***********************************************************************/
#define LOG_BZ88N 4000                 /* Start Z88N */
#define LOG_OPENDYN 4010               /* Oeffnen Z88.DYN */
#define LOG_NODYN 4020                 /* kein Z88.DYN */
#define LOG_WRONGDYN 4030              /* Z88.DYN falsch */
#define LOG_MAXSE 4040                 /* MAXSE */
#define LOG_MAXESS 4050                /* MAXESS */
#define LOG_MAXKSS 4060                /* MAXKSS */
#define LOG_MAXAN 4070                 /* MAXAN */
#define LOG_MAXK 4080                  /* MAXK */
#define LOG_MAXE 4090                  /* MAXE */
#define LOG_MAXNFG 4100                /* MAXNFG */
#define LOG_MAXNEG 4110                /* MAXNEG */
#define LOG_OKDYN 4120                 /* Z88.DYN gelesen..o.k. */
#define LOG_ALLOCMEMY 4130             /* Memory anlegen */
#define LOG_ARRAYNOTOK 4140            /* Array nicht o.k. */
#define LOG_ARRAYOK 4150               /* Array o.k. */
#define LOG_SUMMEMY 4160               /* Memory in Bytes */
#define LOG_EXITDYN88N 4170            /* Verlassen Speicherunit DYN88N */
#define LOG_REANI 4180                 /* Start Leseunit RNI88 */
#define LOG_OPENNI 4190                /* Oeffnen Z88NI.TXT */
#define LOG_NONI 4200                  /* kein Z88NI.TXT */
#define LOG_OPENI1 4210                /* Oeffnen Z88I1.TXT */
#define LOG_NOI1 4220                  /* kein Z88I1.TXT */
#define LOG_EXSUPERK 4230              /* zuviel Superknoten */
#define LOG_EXSUPERE 4240              /* zuviel Superelemente */
#define LOG_EXITRNI88 4250             /* Verlassen RNI88 */
#define LOG_BERJOIN 4260               /* Berechne join */
#define LOG_EXITJOIN 4270              /* Exit join */
#define LOG_SMC188N 4280               /* Start MC188N */
#define LOG_SMC288N 4290               /* Start MC288N */
#define LOG_SMC388N 4300               /* Start MC388N */
#define LOG_SMC488N 4310               /* Start MC488N */
#define LOG_SMC588N 4320               /* Start MC588N */
#define LOG_SMC688N 4330               /* Start MC688N */
#define LOG_SMC788N 4340               /* Start MC788N */
#define LOG_SMC888N 4350               /* Start MC888N */
#define LOG_TOBIG1 4360                /* MAXSE zu klein */
#define LOG_BERKOIN 4370               /* Berechne Koinzidenz */
#define LOG_WRII1 4380                 /* Z88O1.TXT beschreiben */
#define LOG_FEEXID 4390                /* Struktur zu gross fuer FE */
#define LOG_NOFCD 4440                 /* Fehler bei Z88.FCD */
#define LOG_NOACROBAT 4450             /* kein PDF-Viewer */


