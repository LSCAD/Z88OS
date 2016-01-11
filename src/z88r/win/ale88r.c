/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows OS.
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
*  function ale88r gibt Fehlermeldungen aus
*  24.5.2012 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <windows.h>  
#endif

/***********************************************************************
*  hier beginnt Function ale88r
***********************************************************************/
int ale88r(int ialert)
{
extern FR_INT4 LANG;

char cmess[256];

switch(ialert)
  {
  case AL_NOLOG:
    if(LANG == 1) strcpy(cmess,"Kann Z88R.LOG nicht oeffnen !   STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88R.LOG !    STOP");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_NOACROBAT:
    if(LANG == 1) strcpy(cmess,"Kann PDF-Viewer nicht oeffnen !");
    if(LANG == 2) strcpy(cmess,"Cannot open PDF Viewer !");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_NODYN:
    if(LANG == 1) strcpy(cmess,"Kann Z88.DYN nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88.DYN !    STOP");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_WRONGDYN:
    if(LANG == 1) strcpy(cmess,"Z88.DYN ist nicht korrekt !    STOP");
    if(LANG == 2) strcpy(cmess,"Z88.DYN is invalid or wrong !    STOP");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_NOMEMY:
    if(LANG == 1) strcpy(cmess,"Nicht genug dynamischer Speicher !    STOP\
    Abhilfe: Eintraege in Z88.DYN erhoehen");
    if(LANG == 2) strcpy(cmess,"Dynamic memory exhausted !    STOP\
    Recover: increase entries in Z88.DYN");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_NOI1:
    if(LANG == 1) strcpy(cmess,"Kann Z88I1.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88I1.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_NOI2:
    if(LANG == 1) strcpy(cmess,"Kann Z88I2.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88I2.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_NOMAN:
    if(LANG == 1) strcpy(cmess,"Kann Z88MAN.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88MAN.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_WRONGMAN:
    if(LANG == 1) strcpy(cmess,"Z88MAN.TXT ist nicht korrekt !    STOP");
    if(LANG == 2) strcpy(cmess,"Z88MAN.TXT is invalid or wrong !    STOP");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_NOMAT:
    if(LANG == 1) strcpy(cmess,"Kann Z88MAT.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88MAT.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_NOMATCSV:
    if(LANG == 1) strcpy(cmess,"Kann Materialdatei *.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open material file *.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_NOINT:
    if(LANG == 1) strcpy(cmess,"Kann Z88INT.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88INT.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_NOELP:
    if(LANG == 1) strcpy(cmess,"Kann Z88ELP.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88ELP.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_NOI5:
    if(LANG == 1) strcpy(cmess,"Kann Z88I5.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88I5.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_NOO0:
    if(LANG == 1) strcpy(cmess,"Kann Z88O0.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O0.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_NOO1:
    if(LANG == 1) strcpy(cmess,"Kann Z88O1.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O1.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_NOO2:
    if(LANG == 1) strcpy(cmess,"Kann Z88O2.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O2.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_NOO3:
    if(LANG == 1) strcpy(cmess,"Kann Z88O3.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O3.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_NOO4:
    if(LANG == 1) strcpy(cmess,"Kann Z88O4.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O4.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_NOO5:
    if(LANG == 1) strcpy(cmess,"Kann Z88O5.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O5.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_NOO8:
    if(LANG == 1) strcpy(cmess,"Kann Z88O8.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O8.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_WRONDIM:
    if(LANG == 1) strcpy(cmess,"Falsche Dimension im Structurfile !    STOP\
    Abhilfe: Im Strukturfile 2 oder 3 fuer Dimension waehlen.");
    if(LANG == 2) strcpy(cmess,"Wrong dimension in structure file !    STOP\
    Recover: enter 2 or 3 for dimension in structure file.");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_EXMAXK:
    if(LANG == 1) strcpy(cmess,"Speicher fuer Knoten ueberschritten !    STOP\
    Abhilfe: MAXK in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for nodes exhausted !    STOP\
    Recover: increase MAXK in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_EXMAXE:
    if(LANG == 1) strcpy(cmess,"Speicher fuer Elemente ueberschritten !\
    STOP    Abhilfe: MAXE in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for elements exhausted !    STOP\
    Recover: increase MAXE in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_EXMAXNFG:
    if(LANG == 1) strcpy(cmess,"Speicher fuer Freiheitsgrade ueberschritten !\
    STOP    Abhilfe: MAXNFG in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for degrees of freedom exhausted !\
    STOP    Recover: increase MAXNFG in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_EXMAXMAT:
    if(LANG == 1) strcpy(cmess,"Speicher fuer Materialgesetze ueberschritten !\
    STOP    Abhilfe: MAXMAT in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for material groups exhausted !\
    STOP    Recover: increase MAXMAT in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_EXMAXINT:
    if(LANG == 1) strcpy(cmess,"Speicher fuer Integrationsordnungen ueberschritten !\
    STOP    Abhilfe: MAXJNT in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for integration order groups exhausted !\
    STOP    Recover: increase MAXJNT in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_EXMAXPEL:
    if(LANG == 1) strcpy(cmess,"Speicher fuer Elementparameter ueberschritten !\
    STOP    Abhilfe: MAXPEL in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for element parameter groups exhausted !\
    STOP    Recover: increase MAXPEL in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_EXMAXPR:
    if(LANG == 1) strcpy(cmess,"Speicher fuer Lastvektoren ueberschritten !\
    STOP    Abhilfe: MAXPR in Z88.DYN erhoehen .");
    if(LANG == 2) strcpy(cmess,"Memory for load vectors exhausted !\
    STOP    Recover: increase MAXPR in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_WROKFLAG:
    if(LANG == 1) strcpy(cmess,"Koordinatenflag KFLAG falsch !\
    STOP    Abhilfe: KFLAG in 1. Zeile Z88I1.TXT zu 0 oder 1 setzen.");
    if(LANG == 2) strcpy(cmess,"Coordinate flag KFLAG wrong !\
    STOP    Recover: enter 0 or 1 for KFLAG in first line Z88I1.TXT .");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_WROETYP:
    if(LANG == 1) strcpy(cmess,"Unbekannter Elementtyp in Z88I1.TXT !\
    STOP    Abhilfe: Elementtypen von 1 bis 24 zulassen.");
    if(LANG == 2) strcpy(cmess,"Unknown element type in Z88I1.TXT !\
    STOP    Recover: enter element types from 1 to 24.");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_EXGS:
    if(LANG == 1) strcpy(cmess,"Zuwenig Memory fuer Gesamtsteifigkeitsmatrix !\
    STOP    Abhilfe: MAXGS in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for stiffness matrix exhausted !\
    STOP    Recover: increase MAXGS in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88I2",MB_OK | MB_ICONHAND);
  break;

  case AL_EXKOI:
    if(LANG == 1) strcpy(cmess,"Zuwenig Memory fuer Koinzidenzvektor !\
    STOP    Abhilfe: MAXKOI in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for coincidence vector exhausted !\
    STOP    Recover: increase MAXKOI in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_EXMAXIEZ:
    if(LANG == 1) strcpy(cmess,"Pointer IEZ hat zuwenig Speicher !\
    STOP    Abhilfe: MAXIEZ in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Pointer IEZ has insufficient memory !\
    STOP    Recover: increase MAXIEZ in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_JACNEG:
    if(LANG == 1) strcpy(cmess,"Jacobi-Determinante Null oder negativ !\
    STOP    Elementnumerierung falsch, nicht mathematisch positiv\
    oder Elemente total verzerrt\
    Abhilfe: Siehe Online Hilfe oder Handbuch zum Elementtyp");
    if(LANG == 2) strcpy(cmess,"Jacobi determinant zero or negative !\
    STOP    element numbering wrong, not counter-clockwise\
    or totally distorted\
    Recover: renumber or correct wrong elements (consult manual)");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_JACLOA:
    if(LANG == 1) strcpy(cmess,"Jacobi-Determinante Null oder negativ !\
    STOP    Lastvektor falsch (Stimmt die Numerierung?)\
    Abhilfe: Siehe Online Hilfe oder Handbuch zum Elementtyp");
    if(LANG == 2) strcpy(cmess,"Jacobi determinant zero or negative !\
    STOP    Load vector wrong (Numering wrong?)\
    Recover: consult manual");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;

  case AL_DIAGNULL:
    if(LANG == 1) strcpy(cmess,"Diagonalelement im Gleichungssystem Null\
 oder negativ !    STOP    Liegt oft an fehlenden oder falschen Rand\
bedingungen.    Abhilfe: Randbedingungen checken (statisch unterbestimmt ?).");
    if(LANG == 2) strcpy(cmess,"diagonal element in array zero or negative !\
    STOP    Often caused by missing or wrong constraints\
    Recover: check constraints (underdefined ?).");
    MessageBox(NULL,cmess, "Z88R",MB_OK | MB_ICONHAND);
  break;
  }
return(0);
}

