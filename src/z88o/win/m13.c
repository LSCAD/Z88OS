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
* Compilerunit m13.c fuer Z88O enthaelt:
* fsca88  -  Farbskala Spannungen und Verschiebungen
* malk88  -  Knotennummern malen
* tet588  -  Wireframe 
* fsrb88  -  Farbskala Randbedingungen
* 31.7.2011 Rieg
***********************************************************************/ 
/***********************************************************************
* Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88o.h>
#include <windows.h>
#include <commctrl.h>
#include <gl\gl.h>
#include <stdio.h>  
#endif

/***********************************************************************
* Leseformate
***********************************************************************/
#ifdef FR_XINT
#define PDB "%d "
#define PD "%d"
#endif

#ifdef FR_XLONG
#define PDB "%ld "
#define PD "%ld"
#endif

#ifdef FR_XLOLO
#define PDB "%lld "
#define PD "%lld"
#endif

#ifdef FR_XDOUB
#define PG "%+#10.2lE"
#endif

#ifdef FR_XQUAD
#define PG "%Lg"
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
GLFONT * FontCreate(HDC hdc,const char *typeface,
                    int height,int weight,DWORD italic);
void	 FontPuts(GLFONT *font, const char *cs);
void     FontDelete(GLFONT *font);

/***********************************************************************
* fsca88 zeichnet die Farbskala fuer die Spannungen und Verschiebungen
***********************************************************************/
int fsca88(void)
{
extern GLFONT      *Font;

extern FR_DOUBLE   xm;

extern GLfloat     rot[];
extern GLfloat     gruen[];
extern GLfloat     blau[];

extern FR_DOUBLE   fspa[];

extern FR_INT4     LANG,igpanz,isflag;

extern int         if3d;

char               cstring[80];

/*----------------------------------------------------------------------
* fsca88 zeichnet die Farbskala fuer die Spannungen und Verschiebungen
*---------------------------------------------------------------------*/
glColor3f(rot[1],gruen[1],blau[1]);
glRectd(xm+4,48.0,xm+12,40.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,44.0,0.00);
sprintf(cstring,PG " ~ " PG,fspa[1],fspa[2]);
FontPuts(Font,cstring);	

glColor3f(rot[2],gruen[2],blau[2]);
glRectd(xm+4,40.0,xm+12,32.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,36.0,0.00);
sprintf(cstring,PG " ~ " PG,fspa[2],fspa[3]);
FontPuts(Font,cstring);	

glColor3f(rot[3],gruen[3],blau[3]);
glRectd(xm+4,32.0,xm+12,24.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,28.0,0.00);
sprintf(cstring,PG " ~ " PG,fspa[3],fspa[4]);
FontPuts(Font,cstring);	

glColor3f(rot[4],gruen[4],blau[4]);
glRectd(xm+4,24.0,xm+12,16.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,20.0,0.00);
sprintf(cstring,PG " ~ " PG,fspa[4],fspa[5]);
FontPuts(Font,cstring);	

glColor3f(rot[5],gruen[5],blau[5]);
glRectd(xm+4,16.0,xm+12,8.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,12.0,0.00);
sprintf(cstring,PG " ~ " PG,fspa[5],fspa[6]);
FontPuts(Font,cstring);	

glColor3f(rot[6],gruen[6],blau[6]);
glRectd(xm+4,8.0,xm+12,0.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,4.0,0.00);
sprintf(cstring,PG " ~ " PG,fspa[6],fspa[7]);
FontPuts(Font,cstring);	

glColor3f(rot[7],gruen[7],blau[7]);
glRectd(xm+4,0.0,xm+12,-8.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,-4.0,0.00);
sprintf(cstring,PG " ~ " PG,fspa[7],fspa[8]);
FontPuts(Font,cstring);	

glColor3f(rot[8],gruen[8],blau[8]);
glRectd(xm+4,-8.0,xm+12,-16.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,-12.0,0.00);
sprintf(cstring,PG " ~ " PG,fspa[8],fspa[9]);
FontPuts(Font,cstring);	

glColor3f(rot[9],gruen[9],blau[9]);
glRectd(xm+4,-16.0,xm+12,-24.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,-20.0,0.00);
sprintf(cstring,PG " ~ " PG,fspa[9],fspa[10]);
FontPuts(Font,cstring);	

glColor3f(rot[10],gruen[10],blau[10]);
glRectd(xm+4,-24.0,xm+12,-32.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,-28.0,0.00);
sprintf(cstring,PG " ~ " PG,fspa[10],fspa[11]);
FontPuts(Font,cstring);	

glColor3f(rot[11],gruen[11],blau[11]);
glRectd(xm+4,-32.0,xm+12,-40.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,-36.0,0.00);
sprintf(cstring,PG " ~ " PG,fspa[11],fspa[12]);
FontPuts(Font,cstring);	

if(if3d == IDM_SHOWSPANN || if3d == IDM_SHOWGAUSS || if3d == IDM_SHOWGAUPU)
  {
  glColor3f(1.0f,0.5f,0.0f);
  glRasterPos3d(xm+4,-44.0,0.00);
  if(LANG == 1 && isflag == 0)strcpy(cstring,"keine V-Spannungen");
  if(LANG == 2 && isflag == 0)strcpy(cstring,"no reduced Stresses");
  if(LANG == 1 && isflag == 1)strcpy(cstring,"V-Spannungen (GEH)");
  if(LANG == 2 && isflag == 1)strcpy(cstring,"v.Mises Stresses");
  if(LANG == 1 && isflag == 2)strcpy(cstring,"V-Spannungen (NH)");
  if(LANG == 2 && isflag == 2)strcpy(cstring,"principal Stresses");
  if(LANG == 1 && isflag == 3)strcpy(cstring,"V-Spannungen (SH)");
  if(LANG == 2 && isflag == 3)strcpy(cstring,"Tresca Stresses");
  FontPuts(Font,cstring);	
  }

if(if3d == IDM_SHOWSPANN && isflag > 0)
  {
  glRasterPos3d(xm+4,-48.0,0.00);
  if(LANG == 1)strcpy(cstring,"in den Eckknoten");
  if(LANG == 2)strcpy(cstring,"in corner nodes");
  FontPuts(Font,cstring);	
  }

if(if3d == IDM_SHOWGAUSS  && isflag > 0)
  {
  glRasterPos3d(xm+4,-48.0,0.00);
  if(LANG == 1)strcpy(cstring,"pro Element gemittelt");
  if(LANG == 2)strcpy(cstring,"mean value per element");
  FontPuts(Font,cstring);		
  }

if(if3d == IDM_SHOWGAUPU  && isflag > 0)
  {
  glRasterPos3d(xm+4,-48.0,0.00);
  if(LANG == 1)sprintf(cstring,"in " PD " Gausspunkten",igpanz);
  if(LANG == 2)sprintf(cstring,"in " PD " Gauss points",igpanz);
  FontPuts(Font,cstring);		
  }

if(if3d == IDM_SHOWVX)
  {
  glColor3f(1.0f,0.5f,0.0f);
  glRasterPos3d(xm+4,-44.0,0.00);
  if(LANG == 1)strcpy(cstring,"X-Verschiebungen");
  if(LANG == 2)strcpy(cstring,"X Displacements");
  FontPuts(Font,cstring);	
  }

if(if3d == IDM_SHOWVY)
  {
  glColor3f(1.0f,0.5f,0.0f);
  glRasterPos3d(xm+4,-44.0,0.00);
  if(LANG == 1)strcpy(cstring,"Y-Verschiebungen");
  if(LANG == 2)strcpy(cstring,"Y Displacements");
  FontPuts(Font,cstring);	
  }

if(if3d == IDM_SHOWVZ)
  {
  glColor3f(1.0f,0.5f,0.0f);
  glRasterPos3d(xm+4,-44.0,0.00);
  if(LANG == 1)strcpy(cstring,"Z-Verschiebungen");
  if(LANG == 2)strcpy(cstring,"Z Displacements");
  FontPuts(Font,cstring);	
  }

return 0;
}

/***********************************************************************
* malk88 zeichnet die Knotennummern
***********************************************************************/
int malk88(void)
{
extern GLFONT      *Font;

extern FR_DOUBLEAY xv;
extern FR_DOUBLEAY yv;
extern FR_DOUBLEAY zv;

extern FR_INT4     jkvon,jkbis,nkp,LANG;

extern GLfloat     node_col[];

FR_INT4            i,ipuf;

char               cstring[80];

/*----------------------------------------------------------------------
* und los
*---------------------------------------------------------------------*/
glColor3f(node_col[0],node_col[1],node_col[2]);

if(jkvon <=  0 || jkbis <=  0) return 0;

if(jkvon > nkp) jkvon= nkp;
if(jkbis > nkp) jkbis= nkp;

if(jkbis < jkvon)
  {
  ipuf=  jkbis;
  jkbis= jkvon;
  jkvon= ipuf;
  } 

for(i= jkvon; i <= jkbis;i++)
  { 
  glRasterPos3d(xv[i],yv[i],zv[i]);
  ltoa(i,cstring,10);
  FontPuts(Font,cstring);
  }	

return 0;
}

/***********************************************************************
* hier beginnt Function tet588: reines FE Netz
***********************************************************************/
int tet588(void)
{
extern GLFONT      *Font;

extern FR_DOUBLEAY xv;
extern FR_DOUBLEAY yv;
extern FR_DOUBLEAY zv;

extern FR_INT4AY   ityp;
extern FR_INT4AY   koi;
extern FR_INT4AY   koffs;

extern FR_INT4     ne,jevon,jebis;

extern GLfloat     elem_col[],hide_col[];

FR_DOUBLE          xla,yla,zla;

FR_INT4            i,j,k,iflag;

extern int         iflabe;

FR_INT4            ipuf;

char               cstring[80];

/***********************************************************************
* jevon und jebis checken
***********************************************************************/
if(jevon > ne) jevon= ne;
if(jebis > ne) jebis= ne;

if(jebis < jevon)
  {
  ipuf=  jebis;
  jebis= jevon;
  jevon= ipuf;
  } 

/***********************************************************************
* Schleife ueber alle Elemente
***********************************************************************/
for (i= 1; i <= ne; i++)
  {
  glColor3f(hide_col[0],hide_col[1],hide_col[2]);
  iflag= 0;
  if(iflabe == IDM_ELEMENTE || iflabe == IDM_LALLES)
    if(i >= jevon && i <= jebis) iflag= 1;

/*----------------------------------------------------------------------
* Stab 4 u. 9, Balken 2 und 13, Welle 5
*---------------------------------------------------------------------*/
  if(ityp[i] == 4 || ityp[i] == 9  || 
     ityp[i] == 2 || ityp[i] == 13 ||
     ityp[i] == 5)
    {       
    if(iflag)
      {
      glColor3f(elem_col[0],elem_col[1],elem_col[2]);
      xla= (xv[koi[koffs[i]]]+xv[koi[koffs[i]+1]])*0.5;
      yla= (yv[koi[koffs[i]]]+yv[koi[koffs[i]+1]])*0.5;
      zla= (zv[koi[koffs[i]]]+zv[koi[koffs[i]+1]])*0.5;
      glRasterPos3d(xla,yla,zla);
      ltoa(i,cstring,10);
      FontPuts(Font,cstring);
      }

    glBegin(GL_LINES);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
      glVertex3d(xv[koi[koffs[i]+1]],yv[koi[koffs[i]+1]],zv[koi[koffs[i]+1]]);
    glEnd();

    }  /* Stab 4 u. 9, Balken 2 und 13, Welle 5 */


/*----------------------------------------------------------------------
* Scheibe 7, Torus 8 u. Platte 20 u. Schale 23
*---------------------------------------------------------------------*/
  if(ityp[i] == 7  || ityp[i] == 8 || ityp[i] == 20 || ityp[i] == 23)
    {       
    if(iflag)
      {
      glColor3f(elem_col[0],elem_col[1],elem_col[2]);
      xla= (xv[koi[koffs[i]]]+xv[koi[koffs[i]+2]])*0.5;
      yla= (yv[koi[koffs[i]]]+yv[koi[koffs[i]+2]])*0.5;
      zla= (zv[koi[koffs[i]]]+zv[koi[koffs[i]+2]])*0.5;
      glRasterPos3d(xla,yla,zla);
      ltoa(i,cstring,10);
      FontPuts(Font,cstring);
      }

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
      glVertex3d(xv[koi[koffs[i]+4]],yv[koi[koffs[i]+4]],zv[koi[koffs[i]+4]]);
      glVertex3d(xv[koi[koffs[i]+1]],yv[koi[koffs[i]+1]],zv[koi[koffs[i]+1]]);
      glVertex3d(xv[koi[koffs[i]+5]],yv[koi[koffs[i]+5]],zv[koi[koffs[i]+5]]);
      glVertex3d(xv[koi[koffs[i]+2]],yv[koi[koffs[i]+2]],zv[koi[koffs[i]+2]]);
      glVertex3d(xv[koi[koffs[i]+6]],yv[koi[koffs[i]+6]],zv[koi[koffs[i]+6]]);
      glVertex3d(xv[koi[koffs[i]+3]],yv[koi[koffs[i]+3]],zv[koi[koffs[i]+3]]);
      glVertex3d(xv[koi[koffs[i]+7]],yv[koi[koffs[i]+7]],zv[koi[koffs[i]+7]]);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
    glEnd();

    }  /* Scheibe 7, Torus 8 und Platte 20 und Schale 23 */

/*----------------------------------------------------------------------
* Scheibe 11 und Torus 12
*---------------------------------------------------------------------*/
  if(ityp[i] == 11  || ityp[i] == 12)
    {       
    if(iflag)
      {
      glColor3f(elem_col[0],elem_col[1],elem_col[2]);
      xla= (xv[koi[koffs[i]]]+xv[koi[koffs[i]+2]])*0.5;
      yla= (yv[koi[koffs[i]]]+yv[koi[koffs[i]+2]])*0.5;
      zla= (zv[koi[koffs[i]]]+zv[koi[koffs[i]+2]])*0.5;
      glRasterPos3d(xla,yla,zla);
      ltoa(i,cstring,10);
      FontPuts(Font,cstring);
      }

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]   ]],yv[koi[koffs[i]   ]],zv[koi[koffs[i]   ]]);
      glVertex3d(xv[koi[koffs[i]+ 4]],yv[koi[koffs[i]+ 4]],zv[koi[koffs[i]+ 4]]);
      glVertex3d(xv[koi[koffs[i]+ 5]],yv[koi[koffs[i]+ 5]],zv[koi[koffs[i]+ 5]]);
      glVertex3d(xv[koi[koffs[i]+ 1]],yv[koi[koffs[i]+ 1]],zv[koi[koffs[i]+ 1]]);
      glVertex3d(xv[koi[koffs[i]+ 6]],yv[koi[koffs[i]+ 6]],zv[koi[koffs[i]+ 6]]);
      glVertex3d(xv[koi[koffs[i]+ 7]],yv[koi[koffs[i]+ 7]],zv[koi[koffs[i]+ 7]]);
      glVertex3d(xv[koi[koffs[i]+ 2]],yv[koi[koffs[i]+ 2]],zv[koi[koffs[i]+ 2]]);
      glVertex3d(xv[koi[koffs[i]+ 8]],yv[koi[koffs[i]+ 8]],zv[koi[koffs[i]+ 8]]);
      glVertex3d(xv[koi[koffs[i]+ 9]],yv[koi[koffs[i]+ 9]],zv[koi[koffs[i]+ 9]]);
      glVertex3d(xv[koi[koffs[i]+ 3]],yv[koi[koffs[i]+ 3]],zv[koi[koffs[i]+ 3]]);
      glVertex3d(xv[koi[koffs[i]+10]],yv[koi[koffs[i]+10]],zv[koi[koffs[i]+10]]);
      glVertex3d(xv[koi[koffs[i]+11]],yv[koi[koffs[i]+11]],zv[koi[koffs[i]+11]]);
      glVertex3d(xv[koi[koffs[i]   ]],yv[koi[koffs[i]   ]],zv[koi[koffs[i]   ]]);
    glEnd();

    }  /* Scheibe 11 und Torus 12 */

/*----------------------------------------------------------------------
* Volumenschalenele.21
*---------------------------------------------------------------------*/
  if(ityp[i] == 21)
    {       
    if(iflag)
      {
      glColor3f(elem_col[0],elem_col[1],elem_col[2]);
      xla= (xv[koi[koffs[i]]]+xv[koi[koffs[i]+2]])*0.5;
      yla= (yv[koi[koffs[i]]]+yv[koi[koffs[i]+2]])*0.5;
      zla= (zv[koi[koffs[i]]]+zv[koi[koffs[i]+2]])*0.5;
      glRasterPos3d(xla,yla,zla);
      ltoa(i,cstring,10);
      FontPuts(Font,cstring);
      }

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]   ]],yv[koi[koffs[i]   ]],zv[koi[koffs[i]   ]]);
      glVertex3d(xv[koi[koffs[i]+ 4]],yv[koi[koffs[i]+ 4]],zv[koi[koffs[i]+ 4]]);
      glVertex3d(xv[koi[koffs[i]+ 1]],yv[koi[koffs[i]+ 1]],zv[koi[koffs[i]+ 1]]);
      glVertex3d(xv[koi[koffs[i]+ 5]],yv[koi[koffs[i]+ 5]],zv[koi[koffs[i]+ 5]]);
      glVertex3d(xv[koi[koffs[i]+ 2]],yv[koi[koffs[i]+ 2]],zv[koi[koffs[i]+ 2]]);
      glVertex3d(xv[koi[koffs[i]+ 6]],yv[koi[koffs[i]+ 6]],zv[koi[koffs[i]+ 6]]);
      glVertex3d(xv[koi[koffs[i]+ 3]],yv[koi[koffs[i]+ 3]],zv[koi[koffs[i]+ 3]]);
      glVertex3d(xv[koi[koffs[i]+ 7]],yv[koi[koffs[i]+ 7]],zv[koi[koffs[i]+ 7]]);
      glVertex3d(xv[koi[koffs[i]   ]],yv[koi[koffs[i]   ]],zv[koi[koffs[i]   ]]);
    glEnd();

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]+ 8]],yv[koi[koffs[i]+ 8]],zv[koi[koffs[i]+ 8]]);
      glVertex3d(xv[koi[koffs[i]+12]],yv[koi[koffs[i]+12]],zv[koi[koffs[i]+12]]);
      glVertex3d(xv[koi[koffs[i]+ 9]],yv[koi[koffs[i]+ 9]],zv[koi[koffs[i]+ 9]]);
      glVertex3d(xv[koi[koffs[i]+13]],yv[koi[koffs[i]+13]],zv[koi[koffs[i]+13]]);
      glVertex3d(xv[koi[koffs[i]+10]],yv[koi[koffs[i]+10]],zv[koi[koffs[i]+10]]);
      glVertex3d(xv[koi[koffs[i]+14]],yv[koi[koffs[i]+14]],zv[koi[koffs[i]+14]]);
      glVertex3d(xv[koi[koffs[i]+11]],yv[koi[koffs[i]+11]],zv[koi[koffs[i]+11]]);
      glVertex3d(xv[koi[koffs[i]+15]],yv[koi[koffs[i]+15]],zv[koi[koffs[i]+15]]);
      glVertex3d(xv[koi[koffs[i]+ 8]],yv[koi[koffs[i]+ 8]],zv[koi[koffs[i]+ 8]]);
    glEnd();

    glBegin(GL_LINES);
      glVertex3d(xv[koi[koffs[i]   ]],yv[koi[koffs[i]   ]],zv[koi[koffs[i]   ]]);
      glVertex3d(xv[koi[koffs[i]+ 8]],yv[koi[koffs[i]+ 8]],zv[koi[koffs[i]+ 8]]);
      glVertex3d(xv[koi[koffs[i]+ 1]],yv[koi[koffs[i]+ 1]],zv[koi[koffs[i]+ 1]]);
      glVertex3d(xv[koi[koffs[i]+ 9]],yv[koi[koffs[i]+ 9]],zv[koi[koffs[i]+ 9]]);
      glVertex3d(xv[koi[koffs[i]+ 2]],yv[koi[koffs[i]+ 2]],zv[koi[koffs[i]+ 2]]);
      glVertex3d(xv[koi[koffs[i]+10]],yv[koi[koffs[i]+10]],zv[koi[koffs[i]+10]]);
      glVertex3d(xv[koi[koffs[i]+ 3]],yv[koi[koffs[i]+ 3]],zv[koi[koffs[i]+ 3]]);
      glVertex3d(xv[koi[koffs[i]+11]],yv[koi[koffs[i]+11]],zv[koi[koffs[i]+11]]);
    glEnd();

    }  /* Ende deg.Volumenele 21 */

/*----------------------------------------------------------------------
* Platte 19
*---------------------------------------------------------------------*/
  if(ityp[i] == 19)
    {       
    if(iflag)
      {
      glColor3f(elem_col[0],elem_col[1],elem_col[2]);
      xla= (xv[koi[koffs[i]]]+xv[koi[koffs[i]+15]])*0.5;
      yla= (yv[koi[koffs[i]]]+yv[koi[koffs[i]+15]])*0.5;
      zla= (zv[koi[koffs[i]]]+zv[koi[koffs[i]+15]])*0.5;
      glRasterPos3d(xla,yla,zla);
      ltoa(i,cstring,10);
      FontPuts(Font,cstring);
      }

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]   ]],yv[koi[koffs[i]   ]],zv[koi[koffs[i]   ]]);
      glVertex3d(xv[koi[koffs[i]+ 4]],yv[koi[koffs[i]+ 4]],zv[koi[koffs[i]+ 4]]);
      glVertex3d(xv[koi[koffs[i]+ 8]],yv[koi[koffs[i]+ 8]],zv[koi[koffs[i]+ 8]]);
      glVertex3d(xv[koi[koffs[i]+12]],yv[koi[koffs[i]+12]],zv[koi[koffs[i]+12]]);
      glVertex3d(xv[koi[koffs[i]+13]],yv[koi[koffs[i]+13]],zv[koi[koffs[i]+13]]);
      glVertex3d(xv[koi[koffs[i]+14]],yv[koi[koffs[i]+14]],zv[koi[koffs[i]+14]]);
      glVertex3d(xv[koi[koffs[i]+15]],yv[koi[koffs[i]+15]],zv[koi[koffs[i]+15]]);
      glVertex3d(xv[koi[koffs[i]+11]],yv[koi[koffs[i]+11]],zv[koi[koffs[i]+11]]);
      glVertex3d(xv[koi[koffs[i]+ 7]],yv[koi[koffs[i]+ 7]],zv[koi[koffs[i]+ 7]]);
      glVertex3d(xv[koi[koffs[i]+ 3]],yv[koi[koffs[i]+ 3]],zv[koi[koffs[i]+ 3]]);
      glVertex3d(xv[koi[koffs[i]+ 2]],yv[koi[koffs[i]+ 2]],zv[koi[koffs[i]+ 2]]);
      glVertex3d(xv[koi[koffs[i]+ 1]],yv[koi[koffs[i]+ 1]],zv[koi[koffs[i]+ 1]]);
      glVertex3d(xv[koi[koffs[i]   ]],yv[koi[koffs[i]   ]],zv[koi[koffs[i]   ]]);
    glEnd();

    }  /* Platte 19 */

/*----------------------------------------------------------------------
* Scheibe 3, Scheibe 14, Torus 15 und Platte 18 und Schale 24 
*---------------------------------------------------------------------*/
  if(ityp[i] ==  3 || ityp[i] == 14 || 
     ityp[i] == 15 || ityp[i] == 18 || ityp[i] == 24)
    {       
    if(iflag)
      {
      glColor3f(elem_col[0],elem_col[1],elem_col[2]);
      xla= (xv[koi[koffs[i]]]+xv[koi[koffs[i]+1]]+xv[koi[koffs[i]+2]])*0.333;
      yla= (yv[koi[koffs[i]]]+yv[koi[koffs[i]+1]]+yv[koi[koffs[i]+2]])*0.333;
      zla= (zv[koi[koffs[i]]]+zv[koi[koffs[i]+1]]+zv[koi[koffs[i]+2]])*0.333;
      glRasterPos3d(xla,yla,zla);
      ltoa(i,cstring,10);
      FontPuts(Font,cstring);
      }

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
      glVertex3d(xv[koi[koffs[i]+3]],yv[koi[koffs[i]+3]],zv[koi[koffs[i]+3]]);
      glVertex3d(xv[koi[koffs[i]+1]],yv[koi[koffs[i]+1]],zv[koi[koffs[i]+1]]);
      glVertex3d(xv[koi[koffs[i]+4]],yv[koi[koffs[i]+4]],zv[koi[koffs[i]+4]]);
      glVertex3d(xv[koi[koffs[i]+2]],yv[koi[koffs[i]+2]],zv[koi[koffs[i]+2]]);
      glVertex3d(xv[koi[koffs[i]+5]],yv[koi[koffs[i]+5]],zv[koi[koffs[i]+5]]);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
    glEnd();

    }  /* Scheiben 3,14, Torus 15, Platte 18 und Schale 24 */

/*----------------------------------------------------------------------
* Volumenschalenelement 22
*---------------------------------------------------------------------*/
  if(ityp[i] ==  22)
    {       
    if(iflag)
      {
      glColor3f(elem_col[0],elem_col[1],elem_col[2]);
      xla=  (xv[koi[koffs[i]  ]]+xv[koi[koffs[i]+1]]+xv[koi[koffs[i]+2]])*0.333;
      yla=  (yv[koi[koffs[i]  ]]+yv[koi[koffs[i]+1]]+yv[koi[koffs[i]+2]])*0.333;
      zla=  (zv[koi[koffs[i]  ]]+zv[koi[koffs[i]+1]]+zv[koi[koffs[i]+2]])*0.333;
      xla+= (xv[koi[koffs[i]+6]]+xv[koi[koffs[i]+7]]+xv[koi[koffs[i]+8]])*0.333;
      yla+= (yv[koi[koffs[i]+6]]+yv[koi[koffs[i]+7]]+yv[koi[koffs[i]+8]])*0.333;
      zla+= (zv[koi[koffs[i]+6]]+zv[koi[koffs[i]+7]]+zv[koi[koffs[i]+8]])*0.333;
      xla/= 2.;
      yla/= 2.;
      zla/= 2.;
      glRasterPos3d(xla,yla,zla);
      ltoa(i,cstring,10);
      FontPuts(Font,cstring);
      }

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
      glVertex3d(xv[koi[koffs[i]+3]],yv[koi[koffs[i]+3]],zv[koi[koffs[i]+3]]);
      glVertex3d(xv[koi[koffs[i]+1]],yv[koi[koffs[i]+1]],zv[koi[koffs[i]+1]]);
      glVertex3d(xv[koi[koffs[i]+4]],yv[koi[koffs[i]+4]],zv[koi[koffs[i]+4]]);
      glVertex3d(xv[koi[koffs[i]+2]],yv[koi[koffs[i]+2]],zv[koi[koffs[i]+2]]);
      glVertex3d(xv[koi[koffs[i]+5]],yv[koi[koffs[i]+5]],zv[koi[koffs[i]+5]]);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
    glEnd(); 

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]+ 6]],yv[koi[koffs[i]+ 6]],zv[koi[koffs[i]+ 6]]);
      glVertex3d(xv[koi[koffs[i]+ 9]],yv[koi[koffs[i]+ 9]],zv[koi[koffs[i]+ 9]]);
      glVertex3d(xv[koi[koffs[i]+ 7]],yv[koi[koffs[i]+ 7]],zv[koi[koffs[i]+ 7]]);
      glVertex3d(xv[koi[koffs[i]+10]],yv[koi[koffs[i]+10]],zv[koi[koffs[i]+10]]);
      glVertex3d(xv[koi[koffs[i]+ 8]],yv[koi[koffs[i]+ 8]],zv[koi[koffs[i]+ 8]]);
      glVertex3d(xv[koi[koffs[i]+11]],yv[koi[koffs[i]+11]],zv[koi[koffs[i]+11]]);
      glVertex3d(xv[koi[koffs[i]+ 6]],yv[koi[koffs[i]+ 6]],zv[koi[koffs[i]+ 6]]);
    glEnd();

    glBegin(GL_LINES);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
      glVertex3d(xv[koi[koffs[i]+6]],yv[koi[koffs[i]+6]],zv[koi[koffs[i]+6]]);
      glVertex3d(xv[koi[koffs[i]+1]],yv[koi[koffs[i]+1]],zv[koi[koffs[i]+1]]);
      glVertex3d(xv[koi[koffs[i]+7]],yv[koi[koffs[i]+7]],zv[koi[koffs[i]+7]]);
      glVertex3d(xv[koi[koffs[i]+2]],yv[koi[koffs[i]+2]],zv[koi[koffs[i]+2]]);
      glVertex3d(xv[koi[koffs[i]+8]],yv[koi[koffs[i]+8]],zv[koi[koffs[i]+8]]);
    glEnd();

    }  /* Volumenscheibe 22 */

/*----------------------------------------------------------------------
* Torus 6
*---------------------------------------------------------------------*/
  if(ityp[i] == 6)
    {       
    if(iflag)
      {
      glColor3f(elem_col[0],elem_col[1],elem_col[2]);
      xla= (xv[koi[koffs[i]]]+xv[koi[koffs[i]+1]]+xv[koi[koffs[i]+2]])*0.333;
      yla= (yv[koi[koffs[i]]]+yv[koi[koffs[i]+1]]+yv[koi[koffs[i]+2]])*0.333;
      zla= (zv[koi[koffs[i]]]+zv[koi[koffs[i]+1]]+zv[koi[koffs[i]+2]])*0.333;
      glRasterPos3d(xla,yla,zla);
      ltoa(i,cstring,10);
      FontPuts(Font,cstring);
      }

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
      glVertex3d(xv[koi[koffs[i]+1]],yv[koi[koffs[i]+1]],zv[koi[koffs[i]+1]]);
      glVertex3d(xv[koi[koffs[i]+2]],yv[koi[koffs[i]+2]],zv[koi[koffs[i]+2]]);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
    glEnd();

    }  /* Torus 6 */

/*----------------------------------------------------------------------
* Tetraeder 16
*---------------------------------------------------------------------*/
  if(ityp[i] == 16)
    {       
    if(iflag)
      {
      glColor3f(elem_col[0],elem_col[1],elem_col[2]);
      xla= (xv[koi[koffs[i]]]+xv[koi[koffs[i]+1]]+
            xv[koi[koffs[i]+2]]+xv[koi[koffs[i]+3]])*0.25;
      yla= (yv[koi[koffs[i]]]+yv[koi[koffs[i]+1]]+
            yv[koi[koffs[i]+2]]+yv[koi[koffs[i]+3]])*0.25;
      zla= (zv[koi[koffs[i]]]+zv[koi[koffs[i]+1]]+
            zv[koi[koffs[i]+2]]+zv[koi[koffs[i]+3]])*0.25;
      glRasterPos3d(xla,yla,zla);
      ltoa(i,cstring,10);
      FontPuts(Font,cstring);
      }

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
      glVertex3d(xv[koi[koffs[i]+6]],yv[koi[koffs[i]+6]],zv[koi[koffs[i]+6]]);
      glVertex3d(xv[koi[koffs[i]+2]],yv[koi[koffs[i]+2]],zv[koi[koffs[i]+2]]);
      glVertex3d(xv[koi[koffs[i]+8]],yv[koi[koffs[i]+8]],zv[koi[koffs[i]+8]]);
      glVertex3d(xv[koi[koffs[i]+3]],yv[koi[koffs[i]+3]],zv[koi[koffs[i]+3]]);
      glVertex3d(xv[koi[koffs[i]+9]],yv[koi[koffs[i]+9]],zv[koi[koffs[i]+9]]);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
    glEnd();

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
      glVertex3d(xv[koi[koffs[i]+4]],yv[koi[koffs[i]+4]],zv[koi[koffs[i]+4]]);
      glVertex3d(xv[koi[koffs[i]+1]],yv[koi[koffs[i]+1]],zv[koi[koffs[i]+1]]);
      glVertex3d(xv[koi[koffs[i]+7]],yv[koi[koffs[i]+7]],zv[koi[koffs[i]+7]]);
      glVertex3d(xv[koi[koffs[i]+3]],yv[koi[koffs[i]+3]],zv[koi[koffs[i]+3]]);
      glVertex3d(xv[koi[koffs[i]+9]],yv[koi[koffs[i]+9]],zv[koi[koffs[i]+9]]);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
    glEnd();

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
      glVertex3d(xv[koi[koffs[i]+4]],yv[koi[koffs[i]+4]],zv[koi[koffs[i]+4]]);
      glVertex3d(xv[koi[koffs[i]+1]],yv[koi[koffs[i]+1]],zv[koi[koffs[i]+1]]);
      glVertex3d(xv[koi[koffs[i]+5]],yv[koi[koffs[i]+5]],zv[koi[koffs[i]+5]]);
      glVertex3d(xv[koi[koffs[i]+2]],yv[koi[koffs[i]+2]],zv[koi[koffs[i]+2]]);
      glVertex3d(xv[koi[koffs[i]+6]],yv[koi[koffs[i]+6]],zv[koi[koffs[i]+6]]);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
    glEnd();

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]+3]],yv[koi[koffs[i]+3]],zv[koi[koffs[i]+3]]);
      glVertex3d(xv[koi[koffs[i]+7]],yv[koi[koffs[i]+7]],zv[koi[koffs[i]+7]]);
      glVertex3d(xv[koi[koffs[i]+1]],yv[koi[koffs[i]+1]],zv[koi[koffs[i]+1]]);
      glVertex3d(xv[koi[koffs[i]+5]],yv[koi[koffs[i]+5]],zv[koi[koffs[i]+5]]);
      glVertex3d(xv[koi[koffs[i]+2]],yv[koi[koffs[i]+2]],zv[koi[koffs[i]+2]]);
      glVertex3d(xv[koi[koffs[i]+8]],yv[koi[koffs[i]+8]],zv[koi[koffs[i]+8]]);
      glVertex3d(xv[koi[koffs[i]+3]],yv[koi[koffs[i]+3]],zv[koi[koffs[i]+3]]);
    glEnd();
    }  /* Ende Tetraeder 16 */

/*----------------------------------------------------------------------
* Tetraeder 17
*---------------------------------------------------------------------*/
  if(ityp[i] == 17)
    {       
    if(iflag)
      {
      glColor3f(elem_col[0],elem_col[1],elem_col[2]);
      xla= (xv[koi[koffs[i]]]+xv[koi[koffs[i]+1]]+
            xv[koi[koffs[i]+2]]+xv[koi[koffs[i]+3]])*0.25;
      yla= (yv[koi[koffs[i]]]+yv[koi[koffs[i]+1]]+
            yv[koi[koffs[i]+2]]+yv[koi[koffs[i]+3]])*0.25;
      zla= (zv[koi[koffs[i]]]+zv[koi[koffs[i]+1]]+
            zv[koi[koffs[i]+2]]+zv[koi[koffs[i]+3]])*0.25;
      glRasterPos3d(xla,yla,zla);
      ltoa(i,cstring,10);
      FontPuts(Font,cstring);
      }

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
      glVertex3d(xv[koi[koffs[i]+2]],yv[koi[koffs[i]+2]],zv[koi[koffs[i]+2]]);
      glVertex3d(xv[koi[koffs[i]+3]],yv[koi[koffs[i]+3]],zv[koi[koffs[i]+3]]);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
    glEnd();

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
      glVertex3d(xv[koi[koffs[i]+1]],yv[koi[koffs[i]+1]],zv[koi[koffs[i]+1]]);
      glVertex3d(xv[koi[koffs[i]+3]],yv[koi[koffs[i]+3]],zv[koi[koffs[i]+3]]);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
    glEnd();

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
      glVertex3d(xv[koi[koffs[i]+1]],yv[koi[koffs[i]+1]],zv[koi[koffs[i]+1]]);
      glVertex3d(xv[koi[koffs[i]+2]],yv[koi[koffs[i]+2]],zv[koi[koffs[i]+2]]);
      glVertex3d(xv[koi[koffs[i]  ]],yv[koi[koffs[i]  ]],zv[koi[koffs[i]  ]]);
    glEnd();

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]+3]],yv[koi[koffs[i]+3]],zv[koi[koffs[i]+3]]);
      glVertex3d(xv[koi[koffs[i]+1]],yv[koi[koffs[i]+1]],zv[koi[koffs[i]+1]]);
      glVertex3d(xv[koi[koffs[i]+2]],yv[koi[koffs[i]+2]],zv[koi[koffs[i]+2]]);
      glVertex3d(xv[koi[koffs[i]+3]],yv[koi[koffs[i]+3]],zv[koi[koffs[i]+3]]);
    glEnd();
    }  /* Ende Tetraeder 17 */

/*----------------------------------------------------------------------
* Hexaeder 10
*---------------------------------------------------------------------*/
  if(ityp[i] == 10)
    {       
    if(iflag)
      {
      glColor3f(elem_col[0],elem_col[1],elem_col[2]);
      xla= (xv[koi[koffs[i]]]+xv[koi[koffs[i]+7]])*0.5;
      yla= (yv[koi[koffs[i]]]+yv[koi[koffs[i]+7]])*0.5;
      zla= (zv[koi[koffs[i]]]+zv[koi[koffs[i]+7]])*0.5;
      glRasterPos3d(xla,yla,zla);
      ltoa(i,cstring,10);
      FontPuts(Font,cstring);
      }

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]   ]],yv[koi[koffs[i]   ]],zv[koi[koffs[i]   ]]);
      glVertex3d(xv[koi[koffs[i]+ 8]],yv[koi[koffs[i]+ 8]],zv[koi[koffs[i]+ 8]]);
      glVertex3d(xv[koi[koffs[i]+ 1]],yv[koi[koffs[i]+ 1]],zv[koi[koffs[i]+ 1]]);
      glVertex3d(xv[koi[koffs[i]+ 9]],yv[koi[koffs[i]+ 9]],zv[koi[koffs[i]+ 9]]);
      glVertex3d(xv[koi[koffs[i]+ 2]],yv[koi[koffs[i]+ 2]],zv[koi[koffs[i]+ 2]]);
      glVertex3d(xv[koi[koffs[i]+10]],yv[koi[koffs[i]+10]],zv[koi[koffs[i]+10]]);
      glVertex3d(xv[koi[koffs[i]+ 3]],yv[koi[koffs[i]+ 3]],zv[koi[koffs[i]+ 3]]);
      glVertex3d(xv[koi[koffs[i]+11]],yv[koi[koffs[i]+11]],zv[koi[koffs[i]+11]]);
      glVertex3d(xv[koi[koffs[i]   ]],yv[koi[koffs[i]   ]],zv[koi[koffs[i]   ]]);
    glEnd();

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]+ 4]],yv[koi[koffs[i]+ 4]],zv[koi[koffs[i]+ 4]]);
      glVertex3d(xv[koi[koffs[i]+12]],yv[koi[koffs[i]+12]],zv[koi[koffs[i]+12]]);
      glVertex3d(xv[koi[koffs[i]+ 5]],yv[koi[koffs[i]+ 5]],zv[koi[koffs[i]+ 5]]);
      glVertex3d(xv[koi[koffs[i]+13]],yv[koi[koffs[i]+13]],zv[koi[koffs[i]+13]]);
      glVertex3d(xv[koi[koffs[i]+ 6]],yv[koi[koffs[i]+ 6]],zv[koi[koffs[i]+ 6]]);
      glVertex3d(xv[koi[koffs[i]+14]],yv[koi[koffs[i]+14]],zv[koi[koffs[i]+14]]);
      glVertex3d(xv[koi[koffs[i]+ 7]],yv[koi[koffs[i]+ 7]],zv[koi[koffs[i]+ 7]]);
      glVertex3d(xv[koi[koffs[i]+15]],yv[koi[koffs[i]+15]],zv[koi[koffs[i]+15]]);
      glVertex3d(xv[koi[koffs[i]+ 4]],yv[koi[koffs[i]+ 4]],zv[koi[koffs[i]+ 4]]);
    glEnd();

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]+ 4]],yv[koi[koffs[i]+ 4]],zv[koi[koffs[i]+ 4]]);
      glVertex3d(xv[koi[koffs[i]+16]],yv[koi[koffs[i]+16]],zv[koi[koffs[i]+16]]);
      glVertex3d(xv[koi[koffs[i]   ]],yv[koi[koffs[i]   ]],zv[koi[koffs[i]   ]]);
    glEnd();

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]+ 5]],yv[koi[koffs[i]+ 5]],zv[koi[koffs[i]+ 5]]);
      glVertex3d(xv[koi[koffs[i]+17]],yv[koi[koffs[i]+17]],zv[koi[koffs[i]+17]]);
      glVertex3d(xv[koi[koffs[i]+ 1]],yv[koi[koffs[i]+ 1]],zv[koi[koffs[i]+ 1]]);
    glEnd();

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]+ 6]],yv[koi[koffs[i]+ 6]],zv[koi[koffs[i]+ 6]]);
      glVertex3d(xv[koi[koffs[i]+18]],yv[koi[koffs[i]+18]],zv[koi[koffs[i]+18]]);
      glVertex3d(xv[koi[koffs[i]+ 2]],yv[koi[koffs[i]+ 2]],zv[koi[koffs[i]+ 2]]);
    glEnd();

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]+ 7]],yv[koi[koffs[i]+ 7]],zv[koi[koffs[i]+ 7]]);
      glVertex3d(xv[koi[koffs[i]+19]],yv[koi[koffs[i]+19]],zv[koi[koffs[i]+19]]);
      glVertex3d(xv[koi[koffs[i]+ 3]],yv[koi[koffs[i]+ 3]],zv[koi[koffs[i]+ 3]]);
    glEnd();
    }  /* Ende Hexaeder 10 */

/*----------------------------------------------------------------------
* Hexaeder 1
*---------------------------------------------------------------------*/
  if(ityp[i] == 1)
    {       
    if(iflag)
      {
      glColor3f(elem_col[0],elem_col[1],elem_col[2]);
      xla= (xv[koi[koffs[i]]]+xv[koi[koffs[i]+6]])*0.5;
      yla= (yv[koi[koffs[i]]]+yv[koi[koffs[i]+6]])*0.5;
      zla= (zv[koi[koffs[i]]]+zv[koi[koffs[i]+6]])*0.5;
      glRasterPos3d(xla,yla,zla);
      ltoa(i,cstring,10);
      FontPuts(Font,cstring);
      }

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]   ]],yv[koi[koffs[i]   ]],zv[koi[koffs[i]   ]]);
      glVertex3d(xv[koi[koffs[i]+ 1]],yv[koi[koffs[i]+ 1]],zv[koi[koffs[i]+ 1]]);
      glVertex3d(xv[koi[koffs[i]+ 2]],yv[koi[koffs[i]+ 2]],zv[koi[koffs[i]+ 2]]);
      glVertex3d(xv[koi[koffs[i]+ 3]],yv[koi[koffs[i]+ 3]],zv[koi[koffs[i]+ 3]]);
      glVertex3d(xv[koi[koffs[i]   ]],yv[koi[koffs[i]   ]],zv[koi[koffs[i]   ]]);
    glEnd();

    glBegin(GL_LINE_STRIP);
      glVertex3d(xv[koi[koffs[i]+ 4]],yv[koi[koffs[i]+ 4]],zv[koi[koffs[i]+ 4]]);
      glVertex3d(xv[koi[koffs[i]+ 5]],yv[koi[koffs[i]+ 5]],zv[koi[koffs[i]+ 5]]);
      glVertex3d(xv[koi[koffs[i]+ 6]],yv[koi[koffs[i]+ 6]],zv[koi[koffs[i]+ 6]]);
      glVertex3d(xv[koi[koffs[i]+ 7]],yv[koi[koffs[i]+ 7]],zv[koi[koffs[i]+ 7]]);
      glVertex3d(xv[koi[koffs[i]+ 4]],yv[koi[koffs[i]+ 4]],zv[koi[koffs[i]+ 4]]);
    glEnd();

    glBegin(GL_LINES);
      glVertex3d(xv[koi[koffs[i]+ 4]],yv[koi[koffs[i]+ 4]],zv[koi[koffs[i]+ 4]]);
      glVertex3d(xv[koi[koffs[i]   ]],yv[koi[koffs[i]   ]],zv[koi[koffs[i]   ]]);
    glEnd();

    glBegin(GL_LINES);
      glVertex3d(xv[koi[koffs[i]+ 5]],yv[koi[koffs[i]+ 5]],zv[koi[koffs[i]+ 5]]);
      glVertex3d(xv[koi[koffs[i]+ 1]],yv[koi[koffs[i]+ 1]],zv[koi[koffs[i]+ 1]]);
    glEnd();

    glBegin(GL_LINES);
      glVertex3d(xv[koi[koffs[i]+ 6]],yv[koi[koffs[i]+ 6]],zv[koi[koffs[i]+ 6]]);
      glVertex3d(xv[koi[koffs[i]+ 2]],yv[koi[koffs[i]+ 2]],zv[koi[koffs[i]+ 2]]);
    glEnd();

    glBegin(GL_LINES);
      glVertex3d(xv[koi[koffs[i]+ 7]],yv[koi[koffs[i]+ 7]],zv[koi[koffs[i]+ 7]]);
      glVertex3d(xv[koi[koffs[i]+ 3]],yv[koi[koffs[i]+ 3]],zv[koi[koffs[i]+ 3]]);
    glEnd();
    }  /* Ende Hexaeder 10 */
  }  /* Ende Schleife ueber alle Elemente */
return 0;
}

/***********************************************************************
* fsrb88 zeichnet die Farbskala fuer die Randbedingungen
***********************************************************************/
int fsrb88(void)
{
extern GLFONT      *Font;

extern FR_DOUBLE   xm;

extern GLfloat     rot[];
extern GLfloat     gruen[];
extern GLfloat     blau[];

extern FR_INT4     LANG;

extern int         if3d;

char               cstring[80];

/*----------------------------------------------------------------------
* fsrb88 zeichnet die Farbskala fuer die Randbedingungen
*---------------------------------------------------------------------*/
glColor3f(rot[1],gruen[1],blau[1]);
glRectd(xm+4,48.0,xm+12,40.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,44.0,0.00);
if(LANG == 1) sprintf(cstring,"U1=UX=0 (Platten:UZ=0)");
if(LANG == 2) sprintf(cstring,"U1=UX=0 (Plates: UZ=0)");
FontPuts(Font,cstring);	

glColor3f(rot[2],gruen[2],blau[2]);
glRectd(xm+4,40.0,xm+12,32.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,36.0,0.00);
if(LANG == 1) sprintf(cstring,"U2=UY=0 (Platten:RotX=0)");
if(LANG == 2) sprintf(cstring,"U2=UY=0 (Plates: RotX=0)");
FontPuts(Font,cstring);	

glColor3f(rot[3],gruen[3],blau[3]);
glRectd(xm+4,32.0,xm+12,24.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,28.0,0.00);
if(LANG == 1) sprintf(cstring,"U3=UZ=0 (Platten:RotY=0)");
if(LANG == 2) sprintf(cstring,"U3=UZ=0 (Plates: RotY=0)");
FontPuts(Font,cstring);	

glColor3f(rot[4],gruen[4],blau[4]);
glRectd(xm+4,24.0,xm+12,16.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,20.0,0.00);
if(LANG == 1) sprintf(cstring,"U4=RotX=0");
if(LANG == 2) sprintf(cstring,"U4=RotX=0");
FontPuts(Font,cstring);	

glColor3f(rot[5],gruen[5],blau[5]);
glRectd(xm+4,16.0,xm+12,8.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,12.0,0.00);
if(LANG == 1) sprintf(cstring,"U5=RotY=0");
if(LANG == 2) sprintf(cstring,"U5=RotY=0");
FontPuts(Font,cstring);	

glColor3f(rot[6],gruen[6],blau[6]);
glRectd(xm+4,8.0,xm+12,0.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,4.0,0.00);
if(LANG == 1) sprintf(cstring,"U6=RotZ=0");
if(LANG == 2) sprintf(cstring,"U6=RotZ=0");
FontPuts(Font,cstring);	

glColor3f(rot[7],gruen[7],blau[7]);
glRectd(xm+4,0.0,xm+12,-8.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,-4.0,0.00);
if(LANG == 1) sprintf(cstring,"Verschiebungen gegeben");
if(LANG == 2) sprintf(cstring,"Displacements given");
FontPuts(Font,cstring);	

glColor3f(rot[8],gruen[8],blau[8]);
glRectd(xm+4,-8.0,xm+12,-16.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,-12.0,0.00);
if(LANG == 1) sprintf(cstring,"Druck/Oberflaechenlasten");
if(LANG == 2) sprintf(cstring,"Surface/Pressure Loads");
FontPuts(Font,cstring);	

glColor3f(rot[9],gruen[9],blau[9]);
glRectd(xm+4,-16.0,xm+12,-24.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,-20.0,0.00);
if(LANG == 1) sprintf(cstring,"Kraefte X");
if(LANG == 2) sprintf(cstring,"Forces X");
FontPuts(Font,cstring);	

glColor3f(rot[10],gruen[10],blau[10]);
glRectd(xm+4,-24.0,xm+12,-32.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,-28.0,0.00);
if(LANG == 1) sprintf(cstring,"Kraefte Y");
if(LANG == 2) sprintf(cstring,"Forces Y");
FontPuts(Font,cstring);	

glColor3f(rot[11],gruen[11],blau[11]);
glRectd(xm+4,-32.0,xm+12,-40.0);
glColor3f(1.0f,0.5f,0.0f);
glRasterPos3d(xm+16,-36.0,0.00);
if(LANG == 1) sprintf(cstring,"Kraefte Z");
if(LANG == 2) sprintf(cstring,"Forces Z");
FontPuts(Font,cstring);	

return 0;
}
