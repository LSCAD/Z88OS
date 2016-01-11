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
/*****************************************************************************
* Callbacks fuer z88o
* 31.7.2011 Rieg
*****************************************************************************/

/*****************************************************************************
* Includes
*****************************************************************************/
/*----------------------------------------------------------------------------
* UNIX
*---------------------------------------------------------------------------*/
#ifdef FR_UNIX
#include <z88o.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtkgl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

/***********************************************************************
* Leseformate
***********************************************************************/
#ifdef FR_XINT
#define PD "%d"
#endif

#ifdef FR_XLONG
#define PD "%ld"
#endif

#ifdef FR_XLOLO
#define PD "%lld"
#endif

/*****************************************************************************
* Functions
*****************************************************************************/
int      ri1x88(void);
int      ri2x88(void);
int      ri5x88(void);
int      ro2x88(void);
int      ro5x88(void);
int      ro8x88(void);
int      rcoo88(void);
int      wlog88o(FR_INT4,int);
int      ale88o(int);
int      vu3b88(void);
int      vv3b88(void);
int      vsca88(void);
int      vcur88(void);
int      stro88(void);
int      snow88(void);
int      fvx88(void);
int      fvy88(void);
int      fvz88(void);
int      mko88(void);
int      tet188(void);
int      tet288(void);
int      tet388(void);
int      tet488(void);
int      tet588(void);
int      fsca88(void);
int      fsrb88(void);
int      frbd88(void);
int      malk88(void);
int      mrbd88(void);
int      spgp88(void);
int      magp88(void);
int      vgpc88(void);
int      man88o(void);

/*****************************************************************************
* Function InvalidateRect88 : EXPOSE-Event erzeugen
*****************************************************************************/
void InvalidateRect88(void)
{
extern GtkWidget *DRAWA;
gdk_window_invalidate_rect(GDK_WINDOW(DRAWA->window),NULL,TRUE);
}

/*****************************************************************************
* WMU_CREATE
*****************************************************************************/
void WMU_CREATE(GtkWidget *widget,gpointer data)
{
extern GtkWidget     *DRAWA;
extern PangoFont     *font;
extern char          CF_GRAFICS[];
extern GLuint        font_list_base;

GdkGLContext         *glcontext;
GdkGLDrawable        *gldrawable;
PangoFontDescription *font_desc;

glcontext = gtk_widget_get_gl_context(DRAWA);
gldrawable= gtk_widget_get_gl_drawable(DRAWA);

gdk_gl_drawable_gl_begin(gldrawable,glcontext);

font_list_base = glGenLists (128);
font_desc = pango_font_description_from_string(CF_GRAFICS);

font = gdk_gl_font_use_pango_font(font_desc,0,128,font_list_base);
if(font == NULL)
  {
  ale88o(AL_NO_CF_GRAFICS);
  }
glListBase(font_list_base);
gdk_gl_drawable_gl_end(gldrawable);

return;
}

/*****************************************************************************
* WMU_SIZE
*****************************************************************************/
void WMU_SIZE(GtkWidget *widget,GdkEventConfigure *event,gpointer data)
{
extern GtkWidget *DRAWA;
extern FR_DOUBLE xm,xp,ym,yp,zm,zp,ymsv,ypsv,SV;
extern int       IB,IH;
int              ixClient,iyClient;
GdkGLContext     *glcontext;
GdkGLDrawable    *gldrawable;

glcontext = gtk_widget_get_gl_context(DRAWA);
gldrawable= gtk_widget_get_gl_drawable(DRAWA);

gdk_gl_drawable_gl_begin(gldrawable,glcontext);

ixClient= DRAWA->allocation.width;
iyClient= DRAWA->allocation.height;

IB= ixClient;
IH= iyClient;

SV = (double) IH / (double) IB;
ymsv = ym * SV;
ypsv = yp * SV;

glViewport(0,0,IB,IH);

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho(xm,xp,ymsv,ypsv,zm,zp);

glMatrixMode(GL_MODELVIEW);
gdk_gl_drawable_gl_end(gldrawable);

return;
}

/*****************************************************************************
* CB_MATA
*****************************************************************************/
void CB_MATA(GtkWidget *widget,GdkEvent *event,gpointer data)
{
extern FR_DOUBLE  xx,yy;
extern int        ifmaus;

if( event->motion.state & GDK_BUTTON1_MASK)
  {
  xx= event->motion.x;
  yy= event->motion.y;
  ifmaus= IDM_PAN;
  InvalidateRect88();
  }

if( event->motion.state & GDK_BUTTON2_MASK)
  {
  xx= event->motion.x;
  yy= event->motion.y;
  ifmaus= IDM_ZOOM;
  InvalidateRect88();
  }

if( event->motion.state & GDK_BUTTON3_MASK)
  {
  xx= event->motion.x;
  yy= event->motion.y;
  ifmaus= IDM_ROTATE;
  InvalidateRect88();
  }

return;
}

/*****************************************************************************
* WM_KEY
*****************************************************************************/
void WM_KEY(GtkWidget *button,GdkEventKey *event)
{
extern FR_DOUBLE facx,facy,facz,fzoom,cx,cy,cz,rotx,roty,rotz;
extern FR_DOUBLE xmin,xmax,ymin,ymax,zmin,zmax;
extern FR_INT4 izoom;
extern int ifvcur;
guint key;

key= event->keyval;

if(key == GDK_Prior)
  {
  facx *= fzoom;
  facy *= fzoom;
  facz *= fzoom;
  izoom++;
  InvalidateRect88();
  }

if(key == GDK_Next)
  {
  facx /= fzoom;
  facy /= fzoom;
  facz /= fzoom;
  izoom--;
  InvalidateRect88();
  }

if(key == GDK_Up)
  {
  if(ifvcur == 0) vcur88();
  cy= cy - 0.05*(FR_FABS(ymax) + FR_FABS(ymin))/FR_POW(fzoom,(double)izoom);
  InvalidateRect88();
  }

if(key == GDK_Down)
  {
  if(ifvcur == 0) vcur88();
  cy= cy + 0.05*(FR_FABS(ymax) + FR_FABS(ymin))/FR_POW(fzoom,(double)izoom);
  InvalidateRect88();
  }

if(key == GDK_Right)
  {
  if(ifvcur == 0) vcur88();
  cx= cx - 0.05*(FR_FABS(xmax) + FR_FABS(xmin))/FR_POW(fzoom,(double)izoom);
  InvalidateRect88();
  }

if(key == GDK_Left)
  {
  if(ifvcur == 0) vcur88();
  cx= cx + 0.05*(FR_FABS(xmax) + FR_FABS(xmin))/FR_POW(fzoom,(double)izoom);
  InvalidateRect88();
  }

if(key == GDK_Home)
  {
  if(ifvcur == 0) vcur88();
  cz= cz - 0.05*(FR_FABS(zmax) + FR_FABS(zmin))/FR_POW(fzoom,(double)izoom);
  InvalidateRect88();
  }

if(key == GDK_End)
  {
  if(ifvcur == 0) vcur88();
  cz= cz + 0.05*(FR_FABS(zmax) + FR_FABS(zmin))/FR_POW(fzoom,(double)izoom);
  InvalidateRect88();
  }

if(key == GDK_F2)
  {
  rotx -= 10.;
  if ((int)rotx == -10) rotx= 350.;
  InvalidateRect88();
  }

if(key == GDK_F3)
  {
  rotx += 10.;
  if ((int)rotx == 360) rotx= 0.;
  InvalidateRect88();
  }

if(key == GDK_F4)
  {
  roty -= 10.;
  if ((int)roty == -10) roty= 350.;
  InvalidateRect88();
  }

if(key == GDK_F5)
  {
  roty += 10.;
  if ((int)roty == 360) roty= 0.;
  InvalidateRect88();
  }

if(key == GDK_F6)
  {
  rotz -= 10.;
  if ((int)rotz == -10) rotz= 350.;
  InvalidateRect88();
  }

if(key == GDK_F7)
  {
  rotz += 10.;
  if ((int)rotz == 360) rotz= 0.;
  InvalidateRect88();
  }

if(key == GDK_F8)
  {
  rotx=roty=rotz= 0.;
  InvalidateRect88();
  }

}

/*****************************************************************************
* WMU_DESTROY
*****************************************************************************/
void WMU_DESTROY(GtkWidget *button,gpointer data)
{
gtk_main_quit();
}

/*****************************************************************************
* CB_WER
*****************************************************************************/
void CB_WER(GtkWidget *button,gpointer data)
{
extern FR_INT4 LANG;  
extern         GtkWidget *H_WIN;
extern int     *pp;
extern char    cmess[],cbytes[];
GtkWidget      *MB_WER;

  
if(LANG == 1) strcpy(cmess,"Z88O V14OS fuer UNIX/LINUX\n\
von Univ.Prof.Dr.-Ing. Frank Rieg, Universitaet Bayreuth 2011\n\
frank.rieg@uni-bayreuth.de\nwww.z88.de\n");
if(LANG == 2) strcpy(cmess,"Z88O V14OS for UNIX/LINUX\n\
by Prof.Dr. Frank Rieg, University of Bayreuth, Germany 2011\n\
frank.rieg@uni-bayreuth.de\nwww.z88.de or www.z88.org\n");

#ifdef FR_XQUAD
        sprintf(cbytes,"Floats: %d Bytes\n",(int)sizeof(long double)); 
        strcat(cmess,cbytes);    
#endif
#ifdef FR_XDOUB
        sprintf(cbytes,"Floats: %d Bytes\n",(int)sizeof(double));  
        strcat(cmess,cbytes);   
#endif
#ifdef FR_XINT
        sprintf(cbytes,"Integers: %d Bytes\n",(int)sizeof(int)); 
        strcat(cmess,cbytes);
#endif
#ifdef FR_XLONG
        sprintf(cbytes,"Integers: %d Bytes\n",(int)sizeof(long));  
        strcat(cmess,cbytes); 
#endif
#ifdef FR_XLOLO
        sprintf(cbytes,"Integers: %d Bytes\n",(int)sizeof(long long));
        strcat(cmess,cbytes);   
#endif
        sprintf(cbytes,"Pointers: %d Bytes\n",(int)sizeof(pp));     
        strcat(cmess,cbytes);

MB_WER= gtk_message_dialog_new(GTK_WINDOW(H_WIN),GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO, GTK_BUTTONS_OK,cmess);
gtk_dialog_run(GTK_DIALOG(MB_WER));
gtk_widget_destroy(MB_WER);
}

/*****************************************************************************
* CB_HELP
*****************************************************************************/
void CB_HELP(GtkWidget *button,gpointer data)
{
extern FR_INT4 LANG;
extern int     iret;
extern char    CBROWSER[],CPREFIX[];

char command[320];

strcpy(command,CBROWSER);
strcat(command," ");
strcat(command,CPREFIX);
if(LANG == 1) strcat(command,"z88mang.pdf");
if(LANG == 2) strcat(command,"z88mane.pdf");
iret= system(command);
if(iret != 0) ale88o(AL_NOHELP);
}

/*****************************************************************************
* CB_RUN
*****************************************************************************/
void CB_RUN(GtkWidget *button,gpointer data)
{
extern FILE *fi1;
extern FR_DOUBLE rotx,roty,rotz;
extern FR_INT4 nkp,ne,jkvon,jkbis,jevon,jebis,izoom;
extern int ialert,iflade,iflaver,iflspa,ifscale;
extern char cstrn[];

/*============================================================================
* Urzustand herstellen
*===========================================================================*/
iflaver= ID_NOTLOADVERF;
iflspa = ID_NOTLOADSPANN;
ifscale= IDM_YESSCALE;

rotx= 0.;
roty= 0.;
rotz= 0.;

izoom= 1;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88MAN.TXT lesen --> ibflag,ipflag, Z88I5.TXT pruefen --> iqflag
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
man88o();

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88I1.TXT oeffnen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
fi1= fopen(cstrn,"r");
if(fi1 == NULL)
  {
  wlog88o(0,LOG_NOSTRFI);
  ale88o(AL_NOSTRFI);
  return;
  }
rewind(fi1);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88I1.TXT lesen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
ialert=ri1x88();  
if(ialert != 0) ale88o(ialert);
else            iflade= ID_LOADSTRUC;
        
if(fi1) fclose(fi1); 

jkvon= 1;
jkbis= nkp;
jevon= 1;
jebis= ne;

InvalidateRect88();
}

/*****************************************************************************
* CB_FILE
*****************************************************************************/
void CB_FILE(GtkWidget *button,gpointer data)
{
extern char cstrn[];
extern int iflade,iflaver,iflspa,ifscale;

GtkWidget *FC_DIA;
gint ires;
gchar *cfilename;

FC_DIA= gtk_file_chooser_dialog_new("Filename",NULL,
                                    GTK_FILE_CHOOSER_ACTION_OPEN,
                                    GTK_STOCK_OK,GTK_RESPONSE_OK,
                                    GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
ires= gtk_dialog_run(GTK_DIALOG(FC_DIA));
if(ires == GTK_RESPONSE_OK)
  {
  cfilename= gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(FC_DIA));
  strcpy(cstrn,cfilename);
  iflade = ID_NOTLOADSTRUC;
  iflaver= ID_NOTLOADVERF;
  iflspa = ID_NOTLOADSPANN;
  ifscale= IDM_YESSCALE;
  InvalidateRect88();
  }

gtk_widget_destroy(FC_DIA);
return;
}

/*****************************************************************************
* CB_ASCA
*****************************************************************************/
void CB_ASCA(GtkWidget *button,gpointer data)
{
extern FR_DOUBLE rotx,roty,rotz,s,rx,ry,rz,tx,ty;
extern FR_INT4 izoom;
extern int ifscale;
ifscale = IDM_YESSCALE;
izoom= 1;
rotx= 0.;
roty= 0.;
rotz= 0.;
s   = 1.;
rx  = 0.;
ry  = 0.;
rz  = 0.;
tx  = 0.;
ty  = 0.;
InvalidateRect88();
}

/*****************************************************************************
* CB_MAUS
*****************************************************************************/
void CB_MAUS(GtkWidget *button,gpointer data)
{
extern FR_INT4 LANG;
extern int ifkom;
char cstring[80];

if(ifkom == ID_FUNKEY ) 
  {
  ifkom= ID_MOUSE;
  if(LANG == 1) strcpy(cstring,"* Maus / Tastatur");
  if(LANG == 2) strcpy(cstring,"* Mouse / Keyboard");
  gtk_button_set_label(GTK_BUTTON(button),cstring);
  }
else
  {
  ifkom= ID_FUNKEY;
  if(LANG == 1) strcpy(cstring,"* Tastatur / Maus");
  if(LANG == 2) strcpy(cstring,"* Keyboard / Mouse");
  gtk_button_set_label(GTK_BUTTON(button),cstring);
  }
}

/*****************************************************************************
* CB_UNVER
*****************************************************************************/
void CB_UNVER(GtkWidget *button,gpointer data)
{
extern GtkWidget *PB_UNVER,*PB_VERFO;
extern FR_INT4   LANG;
extern int       ifverf;
char             cstring[80];

ifverf = IDM_UNVERFORMT;

if(LANG == 1) strcpy(cstring,"* unverformt");
if(LANG == 2) strcpy(cstring,"* undeflected");
gtk_button_set_label(GTK_BUTTON(PB_UNVER),cstring);
if(LANG == 1) strcpy(cstring,"verformt");
if(LANG == 2) strcpy(cstring,"deflected");
gtk_button_set_label(GTK_BUTTON(PB_VERFO),cstring);

InvalidateRect88(); 
}

/*****************************************************************************
* CB_VERFO
*****************************************************************************/
void CB_VERFO(GtkWidget *button,gpointer data)
{
extern GtkWidget *PB_UNVER,*PB_VERFO;
extern FR_INT4   LANG;
extern int       ifverf;
char             cstring[80];

ifverf = IDM_VERFORMT;

if(LANG == 1) strcpy(cstring,"unverformt");
if(LANG == 2) strcpy(cstring,"undeflected");
gtk_button_set_label(GTK_BUTTON(PB_UNVER),cstring);
if(LANG == 1) strcpy(cstring,"* verformt");
if(LANG == 2) strcpy(cstring,"* deflected");
gtk_button_set_label(GTK_BUTTON(PB_VERFO),cstring);

InvalidateRect88(); 
}

/*****************************************************************************
* CB_LIGHT
*****************************************************************************/
void CB_LIGHT(GtkWidget *button,gpointer data)
{
extern GtkWidget *PB_LIGHT,*PB_HIDDE,*PB_WIREF,*PB_SSPAN,*PB_SGAUS,*PB_SGAPU;
extern GtkWidget *PB_VX,*PB_VY,*PB_VZ;
extern FR_INT4   LANG;
extern int       if3d;
char             cstring[80];

if3d = IDM_LIGHT; 

if(LANG == 1) strcpy(cstring,"* Licht");
if(LANG == 2) strcpy(cstring,"* Light");
gtk_button_set_label(GTK_BUTTON(PB_LIGHT),cstring);
strcpy(cstring,"Hidden Line");
gtk_button_set_label(GTK_BUTTON(PB_HIDDE),cstring);
strcpy(cstring,"Wireframe");
gtk_button_set_label(GTK_BUTTON(PB_WIREF),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen Eckknoten");
if(LANG == 2) strcpy(cstring,"Stresses Corner Nodes");
gtk_button_set_label(GTK_BUTTON(PB_SSPAN),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen pro Element");
if(LANG == 2) strcpy(cstring,"Stresses per Element");
gtk_button_set_label(GTK_BUTTON(PB_SGAUS),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen Gausspunkte");
if(LANG == 2) strcpy(cstring,"Stresses Gauss Points");
gtk_button_set_label(GTK_BUTTON(PB_SGAPU),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen X");
if(LANG == 2) strcpy(cstring,"Deflections X");
gtk_button_set_label(GTK_BUTTON(PB_VX),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen Y");
if(LANG == 2) strcpy(cstring,"Deflections Y");
gtk_button_set_label(GTK_BUTTON(PB_VY),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen Z");
if(LANG == 2) strcpy(cstring,"Deflections Z");
gtk_button_set_label(GTK_BUTTON(PB_VZ),cstring);

InvalidateRect88(); 
}

/*****************************************************************************
* CB_HIDDEN
*****************************************************************************/
void CB_HIDDE(GtkWidget *button,gpointer data)
{
extern GtkWidget *PB_LIGHT,*PB_HIDDE,*PB_WIREF,*PB_SSPAN,*PB_SGAUS,*PB_SGAPU;
extern GtkWidget *PB_VX,*PB_VY,*PB_VZ;
extern FR_INT4   LANG;
extern int       if3d;
char             cstring[80];

if3d = IDM_HIDDEN; 

if(LANG == 1) strcpy(cstring,"Licht");
if(LANG == 2) strcpy(cstring,"Light");
gtk_button_set_label(GTK_BUTTON(PB_LIGHT),cstring);
strcpy(cstring,"* Hidden Line");
gtk_button_set_label(GTK_BUTTON(PB_HIDDE),cstring);
strcpy(cstring,"Wireframe");
gtk_button_set_label(GTK_BUTTON(PB_WIREF),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen Eckknoten");
if(LANG == 2) strcpy(cstring,"Stresses Corner Nodes");
gtk_button_set_label(GTK_BUTTON(PB_SSPAN),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen pro Element");
if(LANG == 2) strcpy(cstring,"Stresses per Element");
gtk_button_set_label(GTK_BUTTON(PB_SGAUS),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen Gausspunkte");
if(LANG == 2) strcpy(cstring,"Stresses Gauss Points");
gtk_button_set_label(GTK_BUTTON(PB_SGAPU),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen X");
if(LANG == 2) strcpy(cstring,"Deflections X");
gtk_button_set_label(GTK_BUTTON(PB_VX),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen Y");
if(LANG == 2) strcpy(cstring,"Deflections Y");
gtk_button_set_label(GTK_BUTTON(PB_VY),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen Z");
if(LANG == 2) strcpy(cstring,"Deflections Z");
gtk_button_set_label(GTK_BUTTON(PB_VZ),cstring);

InvalidateRect88(); 
}

/*****************************************************************************
* CB_WIREF
*****************************************************************************/
void CB_WIREF(GtkWidget *button,gpointer data)
{
extern GtkWidget *PB_LIGHT,*PB_HIDDE,*PB_WIREF,*PB_SSPAN,*PB_SGAUS,*PB_SGAPU;
extern GtkWidget *PB_VX,*PB_VY,*PB_VZ;
extern FR_INT4   LANG;
extern int       if3d;
char             cstring[80];

if3d = IDM_WIREFR; 

if(LANG == 1) strcpy(cstring,"Licht");
if(LANG == 2) strcpy(cstring,"Light");
gtk_button_set_label(GTK_BUTTON(PB_LIGHT),cstring);
strcpy(cstring,"Hidden Line");
gtk_button_set_label(GTK_BUTTON(PB_HIDDE),cstring);
strcpy(cstring,"* Wireframe");
gtk_button_set_label(GTK_BUTTON(PB_WIREF),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen Eckknoten");
if(LANG == 2) strcpy(cstring,"Stresses Corner Nodes");
gtk_button_set_label(GTK_BUTTON(PB_SSPAN),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen pro Element");
if(LANG == 2) strcpy(cstring,"Stresses per Element");
gtk_button_set_label(GTK_BUTTON(PB_SGAUS),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen Gausspunkte");
if(LANG == 2) strcpy(cstring,"Stresses Gauss Points");
gtk_button_set_label(GTK_BUTTON(PB_SGAPU),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen X");
if(LANG == 2) strcpy(cstring,"Deflections X");
gtk_button_set_label(GTK_BUTTON(PB_VX),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen Y");
if(LANG == 2) strcpy(cstring,"Deflections Y");
gtk_button_set_label(GTK_BUTTON(PB_VY),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen Z");
if(LANG == 2) strcpy(cstring,"Deflections Z");
gtk_button_set_label(GTK_BUTTON(PB_VZ),cstring);

InvalidateRect88(); 
}

/*****************************************************************************
* CB_SSPAN
*****************************************************************************/
void CB_SSPAN(GtkWidget *button,gpointer data)
{
extern GtkWidget *PB_LIGHT,*PB_HIDDE,*PB_WIREF,*PB_SSPAN,*PB_SGAUS,*PB_SGAPU;
extern GtkWidget *PB_VX,*PB_VY,*PB_VZ;
extern FR_INT4   LANG;
extern int       if3d;
char             cstring[80];

if3d = IDM_SHOWSPANN; 

if(LANG == 1) strcpy(cstring,"Licht");
if(LANG == 2) strcpy(cstring,"Light");
gtk_button_set_label(GTK_BUTTON(PB_LIGHT),cstring);
strcpy(cstring,"Hidden Line");
gtk_button_set_label(GTK_BUTTON(PB_HIDDE),cstring);
strcpy(cstring,"Wireframe");
gtk_button_set_label(GTK_BUTTON(PB_WIREF),cstring);
if(LANG == 1) strcpy(cstring,"* Spannungen Eckknoten");
if(LANG == 2) strcpy(cstring,"* Stresses Corner Nodes");
gtk_button_set_label(GTK_BUTTON(PB_SSPAN),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen pro Element");
if(LANG == 2) strcpy(cstring,"Stresses per Element");
gtk_button_set_label(GTK_BUTTON(PB_SGAUS),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen Gausspunkte");
if(LANG == 2) strcpy(cstring,"Stresses Gauss Points");
gtk_button_set_label(GTK_BUTTON(PB_SGAPU),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen X");
if(LANG == 2) strcpy(cstring,"Deflections X");
gtk_button_set_label(GTK_BUTTON(PB_VX),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen Y");
if(LANG == 2) strcpy(cstring,"Deflections Y");
gtk_button_set_label(GTK_BUTTON(PB_VY),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen Z");
if(LANG == 2) strcpy(cstring,"Deflections Z");
gtk_button_set_label(GTK_BUTTON(PB_VZ),cstring);

InvalidateRect88(); 
}

/*****************************************************************************
* CB_SGAUS
*****************************************************************************/
void CB_SGAUS(GtkWidget *button,gpointer data)
{
extern GtkWidget *PB_LIGHT,*PB_HIDDE,*PB_WIREF,*PB_SSPAN,*PB_SGAUS,*PB_SGAPU;
extern GtkWidget *PB_VX,*PB_VY,*PB_VZ;
extern FR_INT4   LANG;
extern int       if3d;
char             cstring[80];

if3d = IDM_SHOWGAUSS; 

if(LANG == 1) strcpy(cstring,"Licht");
if(LANG == 2) strcpy(cstring,"Light");
gtk_button_set_label(GTK_BUTTON(PB_LIGHT),cstring);
strcpy(cstring,"Hidden Line");
gtk_button_set_label(GTK_BUTTON(PB_HIDDE),cstring);
strcpy(cstring,"Wireframe");
gtk_button_set_label(GTK_BUTTON(PB_WIREF),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen Eckknoten");
if(LANG == 2) strcpy(cstring,"Stresses Corner Nodes");
gtk_button_set_label(GTK_BUTTON(PB_SSPAN),cstring);
if(LANG == 1) strcpy(cstring,"* Spannungen pro Element");
if(LANG == 2) strcpy(cstring,"* Stresses per Element");
gtk_button_set_label(GTK_BUTTON(PB_SGAUS),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen Gausspunkte");
if(LANG == 2) strcpy(cstring,"Stresses Gauss Points");
gtk_button_set_label(GTK_BUTTON(PB_SGAPU),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen X");
if(LANG == 2) strcpy(cstring,"Deflections X");
gtk_button_set_label(GTK_BUTTON(PB_VX),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen Y");
if(LANG == 2) strcpy(cstring,"Deflections Y");
gtk_button_set_label(GTK_BUTTON(PB_VY),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen Z");
if(LANG == 2) strcpy(cstring,"Deflections Z");
gtk_button_set_label(GTK_BUTTON(PB_VZ),cstring);

InvalidateRect88(); 
}

/*****************************************************************************
* CB_SGAPU
*****************************************************************************/
void CB_SGAPU(GtkWidget *button,gpointer data)
{
extern GtkWidget *PB_LIGHT,*PB_HIDDE,*PB_WIREF,*PB_SSPAN,*PB_SGAUS,*PB_SGAPU;
extern GtkWidget *PB_VX,*PB_VY,*PB_VZ;
extern FR_INT4   LANG;
extern int       if3d;
char             cstring[80];

if3d = IDM_SHOWGAUPU; 

if(LANG == 1) strcpy(cstring,"Licht");
if(LANG == 2) strcpy(cstring,"Light");
gtk_button_set_label(GTK_BUTTON(PB_LIGHT),cstring);
strcpy(cstring,"Hidden Line");
gtk_button_set_label(GTK_BUTTON(PB_HIDDE),cstring);
strcpy(cstring,"Wireframe");
gtk_button_set_label(GTK_BUTTON(PB_WIREF),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen Eckknoten");
if(LANG == 2) strcpy(cstring,"Stresses Corner Nodes");
gtk_button_set_label(GTK_BUTTON(PB_SSPAN),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen pro Element");
if(LANG == 2) strcpy(cstring,"Stresses per Element");
gtk_button_set_label(GTK_BUTTON(PB_SGAUS),cstring);
if(LANG == 1) strcpy(cstring,"* Spannungen Gausspunkte");
if(LANG == 2) strcpy(cstring,"* Stresses Gauss Points");
gtk_button_set_label(GTK_BUTTON(PB_SGAPU),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen X");
if(LANG == 2) strcpy(cstring,"Deflections X");
gtk_button_set_label(GTK_BUTTON(PB_VX),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen Y");
if(LANG == 2) strcpy(cstring,"Deflections Y");
gtk_button_set_label(GTK_BUTTON(PB_VY),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen Z");
if(LANG == 2) strcpy(cstring,"Deflections Z");
gtk_button_set_label(GTK_BUTTON(PB_VZ),cstring);

InvalidateRect88(); 
}

/*****************************************************************************
* CB_VX
*****************************************************************************/
void CB_VX(GtkWidget *button,gpointer data)
{
extern GtkWidget *PB_LIGHT,*PB_HIDDE,*PB_WIREF,*PB_SSPAN,*PB_SGAUS,*PB_SGAPU;
extern GtkWidget *PB_VX,*PB_VY,*PB_VZ;
extern FR_INT4   LANG;
extern int       if3d;
char             cstring[80];

if3d = IDM_SHOWVX; 

if(LANG == 1) strcpy(cstring,"Licht");
if(LANG == 2) strcpy(cstring,"Light");
gtk_button_set_label(GTK_BUTTON(PB_LIGHT),cstring);
strcpy(cstring,"Hidden Line");
gtk_button_set_label(GTK_BUTTON(PB_HIDDE),cstring);
strcpy(cstring,"Wireframe");
gtk_button_set_label(GTK_BUTTON(PB_WIREF),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen Eckknoten");
if(LANG == 2) strcpy(cstring,"Stresses Corner Nodes");
gtk_button_set_label(GTK_BUTTON(PB_SSPAN),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen pro Element");
if(LANG == 2) strcpy(cstring,"Stresses per Element");
gtk_button_set_label(GTK_BUTTON(PB_SGAUS),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen Gausspunkte");
if(LANG == 2) strcpy(cstring,"Stresses Gauss Points");
gtk_button_set_label(GTK_BUTTON(PB_SGAPU),cstring);
if(LANG == 1) strcpy(cstring,"* Verschiebungen X");
if(LANG == 2) strcpy(cstring,"* Deflections X");
gtk_button_set_label(GTK_BUTTON(PB_VX),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen Y");
if(LANG == 2) strcpy(cstring,"Deflections Y");
gtk_button_set_label(GTK_BUTTON(PB_VY),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen Z");
if(LANG == 2) strcpy(cstring,"Deflections Z");
gtk_button_set_label(GTK_BUTTON(PB_VZ),cstring);

InvalidateRect88(); 
}

/*****************************************************************************
* CB_VY
*****************************************************************************/
void CB_VY(GtkWidget *button,gpointer data)
{
extern GtkWidget *PB_LIGHT,*PB_HIDDE,*PB_WIREF,*PB_SSPAN,*PB_SGAUS,*PB_SGAPU;
extern GtkWidget *PB_VX,*PB_VY,*PB_VZ;
extern FR_INT4   LANG;
extern int       if3d;
char             cstring[80];

if3d = IDM_SHOWVY; 

if(LANG == 1) strcpy(cstring,"Licht");
if(LANG == 2) strcpy(cstring,"Light");
gtk_button_set_label(GTK_BUTTON(PB_LIGHT),cstring);
strcpy(cstring,"Hidden Line");
gtk_button_set_label(GTK_BUTTON(PB_HIDDE),cstring);
strcpy(cstring,"Wireframe");
gtk_button_set_label(GTK_BUTTON(PB_WIREF),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen Eckknoten");
if(LANG == 2) strcpy(cstring,"Stresses Corner Nodes");
gtk_button_set_label(GTK_BUTTON(PB_SSPAN),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen pro Element");
if(LANG == 2) strcpy(cstring,"Stresses per Element");
gtk_button_set_label(GTK_BUTTON(PB_SGAUS),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen Gausspunkte");
if(LANG == 2) strcpy(cstring,"Stresses Gauss Points");
gtk_button_set_label(GTK_BUTTON(PB_SGAPU),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen X");
if(LANG == 2) strcpy(cstring,"Deflections X");
gtk_button_set_label(GTK_BUTTON(PB_VX),cstring);
if(LANG == 1) strcpy(cstring,"* Verschiebungen Y");
if(LANG == 2) strcpy(cstring,"* Deflections Y");
gtk_button_set_label(GTK_BUTTON(PB_VY),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen Z");
if(LANG == 2) strcpy(cstring,"Deflections Z");
gtk_button_set_label(GTK_BUTTON(PB_VZ),cstring);

InvalidateRect88(); 
}

/*****************************************************************************
* CB_VZ
*****************************************************************************/
void CB_VZ(GtkWidget *button,gpointer data)
{
extern GtkWidget *PB_LIGHT,*PB_HIDDE,*PB_WIREF,*PB_SSPAN,*PB_SGAUS,*PB_SGAPU;
extern GtkWidget *PB_VX,*PB_VY,*PB_VZ;
extern FR_INT4   LANG;
extern int       if3d;
char             cstring[80];

if3d = IDM_SHOWVZ; 

if(LANG == 1) strcpy(cstring,"Licht");
if(LANG == 2) strcpy(cstring,"Light");
gtk_button_set_label(GTK_BUTTON(PB_LIGHT),cstring);
strcpy(cstring,"Hidden Line");
gtk_button_set_label(GTK_BUTTON(PB_HIDDE),cstring);
strcpy(cstring,"Wireframe");
gtk_button_set_label(GTK_BUTTON(PB_WIREF),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen Eckknoten");
if(LANG == 2) strcpy(cstring,"Stresses Corner Nodes");
gtk_button_set_label(GTK_BUTTON(PB_SSPAN),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen pro Element");
if(LANG == 2) strcpy(cstring,"Stresses per Element");
gtk_button_set_label(GTK_BUTTON(PB_SGAUS),cstring);
if(LANG == 1) strcpy(cstring,"Spannungen Gausspunkte");
if(LANG == 2) strcpy(cstring,"Stresses Gauss Points");
gtk_button_set_label(GTK_BUTTON(PB_SGAPU),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen X");
if(LANG == 2) strcpy(cstring,"Deflections X");
gtk_button_set_label(GTK_BUTTON(PB_VX),cstring);
if(LANG == 1) strcpy(cstring,"Verschiebungen Y");
if(LANG == 2) strcpy(cstring,"Deflections Y");
gtk_button_set_label(GTK_BUTTON(PB_VY),cstring);
if(LANG == 1) strcpy(cstring,"* Verschiebungen Z");
if(LANG == 2) strcpy(cstring,"* Deflections Z");
gtk_button_set_label(GTK_BUTTON(PB_VZ),cstring);

InvalidateRect88(); 
}

/*****************************************************************************
* CB_SRBD
*****************************************************************************/
void CB_SRBD(GtkWidget *button,gpointer data)
{
extern int if3d,ifrbd;
if(!(if3d == IDM_SHOWSPANN || if3d == IDM_SHOWGAUSS ||
     if3d == IDM_SHOWVX || if3d == IDM_SHOWVY || if3d == IDM_SHOWVZ))
  {
  if(ifrbd == IDM_NORBD) ifrbd= IDM_YESRBD;
  else                   ifrbd= IDM_NORBD;
  InvalidateRect88();
  }
}

/*****************************************************************************
* CB_KOOR
*****************************************************************************/
void CB_KOOR(GtkWidget *button,gpointer data)
{
extern int ifkoor;
if(ifkoor == IDM_NOKOOR) ifkoor= IDM_YESKOOR;
else                     ifkoor= IDM_NOKOOR;
InvalidateRect88();
}

/*****************************************************************************
* CB_NOLA
*****************************************************************************/
void CB_NOLA(GtkWidget *button,gpointer data)
{
extern int iflabe,iplot;
iplot  = 0;
iflabe = IDM_NOLABELS;
InvalidateRect88();
}

/*****************************************************************************
* CB_NODE
*****************************************************************************/
void CB_NODE(GtkWidget *button,gpointer data)
{
extern FR_INT4 jkvon,jkbis;
extern int     iflabe,iplot; 
char           ckvon[20],ckbis[20];
extern FR_INT4 LANG;

GtkWidget *DIA_NODE,*TABLE,*VON,*BIS;
GtkWidget *L_VON,*L_BIS;

int iret;

char cstring[80];
const gchar *cvon,*cbis;

/*---------------------------------------------------------------------------
* beim allerersten Start gehen die Maximalwerte rein
*--------------------------------------------------------------------------*/
sprintf(ckvon,PD,jkvon);
sprintf(ckbis,PD,jkbis);

if(LANG == 1) strcpy(cstring,"KNOTENNUM.");
if(LANG == 2) strcpy(cstring,"NODE NUM..");
DIA_NODE= gtk_dialog_new_with_buttons(cstring,NULL,GTK_DIALOG_MODAL,
                                     GTK_STOCK_OK,GTK_RESPONSE_OK,
                                     GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
gtk_dialog_set_default_response(GTK_DIALOG(DIA_NODE),GTK_RESPONSE_OK);

if(LANG == 1) strcpy(cstring,"Von");
if(LANG == 2) strcpy(cstring,"From");
L_VON= gtk_label_new(cstring);
if(LANG == 1) strcpy(cstring,"Bis");
if(LANG == 2) strcpy(cstring,"To");
L_BIS= gtk_label_new(cstring);

VON= gtk_entry_new();
BIS= gtk_entry_new();

gtk_entry_set_text(GTK_ENTRY(VON),ckvon);
gtk_entry_set_text(GTK_ENTRY(BIS),ckbis);

TABLE= gtk_table_new(2,2,FALSE);
gtk_table_attach_defaults(GTK_TABLE(TABLE),L_VON,0,1,0,1);
gtk_table_attach_defaults(GTK_TABLE(TABLE),L_BIS,0,1,1,2);
gtk_table_attach_defaults(GTK_TABLE(TABLE),  VON,1,2,0,1);
gtk_table_attach_defaults(GTK_TABLE(TABLE),  BIS,1,2,1,2);
gtk_table_set_row_spacings(GTK_TABLE(TABLE),5);
gtk_table_set_col_spacings(GTK_TABLE(TABLE),5);
gtk_container_set_border_width(GTK_CONTAINER(TABLE),5);

gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(DIA_NODE)->vbox),TABLE);
gtk_widget_show_all(DIA_NODE);
iret= gtk_dialog_run(GTK_DIALOG(DIA_NODE));

if(iret == GTK_RESPONSE_OK)
  {
  cvon= gtk_entry_get_text(GTK_ENTRY(VON));
  cbis= gtk_entry_get_text(GTK_ENTRY(BIS));
  jkvon= atol(cvon);
  jkbis= atol(cbis);
  }

gtk_widget_destroy(DIA_NODE);

iplot  = 0;
iflabe = IDM_KNOTEN;
InvalidateRect88();
}

/*****************************************************************************
* CB_ELE
*****************************************************************************/
void CB_ELE(GtkWidget *button,gpointer data)
{
extern FR_INT4 jevon,jebis;
extern int     iflabe,iplot; 
char           ckvon[20],ckbis[20];
extern FR_INT4 LANG;

GtkWidget *DIA_ELE,*TABLE,*VON,*BIS;
GtkWidget *L_VON,*L_BIS;

int iret;

char cstring[80];
const gchar *cvon,*cbis;

/*---------------------------------------------------------------------------
* beim allerersten Start gehen die Maximalwerte rein
*--------------------------------------------------------------------------*/
sprintf(ckvon,PD,jevon);
sprintf(ckbis,PD,jebis);

if(LANG == 1) strcpy(cstring,"ELEMENTNUM.");
if(LANG == 2) strcpy(cstring,"ELEMENT NUM..");
DIA_ELE= gtk_dialog_new_with_buttons(cstring,NULL,GTK_DIALOG_MODAL,
                                     GTK_STOCK_OK,GTK_RESPONSE_OK,
                                     GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
gtk_dialog_set_default_response(GTK_DIALOG(DIA_ELE),GTK_RESPONSE_OK);

if(LANG == 1) strcpy(cstring,"Von");
if(LANG == 2) strcpy(cstring,"From");
L_VON= gtk_label_new(cstring);
if(LANG == 1) strcpy(cstring,"Bis");
if(LANG == 2) strcpy(cstring,"To");
L_BIS= gtk_label_new(cstring);

VON= gtk_entry_new();
BIS= gtk_entry_new();

gtk_entry_set_text(GTK_ENTRY(VON),ckvon);
gtk_entry_set_text(GTK_ENTRY(BIS),ckbis);

TABLE= gtk_table_new(2,2,FALSE);
gtk_table_attach_defaults(GTK_TABLE(TABLE),L_VON,0,1,0,1);
gtk_table_attach_defaults(GTK_TABLE(TABLE),L_BIS,0,1,1,2);
gtk_table_attach_defaults(GTK_TABLE(TABLE),  VON,1,2,0,1);
gtk_table_attach_defaults(GTK_TABLE(TABLE),  BIS,1,2,1,2);
gtk_table_set_row_spacings(GTK_TABLE(TABLE),5);
gtk_table_set_col_spacings(GTK_TABLE(TABLE),5);
gtk_container_set_border_width(GTK_CONTAINER(TABLE),5);

gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(DIA_ELE)->vbox),TABLE);
gtk_widget_show_all(DIA_ELE);
iret= gtk_dialog_run(GTK_DIALOG(DIA_ELE));

if(iret == GTK_RESPONSE_OK)
  {
  cvon= gtk_entry_get_text(GTK_ENTRY(VON));
  cbis= gtk_entry_get_text(GTK_ENTRY(BIS));
  jevon= atol(cvon);
  jebis= atol(cbis);
  }

gtk_widget_destroy(DIA_ELE);

iplot  = 0;
iflabe = IDM_ELEMENTE;
InvalidateRect88();
}

/*****************************************************************************
* CB_ALLE
*****************************************************************************/
void CB_ALLE(GtkWidget *button,gpointer data)
{
extern int iflabe,iplot;
iplot  = 1;
iflabe = IDM_LALLES;
InvalidateRect88();
}

/*****************************************************************************
* CB_VER
*****************************************************************************/
void CB_VER(GtkWidget *button,gpointer data)
{
extern double  fux,fuy,fuz;
extern FR_INT4 LANG;

GtkWidget *DIA_VER,*TABLE,*FUX,*FUY,*FUZ;
GtkWidget *L_FUX,*L_FUY,*L_FUZ;
int idigit= 20,iret;
char cfux[31],cfuy[31],cfuz[31];
char cstring[80];
const gchar *ccx,*ccy,*ccz;

/*---------------------------------------------------------------------------
* beim allerersten Start gehen fux, fuy & fuz mit je 100. rein
*--------------------------------------------------------------------------*/
gcvt(fux,idigit,cfux); 
gcvt(fuy,idigit,cfuy); 
gcvt(fuz,idigit,cfuz); 

if(LANG == 1) strcpy(cstring,"VERGROESSERUNG VER.");
if(LANG == 2) strcpy(cstring,"MAGNIFICATION DEFL.");
DIA_VER= gtk_dialog_new_with_buttons(cstring,NULL,GTK_DIALOG_MODAL,
                                     GTK_STOCK_OK,GTK_RESPONSE_OK,
                                     GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
gtk_dialog_set_default_response(GTK_DIALOG(DIA_VER),GTK_RESPONSE_OK);

L_FUX= gtk_label_new("FUX");
L_FUY= gtk_label_new("FUY");
L_FUZ= gtk_label_new("FUZ");

FUX= gtk_entry_new();
FUY= gtk_entry_new();
FUZ= gtk_entry_new();

gtk_entry_set_text(GTK_ENTRY(FUX),cfux);
gtk_entry_set_text(GTK_ENTRY(FUY),cfuy);
gtk_entry_set_text(GTK_ENTRY(FUZ),cfuz);

TABLE= gtk_table_new(3,2,FALSE);
gtk_table_attach_defaults(GTK_TABLE(TABLE),L_FUX,0,1,0,1);
gtk_table_attach_defaults(GTK_TABLE(TABLE),L_FUY,0,1,1,2);
gtk_table_attach_defaults(GTK_TABLE(TABLE),L_FUZ,0,1,2,3);
gtk_table_attach_defaults(GTK_TABLE(TABLE),  FUX,1,2,0,1);
gtk_table_attach_defaults(GTK_TABLE(TABLE),  FUY,1,2,1,2);
gtk_table_attach_defaults(GTK_TABLE(TABLE),  FUZ,1,2,2,3);
gtk_table_set_row_spacings(GTK_TABLE(TABLE),5);
gtk_table_set_col_spacings(GTK_TABLE(TABLE),5);
gtk_container_set_border_width(GTK_CONTAINER(TABLE),5);

gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(DIA_VER)->vbox),TABLE);
gtk_widget_show_all(DIA_VER);
iret= gtk_dialog_run(GTK_DIALOG(DIA_VER));

if(iret == GTK_RESPONSE_OK)
  {
  ccx= gtk_entry_get_text(GTK_ENTRY(FUX));
  ccy= gtk_entry_get_text(GTK_ENTRY(FUY));
  ccz= gtk_entry_get_text(GTK_ENTRY(FUZ));
  fux= atof(ccx);
  fuy= atof(ccy);
  fuz= atof(ccz);
  InvalidateRect88();
  }

gtk_widget_destroy(DIA_VER);
}

/*****************************************************************************
* CB_ROT
*****************************************************************************/
void CB_ROT(GtkWidget *button,gpointer data)
{
extern double  rotx,roty,rotz;
extern FR_INT4 LANG;

GtkWidget *DIA_ROT,*TABLE,*ROTX,*ROTY,*ROTZ;
GtkWidget *L_ROTX,*L_ROTY,*L_ROTZ;
int idigit= 20,iret;
char crotx[31],croty[31],crotz[31];
char cstring[80];
const gchar *ccx,*ccy,*ccz;

/*---------------------------------------------------------------------------
* beim allerersten Start gehen rotx, roty & rotz mit je 0. rein
*--------------------------------------------------------------------------*/
gcvt(rotx,idigit,crotx); 
gcvt(roty,idigit,croty); 
gcvt(rotz,idigit,crotz); 

if(LANG == 1) strcpy(cstring,"ROTATIONEN 3-D");
if(LANG == 2) strcpy(cstring,"ROTATIONS 3-D");
DIA_ROT= gtk_dialog_new_with_buttons(cstring,NULL,GTK_DIALOG_MODAL,
                                     GTK_STOCK_OK,GTK_RESPONSE_OK,
                                     GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
gtk_dialog_set_default_response(GTK_DIALOG(DIA_ROT),GTK_RESPONSE_OK);

L_ROTX= gtk_label_new("ROTX");
L_ROTY= gtk_label_new("ROTY");
L_ROTZ= gtk_label_new("ROTZ");

ROTX= gtk_entry_new();
ROTY= gtk_entry_new();
ROTZ= gtk_entry_new();

gtk_entry_set_text(GTK_ENTRY(ROTX),crotx);
gtk_entry_set_text(GTK_ENTRY(ROTY),croty);
gtk_entry_set_text(GTK_ENTRY(ROTZ),crotz);

TABLE= gtk_table_new(3,2,FALSE);
gtk_table_attach_defaults(GTK_TABLE(TABLE),L_ROTX,0,1,0,1);
gtk_table_attach_defaults(GTK_TABLE(TABLE),L_ROTY,0,1,1,2);
gtk_table_attach_defaults(GTK_TABLE(TABLE),L_ROTZ,0,1,2,3);
gtk_table_attach_defaults(GTK_TABLE(TABLE),  ROTX,1,2,0,1);
gtk_table_attach_defaults(GTK_TABLE(TABLE),  ROTY,1,2,1,2);
gtk_table_attach_defaults(GTK_TABLE(TABLE),  ROTZ,1,2,2,3);
gtk_table_set_row_spacings(GTK_TABLE(TABLE),5);
gtk_table_set_col_spacings(GTK_TABLE(TABLE),5);
gtk_container_set_border_width(GTK_CONTAINER(TABLE),5);

gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(DIA_ROT)->vbox),TABLE);
gtk_widget_show_all(DIA_ROT);
iret= gtk_dialog_run(GTK_DIALOG(DIA_ROT));

if(iret == GTK_RESPONSE_OK)
  {
  ccx= gtk_entry_get_text(GTK_ENTRY(ROTX));
  ccy= gtk_entry_get_text(GTK_ENTRY(ROTY));
  ccz= gtk_entry_get_text(GTK_ENTRY(ROTZ));
  rotx= atof(ccx);
  roty= atof(ccy);
  rotz= atof(ccz);
  InvalidateRect88();
  }

gtk_widget_destroy(DIA_ROT);
}

/*****************************************************************************
* CB_ZM
*****************************************************************************/
void CB_ZM(GtkWidget *button,gpointer data)
{
extern GtkWidget *DRAWA;
extern FR_DOUBLE xm,xp,ym,yp,zm,zp;
extern int       IB,IH;
extern double  zm;
extern FR_INT4 LANG;

GdkGLContext     *glcontext;
GdkGLDrawable    *gldrawable;
GtkWidget *DIA_ZM,*TABLE,*ZM;
GtkWidget *L_ZM;
int idigit= 20,iret;
char czm[31];
char cstring[80];
const gchar *ccm;

/*---------------------------------------------------------------------------
* beim allerersten Start geht zm mit -100. rein
*--------------------------------------------------------------------------*/
gcvt(zm,idigit,czm); 

if(LANG == 1) strcpy(cstring,"Z-Limit zum Betrachter");
if(LANG == 2) strcpy(cstring,"Z Limit towards you");
DIA_ZM= gtk_dialog_new_with_buttons(cstring,NULL,GTK_DIALOG_MODAL,
                                     GTK_STOCK_OK,GTK_RESPONSE_OK,
                                     GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
gtk_dialog_set_default_response(GTK_DIALOG(DIA_ZM),GTK_RESPONSE_OK);

L_ZM= gtk_label_new("Clipping -Z");

ZM= gtk_entry_new();

gtk_entry_set_text(GTK_ENTRY(ZM),czm);

TABLE= gtk_table_new(1,2,FALSE);
gtk_table_attach_defaults(GTK_TABLE(TABLE),L_ZM,0,1,0,1);
gtk_table_attach_defaults(GTK_TABLE(TABLE),  ZM,1,2,0,1);
gtk_table_set_row_spacings(GTK_TABLE(TABLE),5);
gtk_table_set_col_spacings(GTK_TABLE(TABLE),5);
gtk_container_set_border_width(GTK_CONTAINER(TABLE),5);

gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(DIA_ZM)->vbox),TABLE);
gtk_widget_show_all(DIA_ZM);
iret= gtk_dialog_run(GTK_DIALOG(DIA_ZM));

if(iret == GTK_RESPONSE_OK)
  {
  ccm= gtk_entry_get_text(GTK_ENTRY(ZM));
  zm= atof(ccm);

  glcontext = gtk_widget_get_gl_context(DRAWA);
  gldrawable= gtk_widget_get_gl_drawable(DRAWA);

  gdk_gl_drawable_gl_begin(gldrawable,glcontext);
  glViewport(0,0,IB,IH);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(xm,xp,ym,yp,zm,zp);

  glMatrixMode(GL_MODELVIEW);
  gdk_gl_drawable_gl_end(gldrawable);

  InvalidateRect88();
  }

gtk_widget_destroy(DIA_ZM);
}

/*****************************************************************************
* CB_NORBD
*****************************************************************************/
void CB_NORBD(GtkWidget *button,gpointer data)
{
extern int ifrbd;
ifrbd= IDM_NORBD;
InvalidateRect88();
}

/*****************************************************************************
* CB_YESRBD
*****************************************************************************/
void CB_YESRBD(GtkWidget *button,gpointer data)
{
extern int if3d,ifrbd;
if(!(if3d == IDM_SHOWSPANN || if3d == IDM_SHOWGAUSS ||
     if3d == IDM_SHOWVX || if3d == IDM_SHOWVY || if3d == IDM_SHOWVZ))
  {
  ifrbd= IDM_YESRBD;
  InvalidateRect88();
  }
}

/*****************************************************************************
* CB_ZOPLUS
*****************************************************************************/
void CB_ZOPLUS(GtkWidget *button,gpointer data)
{
extern FR_DOUBLE zorbd;
zorbd *= 1.5;
InvalidateRect88();
}

/*****************************************************************************
* CB_ZOMINUS
*****************************************************************************/
void CB_ZOMINUS(GtkWidget *button,gpointer data)
{
extern FR_DOUBLE zorbd;
zorbd /= 1.5;
InvalidateRect88();
}

/*****************************************************************************
* CB_RBDALL
*****************************************************************************/
void CB_RBDALL(GtkWidget *button,gpointer data)
{
extern int ifwbc;
ifwbc= IDM_RBDALL;
InvalidateRect88();
}

/*****************************************************************************
* CB_RBDUX
*****************************************************************************/
void CB_RBDUX(GtkWidget *button,gpointer data)
{
extern int ifwbc;
ifwbc= IDM_RBDUX;
InvalidateRect88();
}

/*****************************************************************************
* CB_RBDUY
*****************************************************************************/
void CB_RBDUY(GtkWidget *button,gpointer data)
{
extern int ifwbc;
ifwbc= IDM_RBDUY;
InvalidateRect88();
}

/*****************************************************************************
* CB_RBDUZ
*****************************************************************************/
void CB_RBDUZ(GtkWidget *button,gpointer data)
{
extern int ifwbc;
ifwbc= IDM_RBDUZ;
InvalidateRect88();
}

/*****************************************************************************
* CB_RBDU4
*****************************************************************************/
void CB_RBDU4(GtkWidget *button,gpointer data)
{
extern int ifwbc;
ifwbc= IDM_RBDU4;
InvalidateRect88();
}

/*****************************************************************************
* CB_RBDU5
*****************************************************************************/
void CB_RBDU5(GtkWidget *button,gpointer data)
{
extern int ifwbc;
ifwbc= IDM_RBDU5;
InvalidateRect88();
}

/*****************************************************************************
* CB_RBDU6
*****************************************************************************/
void CB_RBDU6(GtkWidget *button,gpointer data)
{
extern int ifwbc;
ifwbc= IDM_RBDU6;
InvalidateRect88();
}

/*****************************************************************************
* CB_RBDUA
*****************************************************************************/
void CB_RBDUA(GtkWidget *button,gpointer data)
{
extern int ifwbc;
ifwbc= IDM_RBDUA;
InvalidateRect88();
}

/*****************************************************************************
* CB_RBDOL
*****************************************************************************/
void CB_RBDOL(GtkWidget *button,gpointer data)
{
extern int ifwbc;
ifwbc= IDM_RBDOL;
InvalidateRect88();
}

/*****************************************************************************
* CB_RBDFX
*****************************************************************************/
void CB_RBDFX(GtkWidget *button,gpointer data)
{
extern int ifwbc;
ifwbc= IDM_RBDFX;
InvalidateRect88();
}

/*****************************************************************************
* CB_RBDFY
*****************************************************************************/
void CB_RBDFY(GtkWidget *button,gpointer data)
{
extern int ifwbc;
ifwbc= IDM_RBDFY;
InvalidateRect88();
}

/*****************************************************************************
* CB_RBDFZ
*****************************************************************************/
void CB_RBDFZ(GtkWidget *button,gpointer data)
{
extern int ifwbc;
ifwbc= IDM_RBDFZ;
InvalidateRect88();
}

/*****************************************************************************
* CB_GPZOPLUS
*****************************************************************************/
void CB_GPZOPLUS(GtkWidget *button,gpointer data)
{
extern FR_DOUBLE zoogp;
zoogp *= 1.5;
InvalidateRect88();
}

/*****************************************************************************
* CB_GPZOMINUS
*****************************************************************************/
void CB_GPZOMINUS(GtkWidget *button,gpointer data)
{
extern FR_DOUBLE zoogp;
zoogp /= 1.5;
InvalidateRect88();
}

/*****************************************************************************
* CB_YESNOST
*****************************************************************************/
void CB_YESNOST(GtkWidget *button,gpointer data)
{
extern int ifnost;
ifnost= IDM_YESNOST;
InvalidateRect88();
}

/*****************************************************************************
* CB_NONOST
*****************************************************************************/
void CB_NONOST(GtkWidget *button,gpointer data)
{
extern int ifnost;
ifnost= IDM_NONOST;
InvalidateRect88();
}

/*****************************************************************************
* WMU_PAINT
*****************************************************************************/
void WMU_PAINT(GtkWidget *widget,GdkEventExpose *event,gpointer data)
{
extern GtkWidget *DRAWA;

GdkGLContext     *glcontext;
GdkGLDrawable    *gldrawable;

extern FILE      *fi1,*fi2,*fi5,*fo2,*fo5,*fo8;

extern int       iflade,iflaver,iflspa,iflao5,iflarbd,iflai5,IB,ifkom,ialert;
extern int       ifmaus,ifverf,if3d,iflabe,ifscale,ifrbd,ifwbc,ifkoor,ifnost,ifvcur;

extern GLfloat   back_col[];
extern GLfloat   specula0[];
extern GLfloat   specula1[];
extern GLfloat   specula2[];
extern GLfloat   ambient0[];
extern GLfloat   ambient1[];
extern GLfloat   diffuse0[];
extern GLfloat   diffuse1[];
extern GLfloat   positio0[];
extern GLfloat   positio1[];
extern GLfloat   positio2[];
extern GLfloat   spec_mat[];
extern GLfloat   diff_mat[];
extern GLfloat   shine[];
extern GLfloat   hide_col[];
extern GLfloat   hide_off[];
extern GLfloat   bline;

extern FR_DOUBLE xx,yy,rx,ry,rz,s,tx,ty;
extern FR_DOUBLE rotx,roty,rotz,xw,yp;
extern FR_INT4   ndim,iqflag;

glcontext = gtk_widget_get_gl_context (DRAWA);
gldrawable= gtk_widget_get_gl_drawable(DRAWA);

  gdk_gl_drawable_gl_begin(gldrawable,glcontext);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glCallList (1);

/*======================================================================
* Polygon-Modus FILL und Hidden-Surface Removal an
*=====================================================================*/
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

/*======================================================================
* Hintergrundfarbe
*=====================================================================*/
    glClearColor(back_col[0],back_col[1],back_col[2],back_col[3]);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/*======================================================================
* Lichtquelle immer am selben Ort lassen
*=====================================================================*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

/*======================================================================
* Z88I1.TXT schon geladen?
*=====================================================================*/
    if(iflade == ID_NOTLOADSTRUC) goto Lflush;

/*======================================================================
* Maximalwerte ermitteln und Skalieren 
*=====================================================================*/
    if(ifscale == IDM_YESSCALE) vsca88();

/*======================================================================
* Laden von Z88O2.TXT, wenn Anzeige der Verformungen
*=====================================================================*/ 
    if(iflaver == ID_NOTLOADVERF && 
       (ifverf == IDM_VERFORMT   ||   if3d   == IDM_SHOWVX     ||
        if3d   == IDM_SHOWVY     ||   if3d   == IDM_SHOWVZ))
      {
      fo2= fopen("z88o2.txt","r");
      if(fo2 == NULL)
        {
        ale88o(AL_NOO2);
        wlog88o(0,LOG_NOO2);
        goto Lflush;
        }
      rewind(fo2);

      ro2x88(); 
      iflaver= ID_LOADVERF;
      if(fo2) fclose(fo2); 
      }

/*======================================================================
* Laden von Z88I2.TXT, wenn Anzeige der Randbedingungen
*=====================================================================*/ 
    if(iflarbd == ID_NOTLOADRBD && ifrbd == IDM_YESRBD)
      {
      fi2= fopen("z88i2.txt","r");
      if(fi2 == NULL)
        {
        ale88o(AL_NOI2);
        wlog88o(0,LOG_NOI2);
        ifrbd= IDM_NORBD;
        goto Lflush;
        }
      rewind(fi2);

      ialert= ri2x88();
      if(ialert != 0)
        {
        ale88o(ialert);
        wlog88o(0,LOG_EXMAXRBD);
        ifrbd= IDM_NORBD;
        goto Lflush;
        }
      else
        iflarbd= ID_LOADRBD;
       
      if(fi2) fclose(fi2); 
      }

/*======================================================================
* Laden von Z88I5.TXT, wenn Anzeige der Randbedingungen und Flaechenla.
*=====================================================================*/ 
    if(iflai5 == ID_NOTLOADI5 && ifrbd == IDM_YESRBD && iqflag == 1)
      {
      fi5= fopen("z88i5.txt","r");
      if(fi5 == NULL)
        {
        ale88o(AL_NOI5);
        wlog88o(0,LOG_NOI5);
        ifrbd= IDM_NORBD;
        goto Lflush;
        }
      rewind(fi5);

      ialert= ri5x88(); 
      if(ialert != 0)
        {
        ale88o(ialert);
        wlog88o(0,LOG_EXMAXPR);
        ifrbd= IDM_NORBD;
        goto Lflush;
        }
      else
        iflai5= ID_LOADI5;
      
      if(fi5) fclose(fi5); 
      }

/*======================================================================
* Laden von Z88O8.TXT, wenn Anzeige der Spannungen in Eckknoten
*=====================================================================*/ 
    if(iflspa == ID_NOTLOADSPANN && 
        (if3d == IDM_SHOWSPANN || if3d == IDM_SHOWGAUSS))
      {
      fo8= fopen("z88o8.txt","r");
      if(fo8 == NULL)
        {
        ale88o(AL_NOO8);    
        wlog88o(0,LOG_NOO8);
        goto Lflush;
        }
      rewind(fo8);

      ialert= ro8x88();
      if(ialert != 0) ale88o(ialert);
      else            iflspa= ID_LOADSPANN;
      
      if(fo8) fclose(fo8); 
      }

/*======================================================================
* Laden von Z88O5.TXT, wenn Anzeige der Spannungen in Gausspunkten
*=====================================================================*/ 
    if(iflao5 == ID_NOTLOADSPAO5 && if3d == IDM_SHOWGAUPU)
      {
      fo5= fopen("z88o5.txt","r");
      if(fo5 == NULL)
        {
        ale88o(AL_NOO5);    
        wlog88o(0,LOG_NOO5);
        goto Lflush;
        }
      rewind(fo5);

      ialert= ro5x88(); 
      if(ialert != 0) ale88o(ialert);
      else            iflao5= ID_LOADSPAO5;

      if(fo5) fclose(fo5); 
      }

/*======================================================================
* Anzeige Randbedingungen ausschalten fuer die folgenden anderen Anzeigen
*=====================================================================*/ 
    if(if3d == IDM_SHOWSPANN || if3d == IDM_SHOWGAUSS || if3d == IDM_SHOWGAUPU ||
       if3d == IDM_SHOWVX    || if3d == IDM_SHOWVY    || if3d == IDM_SHOWVZ)
      {
      ifrbd= IDM_NORBD;
      }

/*======================================================================
* Berechnen der Spannungs- und Verschiebungsfarbwerte
*=====================================================================*/ 
    if(if3d == IDM_SHOWSPANN && iflspa == ID_LOADSPANN) stro88();
    if(if3d == IDM_SHOWGAUSS && iflspa == ID_LOADSPANN) snow88();
    if(if3d == IDM_SHOWGAUPU && iflao5 == ID_LOADSPAO5) spgp88();
    if(if3d == IDM_SHOWVX)    fvx88();
    if(if3d == IDM_SHOWVY)    fvy88();  
    if(if3d == IDM_SHOWVZ)    fvz88();   

/*======================================================================
* Spannungsskala bzw. Verschiebungsskala zeichnen
*=====================================================================*/
    if((if3d == IDM_SHOWSPANN && iflspa == ID_LOADSPANN) || 
       (if3d == IDM_SHOWGAUSS && iflspa == ID_LOADSPANN) || 
       (if3d == IDM_SHOWGAUPU && iflao5 == ID_LOADSPAO5) ||
       if3d == IDM_SHOWVX    ||  if3d == IDM_SHOWVY      || if3d == IDM_SHOWVZ)
      {
      glDisable(GL_NORMALIZE);
      glDisable(GL_LIGHTING);
      glShadeModel(GL_FLAT);
      fsca88();
      }

/*======================================================================
* Randbedingungsskala zeichnen
*=====================================================================*/
    if(ifrbd == IDM_YESRBD && iflarbd == ID_LOADRBD) 
      {
      glDisable(GL_NORMALIZE);
      glDisable(GL_LIGHTING);
      glShadeModel(GL_FLAT);
      fsrb88();
      }

/*========================================================
* Licht ?
*=======================================================*/
    if(if3d == IDM_LIGHT)
      {
      glEnable(GL_NORMALIZE);
      glEnable(GL_LIGHTING);

      glLightfv(GL_LIGHT0,GL_SPECULAR,specula0);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,diffuse0 );
      glLightfv(GL_LIGHT0,GL_POSITION,positio0);
      glLightfv(GL_LIGHT0,GL_AMBIENT ,ambient0 );
      glEnable(GL_LIGHT0);

      glLightfv(GL_LIGHT1,GL_SPECULAR,specula1);
      glLightfv(GL_LIGHT1,GL_DIFFUSE ,diffuse1);
      glLightfv(GL_LIGHT1,GL_POSITION,positio1);
      glLightfv(GL_LIGHT1,GL_AMBIENT ,ambient1);
      glEnable(GL_LIGHT1);

      glLightfv(GL_LIGHT2,GL_SPECULAR,specula2);
      glLightfv(GL_LIGHT2,GL_POSITION,positio2);
      glEnable(GL_LIGHT2);

      glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,diff_mat);
      glMaterialfv(GL_FRONT,GL_SPECULAR,spec_mat);
      glMaterialfv(GL_FRONT,GL_SHININESS,shine);
      }

/*========================================================
* Die Transformationen ausfuehren
*=======================================================*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    if(ifmaus == IDM_ZOOM)  /* Zoom */
      {
      s=8./3.*xx*xx/IB/IB+1./3.;
      if(s < 0.) s= 0.;
      }

    if(ifmaus == IDM_PAN)  /* Panning */
      {
      xw= (FR_DOUBLE)IB;
      ty= -yp*2/(xw/2) *(yy-xw/2);
      tx= -yp*2/(xw/2) *(xw/2-xx);
      }

    if(ifmaus == IDM_ROTATE)  /* Rotieren */
      {
      rx= yy;
      ry= xx;
      }

    if(ifkom == ID_MOUSE)
      {
      glScaled(s,s,s);
      glTranslated(tx,ty,0);
      glRotated(rx,0.,1.,0.);
      glRotated(ry,1.,0.,0.);
      }

    if(ifkom == ID_FUNKEY);
      {
      glRotated(rotx,1.,0.,0.);
      glRotated(roty,0.,1.,0.);
      glRotated(rotz,0.,0.,1.);
      }

/*========================================================
* Koordinaten umrechnen
*=======================================================*/
    if(ifverf == IDM_UNVERFORMT) vu3b88();
    else                         vv3b88();

/*========================================================
* Schleife ueber alle Elemente, mit Licht
*=======================================================*/
    if(ifkoor == IDM_YESKOOR) 
      {
      glColor3f(hide_col[0],hide_col[1],hide_col[2]);
      mko88();
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 1) mit Licht
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(if3d == IDM_LIGHT) 
      {
      tet188();
      if(ifrbd == IDM_YESRBD) 
        {
        glDisable(GL_NORMALIZE);
        glDisable(GL_LIGHTING);
        glShadeModel(GL_SMOOTH);
        mrbd88();
        }
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 2) Hidden Lines 
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(if3d == IDM_HIDDEN && ndim == 3) 
      {
      glDisable(GL_NORMALIZE);
      glDisable(GL_LIGHTING);
      glEnable(GL_DEPTH_TEST);
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glColor3f(hide_col[0],hide_col[1],hide_col[2]);
      tet388();

      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glEnable(GL_POLYGON_OFFSET_FILL);
      glPolygonOffset(hide_off[0],hide_off[1]);
      glColor3f(back_col[0],back_col[1],back_col[2]);
      tet388();

      if(ifrbd == IDM_YESRBD) mrbd88();

      glDisable(GL_POLYGON_OFFSET_FILL); 
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 3) Wireframe
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(if3d == IDM_WIREFR) 
      {
      glDisable(GL_NORMALIZE);
      glDisable(GL_LIGHTING);
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glColor3f(hide_col[0],hide_col[1],hide_col[2]);
      tet588();
      if(ifrbd == IDM_YESRBD) mrbd88();
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 4) Spannungen an Eckknoten, Verschiebungen an Eckknoten
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(if3d == IDM_SHOWSPANN || if3d == IDM_SHOWVX    ||
       if3d == IDM_SHOWVY    || if3d == IDM_SHOWVZ)
      {
      glDisable(GL_NORMALIZE);
      glDisable(GL_LIGHTING);
      glShadeModel(GL_SMOOTH);
      tet288();

      if(ndim == 3 && ifnost == IDM_YESNOST)
        {
        glLineWidth(bline);

        glDisable(GL_NORMALIZE);
        glDisable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glColor3f(hide_col[0],hide_col[1],hide_col[2]);
        tet388();

        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(hide_off[0],hide_off[1]);
        glColor3f(back_col[0],back_col[1],back_col[2]);
        tet388();

        glDisable(GL_POLYGON_OFFSET_FILL); 
        glLineWidth(1.0);
        }
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 5) Spannungen pro Element gemittelt
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(if3d == IDM_SHOWGAUSS)
      {
      glDisable(GL_NORMALIZE);
      glDisable(GL_LIGHTING);
      glShadeModel(GL_FLAT);
      tet488();

      if(ndim == 3 && ifnost == IDM_YESNOST)
        {
        glLineWidth(bline);

        glDisable(GL_NORMALIZE);
        glDisable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        glColor3f(hide_col[0],hide_col[1],hide_col[2]);
        tet388();

        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(hide_off[0],hide_off[1]);
        glColor3f(back_col[0],back_col[1],back_col[2]);
        tet388();

        glDisable(GL_POLYGON_OFFSET_FILL); 
        glLineWidth(1.0);
        }
      }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* 6) Spannungen in den Gausspunkten
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    if(if3d == IDM_SHOWGAUPU && ifverf == IDM_UNVERFORMT &&
       iflao5 == ID_LOADSPAO5) 
      {
      glDisable(GL_NORMALIZE);
      glDisable(GL_LIGHTING);
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glColor3f(hide_col[0],hide_col[1],hide_col[2]);
      tet588();
      vgpc88();
      spgp88();
      magp88();
      }

/*========================================================
* Knotennummern plotten ?
*=======================================================*/
    if((iflabe == IDM_KNOTEN || iflabe == IDM_LALLES) 
        &&
       (if3d == IDM_WIREFR   || 
       (if3d == IDM_HIDDEN && ndim == 3))) malk88();

/*========================================================
* fertig OpenGL
*=======================================================*/
Lflush:
if(gdk_gl_drawable_is_double_buffered(gldrawable))
  gdk_gl_drawable_swap_buffers(gldrawable);
else
  glFlush();
gdk_gl_drawable_gl_end (gldrawable);
}



