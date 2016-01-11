/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the UNIX OS.
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
*  function ale88x gibt Fehlermeldungen aus
*  30.7.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88x.h>
#include <stdio.h>    /* printf */
#endif

/***********************************************************************
*  hier beginnt Function ale88x
***********************************************************************/
int ale88x(int ialert)
{
extern FR_INT4 LANG;

switch(ialert)
  {
  case AL_NOCFLAG:
    if(LANG==1)
    {
    printf("### kein Steuerflag fuer Z88X angegeben ..Stop ###\n");
    printf("### Richtiger Aufruf:                          ###\n");
    printf("### z88x -i1tx (von Z88I1.TXT, nach Z88X.DXF)  ###\n");
    printf("### z88x -iatx (von Z88I*.TXT, nach Z88X.DXF)  ###\n");
    printf("### z88x -nitx (von Z88NI.TXT, nach Z88X.DXF)  ###\n");
    printf("### z88x -i1fx (von Z88X.DXF, nach Z88I1.TXT)  ###\n");
    printf("### z88x -iafx (von Z88X.DXF, nach Z88I*.TXT)  ###\n");
    printf("### z88x -nifx (von Z88X,DXF, nach Z88NI.TXT)  ###\n");
    }
    if(LANG==2)
    {
    printf("### no flags for Z88X found ..stop            ###\n");
    printf("### correct use:                              ###\n");
    printf("### z88x -i1tx (from Z88I1.TXT, to Z88X.DXF)  ###\n");
    printf("### z88x -iatx (from Z88I*.TXT, to Z88X.DXF)  ###\n");
    printf("### z88x -nitx (from Z88NI.TXT, to Z88X.DXF)  ###\n");
    printf("### z88x -i1fx (from Z88X.DXF, to Z88I1.TXT)  ###\n");
    printf("### z88x -iafx (from Z88X.DXF, to Z88I*.TXT)  ###\n");
    printf("### z88x -nifx (from Z88X,DXF, to Z88NI.TXT)  ###\n");
    }
  break;

  case AL_WROCFLAG:
    if(LANG==1)
    {
    printf("### Steuerflag fuer Z88X falsch ......... Stop ###\n");
    printf("### Richtiger Aufruf:                          ###\n");
    printf("### z88x -i1tx (von Z88I1.TXT, nach Z88X.DXF)  ###\n");
    printf("### z88x -iatx (von Z88I*.TXT, nach Z88X.DXF)  ###\n");
    printf("### z88x -nitx (von Z88NI.TXT, nach Z88X.DXF)  ###\n");
    printf("### z88x -i1fx (von Z88X.DXF, nach Z88I1.TXT)  ###\n");
    printf("### z88x -iafx (von Z88X.DXF, nach Z88I*.TXT)  ###\n");
    printf("### z88x -nifx (von Z88X,DXF, nach Z88NI.TXT)  ###\n");
    }
    if(LANG==2)
    {
    printf("### invalid flag for Z88X found ..stop        ###\n");
    printf("### correct use:                              ###\n");
    printf("### z88x -i1tx (from Z88I1.TXT, to Z88X.DXF)  ###\n");
    printf("### z88x -iatx (from Z88I*.TXT, to Z88X.DXF)  ###\n");
    printf("### z88x -nitx (from Z88NI.TXT, to Z88X.DXF)  ###\n");
    printf("### z88x -i1fx (from Z88X.DXF, to Z88I1.TXT)  ###\n");
    printf("### z88x -iafx (from Z88X.DXF, to Z88I*.TXT)  ###\n");
    printf("### z88x -nifx (from Z88X,DXF, to Z88NI.TXT)  ###\n");
    }
  break;

  case AL_NOLOG:
    if(LANG==1) printf("### kann Z88X.LOG nicht oeffnen ..Stop ###\n");
    if(LANG==2) printf("### cannot open Z88X.LOG ..stop ###\n");
  break;

  case AL_NODYN:
    if(LANG==1) printf("### kann Z88.DYN nicht oeffnen ..Stop ###\n");
    if(LANG==2) printf("### cannot open Z88.DYN ..stop ###\n");
  break;

  case AL_WRONGDYN:
    if(LANG==1) printf("### File Z88.DYN ist nicht korrekt ..Stop ###\n");
    if(LANG==2) printf("### file Z88.DYN is not okay ..stop ###\n");
  break;

  case AL_NOMEMY:
    if(LANG==1) printf("### nicht genuegend dynamisches Memory ..Stop ###\n");
    if(LANG==2) printf("### insufficient dynamic memory ..stop ###\n");
  break;

  case AL_NOI1:
    if(LANG==1) printf("### kann Z88I1.TXT nicht oeffnen ..Stop ###\n");
    if(LANG==2) printf("### cannot open Z88I1.TXT ..stop ###\n");
  break;

  case AL_NOI2:
    if(LANG==1) printf("### kann Z88I2.TXT nicht oeffnen ..Stop ###\n");
    if(LANG==2) printf("### cannot open Z88I2.TXT ..stop ###\n");
  break;

  case AL_NOI5:
    if(LANG==1) printf("### kann Z88I5.TXT nicht oeffnen ..Stop ###\n");
    if(LANG==2) printf("### cannot open Z88I5.TXT ..stop ###\n");
  break;

  case AL_NONI:
    if(LANG==1) printf("### kann Z88NI.TXT nicht oeffnen ..Stop ###\n");
    if(LANG==2) printf("### cannot open Z88NI.TXT ..stop ###\n");
  break;

  case AL_NOX:
    if(LANG==1) printf("### kann Z88X.DXF nicht oeffnen ..Stop ###\n");
    if(LANG==2) printf("### cannot open Z88X.DXF ..stop ###\n");
  break;

  case AL_WROIXI1:
    if(LANG==1)
    {
    printf("### Z88X.DXF fuer Z88I1.TXT falsch:              ###\n");
    printf("### erste Eingabegruppe fehlt oder falsch ..Stop ###\n");
    }
    if(LANG==2)
    {
    printf("### Z88X.DXF for Z88I1.TXT wrong:             ###\n");
    printf("### first input group missing or wrong ..stop ###\n");
    }
  break;

  case AL_WROIXNI:
    if(LANG==1)
    {
    printf("### Z88X.DXF fuer Z88NI.TXT falsch:              ###\n");
    printf("### erste Eingabegruppe fehlt oder falsch ..Stop ###\n");
    }
    if(LANG==2)
    {
    printf("### Z88X.DXF for Z88NI.TXT wrong:             ###\n");
    printf("### first input group missing or wrong ..stop ###\n");
    }
  break;

  case AL_WROIXKNO:
    if(LANG==1)
    {
    printf("### Z88X.DXF fuer Z88I1.TXT/Z88NI.TXT falsch:   ###\n");
    printf("### Gefundene Anzahl Knoten stimmt nicht ..Stop ###\n");
    }
    if(LANG==2)
    {
    printf("### Z88X.DXF for Z88I1.TXT/Z88NI.TXT wrong:           ###\n");
    printf("### detected number of nodes sounds impossible ..stop ###\n");
    }
  break;

  case AL_WROIXELE:
    if(LANG==1)
    {
    printf("### Z88X.DXF fuer Z88I1.TXT/Z88NI.TXT falsch:     ###\n");
    printf("### Gefundene Anzahl Elemente stimmt nicht ..Stop ###\n");
    }
    if(LANG==2)
    {
    printf("### Z88X.DXF for Z88I1.TXT/Z88NI.TXT wrong:              ###\n");
    printf("### detected number of elements sounds impossible ..stop ###\n");
    }
  break;

  case AL_WROIXKOI:
    if(LANG==1)
    {
    printf("### Z88X.DXF fuer Z88I1.TXT/Z88NI.TXT falsch: ###\n");
    printf("### identische Knoten in Element(en) ..Stop   ###\n");
    }
    if(LANG==2)
    {
    printf("### Z88X.DXF for Z88I1.TXT/Z88NI.TXT wrong: ###\n");
    printf("### identical nodes in element(s) ..stop    ###\n");
    }
  break;

  case AL_WROIXI21Z:
    if(LANG==1)
    {
    printf("### Z88X.DXF fuer Z88I2.TXT falsch:                  ###\n");
    printf("### Anzahl Randbedingungen fehlen oder falsch ..Stop ###\n");
    }
    if(LANG==2)
    {
    printf("### Z88X.DXF for Z88I2.TXT wrong:                 ###\n");
    printf("### number of constraints missing or wrong ..stop ###\n");
    }
  break;

  case AL_WROIXI2R:
    if(LANG==1)
    {
    printf("### Z88X.DXF fuer Z88I2.TXT falsch:             ###\n");
    printf("### Falsche oder zuwenig Randbedingungen ..Stop ###\n");
    }
    if(LANG==2)
    {
    printf("### Z88X.DXF for Z88I2.TXT wrong:           ###\n");
    printf("### incorrect or too few constraints ..stop ###\n");
    }
  break;

  case AL_WROIXI51Z:
    if(LANG==1)
    {
    printf("### Z88X.DXF fuer Z88I5.TXT falsch:                 ###\n");
    printf("### Anzahl Flaechenlasten fehlen oder falsch ..Stop ###\n");
    }
    if(LANG==2)
    {
    printf("### Z88X.DXF for Z88I5.TXT wrong:                   ###\n");
    printf("### number of surface loads missing or wrong ..stop ###\n");
    }
  break;

  case AL_WROIXI5R:
    if(LANG==1)
    {
    printf("### Z88X.DXF fuer Z88I5.TXT falsch:            ###\n");
    printf("### Falsche oder zuwenig Flaechenlasten ..Stop ###\n");
    }
    if(LANG==2)
    {
    printf("### Z88X.DXF for Z88I5.TXT wrong:             ###\n");
    printf("### incorrect or too few surface loads ..stop ###\n");
    }
  break;

  case AL_WRONDIM:
    if(LANG==1) printf("### Dimension falsch ..Stop ###\n");
    if(LANG==2) printf("### dimension wrong ..stop ###\n");
  break;

  case AL_EXMAXK:
    if(LANG==1)
    {
    printf("### Zuviele Knoten ..zuwenig Speicher ..Stop ###\n");
    printf("### Abhilfe: MAXK in Z88.DYN erhoehen        ###\n");
    }
    if(LANG==2)
    {
    printf("### too many nodes ..memory exhausted ..stop ###\n");
    printf("### recover: increase MAXK in Z88.DYN        ###\n");
    }
  break;

  case AL_EXMAXE:
    if(LANG==1)
    {
    printf("### Zuviele Elemente ..zuwenig Speicher ..Stop ###\n");
    printf("### Abhilfe: MAXE in Z88.DYN erhoehen          ###\n");
    }
    if(LANG==2)
    {
    printf("### too many elements ..memory exhausted ..stop ###\n");
    printf("### recover: increase MAXE in Z88.DYN           ###\n");
    }
  break;

  case AL_EXMAXNFG:
    if(LANG==1)
    {
    printf("### Zuviele Freiheitsgrade ..zuwenig Speicher ..Stop ###\n");
    printf("### Abhilfe: MAXNFG in Z88.DYN erhoehen              ###\n");
    }
    if(LANG==2)
    {
    printf("### too many DOF ..memory exhausted ..stop ###\n");
    printf("### recover: increase MAXNFG in Z88.DYN    ###\n");
    }
  break;

  case AL_EXMAXPR:
    if(LANG==1)
    {
    printf("### Zuviele Flaechenlasten ..zuwenig Speicher ..Stop ###\n");
    printf("### Abhilfe: MAXPR in Z88.DYN erhoehen               ###\n");
    }
    if(LANG==2)
    {
    printf("### too many surface loads ..memory exhausted ..stop ###\n");
    printf("### recover: increase MAXPR in Z88.DYN               ###\n");
    }
  break;

  case AL_WROKFLAG:
    if(LANG==1) printf("### Koordinatenflag KFLAG falsch ..Stop ###\n");
    if(LANG==2) printf("### coordinate flag KFLAG wrong ..stop ###\n");
  break;

  case AL_WROETYPI1:
    if(LANG==1) printf("### Unbekannter Elementtyp in Z88I1.TXT ..Stop ###\n");
    if(LANG==2) printf("### unknown element type in Z88I1.TXT ..stop ###\n");
  break;

  case AL_WROETYPNI:
    if(LANG==1) printf("### Unbekannter Elementtyp in Z88NI.TXT ..Stop ###\n");
    if(LANG==2) printf("### unknown element type in Z88NI.TXT ..stop ###\n");
  break;

  case AL_EXKOI:
    if(LANG==1)
    {
    printf("### Struktur zu gross fuer Z88X ..zuwenig Speicher ..Stop ###\n");
    printf("### Abhilfe: Hilfsvariable MAXKOI in Z88.DYN erhoehen     ###\n");
    }
    if(LANG==2)
    {
    printf("### structure too large for Z88X ..memory exhausted ..stop ###\n");
    printf("### recover: increase aux. variable MAXKOI in Z88.DYN      ###\n");
    }
    break;

  case AL_TOOFEW:
    if(LANG==1)
    {
    printf("### Z88X.DXF von CAD falsch:                            ###\n");
    printf("### Zuwenig oder falsche Linien auf Layer Z88NET ..Stop ###\n");
    }
    if(LANG==2)
    {
    printf("### Z88X.DXF from CAD wrong:                      ###\n");
    printf("### Too few or wrong lines on layer Z88NET ..stop ###\n");
    }
  break;

  case AL_NOPOINTS:
    if(LANG==1)
    {
    printf("### Z88X.DXF von CAD falsch:                         ###\n");
    printf("### Knoten nicht richtig definiert (P Nummer) ..Stop ###\n");
    }
    if(LANG==2)
    {
    printf("### Z88X.DXF from CAD wrong:                     ###\n");
    printf("### Nodes not properly defined (P number) ..stop ###\n");
    }
  break;

  case AL_NOLAYNET:
    if(LANG==1)
    {
    printf("### Z88X.DXF von CAD falsch:                           ###\n");
    printf("### Keine oder zuwenig Objekte auf Layer Z88NET ..Stop ###\n");
    }
    if(LANG==2)
    {
    printf("### Z88X.DXF from CAD wrong:                     ###\n");
    printf("### No or too few objects on layer Z88NET ..stop ###\n");
    }
  break;

  case AL_NOACROBAT:
    if(LANG==1) printf("### kann PDF-Viewer nicht oeffnen ..Stop ###\n");
    if(LANG==2) printf("### cannot open PDF-Viewer ..stop ###\n");
  break;

  }
return(0);
}

