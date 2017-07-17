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
* Z88 should compile and run under any Windows release.
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
/**********************************************************************
*  Z88X
*  7.3.2017 Rieg
***********************************************************************/

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88x.h>
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>    /* FILE */
#include <stdlib.h>   /* exit */
#include <string.h>   /* strcpy */
#endif

/***********************************************************************
*  Window- Function-Declarationen
***********************************************************************/
LRESULT CALLBACK WndProc            (HWND, UINT, WPARAM, LPARAM);

BOOL    CALLBACK TextSDiaProc       (HWND, UINT, WPARAM, LPARAM);

HWND    InitToolBar   (HWND hParent);

HFONT   EzCreateFont (HDC hdc, char * szFaceName, int iDeciPtHeight,
                    int iDeciPtWidth, int iAttributes, BOOL fLogRes);

/***********************************************************************
*  externe Variable
***********************************************************************/
HDC        hDC;
HINSTANCE  hInstance;
HFONT      hFont;

HWND       hToolBar;
HMENU      hMenuGer,hMenuEng;

HCURSOR    waitcur;

/***********************************************************************
*  Function-Declarationen
***********************************************************************/
int dyn88x(void);
int ale88x(int);
int rea88x(void);
int rdxf88x(void);
int z88tx(void);
int z88fx(void);
int wrim88x(FR_INT4,int);
int wlog88x(FR_INT4,int);
void sub88x(FR_INT4);
int lan88x(void);

/***********************************************************************
*  globale Variable
***********************************************************************/
/*--------------------------------------------------------------------------
* Files
*-------------------------------------------------------------------------*/
FILE *fdyn,*fwlo,*fz88,*fdxf,*fi2,*fi5,*fcfg;

/*  
**   fdyn= z88.dyn
**   fwlo= z88x.log
**   fz88= z88ni.txt oder z88i1.txt
**   fdxf= z88x.dxf oder z88x.dxf
**   fi2 = z88i2.txt
**   fi5 = z88i5.txt
**   fcfg= z88com.cfg
*/ 

char cdyn[8] = "z88.dyn";
char clgd[9] = "z88x.log";
char ci1[10] = "z88i1.txt";
char ci2[10] = "z88i2.txt";
char ci5[10] = "z88i5.txt";
char cni[10] = "z88ni.txt";
char cxx[10] = "z88x.dxf";
char cfg[11] = "z88com.cfg";
  
/*--------------------------------------------------------------------------
* Pointer
*-------------------------------------------------------------------------*/
FR_DOUBLEAY x;
FR_DOUBLEAY y;
FR_DOUBLEAY z;
FR_DOUBLEAY wert;
FR_DOUBLEAY pres;
FR_DOUBLEAY tr1;
FR_DOUBLEAY tr2;

FR_INT4AY koi;
FR_INT4AY ifrei; 
FR_INT4AY ioffs;
FR_INT4AY koffs;
FR_INT4AY ityp;
FR_INT4AY itypfe;
FR_INT4AY jel;
FR_INT4AY iel;
FR_INT4AY kel;
FR_INT4AY nkn;
FR_INT4AY ifg;
FR_INT4AY irflag;
FR_INT4AY noi;
FR_INT4AY noffs;
FR_INT4AY nep;

FR_CHARAY cjmode;
FR_CHARAY cimode;
FR_CHARAY ckmode;

/*--------------------------------------------------------------------------
* Char-Arrays
*-------------------------------------------------------------------------*/
char cstore[256];
char cbcall[128];
char cbpref[128];
char callbrow[512];
char cbhelp[512];
char cmess [512];
char cbytes[128];
char *comli;

/*--------------------------------------------------------------------------
* Variable
*-------------------------------------------------------------------------*/
double epsx,epsy,epsz;

FR_INT4 intore,nel,ktyp;
FR_INT4 IDYNMEM,ICFLAG,LANG=2;
FR_INT4 ndim,nkp,ne,nfg,nkoi,kflagss,kflag,iqflag,niflag;
FR_INT4 nrb,ianz,ifrej;

int     *pp;

char    cflag[10];

/*--------------------------------------------------------------------------
* vorbelegte Variable
*-------------------------------------------------------------------------*/
double texts= 1.0;                     /* Startwert Textsize */

FR_INT4 MAXNFG=0,MAXK=0,MAXE=0,MAXKOI=0,MAXPR=0,npr=0;
FR_INT4 ITSFLAG= 0;                    /* berechneten Textsize nehmen */

int ifmode= IDM_IAFX;

/***********************************************************************
* WinMain
***********************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   PSTR lpszCmdLine, int nCmdShow)
{
HWND       hWnd;
MSG        msg;
WNDCLASSEX wndclass;

char       capname[10];
       
/***********************************************************************
* Handles kommen lassen, window oeffnen
***********************************************************************/
comli= (char *)calloc(256,sizeof(char)); 
comli= lpszCmdLine;

strcpy(capname, "Z88X");

wndclass.cbSize        = sizeof(wndclass);
wndclass.style         = CS_HREDRAW | CS_VREDRAW;
wndclass.lpfnWndProc   = WndProc;
wndclass.cbClsExtra    = 0;
wndclass.cbWndExtra    = 0;
wndclass.hInstance     = hInstance;
wndclass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88X));
wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
wndclass.hbrBackground = CreateSolidBrush(RGB(255,255,255));
wndclass.lpszMenuName  = capname;
wndclass.lpszClassName = capname;
wndclass.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88X));

RegisterClassEx(&wndclass);

hWnd = CreateWindow(capname,"Z88 DXF Converter Z88X",
                    WS_OVERLAPPEDWINDOW,
                    0,150,
                    420,426,
                    NULL, NULL, hInstance, NULL);

InitCommonControls();

ShowWindow(hWnd, nCmdShow);
UpdateWindow(hWnd);

while(GetMessage(&msg, NULL, 0, 0))
  {
  TranslateMessage(&msg);
  DispatchMessage(&msg);
  }

DeleteObject(hFont);

return msg.wParam;
}

/***********************************************************************
* Main Window Procedure
***********************************************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT Message,
                         WPARAM wParam, LPARAM lParam)
{
extern HDC        hDC;
extern HINSTANCE  hInstance;
extern HFONT      hFont;

extern HWND       hToolBar;
extern HMENU      hMenuGer,hMenuEng;

extern HCURSOR    waitcur;

extern FR_INT4    ICFLAG,LANG,ITSFLAG;
extern int        ifmode;

extern char       cstore[];
extern char       cbcall[];
extern char       cbpref[];
extern char       callbrow[];
extern char       cbhelp[];
extern char       cmess[];
extern char       *comli;

HMENU             hMenu;

PAINTSTRUCT       ps;

static int        ixClient,iyClient;

int               imess,iret,ipara1=0;


size_t            laenge;

/*----------------------------------------------------------------------
* Los gehts
*---------------------------------------------------------------------*/
switch (Message)
  {
/*----------------------------------------------------------------------
* case WM_CREATE
*---------------------------------------------------------------------*/
  case WM_CREATE:
    if(ifmode == IDM_IAFX) ICFLAG = 5;

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
    waitcur= LoadCursor(hInstance,MAKEINTRESOURCE(CUR_Z88X));

/*======================================================================
* Sprache feststellen
*=====================================================================*/
    iret= lan88x();
    if(iret != 0)
      {
      ale88x(iret);
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
    iret= dyn88x();
    if(iret != 0) 
      { 
      ale88x(iret);
      PostQuitMessage(0);
      return 0;
      }           

/*======================================================================
* Toolbar
*=====================================================================*/
    hToolBar= InitToolBar(hWnd);

/*======================================================================
* Commandline auswerten
*=====================================================================*/
    if( (strstr(comli,"-i1tx"))!= NULL) 
      {
      ipara1= 1;
      ICFLAG= 1;
      }
    if( (strstr(comli,"-iatx"))!= NULL) 
      {
      ipara1= 1;
      ICFLAG= 2;
      }
    if( (strstr(comli,"-nitx"))!= NULL) 
      {
      ipara1= 1;
      ICFLAG= 3;
      }
    if( (strstr(comli,"-i1fx"))!= NULL) 
      {
      ipara1= 1;
      ICFLAG= 4;
      }
    if( (strstr(comli,"-iafx"))!= NULL) 
      {
      ipara1= 1;
      ICFLAG= 5;
      }
    if( (strstr(comli,"-nifx"))!= NULL) 
      {
      ipara1= 1;
      ICFLAG= 6;
      }


    if(ipara1 == 1) 
      PostMessage(hWnd,WM_COMMAND,IDM_GO,0);

  return 0; /* Ende WM_CREATE */

/*----------------------------------------------------------------------
* case WM_INITMENU
*---------------------------------------------------------------------*/
  case WM_INITMENU:
    hMenu= GetMenu(hWnd); /* muss rein */

    CheckMenuItem(hMenu,IDM_I1TX, MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_IATX, MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_NITX, MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_I1FX, MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_IAFX, MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_NIFX, MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,ifmode,     MF_CHECKED   | MF_BYCOMMAND);   
  return 0;
  
/*----------------------------------------------------------------------
* case WM_MOVE
*---------------------------------------------------------------------*/
  case WM_MOVE:
  return 0;

/*----------------------------------------------------------------------
* case WM_SIZE
*---------------------------------------------------------------------*/
  case WM_SIZE:
    iyClient= HIWORD(lParam);
    ixClient= LOWORD(lParam);
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
        case ITC_GO:
          if(LANG == 1) pReply= "Berechne";
          if(LANG == 2) pReply= "Run";
        break;

        case ITC_HELP:
          if(LANG == 1) pReply= "OnLine-Hilfe";
          if(LANG == 2) pReply= "OnLine Help";
        break;

        case ITC_I1TX:
          if(LANG == 1) pReply= "Konvertiere Z88I1.TXT in Z88X.DXF";
          if(LANG == 2) pReply= "Convert Z88I1.TXT into Z88X.DXF";
        break;

        case ITC_IATX:
          if(LANG == 1) pReply= "Konvertiere Z88I*.TXT in Z88X.DXF";
          if(LANG == 2) pReply= "Convert Z88I*.TXT into Z88X.DXF";
        break;

        case ITC_NITX:
          if(LANG == 1) pReply= "Konvertiere Z88NI.TXT in Z88X.DXF";
          if(LANG == 2) pReply= "Convert Z88NI.TXT into Z88X.DXF";
        break;

        case ITC_I1FX:
          if(LANG == 1) pReply= "Konvertiere Z88X.DXF in Z88I1.TXT";
          if(LANG == 2) pReply= "Convert Z88X.DXF into Z88I1.TXT";
        break;

        case ITC_IAFX:
          if(LANG == 1) pReply= "Konvertiere Z88X.DXF in Z88I*.TXT";
          if(LANG == 2) pReply= "Convert Z88X.DXF into Z88I*.TXT";
        break;

        case ITC_NIFX:
          if(LANG == 1) pReply= "Konvertiere Z88X.DXF in Z88NI.TXT";
          if(LANG == 2) pReply= "Convert Z88X.DXF into Z88NI.TXT";
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
* case WM_COMMAND
*---------------------------------------------------------------------*/
  case WM_COMMAND:
    switch (LOWORD(wParam))
      {

/*======================================================================
* COMMAND : Wer ist es
*=====================================================================*/
      case IDM_WER:
        if(LANG == 1) strcpy(cmess,
"DXF-Konverter Z88X fuer Windows\n\
Version 15OS\n\
Copyright Univ.-Prof.Dr.-Ing. Frank Rieg,\n\
Universitaet Bayreuth, 2017\n\
Alle Rechte vorbehalten\n");

          if(LANG == 2) strcpy(cmess,
"DXF Converter Z88X for Windows\n\
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

        MessageBox(NULL,cmess,"Z88X", MB_OK | MB_ICONINFORMATION);
      return 0;

/*======================================================================
* COMMAND : Textsize
*=====================================================================*/
      case IDM_TEXTSIZE:
        if(LANG == 1) DialogBox(hInstance,"Dlg_TextS88G",hWnd,TextSDiaProc);
        if(LANG == 2) DialogBox(hInstance,"Dlg_TextS88E",hWnd,TextSDiaProc);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
* COMMAND : Xit
*=====================================================================*/
      case IDM_XIT:
      case ITC_XIT:
        PostQuitMessage(0);
      return 0; 

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
          MessageBox(NULL,cmess,"Z88X", MB_OK | MB_ICONHAND);
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
          wlog88x(0L,LOG_NOACROBAT);
          ale88x(AL_NOACROBAT);
          }
      return 0;

/*======================================================================
* COMMAND : Mode aus Menue
*=====================================================================*/
      case IDM_I1TX:
      case IDM_IATX:
      case IDM_NITX:
      case IDM_I1FX:
      case IDM_IAFX:
      case IDM_NIFX:
        hMenu= GetMenu(hWnd);
        CheckMenuItem(hMenu,ifmode,MF_UNCHECKED | MF_BYCOMMAND);
        ifmode= (int)wParam;
        CheckMenuItem(hMenu,ifmode,MF_CHECKED | MF_BYCOMMAND);   

        if     (ifmode == IDM_I1TX) 
          {
          ICFLAG = 1;
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_I1TX,(LPARAM) MAKELONG(TRUE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_IATX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_NITX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_I1FX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_IAFX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_NIFX,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if(ifmode == IDM_IATX) 
          {
          ICFLAG = 2;
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_I1TX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_IATX,(LPARAM) MAKELONG(TRUE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_NITX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_I1FX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_IAFX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_NIFX,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if(ifmode == IDM_NITX) 
          {
          ICFLAG = 3;
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_I1TX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_IATX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_NITX,(LPARAM) MAKELONG(TRUE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_I1FX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_IAFX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_NIFX,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if(ifmode == IDM_I1FX) 
          {
          ICFLAG = 4;
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_I1TX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_IATX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_NITX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_I1FX,(LPARAM) MAKELONG(TRUE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_IAFX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_NIFX,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if(ifmode == IDM_IAFX) 
          {
          ICFLAG = 5;
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_I1TX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_IATX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_NITX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_I1FX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_IAFX,(LPARAM) MAKELONG(TRUE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_NIFX,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if(ifmode == IDM_NIFX) 
          {
          ICFLAG = 6;
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_I1TX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_IATX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_NITX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_I1FX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_IAFX,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_NIFX,(LPARAM) MAKELONG(TRUE,0) );
          }

        else MessageBox(NULL,"No Mode !","Z88X", MB_OK | MB_ICONHAND);

        InvalidateRect(hWnd,NULL,TRUE);
      return 0; 

/*======================================================================
* COMMAND : Mode aus Toolbar
*=====================================================================*/
      case ITC_I1TX:
        ICFLAG = 1;
        ifmode = IDM_I1TX; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_IATX:
        ICFLAG = 2;
        ifmode = IDM_IATX; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_NITX:
        ICFLAG = 3;
        ifmode = IDM_NITX; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_I1FX:
        ICFLAG = 4;
        ifmode = IDM_I1FX; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_IAFX:
        ICFLAG = 5;
        ifmode = IDM_IAFX; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_NIFX:
        ICFLAG = 6;
        ifmode = IDM_NIFX; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
* COMMAND : Go
*=====================================================================*/
      case IDM_GO:
      case ITC_GO:
        SetCursor(waitcur);
        ShowCursor(TRUE);

        hDC= GetDC(hWnd);
        hFont= EzCreateFont(hDC,"Times New Roman",120,0,2,TRUE);
        SelectObject(hDC,hFont);
        SetBkColor(hDC,RGB(255,255,255));

        laenge= strlen(comli);
        TextOut(hDC,10,30,comli,laenge);

        if     (ICFLAG == 1) wlog88x(1L,LOG_CFLAGI1TX);
        else if(ICFLAG == 2) wlog88x(2L,LOG_CFLAGIATX);
        else if(ICFLAG == 3) wlog88x(3L,LOG_CFLAGNITX);
        else if(ICFLAG == 4) wlog88x(4L,LOG_CFLAGI1FX);
        else if(ICFLAG == 5) wlog88x(5L,LOG_CFLAGIAFX);
        else if(ICFLAG == 6) wlog88x(6L,LOG_CFLAGNIFX);
         
/*---------------------------------------------------------------------------
* Entscheiden, welcher Berechnungsgang
*--------------------------------------------------------------------------*/
        if(ICFLAG == 1 || ICFLAG == 2)
          {                            /* Start -I1TX oder -IATX */ 

/*---------------------------------------------------------------------------
* Berechnungsgang 1: von Z88I1.TXT nach Z88X.DXF
* Berechnungsgang 2: von Z88I1.TXT, Z88I2.TXT, Z88I3.TXT nach Z88X.DXF
*--------------------------------------------------------------------------*/
/*===========================================================================
* Einlesen Z88I1.TXT
*==========================================================================*/
          iret= rea88x();
          if(iret != 0)
            {
            ale88x(iret);
            PostQuitMessage(0);
            return(0);
            }           
  
/*===========================================================================
* Rechnen
*==========================================================================*/
          iret= z88tx();
          if(iret != 0)
            {
            ale88x(iret);
            PostQuitMessage(0);
            return(0);
            }           

          }                            /* Ende -I1TX und -IATX */
/*---------------------------------------------------------------------------
* Ende Berechnungsgang 1 und 2
*--------------------------------------------------------------------------*/

        if(ICFLAG == 3)
          {                            /* Start -NITX */ 

/*---------------------------------------------------------------------------
* Berechnungsgang 3: von Z88NI.TXT nach Z88X.DXF
*--------------------------------------------------------------------------*/
/*===========================================================================
* Einlesen Z88NI.TXT
*==========================================================================*/
          iret= rea88x();
          if(iret != 0)
            {
            ale88x(iret);
            PostQuitMessage(0);
            return(0);
            }           
  
/*===========================================================================
* Rechnen
*==========================================================================*/
          iret= z88tx();
          if(iret != 0)
            {
            ale88x(iret);
            PostQuitMessage(0);
            return(0);
            }           

          }                            /* Ende -NITX */
/*---------------------------------------------------------------------------
* Ende Berechnungsgang 3
*--------------------------------------------------------------------------*/

        if(ICFLAG == 4 || ICFLAG == 5)
          {                            /* Start -I1FX oder -IAFX */ 

/*---------------------------------------------------------------------------
* Berechnungsgang 4: von Z88X.DXF nach Z88I1.TXT
* Berechnungsgang 5: von Z88X.DXF nach Z88I1.TXT, Z88I2.TXT, Z88I3.TXT
*--------------------------------------------------------------------------*/
/*===========================================================================
* Rechnen
*==========================================================================*/
          iret= z88fx();
          if(iret != 0)
            {
            ale88x(iret);
            PostQuitMessage(0);
            return(0);
            }           

          }                            /* Ende -I1FX oder -IAFX */
/*---------------------------------------------------------------------------
* Ende Berechnungsgang 4 und 5
*--------------------------------------------------------------------------*/

        if(ICFLAG == 6)
          {                            /* Start -NIFX */ 

/*---------------------------------------------------------------------------
* Berechnungsgang 6: von Z88X.DXF nach Z88NI.TXT
*--------------------------------------------------------------------------*/
/*===========================================================================
* Rechnen
*==========================================================================*/
          iret= z88fx();
          if(iret != 0)
            {
            ale88x(iret);
            PostQuitMessage(0);
            return(0);
            }           

          }                            /* Ende -NIFX */
/*---------------------------------------------------------------------------
* Ende Berechnungsgang 6
* und Ende Case Go
*--------------------------------------------------------------------------*/
        ReleaseDC(hWnd,hDC);  
        SetCursor(LoadCursor(NULL,IDC_ARROW));
        if(LANG == 1) strcpy(cmess,"DXF-Converter Z88X gelaufen");
        if(LANG == 2) strcpy(cmess,"DXF Coverter Z88X done");
        MessageBox(NULL,cmess,"Z88X", MB_OK | MB_ICONINFORMATION);
        PostQuitMessage(0);
      return 0;                           /* end case GO */

      default:
        return DefWindowProc(hWnd, Message, wParam, lParam);
      }                                /* end switch command */ 

/*----------------------------------------------------------------------
* case WM_PAINT
*---------------------------------------------------------------------*/
  case WM_PAINT:
    memset(&ps, 0x00, sizeof(PAINTSTRUCT));
    hDC = BeginPaint(hWnd, &ps);

    SetBkMode(hDC, TRANSPARENT);

    EndPaint(hWnd, &ps);
  return 0;

/*----------------------------------------------------------------------
* case WM_CLOSE
*---------------------------------------------------------------------*/
  case WM_CLOSE:
    PostQuitMessage(0);
  return 0;

/*----------------------------------------------------------------------
* case WM_DESTROY
*---------------------------------------------------------------------*/
  case WM_DESTROY:
    PostQuitMessage(0);
  return 0;

  default:
    return DefWindowProc(hWnd, Message, wParam, lParam);
  } 
}

/*****************************************************************************
* Function TextSDiaProc zeigt Dialog- Box fuer Textsize an
*****************************************************************************/
BOOL CALLBACK TextSDiaProc(HWND hDlg, UINT message,
                           WPARAM wParam, LPARAM lParam)
{
extern double texts;

int  idigit= 20;

char ctexts[31];

/*---------------------------------------------------------------------------
* beim allerersten Start geht texts mit 1. rein
*--------------------------------------------------------------------------*/
gcvt(texts,idigit,ctexts); 

switch (message)
  {
  case WM_INITDIALOG:
    SetDlgItemText(hDlg,IDDLG_V_TEXT,ctexts);
  return(TRUE);

  case WM_COMMAND:
    switch (LOWORD(wParam))
      {
      case IDOK:
        GetDlgItemText(hDlg,IDDLG_V_TEXT,ctexts,30);
        texts= (double) atof(ctexts);
        ITSFLAG= 1;
        EndDialog(hDlg,0);
      return TRUE;
        
      case IDCANCEL:
        EndDialog(hDlg,0);
      return TRUE;
      }
  }
return FALSE;
}

