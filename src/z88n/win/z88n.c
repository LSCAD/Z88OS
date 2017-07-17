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
* V15.0  November 18 2015
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
*  Z88N fuer Windows
*  7.3.2017
***********************************************************************/

/***********************************************************************
* Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88n.h>
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>    /* FILE */
#include <stdlib.h>   /* exit */
#include <string.h>   /* strcpy */
#endif

/***********************************************************************
* Window- Function- Deklarationen
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

/****************************************************************************
* Function-Declarationen
****************************************************************************/
int dyn88n(void);
int ale88n(int);
int rni88(void);
int join88(void);
int mc188n(void);
int mc288n(void);
int mc388n(void);
int mc488n(void);
int mc588n(void);
int mc688n(void);
int mc788n(void);
int mc888n(void);
int lan88n(void);

/****************************************************************************
* globale Variable
****************************************************************************/
/*--------------------------------------------------------------------------
* Files
*-------------------------------------------------------------------------*/
FILE *fdyn,*fwlo,*fni,*fi1,*fcfg;

/*  
**   fdyn= z88.dyn
**   fwlo= z88n.log
**   fni=  z88ni.txt
**   fi1=  z88i1.txt
**   fcfg= z88com.cfg
*/ 

char cdyn[8] = "z88.dyn";
char clgd[9] = "z88n.log";
char cni[10] = "z88ni.txt";
char ci1[10] = "z88i1.txt";
char cfg[11] = "z88com.cfg";
  
/*--------------------------------------------------------------------------
* Pointer
*-------------------------------------------------------------------------*/
FR_DOUBLEAY x;
FR_DOUBLEAY y;
FR_DOUBLEAY z;
FR_DOUBLEAY xss;
FR_DOUBLEAY yss;
FR_DOUBLEAY zss;

FR_INT4AY koima;
FR_INT4AY join; 
FR_INT4AY koiss;
FR_INT4AY ioffss;
FR_INT4AY koffss;
FR_INT4AY jel;
FR_INT4AY iel;
FR_INT4AY kel;

FR_CHARAY cjmode;
FR_CHARAY cimode;
FR_CHARAY ckmode;

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
* Arrays
*-------------------------------------------------------------------------*/
double h[21];

FR_INT4 jhxsta[21]= {0,1,3,3,1,1,3,3,1,2,3,2,1,2,3,2,1,1,3,3,1};
FR_INT4 ihxsta[21]= {0,1,1,3,3,1,1,3,3,1,2,3,2,1,2,3,2,1,1,3,3};
FR_INT4 khxsta[21]= {0,1,1,1,1,3,3,3,3,1,1,1,1,3,3,3,3,2,2,2,2};
FR_INT4 jlqsta[9] = {0,1,2,2,1,1,2,2,1};
FR_INT4 ilqsta[9] = {0,1,1,2,2,1,1,2,2};
FR_INT4 klqsta[9] = {0,1,1,1,1,2,2,2,2};
FR_INT4 jcssta[9] = {0,1,3,3,1,2,3,2,1};
FR_INT4 icssta[9] = {0,1,1,3,3,1,2,3,2};
FR_INT4 jklsta[17]= {0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4};
FR_INT4 iklsta[17]= {0,1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4};
FR_INT4 j21sta[17]= {0,1,3,3,1,2,3,2,1, 1,3,3,1,2,3,2,1};
FR_INT4 i21sta[17]= {0,1,1,3,3,1,2,3,2, 1,1,3,3,1,2,3,2};
FR_INT4 k21sta[17]= {0,1,1,1,1,1,1,1,1, 2,2,2,2,2,2,2,2};

/*--------------------------------------------------------------------------
* Variable
*-------------------------------------------------------------------------*/
FR_INT4 IDYNMEM,LANG=2;
FR_INT4 ndim,nkpss,ness,nfreis,ifrei,itypss,ityp;

int     *pp;

/*--------------------------------------------------------------------------
* vorbelegte Variable
*-------------------------------------------------------------------------*/
double epsx=  0.01;
double epsy=  0.01;
double epsz=  0.01;

FR_INT4 MAXSE=0,MAXESS=0,MAXKSS=0,MAXK=0,MAXE=0,MAXNFG=0,MAXAN=0;

FR_INT4 kflagss= 0,kflag= 0,niflag= 0,idyn= 2;

/***********************************************************************
* WinMain
***********************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   PSTR lpszCmdLine, int nCmdShow)
{
HWND              hWnd;
MSG               msg;
WNDCLASSEX        wndclass;


char              capname[10];
       
/***********************************************************************
* Handles kommen lassen, window oeffnen
***********************************************************************/
comli= (char *)calloc(256,sizeof(char)); 
comli= lpszCmdLine;

strcpy(capname, "Z88N");

wndclass.cbSize        = sizeof(wndclass);
wndclass.style         = CS_HREDRAW | CS_VREDRAW;
wndclass.lpfnWndProc   = WndProc;
wndclass.cbClsExtra    = 0;
wndclass.cbWndExtra    = 0;
wndclass.hInstance     = hInstance;
wndclass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88N));
wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
wndclass.hbrBackground = CreateSolidBrush(RGB(255,255,255));
wndclass.lpszMenuName  = capname;
wndclass.lpszClassName = capname;
wndclass.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88N));

RegisterClassEx(&wndclass);

hWnd = CreateWindow(capname,"Z88 Mapped Mesher Z88N",
                    WS_OVERLAPPEDWINDOW,
                    0, 150,
                    400, 206,
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

extern char       cstore[];
extern char       cbcall[];
extern char       cbpref[];
extern char       cbhelp[];
extern char       cmess[];
extern char       *comli;

PAINTSTRUCT       ps;

static int        ixClient,iyClient;

int               imess,iret;

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
    waitcur= LoadCursor(hInstance,MAKEINTRESOURCE(CUR_Z88N));

/*======================================================================
* Sprache feststellen
*=====================================================================*/
    iret= lan88n();
    if(iret != 0)
      {
      ale88n(iret);
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
    iret= dyn88n();
    if(iret != 0) 
      { 
      ale88n(iret);
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
    if( (strstr(comli,"-run"))!= NULL) 
      PostMessage(hWnd,WM_COMMAND,IDM_GO,0);

  return 0; /* Ende WM_CREATE */

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
"Netzgenerator Z88N fuer Windows\n\
Version 15OS\n\
Copyright Univ.-Prof.Dr.-Ing. Frank Rieg,\n\
Universitaet Bayreuth, 2017\n\
Alle Rechte vorbehalten\n");

          if(LANG == 2) strcpy(cmess,
"Mesh Generator Z88N for Windows\n\
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

        MessageBox(NULL,cmess,"Z88N", MB_OK | MB_ICONINFORMATION);
      return 0;

/*======================================================================
* COMMAND : Exit
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
          wlog88n(0L,LOG_NOACROBAT);
          ale88n(AL_NOACROBAT);
          }
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
  
/*---------------------------------------------------------------------------
* Einlesen Z88NI.TXT
*--------------------------------------------------------------------------*/
        iret= rni88();
        if(iret != 0)
          {
          ale88n(iret);
          PostQuitMessage(0);
          return(0);  
          }           

/*---------------------------------------------------------------------------
* join berechnen
*--------------------------------------------------------------------------*/
        join88();

/*---------------------------------------------------------------------------
* Entscheiden, welche Function mcX88n
*--------------------------------------------------------------------------*/
        if( itypss == 10 && ityp == 10 ) 
          {
          iret= mc188n();
          if(iret != 0)
            {
            ale88n(iret);
            PostQuitMessage(0);
            return(0);  
            }           
          }

        if( itypss == 10 && ityp == 1 ) 
          {
          iret= mc288n();
          if(iret != 0)
            {
            ale88n(iret);
            PostQuitMessage(0);
            return(0);  
            }           
          }

        if( itypss == 1 && ityp == 1 ) 
          {
          iret= mc788n();
          if(iret != 0)
            {
            ale88n(iret);
            PostQuitMessage(0);
            return(0);  
            }           
          }

        if( (itypss == 7 || itypss == 8) && (ityp == 7 || ityp == 8) ) 
          {
          iret= mc388n();
          if(iret != 0)
            {
            ale88n(iret);
            PostQuitMessage(0);
            return(0);  
            }           
          }

        if( (itypss == 11 || itypss == 12) && (ityp == 7 || ityp == 8)) 
          {
          iret= mc488n();
          if(iret != 0)
            {
            ale88n(iret);
            PostQuitMessage(0);
            return(0);  
            }           
          }
       
        if( itypss == 20 && ityp == 19) 
          {
          iret= mc588n();
          if(iret != 0)
            {
            ale88n(iret);
            PostQuitMessage(0);
            return(0);              
            }           
          }

        if( itypss == 21 && ityp == 21 ) 
          {
          iret= mc688n();
          if(iret != 0)
            {
            ale88n(iret);
            PostQuitMessage(0);
            return(0);                      
            }           
          }

        if( itypss == 20 && ityp == 20 ) 
          {
          iret= mc888n();
          if(iret != 0)
            {
            ale88n(iret);
            PostQuitMessage(0);
            return(0);                      
            }           
          }

/*===========================================================================
* Ende Case Go
*==========================================================================*/
        ReleaseDC(hWnd,hDC);  
        SetCursor(LoadCursor(NULL,IDC_ARROW));
        if(LANG == 1) strcpy(cmess,"Netzgenerator Z88N gelaufen");
        if(LANG == 2) strcpy(cmess,"Mesher Z88N done");
        MessageBox(NULL,cmess,"Z88N", MB_OK | MB_ICONINFORMATION);
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
