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
*  Diese Compilereinheit enthaelt Functions fuer das Font-Management
*  im OpenGL- Programm Z88O. Sie sind dem Buch OpenGL SuperBible von
*  Richard S. Wright und Michael Sweet entnommen:
*  FontCreate
*  FontDelete
*  FontPuts
*  17.7.2011 RIEG
***********************************************************************/

/***********************************************************************
* Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88o.h>
#include <windows.h>
#include <commctrl.h>
#include <gl\gl.h>
#include <string.h>  /* strcpy,sprintf */
#include <stdio.h>   /* fopen, fprintf, fclose */
#include <math.h>    /* fabs */
#endif

/**********************************************************
* Font- Structure GLFONT
**********************************************************/
typedef struct
    {
    GLuint base;        /* DisplayList Nr.erstes Zeichen */
    int    widths[256]; /* Zeichenweite in Pixels */
    int    height;      /* Zeichenhoehe */
    } GLFONT;

/***********************************************************************
* FontCreate
***********************************************************************/
GLFONT * FontCreate(HDC hdc,const char *typeface,
                    int height,int weight,DWORD italic)
  {
  GLFONT *font;
  HFONT   fontid;
  int     charset;

  if((font= calloc(1,sizeof(GLFONT)))== (GLFONT *)0)
    return((GLFONT *)0);

  if((font->base= glGenLists(256))== 0)
    {
    free(font);
    return (0);
    }

  charset= ANSI_CHARSET;

  fontid= CreateFont(height, 0, 0, 0, weight, italic, FALSE, FALSE,
                     charset, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
                     DRAFT_QUALITY, DEFAULT_PITCH, typeface);

  SelectObject(hdc,fontid);

  wglUseFontBitmaps(hdc,0,256,font->base);

  GetCharWidth(hdc,0,255,font->widths);
  font->height = height;

  return (font);
  }

/**********************************************************
* FontDelete
**********************************************************/
void FontDelete(GLFONT *font)
  {
  if(font== (GLFONT *)0)
    return;

  glDeleteLists(font->base,256);
  free(font);
  }

/**********************************************************
* FontPuts
**********************************************************/
void FontPuts(GLFONT *font,const char *cs)
  {
  if (font== (GLFONT *)0 || cs== NULL) return;

  glPushAttrib(GL_LIST_BIT);
  glListBase(font->base);
  glCallLists(strlen(cs),GL_UNSIGNED_BYTE,cs);
  glPopAttrib();
  }



