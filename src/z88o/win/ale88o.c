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
* ale88o gibt Alert-Boxen aus (1 int)
* 3.8.2011 Rieg
***********************************************************************/ 
/***********************************************************************
* Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88o.h>
#include <windows.h>
#include <gl\gl.h>
#include <string.h>  /* strcpy */
#endif

/***********************************************************************
* Font- Structure GLFONT
***********************************************************************/
typedef struct
    {
    GLuint base;        /* DisplayList Nr.erstes Zeichen */
    int    widths[256]; /* Zeichenweite in Pixels */
    int    height;      /* Zeichenhoehe */
    } GLFONT;

/***********************************************************************
* Functions
***********************************************************************/
void	 FontPuts(GLFONT *font, const char *cs);

/***********************************************************************
* hier beginnt Function ale88o
***********************************************************************/
int ale88o(int ialert)
{
extern GLFONT    *Font;
extern FR_DOUBLE xm;
extern FR_INT4   LANG;

char             cmess[256];

switch(ialert)
  {
/*----------------------------------------------------------------------
* diese Fehler laufen alle ausserhalb der WM_PAINT-Loop
*---------------------------------------------------------------------*/
  case AL_NOMAN:
    if(LANG == 1) strcpy(cmess,"Kann Z88MAN.TXT nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88MAN.TXT !    STOP");
    MessageBox(NULL,cmess, "Z88O",MB_OK | MB_ICONHAND);
  break;

  case AL_WRONGMAN:
    if(LANG == 1) strcpy(cmess,"Z88MAN.TXT ist nicht korrekt !    STOP");
    if(LANG == 2) strcpy(cmess,"Z88MAN.TXT is invalid or wrong !    STOP");
    MessageBox(NULL,cmess, "Z88O",MB_OK | MB_ICONHAND);
  break;

  case AL_NOLOG:
    if(LANG == 1) strcpy(cmess,"Kann Z88O.LOG nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O.LOG !    STOP");
    MessageBox(NULL,cmess, "Z88O",MB_OK | MB_ICONHAND);
  break;

  case AL_NODYN:
    if(LANG == 1) strcpy(cmess,"Kann Z88.DYN nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88.DYN !    STOP");
    MessageBox(NULL,cmess, "Z88O",MB_OK | MB_ICONHAND);
  break;

  case AL_WRONGDYN:
    if(LANG == 1) strcpy(cmess,"Z88.DYN ist nicht korrekt !    STOP");
    if(LANG == 2) strcpy(cmess,"Z88.DYN is invalid or wrong !    STOP");
    MessageBox(NULL,cmess, "Z88O",MB_OK | MB_ICONHAND);
  break;

  case AL_NOOGL:
    if(LANG == 1) strcpy(cmess,"Kann Z88O.OGL nicht oeffnen !    STOP");
    if(LANG == 2) strcpy(cmess,"Cannot open Z88O.OGL !    STOP");
    MessageBox(NULL,cmess, "Z88O",MB_OK | MB_ICONHAND);
  break;

  case AL_WRONGOGL:
    if(LANG == 1) strcpy(cmess,"Z88O.OGL ist nicht korrekt !    STOP");
    if(LANG == 2) strcpy(cmess,"Z88O.OGL is invalid or wrong !    STOP");
    MessageBox(NULL,cmess, "Z88O",MB_OK | MB_ICONHAND);
  break;

  case AL_NOMEMY:
    if(LANG == 1) strcpy(cmess,"Nicht genug dynamischer Speicher !    STOP\
    Abhilfe: Eintraege in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Dynamic memory exhausted !    STOP\
    Recover: increase entries in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88O",MB_OK | MB_ICONHAND);
  break;

  case AL_NOSTRFI:
    if(LANG == 1) strcpy(cmess,"Strukturfile nicht gefunden !\
    Anderes Strukturfile mit > Datei > Strukturfile angeben.");
    if(LANG == 2) strcpy(cmess,"Structure file not found !\
    Enter a valid filename in section > File > Structure File.");
    MessageBox(NULL,cmess, "Z88O",MB_OK | MB_ICONQUESTION);
  break;  

  case AL_EXMAXK:
    if(LANG == 1) strcpy(cmess,"Speicher fuer Knoten ueberschritten !    STOP\
    Abhilfe: MAXK in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for nodes exhausted !    STOP\
    Recover: increase MAXK in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88O",MB_OK | MB_ICONHAND);
  break;

  case AL_EXMAXKOI:
    if(LANG == 1) strcpy(cmess,"Speicher fuer Koinzidenzvektor ueberschritten !    STOP\
    Abhilfe: MAXKOI in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for coincidence vector exhausted !    STOP\
    Recover: increase MAXKOI in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88O",MB_OK | MB_ICONHAND);
  break;

  case AL_EXMAXE:
    if(LANG == 1) strcpy(cmess,"Speicher fuer Elemente ueberschritten !\
    STOP    Abhilfe: MAXE in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for elements exhausted !    STOP\
    Recover: increase MAXE in Z88.DYN .");
    MessageBox(NULL,cmess, "Z88O",MB_OK | MB_ICONHAND);
  break;

  case AL_WRONGDIM:
    if(LANG == 1) strcpy(cmess,"Falsche Dimension im Structurfile !\
    STOP    Abhilfe: Im Strukturfile 2 oder 3 fuer Dimension waehlen.");
    if(LANG == 2) strcpy(cmess,"Wrong dimension in structur file !\
    STOP    Recover: enter 2 or 3 for dimension in structure file.");
    MessageBox(NULL,cmess, "Z88O",MB_OK | MB_ICONHAND);
  break;

  case AL_NOACROBAT:
    if(LANG == 1) strcpy(cmess,"Kann PDF-Viewer nicht oeffnen !");
    if(LANG == 2) strcpy(cmess,"Cannot open PDF Viewer !");
    MessageBox(NULL,cmess, "Z88O",MB_OK | MB_ICONHAND);
  break;

/*----------------------------------------------------------------------
* diese Fehler laufen alle in der WM_PAINT-Loop
*---------------------------------------------------------------------*/
  case AL_NOI2:
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f,0.0f,0.0f);
    glRasterPos3d(xm+4,-56.0,0.00);
    if(LANG == 1) strcpy(cmess,"Z88I2.TXT nicht gefunden! Daher keine Anzeige der Randbedingungen.");
    if(LANG == 2) strcpy(cmess,"Z88I2.TXT not found! Thus no view of boundary conditions.");
    FontPuts(Font,cmess);
  break;

  case AL_NOI5:
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f,0.0f,0.0f);
    glRasterPos3d(xm+4,-56.0,0.00);
    if(LANG == 1) strcpy(cmess,"Z88I5.TXT nicht gefunden! Daher keine Anzeige der Drucklasten.");
    if(LANG == 2) strcpy(cmess,"Z88I5.TXT not found! Thus no view for pressure loads.");
    FontPuts(Font,cmess);
  break;

  case AL_NOO2:
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f,0.0f,0.0f);
    glRasterPos3d(xm+4,-56.0,0.00);
    if(LANG == 1) strcpy(cmess,"Z88O2.TXT nicht gefunden! Zuerst Verformungsrechnung mit Solver.");
    if(LANG == 2) strcpy(cmess,"Z88O2.TXT not found! Start a solver run first.");
    FontPuts(Font,cmess);
  break;
    
  case AL_NOO8:
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f,0.0f,0.0f);
    glRasterPos3d(xm+4,-56.0,0.00);
    if(LANG == 1) strcpy(cmess,"Z88O8.TXT nicht gefunden! Zuerst Spannungsberechnung mit Z88D");
    if(LANG == 2) strcpy(cmess,"Z88O8.TXT not found! Start a stress computation with Z88D first.");
    FontPuts(Font,cmess);
  break;    

  case AL_NOO5:
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f,0.0f,0.0f);
    glRasterPos3d(xm+4,-56.0,0.00);
    if(LANG == 1) strcpy(cmess,"Z88O5.TXT nicht gefunden! Zuerst Spannungsberechnung mit Z88D.");
    if(LANG == 2) strcpy(cmess,"Z88O5.TXT not found! Start a stress computation with Z88D first.");
    FontPuts(Font,cmess);
  break;    

  case AL_EXMAXGP:
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f,0.0f,0.0f);
    glRasterPos3d(xm+4,-56.0,0.00);
    if(LANG == 1) strcpy(cmess,"zuviele Gausspunkte! Abhilfe: MAXGP in Z88.DYN erhoehen");
    if(LANG == 2) strcpy(cmess,"too many Gauss points! Recover: increase MAXGP in Z88.DYN");
    FontPuts(Font,cmess);
  break;

  case AL_NINT0:
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f,0.0f,0.0f);
    glRasterPos3d(xm+4,-56.0,0.00);
    if(LANG == 1) strcpy(cmess,"Integrationsordnung 0! Abhilfe: NINT > 0 in Z88INT.TXT, Z88R starten");
    if(LANG == 2) strcpy(cmess,"integration order 0! Recover: NINT > 0 in Z88INT.TXT, run Z88R again");
    FontPuts(Font,cmess);
  break;

  case AL_NONINT0:
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f,0.0f,0.0f);
    glRasterPos3d(xm+4,-56.0,0.00);
    if(LANG == 1) strcpy(cmess,"Integrationsordnung ist nicht Null! Neuer Lauf Z88R mit NINT=0 in Z88INT.TXT.");
    if(LANG == 2) strcpy(cmess,"Integration constant is not Zero! Run Z88R again, enter NINT=0 in Z88INT.TXT .");
    FontPuts(Font,cmess);
  break;

  case AL_EXMAXPR:
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f,0.0f,0.0f);
    glRasterPos3d(xm+4,-56.0,0.00);
    if(LANG == 1) strcpy(cmess,"Speicher fuer Drucklasten ueberschritten! Abhilfe: MAXPR in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for pressure loads exhausted! Recover: increase MAXPR in Z88.DYN .");
    FontPuts(Font,cmess);
  break;

  case AL_EXMAXRBD:
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    glColor3f(1.0f,0.0f,0.0f);
    glRasterPos3d(xm+4,-56.0,0.00);
    if(LANG == 1) strcpy(cmess,"Speicher fuer Randbedingungen ueberschritten! Abhilfe: MAXRBD in Z88.DYN erhoehen.");
    if(LANG == 2) strcpy(cmess,"Memory for boundary conditions exhausted! Recover: increase MAXRBD in Z88.DYN .");
    FontPuts(Font,cmess);
  break;
  }
return 0;
}  
