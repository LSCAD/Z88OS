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
/**********************************************************
*  Compilerunit M12.C enthaelt:
*  tet188  mit Licht
*  tet288  mit Spannungen, Eckknoten
*  tet388  Hidden Line
*  tet488  mit Spannungen, Elemente
*  18.11.2015 RIEG
**********************************************************/

/*----------------------------------------------------------------------
* Windows
*---------------------------------------------------------------------*/
#ifdef FR_WIN
#include <z88o.h>
#include <windows.h>
#include <commctrl.h>
#include <gl\gl.h>
#include <stdio.h>    /* fprintf,fgets,sscanf */
#endif

/*----------------------------------------------------------------------
* UNIX
*---------------------------------------------------------------------*/
#ifdef FR_UNIX
#include <z88o.h>
#include <stdio.h>    /* fprintf,fgets,sscanf */
#include <GL/gl.h>
#include <GL/glx.h>
#endif

/***********************************************************************
* hier beginnt Function tet188: mit Licht
***********************************************************************/
int tet188(void)
{
extern FR_DOUBLEAY xv;
extern FR_DOUBLEAY yv;
extern FR_DOUBLEAY zv;

extern FR_DOUBLE   xe[];
extern FR_DOUBLE   ye[];
extern FR_DOUBLE   ze[];

extern FR_DOUBLE   vx[];
extern FR_DOUBLE   vy[];
extern FR_DOUBLE   vz[];

extern FR_INT4AY   ityp;
extern FR_INT4AY   koi;
extern FR_INT4AY   koffs;

extern FR_INT4     ne;

FR_DOUBLE ax,ay,az,bx,by,bz;

FR_INT4            i,j;

/***********************************************************************
* Schleife ueber alle Elemente
***********************************************************************/
for (i= 1; i <= ne; i++)
  {

/*----------------------------------------------------------------------
* Stab 4 u. 9, Balken 2 und 13, Welle 5, Balken 25
*---------------------------------------------------------------------*/
  if(ityp[i] == 4 || ityp[i] == 9  || 
     ityp[i] == 2 || ityp[i] == 13 ||
     ityp[i] == 5 || ityp[i] == 25)
    {       

/*======================================================================
* die zwei Eck-Punkte fuer jeden Stab holen
*=====================================================================*/
    for (j= 1; j <= 2; j++)
      {
      xe[j]= xv[koi[koffs[i]+j-1]];
      ye[j]= yv[koi[koffs[i]+j-1]];
      ze[j]= zv[koi[koffs[i]+j-1]];
      }

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_LINES);
      glVertex3d( xe[1],ye[1],ze[1]);
      glVertex3d( xe[2],ye[2],ze[2]);
    glEnd();
    }  /* Stab 4 u. 9, Balken 2 und 13, Welle 5, Balken 25 */

/*----------------------------------------------------------------------
* Scheibe 7,Torus 8,Scheibe 11,Torus 12 u.Platte 19 u. 20, Schale 23
*---------------------------------------------------------------------*/
  if(ityp[i] == 7  || ityp[i] == 8  || 
     ityp[i] == 11 || ityp[i] == 12 ||
     ityp[i] == 19 || ityp[i] == 20 || ityp[i] == 23)
    {       

/*======================================================================
* die vier Eck-Punkte fuer jede Scheibe oder Platte holen
*=====================================================================*/
  if(ityp[i] != 19)
    {
    for (j= 1; j <= 4; j++)
      {
      xe[j]= xv[koi[koffs[i]+j-1]];
      ye[j]= yv[koi[koffs[i]+j-1]];
      ze[j]= zv[koi[koffs[i]+j-1]];
      }
    }
  else
    {
    xe[1]= xv[koi[koffs[i]]];
    ye[1]= yv[koi[koffs[i]]];
    ze[1]= zv[koi[koffs[i]]];

    xe[2]= xv[koi[koffs[i]+12]];
    ye[2]= yv[koi[koffs[i]+12]];
    ze[2]= zv[koi[koffs[i]+12]];

    xe[3]= xv[koi[koffs[i]+15]];
    ye[3]= yv[koi[koffs[i]+15]];
    ze[3]= zv[koi[koffs[i]+15]];

    xe[4]= xv[koi[koffs[i]+3]];
    ye[4]= yv[koi[koffs[i]+3]];
    ze[4]= zv[koi[koffs[i]+3]];
    }

/*======================================================================
* den Normalenvektor bestimmen
*=====================================================================*/
    /* erster Vektor */
    ax= xe[2]-xe[1];
    ay= ye[2]-ye[1];
    az= ze[2]-ze[1];

    /* zweiter Vektor */
    bx= xe[4]-xe[1];
    by= ye[4]-ye[1];
    bz= ze[4]-ze[1];

    /* Kreuzprodukt */
    vx[1]= ay*bz-by*az;
    vy[1]= az*bx-bz*ax;
    vz[1]= ax*by-bx*ay;

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_QUADS);
      glNormal3d( vx[1],vy[1],vz[1]);
      glVertex3d( xe[1],ye[1],ze[1]);
      glVertex3d( xe[2],ye[2],ze[2]);
      glVertex3d( xe[3],ye[3],ze[3]);
      glVertex3d( xe[4],ye[4],ze[4]);
    glEnd();
    }  /* Scheibe 7,11,Torus 8,12 u.Platte 19 u.20, Schale 23 */

/*----------------------------------------------------------------------
* Scheibe 3, Torus 6, Scheibe 14, Torus 15, Platte 18, Schale 24
*---------------------------------------------------------------------*/
  if(ityp[i] == 3  || ityp[i] == 14 || 
     ityp[i] == 6  || ityp[i] == 15 ||
     ityp[i] == 18 || ityp[i] == 24)
    {       

/*======================================================================
* die drei Eck-Punkte fuer jede Scheibe oder Platte holen
*=====================================================================*/
  for (j= 1; j <= 3; j++)
    {
    xe[j]= xv[koi[koffs[i]+j-1]];
    ye[j]= yv[koi[koffs[i]+j-1]];
    ze[j]= zv[koi[koffs[i]+j-1]];
    }

/*======================================================================
* den Normalenvektor bestimmen
*=====================================================================*/
    /* erster Vektor */
    ax= xe[2]-xe[1];
    ay= ye[2]-ye[1];
    az= ze[2]-ze[1];

    /* zweiter Vektor */
    bx= xe[3]-xe[1];
    by= ye[3]-ye[1];
    bz= ze[3]-ze[1];

    /* Kreuzprodukt */
    vx[1]= ay*bz-by*az;
    vy[1]= az*bx-bz*ax;
    vz[1]= ax*by-bx*ay;

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_TRIANGLES);
      glNormal3d( vx[1],vy[1],vz[1]);
      glVertex3d( xe[1],ye[1],ze[1]);
      glVertex3d( xe[2],ye[2],ze[2]);
      glVertex3d( xe[3],ye[3],ze[3]);
    glEnd();
    }  /* Scheibe 3,14, Torus 6,15, Platte 18, Schale 24 */

/*----------------------------------------------------------------------
* Tetraeder 16 und 17
*---------------------------------------------------------------------*/
  if(ityp[i] == 16 || ityp[i] == 17)
    {       
/*======================================================================
* die vier Punkte fuer jeden Tetraeder holen
*=====================================================================*/
    for (j= 1; j <= 4; j++)
      {
      xe[j]= xv[koi[koffs[i]+j-1]];
      ye[j]= yv[koi[koffs[i]+j-1]];
      ze[j]= zv[koi[koffs[i]+j-1]];
      }

/*======================================================================
* die Normalenvektoren fuer die vier Dreiecke bestimmen
*=====================================================================*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* erster Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[3]-xe[1];
    ay= ye[3]-ye[1];
    az= ze[3]-ze[1];

    /* zweiter Vektor */
    bx= xe[2]-xe[1];
    by= ye[2]-ye[1];
    bz= ze[2]-ze[1];

    /* Kreuzprodukt */
    vx[1]= ay*bz-by*az;
    vy[1]= az*bx-bz*ax;
    vz[1]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* zweiter Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[2]-xe[1];
    ay= ye[2]-ye[1];
    az= ze[2]-ze[1];

    /* zweiter Vektor */
    bx= xe[4]-xe[1];
    by= ye[4]-ye[1];
    bz= ze[4]-ze[1];

    /* Kreuzprodukt */
    vx[2]= ay*bz-by*az;
    vy[2]= az*bx-bz*ax;
    vz[2]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* dritter Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[4]-xe[1];
    ay= ye[4]-ye[1];
    az= ze[4]-ze[1];

    /* zweiter Vektor */
    bx= xe[3]-xe[1];
    by= ye[3]-ye[1];
    bz= ze[3]-ze[1];

    /* Kreuzprodukt */
    vx[3]= ay*bz-by*az;
    vy[3]= az*bx-bz*ax;
    vz[3]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* vierter Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[3]-xe[2];
    ay= ye[3]-ye[2];
    az= ze[3]-ze[2];

    /* zweiter Vektor */
    bx= xe[4]-xe[2];
    by= ye[4]-ye[2];
    bz= ze[4]-ze[2];

    /* Kreuzprodukt */
    vx[4]= ay*bz-by*az;
    vy[4]= az*bx-bz*ax;
    vz[4]= ax*by-bx*ay;

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_TRIANGLES);
      glNormal3d( vx[1],vy[1],vz[1]);
      glVertex3d( xe[1],ye[1],ze[1]);
      glVertex3d( xe[3],ye[3],ze[3]);
      glVertex3d( xe[2],ye[2],ze[2]);

      glNormal3d( vx[2],vy[2],vz[2]);
      glVertex3d( xe[1],ye[1],ze[1]);
      glVertex3d( xe[2],ye[2],ze[2]);
      glVertex3d( xe[4],ye[4],ze[4]);

      glNormal3d( vx[3],vy[3],vz[3]);
      glVertex3d( xe[1],ye[1],ze[1]);
      glVertex3d( xe[4],ye[4],ze[4]);
      glVertex3d( xe[3],ye[3],ze[3]);

      glNormal3d( vx[4],vy[4],vz[4]);
      glVertex3d( xe[2],ye[2],ze[2]);
      glVertex3d( xe[3],ye[3],ze[3]);
      glVertex3d( xe[4],ye[4],ze[4]);
    glEnd();
    }  /* Ende Tetraeder 16 und 17 */

/*----------------------------------------------------------------------
* Hexaeder 1, 10 und 21
*---------------------------------------------------------------------*/
  if(ityp[i] == 1 || ityp[i] == 10 || ityp[i] == 21)
    {       
/*======================================================================
* die acht Punkte fuer jeden Hexaeder holen
*=====================================================================*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Hexaeder 1 und 10
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(ityp[i] == 1 || ityp[i] == 10)
      {
      for (j= 1; j <= 8; j++)
        {
        xe[j]= xv[koi[koffs[i]+j-1]];
        ye[j]= yv[koi[koffs[i]+j-1]];
        ze[j]= zv[koi[koffs[i]+j-1]];
        }
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Volumenschalenele. 21
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(ityp[i] == 21)
      {
      for (j= 1; j <= 4; j++)
        {
        xe[j]= xv[koi[koffs[i]+j-1]];
        ye[j]= yv[koi[koffs[i]+j-1]];
        ze[j]= zv[koi[koffs[i]+j-1]];
        }
      for (j= 5; j <= 8; j++)
        {
        xe[j]= xv[koi[koffs[i]+j+4-1]];
        ye[j]= yv[koi[koffs[i]+j+4-1]];
        ze[j]= zv[koi[koffs[i]+j+4-1]];
        }
      }

/*======================================================================
* die Normalenvektoren fuer die 12 Dreiecke (2 pro Seite) bestimmen
*=====================================================================*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* erster Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[2]-xe[1];
    ay= ye[2]-ye[1];
    az= ze[2]-ze[1];

    /* zweiter Vektor */
    bx= xe[3]-xe[1];
    by= ye[3]-ye[1];
    bz= ze[3]-ze[1];

    /* Kreuzprodukt */
    vx[1]= ay*bz-by*az;
    vy[1]= az*bx-bz*ax;
    vz[1]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* zweiter Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[3]-xe[1];
    ay= ye[3]-ye[1];
    az= ze[3]-ze[1];

    /* zweiter Vektor */
    bx= xe[4]-xe[1];
    by= ye[4]-ye[1];
    bz= ze[4]-ze[1];

    /* Kreuzprodukt */
    vx[2]= ay*bz-by*az;
    vy[2]= az*bx-bz*ax;
    vz[2]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* dritter Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[6]-xe[5];
    ay= ye[6]-ye[5];
    az= ze[6]-ze[5];

    /* zweiter Vektor */
    bx= xe[2]-xe[5];
    by= ye[2]-ye[5];
    bz= ze[2]-ze[5];

    /* Kreuzprodukt */
    vx[3]= ay*bz-by*az;
    vy[3]= az*bx-bz*ax;
    vz[3]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* vierter Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[2]-xe[5];
    ay= ye[2]-ye[5];
    az= ze[2]-ze[5];

    /* zweiter Vektor */
    bx= xe[1]-xe[5];
    by= ye[1]-ye[5];
    bz= ze[1]-ze[5];

    /* Kreuzprodukt */
    vx[4]= ay*bz-by*az;
    vy[4]= az*bx-bz*ax;
    vz[4]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* fuenfter Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[7]-xe[6];
    ay= ye[7]-ye[6];
    az= ze[7]-ze[6];

    /* zweiter Vektor */
    bx= xe[3]-xe[6];
    by= ye[3]-ye[6];
    bz= ze[3]-ze[6];

    /* Kreuzprodukt */
    vx[5]= ay*bz-by*az;
    vy[5]= az*bx-bz*ax;
    vz[5]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* sechster Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[3]-xe[6];
    ay= ye[3]-ye[6];
    az= ze[3]-ze[6];

    /* zweiter Vektor */
    bx= xe[2]-xe[6];
    by= ye[2]-ye[6];
    bz= ze[2]-ze[6];

    /* Kreuzprodukt */
    vx[6]= ay*bz-by*az;
    vy[6]= az*bx-bz*ax;
    vz[6]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 7. Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[7]-xe[8];
    ay= ye[7]-ye[8];
    az= ze[7]-ze[8];

    /* zweiter Vektor */
    bx= xe[5]-xe[8];
    by= ye[5]-ye[8];
    bz= ze[5]-ze[8];

    /* Kreuzprodukt */
    vx[7]= ay*bz-by*az;
    vy[7]= az*bx-bz*ax;
    vz[7]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 8. Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[6]-xe[7];
    ay= ye[6]-ye[7];
    az= ze[6]-ze[7];

    /* zweiter Vektor */
    bx= xe[5]-xe[7];
    by= ye[5]-ye[7];
    bz= ze[5]-ze[7];

    /* Kreuzprodukt */
    vx[8]= ay*bz-by*az;
    vy[8]= az*bx-bz*ax;
    vz[8]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 9. Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[8]-xe[7];
    ay= ye[8]-ye[7];
    az= ze[8]-ze[7];

    /* zweiter Vektor */
    bx= xe[3]-xe[7];
    by= ye[3]-ye[7];
    bz= ze[3]-ze[7];

    /* Kreuzprodukt */
    vx[9]= ay*bz-by*az;
    vy[9]= az*bx-bz*ax;
    vz[9]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 10. Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[4]-xe[8];
    ay= ye[4]-ye[8];
    az= ze[4]-ze[8];

    /* zweiter Vektor */
    bx= xe[3]-xe[8];
    by= ye[3]-ye[8];
    bz= ze[3]-ze[8];

    /* Kreuzprodukt */
    vx[10]= ay*bz-by*az;
    vy[10]= az*bx-bz*ax;
    vz[10]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 11. Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[5]-xe[8];
    ay= ye[5]-ye[8];
    az= ze[5]-ze[8];

    /* zweiter Vektor */
    bx= xe[4]-xe[8];
    by= ye[4]-ye[8];
    bz= ze[4]-ze[8];

    /* Kreuzprodukt */
    vx[11]= ay*bz-by*az;
    vy[11]= az*bx-bz*ax;
    vz[11]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 12. Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[1]-xe[5];
    ay= ye[1]-ye[5];
    az= ze[1]-ze[5];

    /* zweiter Vektor */
    bx= xe[4]-xe[5];
    by= ye[4]-ye[5];
    bz= ze[4]-ze[5];

    /* Kreuzprodukt */
    vx[12]= ay*bz-by*az;
    vy[12]= az*bx-bz*ax;
    vz[12]= ax*by-bx*ay;


/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_TRIANGLES);
      glNormal3d( vx[1],vy[1],vz[1]);
      glVertex3d( xe[1],ye[1],ze[1]);
      glVertex3d( xe[2],ye[2],ze[2]);
      glVertex3d( xe[3],ye[3],ze[3]);

      glNormal3d( vx[2],vy[2],vz[2]);
      glVertex3d( xe[1],ye[1],ze[1]);
      glVertex3d( xe[3],ye[3],ze[3]);
      glVertex3d( xe[4],ye[4],ze[4]);

      glNormal3d( vx[3],vy[3],vz[3]);
      glVertex3d( xe[5],ye[5],ze[5]);
      glVertex3d( xe[6],ye[6],ze[6]);
      glVertex3d( xe[2],ye[2],ze[2]);

      glNormal3d( vx[4],vy[4],vz[4]);
      glVertex3d( xe[5],ye[5],ze[5]);
      glVertex3d( xe[2],ye[2],ze[2]);
      glVertex3d( xe[1],ye[1],ze[1]);

      glNormal3d( vx[5],vy[5],vz[5]);
      glVertex3d( xe[6],ye[6],ze[6]);
      glVertex3d( xe[7],ye[7],ze[7]);
      glVertex3d( xe[3],ye[3],ze[3]);

      glNormal3d( vx[6],vy[6],vz[6]);
      glVertex3d( xe[6],ye[6],ze[6]);
      glVertex3d( xe[3],ye[3],ze[3]);
      glVertex3d( xe[2],ye[2],ze[2]);

      glNormal3d( vx[7],vy[7],vz[7]);
      glVertex3d( xe[5],ye[5],ze[5]);
      glVertex3d( xe[8],ye[8],ze[8]);
      glVertex3d( xe[7],ye[7],ze[7]);

      glNormal3d( vx[8],vy[8],vz[8]);
      glVertex3d( xe[5],ye[5],ze[5]);
      glVertex3d( xe[7],ye[7],ze[7]);
      glVertex3d( xe[6],ye[6],ze[6]);

      glNormal3d( vx[9],vy[9],vz[9]);
      glVertex3d( xe[3],ye[3],ze[3]);
      glVertex3d( xe[7],ye[7],ze[7]);
      glVertex3d( xe[8],ye[8],ze[8]);

      glNormal3d( vx[10],vy[10],vz[10]);
      glVertex3d( xe[3],ye[3],ze[3]);
      glVertex3d( xe[8],ye[8],ze[8]);
      glVertex3d( xe[4],ye[4],ze[4]);

      glNormal3d( vx[11],vy[11],vz[11]);
      glVertex3d( xe[4],ye[4],ze[4]);
      glVertex3d( xe[8],ye[8],ze[8]);
      glVertex3d( xe[5],ye[5],ze[5]);

      glNormal3d( vx[12],vy[12],vz[12]);
      glVertex3d( xe[4],ye[4],ze[4]);
      glVertex3d( xe[5],ye[5],ze[5]);
      glVertex3d( xe[1],ye[1],ze[1]);
    glEnd();
    }  /* Ende Hexaeder 1, 10 und 21 */

/*----------------------------------------------------------------------
* Volumenschale 22
*---------------------------------------------------------------------*/
  if(ityp[i] == 22)
    {       
/*======================================================================
* die sechs Punkte fuer jede Schale holen
*=====================================================================*/
    for (j= 1; j <= 3; j++)
      {
      xe[j]= xv[koi[koffs[i]+j-1]];
      ye[j]= yv[koi[koffs[i]+j-1]];
      ze[j]= zv[koi[koffs[i]+j-1]];
      }
    for (j= 4; j <= 6; j++)
      {
      xe[j]= xv[koi[koffs[i]+j+3-1]];
      ye[j]= yv[koi[koffs[i]+j+3-1]];
      ze[j]= zv[koi[koffs[i]+j+3-1]];
      }

/*======================================================================
* die Normalenvektoren fuer 8 Dreiecke (2 pro Seiten-Seite) bestimmen
*=====================================================================*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* erster Normalenvektor (Deckflaeche)
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[2]-xe[1];
    ay= ye[2]-ye[1];
    az= ze[2]-ze[1];

    /* zweiter Vektor */
    bx= xe[3]-xe[1];
    by= ye[3]-ye[1];
    bz= ze[3]-ze[1];

    /* Kreuzprodukt */
    vx[1]= ay*bz-by*az;
    vy[1]= az*bx-bz*ax;
    vz[1]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* zweiter Normalenvektor (Unterseite)
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[5]-xe[4];
    ay= ye[5]-ye[4];
    az= ze[5]-ze[4];

    /* zweiter Vektor */
    bx= xe[6]-xe[4];
    by= ye[6]-ye[4];
    bz= ze[6]-ze[4];

    /* Kreuzprodukt */
    vx[2]= ay*bz-by*az;
    vy[2]= az*bx-bz*ax;
    vz[2]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* dritter Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[5]-xe[4];
    ay= ye[5]-ye[4];
    az= ze[5]-ze[4];

    /* zweiter Vektor */
    bx= xe[1]-xe[4];
    by= ye[1]-ye[4];
    bz= ze[1]-ze[4];

    /* Kreuzprodukt */
    vx[3]= ay*bz-by*az;
    vy[3]= az*bx-bz*ax;
    vz[3]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* vierter Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[5]-xe[1];
    ay= ye[5]-ye[1];
    az= ze[5]-ze[1];

    /* zweiter Vektor */
    bx= xe[2]-xe[1];
    by= ye[2]-ye[1];
    bz= ze[2]-ze[1];

    /* Kreuzprodukt */
    vx[4]= ay*bz-by*az;
    vy[4]= az*bx-bz*ax;
    vz[4]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* fuenfter Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[6]-xe[5];
    ay= ye[6]-ye[5];
    az= ze[6]-ze[5];

    /* zweiter Vektor */
    bx= xe[2]-xe[5];
    by= ye[2]-ye[5];
    bz= ze[2]-ze[5];

    /* Kreuzprodukt */
    vx[5]= ay*bz-by*az;
    vy[5]= az*bx-bz*ax;
    vz[5]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* sechster Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[6]-xe[2];
    ay= ye[6]-ye[2];
    az= ze[6]-ze[2];

    /* zweiter Vektor */
    bx= xe[3]-xe[2];


    by= ye[3]-ye[2];
    bz= ze[3]-ze[2];

    /* Kreuzprodukt */
    vx[6]= ay*bz-by*az;
    vy[6]= az*bx-bz*ax;
    vz[6]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 7. Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[4]-xe[6];
    ay= ye[4]-ye[6];
    az= ze[4]-ze[6];

    /* zweiter Vektor */
    bx= xe[3]-xe[6];
    by= ye[3]-ye[6];
    bz= ze[3]-ze[6];

    /* Kreuzprodukt */
    vx[7]= ay*bz-by*az;
    vy[7]= az*bx-bz*ax;
    vz[7]= ax*by-bx*ay;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 8. Normalenvektor
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    /* erster Vektor */
    ax= xe[4]-xe[3];
    ay= ye[4]-ye[3];
    az= ze[4]-ze[3];

    /* zweiter Vektor */
    bx= xe[1]-xe[3];
    by= ye[1]-ye[3];
    bz= ze[1]-ze[3];

    /* Kreuzprodukt */
    vx[8]= ay*bz-by*az;
    vy[8]= az*bx-bz*ax;
    vz[8]= ax*by-bx*ay;

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_TRIANGLES);
      glNormal3d( vx[1],vy[1],vz[1]);
      glVertex3d( xe[1],ye[1],ze[1]);
      glVertex3d( xe[2],ye[2],ze[2]);
      glVertex3d( xe[3],ye[3],ze[3]);

      glNormal3d( vx[2],vy[2],vz[2]);
      glVertex3d( xe[4],ye[4],ze[4]);
      glVertex3d( xe[5],ye[5],ze[5]);
      glVertex3d( xe[6],ye[6],ze[6]);

      glNormal3d( vx[3],vy[3],vz[3]);
      glVertex3d( xe[4],ye[4],ze[4]);
      glVertex3d( xe[5],ye[5],ze[5]);
      glVertex3d( xe[1],ye[1],ze[1]);

      glNormal3d( vx[4],vy[4],vz[4]);
      glVertex3d( xe[1],ye[1],ze[1]);
      glVertex3d( xe[5],ye[5],ze[5]);
      glVertex3d( xe[2],ye[2],ze[2]);

      glNormal3d( vx[5],vy[5],vz[5]);
      glVertex3d( xe[5],ye[5],ze[5]);
      glVertex3d( xe[6],ye[6],ze[6]);
      glVertex3d( xe[2],ye[2],ze[2]);

      glNormal3d( vx[6],vy[6],vz[6]);
      glVertex3d( xe[2],ye[2],ze[2]);
      glVertex3d( xe[6],ye[6],ze[6]);
      glVertex3d( xe[3],ye[3],ze[3]);

      glNormal3d( vx[7],vy[7],vz[7]);
      glVertex3d( xe[6],ye[6],ze[6]);
      glVertex3d( xe[4],ye[4],ze[4]);
      glVertex3d( xe[3],ye[3],ze[3]);

      glNormal3d( vx[8],vy[8],vz[8]);
      glVertex3d( xe[3],ye[3],ze[3]);
      glVertex3d( xe[4],ye[4],ze[4]);
      glVertex3d( xe[1],ye[1],ze[1]);

    glEnd();
    }  /* Ende Volumenschale 22 */


  }  /* Ende Schleife ueber alle Elemente */

return 0;
}

/***********************************************************************
* hier beginnt Function tet288: mit Spannungen oder Verschiebungen an
* den Eckknoten
***********************************************************************/
int tet288(void)
{
extern FR_DOUBLEAY xv;
extern FR_DOUBLEAY yv;
extern FR_DOUBLEAY zv;

extern FR_DOUBLE   xe[];
extern FR_DOUBLE   ye[];
extern FR_DOUBLE   ze[];

extern FR_DOUBLE   vx[];
extern FR_DOUBLE   vy[];
extern FR_DOUBLE   vz[];

extern GLfloat     rot[];
extern GLfloat     gruen[];
extern GLfloat     blau[];

extern FR_INT4AY   ifarbe;

extern FR_INT4AY   ityp;
extern FR_INT4AY   koi;
extern FR_INT4AY   koffs;

extern FR_INT4     kf[];

extern FR_INT4     ne;

FR_INT4            i,j,k;

static FR_INT4     jp7[5]= {0,1,2,3,4};

static FR_INT4     jp16[13]={0,1,3,2,1,2,4,1,4,3,2,3,4};

static FR_INT4     jp10[37]={0,1,2,3,1,3,4,5,6,2,5,2,1,6,7,3,6,3,2,
                               5,8,7,5,7,6,3,7,8,3,8,4,4,8,5,4,5,1};

static FR_INT4     jp22[25]={0,1,2,3,4,6,5,4,5,1,1,5,2,5,6,2,2,6,3,
                               6,4,3,3,4,1};
           
/***********************************************************************
* Schleife ueber alle Elemente
***********************************************************************/
for (i= 1; i <= ne; i++)
  {

/*----------------------------------------------------------------------
* Stab 4 u. 9, Balken 2 und 13, Welle 5, Balken 25
*---------------------------------------------------------------------*/
  if(ityp[i] == 4 || ityp[i] == 9  || 
     ityp[i] == 2 || ityp[i] == 13 ||
     ityp[i] == 5 || ityp[i] == 25)
    {       

/*======================================================================
* die zwei Eck-Punkte fuer jeden Stab holen
*=====================================================================*/
    for (j= 1; j <= 2; j++)
      {
      xe[j]= xv[koi[koffs[i]+j-1]];
      ye[j]= yv[koi[koffs[i]+j-1]];
      ze[j]= zv[koi[koffs[i]+j-1]];
      kf[j]= koi[koffs[i]+j-1];
      }

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_LINES);
      for(k= 1; k <= 2; k++)
        {
        glColor3f (rot  [ifarbe[kf[jp7[k]]]],
                   gruen[ifarbe[kf[jp7[k]]]],
                   blau [ifarbe[kf[jp7[k]]]]);
        glVertex3d(xe[k],ye[k],ze[k]);
        }
    glEnd();
    }  /* Stab 4 u. 9, Balken 2 und 13, Welle 5, Balken 25 */

/*----------------------------------------------------------------------
* Scheibe 7,Torus 8,Scheibe 11,Torus 12 u.Platte 19 u.20,Schale 23
*---------------------------------------------------------------------*/
  if(ityp[i] == 7  || ityp[i] == 8  || 
     ityp[i] == 11 || ityp[i] == 12 ||
     ityp[i] == 19 || ityp[i] == 20 || ityp[i] == 23)
    {       

/*======================================================================
* die vier Eck-Punkte fuer jede Scheibe oder Platte holen
*=====================================================================*/
  if(ityp[i] != 19)
    {
    for (j= 1; j <= 4; j++)
      {
      xe[j]= xv[koi[koffs[i]+j-1]];
      ye[j]= yv[koi[koffs[i]+j-1]];
      ze[j]= zv[koi[koffs[i]+j-1]];
      kf[j]= koi[koffs[i]+j-1];
      }
    }
  else
    {
    xe[1]= xv[koi[koffs[i]]];
    ye[1]= yv[koi[koffs[i]]];
    ze[1]= zv[koi[koffs[i]]];
    kf[1]= koi[koffs[i]];

    xe[2]= xv[koi[koffs[i]+12]];
    ye[2]= yv[koi[koffs[i]+12]];
    ze[2]= zv[koi[koffs[i]+12]];
    kf[2]= koi[koffs[i]+12];

    xe[3]= xv[koi[koffs[i]+15]];
    ye[3]= yv[koi[koffs[i]+15]];
    ze[3]= zv[koi[koffs[i]+15]];
    kf[3]= koi[koffs[i]+15];

    xe[4]= xv[koi[koffs[i]+3]];
    ye[4]= yv[koi[koffs[i]+3]];
    ze[4]= zv[koi[koffs[i]+3]];
    kf[4]= koi[koffs[i]+3];
    }

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_QUADS);
      for(k= 1; k <= 4; k++)
        {
        glColor3f (rot  [ifarbe[kf[jp7[k]]]],
                   gruen[ifarbe[kf[jp7[k]]]],
                   blau [ifarbe[kf[jp7[k]]]]);
        glVertex3d(xe[jp7[k]],ye[jp7[k]],ze[jp7[k]]);
        }
    glEnd();
    }  /* Scheibe 7,11,Torus 8,12 u.Platte 19 u.20,Schale 23 */

/*----------------------------------------------------------------------
* Scheibe 3, Torus 6, Scheibe 14, Torus 15, Platte 18, Schale 24
*---------------------------------------------------------------------*/
  if(ityp[i] == 3  || ityp[i] == 14 || 
     ityp[i] == 6  || ityp[i] == 15 ||
     ityp[i] == 18 || ityp[i] == 24)
    {       

/*======================================================================
* die drei Eck-Punkte fuer jede Scheibe oder Platte holen
*=====================================================================*/
  for (j= 1; j <= 3; j++)
    {
    xe[j]= xv[koi[koffs[i]+j-1]];
    ye[j]= yv[koi[koffs[i]+j-1]];
    ze[j]= zv[koi[koffs[i]+j-1]];
    kf[j]= koi[koffs[i]+j-1];
    }

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_TRIANGLES);
      for(k= 1; k <= 3; k++)
        {
        glColor3f (rot  [ifarbe[kf[jp7[k]]]],
                   gruen[ifarbe[kf[jp7[k]]]],
                   blau [ifarbe[kf[jp7[k]]]]);
        glVertex3d(xe[jp7[k]],ye[jp7[k]],ze[jp7[k]]);
        }
    glEnd();
    }  /* Scheibe 3,14, Torus 6,15, Platte 18, Schale 24 */

/*----------------------------------------------------------------------
* Tetraeder 16 und 17
*---------------------------------------------------------------------*/
  if(ityp[i] == 16 || ityp[i] == 17)
    {       

/*======================================================================
* die vier Punkte fuer jeden Tetraeder holen
*=====================================================================*/
    for (j= 1; j <= 4; j++)
      {
      xe[j]= xv[koi[koffs[i]+j-1]];
      ye[j]= yv[koi[koffs[i]+j-1]];
      ze[j]= zv[koi[koffs[i]+j-1]];
      kf[j]= koi[koffs[i]+j-1];
      }

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_TRIANGLES);
      for(k= 1; k <= 12; k++)
        {
        glColor3f (rot  [ifarbe[kf[jp16[k]]]],
                   gruen[ifarbe[kf[jp16[k]]]],
                   blau [ifarbe[kf[jp16[k]]]]);
        glVertex3d(xe[jp16[k]],ye[jp16[k]],ze[jp16[k]]);
        }
    glEnd();
    }  /* Ende Tetraeder 16 und 17 */

/*----------------------------------------------------------------------
* Hexaeder 1, 10 und 21
*---------------------------------------------------------------------*/
  if(ityp[i] == 1 || ityp[i] == 10  || ityp[i] == 21)
    {       
/*======================================================================
* die acht Punkte fuer jeden Hexaeder holen
*=====================================================================*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Hexaeder 1 und 10
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(ityp[i] == 1 || ityp[i] == 10)
      {
      for (j= 1; j <= 8; j++)
        {
        xe[j]= xv[koi[koffs[i]+j-1]];
        ye[j]= yv[koi[koffs[i]+j-1]];
        ze[j]= zv[koi[koffs[i]+j-1]];
        kf[j]=    koi[koffs[i]+j-1];
        }
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Volumenschalenele. 21
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(ityp[i] == 21)
      {
      for (j= 1; j <= 4; j++)
        {
        xe[j]= xv[koi[koffs[i]+j-1]];
        ye[j]= yv[koi[koffs[i]+j-1]];
        ze[j]= zv[koi[koffs[i]+j-1]];
        kf[j]=    koi[koffs[i]+j-1];
        }
      for (j= 5; j <= 8; j++)
        {
        xe[j]= xv[koi[koffs[i]+j+4-1]];
        ye[j]= yv[koi[koffs[i]+j+4-1]];
        ze[j]= zv[koi[koffs[i]+j+4-1]];
        kf[j]=    koi[koffs[i]+j+4-1];
        }
      }

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_TRIANGLES);
      for(k= 1; k <= 36; k++) /* 12 Dreiecke */
        {
        glColor3f (rot  [ifarbe[kf[jp10[k]]]],
                   gruen[ifarbe[kf[jp10[k]]]],
                   blau [ifarbe[kf[jp10[k]]]]);
        glVertex3d(xe[jp10[k]],ye[jp10[k]],ze[jp10[k]]);
        }
    glEnd();
    }  /* Ende Hexaeder 1, 10 und Schale 21 */

/*----------------------------------------------------------------------
* Volumenschale 22
*---------------------------------------------------------------------*/
  if(ityp[i] == 22)
    {       
/*======================================================================
* die sechs Punkte fuer jede Schale holen
*=====================================================================*/
    for (j= 1; j <= 3; j++)
      {
      xe[j]= xv[koi[koffs[i]+j-1]];
      ye[j]= yv[koi[koffs[i]+j-1]];
      ze[j]= zv[koi[koffs[i]+j-1]];
      kf[j]=    koi[koffs[i]+j-1];
      }
    for (j= 4; j <= 6; j++)
      {
      xe[j]= xv[koi[koffs[i]+j+3-1]];
      ye[j]= yv[koi[koffs[i]+j+3-1]];
      ze[j]= zv[koi[koffs[i]+j+3-1]];
      kf[j]=    koi[koffs[i]+j+3-1];
      }

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_TRIANGLES);
      for(k= 1; k <= 24; k++) /* 8 Dreiecke */
        {
        glColor3f (rot  [ifarbe[kf[jp22[k]]]],
                   gruen[ifarbe[kf[jp22[k]]]],
                   blau [ifarbe[kf[jp22[k]]]]);
        glVertex3d(xe[jp22[k]],ye[jp22[k]],ze[jp22[k]]);
        }
    glEnd();
    }  /* Ende Volumenschale 22 */

  }  /* Ende Schleife ueber alle Elemente */

return 0;
}

/***********************************************************************
* hier beginnt Function tet388: Hidden Line
***********************************************************************/
int tet388(void)
{
extern FR_DOUBLEAY xv;
extern FR_DOUBLEAY yv;
extern FR_DOUBLEAY zv;

extern FR_DOUBLE   xe[];
extern FR_DOUBLE   ye[];
extern FR_DOUBLE   ze[];

extern FR_INT4AY   ityp;
extern FR_INT4AY   koi;
extern FR_INT4AY   koffs;

extern FR_INT4     ne;

FR_INT4            i,j,k;

static FR_INT4     jp7[5]=  {0,1,2,3,4};

static FR_INT4     jp16[13]={0,1,3,2,1,2,4,1,4,3,2,3,4};

static FR_INT4     jp10[25]={0,1,2,3,4,5,6,7,8,1,2,6,5,2,3,7,6,
                               3,4,8,7,1,4,8,5};

static FR_INT4     jd22[7] ={0,1,2,3,4,5,6};

static FR_INT4     jv22[13]={0,1,4,5,2,2,5,6,3,3,6,4,1};

/***********************************************************************
* Schleife ueber alle Elemente
***********************************************************************/
for (i= 1; i <= ne; i++)
  {

/*----------------------------------------------------------------------
* Stab 4 u. 9, Balken 2 und 13, Welle 5, Balken 25
*---------------------------------------------------------------------*/
  if(ityp[i] == 4 || ityp[i] == 9  || 
     ityp[i] == 2 || ityp[i] == 13 ||
     ityp[i] == 5 || ityp[i] == 25)
    {       

/*======================================================================
* die zwei Eck-Punkte fuer jeden Stab holen
*=====================================================================*/
  for (j= 1; j <= 2; j++)
    {
    xe[j]= xv[koi[koffs[i]+j-1]];
    ye[j]= yv[koi[koffs[i]+j-1]];
    ze[j]= zv[koi[koffs[i]+j-1]];
    }

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_LINES);
      glVertex3d( xe[1],ye[1],ze[1]);
      glVertex3d( xe[2],ye[2],ze[2]);
    glEnd();
    }  /* Stab 4 u. 9, Balken 2 und 13, Welle 5, Balken 25 */


/*----------------------------------------------------------------------
* Scheibe 7,Torus 8,Scheibe 11,Torus 12 u.Platte 19 u.20,Schale 23
*---------------------------------------------------------------------*/
  if(ityp[i] == 7  || ityp[i] == 8  || 
     ityp[i] == 11 || ityp[i] == 12 ||
     ityp[i] == 19 || ityp[i] == 20 || ityp[i] == 23)
    {       

/*======================================================================
* die vier Eck-Punkte fuer jede Scheibe oder Platte holen
*=====================================================================*/
  if(ityp[i] != 19)
    {
    for (j= 1; j <= 4; j++)
      {
      xe[j]= xv[koi[koffs[i]+j-1]];
      ye[j]= yv[koi[koffs[i]+j-1]];
      ze[j]= zv[koi[koffs[i]+j-1]];
      }
    }
  else
    {
    xe[1]= xv[koi[koffs[i]]];
    ye[1]= yv[koi[koffs[i]]];
    ze[1]= zv[koi[koffs[i]]];

    xe[2]= xv[koi[koffs[i]+12]];
    ye[2]= yv[koi[koffs[i]+12]];
    ze[2]= zv[koi[koffs[i]+12]];

    xe[3]= xv[koi[koffs[i]+15]];
    ye[3]= yv[koi[koffs[i]+15]];
    ze[3]= zv[koi[koffs[i]+15]];

    xe[4]= xv[koi[koffs[i]+3]];
    ye[4]= yv[koi[koffs[i]+3]];
    ze[4]= zv[koi[koffs[i]+3]];
    }

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_QUADS);
      for(k= 1; k <= 4; k++)
        glVertex3d(xe[jp7[k]],ye[jp7[k]],ze[jp7[k]]);
    glEnd();
    }  /* Scheibe 7,11,Torus 8,12 u.Platte 19 u.20,Schale 23 */

/*----------------------------------------------------------------------
* Scheibe 3, Torus 6, Scheibe 14, Torus 15, Platte 18, Schale 24
*---------------------------------------------------------------------*/
  if(ityp[i] == 3  || ityp[i] == 14 || 
     ityp[i] == 6  || ityp[i] == 15 ||
     ityp[i] == 18 || ityp[i] == 24)
    {       

/*======================================================================
* die drei Eck-Punkte fuer jede Scheibe oder Platte holen
*=====================================================================*/
  for (j= 1; j <= 3; j++)
    {
    xe[j]= xv[koi[koffs[i]+j-1]];
    ye[j]= yv[koi[koffs[i]+j-1]];
    ze[j]= zv[koi[koffs[i]+j-1]];
    }

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_TRIANGLES);
      for(k= 1; k <= 3; k++)
        glVertex3d(xe[jp7[k]],ye[jp7[k]],ze[jp7[k]]);
    glEnd();
    }  /* Scheibe 3,14, Torus 6,15, Platte 18, Schale 24 */

/*----------------------------------------------------------------------
* Tetraeder 16 und 17
*---------------------------------------------------------------------*/
  if(ityp[i] == 16 || ityp[i] == 17)
    {       
       
/*======================================================================
* die vier Eck-Punkte fuer jeden Tetraeder holen
*=====================================================================*/
    for (j= 1; j <= 4; j++)
      {
      xe[j]= xv[koi[koffs[i]+j-1]];
      ye[j]= yv[koi[koffs[i]+j-1]];
      ze[j]= zv[koi[koffs[i]+j-1]];
      }

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_TRIANGLES);
      for(k= 1; k <= 12; k++)
        glVertex3d(xe[jp16[k]],ye[jp16[k]],ze[jp16[k]]);
    glEnd();
    }  /* Ende Tetraeder 16 und 17 */

/*----------------------------------------------------------------------
* Hexaeder 1, 10 und 21
*---------------------------------------------------------------------*/
  if(ityp[i] == 1 || ityp[i] == 10 || ityp[i] == 21)
    {       
/*======================================================================
* die acht Punkte fuer jeden Hexaeder holen
*=====================================================================*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Hexaeder 1 und 10: die 8 Eckknoten
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(ityp[i] == 1 || ityp[i] == 10)
      {
      for (j= 1; j <= 8; j++)
        {
        xe[j]= xv[koi[koffs[i]+j-1]];
        ye[j]= yv[koi[koffs[i]+j-1]];
        ze[j]= zv[koi[koffs[i]+j-1]];
        }
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Volumenschalenele. 21: die 8 Eckknoten
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(ityp[i] == 21)
      {
      for (j= 1; j <= 4; j++)
        {
        xe[j]= xv[koi[koffs[i]+j-1]];
        ye[j]= yv[koi[koffs[i]+j-1]];
        ze[j]= zv[koi[koffs[i]+j-1]];
        }
      for (j= 5; j <= 8; j++)
        {
        xe[j]= xv[koi[koffs[i]+j+4-1]];
        ye[j]= yv[koi[koffs[i]+j+4-1]];
        ze[j]= zv[koi[koffs[i]+j+4-1]];
        }
      }

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_QUADS);
      for(k= 1; k <= 24; k++)
        glVertex3d(xe[jp10[k]],ye[jp10[k]],ze[jp10[k]]);
    glEnd();
    }  /* Ende Hexaeder 1, 10 und 21 */

/*----------------------------------------------------------------------
* Volumenschale 22
*---------------------------------------------------------------------*/
  if(ityp[i] == 22)
    {       
    for (j= 1; j <= 3; j++)
      {
      xe[j]= xv[koi[koffs[i]+j-1]];
      ye[j]= yv[koi[koffs[i]+j-1]];
      ze[j]= zv[koi[koffs[i]+j-1]];
      }
    for (j= 4; j <= 6; j++)
      {
      xe[j]= xv[koi[koffs[i]+j+3-1]];
      ye[j]= yv[koi[koffs[i]+j+3-1]];
      ze[j]= zv[koi[koffs[i]+j+3-1]];
      }

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_TRIANGLES);
      for(k= 1; k <= 6; k++)
        glVertex3d(xe[jd22[k]],ye[jd22[k]],ze[jd22[k]]);
    glEnd();

    glBegin(GL_QUADS);
      for(k= 1; k <= 12; k++)
        glVertex3d(xe[jv22[k]],ye[jv22[k]],ze[jv22[k]]);
    glEnd();
    }  /* Ende Volumenschale 22 */


  }  /* Ende Schleife ueber alle Elemente */

return 0;
}

/***********************************************************************
* hier beginnt Function tet488: Spannungen pro Element
***********************************************************************/
int tet488(void)
{
extern FR_DOUBLEAY xv;
extern FR_DOUBLEAY yv;
extern FR_DOUBLEAY zv;

extern FR_DOUBLE   xe[];
extern FR_DOUBLE   ye[];
extern FR_DOUBLE   ze[];

extern FR_DOUBLE   vx[];
extern FR_DOUBLE   vy[];
extern FR_DOUBLE   vz[];

extern GLfloat     rot[];
extern GLfloat     gruen[];
extern GLfloat     blau[];

extern FR_INT4AY   jfarbe;

extern FR_INT4AY   ityp;
extern FR_INT4AY   koi;
extern FR_INT4AY   koffs;

extern FR_INT4     ne;

FR_INT4            i,j,k;

static FR_INT4     jp7[5]=  {0,1,2,3,4};

static FR_INT4     jp16[13]={0,1,3,2,1,2,4,1,4,3,2,3,4};

static FR_INT4     jp10[37]={0,1,2,3,1,3,4,5,6,2,5,2,1,6,7,3,6,3,2,
                               5,8,7,5,7,6,3,7,8,3,8,4,4,8,5,4,5,1};

static FR_INT4     jp22[25]={0,1,2,3,4,6,5,4,5,1,1,5,2,5,6,2,2,6,3,
                               6,4,3,3,4,1};

/***********************************************************************
* Schleife ueber alle Elemente
***********************************************************************/
for (i= 1; i <= ne; i++)
  {

/*----------------------------------------------------------------------
* Stab 4 u. 9, Balken 2 und 13, Welle 5, Balken 25
*---------------------------------------------------------------------*/
  if(ityp[i] == 4 || ityp[i] == 9  || 
     ityp[i] == 2 || ityp[i] == 13 ||
     ityp[i] == 5 || ityp[i] == 25)
    {       

/*======================================================================
* die zwei Eck-Punkte fuer jeden Stab holen
*=====================================================================*/
    for (j= 1; j <= 2; j++)
      {
      xe[j]= xv[koi[koffs[i]+j-1]];
      ye[j]= yv[koi[koffs[i]+j-1]];
      ze[j]= zv[koi[koffs[i]+j-1]];
      }

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_LINES);
      glColor3f (rot[jfarbe[i]],gruen[jfarbe[i]],blau [jfarbe[i]]); 
      glVertex3d( xe[1],ye[1],ze[1]);
      glVertex3d( xe[2],ye[2],ze[2]);
    glEnd();
    }    /* Stab 4 u. 9, Balken 2 und 13, Welle 5, Balken 25*/


/*----------------------------------------------------------------------
* Scheibe 7,Torus 8,Scheibe 11,Torus 12 u. Platte 19 u.20,Schale 23
*---------------------------------------------------------------------*/
  if(ityp[i] == 7  || ityp[i] == 8  || 
     ityp[i] == 11 || ityp[i] == 12 ||
     ityp[i] == 19 || ityp[i] == 20 || ityp[i] == 23)
    {       
    
/*======================================================================
* die vier Eck-Punkte fuer jede Scheibe oder Platte holen
*=====================================================================*/
  if(ityp[i] != 19)
    {
    for (j= 1; j <= 4; j++)
      {
      xe[j]= xv[koi[koffs[i]+j-1]];
      ye[j]= yv[koi[koffs[i]+j-1]];
      ze[j]= zv[koi[koffs[i]+j-1]];
      }
    }
  else
    {
    xe[1]= xv[koi[koffs[i]]];
    ye[1]= yv[koi[koffs[i]]];
    ze[1]= zv[koi[koffs[i]]];

    xe[2]= xv[koi[koffs[i]+12]];
    ye[2]= yv[koi[koffs[i]+12]];
    ze[2]= zv[koi[koffs[i]+12]];

    xe[3]= xv[koi[koffs[i]+15]];
    ye[3]= yv[koi[koffs[i]+15]];
    ze[3]= zv[koi[koffs[i]+15]];

    xe[4]= xv[koi[koffs[i]+3]];
    ye[4]= yv[koi[koffs[i]+3]];
    ze[4]= zv[koi[koffs[i]+3]];
    }

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_QUADS);
      glColor3f (rot[jfarbe[i]],gruen[jfarbe[i]],blau [jfarbe[i]]); 
      for(k= 1; k <= 4; k++)
        glVertex3d(xe[jp7[k]],ye[jp7[k]],ze[jp7[k]]);
    glEnd();
    }  /* Scheibe 7,11, Torus 8,12 und Platte 19 u.20,Schale 23 */

/*----------------------------------------------------------------------
* Scheibe 3, Torus 6, Scheibe 14, Torus 15, Platte 18, Schale 24
*---------------------------------------------------------------------*/
  if(ityp[i] == 3  || ityp[i] == 14 || 
     ityp[i] == 6  || ityp[i] == 15 ||
     ityp[i] == 18 || ityp[i] == 24)
    {       

/*======================================================================
* die drei Eck-Punkte fuer jede Scheibe oder Platte holen
*=====================================================================*/
  for (j= 1; j <= 3; j++)
    {
    xe[j]= xv[koi[koffs[i]+j-1]];
    ye[j]= yv[koi[koffs[i]+j-1]];
    ze[j]= zv[koi[koffs[i]+j-1]];
    }

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_TRIANGLES);
      glColor3f (rot[jfarbe[i]],gruen[jfarbe[i]],blau [jfarbe[i]]); 
      for(k= 1; k <= 3; k++)
        glVertex3d(xe[jp7[k]],ye[jp7[k]],ze[jp7[k]]);
    glEnd();
    }  /* Scheibe 3,14, Torus 6,15, Platte 18, Schale 24 */

/*----------------------------------------------------------------------
* Tetraeder 16 und 17
*---------------------------------------------------------------------*/
  if(ityp[i] == 16 || ityp[i] == 17)
    {       

/*======================================================================
* die vier Eck-Punkte fuer jeden Tetraeder holen
*=====================================================================*/
    for (j= 1; j <= 4; j++)
      {
      xe[j]= xv[koi[koffs[i]+j-1]];
      ye[j]= yv[koi[koffs[i]+j-1]];
      ze[j]= zv[koi[koffs[i]+j-1]];
      }

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_TRIANGLES);
      glColor3f (rot[jfarbe[i]],gruen[jfarbe[i]],blau [jfarbe[i]]); 
      for(k= 1; k <= 12; k++)
        glVertex3d(xe[jp16[k]],ye[jp16[k]],ze[jp16[k]]);
    glEnd();
    }  /* Ende Tetraeder 16 und 17 */

/*----------------------------------------------------------------------
* Hexaeder 1, 10 und 21
*---------------------------------------------------------------------*/
  if(ityp[i] == 1 || ityp[i] == 10 || ityp[i] == 21)
    {       
/*======================================================================
* die acht Punkte fuer jeden Hexaeder holen
*=====================================================================*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Hexaeder 1 und 10: die 8 Eckknoten
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(ityp[i] == 1 || ityp[i] == 10)
      {
      for (j= 1; j <= 8; j++)
        {
        xe[j]= xv[koi[koffs[i]+j-1]];
        ye[j]= yv[koi[koffs[i]+j-1]];
        ze[j]= zv[koi[koffs[i]+j-1]];
        }
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Volumenschalenele. 21: die 8 Eckknoten
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(ityp[i] == 21)
      {
      for (j= 1; j <= 4; j++)
        {
        xe[j]= xv[koi[koffs[i]+j-1]];
        ye[j]= yv[koi[koffs[i]+j-1]];
        ze[j]= zv[koi[koffs[i]+j-1]];
        }
      for (j= 5; j <= 8; j++)
        {
        xe[j]= xv[koi[koffs[i]+j+4-1]];
        ye[j]= yv[koi[koffs[i]+j+4-1]];
        ze[j]= zv[koi[koffs[i]+j+4-1]];
        }
      }

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_TRIANGLES);
      glColor3f (rot[jfarbe[i]],gruen[jfarbe[i]],blau [jfarbe[i]]); 
      for(k= 1; k <= 36; k++)
        glVertex3d(xe[jp10[k]],ye[jp10[k]],ze[jp10[k]]);
    glEnd();
    }  /* Ende Hexaeder 1, 10 und 21 */

/*----------------------------------------------------------------------
* Volumenschale 22
*---------------------------------------------------------------------*/
  if(ityp[i] == 22)
    {       
    for (j= 1; j <= 3; j++)
      {
      xe[j]= xv[koi[koffs[i]+j-1]];
      ye[j]= yv[koi[koffs[i]+j-1]];
      ze[j]= zv[koi[koffs[i]+j-1]];
      }
    for (j= 4; j <= 6; j++)
      {
      xe[j]= xv[koi[koffs[i]+j+3-1]];
      ye[j]= yv[koi[koffs[i]+j+3-1]];
      ze[j]= zv[koi[koffs[i]+j+3-1]];
      }

/*======================================================================
* ... und rendern
*=====================================================================*/
    glBegin(GL_TRIANGLES);
      glColor3f (rot[jfarbe[i]],gruen[jfarbe[i]],blau [jfarbe[i]]); 
      for(k= 1; k <= 24; k++)
        glVertex3d(xe[jp22[k]],ye[jp22[k]],ze[jp22[k]]);
    glEnd();
    }  /* Ende Volumenschale 22 */


  }  /* Ende Schleife ueber alle Elemente */

return 0;
}

