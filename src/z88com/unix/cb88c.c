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
****************************************************************************************/ 
/****************************************************************************************
* CB88C fuer X11 und gtk+
* 7.3.2017 Rieg
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
* Functions
****************************************************************************************/
int ale88c(int);
int rcol88c(void);

/****************************************************************************************
* Callbacks
****************************************************************************************/
/*---------------------------------------------------------------------------------------
* CB_WER
*--------------------------------------------------------------------------------------*/
void CB_WER(GtkWidget *button,gpointer data)
{
extern GtkWidget *HWND; 
extern GtkWidget *MB_WER;

extern FR_INT4 LANG;
extern int     *pp;

char cmess[512],cbytes[128];

if(LANG == 1) strcpy(cmess,
"Der Z88-Commander Version 15OS\nProf.Dr.-Ing. Frank Rieg\nUniversitaet Bayreuth 2017\n\
frank.rieg@uni-bayreuth.de\nwww.z88.de\n");
if(LANG == 2) strcpy(cmess,
"The Z88-Commander Version 15OS\nProf. Frank Rieg\nUniversity of Bayreuth,Germany,2017\n\
frank.rieg@uni-bayreuth.de\nwww.z88.de\n");

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

MB_WER= gtk_message_dialog_new(GTK_WINDOW(HWND),GTK_DIALOG_DESTROY_WITH_PARENT,
        GTK_MESSAGE_INFO, GTK_BUTTONS_OK,cmess);
gtk_dialog_run(GTK_DIALOG(MB_WER));
gtk_widget_destroy(MB_WER);
}

/*---------------------------------------------------------------------------------------
* CB_EXIT
*--------------------------------------------------------------------------------------*/
void CB_EXIT(GtkWidget *button,gpointer data)
{
gtk_main_quit();
}

/*---------------------------------------------------------------------------------------
* CB_HELP
*--------------------------------------------------------------------------------------*/
void CB_HELP(GtkWidget *button,gpointer data)
{
extern GtkWidget *PB_HELP;
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
if(iret != 0) ale88c(AL_NOHELP);
}

/*---------------------------------------------------------------------------------------
* CB_Z88N
*--------------------------------------------------------------------------------------*/
void CB_Z88N(GtkWidget *button,gpointer data)
{
extern int     iret;

iret= system("z88n");
if(iret != 0) ale88c(AL_NOZ88N);
}

/*---------------------------------------------------------------------------------------
* CB_Z88G
*--------------------------------------------------------------------------------------*/
void CB_Z88G(GtkWidget *button,gpointer data)
{
extern int     iret;

iret= system("z88g");
if(iret != 0) ale88c(AL_NOZ88G);
}

/*---------------------------------------------------------------------------------------
* CB_Z88H
*--------------------------------------------------------------------------------------*/
void CB_Z88H(GtkWidget *button,gpointer data)
{
extern int     iret;

iret= system("z88h");
if(iret != 0) ale88c(AL_NOZ88H);
}

/*---------------------------------------------------------------------------------------
* CB_Z88O
*--------------------------------------------------------------------------------------*/
void CB_Z88O(GtkWidget *button,gpointer data)
{
extern int     iret;

iret= system("z88o");
if(iret != 0) ale88c(AL_NOZ88O);
}

/*---------------------------------------------------------------------------------------
* CB_DYN
*--------------------------------------------------------------------------------------*/
void CB_DYN(GtkWidget *button,gpointer data)
{
extern int     iret;
extern char    CEDITOR[];

char command[320];

strcpy(command,CEDITOR);
strcat(command," z88.dyn");
iret= system(command);
if(iret != 0) ale88c(AL_NOEDDYN);
}

/*---------------------------------------------------------------------------------------
* CB_FCD
*--------------------------------------------------------------------------------------*/
void CB_FCD(GtkWidget *button,gpointer data)
{
extern FR_INT4 LANG;
extern int     iret;
extern char    CEDITOR[];

char command[320];

strcpy(command,CEDITOR);
strcat(command," z88.fcd");
iret= system(command);
if(iret == 0)
  {
  iret= rcol88c();
  if(iret != 0)
    {
    if(LANG == 1) fprintf(stderr,"Datei Z88.FCD is ungueltig oder falsch! STOP !\n"); 
    if(LANG == 2) fprintf(stderr,"File Z88.FCD is invalid or wrong! STOP !\n");
    exit(1);
    }
  }
else ale88c(AL_NOEDFCD);
}

/*---------------------------------------------------------------------------------------
* CB_NI
*--------------------------------------------------------------------------------------*/
void CB_NI(GtkWidget *button,gpointer data)
{
extern int     iret;
extern char    CEDITOR[];

char command[320];

strcpy(command,CEDITOR);
strcat(command," z88ni.txt");
iret= system(command);
if(iret != 0) ale88c(AL_NOEDNI);
}

/*---------------------------------------------------------------------------------------
* CB_I1
*--------------------------------------------------------------------------------------*/
void CB_I1(GtkWidget *button,gpointer data)
{
extern int     iret;
extern char    CEDITOR[];

char command[320];

strcpy(command,CEDITOR);
strcat(command," z88i1.txt");
iret= system(command);
if(iret != 0) ale88c(AL_NOEDI1);
}

/*---------------------------------------------------------------------------------------
* CB_I2
*--------------------------------------------------------------------------------------*/
void CB_I2(GtkWidget *button,gpointer data)
{
extern int     iret;
extern char    CEDITOR[];

char command[320];

strcpy(command,CEDITOR);
strcat(command," z88i2.txt");
iret= system(command);
if(iret != 0) ale88c(AL_NOEDI2);
}

/*---------------------------------------------------------------------------------------
* CB_MAN
*--------------------------------------------------------------------------------------*/
void CB_MAN(GtkWidget *button,gpointer data)
{
extern int     iret;
extern char    CEDITOR[];

char command[320];

strcpy(command,CEDITOR);
strcat(command," z88man.txt");
iret= system(command);
if(iret != 0) ale88c(AL_NOEDMAN);
}

/*---------------------------------------------------------------------------------------
* CB_MAT
*--------------------------------------------------------------------------------------*/
void CB_MAT(GtkWidget *button,gpointer data)
{
extern int     iret;
extern char    CEDITOR[];

char command[320];

strcpy(command,CEDITOR);
strcat(command," z88mat.txt");
iret= system(command);
if(iret != 0) ale88c(AL_NOEDMAT);
}

/*---------------------------------------------------------------------------------------
* CB_MATM
*--------------------------------------------------------------------------------------*/
void CB_MATM(GtkWidget *button,gpointer data)
{
extern int       iret;
extern char      CEDITOR[];

GtkWidget        *FC_DIA;
gchar            *cfilename;
GtkFileFilter    *ffilter;

char             command[320];

ffilter = gtk_file_filter_new ();
gtk_file_filter_add_pattern(ffilter, "*.txt");

FC_DIA= gtk_file_chooser_dialog_new("Open Special Material File",NULL,
                                    GTK_FILE_CHOOSER_ACTION_OPEN,
                                    GTK_STOCK_OK,GTK_RESPONSE_OK,
                                    GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);

gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(FC_DIA),ffilter);

iret= gtk_dialog_run(GTK_DIALOG(FC_DIA));
if(iret == GTK_RESPONSE_OK)
  {
  cfilename= gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(FC_DIA));
  strcpy(command,CEDITOR);
  strcat(command," ");
  strcat(command,cfilename);
  iret= system(command);
  if(iret != 0) ale88c(AL_NOEDMAT);
  }
gtk_widget_destroy(FC_DIA);
}

/*---------------------------------------------------------------------------------------
* CB_ELP
*--------------------------------------------------------------------------------------*/
void CB_ELP(GtkWidget *button,gpointer data)
{
extern int     iret;
extern char    CEDITOR[];

char command[320];

strcpy(command,CEDITOR);
strcat(command," z88elp.txt");
iret= system(command);
if(iret != 0) ale88c(AL_NOEDELP);
}

/*---------------------------------------------------------------------------------------
* CB_INT
*--------------------------------------------------------------------------------------*/
void CB_INT(GtkWidget *button,gpointer data)
{
extern int     iret;
extern char    CEDITOR[];

char command[320];

strcpy(command,CEDITOR);
strcat(command," z88int.txt");
iret= system(command);
if(iret != 0) ale88c(AL_NOEDINT);
}

/*---------------------------------------------------------------------------------------
* CB_I5
*--------------------------------------------------------------------------------------*/
void CB_I5(GtkWidget *button,gpointer data)
{
extern int     iret;
extern char    CEDITOR[];

char command[320];

strcpy(command,CEDITOR);
strcat(command," z88i5.txt");
iret= system(command);
if(iret != 0) ale88c(AL_NOEDI5);
}

/*---------------------------------------------------------------------------------------
* CB_O0
*--------------------------------------------------------------------------------------*/
void CB_O0(GtkWidget *button,gpointer data)
{
extern int     iret;
extern char    CEDITOR[];

char command[320];

strcpy(command,CEDITOR);
strcat(command," z88o0.txt");
iret= system(command);
if(iret != 0) ale88c(AL_NOEDO0);
}

/*---------------------------------------------------------------------------------------
* CB_O1
*--------------------------------------------------------------------------------------*/
void CB_O1(GtkWidget *button,gpointer data)
{
extern int     iret;
extern char    CEDITOR[];

char command[320];

strcpy(command,CEDITOR);
strcat(command," z88o1.txt");
iret= system(command);
if(iret != 0) ale88c(AL_NOEDO1);
}

/*---------------------------------------------------------------------------------------
* CB_O2
*--------------------------------------------------------------------------------------*/
void CB_O2(GtkWidget *button,gpointer data)
{
extern int     iret;
extern char    CEDITOR[];

char command[320];

strcpy(command,CEDITOR);
strcat(command," z88o2.txt");
iret= system(command);
if(iret != 0) ale88c(AL_NOEDO2);
}

/*---------------------------------------------------------------------------------------
* CB_O3
*--------------------------------------------------------------------------------------*/
void CB_O3(GtkWidget *button,gpointer data)
{
extern int     iret;
extern char    CEDITOR[];

char command[320];

strcpy(command,CEDITOR);
strcat(command," z88o3.txt");
iret= system(command);
if(iret != 0) ale88c(AL_NOEDO3);
}

/*---------------------------------------------------------------------------------------
* CB_O4
*--------------------------------------------------------------------------------------*/
void CB_O4(GtkWidget *button,gpointer data)
{
extern int     iret;
extern char    CEDITOR[];

char command[320];

strcpy(command,CEDITOR);
strcat(command," z88o4.txt");
iret= system(command);
if(iret != 0) ale88c(AL_NOEDO4);
}

/*---------------------------------------------------------------------------------------
* CB_I1D
*--------------------------------------------------------------------------------------*/
void CB_I1D(GtkWidget *button,gpointer data)
{
extern int     iret;

iret= system("z88x -i1tx");
if(iret != 0) ale88c(AL_NOZ88X);
}

/*---------------------------------------------------------------------------------------
* CB_ISD
*--------------------------------------------------------------------------------------*/
void CB_ISD(GtkWidget *button,gpointer data)
{
extern int     iret;

iret= system("z88x -iatx");
if(iret != 0) ale88c(AL_NOZ88X);
}

/*---------------------------------------------------------------------------------------
* CB_NID
*--------------------------------------------------------------------------------------*/
void CB_NID(GtkWidget *button,gpointer data)
{
extern int     iret;

iret= system("z88x -nitx");
if(iret != 0) ale88c(AL_NOZ88X);
}

/*---------------------------------------------------------------------------------------
* CB_DI1
*--------------------------------------------------------------------------------------*/
void CB_DI1(GtkWidget *button,gpointer data)
{
extern int     iret;

iret= system("z88x -i1fx");
if(iret != 0) ale88c(AL_NOZ88X);
}

/*---------------------------------------------------------------------------------------
* CB_DIS
*--------------------------------------------------------------------------------------*/
void CB_DIS(GtkWidget *button,gpointer data)
{
extern int     iret;

iret= system("z88x -iafx");
if(iret != 0) ale88c(AL_NOZ88X);
}

/*---------------------------------------------------------------------------------------
* CB_DNI
*--------------------------------------------------------------------------------------*/
void CB_DNI(GtkWidget *button,gpointer data)
{
extern int     iret;

iret= system("z88x -nifx");
if(iret != 0) ale88c(AL_NOZ88X);
}

/*---------------------------------------------------------------------------------------
* CB_IN0
*--------------------------------------------------------------------------------------*/
void CB_IN0(GtkWidget *button,gpointer data)
{
extern int     ifnili;

ifnili= 0;
}

/*---------------------------------------------------------------------------------------
* CB_IN9
*--------------------------------------------------------------------------------------*/
void CB_IN9(GtkWidget *button,gpointer data)
{
extern int     ifnili;

ifnili= 9;
}

/*---------------------------------------------------------------------------------------
* CB_FC
*--------------------------------------------------------------------------------------*/
void CB_FC(GtkWidget *button,gpointer data)
{
extern int     iret,ifnili;

if(ifnili == 0) iret= system("z88r -c -choly");
if(ifnili == 9) iret= system("z88r -t -choly");
if(iret   != 0) ale88c(AL_NOZ88R);
}

/*---------------------------------------------------------------------------------------
* CB_I2C
*--------------------------------------------------------------------------------------*/
void CB_I2C(GtkWidget *button,gpointer data)
{
extern int     iret,ifnili;

if(ifnili == 0) iret= system("z88r -c -siccg");
if(ifnili == 9) iret= system("z88r -t -siccg");
if(iret   != 0) ale88c(AL_NOZ88R);
}

/*---------------------------------------------------------------------------------------
* CB_I2S
*--------------------------------------------------------------------------------------*/
void CB_I2S(GtkWidget *button,gpointer data)
{
extern int     iret,ifnili;

if(ifnili == 0) iret= system("z88r -c -sorcg");
if(ifnili == 9) iret= system("z88r -t -sorcg");
if(iret   != 0) ale88c(AL_NOZ88R);
}


