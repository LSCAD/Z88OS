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
/*****************************************************************************
* Compilerunit m11.c fuer Z88O enthaelt:
*       PopFileInitialize
*       PopFileOpenDlg
*       FaktorVerDiaProc
*       FaktorRotDiaProc
*       FaktorZmDiaProc
*       KnotenDiaProc
*       ElementDiaProc
* 17.7.2011 Rieg
*****************************************************************************/ 
/*****************************************************************************
* Windows
*****************************************************************************/
#ifdef FR_WIN
#include <z88o.h>
#include <windows.h>
#include <commdlg.h>
#include <stdlib.h>  /* gcvt, atof */
#endif

/*****************************************************************************
* Function PopFileInitialize bereitet Fileauswahlbox fuer Struktur vor
*****************************************************************************/
void PopFileInitialize(HWND hwnd)
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
* Function PopFileOpenDlg zeigt Fileauswahlbox fuer Struktur an
*****************************************************************************/
BOOL PopFileOpenDlg(HWND hwnd)
{
extern OPENFILENAME ofn;
extern char cfname[];
extern char ctname[];
extern char cstrn[];

strcpy(cfname,"z88i1.txt");

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

/*****************************************************************************
* Function FaktorVerDiaProc zeigt Dialog- Box fuer Vergr. Verschiebungen an
*****************************************************************************/
BOOL CALLBACK FaktorVerDiaProc(HWND hDlg, UINT message,
                               WPARAM wParam, LPARAM lParam)
{
extern double fux,fuy,fuz;
int  idigit= 20;
char cfux[31], cfuy[31], cfuz[31];

/*---------------------------------------------------------------------------
* beim allerersten Start gehen fux, fuy & fuz mit je 100. rein
*--------------------------------------------------------------------------*/
gcvt(fux,idigit,cfux); 
gcvt(fuy,idigit,cfuy); 
gcvt(fuz,idigit,cfuz); 

switch (message)
  {
  case WM_INITDIALOG:
    SetDlgItemText(hDlg,IDDLG_V_TEXT9, cfux);
    SetDlgItemText(hDlg,IDDLG_V_TEXT10,cfuy);
    SetDlgItemText(hDlg,IDDLG_V_TEXT11,cfuz);
    return(TRUE);

  case WM_COMMAND:
    switch (LOWORD(wParam))
      {
      case IDOK:
        GetDlgItemText(hDlg,IDDLG_V_TEXT9, cfux,30);
        GetDlgItemText(hDlg,IDDLG_V_TEXT10,cfuy,30);
        GetDlgItemText(hDlg,IDDLG_V_TEXT11,cfuz,30);
        fux= atof(cfux);
        fuy= atof(cfuy);
        fuz= atof(cfuz);
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
* Function FaktorRotDiaProc zeigt Dialog- Box fuer Rotatione an
*****************************************************************************/
BOOL CALLBACK FaktorRotDiaProc(HWND hDlg, UINT message,
                               WPARAM wParam, LPARAM lParam)
{
extern double rotx,roty,rotz;
int  idigit= 20;
char crotx[31], croty[31], crotz[31];

/*---------------------------------------------------------------------------
* beim allerersten Start gehen roty,roty & rotz mit je 0. rein
*--------------------------------------------------------------------------*/
gcvt(rotx,idigit,crotx); 
gcvt(roty,idigit,croty); 
gcvt(rotz,idigit,crotz); 

switch (message)
  {
  case WM_INITDIALOG:
    SetDlgItemText(hDlg,IDDLG_V_TEXT12,crotx);
    SetDlgItemText(hDlg,IDDLG_V_TEXT13,croty);
    SetDlgItemText(hDlg,IDDLG_V_TEXT14,crotz);
    return(TRUE);

  case WM_COMMAND:
    switch (LOWORD(wParam))
      {
      case IDOK:
        GetDlgItemText(hDlg,IDDLG_V_TEXT12,crotx,30);
        GetDlgItemText(hDlg,IDDLG_V_TEXT13,croty,30);
        GetDlgItemText(hDlg,IDDLG_V_TEXT14,crotz,30);
        rotx= atof(crotx);
        roty= atof(croty);
        rotz= atof(crotz);
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
* Function FaktorZmDiaProc zeigt Dialog- Box fuer zm an
*****************************************************************************/
BOOL CALLBACK FaktorZmDiaProc(HWND hDlg, UINT message,
                              WPARAM wParam, LPARAM lParam)
{
extern double zm;
int  idigit= 20;
char czm[31];

/*---------------------------------------------------------------------------
* beim allerersten Start geht zm mit -100 rein
*--------------------------------------------------------------------------*/
gcvt(zm,idigit,czm); 

switch (message)
  {
  case WM_INITDIALOG:
    SetDlgItemText(hDlg,IDDLG_V_TEXT15,czm);
    return(TRUE);

  case WM_COMMAND:
    switch (LOWORD(wParam))
      {
      case IDOK:
        GetDlgItemText(hDlg,IDDLG_V_TEXT15,czm,32);
        zm= atof(czm);
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
* Function KnotenDiaProc zeigt Dialog- Box fuer Knoten- Plotten an
*****************************************************************************/
BOOL CALLBACK KnotenDiaProc(HWND hDlg, UINT message,
                               WPARAM wParam, LPARAM lParam)
{
extern FR_INT4 jkvon,jkbis;
extern int     iplot; 
char           ckvon[20],ckbis[20];

/*---------------------------------------------------------------------------
* beim allerersten Start gehen jkvon und jkbis mit je 0 rein
*--------------------------------------------------------------------------*/
ltoa(jkvon,ckvon,10);
ltoa(jkbis,ckbis,10); 

switch (message)
  {
  case WM_INITDIALOG:
    SetDlgItemText(hDlg,IDDLG_V_TEXT16,ckvon);
    SetDlgItemText(hDlg,IDDLG_V_TEXT17,ckbis);
  return(TRUE);

  case WM_COMMAND:
    switch (LOWORD(wParam))
      {
      case IDOK:
        GetDlgItemText(hDlg,IDDLG_V_TEXT16,ckvon,20);
        GetDlgItemText(hDlg,IDDLG_V_TEXT17,ckbis,20);
        jkvon= atol(ckvon);
        jkbis= atol(ckbis);
        iplot= 1;
        EndDialog(hDlg,0);
      return TRUE;
        
      case IDCANCEL:
        iplot= 0;
        EndDialog(hDlg,0);
      return TRUE;
      }

  }
 
return FALSE;
}

/*****************************************************************************
* Function ElementDiaProc zeigt Dialog- Box fuer Element- Plotten an
*****************************************************************************/
BOOL CALLBACK ElementDiaProc(HWND hDlg, UINT message,
                               WPARAM wParam, LPARAM lParam)
{
extern FR_INT4 jevon,jebis;
extern int     iplot; 
char           cevon[20],cebis[20];

/*---------------------------------------------------------------------------
* beim allerersten Start gehen jevon und jebis mit je 0 rein
*--------------------------------------------------------------------------*/
ltoa(jevon,cevon,10);
ltoa(jebis,cebis,10); 

switch (message)
  {
  case WM_INITDIALOG:
    SetDlgItemText(hDlg,IDDLG_V_TEXT18,cevon);
    SetDlgItemText(hDlg,IDDLG_V_TEXT19,cebis);
  return(TRUE);

  case WM_COMMAND:
    switch (LOWORD(wParam))
      {
      case IDOK:
        GetDlgItemText(hDlg,IDDLG_V_TEXT18,cevon,20);
        GetDlgItemText(hDlg,IDDLG_V_TEXT19,cebis,20);
        jevon= atol(cevon);
        jebis= atol(cebis);
        iplot= 1;
        EndDialog(hDlg,0);
      return TRUE;
        
      case IDCANCEL:
        iplot= 0;
        EndDialog(hDlg,0);
      return TRUE;
      }

  }
 
return FALSE;
}
