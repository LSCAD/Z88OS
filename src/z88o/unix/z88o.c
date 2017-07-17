/*****************************************************************************
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
*****************************************************************************/ 
/*****************************************************************************
* Z88O fuer UNIX, X11 und gtk+
* 18.11.2015 Rieg
*****************************************************************************/
/*****************************************************************************
* UNIX
*****************************************************************************/
#ifdef FR_UNIX
#include <z88o.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gdkgl.h>
#include <gtkglarea.h>
#include <gtk/gtk.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

/*****************************************************************************
* Functions
*****************************************************************************/
void WMU_SIZE   (GtkWidget *,GdkEventConfigure *,gpointer);
void WMU_PAINT  (GtkWidget *,GdkEventExpose *,gpointer);
void WM_KEY    (GtkWidget *,gpointer);
void WMU_DESTROY(GtkWidget *,gpointer);
void WMU_CREATE (GtkWidget *,gpointer);

void CB_MATA   (GtkWidget *,GdkEvent *,gpointer);

void CB_WER   (GtkWidget *,gpointer);
void CB_HELP  (GtkWidget *,gpointer);
void CB_RUN   (GtkWidget *,gpointer);
void CB_FILE  (GtkWidget *,gpointer);
void CB_ASCA  (GtkWidget *,gpointer);
void CB_MAUS  (GtkWidget *,gpointer);
void CB_UNVER (GtkWidget *,gpointer);
void CB_VERFO (GtkWidget *,gpointer);
void CB_LIGHT (GtkWidget *,gpointer);
void CB_HIDDE (GtkWidget *,gpointer);
void CB_WIREF (GtkWidget *,gpointer);
void CB_SSPAN (GtkWidget *,gpointer);
void CB_SGAUS (GtkWidget *,gpointer);
void CB_SGAPU (GtkWidget *,gpointer);
void CB_VX    (GtkWidget *,gpointer);
void CB_VY    (GtkWidget *,gpointer);
void CB_VZ    (GtkWidget *,gpointer);
void CB_SRBD  (GtkWidget *,gpointer);
void CB_KOOR  (GtkWidget *,gpointer);
void CB_NOLA  (GtkWidget *,gpointer);
void CB_NODE  (GtkWidget *,gpointer);
void CB_ELE   (GtkWidget *,gpointer);
void CB_ALLE  (GtkWidget *,gpointer);
void CB_VER   (GtkWidget *,gpointer);
void CB_ROT   (GtkWidget *,gpointer);
void CB_ZM    (GtkWidget *,gpointer);
void CB_NORBD (GtkWidget *,gpointer);
void CB_YESRBD(GtkWidget *,gpointer);
void CB_ZOPLUS(GtkWidget *,gpointer);
void CB_ZOMINUS(GtkWidget *,gpointer);
void CB_RBDALL(GtkWidget *,gpointer);
void CB_RBDUX (GtkWidget *,gpointer);
void CB_RBDUY (GtkWidget *,gpointer);
void CB_RBDUZ (GtkWidget *,gpointer);
void CB_RBDU4 (GtkWidget *,gpointer);
void CB_RBDU5 (GtkWidget *,gpointer);
void CB_RBDU6 (GtkWidget *,gpointer);
void CB_RBDUA (GtkWidget *,gpointer);
void CB_RBDOL (GtkWidget *,gpointer);
void CB_RBDFX (GtkWidget *,gpointer);
void CB_RBDFY (GtkWidget *,gpointer);
void CB_RBDFZ (GtkWidget *,gpointer);
void CB_GPZOPLUS(GtkWidget *,gpointer);
void CB_GPZOMINUS (GtkWidget *,gpointer);
void CB_NONOST (GtkWidget *,gpointer);
void CB_YESNOST(GtkWidget *,gpointer);

/***********************************************************************
*  Function-Declarationen
***********************************************************************/
int      dyn88o(void);
void     ri1x88(void);
void     ri2x88(void);
int      ro2x88(void);
int      ro8x88(void);
int      rcoo88(void);
int      wlog88o(FR_INT4,int);
int      ale88o(int);
int      lan88o(void);
int      vu3b88(void);
int      vv3b88(void);
int      vsca88(void);
int      vcur88(void);
int      stro88(void);
int      snow88(void);
int      fvx88(void);
int      fvy88(void);
int      fvz88(void);
int      tet188(void);
int      tet288(void);
int      tet388(void);
int      tet488(void);
int      tet588(void);
int      fsca88(void);
int      fsrb88(void);
int      mrbd88(void);
int      man88o(void);

/*****************************************************************************
* Globale Variable
*****************************************************************************/
GtkWidget *H_WIN;
GtkWidget *DRAWA;

FILE *fdyn,*fwlo,*fi1,*fi2,*fi5,*fo2,*fo5,*fo8,*fman;

int IW_DRAWAR,IH_DRAWAR; 
/*
** fdyn= z88.dyn
** fwlo= z88o.log
** fo2=  z88o2.txt
** fi1=  z88i1.txt
** fi2=  z88i2.txt
** fi5=  z88i5.txt
** fo5=  z88o5.txt
** fo8=  z88o8.txt
** fman= z88man.txt
*/ 

FR_DOUBLEAY x;
FR_DOUBLEAY y;
FR_DOUBLEAY z;
FR_DOUBLEAY ux;
FR_DOUBLEAY uy;
FR_DOUBLEAY uz;
FR_DOUBLEAY xv;
FR_DOUBLEAY yv;
FR_DOUBLEAY zv;
FR_DOUBLEAY sep;
FR_DOUBLEAY sne;
FR_DOUBLEAY rwert;
FR_DOUBLEAY xgp;
FR_DOUBLEAY ygp;
FR_DOUBLEAY zgp;
FR_DOUBLEAY xgpo;
FR_DOUBLEAY ygpo;
FR_DOUBLEAY zgpo;
FR_DOUBLEAY siggp;

FR_INT4AY   ityp;
FR_INT4AY   koi;
FR_INT4AY   ityp;
FR_INT4AY   koffs;
FR_INT4AY   noi;
FR_INT4AY   noffs;
FR_INT4AY   nep;
FR_INT4AY   iep;
FR_INT4AY   ifarbe;
FR_INT4AY   jfarbe;
FR_INT4AY   kfarbe;
FR_INT4AY   nkn;
FR_INT4AY   ifg;
FR_INT4AY   iflag1;

FR_DOUBLE   xe[9];
FR_DOUBLE   ye[9];
FR_DOUBLE   ze[9];
FR_DOUBLE   vx[13];
FR_DOUBLE   vy[13];
FR_DOUBLE   vz[13];
FR_DOUBLE   fspa[14];

FR_INT4     kf[9];

GLfloat     rot[13];
GLfloat     gruen[13];
GLfloat     blau[13];

GLfloat     back_col[4];
GLfloat     specula0[4];
GLfloat     specula1[4];
GLfloat     specula2[4];
GLfloat     ambient0[4];
GLfloat     ambient1[4];
GLfloat     diffuse0[4];
GLfloat     diffuse1[4];
GLfloat     positio0[4];
GLfloat     positio1[4];
GLfloat     positio2[4];
GLfloat     spec_mat[4];
GLfloat     diff_mat[4];
GLfloat     shine[1];
GLfloat     hide_col[3];
GLfloat     hide_off[2];
GLfloat     node_col[3];
GLfloat     elem_col[3];
GLfloat     bline= 2.0;

FR_DOUBLE xx= 0., yy=0.;
FR_DOUBLE rx= 0., ry= 0., rz= 0., s= 1., tx=0., ty=0.;

FR_DOUBLE xm= -100.0, xp= 100.0;
FR_DOUBLE ym= -100.0, yp= 100.0; 
FR_DOUBLE zm= -100.0, zp= 100.0;
FR_DOUBLE ymsv,ypsv,SV;

FR_DOUBLE xw= 100.;

FR_DOUBLE fux= 100., fuy= 100., fuz= 100.;
FR_DOUBLE facx= 1.,facy= 1.,facz= 1.;
FR_DOUBLE cx= 0.,cy= 0.,cz= 0.;
FR_DOUBLE rotx= 0.,roty= 0.,rotz= 0.;
FR_DOUBLE xmin,xmax,ymin,ymax,zmin,zmax,fycor;
FR_DOUBLE fzoom= 1.1;
FR_DOUBLE zorbd= 1.0;
FR_DOUBLE zoogp= 0.25;
FR_DOUBLE fazoo= 0.17;
FR_DOUBLE scale= 2.0;
FR_DOUBLE dicke= 2.0;

FR_DOUBLE sigmin,sigmax=0.,siginc;
FR_DOUBLE snemin,snemax=0.,sneinc;
FR_DOUBLE spamin,spamax=0.,spainc;
FR_DOUBLE fxmin,fxmax=-1e-10,fxinc;
FR_DOUBLE fymin,fymax=-1e-10,fyinc;
FR_DOUBLE fzmin,fzmax=-1e-10,fzinc;

FR_INT4 MAXKOI,MAXE,MAXK,MAXRBD,MAXPR,MAXGP;
FR_INT4 IDYNMEM,LANG=2;

FR_INT4 ndim,nkp,ne,nfg,neg,iepanz,kflag,ibflag,ipflag,iqflag;
FR_INT4 i,j,idummy,jdummy,kofold,nrb,npr,nnp;
FR_INT4 izoom= 1;
FR_INT4 jkvon= 0,jkbis= 0,jevon= 0,jebis= 0;
FR_INT4 isflag,igpanz;
FR_INT4 NEEDKOI;

int iflade= ID_NOTLOADSTRUC;
int iflaver=ID_NOTLOADVERF;
int iflspa= ID_NOTLOADSPANN; 
int iflao5= ID_NOTLOADSPAO5;
int iflarbd=ID_NOTLOADRBD;
int iflai5= ID_NOTLOADI5;

int ifkom=  ID_FUNKEY;

int ifmaus= IDM_ZOOM;
int ifverf= IDM_UNVERFORMT;
int if3d  = IDM_LIGHT;
int iflabe= IDM_NOLABELS;
int ifscale=IDM_YESSCALE;
int ifrbd = IDM_NORBD;
int ifwbc=  IDM_RBDALL;
int ifkoor= IDM_YESKOOR;
int ifnost= IDM_YESNOST;
int ifvcur;

int  iret,iplot;

int  IB,IH;
int  imatrix= 1;
int  ialert= 0;

int  *pp;

size_t laenge;

char cline[256];

char  cdyn[8]   = "z88.dyn";
char  clgd[12]  = "z88o.log";
char  cstrn[128]= "z88i1.txt";
char  ci2[10]   = "z88i2.txt";
char  ci5[10]   = "z88i5.txt";
char  co2[10]   = "z88o2.txt";
char  co5[10]   = "z88o5.txt";
char  co8[10]   = "z88o8.txt";
char  cman[11]  = "z88man.txt";

char  CBROWSER[128],CPREFIX[128];
char  CSCALE_FONT[32],CTHICK_FONT[32];

char  cfname[256];
char  ctname[256];

/*--------------------------------------------------------------------------
* Char-Arrays
*-------------------------------------------------------------------------*/
char cstore[256];
char cbcall[128];
char cbpref[128];
char cbhelp[512];
char cmess [512];
char cbytes[128];

/*--------------------------------------------------------------------------
* Widgets, die umgesteuert werden muessen
*-------------------------------------------------------------------------*/
GtkWidget *PB_UNVER,*PB_VERFO,*PB_LIGHT,*PB_HIDDE,*PB_WIREF;
GtkWidget *PB_SSPAN,*PB_SGAUS,*PB_SGAPU,*PB_VX,*PB_VY,*PB_VZ,*PB_SRBD,*PB_KOOR;

/*--------------------------------------------------------------------------
* fuer das gtkglarea-Widget
*-------------------------------------------------------------------------*/
int attrlist[]= {GDK_GL_RGBA,
                 GDK_GL_DOUBLEBUFFER,
                 GDK_GL_RED_SIZE,   8,
                 GDK_GL_GREEN_SIZE, 8,
                 GDK_GL_BLUE_SIZE,  8,
                 GDK_GL_DEPTH_SIZE,24,  /* bei Win und Mac gehen auch 32 */
                 GDK_GL_NONE};

/*****************************************************************************
* Main
*****************************************************************************/
int main (int argc, char *argv[])
{
GtkWidget *HBOX,*VBOX,*G_VBOX;
GtkWidget *HSEP1,*HSEP2,*HSEP3,*HSEP4;
GtkWidget *PB_RUN,*PB_QUIT,*PB_HELP,*PB_INFO,*PB_FILE,*PB_ASCA,*PB_MAUS;
GtkWidget *MENU_BAR,*MENU_LABEL,*MENU_LA,*PB_NOLA,*PB_NODE,*PB_ELE,*PB_ALLE;
GtkWidget *MENU_FAKTOR,*MENU_FA,*PB_VER,*PB_ROT,*PB_ZM;
GtkWidget *MENU_RANDB,*MENU_RB,*PB_NORBD,*PB_YESRBD,*PB_ZOPLUS,*PB_ZOMINUS;
GtkWidget *MENU_SUBRBD,*PB_RBDALL,*PB_RBDUX,*PB_RBDUY,*PB_RBDUZ,*PB_RBDU4;
GtkWidget *PB_SINRBD,*PB_RBDU5,*PB_RBDU6,*PB_RBDUA,*PB_RBDOL,*PB_RBDFX;
GtkWidget *PB_RBDFY,*PB_RBDFZ,*MENU_GAUSS,*MENU_GA,*PB_GPZOPLUS,*PB_GPZOMINUS;
GtkWidget *MENU_NOST,*MENU_NOSTYN,*PB_NONOST,*PB_YESNOST;

GtkTooltips *TT_FILE,*TT_ASCA,*TT_MAUS,*TT_UNVER,*TT_VERFO,*TT_LIGHT,*TT_HIDDE,*TT_WIREF;
GtkTooltips *TT_SSPAN,*TT_SGAUS,*TT_SGAPU,*TT_VX,*TT_VY,*TT_VZ,*TT_SRBD,*TT_KOOR;

gint      ispace= 3;

char      cstring[256];

/*----------------------------------------------------------------------------
*  gtk initialisieren
*---------------------------------------------------------------------------*/
gtk_init (&argc, &argv);

if(gdk_gl_query() == FALSE) 
  {
  g_print("OpenGL geht nicht!\n");
  return 0;
  }

/*---------------------------------------------------------------------------
* lan88o starten
*--------------------------------------------------------------------------*/
iret= lan88o();

if(iret != 0)
  {
  fprintf(stderr,"File Z88O.LOG is invalid or wrong! STOP !\n"); 
  exit(1); 
  }

/*----------------------------------------------------------------------------
* Z88.FCD einlesen.
*---------------------------------------------------------------------------*/
iret= rcoo88();

if(iret != 0)
  {
  if(LANG == 1) fprintf(stderr,"Datei Z88.FCD is ungueltig oder falsch! STOP !\n"); 
  if(LANG == 2) fprintf(stderr,"File Z88.FCD is invalid or wrong! STOP !\n");
  exit(1);
  }

scale= atof(CSCALE_FONT);
dicke= atof(CTHICK_FONT);

ym*= fycor;
yp*= fycor;

/*----------------------------------------------------------------------------
* dyn88o starten
*---------------------------------------------------------------------------*/
iret= dyn88o();
if(iret != 0) ale88o(iret);

/*----------------------------------------------------------------------------
*  Toplevel-Window und Standard-Events
*---------------------------------------------------------------------------*/
H_WIN = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW (H_WIN),"Z88O");

gtk_container_set_reallocate_redraws(GTK_CONTAINER (H_WIN),TRUE);

g_signal_connect(G_OBJECT(H_WIN),"key-press-event",G_CALLBACK (WM_KEY),    NULL);
g_signal_connect(G_OBJECT(H_WIN),"delete_event",   G_CALLBACK (WMU_DESTROY),NULL);

/*----------------------------------------------------------------------------
*  horizontale und vertikale Box
*---------------------------------------------------------------------------*/
HBOX =  gtk_hbox_new(FALSE, 0);
VBOX =  gtk_vbox_new(FALSE, 0);
G_VBOX= gtk_vbox_new(FALSE, 0);

/*----------------------------------------------------------------------------
*  das Drawing-Widget erzeugen
*---------------------------------------------------------------------------*/
DRAWA= GTK_WIDGET(gtk_gl_area_new(attrlist));

gtk_widget_set_size_request(DRAWA,IW_DRAWAR,IH_DRAWAR);

gtk_widget_set_events(DRAWA,GDK_EXPOSURE_MASK | GDK_BUTTON_PRESS_MASK |
                            GDK_BUTTON1_MOTION_MASK |
                            GDK_BUTTON2_MOTION_MASK |
                            GDK_BUTTON3_MOTION_MASK);

g_signal_connect(G_OBJECT(DRAWA),"motion_notify_event",G_CALLBACK(CB_MATA),NULL);
g_signal_connect(G_OBJECT(DRAWA),"configure_event",G_CALLBACK (WMU_SIZE),NULL);
g_signal_connect(G_OBJECT(DRAWA),"expose_event",G_CALLBACK(WMU_PAINT),NULL);
g_signal_connect_after(G_OBJECT(DRAWA),"realize",G_CALLBACK (WMU_CREATE),NULL);

gtk_box_pack_start(GTK_BOX(HBOX),DRAWA,TRUE,TRUE,0);

/*----------------------------------------------------------------------------
*  Buttons rechte Reihe (HBOX) erzeugen
*---------------------------------------------------------------------------*/
PB_RUN = gtk_button_new_with_label("Run");
g_signal_connect(G_OBJECT(PB_RUN),"clicked",G_CALLBACK(CB_RUN),NULL);

if(LANG == 1) strcpy(cstring,"Info");
if(LANG == 2) strcpy(cstring,"About");
PB_INFO = gtk_button_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_INFO),"clicked",G_CALLBACK(CB_WER),NULL);

if(LANG == 1) strcpy(cstring,"Hilfe");
if(LANG == 2) strcpy(cstring,"Help");
PB_HELP = gtk_button_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_HELP),"clicked",G_CALLBACK(CB_HELP),NULL);


if(LANG == 1) strcpy(cstring,"Ende");
if(LANG == 2) strcpy(cstring,"Quit");
PB_QUIT= gtk_button_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_QUIT),"clicked",G_CALLBACK(WMU_DESTROY),NULL);

HSEP1= gtk_hseparator_new();

if(LANG == 1) strcpy(cstring,"Datei");
if(LANG == 2) strcpy(cstring,"File");
PB_FILE= gtk_button_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_FILE),"clicked",G_CALLBACK (CB_FILE),NULL);
TT_FILE= gtk_tooltips_new();
if(LANG == 1) strcpy(cstring,"Strukturfile angeben,Z88I1.TXT ist Default");
if(LANG == 2) strcpy(cstring,"Choose Structure File,Z88I1.TXT is Default");
gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_FILE),PB_FILE,cstring,NULL);

PB_ASCA= gtk_button_new_with_label("Autoscale");
g_signal_connect(G_OBJECT(PB_ASCA),"clicked",G_CALLBACK(CB_ASCA),NULL);
TT_ASCA= gtk_tooltips_new();
if(LANG == 1) strcpy(cstring,"Autoskalieren - Struktur einpassen");
if(LANG == 2) strcpy(cstring,"AutoScale - fit structure");
gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_ASCA),PB_ASCA,cstring,NULL);

if(LANG == 1) strcpy(cstring,"* Tastatur / Maus");
if(LANG == 2) strcpy(cstring,"* Keyboard / Mouse");
PB_MAUS= gtk_button_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_MAUS),"clicked",G_CALLBACK(CB_MAUS),NULL);
TT_MAUS= gtk_tooltips_new();
if(LANG == 1) strcpy(cstring,"Zoom-Schieben-Rotieren ueber Tastatur oder Maus");
if(LANG == 2) strcpy(cstring,"Zoom-Pan-Rotate via Keyboard or Mouse");
gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_MAUS),PB_MAUS,cstring,NULL);

HSEP2= gtk_hseparator_new();

if(LANG == 1) strcpy(cstring,"* unverformt");
if(LANG == 2) strcpy(cstring,"* undeflected");
PB_UNVER= gtk_button_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_UNVER),"clicked",G_CALLBACK(CB_UNVER),NULL);
TT_UNVER= gtk_tooltips_new();
if(LANG == 1) strcpy(cstring,"Zeige unverformte Struktur");
if(LANG == 2) strcpy(cstring,"Show undeflected Structure");
gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_UNVER),PB_UNVER,cstring,NULL);

if(LANG == 1) strcpy(cstring,"verformt");
if(LANG == 2) strcpy(cstring,"deflected");
PB_VERFO= gtk_button_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_VERFO),"clicked",G_CALLBACK(CB_VERFO),NULL);
TT_VERFO= gtk_tooltips_new();
if(LANG == 1) strcpy(cstring,"Zeige verformte Struktur");
if(LANG == 2) strcpy(cstring,"Show deflected Structure");
gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_VERFO),PB_VERFO,cstring,NULL);

HSEP3= gtk_hseparator_new();

if(LANG == 1) strcpy(cstring,"* Licht");
if(LANG == 2) strcpy(cstring,"* Light");
PB_LIGHT= gtk_button_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_LIGHT),"clicked",G_CALLBACK(CB_LIGHT),NULL);
TT_LIGHT= gtk_tooltips_new();
if(LANG == 1) strcpy(cstring,"Licht an, auf Wunsch Anzeige der Randbedingungen");
if(LANG == 2) strcpy(cstring,"Light on, show Boundary Conditions on request");
gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_LIGHT),PB_LIGHT,cstring,NULL);

PB_HIDDE= gtk_button_new_with_label("Hidden Line");
g_signal_connect(G_OBJECT(PB_HIDDE),"clicked",G_CALLBACK(CB_HIDDE),NULL);
TT_HIDDE= gtk_tooltips_new();
if(LANG == 1) strcpy(cstring,"Verdeckte Linien (nur 3D), auf Wunsch Anzeige der Randbedingungen");
if(LANG == 2) strcpy(cstring,"Hidden Line (3D only), show Boundary Conditions on request");
gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_HIDDE),PB_HIDDE,cstring,NULL);

PB_WIREF= gtk_button_new_with_label("Wireframe");
g_signal_connect(G_OBJECT(PB_WIREF),"clicked",G_CALLBACK(CB_WIREF),NULL);
TT_WIREF= gtk_tooltips_new();
if(LANG == 1) strcpy(cstring,"Wireframe, auf Wunsch Anzeige der Randbedingungen");
if(LANG == 2) strcpy(cstring,"Wireframe, show Boundary Conditions on request");
gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_WIREF),PB_WIREF,cstring,NULL);

if(LANG == 1) strcpy(cstring,"Spannungen Eckknoten");
if(LANG == 2) strcpy(cstring,"Stresses Corner Nodes");
PB_SSPAN= gtk_button_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_SSPAN),"clicked",G_CALLBACK(CB_SSPAN),NULL);
TT_SSPAN= gtk_tooltips_new();
if(LANG == 1) strcpy(cstring,"Vergleichsspannungen (GEH,NH,SH: abhaengig von Z88D) in den Eckknoten");
if(LANG == 2) strcpy(cstring,"Reduced Stresses (v.Mises,Rankine,Tresca:depending from Z88D) in corner nodes");
gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_SSPAN),PB_SSPAN,cstring,NULL);

if(LANG == 1) strcpy(cstring,"Spannungen pro Element");
if(LANG == 2) strcpy(cstring,"Stresses per Element");
PB_SGAUS= gtk_button_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_SGAUS),"clicked",G_CALLBACK(CB_SGAUS),NULL);
TT_SGAUS= gtk_tooltips_new();
if(LANG == 1) strcpy(cstring,"Vergleichsspannungen (GEH,NH,SH: abhaengig von Z88D) pro Element gemittelt");
if(LANG == 2) strcpy(cstring,"Reduced Stresses (v.Mises,Rankine,Tresca:depending from Z88D),mean values per Element");
gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_SGAUS),PB_SGAUS,cstring,NULL);

if(LANG == 1) strcpy(cstring,"Spannungen Gausspunkte");
if(LANG == 2) strcpy(cstring,"Stresses Gauss Points");
PB_SGAPU= gtk_button_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_SGAPU),"clicked",G_CALLBACK(CB_SGAPU),NULL);
TT_SGAPU= gtk_tooltips_new();
if(LANG == 1) strcpy(cstring,"Vergleichsspannungen (GEH,NH,SH: abhaengig von Z88D) -nur unverformte Struktur- in den Gausspunkten");
if(LANG == 2) strcpy(cstring,"Reduced Stresses (v.Mises,Rankine,Tresca:depending from Z88D) -undeflected Structure only- in Gauss Points");
gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_SGAPU),PB_SGAPU,cstring,NULL);

if(LANG == 1) strcpy(cstring,"Verschiebungen X");
if(LANG == 2) strcpy(cstring,"Deflections X");
PB_VX= gtk_button_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_VX),"clicked",G_CALLBACK(CB_VX),NULL);
TT_VX= gtk_tooltips_new();
if(LANG == 1) strcpy(cstring,"Zeige X-Verschiebungen");
if(LANG == 2) strcpy(cstring,"Show X Displacements");
gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_VX),PB_VX,cstring,NULL);

if(LANG == 1) strcpy(cstring,"Verschiebungen Y");
if(LANG == 2) strcpy(cstring,"Deflections Y");
PB_VY= gtk_button_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_VY),"clicked",G_CALLBACK(CB_VY),NULL);
TT_VY= gtk_tooltips_new();
if(LANG == 1) strcpy(cstring,"Zeige Y-Verschiebungen");
if(LANG == 2) strcpy(cstring,"Show Y Displacements");
gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_VY),PB_VY,cstring,NULL);

if(LANG == 1) strcpy(cstring,"Verschiebungen Z");
if(LANG == 2) strcpy(cstring,"Deflections Z");
PB_VZ= gtk_button_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_VZ),"clicked",G_CALLBACK(CB_VZ),NULL);
TT_VZ= gtk_tooltips_new();
if(LANG == 1) strcpy(cstring,"Zeige Z-Verschiebungen");
if(LANG == 2) strcpy(cstring,"Show Z Displacements");
gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_VZ),PB_VZ,cstring,NULL);

HSEP4= gtk_hseparator_new();

if(LANG == 1) strcpy(cstring,"Zeige die Randbedingungen");
if(LANG == 2) strcpy(cstring,"Show Boundary Conditions");
PB_SRBD= gtk_button_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_SRBD),"clicked",G_CALLBACK(CB_SRBD),NULL);
TT_SRBD= gtk_tooltips_new();
if(LANG == 1) strcpy(cstring,"Zeige Randbedingungen ja/nein (nur Licht/Hidden Line/Wireframe)");
if(LANG == 2) strcpy(cstring,"Show Boundary Conditions yes/no (Light/hidden Line/Wireframe only)");
gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_SRBD),PB_SRBD,cstring,NULL);

if(LANG == 1) strcpy(cstring,"Zeige Koordinatensystem");
if(LANG == 2) strcpy(cstring,"Show Coordinate System");
PB_KOOR= gtk_button_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_KOOR),"clicked",G_CALLBACK(CB_KOOR),NULL);
TT_KOOR= gtk_tooltips_new();
if(LANG == 1) strcpy(cstring,"Zeige Koordinatensystem ja/nein");
if(LANG == 2) strcpy(cstring,"Show Coordinate System yes/no");
gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_KOOR),PB_KOOR,cstring,NULL);

gtk_box_pack_start(GTK_BOX(VBOX),PB_RUN,  FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(VBOX),PB_INFO, FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(VBOX),PB_HELP, FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(VBOX),PB_QUIT, FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(VBOX),HSEP1,   FALSE,FALSE,ispace);

gtk_box_pack_start(GTK_BOX(VBOX),PB_FILE, FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(VBOX),PB_ASCA, FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(VBOX),PB_MAUS, FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(VBOX),HSEP2,   FALSE,FALSE,ispace);

gtk_box_pack_start(GTK_BOX(VBOX),PB_UNVER,FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(VBOX),PB_VERFO,FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(VBOX),HSEP3,   FALSE,FALSE,ispace);

gtk_box_pack_start(GTK_BOX(VBOX),PB_LIGHT,FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(VBOX),PB_HIDDE,FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(VBOX),PB_WIREF,FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(VBOX),PB_SSPAN,FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(VBOX),PB_SGAUS,FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(VBOX),PB_SGAPU,FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(VBOX),PB_VX,   FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(VBOX),PB_VY,   FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(VBOX),PB_VZ,   FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(VBOX),HSEP4,   FALSE,FALSE,ispace);

gtk_box_pack_start(GTK_BOX(VBOX),PB_SRBD, FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(VBOX),PB_KOOR, FALSE,FALSE,ispace);

gtk_box_pack_start(GTK_BOX(HBOX),VBOX,FALSE,FALSE,ispace);
 
/*----------------------------------------------------------------------------
*  Menue aufbauen
*---------------------------------------------------------------------------*/
MENU_BAR= gtk_menu_bar_new();

/*============================================================================
*  das Label-Menu
*===========================================================================*/
MENU_LABEL= gtk_menu_item_new_with_label("Labels");
gtk_menu_bar_append(GTK_MENU_SHELL(MENU_BAR),MENU_LABEL);

MENU_LA=  gtk_menu_new();
gtk_menu_item_set_submenu(GTK_MENU_ITEM(MENU_LABEL),MENU_LA);

if(LANG == 1) strcpy(cstring,"keine Labels");
if(LANG == 2) strcpy(cstring,"No Labels");
PB_NOLA= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_NOLA),"activate",G_CALLBACK(CB_NOLA),NULL);

if(LANG == 1) strcpy(cstring,"Knoten");
if(LANG == 2) strcpy(cstring,"Nodes");
PB_NODE= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_NODE),"activate",G_CALLBACK(CB_NODE),NULL);

if(LANG == 1) strcpy(cstring,"Elemente");
if(LANG == 2) strcpy(cstring,"Elements"); 
PB_ELE= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_ELE),"activate",G_CALLBACK(CB_ELE),NULL);

if(LANG == 1) strcpy(cstring,"Alles labeln");
if(LANG == 2) strcpy(cstring,"Label all");
PB_ALLE= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_ALLE),"activate",G_CALLBACK(CB_ALLE),NULL);

gtk_menu_append(GTK_MENU(MENU_LA),PB_NOLA);
gtk_menu_append(GTK_MENU(MENU_LA),PB_NODE);
gtk_menu_append(GTK_MENU(MENU_LA),PB_ELE);
gtk_menu_append(GTK_MENU(MENU_LA),PB_ALLE);

/*============================================================================
*  das Faktor-Menu
*===========================================================================*/
if(LANG == 1) strcpy(cstring,"Faktoren");
if(LANG == 2) strcpy(cstring,"Factors");
MENU_FAKTOR= gtk_menu_item_new_with_label(cstring);
gtk_menu_bar_append(GTK_MENU_SHELL(MENU_BAR),MENU_FAKTOR);

MENU_FA=  gtk_menu_new();
gtk_menu_item_set_submenu(GTK_MENU_ITEM(MENU_FAKTOR),MENU_FA);

if(LANG == 1) strcpy(cstring,"Verschiebungen");
if(LANG == 2) strcpy(cstring,"Deflections");
PB_VER= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_VER),"activate",G_CALLBACK(CB_VER),NULL);

if(LANG == 1) strcpy(cstring,"Rotationen 3D");
if(LANG == 2) strcpy(cstring,"Rotations 3D");
PB_ROT= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_ROT),"activate",G_CALLBACK(CB_ROT),NULL);

if(LANG == 1) strcpy(cstring,"Z-Limit zum Betrachter");
if(LANG == 2) strcpy(cstring,"Z limit towards you");
PB_ZM= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_ZM),"activate",G_CALLBACK(CB_ZM),NULL);

gtk_menu_append(GTK_MENU(MENU_FA),PB_VER);
gtk_menu_append(GTK_MENU(MENU_FA),PB_ROT);
gtk_menu_append(GTK_MENU(MENU_FA),PB_ZM);

/*============================================================================
*  das Randbedingungs-Menu
*===========================================================================*/
if(LANG == 1) strcpy(cstring,"Randbedingungen");
if(LANG == 2) strcpy(cstring,"Boundary Conditions");
MENU_RANDB= gtk_menu_item_new_with_label(cstring);
gtk_menu_bar_append(GTK_MENU_SHELL(MENU_BAR),MENU_RANDB);

MENU_RB=  gtk_menu_new();
gtk_menu_item_set_submenu(GTK_MENU_ITEM(MENU_RANDB),MENU_RB);

if(LANG == 1) strcpy(cstring,"RB nicht zeigen");
if(LANG == 2) strcpy(cstring,"Don't show BCs");
PB_NORBD= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_NORBD),"activate",G_CALLBACK(CB_NORBD),NULL);

if(LANG == 1) strcpy(cstring,"RB zeigen");
if(LANG == 2) strcpy(cstring,"Show BCs");
PB_YESRBD= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_YESRBD),"activate",G_CALLBACK(CB_YESRBD),NULL);

PB_ZOPLUS= gtk_menu_item_new_with_label("Zoom +");
g_signal_connect(G_OBJECT(PB_ZOPLUS),"activate",G_CALLBACK(CB_ZOPLUS),NULL);

PB_ZOMINUS= gtk_menu_item_new_with_label("Zoom -");
g_signal_connect(G_OBJECT(PB_ZOMINUS),"activate",G_CALLBACK(CB_ZOMINUS),NULL);

if(LANG == 1) strcpy(cstring,"nur einzelne RB zeigen");
if(LANG == 2) strcpy(cstring,"Only show single BC");
PB_SINRBD= gtk_menu_item_new_with_label(cstring);

gtk_menu_append(GTK_MENU(MENU_RB),PB_NORBD);
gtk_menu_append(GTK_MENU(MENU_RB),PB_YESRBD);
gtk_menu_append(GTK_MENU(MENU_RB),PB_ZOPLUS);
gtk_menu_append(GTK_MENU(MENU_RB),PB_ZOMINUS);
gtk_menu_append(GTK_MENU(MENU_RB),PB_SINRBD);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  das Randbedingungs-Untermenu
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
MENU_SUBRBD= gtk_menu_new();
gtk_menu_item_set_submenu(GTK_MENU_ITEM(PB_SINRBD),MENU_SUBRBD);

if(LANG == 1) strcpy(cstring,"alle RB");
if(LANG == 2) strcpy(cstring,"all the BCs");
PB_RBDALL= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_RBDALL),"activate",G_CALLBACK(CB_RBDALL),NULL);

if(LANG == 1) strcpy(cstring,"nur U1=UX=0");
if(LANG == 2) strcpy(cstring,"only U1=UX=0");
PB_RBDUX= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_RBDUX),"activate",G_CALLBACK(CB_RBDUX),NULL);

if(LANG == 1) strcpy(cstring,"nur U2=UY=0");
if(LANG == 2) strcpy(cstring,"only U2=UY=0");
PB_RBDUY= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_RBDUY),"activate",G_CALLBACK(CB_RBDUY),NULL);

if(LANG == 1) strcpy(cstring,"nur U3=UZ=0");
if(LANG == 2) strcpy(cstring,"only U3=UZ=0");
PB_RBDUZ= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_RBDUZ),"activate",G_CALLBACK(CB_RBDUZ),NULL);

if(LANG == 1) strcpy(cstring,"nur U4=RotX=0");
if(LANG == 2) strcpy(cstring,"only U4=RotX=0");
PB_RBDU4= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_RBDU4),"activate",G_CALLBACK(CB_RBDU4),NULL);

if(LANG == 1) strcpy(cstring,"nur U5=RotY=0");
if(LANG == 2) strcpy(cstring,"only U5=RotY=0");
PB_RBDU5= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_RBDU5),"activate",G_CALLBACK(CB_RBDU5),NULL);

if(LANG == 1) strcpy(cstring,"nur U6=RotZ=0");
if(LANG == 2) strcpy(cstring,"only U6=RotZ=0");
PB_RBDU6= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_RBDU6),"activate",G_CALLBACK(CB_RBDU6),NULL);

if(LANG == 1) strcpy(cstring,"nur U vorgegeben");
if(LANG == 2) strcpy(cstring,"only U given");
PB_RBDUA= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_RBDUA),"activate",G_CALLBACK(CB_RBDUA),NULL);

if(LANG == 1) strcpy(cstring,"nur Oberflaechenlasten");
if(LANG == 2) strcpy(cstring,"only Surface Loads");
PB_RBDOL= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_RBDOL),"activate",G_CALLBACK(CB_RBDOL),NULL);

if(LANG == 1) strcpy(cstring,"nur Kraefte X");
if(LANG == 2) strcpy(cstring,"only Forces X");
PB_RBDFX= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_RBDFX),"activate",G_CALLBACK(CB_RBDFX),NULL);

if(LANG == 1) strcpy(cstring,"nur Kraefte Y");
if(LANG == 2) strcpy(cstring,"only Forces Y");
PB_RBDFY= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_RBDFY),"activate",G_CALLBACK(CB_RBDFY),NULL);

if(LANG == 1) strcpy(cstring,"nur Kraefte Z");
if(LANG == 2) strcpy(cstring,"only Forces Z");
PB_RBDFZ= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_RBDFZ),"activate",G_CALLBACK(CB_RBDFZ),NULL);

gtk_menu_append(GTK_MENU(MENU_SUBRBD),PB_RBDALL);
gtk_menu_append(GTK_MENU(MENU_SUBRBD),PB_RBDUX);
gtk_menu_append(GTK_MENU(MENU_SUBRBD),PB_RBDUY);
gtk_menu_append(GTK_MENU(MENU_SUBRBD),PB_RBDUZ);
gtk_menu_append(GTK_MENU(MENU_SUBRBD),PB_RBDU4);
gtk_menu_append(GTK_MENU(MENU_SUBRBD),PB_RBDU5);
gtk_menu_append(GTK_MENU(MENU_SUBRBD),PB_RBDU6);
gtk_menu_append(GTK_MENU(MENU_SUBRBD),PB_RBDUA);
gtk_menu_append(GTK_MENU(MENU_SUBRBD),PB_RBDOL);
gtk_menu_append(GTK_MENU(MENU_SUBRBD),PB_RBDFX);
gtk_menu_append(GTK_MENU(MENU_SUBRBD),PB_RBDFY);
gtk_menu_append(GTK_MENU(MENU_SUBRBD),PB_RBDFZ);

/*============================================================================
*  das Groesse-Gausspunkte-Menu
*===========================================================================*/
if(LANG == 1) strcpy(cstring,"Groesse Gausspt.");
if(LANG == 2) strcpy(cstring,"Size Gausspt.");
MENU_GAUSS= gtk_menu_item_new_with_label(cstring);
gtk_menu_bar_append(GTK_MENU_SHELL(MENU_BAR),MENU_GAUSS);

MENU_GA=  gtk_menu_new();
gtk_menu_item_set_submenu(GTK_MENU_ITEM(MENU_GAUSS),MENU_GA);

PB_GPZOPLUS= gtk_menu_item_new_with_label("Zoom +");
g_signal_connect(G_OBJECT(PB_GPZOPLUS),"activate",G_CALLBACK(CB_GPZOPLUS),NULL);

PB_GPZOMINUS= gtk_menu_item_new_with_label("Zoom -");
g_signal_connect(G_OBJECT(PB_GPZOMINUS),"activate",G_CALLBACK(CB_GPZOMINUS),NULL);

gtk_menu_append(GTK_MENU(MENU_GA),PB_GPZOPLUS);
gtk_menu_append(GTK_MENU(MENU_GA),PB_GPZOMINUS);

/*============================================================================
*  das Netz-ueber-Spannungen-Menu
*===========================================================================*/
if(LANG == 1) strcpy(cstring,"Netz ueber Spannungen");
if(LANG == 2) strcpy(cstring,"Mesh over Stresses");
MENU_NOST= gtk_menu_item_new_with_label(cstring);
gtk_menu_bar_append(GTK_MENU_SHELL(MENU_BAR),MENU_NOST);

MENU_NOSTYN=  gtk_menu_new();
gtk_menu_item_set_submenu(GTK_MENU_ITEM(MENU_NOST),MENU_NOSTYN);

if(LANG == 1) strcpy(cstring,"Netz ueber Spannungen nein");
if(LANG == 2) strcpy(cstring,"Mesh over Stresses no");
PB_NONOST= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_NONOST),"activate",G_CALLBACK(CB_NONOST),NULL);

if(LANG == 1) strcpy(cstring,"Netz ueber Spannungen ja");
if(LANG == 2) strcpy(cstring,"Mesh over Stresses yes");
PB_YESNOST= gtk_menu_item_new_with_label(cstring);
g_signal_connect(G_OBJECT(PB_YESNOST),"activate",G_CALLBACK(CB_YESNOST),NULL);

gtk_menu_append(GTK_MENU(MENU_NOSTYN),PB_YESNOST);
gtk_menu_append(GTK_MENU(MENU_NOSTYN),PB_NONOST);

/*----------------------------------------------------------------------------
*  Hauptfenster zeigen
*---------------------------------------------------------------------------*/
gtk_box_pack_start(GTK_BOX(G_VBOX),MENU_BAR,FALSE,FALSE,ispace);
gtk_box_pack_start(GTK_BOX(G_VBOX),HBOX,TRUE,TRUE,ispace);
gtk_container_add(GTK_CONTAINER(H_WIN),G_VBOX);

gtk_widget_show_all(H_WIN);

/*----------------------------------------------------------------------------
*  Dispatcher-Loop
*---------------------------------------------------------------------------*/
gtk_main ();

return 0;
}



