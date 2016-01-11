/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for Windows & UNIX.
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
* Z88O.H fuer UNIX und Windows
* 3.8.2011 Rieg
***********************************************************************/

/***********************************************************************
* Datentypen Windows und UNIX
***********************************************************************/
#define FR_INT4AY long *               /* Pointer auf long        */
#define FR_INT4 long                   /* 4 Bytes Integer         */
#define FR_SIZERW size_t               /* Size fuer fread, fwrite */
#define FR_CHARAY char *               /* Pointer auf char        */

#ifdef FR_XDOUB
#define FR_SQRT sqrt                   /* sqrt                    */
#define FR_POW pow                     /* pow                     */
#define FR_FABS fabs                   /* fabs                    */
#define FR_SIN sin                     /* sin                     */
#define FR_COS cos                     /* cos                     */
#define FR_ATAN atan                   /* atan                    */
#define FR_DOUBLEAY double *           /* Pointer auf double      */
#define FR_DOUBLE double               /* double                  */
#endif

#ifdef FR_UNIX
#define FR_CALLOC calloc               /* calloc                  */
#endif

#ifdef FR_WIN
#define FR_CALLOC calloc               /* calloc                  */
#endif

#include <z88math.h>

/***********************************************************************
* Icon
***********************************************************************/
#define ICO_Z88O             10

/***********************************************************************
* Cursor
***********************************************************************/
#define CUR_Z88O             11

/***********************************************************************
* Toolbar
***********************************************************************/
#define BMP_Z88O             12

/***********************************************************************
* Steuerflags
***********************************************************************/
#define ID_NOTLOADSTRUC      20 /* Ladezustand Struktur      */
#define ID_LOADSTRUC         21 /* Strukturfile geladen      */
#define ID_NOTLOADVERF       30 /* Ladezustand Z88O2.TXT     */
#define ID_LOADVERF          31 /* Z88O2.TXT geladen         */  
#define ID_NOTLOADSPANN      40 /* Ladezustand Z88O8.TXT     */
#define ID_LOADSPANN         41 /* Z88O8.TXT geladen         */
#define ID_NOTLOADSPAO5      45 /* Ladezustand Z88O5.TXT     */
#define ID_LOADSPAO5         46 /* Z88O5.TXT geladen         */
#define ID_ZOOM              50 /* Maus: Zoomen              */
#define ID_PAN               51 /* Maus: Verschieben         */
#define ID_ROTATE            52 /* Maus: Rotieren            */
#define ID_FUNKEY            60 /* Rotieren via F-Tasten     */
#define ID_MOUSE             61 /* Rotieren via Maus         */
#define ID_DISABLELABELS     70 /* Labels aus                */
#define ID_ENABLELABELS      71 /* Labels an                 */
#define ID_NOTLOADRBD        80 /* Ladezustand Z88I2.TXT     */
#define ID_LOADRBD           81 /* Z88I2.TXT geladen         */  
#define ID_NOTLOADI5         85 /* Ladezustand Z88I2.TXT     */ 
#define ID_LOADI5            86 /* Z88I5.TXT geladen         */  

/***********************************************************************
* Menue-IDs
***********************************************************************/
#define IDM_RUN              100
#define IDM_FILE             102
#define IDM_XIT              104
#define IDM_WER              106

#define IDM_ZOOM             110 
#define IDM_PAN              112 
#define IDM_ROTATE           114 

#define IDM_UNVERFORMT       120
#define IDM_VERFORMT         122

#define IDM_LIGHT            130 
#define IDM_HIDDEN           131
#define IDM_WIREFR           132
#define IDM_SHOWSPANN        133
#define IDM_SHOWGAUSS        134
#define IDM_SHOWGAUPU        135
#define IDM_SHOWVX           136
#define IDM_SHOWVY           137
#define IDM_SHOWVZ           138

#define IDM_YESSCALE         150
#define IDM_NOSCALE          152

#define IDM_NOLABELS         160
#define IDM_KNOTEN           162
#define IDM_ELEMENTE         164
#define IDM_LALLES           165

#define IDM_PRIOR            170
#define IDM_NEXT             172
#define IDM_UP               174
#define IDM_DOWN             176
#define IDM_LEFT             178
#define IDM_RIGHT            180
#define IDM_HOME             182
#define IDM_END              184
#define IDM_F2               186
#define IDM_F3               188
#define IDM_F4               190
#define IDM_F5               192
#define IDM_F6               194
#define IDM_F7               196
#define IDM_F8               198

#define IDM_VER              200
#define IDM_ROT              202
#define IDM_ZM               204

#define IDM_YESRBD           210
#define IDM_NORBD            212
#define IDM_ZOPLUS           214
#define IDM_ZOMINUS          216
#define IDM_RBDUX            218
#define IDM_RBDUY            220
#define IDM_RBDUZ            222
#define IDM_RBDU4            224
#define IDM_RBDU5            226
#define IDM_RBDU6            228
#define IDM_RBDUA            230
#define IDM_RBDOL            232
#define IDM_RBDFX            234
#define IDM_RBDFY            236
#define IDM_RBDFZ            238
#define IDM_RBDALL           240

#define IDM_GPZOPLUS         242
#define IDM_GPZOMINUS        244

#define IDM_YESKOOR          250
#define IDM_NOKOOR           252

#define IDM_YESNOST          254
#define IDM_NONOST           256

#define IDM_WZOOM            260

#define IDM_HELP             490

/**********************************************************
* Toolbar-IDs
**********************************************************/
#define ITC_RUN              500
#define ITC_FILE             501
#define ITC_YESSCALE         502

#define ITC_MAUS             510

#define ITC_UNVERFORMT       520
#define ITC_VERFORMT         521

#define ITC_LIGHT            530 
#define ITC_HIDDEN           531 
#define ITC_WIREFR           532 
#define ITC_SHOWSPANN        533
#define ITC_SHOWGAUSS        534
#define ITC_SHOWGAUPU        535
#define ITC_SHOWVX           536
#define ITC_SHOWVY           537
#define ITC_SHOWVZ           538

#define ITC_NOLABELS         540
#define ITC_KNOTEN           541
#define ITC_ELEMENTE         542

#define ITC_RBD              545

#define ITC_HELP             550
#define ITC_XIT              560

/**********************************************************
* Box-IDs
**********************************************************/
/*---------------------------------------------------------
* Interface
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT1        600

/*---------------------------------------------------------
* Struktur
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT2        610

/*---------------------------------------------------------
* Globale Vergroesserungen
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT3        620
#define IDDLG_V_TEXT4        630
#define IDDLG_V_TEXT5        640

/*---------------------------------------------------------
* Zentrierfaktoren
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT6        650
#define IDDLG_V_TEXT7        660
#define IDDLG_V_TEXT8        670

/*---------------------------------------------------------
* Vergroesserungen Verschiebungen
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT9        680
#define IDDLG_V_TEXT10       690
#define IDDLG_V_TEXT11       700

/*---------------------------------------------------------
* Rotationen
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT12       710
#define IDDLG_V_TEXT13       720
#define IDDLG_V_TEXT14       730

/*---------------------------------------------------------
* FXCOR
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT15       740

/*---------------------------------------------------------
* Knoten von - bis
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT16       750
#define IDDLG_V_TEXT17       760

/*---------------------------------------------------------
* Elemente von - bis
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT18       770
#define IDDLG_V_TEXT19       780

/***********************************************************************
* Alerts
***********************************************************************/
#define AL_NOLOG 3000                  /* kein Z88O.LOG */ 
#define AL_NODYN 3010                  /* kein Z88.DYN */
#define AL_WRONGDYN 3020               /* Fehler in Z88.DYN */
#define AL_NOMEMY 3030                 /* nicht genug Memory */
#define AL_NONINT0 3040                /* NINT != 0 */
#define AL_NINT0 3045                  /* NINT = 0 */
#define AL_NOSTRFI 3050                /* kein Strukturfile */
#define AL_NOI2 3055                   /* kein Z88I2.TXT */
#define AL_NOO2 3060                   /* kein Z88O2.TXT */
#define AL_NOI5 3065                   /* kein Z88I5.TXT */
#define AL_NOO8 3070                   /* kein Z88O8.TXT */
#define AL_NOO5 3075                   /* kein Z88O5.TXT */
#define AL_EXMAXK 3080                 /* MAXK ueberschritten */
#define AL_EXMAXKOI 3085               /* MAXKOI ueberschritten */
#define AL_EXMAXE 3090                 /* MAXE ueberschritten */
#define AL_EXMAXPR 3092                /* MAXPR ueberschritten */
#define AL_EXMAXRBD 3095               /* MAXRBD ueberschritten */
#define AL_EXMAXGP 3097                /* MAXGP ueberschritten */
#define AL_WRONGDIM 3100               /* NDIM falsch */
#define AL_NOOGL 3110                  /* kein Z88O.OGL */
#define AL_WRONGOGL 3120               /* Z88O.OGL falsch */
#define AL_NOFCD 3130                  /* kein Z88.FCD */
#define AL_WRONGFCD 3140               /* Z88.FCD falsch */
#define AL_NO_GLX 3150                 /* kein GLX-Context */
#define AL_NOHELP 3160                 /* keine Hilfe */
#define AL_NO_CF_GRAFICS 3170          /* kann Pango-Font nicht oeffnen */
#define AL_NOMAN 3180                  /* keine Z88MAN.TXT */
#define AL_WRONGMAN 3190               /* Z88MAN.TXT falsch */
#define AL_NOACROBAT 3200              /* kein PDF-Viewer */
 
/***********************************************************************
* LOGs
***********************************************************************/
#define LOG_BZ88OWIN 4000              /* Start Z88O */
#define LOG_OPENDYN 4010               /* Oeffnen Z88.DYN */
#define LOG_NODYN 4020                 /* kein Z88.DYN */
#define LOG_WRONGDYN 4030              /* Z88.DYN falsch */
#define LOG_MAXKOI 4040                /* MAXKOI */
#define LOG_MAXK 4050                  /* MAXK */
#define LOG_MAXE 4060                  /* MAXE */
#define LOG_OKDYN 4090                 /* Z88.DYN gelesen..o.k. */
#define LOG_ALLOCMEMY 4100             /* Memory anlegen */
#define LOG_ARRAYNOTOK 4110            /* Array nicht o.k. */
#define LOG_ARRAYOK 4120               /* Array o.k. */
#define LOG_SUMMEMY 4130               /* Memory in Bytes */
#define LOG_EXITDYN88O 4140            /* Verlassen Speicherunit DYN88O */
#define LOG_REAI2 4145                 /* Einlesen Z88I2.TXT */
#define LOG_REAI2OK 4147               /* Z88I2.TXT eingelesen */
#define LOG_REAO2 4150                 /* Einlesen Z88O2.TXT */
#define LOG_REAO2OK 4160               /* Z88O2.TXT eingelesen */
#define LOG_REAO8 4170                 /* Einlesen Z88O8.TXT */
#define LOG_REAO5 4171                 /* Einlesen Z88O5.TXT */
#define LOG_BRI588 4172                /* Einlesen Z88I5.TXT */
#define LOG_EXITRI588 4175             /* Z88I5.TXT eingelesen */
#define LOG_NONINT0 4180               /* NINT != 0 */
#define LOG_NINT0 4185                 /* NINT = 0 */
#define LOG_REAO8OK 4190               /* Z88O8.TXT eingelesen */
#define LOG_REAO5OK 4195               /* Z88O5.TXT eingelesen */
#define LOG_REAI1 4200                 /* Einlesen Z88I1.TXT */
#define LOG_REAI1OK 4210               /* Z88I1.TXT eingelesen */
#define LOG_NOSTRFI 4220               /* kein Strukturfile */
#define LOG_NOI2 4225                  /* kein Z88I2.TXT */
#define LOG_NOO2 4230                  /* kein Z88O2.TXT */
#define LOG_NOI5 4235                  /* kein Z88I5.TXT */
#define LOG_NOO8 4240                  /* kein Z88O8.TXT */
#define LOG_NOO5 4245                  /* kein Z88O5.TXT */
#define LOG_EXMAXK 4250                /* MAXK ueberschritten */
#define LOG_EXMAXKOI 4255              /* MAXKOI ueberschritten */
#define LOG_EXMAXE 4260                /* MAXE ueberschritten */
#define LOG_EXMAXPR 4262               /* MAXPR ueberschritten */
#define LOG_EXMAXRBD 4265              /* MAXRBD ueberschritten */
#define LOG_EXMAXGP 4267               /* MAXGP ueberschritten */
#define LOG_WRONGDIM 4270              /* NDIM falsch */
#define LOG_NOOGL 4280                 /* kein Z88O.OGL */
#define LOG_WRONGOGL 4290              /* Z88O.OGL falsch */
#define LOG_NOFCD 4300                 /* kein Z88.FCD */
#define LOG_WRONGFCD 4310              /* Z88.FCD falsch */
#define LOG_NO_CF_ENTRIES 4320         /* kein Font CF_ENTRIES */
#define LOG_NO_CF_BUTTONS 4330         /* kein Font CF_BUTTONS */
#define LOG_NO_CF_GRAFICS 4340         /* kein Font CF_GRAFICS */
#define LOG_NO_CO_BACKGR 4350          /* keine Farbe CO_BACKGR */
#define LOG_NO_CO_FOREGR 4360          /* keine Farbe CO_FOREGR */
#define LOG_NO_CO_ENTRIES 4370         /* keine Farbe CO_ENTRIES */
#define LOG_NO_GLX 4380                /* kein  GLX-Context */
#define LOG_NOMAN 4390                 /* keine Z88MAN.TXT */
#define LOG_WRONGMAN 4400              /* Z88MAN.TXT falsch */
#define LOG_NOACROBAT 4410             /* kein PDF-Viewer */


