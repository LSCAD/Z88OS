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
* Z88COM.H fuer UNIX und Windows
* 66.7.2011 Rieg
***********************************************************************/

/***********************************************************************
* Datentypen UNIX und Windows 
***********************************************************************/
#define FR_INT4 long                   /* long                    */

/***********************************************************************
* Icon (Windows)
***********************************************************************/
#define ICO_Z88COM                       10

/***********************************************************************
* Toolbar (Windows)
***********************************************************************/
#define BMP_Z88COM                       20

/***********************************************************************
* Hintergrund (Windows)
***********************************************************************/
#define BMP_Z88BGR                       30

/***********************************************************************
* Toolbar-IDs (Windows)
***********************************************************************/
#define ITC_Z88X                        100
#define ITC_Z88G                        110
#define ITC_Z88H                        120
#define ITC_Z88N                        130
#define ITC_Z88R                        140
#define ITC_Z88O                        150
#define ITC_DYN                         160
#define ITC_HELP                        170
#define ITC_XIT                         180

/***********************************************************************
* Menue-IDs (Windows)
***********************************************************************/
#define IDM_DATEI                      1000
#define IDM_EDITFEST                   1010
#define IDM_WER                        1020
#define IDM_XIT                        1030
#define IDM_ACROBAT                    1040

#define IDM_COMPUTE                    1050
#define IDM_Z88G                       1060
#define IDM_Z88H                       1070
#define IDM_Z88X                       1080
#define IDM_Z88N                       1090
#define IDM_Z88R                       1100

#define IDM_EDIT                       1200
#define IDM_Z88DYNEDIT                 1210
#define IDM_EDITCOL                    1220
#define IDM_EDITOGL                    1230
#define IDM_Z88NITXT                   1240
#define IDM_Z88I1TXT                   1250
#define IDM_Z88I2TXT                   1260
#define IDM_Z88MANTXT                  1270
#define IDM_Z88MATTXT                  1280
#define IDM_Z88ELPTXT                  1290
#define IDM_Z88INTTXT                  1300
#define IDM_Z88MATCSV                  1310
#define IDM_Z88I5TXT                   1320
#define IDM_Z88O0TXT                   1330
#define IDM_Z88O1TXT                   1340
#define IDM_Z88O2TXT                   1350
#define IDM_Z88O3TXT                   1360
#define IDM_Z88O4TXT                   1370
#define IDM_Z88O6TXT                   1380

#define IDM_Z88O                       1400 
 
/**********************************************************
* Box-IDs (Windows)
**********************************************************/
/*---------------------------------------------------------
* Editor definieren
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT1                  1900
#define IDDLG_V_TEXT2                  1910

/*---------------------------------------------------------
* Browser definieren
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT3                  1920
#define IDDLG_V_TEXT4                  1930

/***********************************************************************
* Alerts
***********************************************************************/
#define AL_NOLOG 3000                  /* kein Z88F.LOG */ 
#define AL_NODYN 3010                  /* kein Z88.DYN */
#define AL_WRONGDYN 3020               /* Fehler in Z88.DYN */
#define AL_NOCFG 3030                  /* kein Z88COM.CFG */
#define AL_WRONGCFG 3040               /* Fehler in Z88COM.CFG */
#define AL_NOWRICFG 3050               /* Schreibfehler Z88COM.CFG */
#define AL_NOCOL 3060                  /* kein Z88.FCD */
#define AL_WRONGCOL 3070               /* Z88.FCD falsch */
#define AL_NOZ88X 3080                 /* kann Z88X nicht starten */
#define AL_NOZ88N 3090                 /* kann Z88N nicht starten */
#define AL_NOZ88R 3100                 /* kann Z88R nicht starten */
#define AL_NOZ88G 3110                 /* kann Z88G nicht starten */
#define AL_NOZ88H 3120                 /* kann Z88H nicht starten */
#define AL_NOEDDYN 3130                /* Fehler Editor Z88.DYN */
#define AL_NOEDCOL 3140                /* Fehler Editor Z88P.COL */
#define AL_NOEDOGL 3150                /* Fehler Editor Z88O.OGL */
#define AL_NOEDNI 3160                 /* Fehler Editor Z88NI.TXT */
#define AL_NOEDI1 3170                 /* Fehler Editor Z88I1.TXT */
#define AL_NOEDI2 3180                 /* Fehler Editor Z88I2.TXT */
#define AL_NOEDMAN 3190                /* Fehler Editor Z88MAN.TXT */
#define AL_NOEDMAT 3200                /* Fehler Editor Z88MAT.TXT */
#define AL_NOEDELP 3210                /* Fehler Editor Z88ELP.TXT */
#define AL_NOEDINT 3220                /* Fehler Editor Z88INT.TXT */
#define AL_NOEDI5 3230                 /* Fehler Editor Z88I5.TXT */
#define AL_NOEDO0 3240                 /* Fehler Editor Z88O0.TXT */
#define AL_NOEDO1 3250                 /* Fehler Editor Z88O1.TXT */
#define AL_NOEDO2 3260                 /* Fehler Editor Z88O2.TXT */
#define AL_NOEDO3 3270                 /* Fehler Editor Z88O3.TXT */
#define AL_NOEDO4 3280                 /* Fehler Editor Z88O4.TXT */
#define AL_NOEDFCD 3290                /* Fehler Editor Z88.FCD */
#define AL_NOZ88O 3300                 /* kann Z88O nicht starten */
#define AL_NOACROBAT 3310              /* kein Acrobat-Reader */
#define AL_NOHELP 3320                 /* kann Acrobat-Reader nicht starten */

/***********************************************************************
* LOGs
***********************************************************************/
#define LOG_BZ88COM 4000               /* Beginn Z88 */
#define LOG_OPENDYN 4010               /* Oeffnen Z88.DYN */
#define LOG_NODYN 4020                 /* kann Z88.DYN nicht oeffnen */
#define LOG_WRONGDYN 4030              /* Z88.DYN nicht o.k. */
#define LOG_NOCFG 4040                 /* kann Z88.DYN nicht oeffnen */
#define LOG_WRONGCFG 4050              /* Z88.DYN nicht o.k. */
#define LOG_NOWRICFG 4060              /* Schreibfehler Z88COM.CFG */
#define LOG_NOCOL 4070                 /* kein Z88.FCD */
#define LOG_WRONGCOL 4080              /* Z88.FCD falsch */
#define LOG_NOZ88X 4090                /* kann Z88X nicht starten */
#define LOG_NOZ88N 4100                /* kann Z88N nicht starten */
#define LOG_NOZ88R 4110                /* kann Z88R nicht starten */
#define LOG_NOZ88G 4120                /* kann Z88G nicht starten */
#define LOG_NOZ88H 4130                /* kann Z88H nicht starten */
#define LOG_NOEDDYN 4140               /* Fehler Editor Z88.DYN */
#define LOG_NOEDFCD 4150               /* Fehler Editor Z88.FCD */
#define LOG_NOEDOGL 4160               /* Fehler Editor Z88O.OGL */
#define LOG_NOEDNI 4170                /* Fehler Editor Z88NI.TXT */
#define LOG_NOEDI1 4180                /* Fehler Editor Z88I1.TXT */
#define LOG_NOEDI2 4190                /* Fehler Editor Z88I2.TXT */
#define LOG_NOEDMAN 4200               /* Fehler Editor Z88MAN.TXT */
#define LOG_NOEDMAT 4210               /* Fehler Editor Z88MAT.TXT */
#define LOG_NOEDELP 4220               /* Fehler Editor Z88ELP.TXT */
#define LOG_NOEDINT 4230               /* Fehler Editor Z88INT.TXT */
#define LOG_NOEDI5 4240               /* Fehler Editor Z88I5.TXT */
#define LOG_NOEDO0 4250                /* Fehler Editor Z88O0.TXT */
#define LOG_NOEDO1 4260                /* Fehler Editor Z88O1.TXT */
#define LOG_NOEDO2 4270                /* Fehler Editor Z88O2.TXT */
#define LOG_NOEDO3 4280                /* Fehler Editor Z88O3.TXT */
#define LOG_NOEDO4 4290                /* Fehler Editor Z88O4.TXT */
#define LOG_NOZ88O 4300                /* kann Z88O nicht starten */
#define LOG_NOACROBAT 4310             /* kein Browser */
#define LOG_LADETECT 4320              /* Sprache entdeckt */
  
