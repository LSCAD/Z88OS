/****************************************************************************
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
* V15.0 November 18, 2015
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
****************************************************************************/ 
/****************************************************************************
*  Programm z88r.c - der lineare Universal-Solver - OpenSource-Version
*  7.3.2017 Rieg
****************************************************************************/
/****************************************************************************
* Windows
****************************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>    /* FILE */
#include <stdlib.h>   /* exit */
#include <string.h>   /* strcpy */
#endif

/****************************************************************************
*  Window- Function-Declarationen
****************************************************************************/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

HWND InitToolBar   (HWND hParent);

HFONT EzCreateFont (HDC hdc, char * szFaceName, int iDeciPtHeight,
                    int iDeciPtWidth, int iAttributes, BOOL fLogRes);

/****************************************************************************
*  externe Windows-Variable
****************************************************************************/
HDC        hDC;
HINSTANCE  hInstance;
HFONT      hFont;
HWND       hToolBar;
HMENU      hMenuGer,hMenuEng;
HCURSOR    waitcur;

/****************************************************************************
* Formate
****************************************************************************/
#define NL "\n"

#ifdef FR_XINT
#define PD "%d"
#define PDB "%d "
#define B5D " %5d"
#define B1D " %1d"
#define P5DB "%5d "
#define P7DB "%7d  "
#endif

#ifdef FR_XLONG
#define PD "%ld"
#define PDB "%ld "
#define B5D " %5ld"
#define B1D " %1ld"
#define P5DB "%5ld "
#define P7DB "%7ld  "
#endif

#ifdef FR_XLOLO
#define PD "%lld"
#define PDB "%lld "
#define B5D " %5lld"
#define B1D " %1lld"
#define P5DB "%5lld "
#define P7DB "%7lld  "
#endif

#ifdef FR_XDOUB
#define PG "%lg"
#define PF "%lf"
#define PFB "%lf "
#define P15E "%+#15.7lE"
#define B315E "   %+#15.7lE"
#define B213E "  %+#13.5lE"
#define P11E "%+#11.3lE"
#endif

#ifdef FR_XQUAD
#define PG "%Lg"
#define PF "%Lf"
#define PFB "%Lf "
#define P15E "%+#15.7LE"
#define B315E "   %+#15.7LE"
#define B213E "  %+#13.5LE"
#define P11E "%+#11.3LE"
#endif

/****************************************************************************
*  Function-Declarationen
****************************************************************************/
int  dyn88r(void);
int  ale88r(int);
int  ri188i(void);
int  z88a(void);
int  z88ai(void);
int  wria88r(void);
int  lan88r(void);
int  wrim88r(FR_INT4,int);
int  wlog88r(FR_INT4,int);
int  z88br(void);
int  z88cr(void);
int  z88dr(void);
int  z88er(void);
void z88bc(void);
void dro288(void);
void fnul88(void);
void fio888(void);
int  wryd88(void);
int  man88r(void);
int  int88r(void);
int  elp88r(void);
int  mat88r(void);

/****************************************************************************
*  globale Variable
****************************************************************************/
/*---------------------------------------------------------------------------
* Files
*--------------------------------------------------------------------------*/
FILE *fdyn,*fwlo,*fcfg,*fi1,*fi2,*fi5,*felp,*fint,*fmat,*fman;
FILE *fo0,*fo1,*fo2,*fo3,*fo4,*fo5,*fo8;

char cdyn[8]  = "z88.dyn";
char cl1[10]  = "z88r.log";
char ci1[10]  = "z88i1.txt";
char ci2[10]  = "z88i2.txt";
char ci5[10]  = "z88i5.txt";
char celp[12] = "z88elp.txt";
char cint[12] = "z88int.txt";
char cmat[12] = "z88mat.txt";
char cman[12] = "z88man.txt";

char co0[10] = "z88o0.txt";
char co1[10] = "z88o1.txt";
char co2[10] = "z88o2.txt";
char co3[10] = "z88o3.txt";
char co4[10] = "z88o4.txt";
char co5[10] = "z88o5.txt";
char co8[10] = "z88o8.txt";  
char cfg[11] = "z88com.cfg";
  
/*---------------------------------------------------------------------------
* Pointer
*--------------------------------------------------------------------------*/
FR_DOUBLEAY GS;
FR_DOUBLEAY CI;
FR_DOUBLEAY se;
FR_DOUBLEAY rs;
FR_DOUBLEAY u;     /* bekommt keinen eigenen Speicher, gemappt auf rs */
FR_DOUBLEAY xi;
FR_DOUBLEAY xa;
FR_DOUBLEAY v;
FR_DOUBLEAY pk;
FR_DOUBLEAY zz;
FR_DOUBLEAY fak;
FR_DOUBLEAY x;
FR_DOUBLEAY y;
FR_DOUBLEAY z;
FR_DOUBLEAY emod;
FR_DOUBLEAY rnue;
FR_DOUBLEAY qpara;
FR_DOUBLEAY riyy;
FR_DOUBLEAY eyy;
FR_DOUBLEAY rizz;
FR_DOUBLEAY ezz;
FR_DOUBLEAY rit;
FR_DOUBLEAY wt;
FR_DOUBLEAY xcp;
FR_DOUBLEAY ycp;
FR_DOUBLEAY zcp;
FR_DOUBLEAY rkap;
FR_DOUBLEAY pres;
FR_DOUBLEAY tr1;
FR_DOUBLEAY tr2;
FR_DOUBLEAY smw;
FR_DOUBLEAY smwku;
FR_DOUBLEAY gmw;
FR_DOUBLEAY gmwku;
FR_DOUBLEAY fsum1;
FR_DOUBLEAY fsum2;
FR_DOUBLEAY fsum3;
FR_DOUBLEAY fsum4;
FR_DOUBLEAY fsum5;
FR_DOUBLEAY fsum6;
FR_DOUBLEAY sigvku;
FR_DOUBLEAY sdu;
FR_DOUBLEAY tmt;
FR_DOUBLEAY tm;
FR_DOUBLEAY zm;

FR_INT4AY ip;
FR_INT4AY iez;
FR_INT4AY koi;
FR_INT4AY ifrei; 
FR_INT4AY ioffs;
FR_INT4AY koffs;
FR_INT4AY ityp;
FR_INT4AY ivon_elp;
FR_INT4AY ibis_elp;
FR_INT4AY ivon_int;
FR_INT4AY ibis_int;
FR_INT4AY ivon_mat;
FR_INT4AY ibis_mat;
FR_INT4AY ifbeti;
FR_INT4AY intord;
FR_INT4AY intos;
FR_INT4AY nep;
FR_INT4AY noi;
FR_INT4AY noffs;
FR_INT4AY jsm;

/*---------------------------------------------------------------------------
* Arrays
*--------------------------------------------------------------------------*/
FR_DOUBLE xk[21], yk[21], zk[21];      /* 21 ist MAXPA , HEXA88 */
FR_DOUBLE h[21];                       /* 21 ist MAXPA , HEXA88 */
FR_DOUBLE b[361];                      /* ist 6 x 60 +1, HEXA88 */
FR_DOUBLE xx[61];                      /* ist 3 x 20 +1, HEXA88 */
FR_DOUBLE d[37];                       /* ist 6 x 6  +1, HEXA88 */
FR_DOUBLE ds[37];                      /* fuer Schalenberech.   */
FR_DOUBLE dp[37];                      /* fuer Schalenberech.   */
FR_DOUBLE p[61];                       /* ist 3 x 20 +1, HEXA88 */

/* fuer Plattenberechnung */
FR_DOUBLE be[49];                      /* fuer 16-Knoten Platte  */
FR_DOUBLE hi[49];
FR_DOUBLE hj[49];
FR_DOUBLE hk[49];
FR_DOUBLE bbi[145];
FR_DOUBLE bsv[97];
FR_DOUBLE dbi[10];
FR_DOUBLE dsv[5];

FR_DOUBLE ul[61];                     /* 61 ist 20 x 3 +1 */
FR_DOUBLE f[61];                      /* 61 ist MAXFE */

/* fuer Schalenberechnung */
FR_DOUBLE xc[9];
FR_DOUBLE yc[9];
FR_DOUBLE zc[9];

FR_INT4 mcomp[21];                    /* 21 ist MAXPA */
FR_INT4 mspan[21];                    /* 21 ist MAXPA */
FR_INT4 jetyp[26];                    /* 25 Elementtypen */

/*---------------------------------------------------------------------------
* Variable
*--------------------------------------------------------------------------*/
FR_DOUBLE emode,rnuee,qparae,riyye,eyye,rizze,ezze,rite,wte,eps,rp;
FR_DOUBLE xkp,ykp,zkp,rkape;
FR_DOUBLE pree,tr1e,tr2e,rpomega,rpalpha;

FR_INT4   intore,nel,ktyp,maxit,kfoun,jelem,ngau,nrb,mmat,mint,melp;
FR_INT4   LANG,IDYNMEM,jpri,ifnili,icore,idumpmax,ihflag,ifbetie;
FR_INT4   ndim,nkp,ne,nfg,nfgp1,nkoi,kflag,ibflag,ipflag,npr,iqflag;
FR_INT4   mxknot,mxfrei,ninto,kc,isflag,mxfe,kdflag,kch1,kch2,kch3;

char      cline[256];
char      cbytes[256];

/*---------------------------------------------------------------------------
* vorbelegte Variable
*--------------------------------------------------------------------------*/
FR_INT4 MAXIEZ=0,MAXGS=0,MAXNFG=0,MAXK=0,MAXE=0,MAXKOI=0;
FR_INT4 MAXESM=3600,MAXPR=0,MAXGP=0,MAXTRA=2305,MAXRBD=0;
FR_INT4 MAXPEL=0,MAXMAT=0;
FR_INT4 MAXJNT=0;  /* nicht MAXINT bei Windows! */
FR_INT4 ICFLAG=1;  /* SICCG-Solver mit Sparse-Speicherung */
FR_INT4 noci=0,iquiet=0;

/*--------------------------------------------------------------------------
* Variable speziell fuer Windows-Z88R
*-------------------------------------------------------------------------*/
int     ifmode= IDM_LINA;
int     ifsolv= IDM_SRSIC;

int     *pp;

char    *comli;
char     cstore[512];
char     cbcall[512];
char     cbpref[512];
char     cbhelp[512];
char     callbrow[512];
char     cmess[512];

/****************************************************************************
* WinMain
****************************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   PSTR lpszCmdLine, int nCmdShow)
{
HWND       hWnd;
MSG        msg;
WNDCLASSEX wndclass;

char       capname[10];
       
/****************************************************************************
* Handles kommen lassen, Window oeffnen
****************************************************************************/
comli= (char *)calloc(256,sizeof(char)); 
comli= lpszCmdLine;

strcpy(capname,"Z88R");

wndclass.cbSize        = sizeof(wndclass);
wndclass.style         = CS_HREDRAW | CS_VREDRAW;
wndclass.lpfnWndProc   = WndProc;
wndclass.cbClsExtra    = 0;
wndclass.cbWndExtra    = 0;
wndclass.hInstance     = hInstance;
wndclass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88R));
wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
wndclass.hbrBackground = CreateSolidBrush(RGB(255,255,255));
wndclass.lpszMenuName  = capname;
wndclass.lpszClassName = capname;
wndclass.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(ICO_Z88R));

RegisterClassEx(&wndclass);

hWnd = CreateWindow(capname,"The linear Z88 Solver Z88R Open Source",
                    WS_OVERLAPPEDWINDOW,
                    0, 150,
                    560, 640,
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

/****************************************************************************
* Main Window Procedure
****************************************************************************/
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
extern int        ifsolv;

extern char       cstore[];
extern char       cbcall[];
extern char       cbpref[];
extern char       cbhelp[];
extern char       cmess[];
extern char       *comli;

HMENU             hMenu;

PAINTSTRUCT       ps;

static int        ixClient,iyClient;

int               imess,iret,ipara1=0,ipara2=0;

size_t            laenge;

FR_INT4           i;

/*---------------------------------------------------------------------------
* Los gehts
*--------------------------------------------------------------------------*/
switch (Message)
  {
/*---------------------------------------------------------------------------
* case WM_CREATE
*--------------------------------------------------------------------------*/
  case WM_CREATE:
/*===========================================================================
* hInstance kommen lassen
*==========================================================================*/
#ifdef FR_XWIN64
    hInstance= (HINSTANCE)GetWindowLongPtr(hWnd,GWLP_HINSTANCE);
#endif
#ifdef FR_XWIN32
    hInstance= (HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE);
#endif

/*===========================================================================
* Wartecursor anlegen
*==========================================================================*/
    waitcur= LoadCursor(hInstance,MAKEINTRESOURCE(CUR_Z88R));

/*===========================================================================
* Sprache feststellen
*==========================================================================*/
    iret= lan88r();
    if(iret != 0)
      {
      ale88r(iret);
      PostQuitMessage(0);
      return(1);
      }

    hMenuGer= LoadMenu(hInstance,"GERMAN");
    hMenuEng= LoadMenu(hInstance,"ENGLISH");

    if(LANG == 1) SetMenu(hWnd,hMenuGer);
    if(LANG == 2) SetMenu(hWnd,hMenuEng);

/*===========================================================================
* IFNILI setzen
*==========================================================================*/
    ifnili= 0;
    ifmode= IDM_LINA;

/*===========================================================================
* ICFLAG setzen
*==========================================================================*/
    ICFLAG= 1;
    ifsolv= IDM_SRSIC;
 
/*===========================================================================
* Toolbar
*==========================================================================*/
    hToolBar= InitToolBar(hWnd);

/*===========================================================================
* Commandline auswerten
*==========================================================================*/
    if( (strstr(comli,"-c"))!= NULL) /* Berechnung */
      {
      ipara1= 1;
      ifnili= 0;
      }
    if( (strstr(comli,"-t"))!= NULL) /* Testmode */
      {
      ipara1= 1;
      ifnili= 9;
      }

    if( (strstr(comli,"-choly"))!= NULL) /* Cholesky-Solver */
      {
      ipara2= 1;
      ICFLAG= 0;
      }
    if( (strstr(comli,"-siccg"))!= NULL) /* SICCG */
      {
      ipara2= 1;
      ICFLAG= 1;
      }
    if( (strstr(comli,"-sorcg"))!= NULL) /* SORCG */
      {
      ipara2= 1;
      ICFLAG= 2;
      }

    if(ipara1 == 1 && ipara2 == 1) 
      PostMessage(hWnd,WM_COMMAND,IDM_GO,0);

  return 0; /* Ende WM_CREATE */

/*---------------------------------------------------------------------------
* case WM_INITMENU
*---------------------------------------------------------------------------*/
  case WM_INITMENU:
    hMenu= GetMenu(hWnd); 

    CheckMenuItem(hMenu,IDM_LINA, MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_TEST, MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,ifmode,   MF_CHECKED   | MF_BYCOMMAND);   

    CheckMenuItem(hMenu,IDM_CHOLY,MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_SRSIC,MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,IDM_SRSOR,MF_UNCHECKED | MF_BYCOMMAND);   
    CheckMenuItem(hMenu,ifsolv,   MF_CHECKED   | MF_BYCOMMAND);   
  return 0;
  
/*---------------------------------------------------------------------------
* case WM_MOVE
*--------------------------------------------------------------------------*/
  case WM_MOVE:
  return 0;

/*---------------------------------------------------------------------------
* case WM_SIZE
*--------------------------------------------------------------------------*/
  case WM_SIZE:
    iyClient= HIWORD(lParam);
    ixClient= LOWORD(lParam);
  return 0;

/*---------------------------------------------------------------------------
* WM_NOTIFY
*--------------------------------------------------------------------------*/
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

        case ITC_LINA:
          if(LANG == 1) pReply= "Berechnung";
          if(LANG == 2) pReply= "computation";
        break;

        case ITC_TEST:
          if(LANG == 1) pReply= "Testmode fuer Speicherbedarf der Solver";
          if(LANG == 2) pReply= "Test Mode for the solver memory needs";
        break;

        case ITC_CHOLY:
          if(LANG == 1) pReply= "Cholesky-Solver (=kleine Strukturen)";
          if(LANG == 2) pReply= "Cholesky Solver (=small structures)";
        break;

        case ITC_SRSIC:
          if(LANG == 1) pReply= "SICCG-Solver (=grosse Strukturen)";
          if(LANG == 2) pReply= "SICCG Solver (=large structures)";
        break;

        case ITC_SRSOR:
          if(LANG == 1) pReply= "SORCG-Solver (=grosse Strukturen)";
          if(LANG == 2) pReply= "SORCG Solver (=large structures)";
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

/*---------------------------------------------------------------------------
* case WM_COMMAND
*--------------------------------------------------------------------------*/
  case WM_COMMAND:
    switch (LOWORD(wParam))
      {

/*===========================================================================
* COMMAND : Wer ist es
*==========================================================================*/
      case IDM_WER:
        if(LANG == 1) strcpy(cmess,
"Der lineare Z88-Solver Z88R fuer Windows\n\
Version 15OS\n\
Copyright Univ.-Prof.Dr.-Ing. Frank Rieg,\n\
Universitaet Bayreuth, 2017\n\
Alle Rechte vorbehalten\n");

          if(LANG == 2) strcpy(cmess,
"The linear Z88 Solver Z88R for Windows\n\
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

        MessageBox(NULL,cmess,"Z88R", MB_OK | MB_ICONINFORMATION);
      return 0; 

/*===========================================================================
* COMMAND : Xit
*==========================================================================*/
      case IDM_XIT:
      case ITC_XIT:
        PostQuitMessage(0);
      return 0; 

/*===========================================================================
* COMMAND : Hilfe
*==========================================================================*/
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
          wlog88r(0L,LOG_NOACROBAT);
          ale88r(AL_NOACROBAT);
          }
      return 0;

/*===========================================================================
* COMMAND : Mode aus Menue
*==========================================================================*/
      case IDM_LINA:
      case IDM_TEST:
        hMenu= GetMenu(hWnd);
        CheckMenuItem(hMenu,ifmode,MF_UNCHECKED | MF_BYCOMMAND);
        ifmode= LOWORD(wParam);
        CheckMenuItem(hMenu,ifmode,MF_CHECKED   | MF_BYCOMMAND);   

        if     (ifmode == IDM_LINA) 
          {
          ifnili = 0;
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_LINA,(LPARAM) MAKELONG(TRUE, 0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_TEST,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if(ifmode == IDM_TEST)
          {
          ifnili = 9;
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_LINA,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_TEST,(LPARAM) MAKELONG(TRUE, 0) );
          }

        else MessageBox(NULL,"No Mode !","Z88R", MB_OK | MB_ICONHAND);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0; 

/*===========================================================================
* COMMAND : Mode aus Toolbar
*==========================================================================*/
      case ITC_LINA:
        ifnili= 0;
        ifmode= IDM_LINA; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_TEST:
        ifnili= 9;
        ifmode= IDM_TEST; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*===========================================================================
* COMMAND : Solver aus Menue
*==========================================================================*/
      case IDM_CHOLY:
      case IDM_SRSIC:
      case IDM_SRSOR:
        hMenu= GetMenu(hWnd);
        CheckMenuItem(hMenu,ifsolv,MF_UNCHECKED | MF_BYCOMMAND);
        ifsolv= LOWORD(wParam);
        CheckMenuItem(hMenu,ifsolv,MF_CHECKED   | MF_BYCOMMAND);   

        if     (ifsolv == IDM_CHOLY) 
          {
          ICFLAG = 0;
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_CHOLY,(LPARAM) MAKELONG(TRUE, 0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_SRSIC,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_SRSOR,(LPARAM) MAKELONG(FALSE,0) );
          }


        else if (ifsolv == IDM_SRSIC) 
          {
          ICFLAG = 1;
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_CHOLY,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_SRSIC,(LPARAM) MAKELONG(TRUE, 0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_SRSOR,(LPARAM) MAKELONG(FALSE,0) );
          }

        else if (ifsolv == IDM_SRSOR) 
          {
          ICFLAG = 2;
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_CHOLY,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_SRSIC,(LPARAM) MAKELONG(FALSE,0) );
          SendMessage(hToolBar,TB_CHECKBUTTON,
          (WPARAM)ITC_SRSOR,(LPARAM) MAKELONG(TRUE, 0) );
          }

        else MessageBox(NULL,"No Solver !","Z88R", MB_OK | MB_ICONHAND);
        InvalidateRect(hWnd,NULL,TRUE);
      return 0; 

/*===========================================================================
* COMMAND : Solver aus Toolbar
*==========================================================================*/
      case ITC_CHOLY:
        ICFLAG = 0;
        ifsolv = IDM_CHOLY; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_SRSIC:
        ICFLAG = 1;
        ifsolv = IDM_SRSIC; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

      case ITC_SRSOR:
        ICFLAG = 2;
        ifsolv = IDM_SRSOR; 
        InvalidateRect(hWnd,NULL,TRUE);
      return 0;

/*===========================================================================
* COMMAND : Go
*==========================================================================*/
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

/****************************************************************************
* Modes ausschreiben
****************************************************************************/
        if(ICFLAG == 0) wrim88r(0,TX_ICFLAG0); /* Cholesky-Solver */
        if(ICFLAG == 1) wrim88r(0,TX_ICFLAG1); /* SICCG-Solver */
        if(ICFLAG == 2) wrim88r(0,TX_ICFLAG2); /* SORCG-Solver */

        if(ifnili == 9) wrim88r(0,TX_IFNILI9); /* Testmode */
        if(ifnili == 0) wrim88r(0,TX_IFNILI0); /* Berechnung */

/****************************************************************************
* Berechnung: IFNILI= 0 oder Testmode: IFNILI = 9
****************************************************************************/
        jpri=  1;                  /* Z88O1.TXT und andere andrucken */

/*===========================================================================
* Einlesen Z88MAN.TXT. Oeffnen & schliessen erfolgt in MAN88R.C
*==========================================================================*/
        iret= man88r();
        if(iret != 0)
          {
          ale88r(iret);
          stop88r();              
          }    

/*===========================================================================
* dynamischen Speicher kommen lassen
*==========================================================================*/
        iret= dyn88r();
        if(iret != 0)
          {
          ale88r(iret);
          stop88r();              
          }    

/*===========================================================================
* Einlesen Z88I1.TXT
*==========================================================================*/
        iret= ri188r();
        if(iret != 0)
          {
          ale88r(iret);
          stop88r();              
          }     

/*===========================================================================
* Einlesen Z88INT.TXT
*==========================================================================*/
        iret= int88r();
        if(iret != 0)
          {
          ale88r(iret);
          stop88r();              
          } 

/*===========================================================================
* Einlesen Z88ELP.TXT
*==========================================================================*/
        iret= elp88r();
        if(iret != 0)
          {
          ale88r(iret);
          stop88r();              
          }   

/*===========================================================================
* Einlesen Z88MAT.TXT
*==========================================================================*/
        iret= mat88r();
        if(iret != 0)
          {
          ale88r(iret);
          stop88r();              
          }                                               

/*===========================================================================
* die Files oeffnen: Z88I2.TXT, Z88I5.TXT und
* Z88O1.TXT, Z88O2.TXT, Z88O3.TXT, Z88O4.TXT, Z88O5.TXT, Z88O8.TXT
*==========================================================================*/
/*---------------------------------------------------------------------------
* die Eingabefiles
*--------------------------------------------------------------------------*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88I2.TXT Randbedingungen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        fi2= fopen(ci2,"r");
        if(fi2 == NULL)
          {
          wlog88r(0,LOG_NOI2);
          fclose(fwlo);
          return(AL_NOI2);
          }
        rewind(fi2);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88I5.TXT Flaechenlasten: Hier nur iqflag feststellen. 
* Ansonsten sind Z88BR --> RI588I fuers Oeffnen und Schliessen zustaendig.
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        fi5= fopen(ci5,"r");
        if(fi5 == NULL) goto L1000; 
        rewind(fi5);

        fgets(cline,256,fi5);
        sscanf(cline,PD,&npr);
        if(npr == 0) iqflag = 0;
        else         iqflag = 1;
        fclose(fi5);    
L1000:;

/*---------------------------------------------------------------------------
* die Ausgabefiles
*--------------------------------------------------------------------------*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88O1.TXT aufbereitete Randbedingungen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        fo1= fopen(co1,"w+");
        if(fo1 == NULL)
          {
          wlog88r(0,LOG_NOO1);
          fclose(fwlo);
          return(AL_NOO1);
          }
        rewind(fo1);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88O2.TXT Verschiebungen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        fo2= fopen(co2,"w+");
        if(fo2 == NULL)
          {
          wlog88r(0,LOG_NOO2);
          fclose(fwlo);
          return(AL_NOO2);
          }
        rewind(fo2);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88O3.TXT Spannungen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        fo3= fopen(co3,"w+");
        if(fo3 == NULL)
          {
          wlog88r(0,LOG_NOO3);
          fclose(fwlo);
          ale88r(AL_NOO3);
          stop88r();              
          }
        rewind(fo3);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88O4.TXT Knotenkraefte
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        fo4= fopen(co4,"w+");
        if(fo4 == NULL)
          {
          wlog88r(0,LOG_NOO4);
          fclose(fwlo);
          ale88r(AL_NOO4);
          stop88r();              
          }
        rewind(fo4);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88O5.TXT fuer Z88O: Spannungen in den Gausspunkten
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        fo5= fopen(co5,"w+");
        if(fo5 == NULL)
          {
          wlog88r(0,LOG_NOO5);
          fclose(fwlo);
          ale88r(AL_NOO5);
          stop88r();              
          }
        rewind(fo5);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Z88O8.TXT fuer Z88O: Spannungen in den Eckknoten und mittlere Spannungen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        fo8= fopen(co8,"w+");
        if(fo8 == NULL)
          {
          wlog88r(0,LOG_NOO8);
          fclose(fwlo);
          ale88r(AL_NOO8);
          stop88r();              
          }
        rewind(fo8);


/*===========================================================================
* Z88A fuer Cholesky-Solver; Jennings
*==========================================================================*/
        if(ICFLAG == 0)
          {
          iret= z88a();
          if(iret != 0)
            {
            ale88r(iret);
            stop88r();              
            } 
          }

/*===========================================================================
* Z88AI fuer SICCG- und SORCG-Solver; Sparsematrix
*==========================================================================*/
        if(ICFLAG != 0)
          {
          iret= z88ai();
          if(iret != 0)
            {
            ale88r(iret);
            stop88r();              
            } 
          }        

/*===========================================================================
* Z88O0.TXT und Anfos fuer GS und koi andrucken
*==========================================================================*/
        iret= wria88r();  /* oeffnet und schliesst fo0 */
        if(iret != 0)
          {
          ale88r(iret);
          stop88r();              
          } 

/*===========================================================================
* Testmode? Dann Absprung, bei Berechnung weitermachen
*==========================================================================*/
        if(ifnili == 9) goto L2000;

/*===========================================================================
* z88br : Compilation + Lastvektoren
*==========================================================================*/
        iret= z88br();
        if(iret != 0)
          {
          ale88r(iret);
          stop88r();              
          }           

/*===========================================================================
* z88cr: Solver
*==========================================================================*/
        iret= z88cr();
        if(iret != 0)
          {
          ale88r(iret);
          stop88r();              
          }   

/*===========================================================================
* z88cr: Spannungsberechnung
*==========================================================================*/                         
        fnul88();           /* fsum1 ~ fsum6 = 0, smwku,gmwku,sigvku = 0   */
        u= rs;              /* z88bc liefert rs                            */
                            /* Z88ER,Z88DR+DRO288 brauchen "historisch" u  */
        z88dr();     

/*===========================================================================
* z88er: Knotenkraft-Berechnung
*==========================================================================*/   
        z88er();

/****************************************************************************
* Z88O2.TXT und Z88O8.TXT andrucken
****************************************************************************/
        dro288();           /* Z88O2.TXT andrucken */
        fio888();           /* Z88O8.TXT beschreiben */

/****************************************************************************
* Dateien schliessen und Ende
****************************************************************************/
L2000:; /* Einsprung fuer Testmode */
        fclose(fi2);
        fclose(fo1);
        fclose(fo2);
        fclose(fo3);
        fclose(fo4);
        fclose(fo5);
        fclose(fo8);
        
/*----------------------------------------------------------------------
* Ende Case Go
*---------------------------------------------------------------------*/
        ReleaseDC(hWnd,hDC);  
        SetCursor(LoadCursor(NULL,IDC_ARROW));
        if(LANG == 1) strcpy(cmess,"Z88 Solver Z88R gelaufen");
        if(LANG == 2) strcpy(cmess,"Z88 solver Z88R done");
        MessageBox(NULL,cmess,"Z88R", MB_OK | MB_ICONINFORMATION);
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

/***********************************************************************
* FNUL88: Summations-Speicher nullen fuer z88er und z88dr
***********************************************************************/
void fnul88(void)
{
extern FR_DOUBLEAY fsum1;
extern FR_DOUBLEAY fsum2;
extern FR_DOUBLEAY fsum3;
extern FR_DOUBLEAY fsum4;
extern FR_DOUBLEAY fsum5;
extern FR_DOUBLEAY fsum6;
extern FR_DOUBLEAY sigvku;
extern FR_DOUBLEAY smwku;
extern FR_DOUBLEAY gmwku;

extern FR_INT4     ne,nkp,MAXGP;

FR_INT4 i;

for(i= 1;i <= nkp;i++) 
  {
  fsum1[i]= 0.;
  fsum2[i]= 0.;
  fsum3[i]= 0.;
  fsum4[i]= 0.;
  fsum5[i]= 0.;
  fsum6[i]= 0.;
  }

for(i= 1; i <= MAXGP; i++)
  sigvku[i] = 0.;

for(i= 1;i <= nkp;i++) 
  smwku[i]= 0.;

for(i= 1; i <= ne; i++)
  gmwku[i] = 0.;

return;
}

/**************************************************************************
* DRO288: Z88O2.TXT andrucken
**************************************************************************/
void dro288(void)
{
extern FILE        *fo2;
extern FR_DOUBLEAY u;
extern FR_INT4     LANG,nkp;

FR_INT4 i,k;

wrim88r(0,TX_WRIO2);
wlog88r(0,LOG_WRIO2);

if(LANG == 1)
  {
  fprintf(fo2,"Ausgabedatei Z88O2.TXT: Verschiebungen, erzeugt mit Z88R V15OS\n");
  fprintf(fo2,"                        **************\n");
  fprintf(fo2,"Lastfall: 1");
  fprintf(fo2,
  "\nKnoten         U(1)              U(2)              U(3)\
              U(4)              U(5)              U(6)\n");
  }

if(LANG == 2)
  {
  fprintf(fo2,"output file Z88O2.TXT: displacements, computed by Z88R V15OS\n");
  fprintf(fo2,"                       *************\n");
  fprintf(fo2,"Loadcase: 1");
  fprintf(fo2,
  "\nnode           U(1)              U(2)              U(3)\
              U(4)              U(5)              U(6)\n");
  }

/*----------------------------------------------------------------------
* Schleife ueber alle Knoten
*---------------------------------------------------------------------*/
k= 1;

for(i = 1;i <= nkp;i++)
  {
          
/*======================================================================
* 2 Freiheitsgrade:
*=====================================================================*/
  if (ifrei[i] == 2)
    {
    fprintf(fo2,NL B5D B315E B315E,i,u[k],u[k+1]);
    k+= 2;
    }

/*======================================================================
* 3 Freiheitsgrade:
*=====================================================================*/
  if (ifrei[i] == 3)
    {
    fprintf(fo2,NL B5D B315E B315E B315E,
    i,u[k],u[k+1],u[k+2]);
    k+= 3;
    }

/*======================================================================
* 6 Freiheitsgrade:
*=====================================================================*/
  if (ifrei[i] == 6)
    {
    fprintf(fo2,NL B5D B315E B315E B315E B315E B315E B315E,
    i,u[k],u[k+1],u[k+2],u[k+3],u[k+4],u[k+5]);
    k+= 6;
    }

/*---------------------------------------------------------------------
* Ende Schleife ueber alle Knoten
*--------------------------------------------------------------------*/
  }

fprintf(fo2,"\n");

return;
}

/**************************************************************************
* FIO888: Beschreiben von Z88O8.TXT
**************************************************************************/
void fio888(void)
{
extern FR_DOUBLEAY smw;
extern FR_DOUBLEAY gmw;

extern FR_INT4AY ityp;
extern FR_INT4AY jsm;

extern FR_INT4 isflag,nkp;

FR_INT4 k,i,janz;

/*======================================================================
* ggf. Ausschreiben von Z88O8.TXT fuer alle Nicht-Balken
*=====================================================================*/
if((isflag == 1 || isflag == 2 || isflag == 3) && 
   !(ityp[1] == 2 || ityp[1] == 5 || ityp[1] == 13 || ityp[1] == 25))
  {

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Wieviel "Eckknoten" ? Dazu ISFLAG als Kennung fuer Z88O
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  janz= 0;
  for(k= 1; k <= nkp; k++)
    if(jsm[k] > 0) janz++;

  if(LANG == 1) fprintf(fo8," " PDB PD,janz,isflag);
  if(LANG == 2) fprintf(fo8," " PDB PD,janz,isflag);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Eckknoten mit Vergleichsspannungen in Z88O8.TXT ausschreiben
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for(k= 1; k <= nkp; k++)
    {
    if(jsm[k] > 0)
      {
      fprintf(fo8,NL P7DB P7DB P11E,k,jsm[k],smwku[k]);
      }
    }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Wieviel Elemente fuer Z88O8.TXT?
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  fprintf(fo8,NL " " PD,ne);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* mittlere Vergleichsspannungen pro Element in Z88O8.TXT ausschreiben
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for(k= 1; k <= ne; k++)
    fprintf(fo8,NL P7DB P11E,k,gmwku[k]);

  }

fprintf(fo5,"\n");
fprintf(fo8,"\n");
return;
}


