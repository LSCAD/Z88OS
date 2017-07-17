/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the WINDOWS and
* the UNIX OS.
*
* Composed and edited and copyright by 
* Professor Dr.-Ing. Frank Rieg, University of Bayreuth, Germany
*
* eMail: 
* frank.rieg@uni-bayreuth.de
* dr.frank.rieg@t-online.de
* 
* V15.0  November 18, 2015
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
*  z88x.h fuer UNIX und Windows
*  29.7.2011 Rieg
***********************************************************************/

/***********************************************************************
* Datentypen Windows und UNIX
***********************************************************************/
#define FR_INT4AY long *               /* Pointer auf long        */
#define FR_INT4 long                   /* long                    */
#define FR_CALLOC calloc               /* calloc */
#define FR_CHARAY char *               /* Pointer auf char        */
#define FR_SIZERW size_t               /* Size fuer fread, fwrite */

#ifdef FR_XDOUB
#define FR_SIN sin                     /* sin                     */
#define FR_COS cos                     /* cos                     */
#define FR_DOUBLEAY double *           /* Pointer auf double      */
#define FR_DOUBLE double               /* double                  */
#endif

#include <z88math.h>

/***********************************************************************
* Icon
***********************************************************************/
#define ICO_Z88X                       10

/***********************************************************************
* Cursor
***********************************************************************/
#define CUR_Z88X                       20

/***********************************************************************
* Toolbar
***********************************************************************/
#define BMP_Z88X                       30

/***********************************************************************
* Menue-IDs
***********************************************************************/
#define IDM_WER                        100
#define IDM_TEXTSIZE                   105 
#define IDM_XIT                        110
#define IDM_I1TX                       120
#define IDM_IATX                       130
#define IDM_NITX                       140
#define IDM_I1FX                       150
#define IDM_IAFX                       160
#define IDM_NIFX                       170
#define IDM_GO                         180

/***********************************************************************
* Toolbar-IDs
***********************************************************************/
#define ITC_GO                         200
#define ITC_HELP                       210
#define ITC_I1TX                       220
#define ITC_IATX                       230
#define ITC_NITX                       240
#define ITC_I1FX                       250
#define ITC_IAFX                       260
#define ITC_NIFX                       270
#define ITC_XIT                        280

/**********************************************************
* Box-IDs
**********************************************************/
/*---------------------------------------------------------
* Textsize
*--------------------------------------------------------*/ 
#define IDDLG_V_TEXT                   600

/***********************************************************************
* Alerts
***********************************************************************/
#define AL_NOCFLAG 3000                /* kein Steuerflag Z88X */
#define AL_WROCFLAG 3010               /* Steuerflag Z88X falsch */
#define AL_NOLOG 3020                  /* kein Z88X.LOG */ 
#define AL_NODYN 3030                  /* kein Z88.DYN */
#define AL_WRONGDYN 3040               /* Fehler in Z88.DYN */
#define AL_NOMEMY 3050                 /* nicht genug Memory */
#define AL_NOI1 3060                   /* Fehler Oeffnen Z88I1.TXT */
#define AL_NOI2 3070                   /* Fehler Oeffnen Z88I2.TXT */
#define AL_NOI5 3085                   /* Fehler Oeffnen Z88I5.TXT */
#define AL_NONI 3090                   /* Fehler Oeffnen Z88NI.TXT */
#define AL_NOX 3100                    /* Fehler Oeffnen Z88X.DXF */
#define AL_WRONDIM 3120                /* Dimension falsch */
#define AL_EXMAXK 3130                 /* zuviele Knoten */
#define AL_EXMAXE 3140                 /* zuviele Elemente */
#define AL_EXMAXNFG 3150               /* zuviele Freiheitsgrade */
#define AL_EXMAXPR 3165                /* zuviele Flaechenlasten */
#define AL_WROKFLAG 3170               /* KFLAG falsch */
#define AL_WROETYPI1 3190              /* falscher Elementtyp Z88I1.TXT */
#define AL_WROETYPNI 3200              /* falscher Elementtyp Z88NI.TXT */
#define AL_EXKOI 3210                  /* MAXKOI exhausted */
#define AL_WROIXI1 3220                /* Z88X.DXF: Z88I1.TXT  */
#define AL_WROIXNI 3230                /* Z88X.DXF: Z88NI.TXT  */
#define AL_WROIXKNO 3240               /* Z88X.DXF: Z88I1.TXT  */
#define AL_WROIXELE 3250               /* Z88X.DXF: Z88I1.TXT  */
#define AL_WROIXKOI 3260               /* Z88X.DXF: Z88I1.TXT  */
#define AL_WROIXI21Z 3280              /* Z88X.DXF: Z88I2.TXT 1.Zeile  */
#define AL_WROIXI2R 3290               /* Z88X.DXF: Z88I2.TXT Randbed.  */
#define AL_TOOFEW 3310                 /* zuwenig Knoten beim Scannen */
#define AL_NOPOINTS 3320               /* "P " fehlt */
#define AL_NOLAYNET 3330               /* kein Z88NET */
#define AL_WROIXI51Z 3340              /* Z88X.DXF: Z88I5.TXT 1.Zeile  */
#define AL_WROIXI5R 3350               /* Z88X.DXF: Z88I5.TXT Randbed.  */
#define AL_NOACROBAT 3360              /* kein Acrobat-Reader  */

/***********************************************************************
* Texte
***********************************************************************/
#define TX_REAI1 4000                  /* Z88I1.TXT einlesen */
#define TX_REAI2 4010                  /* Z88I2.TXT einlesen */
#define TX_REAI5 4025                  /* Z88I5.TXT einlesen */
#define TX_REANI 4030                  /* Z88NI.TXT einlesen */ 
#define TX_REAIX 4040                  /* Z88X.DXF einlesen */
#define TX_WRII1 4050                  /* Z88I1.TXT beschreiben */
#define TX_WRII2 4060                  /* Z88I2.TXT beschreiben */
#define TX_WRII5 4075                  /* Z88I5.TXT beschreiben */
#define TX_WRINI 4080                  /* Z88NI.TXT beschreiben */
#define TX_WRIOX 4090                  /* Z88X.DXF beschreiben */
#define TX_KOOR 4110                   /* Koordinaten einlesen */
#define TX_POLAR 4120                  /* Polarkoordinaten umr. */
#define TX_KOIN 4130                   /* Koinzidenz einlesen */
#define TX_SINFO 4150                  /* Super-Infos einlesen */
#define TX_Z88TX 4160                  /* Start Z88TX */
#define TX_KOIERF 4170                 /* KOI erfordert n */
#define TX_Z88FX 4180                  /* Start Z88FX */
#define TX_FX 4190                     /* Oeffnen Z88X.DXF */
#define TX_CFLAG 4200                  /* Anzeigen CFLAG */

#define TX_FAC 4210                    /* Faktoren in Z88TX rechnen*/
#define TX_SDXF 4220                   /* a. DXF Z88TX schreiben*/
#define TX_SELE 4230                   /* Elemente Z88TX schreiben*/
#define TX_EXITZ88TX 4240              /* Z88TX Ende*/
#define TX_EXITZ88FX 4250              /* Z88FX Ende*/
#define TX_DEC1ZI1 4270                /* Dekodieren 1.Z. Z88I1.TXT */
#define TX_DEC1ZNI 4280                /* Dekodieren 1.Z. Z88NI.TXT */
#define TX_DECKNO 4290                 /* Dekodieren Knoten */
#define TX_DECELE 4300                 /* Dekodieren Elemente */
#define TX_FOUKNO 4310                 /* x Knoten gefunden*/
#define TX_FOUFELE 4320                /* x Finite Elemente gefunden*/
#define TX_FOUSELE 4330                /* x Super- Elemente gefunden*/
#define TX_DEC1ZI2 4350                /* Dekodieren 1.Z. Z88I2.TXT */
#define TX_DECI2R 4360                 /* Dekodieren Randb. Z88I2.TXT */
#define TX_EXITZ88X 4380               /* Z88X Ende */
#define TX_ELE 4390                    /* Element */
#define TX_DEC1ZI5 4400                /* Dekodieren 1.Z. Z88I5.TXT */
#define TX_DECI5R 4410                 /* Dekodieren Randb. Z88I5.TXT */

/***********************************************************************
* Log- Eintraege
***********************************************************************/
#define LOG_BZ88X 5000                 /* Beginn Z88X */
#define LOG_CFLAGI1TX 5010             /* I1TX */
#define LOG_CFLAGIATX 5020             /* IATX */
#define LOG_CFLAGNITX 5030             /* NITX */
#define LOG_CFLAGI1FX 5040             /* I1FX */
#define LOG_CFLAGIAFX 5050             /* IAFX */
#define LOG_CFLAGNIFX 5060             /* NIFX */
#define LOG_OPENZ88DYN 5070            /* Oeffnen Z88.DYN */
#define LOG_NODYN 5080                 /* kann Z88.DYN nicht oeffnen */
#define LOG_WRONGDYN 5090              /* Z88.DYN nicht o.k. */
#define LOG_MAXKOI 5100                /* MAXKOI */
#define LOG_MAXK 5110                  /* MAXK */
#define LOG_MAXE 5120                  /* MAXE */
#define LOG_MAXNFG 5130                /* MAXNFG */
#define LOG_MAXPR 5145                 /* MAXPR */
#define LOG_OKDYN 5150                 /* Z88.DYN scheint o.k. zu sein */
#define LOG_ALLOCMEMY 5160             /* Memory anlegen */
#define LOG_ARRAYNOTOK 5170            /* Memory Kennung I nicht o.k. */
#define LOG_ARRAYOK 5180               /* Memory Kennung I angelegt */
#define LOG_SUMMEMY 5190               /* Memory angefordert */
#define LOG_EXITDYN88X 5200            /* Verlassen DYN88X */
#define LOG_BREA88 5210                /* Start REA88X */
#define LOG_FI1 5220                   /* Einlesen Z88I1.TXT */
#define LOG_FI2 5230                   /* Einlesen Z88I2.TXT */
#define LOG_FI5 5245                   /* Einlesen Z88I5.TXT */
#define LOG_FNI 5250                   /* Einlesen Z88NI.TXT */
#define LOG_NOI1 5260                  /* kein Z88I1.TXT */
#define LOG_NOI2 5270                  /* kein Z88I2.TXT */
#define LOG_NOI5 5285                  /* kein Z88I5.TXT */
#define LOG_NONI 5290                  /* kein Z88NI.TXT */
#define LOG_WRONGDIM 5300              /* ndim falsch */
#define LOG_EXMAXK 5310                /* MAXK ueberschritten */
#define LOG_EXMAXE 5320                /* MAXE ueberschritten */
#define LOG_EXMAXKOI 5330              /* MAXKOI ueberschritten */
#define LOG_EXMAXNFG 5340              /* MAXNFG ueberschritten */
#define LOG_EXMAXPR 5355               /* MAXPR ueberschritten */
#define LOG_WROKFLAG 5360              /* KFLAG falsch */
#define LOG_KOOR 5380                  /* Einlesen Koordinaten */
#define LOG_KOIN 5390                  /* Einlesen Koinzidenz */
#define LOG_WROETYP 5400               /* flascher Elementtyp */
#define LOG_SINFO 5420                 /* Einlesen Superele-Info */
#define LOG_EXITREA88 5430             /* Verlassen REA88X */
#define LOG_Z88TX 5440                 /* Start Z88TX */
#define LOG_FX 5450                    /* Oeffnen Z88X.DXF */
#define LOG_NOX 5460                   /* kein Z88X.DXF */
#define LOG_REAIX 5465                 /* Z88X.DXF einlesen */
#define LOG_WRIOX 5470                 /* Beschreiben Z88OX.DXF */
#define LOG_EXITZ88TX 5480             /* Verlassen Z88TX */
#define LOG_Z88FX 5490                 /* Start Z88FX */
#define LOG_BRDXF88 5500               /* Start RDXF88X */
#define LOG_WRII1 5510                 /* Beschreiben Z88I1.TXT */
#define LOG_WRII2 5520                 /* Beschreiben Z88I2.TXT */
#define LOG_WRII5 5535                 /* Beschreiben Z88I5.TXT */
#define LOG_WRINI 5540                 /* Beschreiben Z88NI.TXT */
#define LOG_EXITZ88FX 5550             /* Verlassen Z88FX */
#define LOG_FAC 5560                   /* Faktoren Z88TX rechnen */
#define LOG_SDXF 5570                  /* a. DXF Z88TX schreiben */ 
#define LOG_SELE 5580                  /* Elemente Z88TX schreiben */ 
#define LOG_EXITZ88X 5590              /* Ende Z88X */
#define LOG_DEC1ZI1 5600               /* Dekodieren 1.Z. Z88I1.TXT */
#define LOG_DEC1ZNI 5610               /* Dekodieren 1.Z. Z88NI.TXT */
#define LOG_DECKNO 5620                /* Dekodieren Knoten */
#define LOG_DECELE 5630                /* Dekodieren Elemente */
#define LOG_FOUKNO 5640                /* Knoten gefunden*/
#define LOG_FOUFELE 5650               /* x Finite Elemente gefunden*/
#define LOG_FOUSELE 5660               /* x Super- Elemente gefunden*/
#define LOG_WROIXI1 5680               /* Fehler Z88IX.DXF: 1.Z. Z88I1.TXT */
#define LOG_WROIXNI 5690               /* Fehler Z88IX.DXF: 1.Z. Z88NI.TXT */
#define LOG_WROIXKNO 5700              /* Fehler Z88IX.DXF: Knoten Z88I1.TXT */
#define LOG_WROIXELE 5710              /* Fehler Z88IX.DXF: Ele. Z88I1.TXT */
#define LOG_WROIXKOI 5720              /* Fehler Z88IX.DXF: Ele. Z88I1.TXT */
#define LOG_WROIXM 5730                /* Fehler Z88IX.DXF: Mat. Z88I1.TXT */
#define LOG_WROIXI21Z 5740             /* Fehler Z88IX.DXF: 1.Z. Z88I2.TXT */
#define LOG_WROIXI2R 5750              /* Fehler Z88IX.DXF: Randb. Z88I2.TXT */
#define LOG_DEC1ZI2 5770               /* Dekodieren 1.Z. Z88I2.TXT */
#define LOG_DECI2R 5780                /* Dekodieren Randb. Z88I2.TXT */
#define LOG_TOOFEW 5800                /* zuwenig Knoten beim Scannen */
#define LOG_NOPOINTS 5810              /* "P " fehlt */
#define LOG_NOLAYNET 5820              /* kein Z88NET */
#define LOG_WROIXI51Z 5830             /* Fehler Z88IX.DXF: 1.Z. Z88I5.TXT */
#define LOG_WROIXI5R 5840              /* Fehler Z88IX.DXF: Randb. Z88I5.TXT */
#define LOG_DEC1ZI5 5850               /* Dekodieren 1.Z. Z88I5.TXT */
#define LOG_DECI5R 5860                /* Dekodieren Randb. Z88I5.TXT */
#define LOG_NOACROBAT 5870             /* kein Acrobat-Reader  */



