/****************************************************************************************
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
****************************************************************************************/ 
/****************************************************************************************
* Z88COM fuer X11 und gtk+
* 1.7.2011 Rieg
****************************************************************************************/

/****************************************************************************************
* Includes
****************************************************************************************/
/*---------------------------------------------------------------------------------------
* UNIX
*--------------------------------------------------------------------------------------*/
#ifdef FR_UNIX
#include <z88com.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

/****************************************************************************************
* globale Variable, speziell fuer X11
****************************************************************************************/
GtkWidget *HWND; 
GtkWidget *LB_UEBER,*LB_EIN,*LB_PPP,*LB_AUS,*LB_DXF,*LB_INS,*LB_SOL;
GtkWidget *PB_WER,*PB_EXIT,*PB_HELP;
GtkWidget *PB_Z88N,*PB_Z88G,*PB_Z88H,*PB_Z88O;
GtkWidget *BOX_FRAME,*BOX_UEBER,*BOX_OBEN,*BOX_EIN1,*BOX_EIN2,*BOX_PPP,*BOX_AUS;
GtkWidget *BOX_DXF1,*BOX_DXF2,*BOX_INS,*BOX_SOL;
GtkWidget *PB_DYN,*PB_FCD,*PB_NI,*PB_I1,*PB_I2,*PB_I5;
GtkWidget *PB_MAN,*PB_MAT,*PB_MATM,*PB_ELP,*PB_INT;
GtkWidget *PB_O0,*PB_O1,*PB_O2,*PB_O3,*PB_O4;
GtkWidget *PB_I1D,*PB_ISD,*PB_NID,*PB_DI1,*PB_DIS,*PB_DNI;
GtkWidget *RB_IN0,*RB_IN9,*PB_FC,*PB_I2C,*PB_I2S;
GtkWidget *HSEP1,*HSEP2,*HSEP3,*HSEP4,*HSEP5,*HSEP6,*HSEP7;

GtkWidget *MB_WER;

GtkTooltips *TT_HELP,*TT_Z88N,*TT_Z88G,*TT_Z88H,*TT_Z88O;
GtkTooltips *TT_DYN,*TT_FCD,*TT_NI,*TT_I1,*TT_I2,*TT_I5;
GtkTooltips *TT_MAN,*TT_MAT,*TT_MATM,*TT_ELP,*TT_INT;
GtkTooltips *TT_O0,*TT_O1,*TT_O2,*TT_O3,*TT_O4;
GtkTooltips *TT_I1D,*TT_ISD,*TT_NID,*TT_DI1,*TT_DIS,*TT_DNI;
GtkTooltips *TT_IN0,*TT_IN9,*TT_FC,*TT_I2C,*TT_I2S;

gint       ispace= 3;

FILE       *fdyn,*fwlo;

FR_INT4    LANG= 2;

char       CEDITOR[128],CBROWSER[128],CPREFIX[128];

char       cdyn[12] = "z88.dyn";  
char       clgd[12] = "z88com.log";

int        ifhelp= 0,iret,ifnili= 0;
int        *pp;

/****************************************************************************************
*  Function-Declarationen
****************************************************************************************/
void CB_WER    (GtkWidget *,gpointer);
void CB_EXIT   (GtkWidget *,gpointer);
void CB_HELP   (GtkWidget *,gpointer);
void CB_Z88N   (GtkWidget *,gpointer);
void CB_Z88G   (GtkWidget *,gpointer);
void CB_Z88H   (GtkWidget *,gpointer);
void CB_Z88O   (GtkWidget *,gpointer);
void CB_Z88X   (GtkWidget *,gpointer);
void CB_Z88F   (GtkWidget *,gpointer);
void CB_DYN    (GtkWidget *,gpointer);
void CB_FCD    (GtkWidget *,gpointer);
void CB_NI     (GtkWidget *,gpointer);
void CB_I1     (GtkWidget *,gpointer);
void CB_I2     (GtkWidget *,gpointer);
void CB_I3     (GtkWidget *,gpointer);
void CB_MAN    (GtkWidget *,gpointer);
void CB_MAT    (GtkWidget *,gpointer);
void CB_MATM   (GtkWidget *,gpointer);
void CB_ELP    (GtkWidget *,gpointer);
void CB_INT    (GtkWidget *,gpointer);
void CB_I5     (GtkWidget *,gpointer);
void CB_O0     (GtkWidget *,gpointer);
void CB_O1     (GtkWidget *,gpointer);
void CB_O2     (GtkWidget *,gpointer);
void CB_O3     (GtkWidget *,gpointer);
void CB_O4     (GtkWidget *,gpointer);
void CB_I1D    (GtkWidget *,gpointer);
void CB_ISD    (GtkWidget *,gpointer);
void CB_NID    (GtkWidget *,gpointer);
void CB_DI1    (GtkWidget *,gpointer);
void CB_DIS    (GtkWidget *,gpointer);
void CB_DNI    (GtkWidget *,gpointer);
void CB_IN0    (GtkWidget *,gpointer);
void CB_IN9    (GtkWidget *,gpointer);
void CB_FC     (GtkWidget *,gpointer);
void CB_I2C    (GtkWidget *,gpointer);
void CB_I2S    (GtkWidget *,gpointer);

int  lan88c(void);
int  rcol88c(void);

/****************************************************************************************
*  Hauptprogramm
****************************************************************************************/
int main(int argc, char *argv[])
  {
  char cstring[128];

/*---------------------------------------------------------------------------------------
*  LAN88C starten
*--------------------------------------------------------------------------------------*/
iret= lan88c();

if(iret == AL_NOLOG)
  {
  fprintf(stderr,"Cannot open file Z88COM.LOG ! STOP !\n"); 
  fclose(fwlo);
  exit(1); 
  }
if(iret == AL_NODYN)
  {
  fprintf(stderr,"Cannot open file Z88.DYN ! STOP !\n"); 
  fclose(fwlo);
  exit(1); 
  }
if(iret == AL_WRONGDYN)
  {
  fprintf(stderr,"File Z88.DYN is invalid or wrong! STOP !\n"); 
  fclose(fwlo);
  exit(1); 
  }

/*---------------------------------------------------------------------------------------
*  Z88.FCD einlesen
*--------------------------------------------------------------------------------------*/
iret= rcol88c();

if(iret != 0)
  {
  if(LANG == 1) fprintf(stderr,"Datei Z88.FCD is ungueltig oder falsch! STOP !\n"); 
  if(LANG == 2) fprintf(stderr,"File Z88.FCD is invalid or wrong! STOP !\n");

  fclose(fwlo);
  exit(1);
  }

/*---------------------------------------------------------------------------------------
*  Hauptfenster
*--------------------------------------------------------------------------------------*/
  gtk_init(&argc,&argv);

  HWND=   gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title   (GTK_WINDOW(HWND),"Z88COM V14OS");
  gtk_window_set_position(GTK_WINDOW(HWND),GTK_WIN_POS_CENTER);
  g_signal_connect       (GTK_OBJECT(HWND),"destroy",GTK_SIGNAL_FUNC(CB_EXIT),NULL);

/*---------------------------------------------------------------------------------------
*  Ueberschrift
*--------------------------------------------------------------------------------------*/
  if(LANG == 1) strcpy(cstring,"Der Z88-Commander Version 14OS");
  if(LANG == 2) strcpy(cstring,"The Z88 Commander Version 14OS");
  LB_UEBER= gtk_label_new(cstring); 

  HSEP1= gtk_hseparator_new();

/*---------------------------------------------------------------------------------------
*  Buttons erzeugen + Callbacks obere Reihe
*--------------------------------------------------------------------------------------*/
  if(LANG == 1) strcpy(cstring,"Info");
  if(LANG == 2) strcpy(cstring,"About");
  PB_WER= gtk_button_new_with_label(cstring);
  g_signal_connect(GTK_OBJECT(PB_WER),"clicked",GTK_SIGNAL_FUNC(CB_WER),"Info");

  if(LANG == 1) strcpy(cstring,"Ende");
  if(LANG == 2) strcpy(cstring,"Exit");
  PB_EXIT= gtk_button_new_with_label(cstring);
  g_signal_connect(GTK_OBJECT(PB_EXIT),"clicked",GTK_SIGNAL_FUNC(CB_EXIT),"Exit");
 
  if(LANG == 1) strcpy(cstring,"Hilfe");
  if(LANG == 2) strcpy(cstring,"Help");
  PB_HELP= gtk_button_new_with_label(cstring);
  g_signal_connect(GTK_OBJECT(PB_HELP),"clicked",GTK_SIGNAL_FUNC(CB_HELP),"Hilfe");
  TT_HELP= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Oeffnen des Handbuchs");
  if(LANG == 2) strcpy(cstring,"Open the Z88 Manual");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_HELP),PB_HELP,cstring,NULL);

  PB_DYN= gtk_button_new_with_label("Z88.DYN");
  g_signal_connect(GTK_OBJECT(PB_DYN),"clicked",GTK_SIGNAL_FUNC(CB_DYN),"Z88.DYN");
  TT_DYN= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Speicher-Steuerdatei Z88.DYN editieren");
  if(LANG == 2) strcpy(cstring,"Edit the Memory Definition File Z88.DYN");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_DYN),PB_DYN,cstring,NULL);

  PB_FCD= gtk_button_new_with_label("Z88.FCD");
  g_signal_connect(GTK_OBJECT(PB_FCD),"clicked",GTK_SIGNAL_FUNC(CB_FCD),"Z88.FCD");
  TT_FCD= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Datei der Einstellungen Z88 fuer UNIX Z88.FCD editieren");
  if(LANG == 2) strcpy(cstring,"Edit the Defaults for UNIX File Z88.FCD");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_FCD),PB_FCD,cstring,NULL);

  HSEP2= gtk_hseparator_new();

/*---------------------------------------------------------------------------------------
*  Buttons erzeugen + Callbacks: Eingabedateien
*--------------------------------------------------------------------------------------*/
  if(LANG == 1) strcpy(cstring,"Editieren der Eingabedateien");
  if(LANG == 2) strcpy(cstring,"Edit the Input Files");
  LB_EIN= gtk_label_new(cstring); 

  PB_NI= gtk_button_new_with_label("Z88NI.TXT");
  g_signal_connect(GTK_OBJECT(PB_NI),"clicked",GTK_SIGNAL_FUNC(CB_NI),"Z88NI.TXT");
  TT_NI= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Netzgenerator-Eingabedatei Z88NI.TXT editieren");
  if(LANG == 2) strcpy(cstring,"Edit the Mesh Genrator Input File Z88NI.TXT");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_NI),PB_NI,cstring,NULL);

  PB_I1= gtk_button_new_with_label("Z88I1.TXT");
  g_signal_connect(GTK_OBJECT(PB_I1),"clicked",GTK_SIGNAL_FUNC(CB_I1),"Z88I1.TXT");
  TT_I1= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"allgemeine Strukturdaten Z88I1.TXT editieren");
  if(LANG == 2) strcpy(cstring,"Edit the Structure File Z88I1.TXT");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_I1),PB_I1,cstring,NULL);

  PB_I2= gtk_button_new_with_label("Z88I2.TXT");
  g_signal_connect(GTK_OBJECT(PB_I2),"clicked",GTK_SIGNAL_FUNC(CB_I2),"Z88I2.TXT");
  TT_I2= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Randbedingungen Z88I2.TXT editieren");
  if(LANG == 2) strcpy(cstring,"Edit the Boundary Condition File Z88I2.TXT");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_I2),PB_I2,cstring,NULL);

  PB_I5= gtk_button_new_with_label("Z88I5.TXT");
  g_signal_connect(GTK_OBJECT(PB_I5),"clicked",GTK_SIGNAL_FUNC(CB_I5),"Z88I5.TXT");
  TT_I5= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Datei der Oberflaechenlasten Z88I5.TXT editieren");
  if(LANG == 2) strcpy(cstring,"Edit the File for Surface Loads Z88I5.TXT");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_I5),PB_I5,cstring,NULL);

  PB_MAN= gtk_button_new_with_label("Z88MAN.TXT");
  g_signal_connect(GTK_OBJECT(PB_MAN),"clicked",GTK_SIGNAL_FUNC(CB_MAN),"Z88MAN.TXT");
  TT_MAN= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Solver-Steuerdatei Z88MAN.TXT editieren");
  if(LANG == 2) strcpy(cstring,"Edit the Parameters File for Solvers Z88MAN.TXT");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_MAN),PB_MAN,cstring,NULL);

  PB_MAT= gtk_button_new_with_label("Z88MAT.TXT");
  g_signal_connect(GTK_OBJECT(PB_MAT),"clicked",GTK_SIGNAL_FUNC(CB_MAT),"Z88MAT.TXT");
  TT_MAT= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Materialdatei Z88MAT.TXT editieren");
  if(LANG == 2) strcpy(cstring,"Edit the Materials File Z88MAT.TXT");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_MAT),PB_MAT,cstring,NULL);

  PB_MATM= gtk_button_new_with_label("?.TXT");
  g_signal_connect(GTK_OBJECT(PB_MATM),"clicked",GTK_SIGNAL_FUNC(CB_MATM),"?.TXT");
  TT_MATM= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Einzel-Materialdateien ?.TXT editieren");
  if(LANG == 2) strcpy(cstring,"Edit the special Material Files ?.TXT");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_MATM),PB_MATM,cstring,NULL);

  PB_ELP= gtk_button_new_with_label("Z88ELP.TXT");
  g_signal_connect(GTK_OBJECT(PB_ELP),"clicked",GTK_SIGNAL_FUNC(CB_ELP),"Z88ELP.TXT");
  TT_ELP= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Elementparameterdatei Z88ELP.TXT editieren");
  if(LANG == 2) strcpy(cstring,"Edit the Element Parameters File Z88ELP.TXT");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_ELP),PB_ELP,cstring,NULL);

  PB_INT= gtk_button_new_with_label("Z88INT.TXT");
  g_signal_connect(GTK_OBJECT(PB_INT),"clicked",GTK_SIGNAL_FUNC(CB_INT),"Z88INT.TXT");
  TT_INT= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Integrationsordnungsdatei Z88INT.TXT editieren");
  if(LANG == 2) strcpy(cstring,"Edit the Integration Orders File Z88INT.TXT");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_INT),PB_INT,cstring,NULL);

  HSEP3= gtk_hseparator_new();

/*---------------------------------------------------------------------------------------
*  Buttons erzeugen + Callbacks: Prae- und Postprozessoren
*--------------------------------------------------------------------------------------*/
  if(LANG == 1) strcpy(cstring,"Prae- und Postprozessoren");
  if(LANG == 2) strcpy(cstring,"Pre- and Postprocessors");
  LB_PPP= gtk_label_new(cstring); 

  PB_Z88N= gtk_button_new_with_label("Z88N");
  g_signal_connect(GTK_OBJECT(PB_Z88N),"clicked",GTK_SIGNAL_FUNC(CB_Z88N),"Z88N");
  TT_Z88N= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Der Netzgenerator");
  if(LANG == 2) strcpy(cstring,"The Mesh Generator");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_Z88N),PB_Z88N,cstring,NULL);

  PB_Z88O= gtk_button_new_with_label("Z88O");
  g_signal_connect(GTK_OBJECT(PB_Z88O),"clicked",GTK_SIGNAL_FUNC(CB_Z88O),"Z88O");
  TT_Z88O= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Das Plotprogramm");
  if(LANG == 2) strcpy(cstring,"The Plot Program");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_Z88O),PB_Z88O,cstring,NULL);

  HSEP4= gtk_hseparator_new();

/*---------------------------------------------------------------------------------------
*  Buttons erzeugen + Callbacks vierte Reihe: Konverter
*--------------------------------------------------------------------------------------*/
  if(LANG == 1) strcpy(cstring,"CAD-Konverter");
  if(LANG == 2) strcpy(cstring,"CAD Converters");
  LB_DXF= gtk_label_new(cstring); 

  PB_Z88G= gtk_button_new_with_label("Z88G");
  g_signal_connect(GTK_OBJECT(PB_Z88G),"clicked",GTK_SIGNAL_FUNC(CB_Z88G),"Z88G");
  TT_Z88G= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Der NASTRAN/COSMOS-Konverter");
  if(LANG == 2) strcpy(cstring,"The NASTRAN/COSMOS Converter");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_Z88G),PB_Z88G,cstring,NULL);

  PB_Z88H= gtk_button_new_with_label("Z88H");
  g_signal_connect(GTK_OBJECT(PB_Z88H),"clicked",GTK_SIGNAL_FUNC(CB_Z88H),"Z88H");
  TT_Z88H= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Der Cuthill-MCKee-Umnummerierer");
  if(LANG == 2) strcpy(cstring,"The Cuthill-McKee Program");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_Z88H),PB_Z88H,cstring,NULL);

  PB_I1D= gtk_button_new_with_label("Z88I1>DXF");
  g_signal_connect(GTK_OBJECT(PB_I1D),"clicked",GTK_SIGNAL_FUNC(CB_I1D),"Z88I1>DXF");
  TT_I1D= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"von Z88I1.TXT nach Z88X.DXF");
  if(LANG == 2) strcpy(cstring,"from Z88I1.TXT to Z88X.DXF");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_I1D),PB_I1D,cstring,NULL);

  PB_ISD= gtk_button_new_with_label("Z88I*>DXF");
  g_signal_connect(GTK_OBJECT(PB_ISD),"clicked",GTK_SIGNAL_FUNC(CB_ISD),"Z88I*>DXF");
  TT_ISD= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"von Z88I*.TXT nach Z88X.DXF");
  if(LANG == 2) strcpy(cstring,"from Z88I*.TXT to Z88X.DXF");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_ISD),PB_ISD,cstring,NULL);

  PB_NID= gtk_button_new_with_label("Z88NI>DXF");
  g_signal_connect(GTK_OBJECT(PB_NID),"clicked",GTK_SIGNAL_FUNC(CB_NID),"Z88NI>DXF");
  TT_NID= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"von Z88NI.TXT nach Z88X.DXF");
  if(LANG == 2) strcpy(cstring,"from Z88NI.TXT to Z88X.DXF");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_NID),PB_NID,cstring,NULL);

  PB_DI1= gtk_button_new_with_label("DXF>Z88I1");
  g_signal_connect(GTK_OBJECT(PB_DI1),"clicked",GTK_SIGNAL_FUNC(CB_DI1),"DXF>Z88I1");
  TT_DI1= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"von Z88X.DXF nach Z88I1.TXT");
  if(LANG == 2) strcpy(cstring,"from Z88X.DXF to Z88I1.TXT");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_DI1),PB_DI1,cstring,NULL);

  PB_DIS= gtk_button_new_with_label("DXF>Z88I*");
  g_signal_connect(GTK_OBJECT(PB_DIS),"clicked",GTK_SIGNAL_FUNC(CB_DIS),"DXF>Z88I*");
  TT_DIS= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"von Z88X.DXF nach Z88I*.TXT");
  if(LANG == 2) strcpy(cstring,"from Z88X.DXF to Z88I*.TXT");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_DIS),PB_DIS,cstring,NULL);

  PB_DNI= gtk_button_new_with_label("DXF>Z88NI");
  g_signal_connect(GTK_OBJECT(PB_DNI),"clicked",GTK_SIGNAL_FUNC(CB_DNI),"DXF>Z88NI");
  TT_DNI= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"von Z88X.DXF nach Z88NI.TXT");
  if(LANG == 2) strcpy(cstring,"from Z88X.DXF to Z88NI.TXT");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_DNI),PB_DNI,cstring,NULL);

  HSEP5= gtk_hseparator_new();

/*---------------------------------------------------------------------------------------
*  Buttons erzeugen + Callbacks: Einstellung der Solver
*--------------------------------------------------------------------------------------*/
  if(LANG == 1) strcpy(cstring,"Einstellungen der Solver");
  if(LANG == 2) strcpy(cstring,"Modes of the Solvers");
  LB_INS= gtk_label_new(cstring); 

  if(LANG == 1) strcpy(cstring,"Berechnung");
  if(LANG == 2) strcpy(cstring,"Computation");
  RB_IN0= gtk_radio_button_new_with_label(NULL,cstring);
  g_signal_connect(GTK_OBJECT(RB_IN0),"clicked",GTK_SIGNAL_FUNC(CB_IN0),"IFNILI0");
  TT_IN0= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Fuer alle Solver: Berechnung");
  if(LANG == 2) strcpy(cstring,"For all the solvers: computation");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_IN0),RB_IN0,cstring,NULL);

  if(LANG == 1) strcpy(cstring,"Testmode");
  if(LANG == 2) strcpy(cstring,"Test Mode");
  RB_IN9= gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(RB_IN0),cstring);
  g_signal_connect(GTK_OBJECT(RB_IN9),"clicked",GTK_SIGNAL_FUNC(CB_IN9),"IFNILI9");
  TT_IN9= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Fuer alle Solver: Testmode, um den Speicherbedarf festzustellen");
  if(LANG == 2) strcpy(cstring,"For all the solvers: Test Mode for detecting the necessary memory");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_IN9),RB_IN9,cstring,NULL);

  HSEP6= gtk_hseparator_new();

/*---------------------------------------------------------------------------------------
*  Buttons erzeugen + Callbacks: Solver
*--------------------------------------------------------------------------------------*/
  if(LANG == 1) strcpy(cstring,"Die Solver");
  if(LANG == 2) strcpy(cstring,"The Solvers");
  LB_SOL= gtk_label_new(cstring); 

  PB_FC= gtk_button_new_with_label("CHOLESKY");
  g_signal_connect(GTK_OBJECT(PB_FC),"clicked",GTK_SIGNAL_FUNC(CB_FC),"CHOLESKY");
  TT_FC= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Der Cholesky-Solver fuer kleine Strukturen");
  if(LANG == 2) strcpy(cstring,"The Cholesky Solver for small structures");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_FC),PB_FC,cstring,NULL);

  PB_I2C= gtk_button_new_with_label("SICCG");
  g_signal_connect(GTK_OBJECT(PB_I2C),"clicked",GTK_SIGNAL_FUNC(CB_I2C),"Z88I2C");
  TT_I2C= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,
  "Der Sparsematrix-Iterationssolver mit SIC Vorkonditionierung fuer grosse Strukturen");
  if(LANG == 2) strcpy(cstring,
  "The Sparse Matrix Iteration Solver SIC preconditioner for large structures");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_I2C),PB_I2C,cstring,NULL);

  PB_I2S= gtk_button_new_with_label("SORCG");
  g_signal_connect(GTK_OBJECT(PB_I2S),"clicked",GTK_SIGNAL_FUNC(CB_I2S),"Z88I2S");
  TT_I2S= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,
  "Der Sparsematrix-Iterationssolver mit SOR Vorkonditionierung fuer grosse Strukture");
  if(LANG == 2) strcpy(cstring,
  "The Sparse Matrix Iteration Solver SOR preconditioner for large structures");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_I2S),PB_I2S,cstring,NULL);

  HSEP7= gtk_hseparator_new();

/*---------------------------------------------------------------------------------------
*  Buttons erzeugen + Callbacks: Ausgabedateien
*--------------------------------------------------------------------------------------*/
  if(LANG == 1) strcpy(cstring,"Editieren der Ausgabedateien");
  if(LANG == 2) strcpy(cstring,"Edit the Output Files");
  LB_AUS= gtk_label_new(cstring); 

  PB_O0= gtk_button_new_with_label("Z88O0.TXT");
  g_signal_connect(GTK_OBJECT(PB_O0),"clicked",GTK_SIGNAL_FUNC(CB_O0),"Z88O0.TXT");
  TT_O0= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Aufbereitete Strukturdaten Z88O0.TXT editieren");
  if(LANG == 2) strcpy(cstring,"Edit Processed Input Data Z88O0.TXT for documentation");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_O0),PB_O0,cstring,NULL);

  PB_O1= gtk_button_new_with_label("Z88O1.TXT");
  g_signal_connect(GTK_OBJECT(PB_O1),"clicked",GTK_SIGNAL_FUNC(CB_O1),"Z88O1.TXT");
  TT_O1= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Aufbereitete Randbedingungen Z88O1.TXT editieren");
  if(LANG == 2) strcpy(cstring,"Edit Processed Boundary Conditions Z88O1.TXT for documentation");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_O1),PB_O1,cstring,NULL);

  PB_O2= gtk_button_new_with_label("Z88O2.TXT");
  g_signal_connect(GTK_OBJECT(PB_O2),"clicked",GTK_SIGNAL_FUNC(CB_O2),"Z88O2.TXT");
  TT_O2= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Berechnete Verschiebungen Z88O2.TXT editieren");
  if(LANG == 2) strcpy(cstring,"Edit Computed Displacements Z88O2.TXT");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_O2),PB_O2,cstring,NULL);

  PB_O3= gtk_button_new_with_label("Z88O3.TXT");
  g_signal_connect(GTK_OBJECT(PB_O3),"clicked",GTK_SIGNAL_FUNC(CB_O3),"Z88O3.TXT");
  TT_O3= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Berechnete Spannungen Z88O3.TXT editieren");
  if(LANG == 2) strcpy(cstring,"Edit Computed Stresses Z88O3.TXT");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_O3),PB_O3,cstring,NULL);

  PB_O4= gtk_button_new_with_label("Z88O4.TXT");
  g_signal_connect(GTK_OBJECT(PB_O4),"clicked",GTK_SIGNAL_FUNC(CB_O4),"Z88O4.TXT");
  TT_O4= gtk_tooltips_new();
  if(LANG == 1) strcpy(cstring,"Berechnete Knotenkraefte Z88O4.TXT editieren");
  if(LANG == 2) strcpy(cstring,"Edit Computed Nodal Forces Z88O4.TXT");
  gtk_tooltips_set_tip(GTK_TOOLTIPS(TT_O4),PB_O4,cstring,NULL);

/*---------------------------------------------------------------------------------------
*  Buttons anordnen
*--------------------------------------------------------------------------------------*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  Boxen erzeugen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  BOX_FRAME = gtk_vbox_new(FALSE,ispace);
  BOX_UEBER = gtk_hbox_new(TRUE, ispace);
  BOX_OBEN  = gtk_hbox_new(TRUE, ispace);
  BOX_EIN1  = gtk_hbox_new(TRUE, ispace);
  BOX_EIN2  = gtk_hbox_new(TRUE, ispace);
  BOX_PPP   = gtk_hbox_new(TRUE, ispace);
  BOX_DXF1  = gtk_hbox_new(TRUE, ispace);
  BOX_DXF2  = gtk_hbox_new(TRUE, ispace);
  BOX_INS   = gtk_hbox_new(TRUE, ispace);
  BOX_SOL   = gtk_hbox_new(TRUE, ispace);
  BOX_AUS   = gtk_hbox_new(TRUE, ispace);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  Ueberschrift
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  gtk_box_pack_start(GTK_BOX(BOX_UEBER),LB_UEBER,    TRUE, TRUE, ispace);
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),BOX_UEBER,   TRUE, FALSE,ispace);
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),HSEP1,       TRUE, FALSE,ispace);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  obere Buttonreihe
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  gtk_box_pack_start(GTK_BOX(BOX_OBEN), PB_WER,     TRUE, TRUE, ispace);
  gtk_box_pack_start(GTK_BOX(BOX_OBEN), PB_EXIT,    TRUE, TRUE, ispace);
  gtk_box_pack_start(GTK_BOX(BOX_OBEN), PB_HELP,    TRUE, TRUE, ispace);
  gtk_box_pack_start(GTK_BOX(BOX_OBEN), PB_DYN,     TRUE, TRUE, ispace);
  gtk_box_pack_start(GTK_BOX(BOX_OBEN), PB_FCD,     TRUE, TRUE, ispace);
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),BOX_OBEN,   TRUE, FALSE,ispace);
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),HSEP2,      TRUE, FALSE,ispace);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  Buttonreihen fuer Eingabe
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),LB_EIN,     TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_EIN1),  PB_NI,     TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_EIN1),  PB_I1 ,    TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_EIN1),  PB_I2 ,    TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_EIN1),  PB_I5 ,    TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),BOX_EIN1,   TRUE, FALSE, ispace);
  gtk_box_pack_start(GTK_BOX(BOX_EIN2),  PB_MAN,    TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_EIN2),  PB_MAT,    TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_EIN2),  PB_MATM,   TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_EIN2),  PB_ELP,    TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_EIN2),  PB_INT,    TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),BOX_EIN2,   TRUE, FALSE, ispace);
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),HSEP3 ,     TRUE, FALSE, ispace);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  Buttonreihe fuer Eingabe
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),LB_PPP,     TRUE, TRUE, ispace);
  gtk_box_pack_start(GTK_BOX(BOX_PPP),  PB_Z88N,    TRUE, TRUE, ispace);
  gtk_box_pack_start(GTK_BOX(BOX_PPP),  PB_Z88O,    TRUE, TRUE, ispace);
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),BOX_PPP,    TRUE, FALSE,ispace);
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),HSEP4 ,     TRUE, FALSE,ispace);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  Buttonreihe fuer DXF <-> Z88
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),LB_DXF,     TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_DXF1),  PB_Z88G,   TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_DXF1),  PB_Z88H,   TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),BOX_DXF1,   TRUE, FALSE, ispace);
  gtk_box_pack_start(GTK_BOX(BOX_DXF2),  PB_I1D,    TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_DXF2),  PB_ISD,    TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_DXF2),  PB_NID,    TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_DXF2),  PB_DI1,    TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_DXF2),  PB_DIS,    TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_DXF2),  PB_DNI,    TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),BOX_DXF2,   TRUE, FALSE, ispace);
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),HSEP5 ,     TRUE, FALSE, ispace);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  Buttonreihe fuer Einstellung Solver
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),LB_INS,    TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_INS),  RB_IN0,    TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_INS),  RB_IN9,    TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),BOX_INS,   TRUE, FALSE, ispace);
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),HSEP6 ,    TRUE, FALSE, ispace);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  Buttonreihe fuer Solver
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),LB_SOL,    TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_SOL),  PB_FC,     TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_SOL),  PB_I2C,    TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_SOL),  PB_I2S,    TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),BOX_SOL,   TRUE, FALSE, ispace);
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),HSEP7 ,    TRUE, FALSE, ispace);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  Buttonreihe fuer Ausgabe
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),LB_AUS,     TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_AUS),  PB_O0,      TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_AUS),  PB_O1,      TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_AUS),  PB_O2,      TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_AUS),  PB_O3,      TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_AUS),  PB_O4,      TRUE, TRUE,  ispace);
  gtk_box_pack_start(GTK_BOX(BOX_FRAME),BOX_AUS,    TRUE, FALSE, ispace);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*  BOX_FRAME in HWND
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  gtk_container_add(GTK_CONTAINER(HWND),BOX_FRAME);
  gtk_widget_show_all(HWND);

  gtk_main();

  return 0;
  }

