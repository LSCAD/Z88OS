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
* Z88COM fuer Windows
* 7.3.2017 Rieg
***********************************************************************/

/***********************************************************************
* Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88com.h>

#include <windows.h>
#include <commctrl.h>

#include <string.h>  /* strcpy, strcat */
#include <stdio.h>   /* fopen, fscanf, fprintf, fclose */
#endif

/***********************************************************************
*  Window-Function-Declarationen
***********************************************************************/
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

HWND InitToolBar   (HWND hParent);
HWND InitStatusBar (HWND hParent);

BOOL CALLBACK EditDiaProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK BrowDiaProc(HWND, UINT, WPARAM, LPARAM);

HFONT EzCreateFont (HDC hdc, char * szFaceName, int iDeciPtHeight,
                    int iDeciPtWidth, int iAttributes, BOOL fLogRes);

void  MatFileInitialize(HWND) ;
BOOL  MatFileOpenDlg(HWND);

/***********************************************************************
*  Window-Variablen-Declarationen
***********************************************************************/
HMENU      hMenuGer,hMenuEng;
HMENU      hMenu;

HINSTANCE  hInstance;

HWND       hToolBar;
HWND       hStatusBar;

HDC        hDC;

HDC        hDCStatus;

RECT       rect;

HFONT      hFont;

OPENFILENAME ofn;

/***********************************************************************
*  Function-Declarationen
***********************************************************************/
int ale88c(int);
int lan88c(void);
int wlog88c(FR_INT4,int);

/***********************************************************************
* Globale Variable
***********************************************************************/
/*--------------------------------------------------------------------------
* Files
*-------------------------------------------------------------------------*/
FILE *fdyn,*fwlo;

/*  
**   fdyn= z88.dyn
**   fwlo= z88com.log
*/ 

char cdyn[8]  = "z88.dyn";
char clgd[11] = "z88com.log";

/*--------------------------------------------------------------------------
* Variable
*-------------------------------------------------------------------------*/
FR_INT4 LANG= 2;

int  iflago;

int  *pp;

char cename[128],cecall[128],calledit[512];
char cbpref[128],cbcall[128],callbrow[512];

char  cfname[256];
char  ctname[256];
char  cstrn[256];

/***********************************************************************
* WinMain-Function
***********************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   PSTR lpszCmdLine, int nCmdShow)
{
HWND       hWnd;
MSG        msg;
WNDCLASSEX wndclass;

HBITMAP    hBitmap;
HBRUSH     hBrush;

char       capname[10];

/***********************************************************************
* Handles kommen lassen, window oeffnen
***********************************************************************/
strcpy(capname, "Z88COM");

hBitmap= LoadBitmap(hInstance,MAKEINTRESOURCE(BMP_Z88BGR));
hBrush=  CreatePatternBrush(hBitmap);

wndclass.cbSize        = sizeof(wndclass);
wndclass.style         = CS_HREDRAW | CS_VREDRAW;
wndclass.lpfnWndProc   = WndProc;
wndclass.cbClsExtra    = 0;
wndclass.cbWndExtra    = 0;
wndclass.hInstance     = hInstance;
wndclass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88COM));
wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
wndclass.hbrBackground = hBrush;
wndclass.lpszMenuName  = capname;
wndclass.lpszClassName = capname;
wndclass.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88COM));

RegisterClassEx(&wndclass);

hWnd = CreateWindow(capname,"Z88-Commander Z88COM V15OS",
                    WS_OVERLAPPEDWINDOW,
                      0,  10,
                    500, 200,
                    NULL, NULL, hInstance, NULL);

InitCommonControls();

ShowWindow(hWnd, nCmdShow);
UpdateWindow(hWnd);

while(GetMessage(&msg, NULL, 0, 0))
  {
  TranslateMessage(&msg);
  DispatchMessage(&msg);
  }

DeleteObject(hFont);              /* Font fuer Statusleiste */
ReleaseDC(hStatusBar,hDCStatus);  /* HDC fuer Statusleiste  */
DeleteObject((HGDIOBJ) hBrush);   /* Hintergrund-Pattern    */
DeleteObject((HGDIOBJ) hBitmap);  /* Hintergrund-Bitmap     */

return msg.wParam;
}

/***********************************************************************
* Main Window Procedure
***********************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT Message,
                         WPARAM wParam, LPARAM lParam)
{
extern FR_INT4    LANG;

extern            int iflago;
extern char       cename[],cecall[],calledit[];
extern char       cbpref[],cbcall[],callbrow[];


HDC               hDC;
PAINTSTRUCT       ps;

RECT              rect;

FILE              *fcfg;

long              lpos,i;
int               imess= 0, c, iret;
static int        iq= 0;  /* kontextsensitive Hilfe an-aus */

size_t            laenge;

char              cmess[512];
char              cbytes[128];
char              cstore[256];
        
/***********************************************************************
* Los gehts
***********************************************************************/
switch (Message)
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
* Sprache feststellen
*=====================================================================*/
    iret= lan88c();

    if(iret != 0) 
      {
      ale88c(iret);
      PostQuitMessage(0);
      return(1);
      }

    hMenuGer= LoadMenu(hInstance,"GERMAN");
    hMenuEng= LoadMenu(hInstance,"ENGLISH");

    if(LANG == 1) SetMenu(hWnd,hMenuGer);
    if(LANG == 2) SetMenu(hWnd,hMenuEng);

/*======================================================================
* z88com.cfg oeffnen
*=====================================================================*/
    fcfg= fopen("z88com.cfg","r");
    if(fcfg == NULL)
      {
      wlog88c(0L,LOG_NOCFG);
      ale88c(AL_NOCFG);
      fclose(fwlo);
      PostQuitMessage(0);
      return 0;
      }

    rewind(fcfg);


    fgets(cstore,128,fcfg);
    laenge= strlen(cstore);
    strncpy(cename,cstore,laenge-1);
    strcat (cename,"\0");

    fgets(cstore,128,fcfg);
    laenge= strlen(cstore);
    strncpy(cecall,cstore,laenge-1);
    strcat (cecall,"\0");

    fgets(cstore,128,fcfg);
    laenge= strlen(cstore);
    strncpy(cbpref,cstore,laenge-1);
    strcat (cbpref,"\0");

    fgets(cstore,128,fcfg);
    laenge= strlen(cstore);
    strncpy(cbcall,cstore,laenge-1);
    strcat (cbcall,"\0");

    fclose(fcfg); 

/*======================================================================
* Toolbar
*=====================================================================*/
    hToolBar= InitToolBar(hWnd);

/*======================================================================
* Fileauswahlbox initialisiren
*=====================================================================*/
    MatFileInitialize(hWnd);

/*======================================================================
* Statusbar
*=====================================================================*/
    hStatusBar= InitStatusBar(hWnd);

    hDCStatus= GetDC(hStatusBar);
    hFont= EzCreateFont(hDCStatus,"Times New Roman",120,0,2,TRUE);
    SelectObject(hDCStatus,hFont);

/*  So geht's auch: via TextOut                                       */
/*  SetBkColor(hDCStatus,RGB(255,128,0));                             */
/*  TextOut(hDCStatus,1,3,"   Filechecker gestartet  ",26);           */

  return 0; /* Ende WM_CREATE */

/*----------------------------------------------------------------------
* WM_INITMENU
*---------------------------------------------------------------------*/
  case WM_INITMENU:
    hMenu= GetMenu(hWnd); 
  return 0;

/*----------------------------------------------------------------------
* WM_MOVE
*---------------------------------------------------------------------*/
  case WM_MOVE:
    if(LANG == 1) strcpy(cmess,"Erwarte Ihre Befehle..");
    if(LANG == 2) strcpy(cmess,"Awaiting Your Commands");
    GetClientRect(hStatusBar,&rect);
    DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  
  return 0;
    
/*----------------------------------------------------------------------
* WM_SIZE
*---------------------------------------------------------------------*/
  case WM_SIZE:
    {
    int icxParent= LOWORD(lParam);
    int icyParent= HIWORD(lParam);
    int ix,iy,icx,icy;

    GetWindowRect(hStatusBar, &rect);
    icy= rect.bottom - rect.top;

    ix= 0;
    iy= icyParent - icy;
    icx= icxParent;

    MoveWindow(hStatusBar,ix,iy,icx,icy,TRUE);

    SendMessage(hToolBar,TB_AUTOSIZE,0,0L);
     
    return 0;
    }
     
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
        case ITC_Z88X:
          if(LANG == 1) pReply= "Start des DXF-Konverters Z88X";
          if(LANG == 2) pReply= "Launch the DXF Converter Z88X";
        break;

        case ITC_Z88G:
          if(LANG == 1) pReply= "Start des COSMOS/NASTRAN-Konverters Z88G";
          if(LANG == 2) pReply= "Launch the COSMOS/NASTRAN Converter Z88G";
        break;

        case ITC_Z88H:
          if(LANG == 1) pReply= "Start des Cuthill-McKee Programms Z88H";
          if(LANG == 2) pReply= "Launch the Cuthill McKee Programm Z88H";
        break;

        case ITC_Z88N:
          if(LANG == 1) pReply= "Start des Netzgenerators Z88N";
          if(LANG == 2) pReply= "Launch the Mapped Mesher Z88N";
        break;

        case ITC_Z88R:
          if(LANG == 1) pReply= "Start des Solvers Z88R";
          if(LANG == 2) pReply= "Launch the Solver Z88R";
        break;

        case ITC_Z88O:
          if(LANG == 1) pReply= "Start des Plotprogramms Z88O";
          if(LANG == 2) pReply= "Launch the Plot Program Z88O";
        break;

         case ITC_DYN:
          if(LANG == 1) pReply= "Editieren der Speicher-Steuerdatei Z88.DYN";
          if(LANG == 2) pReply= "Edit the Memory Headerfile Z88.DYN";
        break;

        case ITC_HELP:
          if(LANG == 1) pReply= "OnLine-Hilfe";
          if(LANG == 2) pReply= "OnLine Help";
        break;

        case ITC_XIT:
          if(LANG == 1) pReply= "Beenden";
          if(LANG == 2) pReply= "Exit";
        break;
        }
      lstrcpy(lpttt->szText,pReply);
      }
    return 0;  /* sehr wichtig */
    }

/*----------------------------------------------------------------------
* WM_COMMAND
*---------------------------------------------------------------------*/
  case WM_COMMAND:
    hMenu= GetMenu(hWnd);
    switch (LOWORD(wParam))
      {

/*----------------------------------------------------------------------
* COMMAND : Menue Datei
*---------------------------------------------------------------------*/
/*======================================================================
* COMMAND : Editor festlegen
*=====================================================================*/
      case IDM_EDITFEST:
          iflago= 0;

          if(LANG == 1) DialogBox(hInstance,"Dlg_Edit88G",hWnd,EditDiaProc);
          if(LANG == 2) DialogBox(hInstance,"Dlg_Edit88E",hWnd,EditDiaProc);
          InvalidateRect(hWnd,NULL,TRUE);

          if(iflago== 1)  /* dann wurde im Dialog o.k. gegeben */
            {
            fcfg= fopen("z88com.cfg","w");
            if(fcfg == NULL)
              {
              wlog88c(0L,LOG_NOCFG);
              ale88c(AL_NOCFG);
              fclose(fwlo);
              PostQuitMessage(0);
              return 0;
              }

            rewind(fcfg);

            fputs (cename,fcfg);
            fprintf(fcfg,"\n");
            fputs (cecall,fcfg);
            fprintf(fcfg,"\n");
            fputs (cbpref,fcfg);
            fprintf(fcfg,"\n");
            fputs (cbcall,fcfg);
            fprintf(fcfg,"\n");

            iflago= 0;
            fflush(fcfg);
            fclose(fcfg);

            if(LANG == 1) strcpy(cmess,"Editor fuer Z88 definiert");
            if(LANG == 2) strcpy(cmess,"Editor defined for Z88");
            GetClientRect(hStatusBar,&rect);
            DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT); 
            } 
      return 0; 

/*======================================================================
* COMMAND : Browser festlegen
*=====================================================================*/
      case IDM_ACROBAT:
          iflago= 0;

          if(LANG == 1) DialogBox(hInstance,"Dlg_Brow88G",hWnd,BrowDiaProc);
          if(LANG == 2) DialogBox(hInstance,"Dlg_Brow88E",hWnd,BrowDiaProc);
          InvalidateRect(hWnd,NULL,TRUE);

          if(iflago== 1)  /* dann wurde im Dialog o.k. gegeben */
            {
            fcfg= fopen("z88com.cfg","w");
            if(fcfg == NULL)
              {
              wlog88c(0L,LOG_NOCFG);
              ale88c(AL_NOCFG);
              fclose(fwlo);
              PostQuitMessage(0);
              return 0;
              }

            rewind(fcfg);

            fputs (cename,fcfg);
            fprintf(fcfg,"\n");
            fputs (cecall,fcfg);
            fprintf(fcfg,"\n");
            fputs (cbpref,fcfg);
            fprintf(fcfg,"\n");
            fputs (cbcall,fcfg);
            fprintf(fcfg,"\n");

            iflago= 0;
            fflush(fcfg);
            fclose(fcfg);

            if(LANG == 1) strcpy(cmess,"PDF-Viewer fuer Z88 definiert");
            if(LANG == 2) strcpy(cmess,"PDF Viewer defined for Z88");
            GetClientRect(hStatusBar,&rect);
            DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  
            }
      return 0; 

/*======================================================================
* COMMAND : Wer ist es
*=====================================================================*/
      case IDM_WER:
        if(LANG == 1) strcpy(cmess,
"Z88 Commander Z88COM fuer Windows\n\
Version 15OS\n\
Copyright Univ.-Prof.Dr.-Ing. Frank Rieg,\n\
Universitaet Bayreuth, 2017\n\
Alle Rechte vorbehalten\n");

        if(LANG == 2) strcpy(cmess,
"Z88 Commander Z88COM for Windows\n\
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

        MessageBox(NULL,cmess,"Z88COM", MB_OK | MB_ICONINFORMATION);
      return 0; 

/*======================================================================
* COMMAND : Exit
*=====================================================================*/
      case IDM_XIT:
      case ITC_XIT:
        PostQuitMessage(0);
      return 0; 

/*======================================================================
* COMMAND : Hilfe via Toolbar
*=====================================================================*/
      case ITC_HELP:
        strcpy(callbrow,cbcall);
        strcat(callbrow," ");
        strcat(callbrow,cbpref);
        if(LANG == 1) strcat(callbrow,"z88mang.pdf");
        if(LANG == 2) strcat(callbrow,"z88mane.pdf");
        imess= WinExec(callbrow,SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOACROBAT);
          ale88c(AL_NOACROBAT);
          }
      return 0;

/*----------------------------------------------------------------------
* Menue Compute
*---------------------------------------------------------------------*/
/*======================================================================
* COMMAND : Z88G
*=====================================================================*/
      case ITC_Z88G:
        if(LANG == 1) strcpy(cmess,"COSMOS-Konverter Z88G wurde gestartet");
        if(LANG == 2) strcpy(cmess,"COSMOS Converter Z88G was launched");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  

        imess= WinExec("z88g.exe",SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOZ88G);
          ale88c(AL_NOZ88G);
          }
      return 0; 

/*======================================================================
* COMMAND : Z88H
*=====================================================================*/
      case ITC_Z88H:
        if(LANG == 1) strcpy(cmess,"Cuthill-McKee Programm Z88H gestartet");
        if(LANG == 2) strcpy(cmess,"Cuthill-McKee pro. Z88H was launched");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  

        imess= WinExec("z88h.exe",SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOZ88H);
          ale88c(AL_NOZ88H);
          }
      return 0; 

/*======================================================================
* COMMAND : Z88X
*=====================================================================*/
      case ITC_Z88X:
        if(LANG == 1) strcpy(cmess,"CAD-Konverter Z88X wurde gestartet");
        if(LANG == 2) strcpy(cmess,"CAD Converter Z88X was launched");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  

        imess= WinExec("z88x.exe",SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOZ88X);
          ale88c(AL_NOZ88X);
          }
      return 0; 

/*======================================================================
* COMMAND : Z88N
*=====================================================================*/
      case ITC_Z88N:
        if(LANG == 1) strcpy(cmess,"Netzgenerator Z88N wurde gestartet");
        if(LANG == 2) strcpy(cmess,"Net Generator Z88N was launched");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  

        imess= WinExec("z88n.exe",SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOZ88N);
          ale88c(AL_NOZ88N);
          }
      return 0; 

/*======================================================================
* COMMAND : Z88R
*=====================================================================*/
      case ITC_Z88R:
        if(LANG == 1) strcpy(cmess,"Solver Z88R wurde gestartet");
        if(LANG == 2) strcpy(cmess,"Solver Z88R was launched");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  

        imess= WinExec("z88r.exe",SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOZ88R);
          ale88c(AL_NOZ88R);
          }
      return 0; 

/*----------------------------------------------------------------------
* COMMAND : Menue Editieren
*---------------------------------------------------------------------*/
/*======================================================================
* COMMAND : Editieren Z88.DYN
*=====================================================================*/
      case IDM_Z88DYNEDIT:
      case ITC_DYN:
        if(LANG == 1) strcpy(cmess,"Z88.DYN wurde editiert");
        if(LANG == 2) strcpy(cmess,"Z88.DYN was edited");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  
        strcpy(calledit,cecall);
        strcat(calledit," z88.dyn");
        imess= WinExec(calledit,SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOEDDYN);
          ale88c(AL_NOEDDYN);
          }
      return 0; 

/*======================================================================
* COMMAND : Editieren Z88O.OGL
*=====================================================================*/
      case IDM_EDITOGL:
        if(LANG == 1) strcpy(cmess,"Z88O.OGL wurde editiert");
        if(LANG == 2) strcpy(cmess,"Z88O.OGL was edited");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  
        strcpy(calledit,cecall);
        strcat(calledit," z88o.ogl");
        imess= WinExec(calledit,SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOEDOGL);
          ale88c(AL_NOEDOGL);
          }
      return 0; 

/*======================================================================
* COMMAND : Editieren Z88NI.TXT
*=====================================================================*/
      case IDM_Z88NITXT:
        if(LANG == 1) strcpy(cmess,"Z88NI.TXT wurde editiert");
        if(LANG == 2) strcpy(cmess,"Z88NI.TXT was edited");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  
        strcpy(calledit,cecall);
        strcat(calledit," z88ni.txt");
        imess= WinExec(calledit,SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOEDNI);
          ale88c(AL_NOEDNI);
          }
      return 0; 

/*======================================================================
* COMMAND : Editieren Z88I1.TXT
*=====================================================================*/
      case IDM_Z88I1TXT:
        if(LANG == 1) strcpy(cmess,"Z88I1.TXT wurde editiert");
        if(LANG == 2) strcpy(cmess,"Z88I1.TXT was edited");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  
        strcpy(calledit,cecall);
        strcat(calledit," z88i1.txt");
        imess= WinExec(calledit,SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOEDI1);
          ale88c(AL_NOEDI1);
          }
      return 0; 

/*======================================================================
* COMMAND : Editieren Z88I2.TXT
*=====================================================================*/
      case IDM_Z88I2TXT:
        if(LANG == 1) strcpy(cmess,"Z88I2.TXT wurde editiert");
        if(LANG == 2) strcpy(cmess,"Z88I2.TXT was edited");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  
        strcpy(calledit,cecall);
        strcat(calledit," z88i2.txt");
        imess= WinExec(calledit,SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOEDI2);
          ale88c(AL_NOEDI2);
          }
      return 0; 

/*======================================================================
* COMMAND : Editieren Z88MAN.TXT
*=====================================================================*/
      case IDM_Z88MANTXT:
        if(LANG == 1) strcpy(cmess,"Z88MAN.TXT wurde editiert");
        if(LANG == 2) strcpy(cmess,"Z88MAN.TXT was edited");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  
        strcpy(calledit,cecall);
        strcat(calledit," z88man.txt");
        imess= WinExec(calledit,SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOEDMAN);
          ale88c(AL_NOEDMAN);
          }
      return 0; 

/*======================================================================
* COMMAND : Editieren Z88MAT.TXT
*=====================================================================*/
      case IDM_Z88MATTXT:
        if(LANG == 1) strcpy(cmess,"Z88MAT.TXT wurde editiert");
        if(LANG == 2) strcpy(cmess,"Z88MAT.TXT was edited");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  
        strcpy(calledit,cecall);
        strcat(calledit," z88mat.txt");
        imess= WinExec(calledit,SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOEDMAT);
          ale88c(AL_NOEDMAT);
          }
      return 0; 

/*======================================================================
* COMMAND : Editieren *.TXT (Materialdateien)
*=====================================================================*/
      case IDM_Z88MATCSV:
        if(MatFileOpenDlg(hWnd))
          {
          if(LANG == 1) strcpy(cmess,"eine Materialdatei wurde editiert");
          if(LANG == 2) strcpy(cmess,"a material data file was edited");
          GetClientRect(hStatusBar,&rect);
          DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  
          strcpy(calledit,cecall);
          strcat(calledit," ");
          strcat(calledit,cstrn); /* von MatFileOpenDlg angeliefert */
          imess= WinExec(calledit,SW_SHOW);
          if(imess < 33) 
            {
            wlog88c(0L,LOG_NOEDMAT);
            ale88c(AL_NOEDMAT);
            }
          }
        else
          {
          if(LANG == 1) strcpy(cmess,"keine Materialdatei ausgewaehlt");
          if(LANG == 2) strcpy(cmess,"You did not choose any material data file");
          MessageBox(hWnd,cmess,"Z88COM", MB_OK | MB_ICONINFORMATION);
          }
      return 0; 

/*======================================================================
* COMMAND : Editieren Z88ELP.TXT
*=====================================================================*/
      case IDM_Z88ELPTXT:
        if(LANG == 1) strcpy(cmess,"Z88ELP.TXT wurde editiert");
        if(LANG == 2) strcpy(cmess,"Z88ELP.TXT was edited");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  
        strcpy(calledit,cecall);
        strcat(calledit," z88elp.txt");
        imess= WinExec(calledit,SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOEDELP);
          ale88c(AL_NOEDELP);
          }
      return 0; 

/*======================================================================
* COMMAND : Editieren Z88INT.TXT
*=====================================================================*/
      case IDM_Z88INTTXT:
        if(LANG == 1) strcpy(cmess,"Z88INT.TXT wurde editiert");
        if(LANG == 2) strcpy(cmess,"Z88INT.TXT was edited");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  
        strcpy(calledit,cecall);
        strcat(calledit," z88int.txt");
        imess= WinExec(calledit,SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOEDINT);
          ale88c(AL_NOEDINT);
          }
      return 0; 

/*======================================================================
* COMMAND : Editieren Z88I5.TXT
*=====================================================================*/
      case IDM_Z88I5TXT:
        if(LANG == 1) strcpy(cmess,"Z88I5.TXT wurde editiert");
        if(LANG == 2) strcpy(cmess,"Z88I5.TXT was edited");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  
        strcpy(calledit,cecall);
        strcat(calledit," z88i5.txt");
        imess= WinExec(calledit,SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOEDI5);
          ale88c(AL_NOEDI5);
          }
      return 0; 

/*======================================================================
* COMMAND : Editieren Z88O0.TXT
*=====================================================================*/
      case IDM_Z88O0TXT:
        if(LANG == 1) strcpy(cmess,"Z88O0.TXT wurde editiert");
        if(LANG == 2) strcpy(cmess,"Z88O0.TXT was edited");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  
        strcpy(calledit,cecall);
        strcat(calledit," z88o0.txt");
        imess= WinExec(calledit,SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOEDO0);
          ale88c(AL_NOEDO0);
          }
      return 0; 

/*======================================================================
* COMMAND : Editieren Z88O1.TXT
*=====================================================================*/
      case IDM_Z88O1TXT:
        if(LANG == 1) strcpy(cmess,"Z88O1.TXT wurde editiert");
        if(LANG == 2) strcpy(cmess,"Z88O1.TXT was edited");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  
        strcpy(calledit,cecall);
        strcat(calledit," z88o1.txt");
        imess= WinExec(calledit,SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOEDO1);
          ale88c(AL_NOEDO1);
          }
      return 0; 

/*======================================================================
* COMMAND : Editieren Z88O2.TXT
*=====================================================================*/
      case IDM_Z88O2TXT:
        if(LANG == 1) strcpy(cmess,"Z88O2.TXT wurde editiert");
        if(LANG == 2) strcpy(cmess,"Z88O2.TXT was edited");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  
        strcpy(calledit,cecall);
        strcat(calledit," z88o2.txt");
        imess= WinExec(calledit,SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOEDO2);
          ale88c(AL_NOEDO2);
          }
       return 0; 

/*======================================================================
* COMMAND : Editieren Z88O3.TXT
*=====================================================================*/
      case IDM_Z88O3TXT:
        if(LANG == 1) strcpy(cmess,"Z88O3.TXT wurde editiert");
        if(LANG == 2) strcpy(cmess,"Z88O3.TXT was edited");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  
        strcpy(calledit,cecall);
        strcat(calledit," z88o3.txt");
        imess= WinExec(calledit,SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOEDO3);
          ale88c(AL_NOEDO3);
          }
      return 0; 

/*======================================================================
* COMMAND : Editieren Z88O4.TXT
*=====================================================================*/
      case IDM_Z88O4TXT:
        if(LANG == 1) strcpy(cmess,"Z88O4.TXT wurde editiert");
        if(LANG == 2) strcpy(cmess,"Z88O4.TXT was edited");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  
        strcpy(calledit,cecall);
        strcat(calledit," z88o4.txt");
        imess= WinExec(calledit,SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOEDO4);
          ale88c(AL_NOEDO4);
          }
      return 0; 

/*----------------------------------------------------------------------
* Menue Plotten
*---------------------------------------------------------------------*/
/*======================================================================
* COMMAND : Plotten mit Z88O
*=====================================================================*/
      case ITC_Z88O:
        if(LANG == 1) strcpy(cmess,"Plotprogramm Z88O wurde gestartet");
        if(LANG == 2) strcpy(cmess,"Plot Program Z88O was launched");
        GetClientRect(hStatusBar,&rect);
        DrawStatusText(hDCStatus,&rect,cmess, SBT_POPOUT);  

        imess= WinExec("z88o.exe",SW_SHOW);
        if(imess < 33) 
          {
          wlog88c(0L,LOG_NOZ88O);
          ale88c(AL_NOZ88O);
          }
      return 0; 

      default:
        return DefWindowProc(hWnd, Message, wParam, lParam);
      }

/*----------------------------------------------------------------------
* WM_PAINT
*---------------------------------------------------------------------*/
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);  /* immer ! */
    SetBkMode(hDC, TRANSPARENT);
    EndPaint(hWnd, &ps);          /* immer ! */
  return 0;

/*----------------------------------------------------------------------
* WM_CLOSE
*---------------------------------------------------------------------*/
  case WM_CLOSE:
    PostQuitMessage(0);
  return 0;

/*----------------------------------------------------------------------
* WM_DESTROY
*---------------------------------------------------------------------*/
  case WM_DESTROY:
     PostQuitMessage(0);
  return 0;

/*----------------------------------------------------------------------
* default
*---------------------------------------------------------------------*/
  default:
    return DefWindowProc(hWnd, Message, wParam, lParam);
  } 
}

/*****************************************************************************
* Function EditDiaProc zeigt Dialog- Box fuer Editor an
*****************************************************************************/
BOOL CALLBACK EditDiaProc(HWND hDlg, UINT message,
                          WPARAM wParam, LPARAM lParam)
{
extern int  iflago;
extern char cename[], cecall[];

switch (message)
  {
  case WM_INITDIALOG:
    SetDlgItemText(hDlg,IDDLG_V_TEXT1,cename);
    SetDlgItemText(hDlg,IDDLG_V_TEXT2,cecall);
    return(TRUE);

  case WM_COMMAND:
    switch (LOWORD(wParam))
      {
      case IDOK:
        GetDlgItemText(hDlg,IDDLG_V_TEXT1,cename,128);
        GetDlgItemText(hDlg,IDDLG_V_TEXT2,cecall,128);
        iflago= 1;
        EndDialog(hDlg,0);
        return TRUE;
        
      case IDCANCEL:
        EndDialog(hDlg,0);
        return TRUE;
      }

  }
 
return FALSE;
}

/*****************************************************************************
* Function BrowDiaProc zeigt Dialog-Box fuer Acrobat an
*****************************************************************************/
BOOL CALLBACK BrowDiaProc(HWND hDlg, UINT message,
                          WPARAM wParam, LPARAM lParam)
{
extern int  iflago;
extern char cbpref[], cbcall[];

switch (message)
  {
  case WM_INITDIALOG:
    SetDlgItemText(hDlg,IDDLG_V_TEXT3,cbpref);
    SetDlgItemText(hDlg,IDDLG_V_TEXT4,cbcall);
    return(TRUE);

  case WM_COMMAND:
    switch (LOWORD(wParam))
      {
      case IDOK:
        GetDlgItemText(hDlg,IDDLG_V_TEXT3,cbpref,128);
        GetDlgItemText(hDlg,IDDLG_V_TEXT4,cbcall,128);
        iflago= 1;
        EndDialog(hDlg,0);
        return TRUE;
        
      case IDCANCEL:
        EndDialog(hDlg,0);
        return TRUE;
      }

  }
 
return FALSE;
}

/*****************************************************************************
* Function MatFileInitialize bereitet Fileauswahlbox fuer Materialdateien vor
*****************************************************************************/
void MatFileInitialize(HWND hwnd)
{
extern OPENFILENAME ofn;

extern FR_INT4      LANG;

static TCHAR cfilter1[]= TEXT ("Textdateien (*.TXT)\0*.txt\0")\
                         TEXT ("Alle Dateien (*.*)\0*.*\0\0");  
static TCHAR cfilter2[]= TEXT ("Text Files (*.TXT)\0*.txt\0")\
                         TEXT ("All Files (*.*)\0*.*\0\0");  
   
ofn.lStructSize       = sizeof (OPENFILENAME) ;
ofn.hwndOwner         = hwnd;
ofn.hInstance         = NULL;
if(LANG == 1) 
  ofn.lpstrFilter     = cfilter1;
if(LANG == 2) 
  ofn.lpstrFilter     = cfilter2;
ofn.lpstrCustomFilter = NULL;
ofn.nMaxCustFilter    = 0;
ofn.nFilterIndex      = 0;
ofn.lpstrFile         = NULL; 
ofn.nMaxFile          = MAX_PATH;
ofn.lpstrFileTitle    = NULL;
ofn.nMaxFileTitle     = MAX_PATH;
ofn.lpstrInitialDir   = NULL;
ofn.lpstrTitle        = NULL;
ofn.Flags             = 0; 
ofn.nFileOffset       = 0;
ofn.nFileExtension    = 0;
ofn.lpstrDefExt       = TEXT("txt");
ofn.lCustData         = 0L;
ofn.lpfnHook          = NULL;
ofn.lpTemplateName    = NULL;
}

/*****************************************************************************
* Function MatFileOpenDlg zeigt Fileauswahlbox fuer Materialdateien an
*****************************************************************************/
BOOL MatFileOpenDlg(HWND hwnd)
{
extern OPENFILENAME ofn;
extern char cfname[];
extern char ctname[];
extern char cstrn[];

strcpy(cfname,"1.txt");

ofn.hwndOwner     = hwnd;
ofn.lpstrFile     = cfname;
ofn.lpstrFileTitle= ctname;
ofn.Flags         = OFN_CREATEPROMPT;

if(!GetOpenFileName(&ofn))
  return FALSE;
else
  {
  strcpy(cstrn,ofn.lpstrFile);
  return TRUE;
  }
}


