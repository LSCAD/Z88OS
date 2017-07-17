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
*  Z88G fuer Windows
*  wandelt COSMOS-Files oder NASTRAN-Files 
*  aus Pro/MESH (PTC, Pro/ENGINEER) 
*  in Z88I*.TXT- Files fuer die Z88- Elementtypen:
* - Scheiben  Nr. 7 ( 8 Knoten) und Nr.14 (6 Knoten)
* - Tetraeder Nr.16 (10 Knoten) und Nr.17 (4 Knoten)
* - Platten   Nr.20 ( 8 Knoten) und Nr.18 (6 Knoten)
* - Torus     Nr. 8 ( 8 Knoten) und Nr.15 (6 Knoten)
* - Schalen   Nr.23 ( 8 Knoten) und Nr.24 (6 Knoten)
*  7.3.2017 Rieg
***********************************************************************/
/***********************************************************************
* Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88g.h>
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>    /* FILE */
#include <stdlib.h>   /* exit */
#include <string.h>   /* strcpy */
#endif

/***********************************************************************
*  Window- Function-Declarationen
***********************************************************************/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND InitToolBar   (HWND hParent);

HFONT EzCreateFont (HDC hdc, char * szFaceName, int iDeciPtHeight,
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
*  Functions
***********************************************************************/
int cosm88(void);
int nast88(void);
int dnas88(void);
int wrim88g(FR_INT4,int);
int wlog88g(FR_INT4,int);
int ale88g(int);
int lan88g(void);

/****************************************************************************
*  globale Variable
****************************************************************************/
/*--------------------------------------------------------------------------
* Files
*-------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------
* Files
*-------------------------------------------------------------------------*/
FILE *fdyn,*fwlo,*fpro,*fin,*fi1,*fi2,*fi5,*fcfg;

/*  
**   fdyn= z88.dyn
**   fwlo= z88g.log
**   fpro= z88g.cos oder z88g.nas
**   fin = z88g.in
**   fi1 = z88i1.txt
**   fi2 = z88i2.txt
**   fi5 = z88i5.txt
**   fcfg= z88com.cfg
*/ 

char cdyn[8] = "z88.dyn";
char clgd[9] = "z88g.log";
char ccco[9] = "z88g.cos";
char cnas[9] = "z88g.nas";
char cin[8]  = "z88g.in";
char ci1[10] = "z88i1.txt";
char ci2[10] = "z88i2.txt";
char ci5[10] = "z88i5.txt";
char cfg[11] = "z88com.cfg";

/*--------------------------------------------------------------------------
* Char-Arrays
*-------------------------------------------------------------------------*/
char cstore[256];
char cbcall[128];
char cbpref[128];
char cbhelp[512];
char callbrow[512];
char cmess[512];
char cbytes[128];
char *comli;

/*--------------------------------------------------------------------------
* Variable
*-------------------------------------------------------------------------*/
FR_INT4   IFFLAG= 0,ICFLAG= 0,LANG=2;

int       ifmode= IDM_VOLU;
int       iffile= IDM_NAST;

int       *pp;

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
* Handles kommen lassen, Window oeffnen
***********************************************************************/
comli= (char *)calloc(256,sizeof(char)); 
comli= lpszCmdLine;

strcpy(capname,"Z88G");

wndclass.cbSize        = sizeof(wndclass);
wndclass.style         = CS_HREDRAW | CS_VREDRAW;
wndclass.lpfnWndProc   = WndProc;
wndclass.cbClsExtra    = 0;
wndclass.cbWndExtra    = 0;
wndclass.hInstance     = hInstance;
wndclass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88G));
wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
wndclass.hbrBackground = CreateSolidBrush(RGB(255,255,255));
wndclass.lpszMenuName  = capname;
wndclass.lpszClassName = capname;
wndclass.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88G));

RegisterClassEx(&wndclass);

hWnd = CreateWindow(capname,"Z88 3D-Converter Z88G",
                    WS_OVERLAPPEDWINDOW,
                    0, 150,
                    540, 346,
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

extern FR_INT4    LANG;

extern int        ifmode;
extern int        iffile;

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

int               imess,iret,ipara1=0,ipara2=0;

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
    waitcur= LoadCursor(hInstance,MAKEINTRESOURCE(CUR_Z88G));

/*======================================================================
* Sprache feststellen
*=====================================================================*/
    iret= lan88g();
    if(iret != 0)
      {
      ale88g(iret);
      PostQuitMessage(0);
      return(1);
      }

    hMenuGer= LoadMenu(hInstance,"GERMAN");
    hMenuEng= LoadMenu(hInstance,"ENGLISH");

    if(LANG == 1) SetMenu(hWnd,hMenuGer);
    if(LANG == 2) SetMenu(hWnd,hMenuEng);

/*===========================================================================
* IFFLAG setzen
*==========================================================================*/
    if(iffile == IDM_NAST) IFFLAG = 2;

/*===========================================================================
* ICFLAG setzen
*==========================================================================*/
    if(ifmode == IDM_VOLU) ICFLAG = 1;

/*======================================================================
* Toolbar
*=====================================================================*/
    hToolBar= InitToolBar(hWnd);

/*======================================================================
* Commandline auswerten
*=====================================================================*/
    if( (strstr(comli,"-nastran"))!= NULL) 
      {
      ipara1= 1;
      IFFLAG= 2;
      }
    if( (strstr(comli,"-cosmos"))!= NULL) 
      {
      ipara1= 1;
      IFFLAG= 1;
      }

    if( (strstr(comli,"-volume"))!= NULL) 
      {
      ipara2= 1;
      ICFLAG= 1;
      }
    if( (strstr(comli,"-pstress"))!= NULL) 
      {
      ipara2= 1;
      ICFLAG= 2;
      }
    if( (strstr(comli,"-plate"))!= NULL) 
      {
      ipara2= 1;
      ICFLAG= 3;
      }
    if( (strstr(comli,"-torus"))!= NULL) 
      {
      ipara2= 1;
      ICFLAG= 4;
      }
    if( (strstr(comli,"-shell"))!= NULL) 
      {
      ipara2= 1;
      ICFLAG= 6;
      }

    if(ipara1 == 1 && ipara2 == 1) 
      PostMessage(hWnd,WM_COMMAND,IDM_GO,0);

  return 0; /* Ende WM_CREATE */

/*----------------------------------------------------------------------
* case WM_INITMENU
*---------------------------------------------------------------------*/
  case WM_INITMENU:
    hMenu= GetMenu(hWnd); /* muss rein */

    CheckMenuItem(hMenu,IDM_NAST, MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_COSM, MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,iffile,   MF_CHECKED   | MF_BYCOMMAND);   

    CheckMenuItem(hMenu,IDM_VOLU, MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_SHEI, MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_PLAT, MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_TORU, MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,ifmode,   MF_CHECKED   | MF_BYCOMMAND);   
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

        case ITC_NAST:
          if(LANG == 1) pReply= "Konvertiere NASTRAN-Datei Z88G.NAS";
          if(LANG == 2) pReply= "Convert the NASTRAN file Z88G.NAS";
        break;

        case ITC_COSM:
          if(LANG == 1) pReply= "Konvertiere COSMOS-Datei Z88G.COS";
          if(LANG == 2) pReply= "Convert the COSMOS file Z88G.COS";
        break;

        case ITC_VOLU:
          if(LANG == 1) pReply= 
          "Konvertiere in Volumenelemente, bei NASTRAN auch mit Flächenlast";
          if(LANG == 2) pReply= 
          "Convert into Volumes, NASTRAN files support surface loads";
        break;

        case ITC_SHEI:
          if(LANG == 1) pReply= "Konvertiere in Scheibenelemente";
          if(LANG == 2) pReply= "Convert into Plane Stress Elements";
        break;

        case ITC_PLAT:
          if(LANG == 1) pReply= "Konvertiere in Plattenelemente";
          if(LANG == 2) pReply= "Convert into Plate Elements";
        break;

        case ITC_TORU:
          if(LANG == 1) pReply= "Konvertiere in Toruselemente";
          if(LANG == 2) pReply= "Convert into Torus Elements";
        break;

        case ITC_SHEL:
          if(LANG == 1) pReply= "Konvertiere in Schalenelemente";
          if(LANG == 2) pReply= "Convert into Shell Elements";
        break;


        case ITC_HELP:
          if(LANG == 1) pReply= "OnLine-Hilfe fuer 3D-Konverter";
          if(LANG == 2) pReply= "OnLine Help for 3D converter";
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
"3D-Konverter Z88G fuer Windows\n\
Version 15OS\n\
Copyright Univ.-Prof.Dr.-Ing. Frank Rieg,\n\
Universitaet Bayreuth, 2017\n\
Alle Rechte vorbehalten\n");

          if(LANG == 2) strcpy(cmess,
"3D Converter Z88G for Windows\n\
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

        MessageBox(NULL,cmess,"Z88G", MB_OK | MB_ICONINFORMATION);
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
          wlog88g(0L,LOG_NOACROBAT);
          ale88g(AL_NOACROBAT);
          }
      return 0;

/*======================================================================
* COMMAND : Filetyp aus Menue
*=====================================================================*/
      case IDM_NAST:
      case IDM_COSM:
        hMenu= GetMenu(hWnd);
        CheckMenuItem(hMenu,iffile,MF_UNCHECKED | MF_BYCOMMAND);
        iffile= LOWORD(wParam);
        CheckMenuItem(hMenu,iffile,MF_CHECKED | MF_BYCOMMAND);   

        if     (iffile == IDM_COSM) 
          {
          IFFLAG = 1;
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_COSM,(LPARAM) MAKELONG(TRUE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_NAST,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if(iffile == IDM_NAST)
          {
          IFFLAG = 2;
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_COSM,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_NAST,(LPARAM) MAKELONG(TRUE,0) );
          }

        else MessageBox(NULL,"No File !","Z88G", MB_OK | MB_ICONHAND);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0; 

/*======================================================================
* COMMAND : Filetyp aus Toolbar
*=====================================================================*/
      case ITC_COSM:
        IFFLAG = 1;
        iffile = IDM_COSM; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_NAST:
        IFFLAG = 2;
        iffile = IDM_NAST; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*======================================================================
* COMMAND : Mode aus Menue
*=====================================================================*/
      case IDM_VOLU:
      case IDM_SHEI:
      case IDM_PLAT:
      case IDM_TORU:
      case IDM_SHEL:
        hMenu= GetMenu(hWnd);
        CheckMenuItem(hMenu,ifmode,MF_UNCHECKED | MF_BYCOMMAND);
        ifmode= LOWORD(wParam);
        CheckMenuItem(hMenu,ifmode,MF_CHECKED | MF_BYCOMMAND);   

        if     (ifmode == IDM_VOLU) 
          {
          ICFLAG = 1;
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_VOLU,(LPARAM) MAKELONG(TRUE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_SHEI,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_PLAT,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_TORU,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_SHEL,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if(ifmode == IDM_SHEI)
          {
          ICFLAG = 2;
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_VOLU,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_SHEI,(LPARAM) MAKELONG(TRUE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_PLAT,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_TORU,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_SHEL,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if(ifmode == IDM_PLAT)
          {
          ICFLAG = 3;
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_VOLU,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_SHEI,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_PLAT,(LPARAM) MAKELONG(TRUE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_TORU,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_SHEL,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if(ifmode == IDM_TORU)
          {
          ICFLAG = 4;
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_VOLU,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_SHEI,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_PLAT,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_TORU,(LPARAM) MAKELONG(TRUE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_SHEL,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if(ifmode == IDM_SHEL)
          {
          ICFLAG = 6;
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_VOLU,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_SHEI,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_PLAT,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_TORU,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_SHEL,(LPARAM) MAKELONG(TRUE,0) );
          }

        else MessageBox(NULL,"No Mode !","Z88G", MB_OK | MB_ICONHAND);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0; 

/*======================================================================
* COMMAND : Mode aus Toolbar
*=====================================================================*/
      case ITC_VOLU:
        ICFLAG = 1;
        ifmode = IDM_VOLU; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_SHEI:
        ICFLAG = 2;
        ifmode = IDM_SHEI; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_PLAT:
        ICFLAG = 3;
        ifmode = IDM_PLAT; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_TORU:
        ICFLAG = 4;
        ifmode = IDM_TORU; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_SHEL:
        ICFLAG = 6;
        ifmode = IDM_SHEL; 
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

/*----------------------------------------------------------------------
* Umsetzen
*---------------------------------------------------------------------*/
        if(IFFLAG == 1)   iret= cosm88();
        if(IFFLAG == 2) 
          {
          if(ICFLAG == 1) iret= dnas88();
          else            iret= nast88();
          }
        if(iret != 0)
          {
          ale88g(iret);
          PostQuitMessage(0);
          return(1);

          }

        wlog88g(0L,LOG_Z88DONE);
        wrim88g(0L,TX_Z88DONE);

/*----------------------------------------------------------------------
* Ende Case Go
*---------------------------------------------------------------------*/
        ReleaseDC(hWnd,hDC);  
        SetCursor(LoadCursor(NULL,IDC_ARROW));
        if(LANG == 1) strcpy(cmess,"3D Konverter Z88G gelaufen");
        if(LANG == 2) strcpy(cmess,"3D converter Z88G done");
        MessageBox(NULL,cmess,"Z88G", MB_OK | MB_ICONINFORMATION);
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

