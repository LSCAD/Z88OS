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
*  Z88O fuer Windows
*  7.3.2017 RIEG
***********************************************************************/
/***********************************************************************
* Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88o.h>
#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <gl\gl.h>
#include <string.h>  /* strcpy */
#include <stdio.h>   /* fopen, fprintf, fclose */
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

/**********************************************************
* Deklaration von Window- Functions
**********************************************************/
LRESULT CALLBACK Z88O_WinProc(HWND, UINT, WPARAM, LPARAM);
HWND             InitToolBar (HWND hParent);
BOOL    CALLBACK StrucDiaProc(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK FaktorVerDiaProc(HWND,UINT,WPARAM,LPARAM);
BOOL    CALLBACK FaktorRotDiaProc(HWND,UINT,WPARAM,LPARAM);
BOOL    CALLBACK FaktorZmDiaProc( HWND,UINT,WPARAM,LPARAM);
BOOL    CALLBACK KnotenDiaProc(   HWND,UINT,WPARAM,LPARAM);
BOOL    CALLBACK ElementDiaProc(  HWND,UINT,WPARAM,LPARAM);
void    PopFileInitialize(HWND) ;
BOOL    PopFileOpenDlg(HWND);

/**********************************************************
* Deklaration von User-Functions
**********************************************************/
int      dyn88o(void);
int      ri1x88(void);
int      ri2x88(void);
int      ri5x88(void);
int      ro2x88(void);
int      ro5x88(void);
int      ro8x88(void);
int      rogl88(void);
int      wlog88o(FR_INT4,int);
int      ale88o(int);
int      lan88o(void);
int      vu3b88(void);
int      vv3b88(void);
int      vgpc88(void);
int      vsca88(void);
int      vcur88(void);
int      stro88(void);
int      snow88(void);
int      spgp88(void);
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
int      malk88(void);
int      magp88(void);
int      fsrb88(void);
int      mrbd88(void);
int      man88o(void);

GLFONT * FontCreate(HDC hdc,const char *typeface,
                    int height,int weight,DWORD italic);
void	 FontPuts(GLFONT *font, const char *cs);
void     FontDelete(GLFONT *font);

/**********************************************************
*  externe Variable
**********************************************************/
HINSTANCE    hInstance,hProgram;

HMENU        hMenuGer,hMenuEng;

HCURSOR      waitcur;

HWND         hWnd,hToolBar;

OPENFILENAME ofn;

HDC          hDC;
HGLRC        hRC;

GLFONT       *Font;

int          iRb=1,ixClient= 1024,iyClient= 740,ix,iy;

PIXELFORMATDESCRIPTOR pfd = {
    sizeof(PIXELFORMATDESCRIPTOR), /* WORD  nSize        */
    1,                             /* WORD  nVersion     */
    PFD_DRAW_TO_WINDOW |           /* DWORD dwFlags      */
    PFD_SUPPORT_OPENGL |
    PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA,                 /* BYTE  iPixelType   */
    32,                            /* BYTE  cColorBits   */
    0,0,0,0,0,0,0,0,0,0,0,0,0,     /* brauchen wir nicht */
    16,                            /* BYTE  cDepthBits   */
    0,                             /* BYTE  cStencilBits */
    0,                             /* BYTE  cAuxBuffers  */
    PFD_MAIN_PLANE,                /* BYTE  iLayerType   */
    0,0,0,0};                      /* brauchen wir nicht */

FILE *fdyn,*fwlo,*fi1,*fi2,*fi5,*fo2,*fo5,*fo8,*fcfg,*fman;

/*
** fdyn= z88.dyn
** fwlo= z88o.log
** fo2=  z88o2.txt
** fi1=  z88i1.txt
** fi2=  z88i2.txt
** fi5=  z88i5.txt
** fo5=  z88o5.txt
** fo8=  z88o8.txt
** fcfg= z88com.cfg
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

FR_DOUBLE sigmin,sigmax=0.,siginc;
FR_DOUBLE snemin,snemax=0.,sneinc;
FR_DOUBLE spamin,spamax=0.,spainc;
FR_DOUBLE fxmin,fxmax=-1e-10,fxinc;
FR_DOUBLE fymin,fymax=-1e-10,fyinc;
FR_DOUBLE fzmin,fzmax=-1e-10,fzinc;

FR_INT4 MAXKOI,MAXE,MAXK,MAXRBD,MAXPR,MAXGP;
FR_INT4 IDYNMEM,LANG=2;

FR_INT4 ndim,nkp,ne,nfg,iepanz,kflag,ibflag,ipflag,iqflag;
FR_INT4 i,j,idummy,jdummy,kofold,nrb,npr,nnp;
FR_INT4 izoom= 1;
FR_INT4 jkvon= 0,jkbis= 0,jevon= 0,jebis= 0;
FR_INT4 isflag,igpanz;
FR_INT4 NEEDKOI;

int iflade= ID_NOTLOADSTRUC;
int iflaver=ID_NOTLOADVERF;
int iflspa= ID_NOTLOADSPANN;  /* Z88O8.TXT */
int iflao5= ID_NOTLOADSPAO5;  /* Z88O5.TXT */
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
int  imatrix=1;

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
char  cfg[11]   = "z88com.cfg";
char  cman[11]  = "z88man.txt";

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
char callbrow[512];

/**********************************************************
* Hauptprogramm mit Message- Loop
**********************************************************/
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   PSTR szCmdLine, int iCmdShow)
{
extern HINSTANCE hProgram;

extern HWND      hWnd;
extern int       ixClient,iyClient;

HACCEL           hAccel;
MSG              msg;
WNDCLASSEX       wndclass;

char             capname[10];

/*---------------------------------------------------------
* Window registrieren
*--------------------------------------------------------*/
hProgram= hInstance;

strcpy(capname, "Z88O");

wndclass.cbSize        = sizeof(wndclass);
wndclass.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
wndclass.lpfnWndProc   = Z88O_WinProc;
wndclass.cbClsExtra    = 0;
wndclass.cbWndExtra    = 0;
wndclass.hInstance     = hProgram;
wndclass.hIcon         = LoadIcon(hProgram,
                           MAKEINTRESOURCE(ICO_Z88O));
wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
wndclass.hbrBackground = CreateSolidBrush(RGB(255,255,255));
wndclass.lpszMenuName  = NULL;
wndclass.lpszClassName = capname;
wndclass.hIconSm       = NULL;

RegisterClassEx(&wndclass);

/*---------------------------------------------------------
* Window erzeugen
*--------------------------------------------------------*/
hWnd = CreateWindow(capname,
                    "Z88O",
                    WS_OVERLAPPEDWINDOW |
                    WS_CLIPCHILDREN |
                    WS_CLIPSIBLINGS ,
                    0,0,
                    ixClient,iyClient,
                    NULL, NULL, hProgram, NULL);
if(!hWnd)
  {
  MessageBox(NULL,"Impossible to start Main Window!",
             "Z88O",MB_OK | MB_ICONINFORMATION);
  return (0);
  }

/*---------------------------------------------------------
* Toolbar ermoeglichen
*--------------------------------------------------------*/
InitCommonControls();

/*---------------------------------------------------------
* Window darstellen
*--------------------------------------------------------*/
ShowWindow(hWnd,iCmdShow);

/*---------------------------------------------------------
* Accelerators laden
*--------------------------------------------------------*/
hAccel= LoadAccelerators(hInstance,capname);

/*---------------------------------------------------------
* Message- Loop: Ereigneisse abfangen
*--------------------------------------------------------*/
while(GetMessage(&msg, NULL, 0, 0))
  {
  if(!TranslateAccelerator(hWnd,hAccel,&msg))
    {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    }
  }

return msg.wParam;
}

/**********************************************************
* Main Window Procedure: Das eigentliche Steuerprogramm
**********************************************************/
LRESULT CALLBACK Z88O_WinProc(HWND hWnd, UINT Message,
                             WPARAM wParam, LPARAM lParam)
{
HMENU hMenu;

int   iPF,imess,ialert;

extern char  cmess[];

/*----------------------------------------------------------------------
* Los gehts - je nach Message verzweigen
*---------------------------------------------------------------------*/
switch(Message)
  {
/*----------------------------------------------------------------------
* WM_CREATE
*---------------------------------------------------------------------*/
  case WM_CREATE:

/*======================================================================
* hInstance kommen lassen
*=====================================================================*/
#ifdef FR_XWIN64
    hInstance= (HINSTANCE)GetWindowLongPtr(hWnd,GWLP_HINSTANCE);
#endif
#ifdef FR_XWIN32
    hInstance= (HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE);
#endif

/*======================================================================
* Wartecursor anlegen
*=====================================================================*/
    waitcur= LoadCursor(hInstance,MAKEINTRESOURCE(CUR_Z88O));

/*======================================================================
* Sprache feststellen
*=====================================================================*/
    iret= lan88o();

    if(iret != 0)
      {
      ale88o(iret);
      PostQuitMessage(0);
      return(1);
      }

    hMenuGer= LoadMenu(hInstance,"GERMAN");
    hMenuEng= LoadMenu(hInstance,"ENGLISH");

    if(LANG == 1) SetMenu(hWnd,hMenuGer);
    if(LANG == 2) SetMenu(hWnd,hMenuEng);

/*======================================================================
* dynamischen Speicher anfordern
*=====================================================================*/
    iret= dyn88o();
    if(iret != 0)
      {
      ale88o(iret);
      PostQuitMessage(0);
      return(1);
      }

/*======================================================================
* FYCOR, Farben, Licht und Material einlesen
*=====================================================================*/
    iret= rogl88();
    if(iret != 0)
      {
      ale88o(iret); 
      PostQuitMessage(0);
      return 0;
      }

    ym*= fycor;
    yp*= fycor;

/*======================================================================
* Toolbar
*=====================================================================*/
    hToolBar= InitToolBar(hWnd);

/*======================================================================
* Fileauswahlbox initialisiren
*=====================================================================*/
    PopFileInitialize(hWnd);

/*======================================================================
* OpenGL aktivieren
*=====================================================================*/
    hDC = GetDC(hWnd);
    iPF = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC, iPF, &pfd);
    hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);

    Font= FontCreate(hDC,"Helvetica",20,0,1);

    IB= ixClient;
    IH= iyClient-48;

    SV = (double) IH / (double) IB;
    ymsv = ym * SV;
    ypsv = yp * SV;

    glViewport(0,0,IB,IH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(xm,xp,ymsv,ypsv,zm,zp);

  return 0;

/*----------------------------------------------------------------------
* case WM_INITMENU
*---------------------------------------------------------------------*/
  case WM_INITMENU:
    hMenu= GetMenu(hWnd);
    CheckMenuItem(hMenu,iflabe,           MF_CHECKED   | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,ifrbd,            MF_CHECKED   | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,ifwbc,            MF_CHECKED   | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,ifkoor,           MF_CHECKED   | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,ifnost,           MF_CHECKED   | MF_BYCOMMAND);   
  return 0;

/*----------------------------------------------------------------------
* WM_NOTIFY
*---------------------------------------------------------------------*/
  case WM_NOTIFY:
    {
    LPNMHDR pnmh= (LPNMHDR) lParam;
    LPSTR   pReply;

    if(pnmh->code == TTN_NEEDTEXT)
      {
      LPTOOLTIPTEXT lpttt= (LPTOOLTIPTEXT) lParam;

      switch(lpttt->hdr.idFrom)
        {
        case ITC_RUN:
          if(LANG == 1) pReply= "Start frei";
          if(LANG == 2) pReply= "Go";
        break;

        case ITC_FILE:
          if(LANG == 1) pReply= "Strukturfile angeben";
          if(LANG == 2) pReply= "define structure file";
        break;

        case ITC_MAUS:
          if(LANG == 1) pReply= "Zoom-Schieben-Rotieren ueber Tastatur (aus) oder Maus (ein)";
          if(LANG == 2) pReply= "Zoom-Pan-Rotate by Keyboard (off) or by Mouse (on)";
        break;

        case ITC_HELP:
          if(LANG == 1) pReply= "OnLine-Hilfe fuer Plotprogramm";
          if(LANG == 2) pReply= "OnLine Help for Plot Program";
        break;

        case ITC_UNVERFORMT:
          if(LANG == 1) pReply= "Zeige unverformte Struktur";
          if(LANG == 2) pReply= "Show Undeflected Structure";
        break;

        case ITC_VERFORMT:
          if(LANG == 1) pReply= "Zeige verformte Struktur";
          if(LANG == 2) pReply= "Show Deflected Structure";
        break;

        case ITC_LIGHT:
          if(LANG == 1) pReply= "Licht an, auf Wunsch Anzeige Randbedingungen";
          if(LANG == 2) pReply= "Light on, show Boundary Conditions on request";
        break;

        case ITC_HIDDEN:
          if(LANG == 1) pReply= "Verdeckte Linien (nur 3D), auf Wunsch Anzeige Randbedingungen";
          if(LANG == 2) pReply= "Hidden Line (3D only), show Boundary Conditions on request";
        break;

        case ITC_WIREFR:
          if(LANG == 1) pReply= "Wireframe, auf Wunsch Anzeige Randbedingungen";
          if(LANG == 2) pReply= "Wireframe, show Boundary Conditions on request";
        break;

        case ITC_SHOWSPANN:
          if(LANG == 1) pReply= "Vergleichsspannungen in den Eckknoten";
          if(LANG == 2) pReply= "Reduced Stresses (v.Mises,Rankine,Tresca) in corner nodes";
        break;

        case ITC_SHOWGAUSS:
          if(LANG == 1) pReply= "Vergleichsspannungen pro Element gemittelt";
          if(LANG == 2) pReply= "Reduced Stresses (v.Mises,Rankine,Tresca) mean values per Element";
        break;

        case ITC_SHOWGAUPU:
          if(LANG == 1) pReply= "Vergleichsspannungen (nur unverformte Struktur) in den Gausspunkten";
          if(LANG == 2) pReply= "Reduced Stresses (v.Mises,Rankine,Tresca) -undeflected structure only- in Gauss points";
        break;

        case ITC_SHOWVX:
          if(LANG == 1) pReply= "Zeige X-Verschiebungen";
          if(LANG == 2) pReply= "Show X Displacements";
        break;

        case ITC_SHOWVY:
          if(LANG == 1) pReply= "Zeige Y-Verschiebungen";
          if(LANG == 2) pReply= "Show Y Displacements";
        break;

        case ITC_SHOWVZ:
          if(LANG == 1) pReply= "Zeige Z-Verschiebungen";
          if(LANG == 2) pReply= "Show Z Displacements";
        break;

        case ITC_YESSCALE:
          if(LANG == 1) pReply= "Auto-Skalieren";
          if(LANG == 2) pReply= "AutoScale";
        break;

        case ITC_RBD:
          if(LANG == 1) pReply= "Zeige Randbedingungen ja/nein";
          if(LANG == 2) pReply= "Show Boundary Conditions yes/no";
        break;

        case ITC_XIT:
          if(LANG == 1) pReply= "Beende";
          if(LANG == 2) pReply= "Exit";
        break;

        }
      lstrcpy(lpttt->szText,pReply);
      }
    return 0;  /* sehr wichtig */
    }

/*----------------------------------------------------------------------
* WM_DESTROY
*---------------------------------------------------------------------*/
  case WM_DESTROY:
    wglMakeCurrent(hDC,NULL);
    wglDeleteContext(hRC);
    PostQuitMessage(0);
  return 0;

/*----------------------------------------------------------------------
* case WM_COMMAND
*---------------------------------------------------------------------*/
  case WM_COMMAND:
    switch (LOWORD(wParam))
      {
/*======================================================================
* Info
*=====================================================================*/ 
      case IDM_WER:
        if(LANG == 1) strcpy(cmess,
"Plotprogramm Z88O fuer Windows\n\
Version 15OS\n\
Copyright Univ.-Prof.Dr.-Ing. Frank Rieg,\n\
Universitaet Bayreuth, 2017\n\
Alle Rechte vorbehalten\n");

          if(LANG == 2) strcpy(cmess,
"Plot Program Z88O for Windows\n\
Version 15OS\n\
Copyright Prof.Dr. Frank Rieg,\n\
University of Bayreuth, Germany 2017\n\
All rights reserved\n");

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

        MessageBox(hWnd,cmess,"Z88O", MB_OK | MB_ICONINFORMATION);
      return 0;

/*======================================================================
* Strukturfile
*=====================================================================*/                           
      case ITC_FILE:
        if(PopFileOpenDlg(hWnd))
          {
          iflade = ID_NOTLOADSTRUC;  /* Z88I1.TXT */
          iflaver= ID_NOTLOADVERF;   /* Z88O2.TXT */
          iflspa = ID_NOTLOADSPANN;  /* Z88O8.TXT */
          iflao5 = ID_NOTLOADSPAO5;  /* Z88O5.TXT */
          ifscale= IDM_YESSCALE;
          rotx= 0.;
          roty= 0.;
          rotz= 0.;
          }
        else
          {
          if(LANG == 1) strcpy(cmess,"Z88O: keine Datei ausgewaehlt");
          if(LANG == 2) strcpy(cmess,"Z88O: You did not choose any file");
          MessageBox(hWnd,cmess,"Z88O", MB_OK | MB_ICONINFORMATION);
          }
      return 0;

/*======================================================================
* Ende
*=====================================================================*/
      case IDM_XIT:
      case ITC_XIT:
        PostQuitMessage(0);
      return 0; 

/*======================================================================
* Go: Z88MAN.TXT untersuchen und Strukturdaten Z88I1.TXT laden
*=====================================================================*/
      case ITC_RUN:
        SetCursor(waitcur);
        ShowCursor(TRUE);

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
          return(0);
          }
        rewind(fi1);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88I1.TXT laden
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        ialert=ri1x88();  
        if(ialert != 0) ale88o(ialert);
        else            iflade= ID_LOADSTRUC;
        
        if(fi1) fclose(fi1); 
        SetCursor(LoadCursor(NULL,IDC_ARROW)); 
        jkvon= 1;
        jkbis= nkp;
        jevon= 1;
        jebis= ne;
        InvalidateRect(hWnd,NULL,TRUE);
      return(0);

/*======================================================================
* COMMAND : Hilfe
*=====================================================================*/
      case ITC_HELP:
        fcfg= fopen(cfg,"r");          /* Z88COM.CFG oeffnen */
        if(fcfg == NULL)
          {
          if(LANG == 1) strcpy(cmess,
          "Datei Z88COM.CFG nicht vorhanden oder zerschossen !");
          if(LANG == 2) strcpy(cmess,
          "File Z88COM.CFG not available or destroyed !");
          MessageBox(NULL,cmess,"Z88G", MB_OK | MB_ICONHAND);
          }

        rewind(fcfg);

        fgets(cstore,128,fcfg);
        fgets(cstore,128,fcfg);

        fgets(cstore,128,fcfg);
        laenge= strlen(cstore);
        strncpy(cbpref,cstore,laenge-1);
        strcat (cbpref,"\0");

        fgets(cstore,128,fcfg);
        laenge= strlen(cstore);
        strncpy(cbcall,cstore,laenge-1);
        strcat (cbcall,"\0");

        fclose(fcfg); 

        strcpy(callbrow,cbcall);
        strcat(callbrow," ");
        strcat(callbrow,cbpref);
        if(LANG == 1) strcat(callbrow,"z88mang.pdf");
        if(LANG == 2) strcat(callbrow,"z88mane.pdf");
        imess= WinExec(callbrow,SW_SHOW);
        if(imess < 33) 
          {
          wlog88o(0L,LOG_NOACROBAT);
          ale88o(AL_NOACROBAT);
          }
      return 0;

/*======================================================================
* Keyboard oder Maus fuer Zoom-Schieben-Rotieren
*=====================================================================*/ 
      case ITC_MAUS:
        if(ifkom == ID_FUNKEY ) ifkom= ID_MOUSE;
        else                    ifkom= ID_FUNKEY;
      return 0;

/*======================================================================
* Unverformt oder verformt
*=====================================================================*/ 
      case ITC_UNVERFORMT:
        ifverf = IDM_UNVERFORMT; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_VERFORMT:
        ifverf = IDM_VERFORMT; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
* Bild
*=====================================================================*/ 
      case IDM_PRIOR:
        facx *= fzoom;
        facy *= fzoom;
        facz *= fzoom;
        izoom++;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;
      
      case IDM_NEXT:
        facx /= fzoom;
        facy /= fzoom;
        facz /= fzoom;
        izoom--;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0; 

      case IDM_UP:
        if(ifvcur == 0) vcur88();
        cy= cy - 0.05*(fabs(ymax) + fabs(ymin))/pow(fzoom,(double)izoom);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_DOWN:
        if(ifvcur == 0) vcur88();
        cy= cy + 0.05*(fabs(ymax) + fabs(ymin))/pow(fzoom,(double)izoom);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_RIGHT:
        if(ifvcur == 0) vcur88();
        cx= cx - 0.05*(fabs(xmax) + fabs(xmin))/pow(fzoom,(double)izoom);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_LEFT:
        if(ifvcur == 0) vcur88();
        cx= cx + 0.05*(fabs(xmax) + fabs(xmin))/pow(fzoom,(double)izoom);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_HOME:
        if(ifvcur == 0) vcur88();
        cz= cz - 0.05*(fabs(zmax) + fabs(zmin))/pow(fzoom,(double)izoom);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_END:
        if(ifvcur == 0) vcur88();
        cz= cz + 0.05*(fabs(zmax) + fabs(zmin))/pow(fzoom,(double)izoom);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;
 
      case IDM_F2:
        rotx -= 10.;
        if ((int)rotx == -10) rotx= 350.;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_F3:
        rotx += 10.;
        if ((int)rotx == 360) rotx= 0.;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_F4:
        roty -= 10.;
        if ((int)roty == -10) roty= 350.;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_F5:
        roty += 10.;
        if ((int)roty == 360) roty= 0.;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_F6:
        rotz -= 10.;
        if ((int)rotz == -10) rotz= 350.;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_F7:
        rotz += 10.;
        if ((int)rotz == 360) rotz= 0.;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_F8:
        rotx= 0.;
        roty= 0.;
        rotz= 0.;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
* Faktor-Boxen
*=====================================================================*/ 
      case IDM_VER:
        if(LANG == 1) DialogBox(hInstance,"Dlg_Ver88G",hWnd,FaktorVerDiaProc);
        if(LANG == 2) DialogBox(hInstance,"Dlg_Ver88E",hWnd,FaktorVerDiaProc);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_ROT:
        if(LANG == 1) DialogBox(hInstance,"Dlg_Rot88G",hWnd,FaktorRotDiaProc);
        if(LANG == 2) DialogBox(hInstance,"Dlg_Rot88E",hWnd,FaktorRotDiaProc);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_ZM:
        if(LANG == 1) DialogBox(hInstance,"Dlg_ZM88G",hWnd,FaktorZmDiaProc);
        if(LANG == 2) DialogBox(hInstance,"Dlg_ZM88E",hWnd,FaktorZmDiaProc);
        glViewport(0,0,IB,IH);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(xm,xp,ym,yp,zm,zp);

        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
* Labels via Menue
*=====================================================================*/ 
      case IDM_NOLABELS:
      case IDM_KNOTEN:
      case IDM_ELEMENTE:
      case IDM_LALLES:
        hMenu= GetMenu(hWnd);
        CheckMenuItem(hMenu,iflabe,MF_UNCHECKED | MF_BYCOMMAND);
        iflabe= LOWORD(wParam);
        CheckMenuItem(hMenu,iflabe,MF_CHECKED | MF_BYCOMMAND);   

        if(iflabe == IDM_LALLES) iplot = 1;
        else                     iplot = 0;

        if(iflabe == IDM_KNOTEN)
          {
          if(LANG == 1) DialogBox(hInstance,"Dlg_Kno88G",hWnd,KnotenDiaProc);
          if(LANG == 2) DialogBox(hInstance,"Dlg_Kno88E",hWnd,KnotenDiaProc);
          }

        if(iflabe == IDM_ELEMENTE)
          {
          if(LANG == 1) DialogBox(hInstance,"Dlg_Ele88G",hWnd,ElementDiaProc);
          if(LANG == 2) DialogBox(hInstance,"Dlg_Ele88E",hWnd,ElementDiaProc);
          }

      InvalidateRect(hWnd,NULL,TRUE);
      return 0;
         
/*======================================================================
* Licht/Hidden Line/Spannungen/Verschiebungen X,Y,Z
*=====================================================================*/ 
      case ITC_LIGHT:
        if3d = IDM_LIGHT; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_HIDDEN:
        if3d = IDM_HIDDEN; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_WIREFR:
        if3d = IDM_WIREFR; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_SHOWSPANN:
        if3d = IDM_SHOWSPANN; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_SHOWGAUSS:
        if3d = IDM_SHOWGAUSS; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_SHOWGAUPU:
        if3d = IDM_SHOWGAUPU; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_SHOWVX:
        if3d = IDM_SHOWVX; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_SHOWVY:
        if3d = IDM_SHOWVY; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_SHOWVZ:
        if3d = IDM_SHOWVZ; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
*     Autoscale setzen
*=====================================================================*/ 
      case ITC_YESSCALE:
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
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
*     Koordinatensystem ?
*=====================================================================*/ 
      case IDM_YESKOOR:
      case IDM_NOKOOR:
        hMenu= GetMenu(hWnd);
        CheckMenuItem(hMenu,ifkoor,MF_UNCHECKED | MF_BYCOMMAND);
        ifkoor= LOWORD(wParam);
        CheckMenuItem(hMenu,ifkoor,MF_CHECKED | MF_BYCOMMAND);   
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
*     Netz ueber Spannungen ?
*=====================================================================*/ 
      case IDM_YESNOST:
      case IDM_NONOST:
        hMenu= GetMenu(hWnd);
        CheckMenuItem(hMenu,ifnost,MF_UNCHECKED | MF_BYCOMMAND);
        ifnost= LOWORD(wParam);
        CheckMenuItem(hMenu,ifnost,MF_CHECKED | MF_BYCOMMAND);   
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
*     Randbedingungen malen?
*=====================================================================*/ 
      case IDM_YESRBD:
      case IDM_NORBD:
        if(!(if3d == IDM_SHOWSPANN || if3d == IDM_SHOWGAUSS ||
             if3d == IDM_SHOWVX || if3d == IDM_SHOWVY || if3d == IDM_SHOWVZ))
          {
          hMenu= GetMenu(hWnd);
          CheckMenuItem(hMenu,ifrbd,MF_UNCHECKED | MF_BYCOMMAND);
          ifrbd= LOWORD(wParam);
          CheckMenuItem(hMenu,ifrbd,MF_CHECKED | MF_BYCOMMAND);   
          if(ifrbd == IDM_YESRBD)
            SendMessage(hToolBar,TB_CHECKBUTTON,(WPARAM)ITC_RBD,(LPARAM) MAKELONG(TRUE,0) );
          else
            SendMessage(hToolBar,TB_CHECKBUTTON,(WPARAM)ITC_RBD,(LPARAM) MAKELONG(FALSE,0) );
          InvalidateRect(hWnd,NULL,TRUE);
          }
        else
          {
          hMenu= GetMenu(hWnd);
          CheckMenuItem(hMenu,ifrbd,MF_UNCHECKED | MF_BYCOMMAND);
          SendMessage(hToolBar,TB_CHECKBUTTON,(WPARAM)ITC_RBD,(LPARAM) MAKELONG(FALSE,0) );
          }
      return 0;

      case ITC_RBD:
        if(!(if3d == IDM_SHOWSPANN || if3d == IDM_SHOWGAUSS ||
             if3d == IDM_SHOWVX || if3d == IDM_SHOWVY || if3d == IDM_SHOWVZ))
          {
          hMenu= GetMenu(hWnd);
          CheckMenuItem(hMenu,ifrbd,MF_UNCHECKED | MF_BYCOMMAND);
          if(ifrbd == IDM_YESRBD) ifrbd= IDM_NORBD;
          else                    ifrbd= IDM_YESRBD;
          if(ifrbd == IDM_YESRBD)
            CheckMenuItem(hMenu,IDM_YESRBD,MF_CHECKED | MF_BYCOMMAND); 
          else
            CheckMenuItem(hMenu,IDM_NORBD,MF_CHECKED | MF_BYCOMMAND); 
          InvalidateRect(hWnd,NULL,TRUE);
          }
        else
          {
          hMenu= GetMenu(hWnd);
          CheckMenuItem(hMenu,ifrbd,MF_UNCHECKED | MF_BYCOMMAND);
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_RBD,(LPARAM) MAKELONG(FALSE,0) );
          }
      return 0;

      case IDM_RBDALL:
      case IDM_RBDUX:
      case IDM_RBDUY:
      case IDM_RBDUZ:
      case IDM_RBDU4:
      case IDM_RBDU5:
      case IDM_RBDU6:
      case IDM_RBDUA:
      case IDM_RBDOL:
      case IDM_RBDFX:
      case IDM_RBDFY:
      case IDM_RBDFZ:
        hMenu= GetMenu(hWnd);
        CheckMenuItem(hMenu,ifwbc,MF_UNCHECKED | MF_BYCOMMAND);
        ifwbc= LOWORD(wParam);
        CheckMenuItem(hMenu,ifwbc,MF_CHECKED | MF_BYCOMMAND);   
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
*     Randbedingungen zoomen?
*=====================================================================*/ 
      case IDM_ZOPLUS:
        zorbd *= 1.5;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_ZOMINUS:
        zorbd /= 1.5;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
*     Gausspunkte zoomen?
*=====================================================================*/ 
      case IDM_GPZOPLUS:
        zoogp *= 1.5;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case IDM_GPZOMINUS:
        zoogp /= 1.5;
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
* Default
*=====================================================================*/ 
      default:
        return DefWindowProc(hWnd, Message, wParam, lParam); /* end switch */
      }

/*----------------------------------------------------------------------
* WM_SIZE: Wenn das Window veraendert wird,dann
*---------------------------------------------------------------------*/
  case WM_SIZE:
    iyClient= HIWORD(lParam);
    ixClient= LOWORD(lParam);

    IB= ixClient;
    IH= iyClient-48;

    SV = (double) IH / (double) IB;
    ymsv = ym * SV;
    ypsv = yp * SV;

    glViewport(0,0,IB,IH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(xm,xp,ymsv,ypsv,zm,zp);

    glMatrixMode(GL_MODELVIEW);
  return 0;

/*----------------------------------------------------------------------
* WM_MOUSEMOVE: Wenn Maus bewegt und linke Taste,dann
*---------------------------------------------------------------------*/
  case WM_MOUSEMOVE:
    if(wParam & MK_LBUTTON)
      {
      iy= HIWORD(lParam);
      ix= LOWORD(lParam);
      xx= (FR_DOUBLE)ix;
      yy= (FR_DOUBLE)iy;
      ifmaus= IDM_PAN;
      InvalidateRect(hWnd,NULL,TRUE);
      }
    if(wParam & MK_MBUTTON)
      {
      iy= HIWORD(lParam);
      ix= LOWORD(lParam);
      xx= (FR_DOUBLE)ix;
      yy= (FR_DOUBLE)iy;
      ifmaus= IDM_ZOOM;
      InvalidateRect(hWnd,NULL,TRUE);
      }
    if(wParam & MK_RBUTTON)
      {
      iy= HIWORD(lParam);
      ix= LOWORD(lParam);
      xx= (FR_DOUBLE)ix;
      yy= (FR_DOUBLE)iy;
      ifmaus= IDM_ROTATE;
      InvalidateRect(hWnd,NULL,TRUE);
      }
  return 0;

/*----------------------------------------------------------------------
* WM_PAINT:
*---------------------------------------------------------------------*/
  case WM_PAINT:

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
      SetCursor(waitcur);
      ShowCursor(TRUE);

      fo2= fopen("z88o2.txt","r");
      if(fo2 == NULL)
        {
        ale88o(AL_NOO2);
        wlog88o(0,LOG_NOO2);
        SetCursor(LoadCursor(NULL,IDC_ARROW)); 
        goto Lflush;
        }
      rewind(fo2);

      ro2x88(); 
      iflaver= ID_LOADVERF;
      if(fo2) fclose(fo2); 
      SetCursor(LoadCursor(NULL,IDC_ARROW)); 
      }

/*======================================================================
* Laden von Z88I2.TXT, wenn Anzeige der Randbedingungen
*=====================================================================*/ 
    if(iflarbd == ID_NOTLOADRBD && ifrbd == IDM_YESRBD)
      {
      SetCursor(waitcur);
      ShowCursor(TRUE);

      fi2= fopen("z88i2.txt","r");
      if(fi2 == NULL)
        {
        ale88o(AL_NOI2);
        wlog88o(0,LOG_NOI2);
        SetCursor(LoadCursor(NULL,IDC_ARROW)); 
        hMenu= GetMenu(hWnd);
        CheckMenuItem(hMenu,(int)IDM_YESRBD,MF_UNCHECKED | MF_BYCOMMAND);
        CheckMenuItem(hMenu,(int)IDM_NORBD, MF_CHECKED   | MF_BYCOMMAND);
        SendMessage(hToolBar,TB_CHECKBUTTON,(WPARAM)ITC_RBD,(LPARAM) MAKELONG(FALSE,0) );
        ifrbd= IDM_NORBD;
        goto Lflush;
        }
      rewind(fi2);

      ialert= ri2x88();
      if(ialert != 0)
        {
        ale88o(ialert);
        wlog88o(0,LOG_EXMAXRBD);
        SetCursor(LoadCursor(NULL,IDC_ARROW)); 
        hMenu= GetMenu(hWnd);
        CheckMenuItem(hMenu,(int)IDM_YESRBD,MF_UNCHECKED | MF_BYCOMMAND);
        CheckMenuItem(hMenu,(int)IDM_NORBD, MF_CHECKED   | MF_BYCOMMAND);
        SendMessage(hToolBar,TB_CHECKBUTTON,(WPARAM)ITC_RBD,(LPARAM) MAKELONG(FALSE,0) );
        ifrbd= IDM_NORBD;
        goto Lflush;
        }
      else
        iflarbd= ID_LOADRBD;
       
      if(fi2) fclose(fi2); 
      SetCursor(LoadCursor(NULL,IDC_ARROW)); 
      }

/*======================================================================
* Laden von Z88I5.TXT, wenn Anzeige der Randbedingungen und Flaechenla.
*=====================================================================*/ 
    if(iflai5 == ID_NOTLOADI5 && ifrbd == IDM_YESRBD && iqflag == 1)
      {
      SetCursor(waitcur);
      ShowCursor(TRUE);

      fi5= fopen("z88i5.txt","r");
      if(fi5 == NULL)
        {
        ale88o(AL_NOI5);
        wlog88o(0,LOG_NOI5);
        SetCursor(LoadCursor(NULL,IDC_ARROW)); 
        hMenu= GetMenu(hWnd);
        CheckMenuItem(hMenu,(int)IDM_YESRBD,MF_UNCHECKED | MF_BYCOMMAND);
        CheckMenuItem(hMenu,(int)IDM_NORBD, MF_CHECKED   | MF_BYCOMMAND);
        SendMessage(hToolBar,TB_CHECKBUTTON,(WPARAM)ITC_RBD,(LPARAM) MAKELONG(FALSE,0) );
        ifrbd= IDM_NORBD;
        goto Lflush;
        }
      rewind(fi5);

      ialert= ri5x88(); 
      if(ialert != 0)
        {
        ale88o(ialert);
        wlog88o(0,LOG_EXMAXPR);
        SetCursor(LoadCursor(NULL,IDC_ARROW)); 
        hMenu= GetMenu(hWnd);
        CheckMenuItem(hMenu,(int)IDM_YESRBD,MF_UNCHECKED | MF_BYCOMMAND);
        CheckMenuItem(hMenu,(int)IDM_NORBD, MF_CHECKED   | MF_BYCOMMAND);
        SendMessage(hToolBar,TB_CHECKBUTTON,(WPARAM)ITC_RBD,(LPARAM) MAKELONG(FALSE,0) );
        ifrbd= IDM_NORBD;
        goto Lflush;
        }
      else
        iflai5= ID_LOADI5;
      
      if(fi5) fclose(fi5); 
      SetCursor(LoadCursor(NULL,IDC_ARROW)); 
      }

/*======================================================================
* Laden von Z88O8.TXT, wenn Anzeige der Spannungen in Eckknoten
*=====================================================================*/ 
    if(iflspa == ID_NOTLOADSPANN && 
        (if3d == IDM_SHOWSPANN ||
         if3d == IDM_SHOWGAUSS))
      {
      SetCursor(waitcur);
      ShowCursor(TRUE);

      fo8= fopen("z88o8.txt","r");
      if(fo8 == NULL)
        {
        ale88o(AL_NOO8);    
        wlog88o(0,LOG_NOO8);
        SetCursor(LoadCursor(NULL,IDC_ARROW)); 
        goto Lflush;
        }
      rewind(fo8);

      ialert= ro8x88();
      if(ialert != 0) ale88o(ialert);
      else            iflspa= ID_LOADSPANN;
      
      if(fo8) fclose(fo8); 
      SetCursor(LoadCursor(NULL,IDC_ARROW)); 
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
        return(AL_NOO5);
        }
      rewind(fo5);

      ialert= ro5x88(); 
      if(ialert != 0) ale88o(ialert);
      else            iflao5= ID_LOADSPAO5;

      if(fo5) fclose(fo5); 
      SetCursor(LoadCursor(NULL,IDC_ARROW)); 
      }

/*======================================================================
* Anzeige Randbedingungen ausschalten fuer die folgenden anderen Anzeigen
*=====================================================================*/ 
    if(if3d == IDM_SHOWSPANN || if3d == IDM_SHOWGAUSS || if3d == IDM_SHOWGAUPU ||
       if3d == IDM_SHOWVX    || if3d == IDM_SHOWVY    || if3d == IDM_SHOWVZ)
      {
      ifrbd= IDM_NORBD;
      hMenu= GetMenu(hWnd);
      CheckMenuItem(hMenu,(int)IDM_YESRBD,MF_UNCHECKED | MF_BYCOMMAND);
      CheckMenuItem(hMenu,(int)IDM_NORBD, MF_CHECKED   | MF_BYCOMMAND);
      SendMessage(hToolBar,TB_CHECKBUTTON,(WPARAM)ITC_RBD,(LPARAM) MAKELONG(FALSE,0) );
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
    glFlush();
    SwapBuffers(hDC);
    ValidateRect(hWnd,NULL);
  return 0;

/*=========================================================
* Wenn keine der obigen Cases zutrifft, dann
*========================================================*/
  default:
    return DefWindowProc(hWnd,Message,wParam,lParam);
  }
}

