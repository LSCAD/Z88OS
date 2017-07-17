/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows & UNIX OS.
*
* Composed and edited and copyright by 
* Professor Dr.-Ing. Frank Rieg, University of Bayreuth, Germany
*
* eMail: 
* frank.rieg@uni-bayreuth.de
* dr.frank.rieg@t-online.de
* 
* V15.0  November 15, 2015
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
* fr_gltext3d
* Der Vektorfont fuer Z88V15OS und Z88AURORA
* 18.11.2015
***********************************************************************/
/***********************************************************************
* UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88o.h>
#include <stdio.h> 
#include <stdlib.h>  
#include <string.h>  
#include <GL/gl.h>
#include <GL/glx.h>
#endif

/***********************************************************************
* ...und los
***********************************************************************/
void fr_gltext3d(
  double xt,double yt,double zt,char *ctext,double scale, double dicke)
{
int    i;
size_t ilaeng;
char   c;

ilaeng= strlen(ctext);

glLineWidth(dicke);

for(i= 0; i < ilaeng; i++)
  {
  c= toupper(ctext[i]);
  if(c == 'A')
    {
    glBegin(GL_LINES);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glVertex3d(xt+scale*5,yt+scale*1,zt);
    glVertex3d(xt+scale*2,yt+scale*4,zt);
    glVertex3d(xt+scale*4,yt+scale*4,zt);
    glEnd();
    xt+= scale*5 + 0.2;
    continue;
    }

  if(c == 'B')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*6,zt);
    glVertex3d(xt+scale*4,yt+scale*5,zt);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glVertex3d(xt+scale*4,yt+scale*3,zt);
    glVertex3d(xt+scale*4,yt+scale*2,zt);
    glVertex3d(xt+scale*3,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(xt+scale*1,yt+scale*4,zt);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'C')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*4,yt+scale*2,zt);
    glVertex3d(xt+scale*3,yt+scale*1,zt);
    glVertex3d(xt+scale*2,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*2,zt);
    glVertex3d(xt+scale*1,yt+scale*6,zt);
    glVertex3d(xt+scale*2,yt+scale*7,zt);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*6,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'D')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*6,zt);
    glVertex3d(xt+scale*4,yt+scale*2,zt);
    glVertex3d(xt+scale*3,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'E')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*4,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*7,zt);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(xt+scale*1,yt+scale*4,zt);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'F')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*7,zt);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(xt+scale*1,yt+scale*4,zt);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'G')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*2,yt+scale*4,zt);
    glVertex3d(xt+scale*4,yt+scale*4,zt);
    glVertex3d(xt+scale*4,yt+scale*2,zt);
    glVertex3d(xt+scale*3,yt+scale*1,zt);
    glVertex3d(xt+scale*2,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*2,zt);
    glVertex3d(xt+scale*1,yt+scale*6,zt);
    glVertex3d(xt+scale*2,yt+scale*7,zt);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*6,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'H')
    {
    glBegin(GL_LINES);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*1,zt);
    glVertex3d(xt+scale*4,yt+scale*7,zt);
    glVertex3d(xt+scale*1,yt+scale*4,zt);
    glVertex3d(xt+scale*4,yt+scale*4,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'I')
    {
    glBegin(GL_LINES);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glVertex3d(xt+scale*3,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glVertex3d(xt+scale*2,yt+scale*1,zt);
    glVertex3d(xt+scale*2,yt+scale*7,zt);
    glEnd();
    xt+= scale*3 + 0.2;
    continue;
    }

  if(c == 'J')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*1,yt+scale*2,zt);
    glVertex3d(xt+scale*2,yt+scale*1,zt);
    glVertex3d(xt+scale*3,yt+scale*1,zt);
    glVertex3d(xt+scale*4,yt+scale*2,zt);
    glVertex3d(xt+scale*4,yt+scale*7,zt);
    glVertex3d(xt+scale*2,yt+scale*7,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'K')
    {
    glBegin(GL_LINES);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*1,yt+scale*4,zt);
    glVertex3d(xt+scale*4,yt+scale*7,zt);
    glVertex3d(xt+scale*1,yt+scale*4,zt);
    glVertex3d(xt+scale*4,yt+scale*1,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'L')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*4,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'M')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glVertex3d(xt+scale*5,yt+scale*7,zt);
    glVertex3d(xt+scale*5,yt+scale*1,zt);
    glEnd();
    xt+= scale*5 + 0.2;
    continue;
    }

  if(c == 'N')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*1,zt);
    glVertex3d(xt+scale*4,yt+scale*7,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'O')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*4,yt+scale*2,zt);
    glVertex3d(xt+scale*3,yt+scale*1,zt);
    glVertex3d(xt+scale*2,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*2,zt);
    glVertex3d(xt+scale*1,yt+scale*6,zt);
    glVertex3d(xt+scale*2,yt+scale*7,zt);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*6,zt);
    glVertex3d(xt+scale*4,yt+scale*2,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'P')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*6,zt);
    glVertex3d(xt+scale*4,yt+scale*5,zt);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glVertex3d(xt+scale*1,yt+scale*4,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'Q')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*4,yt+scale*2,zt);
    glVertex3d(xt+scale*3,yt+scale*1,zt);
    glVertex3d(xt+scale*2,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*2,zt);
    glVertex3d(xt+scale*1,yt+scale*6,zt);
    glVertex3d(xt+scale*2,yt+scale*7,zt);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*6,zt);
    glVertex3d(xt+scale*4,yt+scale*2,zt);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(xt+scale*2,yt+scale*3,zt);
    glVertex3d(xt+scale*4,yt+scale*1,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'R')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*6,zt);
    glVertex3d(xt+scale*4,yt+scale*5,zt);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glVertex3d(xt+scale*1,yt+scale*4,zt);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glVertex3d(xt+scale*4,yt+scale*1,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'S')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*1,yt+scale*2,zt);
    glVertex3d(xt+scale*2,yt+scale*1,zt);
    glVertex3d(xt+scale*3,yt+scale*1,zt);
    glVertex3d(xt+scale*4,yt+scale*2,zt);
    glVertex3d(xt+scale*4,yt+scale*3,zt);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glVertex3d(xt+scale*2,yt+scale*4,zt);
    glVertex3d(xt+scale*1,yt+scale*5,zt);
    glVertex3d(xt+scale*1,yt+scale*6,zt);
    glVertex3d(xt+scale*2,yt+scale*7,zt);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*6,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'T')
    {
    glBegin(GL_LINES);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*7,zt);
    glVertex3d(xt+scale*2.5,yt+scale*1,zt);
    glVertex3d(xt+scale*2.5,yt+scale*7,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'U')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*1,yt+scale*2,zt);
    glVertex3d(xt+scale*2,yt+scale*1,zt);
    glVertex3d(xt+scale*3,yt+scale*1,zt);
    glVertex3d(xt+scale*4,yt+scale*2,zt);
    glVertex3d(xt+scale*4,yt+scale*7,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'V')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*2.5,yt+scale*1,zt);
    glVertex3d(xt+scale*4,yt+scale*7,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'W')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*2,yt+scale*1,zt);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glVertex3d(xt+scale*4,yt+scale*1,zt);
    glVertex3d(xt+scale*5,yt+scale*7,zt);
    glEnd();
    xt+= scale*5 + 0.2;
    continue;
    }

  if(c == 'X')
    {
    glBegin(GL_LINES);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glVertex3d(xt+scale*4,yt+scale*7,zt);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*1,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'Y')
    {
    glBegin(GL_LINES);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*2.5,yt+scale*4,zt);
    glVertex3d(xt+scale*4,yt+scale*7,zt);
    glVertex3d(xt+scale*2.5,yt+scale*4,zt);
    glVertex3d(xt+scale*2.5,yt+scale*4,zt);
    glVertex3d(xt+scale*2.5,yt+scale*1,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == 'Z')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*7,zt);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glVertex3d(xt+scale*4,yt+scale*1,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == '+')
    {
    glBegin(GL_LINES);
    glVertex3d(xt+scale*1,yt+scale*4,zt);
    glVertex3d(xt+scale*4,yt+scale*4,zt);
    glVertex3d(xt+scale*2.5,yt+scale*2,zt);
    glVertex3d(xt+scale*2.5,yt+scale*6,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == '-')
    {
    glBegin(GL_LINES);
    glVertex3d(xt+scale*1,yt+scale*4,zt);
    glVertex3d(xt+scale*4,yt+scale*4,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == ' ')
    {
    xt+= scale*3 + 0.2;
    continue;
    }

  if(c == '1')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*1,yt+scale*6,zt);
    glVertex3d(xt+scale*2,yt+scale*7,zt);
    glVertex3d(xt+scale*2,yt+scale*1,zt);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glVertex3d(xt+scale*3,yt+scale*1,zt);
    glEnd();
    xt+= scale*3 + 0.2;
    continue;
    }

  if(c == '2')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*1,yt+scale*5,zt);
    glVertex3d(xt+scale*1,yt+scale*6,zt);
    glVertex3d(xt+scale*2,yt+scale*7,zt);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*6,zt);
    glVertex3d(xt+scale*4,yt+scale*5,zt);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glVertex3d(xt+scale*4,yt+scale*1,zt);
    glVertex3d(xt+scale*4,yt+scale*2,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == '3')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*1,yt+scale*5,zt);
    glVertex3d(xt+scale*1,yt+scale*6,zt);
    glVertex3d(xt+scale*2,yt+scale*7,zt);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*6,zt);
    glVertex3d(xt+scale*4,yt+scale*5,zt);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glVertex3d(xt+scale*2,yt+scale*4,zt);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glVertex3d(xt+scale*4,yt+scale*3,zt);
    glVertex3d(xt+scale*4,yt+scale*2,zt);
    glVertex3d(xt+scale*3,yt+scale*1,zt);
    glVertex3d(xt+scale*2,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*2,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == '4')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*3,yt+scale*1,zt);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glVertex3d(xt+scale*1,yt+scale*3,zt);
    glVertex3d(xt+scale*4,yt+scale*3,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == '5')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*4,yt+scale*7,zt);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*1,yt+scale*4,zt);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glVertex3d(xt+scale*4,yt+scale*3,zt);
    glVertex3d(xt+scale*4,yt+scale*2,zt);
    glVertex3d(xt+scale*3,yt+scale*1,zt);
    glVertex3d(xt+scale*2,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*2,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == '6')
    {
    glBegin(GL_LINES);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glVertex3d(xt+scale*1,yt+scale*3,zt);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glVertex3d(xt+scale*4,yt+scale*3,zt);
    glVertex3d(xt+scale*4,yt+scale*2,zt);
    glVertex3d(xt+scale*3,yt+scale*1,zt);
    glVertex3d(xt+scale*2,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*2,zt);
    glVertex3d(xt+scale*1,yt+scale*3,zt);
    glVertex3d(xt+scale*2,yt+scale*4,zt);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == '7')
    {
    glBegin(GL_LINES);
    glVertex3d(xt+scale*2,yt+scale*4,zt);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*1,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*7,zt);
    glVertex3d(xt+scale*2,yt+scale*1,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == '8')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glVertex3d(xt+scale*4,yt+scale*5,zt);
    glVertex3d(xt+scale*4,yt+scale*6,zt);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glVertex3d(xt+scale*2,yt+scale*7,zt);
    glVertex3d(xt+scale*1,yt+scale*6,zt);
    glVertex3d(xt+scale*1,yt+scale*5,zt);
    glVertex3d(xt+scale*2,yt+scale*4,zt);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glVertex3d(xt+scale*4,yt+scale*3,zt);
    glVertex3d(xt+scale*4,yt+scale*2,zt);
    glVertex3d(xt+scale*3,yt+scale*1,zt);
    glVertex3d(xt+scale*2,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*2,zt);
    glVertex3d(xt+scale*1,yt+scale*3,zt);
    glVertex3d(xt+scale*2,yt+scale*4,zt);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == '9')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glVertex3d(xt+scale*4,yt+scale*5,zt);
    glVertex3d(xt+scale*4,yt+scale*6,zt);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glVertex3d(xt+scale*2,yt+scale*7,zt);
    glVertex3d(xt+scale*1,yt+scale*6,zt);
    glVertex3d(xt+scale*1,yt+scale*5,zt);
    glVertex3d(xt+scale*2,yt+scale*4,zt);
    glVertex3d(xt+scale*3,yt+scale*4,zt);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(xt+scale*4,yt+scale*5,zt);
    glVertex3d(xt+scale*2,yt+scale*1,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == '0')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*4,yt+scale*2,zt);
    glVertex3d(xt+scale*3,yt+scale*1,zt);
    glVertex3d(xt+scale*2,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*2,zt);
    glVertex3d(xt+scale*1,yt+scale*6,zt);
    glVertex3d(xt+scale*2,yt+scale*7,zt);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glVertex3d(xt+scale*4,yt+scale*6,zt);
    glVertex3d(xt+scale*4,yt+scale*2,zt);
    glEnd();
    glBegin(GL_LINES);
    glVertex3d(xt+scale*4,yt+scale*6,zt);
    glVertex3d(xt+scale*1,yt+scale*2,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == '.')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*1.5,zt);
    glVertex3d(xt+scale*1.5,yt+scale*1.5,zt);
    glVertex3d(xt+scale*1.5,yt+scale*1,zt);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glEnd();
    xt+= scale*1.5 + 0.2;
    continue;
    }

  if(c == '*')
    {
    glBegin(GL_LINES);
    glVertex3d(xt+scale*1,yt+scale*2.5,zt);
    glVertex3d(xt+scale*4,yt+scale*5.5,zt);
    glVertex3d(xt+scale*1,yt+scale*5.5,zt);
    glVertex3d(xt+scale*4,yt+scale*2.5,zt);
    glVertex3d(xt+scale*2.5,yt+scale*2,zt);
    glVertex3d(xt+scale*2.5,yt+scale*6,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  if(c == '/')
    {
    glBegin(GL_LINES);
    glVertex3d(xt+scale*1,yt+scale*1,zt);
    glVertex3d(xt+scale*3,yt+scale*7,zt);
    glEnd();
    xt+= scale*3 + 0.2;
    continue;
    }

  if(c == '=')
    {
    glBegin(GL_LINES);
    glVertex3d(xt+scale*1,yt+scale*3.5,zt);
    glVertex3d(xt+scale*4,yt+scale*3.5,zt);
    glVertex3d(xt+scale*1,yt+scale*4.5,zt);
    glVertex3d(xt+scale*4,yt+scale*4.5,zt);
    glEnd();
    xt+= scale*3 + 0.2;
    continue;
    }

  if(c == '~')
    {
    glBegin(GL_LINE_STRIP);
    glVertex3d(xt+scale*1,yt+scale*4,zt);
    glVertex3d(xt+scale*3,yt+scale*6,zt);
    glVertex3d(xt+scale*5,yt+scale*2,zt);
    glVertex3d(xt+scale*7,yt+scale*4,zt);
    glEnd();
    xt+= scale*4 + 0.2;
    continue;
    }

  }

return;
}


