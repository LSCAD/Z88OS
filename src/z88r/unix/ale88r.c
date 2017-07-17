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
*  function ale88r gibt Fehlermeldungen aus
*  24.5.2012 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>    /* printf */
#endif

/***********************************************************************
*  hier beginnt Function ale88r
***********************************************************************/
int ale88r(int ialert)
{
extern FR_INT4 LANG;

switch(ialert)
  {
  case AL_NOCFLAG:
    if(LANG == 1)
    {
    printf("### keine oder zuwenig Steuerflags fuer Z88R angegeben ..Stop  ###\n");
    printf("### Richtiger Aufruf:  z88r -c -2.Flag (lineare Berechnung)    ###\n");
    printf("###                    z88r -t -2.Flag (Testmode)              ###\n");
    printf("###                    z88r 1.Flag -choly (Cholesky-Solver)    ###\n");
    printf("###                    z88r 1.Flag -siccg (SICCG-Solver)       ###\n");
    printf("###                    z88r 1.Flag -sorcg (SORCG-Solver)       ###\n");
    }
    if(LANG == 2)
    {
    printf("### no or too few flags given for z88r ..stop           ###\n");
    printf("### correct use: z88r -c 2nd flag (linear calculation)  ###\n");
    printf("###              z88r -t 2nd flag (test mode)           ###\n");
    printf("###              z88r 1st flag -choly (Cholesky solver) ###\n");
    printf("###              z88r 1st flag -siccg (SICCG solver)    ###\n");
    printf("###              z88r 1st flag -sorcg (SORCG solver)    ###\n");
    }
  break;

  case AL_WROCFLAG:
    if(LANG == 1)
    {
    printf("### Steuerflags falsch fuer z88r angegeben ..Stop              ###\n");
    printf("### Richtiger Aufruf:  z88r -c -2.Flag (lineare Berechnung)    ###\n");
    printf("###                    z88r -t -2.Flag (Testmode)              ###\n");
    printf("###                    z88r 1.Flag -choly (Cholesky-Solver)    ###\n");
    printf("###                    z88r 1.Flag -siccg (SICCG-Solver)       ###\n");
    printf("###                    z88r 1.Flag -sorcg (SORCG-Solver)       ###\n");
    }
    if(LANG == 2)
    {
    printf("### wrong flags given for z88r ..stop                   ###\n");
    printf("### correct use: z88r -c 2nd flag (linear calculation)  ###\n");
    printf("###              z88r -t 2nd flag (test mode)           ###\n");
    printf("###              z88r 1st flag -choly (Cholesky solver) ###\n");
    printf("###              z88r 1st flag -siccg (SICCG solver)    ###\n");
    printf("###              z88r 1st flag -sorcg (SORCG solver)    ###\n");
    }
  break;

  case AL_NOLOG:
    if(LANG == 1) printf("### kann Z88R.LOG nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88R.LOG ..stop ###\n");
  break;

  case AL_NODYN:
    if(LANG == 1) printf("### kann Z88.DYN nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88.DYN ..stop ###\n");
  break;

  case AL_WRONGDYN:
    if(LANG == 1) printf("### File Z88.DYN ist nicht korrekt ..Stop ###\n");
    if(LANG == 2) printf("### file Z88.DYN is not correct ..stop ###\n");
  break;

  case AL_NOMEMY:
    if(LANG == 1)printf("### nicht genuegend dynamisches Memory ..Stop ###\n");
    if(LANG == 2)printf("### insufficient dynamic memory ..Stop ###\n");
  break;

  case AL_NOI1:
    if(LANG == 1) printf("### kann Z88I1.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88I1.TXT ..stop ###\n");
  break;

  case AL_NOI2:
    if(LANG == 1) printf("### kann Z88I2.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88I2.TXT ..stop ###\n");
  break;

  case AL_NOINT:
    if(LANG == 1) printf("### kann Z88INT.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88INT.TXT ..stop ###\n");
  break;

  case AL_NOELP:
    if(LANG == 1) printf("### kann Z88ELP.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88ELP.TXT ..stop ###\n");
  break;

  case AL_NOMAT:
    if(LANG == 1) printf("### kann Z88MAT.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88MAT.TXT ..stop ###\n");
  break;

  case AL_NOMATCSV:
    if(LANG == 1) printf("### kann Materialdatei *.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open material file *.TXT ..stop ###\n");
  break;

  case AL_NOMAN:
    if(LANG == 1) printf("### kann Z88MAN.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88MAN.TXT ..stop ###\n");
  break;

  case AL_WRONGMAN:
    if(LANG == 1) printf("### Z88MAN.TXT ist nicht korrekt ..Stop ###\n");
    if(LANG == 2) printf("### Z88MAN.TXT is invalid or wrong..stop ###\n");
  break;

  case AL_NOI5:
    if(LANG == 1) printf("### kann Z88I5.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88I5.TXT ..stop ###\n");
  break;

  case AL_NOO0:
    if(LANG == 1) printf("### kann Z88O0.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88O0.TXT ..stop ###\n");
  break;

  case AL_NOO1:
    if(LANG == 1) printf("### kann Z88O1.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88O1.TXT ..stop ###\n");
  break;

  case AL_NOO2:
    if(LANG == 1) printf("### kann Z88O2.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88O2.TXT ..stop ###\n");
  break;

  case AL_NOO3:
    if(LANG == 1) printf("### kann Z88O3.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88O3.TXT ..stop ###\n");
  break;

  case AL_NOO4:
    if(LANG == 1) printf("### kann Z88O4.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88O4.TXT ..stop ###\n");
  break;

  case AL_NOO5:
    if(LANG == 1) printf("### kann Z88O5.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88O5.TXT ..stop ###\n");
  break;

  case AL_NOO8:
    if(LANG == 1) printf("### kann Z88O8.TXT nicht oeffnen ..Stop ###\n");
    if(LANG == 2) printf("### cannot open Z88O8.TXT ..stop ###\n");
  break;

  case AL_WRONDIM:
    if(LANG == 1) printf("### Dimension falsch ..Stop ###\n");
    if(LANG == 2) printf("### wrong dimension ..stop ###\n");
  break;

  case AL_EXMAXK:
    if(LANG == 1)
    {
    printf("### Zuviele Knoten ..zuwenig Speicher ..Stop ###\n");
    printf("### Abhilfe: MAXK in Z88.DYN erhoehen        ###\n");
    }
    if(LANG == 2)
    {
    printf("### too many nodes ..insufficient memory ..stop ###\n");
    printf("### recover: increase MAXK in Z88.DYN           ###\n");
    }
  break;

  case AL_EXMAXE:
    if(LANG == 1)
    {
    printf("### Zuviele Elemente ..zuwenig Speicher ..Stop ###\n");
    printf("### Abhilfe: MAXE in Z88.DYN erhoehen          ###\n");
    }
    if(LANG == 2)
    {
    printf("### too many elements ..insufficient memory ..stop ###\n");
    printf("### recover: increase MAXE in Z88.DYN              ###\n");
    }
  break;

  case AL_EXMAXKOI:
    if(LANG == 1)
    {
    printf("### Koinzidenzvektor KOI laeuft ueber ..Stop ###\n");
    printf("### Abhilfe: MAXKOI in Z88.DYN erhoehen      ###\n");
    }
    if(LANG == 2)
    {
    printf("### koincidence vector KOI exhausted ..stop ###\n");
    printf("### recover: increase MAXKOI in Z88.DYN     ###\n");
    }
  break;

  case AL_EXMAXNFG:
    if(LANG == 1)
    {
    printf("### Zuviele Freiheitsgrade ..zuwenig Speicher ..Stop ###\n");
    printf("### Abhilfe: MAXNFG in Z88.DYN erhoehen              ###\n");
    }
    if(LANG == 2)
    {
    printf("### too many DOF ..insufficient memory ..stop ###\n");
    printf("### recover: increase MAXNFG in Z88.DYN       ###\n");
    }
  break;

  case AL_EXMAXMAT:
    if(LANG == 1)
    {
    printf("### Zuviele Materialgesetze ..zuwenig Speicher ..Stop ###\n");
    printf("### Abhilfe: MAXMAT in Z88.DYN erhoehen               ###\n");
    }
    if(LANG == 2)
    {
    printf("### too many mat lines ..insufficient memory ..stop ###\n");
    printf("### recover: increase MAXMAT in Z88.DYN             ###\n");
    }
  break;

  case AL_EXMAXINT:
    if(LANG == 1)
    {
    printf("### Zuviele Integrationsordnungen ..zuwenig Speicher ..Stop ###\n");
    printf("### Abhilfe: MAXJNT in Z88.DYN erhoehen                     ###\n");
    }
    if(LANG == 2)
    {
    printf("### too many integration lines ..insufficient memory ..stop ###\n");
    printf("### recover: increase MAXJNT in Z88.DYN                     ###\n");
    }
  break;

  case AL_EXMAXPEL:
    if(LANG == 1)
    {
    printf("### Zuviele Elementparameter ..zuwenig Speicher ..Stop ###\n");
    printf("### Abhilfe: MAXPEL in Z88.DYN erhoehen                ###\n");
    }
    if(LANG == 2)
    {
    printf("### too many element parameters ..insufficient memory ..stop ###\n");
    printf("### recover: increase MAXPEL in Z88.DYN                      ###\n");
    }
  break;

  case AL_EXMAXPR:
    if(LANG == 1)
    {
    printf("### Zuviele Lastvektoren ..zuwenig Speicher ..Stop ###\n");
    printf("### Abhilfe: MAXPR in Z88.DYN erhoehen             ###\n");
    }
    if(LANG == 2)
    {
    printf("### too many load vectors ..insufficient memory ..stop ###\n");
    printf("### recover: increase MAXPR in Z88.DYN                 ###\n");
    }
  break;

  case AL_WROKFLAG:
    if(LANG == 1) printf("### KFLAG falsch ..Stop ###\n");
    if(LANG == 2) printf("### KFLAG wrong ..stop ###\n");
  break;

  case AL_WROETYP:
    if(LANG == 1) printf("### Unbekannter Elementtyp in Z88I1.TXT ..Stop ###\n");
    if(LANG == 2) printf("### unknown element type in Z88I1.TXT ..stop ###\n");
  break;

  case AL_EXGS:
    if(LANG == 1)
    {
    printf("### Gleichungssystem zu gross ..zuwenig Speicher ..Stop ###\n");
    printf("### Abhilfe: MAXGS hoeher setzen in Z88.DYN             ###\n");
    }
    if(LANG == 2)
    {
    printf("### system of equations too large ..insufficient memory ..stop ###\n");
    printf("### recover: increase MAXGS in Z88.DYN                         ###\n");
    }
  break;

  case AL_EXKOI:
    if(LANG == 1)
    {
    printf("### Gleichungssystem zu gross ..zuwenig Speicher ..Stop ###\n");
    printf("### Abhilfe: MAXKOI hoeher setzen in Z88.DYN            ###\n");
    }
    if(LANG == 2)
    {
    printf("### system of equations too large ..insufficient memory ..stop ###\n");
    printf("### recover: increase MAXKOI in Z88.DYN                        ###\n");
    }
  break;

  case AL_EXMAXIEZ:
    if(LANG == 1)
    {
    printf("\n### Pointer IEZ hat zuwenig Speicher ..Stop   ###\n");
    printf("### Abhilfe: MAXIEZ hoeher setzen in Z88.DYN  ###\n");
    }
    if(LANG == 2)
    {
    printf("\n### Pointer IEZ has insufficient memory ..stop ###\n");
    printf("### recover: increase MAXIEZ in Z88.DYN        ###\n");
    }
  break;

  case AL_JACNEG:
    if(LANG == 1)
    {
    printf("\n### Jacobi-Determinante Null oder negativ..Stop  ###\n");
    printf("### Elemente zu verzerrt oder falsch numeriert   ###\n");
    printf("### pruefen, Numerierung gegen Uhrzeigersinn?    ###\n");
    }
    if(LANG == 2)
    {
    printf("\n### Jacobi-determinant zero or negative..stop    ###\n");
    printf("### elements to distorted or wrong numbered      ###\n");
    printf("### recover: check numbering (anti-clockwise)    ###\n");
    }
  break;

  case AL_JACLOA:
    if(LANG == 1)
    {
    printf("\n### Jacobi-Determinante Null oder negativ..Stop  ###\n");
    printf("### Lastvektoren falsch in Z88I5.TXT             ###\n");
    printf("### Stimmt die Numerierung der Flaeche? Handbuch ###\n");
    }
    if(LANG == 2)
    {
    printf("\n### Jacobi-determinant zero or negative..stop  ###\n");
    printf("### load vectors wrong in file Z88I5.TXT       ###\n");
    printf("### numering correct? See manual               ###\n");
    }
  break;

  case AL_DIAGNULL:
    if(LANG == 1)
    {
    printf("\n### Diagonalelement im G-System Null oder negativ..Stop  ###\n");
    printf("### liegt oft an fehlenden oder falschen Randbedingungen ###\n");
    printf("### Randbedingungen checken (statisch unterbestimmt ?)   ###\n");
    }
    if(LANG == 2)
    {
    printf("\n### diagonal element in array zero or negative..stop ###\n");
    printf("### often caused by missing or wrong constraints     ###\n");
    printf("### recover: check constraints (underdefined ?)      ###\n");
    }
  break;

  case AL_NOCI:
    if(LANG == 1) printf("### konnte nicht alle GEH/NH/SH-V-Spannungen berechnen ###\n");
    if(LANG == 2) printf("### could not compute all Mises/principal/Tresca stresses ###\n");
  break;
  }
return(0);
}

