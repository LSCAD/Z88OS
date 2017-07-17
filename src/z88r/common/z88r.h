/***********************************************************************
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
* V15.0 November 18, 2015
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
* z88r.h fuer UNIX und Windows
* 3.8.2011 Rieg
***********************************************************************/

/***********************************************************************
* Datentypen fuer Windows und UNIX
***********************************************************************/
#ifdef FR_XINT
#define FR_INT4AY int *                /* Pointer auf int         */
#define FR_INT4 int                    /* int                     */
#define FR_CALLOC calloc               /* calloc                  */
#define FR_SIZERW size_t               /* Size fuer fread, fwrite */
#endif

#ifdef FR_XLONG
#define FR_INT4AY long *               /* Pointer auf long        */
#define FR_INT4 long                   /* long                    */
#define FR_CALLOC calloc               /* calloc                  */
#define FR_SIZERW size_t               /* Size fuer fread, fwrite */
#endif

#ifdef FR_XLOLO
#define FR_INT4AY long long *          /* Pointer auf long        */
#define FR_INT4 long long              /* long                    */
#define FR_CALLOC calloc               /* calloc                  */
#define FR_SIZERW size_t               /* Size fuer fread, fwrite */
#endif

#ifdef FR_XDOUB
#define FR_SQRT sqrt                   /* sqrt                    */
#define FR_POW pow                     /* pow                     */
#define FR_FABS fabs                   /* fabs                    */
#define FR_SIN sin                     /* sin                     */
#define FR_COS cos                     /* cos                     */
#define FR_ACOS acos                   /* acos                    */
#define FR_ATAN atan                   /* atan                    */
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
* Daten
***********************************************************************/
#define ICO_Z88R                      10
#define CUR_Z88R                      20
#define BMP_Z88R                      30

/***********************************************************************
* Menue-IDs
***********************************************************************/
#define IDM_WER                        100
#define IDM_XIT                        110
#define IDM_LINA                       120
#define IDM_TEST                       130
#define IDM_CHOLY                      140
#define IDM_SRSIC                      150
#define IDM_SRSOR                      160
#define IDM_GO                         170

/***********************************************************************
* Toolbar-IDs
***********************************************************************/
#define ITC_HELP                       200
#define ITC_XIT                        210
#define ITC_LINA                       220
#define ITC_TEST                       230
#define ITC_CHOLY                      240
#define ITC_SRSIC                      250
#define ITC_SRSOR                      260
#define ITC_GO                         270

/***********************************************************************
* Alerts
***********************************************************************/
#define AL_NOLOG 3000                  /* kein Z88R.LOG */ 
#define AL_NODYN 3010                  /* kein Z88.DYN */
#define AL_WRONGDYN 3020               /* Fehler in Z88.DYN */
#define AL_NOMEMY 3030                 /* nicht genug Memory */
#define AL_NOI1 3040                   /* Fehler Oeffnen z88i1.txt */
#define AL_NOI2 3050                   /* Fehler Oeffnen z88i2.txt */
#define AL_NOI5 3060                   /* Fehler Oeffnen z88i5.txt */
#define AL_NOO0 3070                   /* Fehler Oeffnen z88o0.txt */
#define AL_NOO1 3160                   /* Fehler Oeffnen z88o1.txt */
#define AL_NOO2 3170                   /* Fehler Oeffnen z88o2.txt */
#define AL_NOO3 3180                   /* Fehler Oeffnen z88o3.txt */
#define AL_NOO4 3190                   /* Fehler Oeffnen z88o4.txt */
#define AL_NOO5 3200                   /* Fehler Oeffnen z88o5.txt */
#define AL_NOO8 3210                   /* Fehler Oeffnen z88o8.txt */
#define AL_NOMAN 3220                  /* kein Z88MAN.TXT */
#define AL_WRONGMAN 3230               /* falsche Z88MANAGE.TXT */
#define AL_NOMAT 3240                  /* keine Z88MAT.TXT da */
#define AL_NOELP 3250                  /* keine Z88ELP.TXT da */
#define AL_NOINT 3260                  /* keine Z88INT.TXT da */
#define AL_NOMATCSV 3270               /* .CSV-File nicht gefunden */
#define AL_WRONDIM 3280                /* NDIM falsch */
#define AL_EXMAXK 3290                 /* zuviele Knoten */
#define AL_EXMAXE 3300                 /* zuviele Elemente */
#define AL_EXMAXKOI 3310               /* Koinzidenzvektor zu klein */
#define AL_EXMAXNFG 3320               /* zuviele Freiheitsgrade */
#define AL_EXMAXMAT 3330               /* zuviele Materialgesetze */
#define AL_EXMAXINT 3340               /* zuviele Integrationsgesetze */
#define AL_EXMAXPEL 3350               /* zuviele Elementparameter */
#define AL_EXMAXPR 3360                /* NOI zu klein */
#define AL_WROKFLAG 3370               /* KFLAG falsch */
#define AL_WROETYP 3380                /* falscher Elementtyp */
#define AL_EXGS 3390                   /* MAXGS exhausted */
#define AL_EXKOI 3400                  /* MAXKOI exhausted */
#define AL_EXMAXIEZ 3410               /* MAXIEZ exhausted */
#define AL_JACNEG 3420                 /* Jacobi-Determinate null/negativ */
#define AL_JACLOA 3430                 /* Jacobi-Determinate null/negativ */
#define AL_DIAGNULL 3440               /* Diagonalele null/negativ */
#define AL_WROCFLAG 3450               /* Steuerflag Z88R falsch */
#define AL_NOCFLAG 3460                /* kein Steuerflag Z88R */
#define AL_NOCI 3470                   /* Probleme bei NH und SG */
#define AL_NOACROBAT 3480              /* kein PDF-Viewer */

/***********************************************************************
* Texte
***********************************************************************/
#define TX_REAI1 4000                  /* Z88I1.TXT einlesen */
#define TX_REAI2 4010                  /* Z88I2.TXT einlesen */
#define TX_REAMAT 4020                 /* Z88MAT.TXT einlesen */
#define TX_REAMAN 4030                 /* Z88MAN.TXT einlesen */
#define TX_REAELP 4040                 /* Z88ELP.TXT einlesen */
#define TX_REAINT 4050                 /* Z88INT.TXT einlesen */
#define TX_REAI5 4060                  /* Z88I5.TXT einlesen */
#define TX_REAI2P2 4070                /* Z88I2.TXT zum 2.mal einlesen */
#define TX_WRIO0 4090                  /* Z88O0.TXT beschreiben */
#define TX_WRIO1 4100                  /* Z88O1.TXT beschreiben */
#define TX_WRIO2 4110                  /* Z88O2.TXT beschreiben */
#define TX_ELE 4120                    /* Element I */
#define TX_KOOR 4130                   /* Koordinaten einlesen */
#define TX_POLAR 4140                  /* Polarkoordinaten umr. */
#define TX_KOIN 4150                   /* Koinzidenz einlesen */
#define TX_Z88A 4160                   /* Start Z88A */
#define TX_Z88AI 4170                  /* Start Z88AI */
#define TX_EXITZ88A 4180               /* Ende Z88A */
#define TX_EXITZ88AI 4190              /* Ende Z88AI */
#define TX_GSERF 4200                  /* GS erfordert n */
#define TX_KOIERF 4210                 /* KOI erfordert n */
#define TX_GSSO 4220                   /* Pointer assembliert */
#define TX_Z88B 4230                   /* Start Z88BR */
#define TX_SUMMEMY 4240                /* Summe angeforderter Speicher */
#define TX_COMPI 4250                  /* Compilieren */
#define TX_Z88CC 4260                  /* Start Z88CR */
#define TX_ERBPA 4270                  /* Einarbeiten RB */
#define TX_SCAL88 4280                 /* Start SCAL88 */
#define TX_CHOY88 4290                 /* CHOY88 starten */
#define TX_SICCG88 4300                /* Start SICCG88 */
#define TX_SORCG88 4310                /* Start SORCG88 */
#define TX_NFG 4320                    /* Anzahl nfg */
#define TX_CHOJ 4330                   /* J = */
#define TX_JACOOK 4340                 /* Epsilon erreicht */
#define TX_JACONOTOK 4350              /* Epsilon nicht erreicht */
#define TX_ITERA 4360                  /* n-te Iteration */
#define TX_PART88 4370                 /* n-te partielle Cholesky-Z. */
#define TX_CR 4380                     /* neue Zeile */
#define TX_DYNMEMY 4390                /* Zusatzspeicher Z88AI */
#define TX_SPANNU 4400                 /* Spannungen */
#define TX_EXITZ88D 4410               /* Ende Z88DR */
#define TX_KNOTENK 4420                /* Knotenkraefte */
#define TX_EXITZ88E 4430               /* Ende Z88ER */
#define TX_VORW 4440                   /* Vorwaertseinsetzen */
#define TX_RUECKW 4450                 /* Vorwaertseinsetzen */
#define TX_IFNILI0 4460                /* ifnili = 0 : lineare Ber. */
#define TX_IFNILI9 4470                /* ifnili = 9 : Testmode */
#define TX_ICFLAG0 4480                /* ICFLAG = 0 : Cholesky */
#define TX_ICFLAG1 4490                /* ICFLAG = 1 : SICCG */
#define TX_ICFLAG2 4500                /* ICFLAG = 2 : SORCG */
#define TX_MEMORY 4510                 /* Hauptspeicher fuer Solver */
#define TX_EGES 4520                   /* Einlesen E-Gesetze */
#define TX_NONZ 4530                   /* Elemente in IJ entdeckt */
#define TX_FORMA 4540                  /* Formatieren */


/***********************************************************************
* LOGs
***********************************************************************/
#define LOG_OPENZ88DYN 5000            /* Oeffnen Z88.DYN */
#define LOG_NODYN 5010                 /* kann Z88.DYN nicht oeffnen */
#define LOG_WRONGDYN 5020              /* Z88.DYN nicht o.k. */
#define LOG_MAXIEZ 5030                /* MAXIEZ */
#define LOG_MAXGS 5040                 /* MAXGS */
#define LOG_MAXKOI 5050                /* MAXKOI */
#define LOG_MAXK 5060                  /* MAXK */
#define LOG_MAXE 5070                  /* MAXE */
#define LOG_MAXNFG 5080                /* MAXNFG */
#define LOG_MAXMAT 5090                /* MAXMAT */
#define LOG_MAXPEL 5100                /* MAXPEL */
#define LOG_MAXINT 5110                /* MAXINT */
#define LOG_MAXESM 5120                /* MAXESM */
#define LOG_MAXPR 5130                 /* MAXPR fuer NOI */
#define LOG_OKDYN 5140                 /* Z88.DYN scheint o.k. zu sein */
#define LOG_ALLOCMEMY 5150             /* Memory anlegen */
#define LOG_ARRAYNOTOK 5160            /* Memory Kennung I nicht o.k. */
#define LOG_ARRAYOK 5170               /* Memory Kennung I angelegt */
#define LOG_SUMMEMY 5180               /* Memory angefordert */
#define LOG_BRI188 5190                /* Start RI188R */
#define LOG_NOI1 5200                  /* kein Z88I1.TXT */
#define LOG_WRONGDIM 5210              /* ndim falsch */
#define LOG_EXMAXK 5220                /* MAXK ueberschritten */
#define LOG_EXMAXE 5230                /* MAXE ueberschritten */
#define LOG_EXMAXKOI 5240              /* Koinzidenzvektor zu klein */
#define LOG_EXMAXNFG 5250              /* MAXNFG ueberschritten */
#define LOG_EXMAXPR 5260               /* MAXPR ueberschritten */
#define LOG_WROKFLAG 5270              /* KFLAG falsch */
#define LOG_KOOR 5280                  /* Einlesen Koordinaten */
#define LOG_KOIN 5290                  /* Einlesen Koinzidenz */
#define LOG_EXITRI188 5300             /* Verlassen RI188R */
#define LOG_EXITRI588 5310             /* Verlassen RI588I */
#define LOG_BWRIA88F 5320              /* Start WRIA88R */
#define LOG_GSERF 5330                 /* GS erforderlich */
#define LOG_KOIERF 5340                /* KOI erforderlich */
#define LOG_EXITWRIA88F 5350           /* Verlassen WRIA88R */
#define LOG_Z88A 5360                  /* Start Z88A */
#define LOG_Z88AI 5370                 /* Start Z88AI */
#define LOG_WROETYP 5380               /* falscher Elementtyp */
#define LOG_EXITZ88A 5390              /* Verlassen Z88A */
#define LOG_EXITZ88AI 5400             /* Verlassen Z88AI */
#define LOG_Z88B 5410                  /* Start Z88BR */
#define LOG_EXGS 5420                  /* MAXGS ueberschritten */
#define LOG_EXKOI 5430                 /* MAXKOI ueberschritten */
#define LOG_EXMAXIEZ 5440              /* MAXIEZ ueberschritten */
#define LOG_COMPI 5450                 /* Compilation */
#define LOG_EXITZ88B 5460              /* Verlassen Z88BR */
#define LOG_Z88CC 5470                 /* Start Z88CR */
#define LOG_NOI2 5480                  /* kein Z88I2.TXT */
#define LOG_NOI5 5490                  /* kein Z88I5.TXT */
#define LOG_BRI588 5500                /* Start RI588I */
#define LOG_NOO1 5510                  /* kein Z88O1.TXT */
#define LOG_NOO2 5520                  /* kein Z88O2.TXT */
#define LOG_REAI2 5530                 /* Einlesen Z88I2.TXT */
#define LOG_WRIO1 5540                 /* Beschreiben Z88O1.TXT */
#define LOG_ERBPA 5550                 /* Einarbeiten RB */
#define LOG_SCAL88 5560                /* Start SCAL88 */
#define LOG_CHOY88 5570                /* Start CHOY88 */
#define LOG_SICCG88 5580               /* Start SICCG88 */
#define LOG_SORCG88 5590               /* Start SORCG88 */
#define LOG_WRIO2 5600                 /* Beschreiben Z88O2.TXT */
#define LOG_EXITZ88CC 5610             /* Verlassen Z88CC */
#define LOG_VORW 5620                  /* Vorwaertseinsetzen */
#define LOG_RUECKW 5630                /* Rueckwaertseinsetzen */
#define LOG_DIAGNULL 5640              /* Diagonalelement <= 0 */
#define LOG_JACNEG 5650                /* Jacobi- Determinate <= 0 */
#define LOG_JACLOA 5660                /* Jacobi- Determinate <= 0 */
#define LOG_CFLAG0 5670                /* ICFLAG = 0: Cholesky */
#define LOG_CFLAG1 5680                /* ICFLAG = 1: SICCG */
#define LOG_CFLAG2 5690                /* ICFLAG = 2: SORCG */
#define LOG_MAXIT 5700                 /* max. Anzahl von Iterationen */
#define LOG_CFLAGS 5710                /* gewaehlter Mode */

#define LOG_ITERA 5720                 /* Anzahl Iterationen */
#define LOG_NOO3 5730                  /* kein Z88O3.TXT */
#define LOG_NOO4 5740                  /* kein Z88O4.TXT */
#define LOG_NOO5 5750                  /* kein Z88O5.TXT */
#define LOG_NOO8 5760                  /* kein Z88O8.TXT */
#define LOG_SPANNU 5770                /* Spannungen */
#define LOG_NOCI 5780                  /* Probleme bei NH und SG */
#define LOG_EXITZ88D 5790              /* Ende Z88DR */
#define LOG_KNOTENK 5800               /* Knotenkraefte */
#define LOG_EXITZ88E 5810              /* Ende Z88ER */
#define LOG_EXITDYN88J 5820            /* Ende DYN88R */
#define LOG_NOO0 5830                  /* Z88O0.TXT */
#define LOG_WRIO0 5840                 /* Fehler bei Z88O0.TXT */
#define LOG_BZ88D 5850                 /* Start Z88DR */
#define LOG_BZ88E 5860                 /* Start Z88ER */
#define LOG_MEMORY 5870                /* Hauptspeicher fuer Solver */
#define LOG_NOMAN 5880                 /* kein Z88MAN.TXT */
#define LOG_WRONGMAN 5890              /* falsche Z88MAN.TXT */
#define LOG_NOMAT 5900                 /* keine Z88MAT.TXT da */
#define LOG_NOELP 5910                 /* keine Z88ELP.TXT da */
#define LOG_NOINT 5920                 /* keine Z88INT.TXT da */
#define LOG_NOMATCSV 5930              /* .CSV-File nicht gefunden */
#define LOG_BZ88R 5940                 /* Start Z88R */
#define LOG_NOACROBAT 5950             /* kein PDF-Viewer */


