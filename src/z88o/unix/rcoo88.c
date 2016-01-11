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
* RCOO88 fuer UNIX: Farben einlesen fuer Z88O
* 31.7.2011 Rieg
***********************************************************************/
/***********************************************************************
* UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88o.h>
#include <stdio.h>   /* fopen,fclose,fgets */
#include <string.h>  /* strstr */
#include <GL/gl.h>
#endif

/***********************************************************************
* Leseformate
* Achtung: Fuer das hier vorkommende %f (float) ist nichts zu tun!
***********************************************************************/
#ifdef FR_XDOUB
#define PG "%lg"
#endif

#ifdef FR_XQUAD
#define PG "%Lg"
#endif

/***********************************************************************
* Functions
***********************************************************************/
int wlog88o(FR_INT4,int);

/***********************************************************************
* Start rcoo88
***********************************************************************/
int rcoo88(void)
{

FILE *fcol;

extern FR_DOUBLE fycor,fazoo;

extern GLfloat   back_col[];
extern GLfloat   rot[], gruen[], blau[];
extern GLfloat   specula0[], diffuse0[], ambient0[], positio0[];
extern GLfloat   specula1[], diffuse1[], ambient1[], positio1[];
extern GLfloat   specula2[], diffuse2[], ambient2[], positio2[];
extern GLfloat   diff_mat[], spec_mat[], shine[];
extern GLfloat   hide_col[];
extern GLfloat   hide_off[];
extern GLfloat   node_col[];
extern GLfloat   elem_col[];
extern GLfloat   bline;

extern int       IW_DRAWAR,IH_DRAWAR;  

extern char      CBROWSER[],CPREFIX[],CPANGO_FONT[],CPANGO_SIZE[];

float            f0,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11;

char             cline[256], cdummy[80];

/*----------------------------------------------------------------------
* Color- datei z88.fcd oeffnen
*---------------------------------------------------------------------*/
fcol= fopen("z88.fcd","rb"); /* fcd = fonts, colors, dimensions       */

if(fcol == NULL)
  {
  wlog88o(0,LOG_NOFCD);
  return(AL_NOFCD);
  }
rewind(fcol);

/*----------------------------------------------------------------------
* Color-Datei z88.fcd lesen: Z88COM
*---------------------------------------------------------------------*/
do
  if(fgets(cline,256,fcol)== NULL) break;
while( (strstr(cline,"Z88COM START"))== NULL);

if( (strstr(cline,"Z88COM START"))!= NULL) 
  {
  do
    {
    fgets(cline,80,fcol);
/*======================================================================
* Z88COM: WINDOW START
*=====================================================================*/
    if( (strstr(cline,"WINDOW START"))!= NULL) 
      {
      do
        {
        fgets(cline,80,fcol);
        if( (strstr(cline,"CBROWSER"))!= NULL) 
          sscanf(cline,"%s %s",cdummy,CBROWSER);
        if( (strstr(cline,"CPREFIX"))!= NULL) 
          sscanf(cline,"%s %s",cdummy,CPREFIX);
        }
      while( (strstr(cline,"WINDOW END"))== NULL);
      }         
    }
  while( (strstr(cline,"Z88COM END"))== NULL);     
  }

else
  {
  wlog88o(0,LOG_WRONGFCD);
  return(AL_WRONGFCD);
  }
  
/*----------------------------------------------------------------------
* Color-Datei z88.fcd lesen: Z88O
*---------------------------------------------------------------------*/
do
  if(fgets(cline,256,fcol)== NULL) break;
while( (strstr(cline,"Z88O START"))== NULL);

if( (strstr(cline,"Z88O START"))!= NULL)              /* File */
  {
  do
    {
    fgets(cline,80,fcol);

/*======================================================================
* Z88O: WINDOW START
*=====================================================================*/
    if( (strstr(cline,"WINDOW START"))!= NULL) 
      {
      do
        {
        fgets(cline,80,fcol);

        if( (strstr(cline,"IW_DRAWAR"))!= NULL) 
          sscanf(cline,"%s %d",cdummy,&IW_DRAWAR);
        if( (strstr(cline,"IH_DRAWAR"))!= NULL) 
          sscanf(cline,"%s %d",cdummy,&IH_DRAWAR);
        if( (strstr(cline,"PANGO_FONT"))!= NULL) 
          sscanf(cline,"%s %s",cdummy,CPANGO_FONT);
        if( (strstr(cline,"PANGO_SIZE"))!= NULL) 
          sscanf(cline,"%s %s",cdummy,CPANGO_SIZE);
        }
      while( (strstr(cline,"WINDOW END"))== NULL);
      }         

/*======================================================================
* OpenGL
*=====================================================================*/
    if( (strstr(cline,"OPENGL START"))!= NULL)            /* File */
      {
      do
        {
        fgets(cline,240,fcol);

        if( (strstr(cline,"DEFAULT START"))!= NULL)       /* Standards */
          {
          do
            {
            fgets(cline,240,fcol);
            if( (strstr(cline,"FYCOR"))!= NULL)           /*  Korrektur */ 
              {
              sscanf(cline,"%s " PG,cdummy,&fycor);
              }
            if( (strstr(cline,"COLOR"))!= NULL)           /*  H-Farbe */ 
              {
              sscanf(cline,"%s %f %f %f %f",cdummy,&f0,&f1,&f2,&f3);
              back_col[0] = (GLfloat)f0;
              back_col[1] = (GLfloat)f1;
              back_col[2] = (GLfloat)f2; 
              back_col[3] = (GLfloat)f3; 
              }
            if( (strstr(cline,"FAZOO"))!= NULL)           /*  Punktgroesse RBD */ 
              {
              sscanf(cline,"%s " PG,cdummy,&fazoo);
              }
            }
          while( (strstr(cline,"DEFAULT END"))== NULL);
          }                                               /*DEFAULT END */

        if( (strstr(cline,"STRESS START"))!= NULL)        /* Spannungen */
          {
          do
            {
            fgets(cline,240,fcol);
            if( (strstr(cline,"RED"))!= NULL)             /*  rot */ 
              {
              sscanf(cline,"%s %f %f %f %f %f %f %f %f %f %f %f %f",
              cdummy,&f0,&f1,&f2,&f3,&f4,&f5,&f6,&f7,&f8,&f9,&f10,&f11);
              rot[0] = (GLfloat)f0;
              rot[1] = (GLfloat)f1;
              rot[2] = (GLfloat)f2; 
              rot[3] = (GLfloat)f3; 
              rot[4] = (GLfloat)f4; 
              rot[5] = (GLfloat)f5;    
              rot[6] = (GLfloat)f6;
              rot[7] = (GLfloat)f7; 
              rot[8] = (GLfloat)f8;  
              rot[9] = (GLfloat)f9;
              rot[10]= (GLfloat)f10; 
              rot[11]= (GLfloat)f11;  
              }
            if( (strstr(cline,"GREEN"))!= NULL)           /*  gruen */ 
              {
              sscanf(cline,"%s %f %f %f %f %f %f %f %f %f %f %f %f",
              cdummy,&f0,&f1,&f2,&f3,&f4,&f5,&f6,&f7,&f8,&f9,&f10,&f11);
              gruen[0] = (GLfloat)f0;
              gruen[1] = (GLfloat)f1;
              gruen[2] = (GLfloat)f2; 
              gruen[3] = (GLfloat)f3; 
              gruen[4] = (GLfloat)f4; 
              gruen[5] = (GLfloat)f5;    
              gruen[6] = (GLfloat)f6;
              gruen[7] = (GLfloat)f7; 
              gruen[8] = (GLfloat)f8;  
              gruen[9] = (GLfloat)f9;
              gruen[10]= (GLfloat)f10; 
              gruen[11]= (GLfloat)f11;  
              }
            if( (strstr(cline,"BLUE"))!= NULL)           /*  blau */ 
              {
              sscanf(cline,"%s %f %f %f %f %f %f %f %f %f %f %f %f",
              cdummy,&f0,&f1,&f2,&f3,&f4,&f5,&f6,&f7,&f8,&f9,&f10,&f11);
              blau[0] = (GLfloat)f0;
              blau[1] = (GLfloat)f1;
              blau[2] = (GLfloat)f2; 
              blau[3] = (GLfloat)f3; 
              blau[4] = (GLfloat)f4; 
              blau[5] = (GLfloat)f5;    
              blau[6] = (GLfloat)f6;
              blau[7] = (GLfloat)f7; 
              blau[8] = (GLfloat)f8;  
              blau[9] = (GLfloat)f9;
              blau[10]= (GLfloat)f10; 
              blau[11]= (GLfloat)f11;  
              }
            }
          while( (strstr(cline,"STRESS END"))== NULL);
          }                                             /* endif STRESS START */

        if( (strstr(cline,"LIGHT0 START"))!= NULL)      /* Licht 0 */
          {
          do
            {
            fgets(cline,240,fcol);
            if( (strstr(cline,"SPECULA0"))!= NULL)      /*  specular0 */ 
              {
              sscanf(cline,"%s %f %f %f %f",
              cdummy,&f0,&f1,&f2,&f3);
              specula0[0] = (GLfloat)f0;
              specula0[1] = (GLfloat)f1;
              specula0[2] = (GLfloat)f2; 
              specula0[3] = (GLfloat)f3; 
              }
            if( (strstr(cline,"DIFFUSE0"))!= NULL)      /*  diffuse0 */ 
              {
              sscanf(cline,"%s %f %f %f %f",
              cdummy,&f0,&f1,&f2,&f3);
              diffuse0[0] = (GLfloat)f0;
              diffuse0[1] = (GLfloat)f1;
              diffuse0[2] = (GLfloat)f2; 
              diffuse0[3] = (GLfloat)f3; 
              }
            if( (strstr(cline,"AMBIENT0"))!= NULL)      /*  diffuse0 */ 
              {
              sscanf(cline,"%s %f %f %f %f",
              cdummy,&f0,&f1,&f2,&f3);
              ambient0[0] = (GLfloat)f0;
              ambient0[1] = (GLfloat)f1;
              ambient0[2] = (GLfloat)f2; 
              ambient0[3] = (GLfloat)f3; 
              }
            if( (strstr(cline,"POSITIO0"))!= NULL)      /*  positio0 */ 
              {
              sscanf(cline,"%s %f %f %f %f",
              cdummy,&f0,&f1,&f2,&f3);
              positio0[0] = (GLfloat)f0;
              positio0[1] = (GLfloat)f1;
              positio0[2] = (GLfloat)f2; 
              positio0[3] = (GLfloat)f3; 
              }
            }
          while( (strstr(cline,"LIGHT0 END"))== NULL);   /* endif LIGHT 0 END */
          }      

        if( (strstr(cline,"LIGHT1 START"))!= NULL)      /* Licht 1 */
          {
          do
            {
            fgets(cline,240,fcol);
            if( (strstr(cline,"SPECULA1"))!= NULL)      /*  specular1 */ 
              {
              sscanf(cline,"%s %f %f %f %f",
              cdummy,&f0,&f1,&f2,&f3);
              specula1[0] = (GLfloat)f0;
              specula1[1] = (GLfloat)f1;
              specula1[2] = (GLfloat)f2; 
              specula1[3] = (GLfloat)f3; 
              }
            if( (strstr(cline,"DIFFUSE1"))!= NULL)      /*  diffuse1 */ 
              {
              sscanf(cline,"%s %f %f %f %f",
              cdummy,&f0,&f1,&f2,&f3);
              diffuse1[0] = (GLfloat)f0;
              diffuse1[1] = (GLfloat)f1;
              diffuse1[2] = (GLfloat)f2; 
              diffuse1[3] = (GLfloat)f3; 
              }
            if( (strstr(cline,"AMBIENT1"))!= NULL)      /*  diffuse1 */ 
              {
              sscanf(cline,"%s %f %f %f %f",
              cdummy,&f0,&f1,&f2,&f3);
              ambient1[0] = (GLfloat)f0;
              ambient1[1] = (GLfloat)f1;
              ambient1[2] = (GLfloat)f2; 
              ambient1[3] = (GLfloat)f3; 
              }
            if( (strstr(cline,"POSITIO1"))!= NULL)      /*  positio1 */ 
              {
              sscanf(cline,"%s %f %f %f %f",
              cdummy,&f0,&f1,&f2,&f3);
              positio1[0] = (GLfloat)f0;
              positio1[1] = (GLfloat)f1;
              positio1[2] = (GLfloat)f2; 
              positio1[3] = (GLfloat)f3; 
              }
            }
          while( (strstr(cline,"LIGHT1 END"))== NULL);   /* endif LIGHT 1 END */
          }      

        if( (strstr(cline,"LIGHT2 START"))!= NULL)      /* Licht 2, Spot */
          {
          do
            {
            fgets(cline,240,fcol);
            if( (strstr(cline,"SPECULA2"))!= NULL)      /*  specular2 */ 
              {
              sscanf(cline,"%s %f %f %f %f",
              cdummy,&f0,&f1,&f2,&f3);
              specula2[0] = (GLfloat)f0;
              specula2[1] = (GLfloat)f1;
              specula2[2] = (GLfloat)f2; 
              specula2[3] = (GLfloat)f3; 
              }
            if( (strstr(cline,"POSITIO2"))!= NULL)      /*  positio2 */ 
              {
              sscanf(cline,"%s %f %f %f %f",
              cdummy,&f0,&f1,&f2,&f3);
              positio2[0] = (GLfloat)f0;
              positio2[1] = (GLfloat)f1;
              positio2[2] = (GLfloat)f2; 
              positio2[3] = (GLfloat)f3; 
              }
            }
          while( (strstr(cline,"LIGHT2 END"))== NULL);   /* endif LIGHT 2 END */
          }      

        if( (strstr(cline,"MAT START"))!= NULL)          /* Material */
          {
          do
            {
            fgets(cline,240,fcol);
            if( (strstr(cline,"DIFF_MA"))!= NULL)        /*  diff_mat */ 
              {
              sscanf(cline,"%s %f %f %f %f",
              cdummy,&f0,&f1,&f2,&f3);
              diff_mat[0] = (GLfloat)f0;
              diff_mat[1] = (GLfloat)f1;
              diff_mat[2] = (GLfloat)f2; 
              diff_mat[3] = (GLfloat)f3; 
              }
            if( (strstr(cline,"SPEC_MA"))!= NULL)        /*  spec_mat */ 
              {
              sscanf(cline,"%s %f %f %f %f",
              cdummy,&f0,&f1,&f2,&f3);
              spec_mat[0] = (GLfloat)f0;
              spec_mat[1] = (GLfloat)f1;
              spec_mat[2] = (GLfloat)f2; 
              spec_mat[3] = (GLfloat)f3; 
              }
            if( (strstr(cline,"SHINING"))!= NULL)        /*  shine */ 
              {
              sscanf(cline,"%s %f",cdummy,&f0);
              shine[0] = (GLfloat)f0;
              }
            }
          while( (strstr(cline,"MAT END"))== NULL);      /* MAT END */
          }   

        if( (strstr(cline,"HIDDENLINE START"))!= NULL)   /* Hidden Line */
          {
          do
            {
            fgets(cline,240,fcol);
            if( (strstr(cline,"COLOR"))!= NULL)           /*  Farbe */ 
              {
              sscanf(cline,"%s %f %f %f",cdummy,&f0,&f1,&f2);
              hide_col[0] = (GLfloat)f0;
              hide_col[1] = (GLfloat)f1;
              hide_col[2] = (GLfloat)f2; 
              }
            if( (strstr(cline,"OFFSET"))!= NULL)          /*  Polygon Offset */ 
              {
              sscanf(cline,"%s %f %f",cdummy,&f0,&f1);
              hide_off[0] = (GLfloat)f0;
              hide_off[1] = (GLfloat)f1;
              }
            if( (strstr(cline,"LINEWI"))!= NULL)          /*  Polygon Offset */ 
              {
              sscanf(cline,"%s %f",cdummy,&f0);
              bline = (GLfloat)f0;
              }
            }
          while( (strstr(cline,"HIDDENLINE END"))== NULL);
          }                                              /* HIDDENLINE END */
   
        if( (strstr(cline,"LABEL START"))!= NULL)        /* Knoten, Elemente */
          {
          do
            {
            fgets(cline,240,fcol);
            if( (strstr(cline,"NODES"))!= NULL)          /*  Farbe */ 
              {
              sscanf(cline,"%s %f %f %f",cdummy,&f0,&f1,&f2);
              node_col[0] = (GLfloat)f0;
              node_col[1] = (GLfloat)f1;
              node_col[2] = (GLfloat)f2; 
              }
            if( (strstr(cline,"ELEMENTS"))!= NULL)       /*  Farbe */ 
              {
              sscanf(cline,"%s %f %f %f",cdummy,&f0,&f1,&f2);
              elem_col[0] = (GLfloat)f0;
              elem_col[1] = (GLfloat)f1;
              elem_col[2] = (GLfloat)f2; 
              }
            }
          while( (strstr(cline,"LABEL END"))== NULL);
          }                                              /* LABEL END */
   
        }
      while( (strstr(cline,"OPENGL END"))== NULL);     
      }
    }
  while( (strstr(cline,"Z88O END"))== NULL);     
  }             

else
  {
  wlog88o(0,LOG_WRONGFCD);
  return(AL_WRONGFCD);
  }  

/*----------------------------------------------------------------------
* korrekt gelesen, file fcol schliessen
*---------------------------------------------------------------------*/
fclose(fcol);
return (0);
}
