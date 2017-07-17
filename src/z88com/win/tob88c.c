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
* TOB88C.C
* 26.7.2011 Rieg
***********************************************************************/
#include <windows.h>
#include <commctrl.h>

#include <z88com.h>

#ifdef FR_XWIN32
TBBUTTON tbb[] = 
     {
     0, ITC_Z88X,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
     1, ITC_Z88G,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
     2, ITC_Z88H,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
     3, ITC_Z88N,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
     4, ITC_Z88R,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
     5, ITC_Z88O,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
     6, ITC_DYN,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
     7, ITC_HELP,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,
     8, ITC_XIT,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0
     } ;
#endif

#ifdef FR_XWIN64
TBBUTTON tbb[] = 
     {
     0, ITC_Z88X,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,0,0,0,0,
     1, ITC_Z88G,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,0,0,0,0,
     2, ITC_Z88H,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,0,0,0,0,
     3, ITC_Z88N,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,0,0,0,0,
     4, ITC_Z88R,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,0,0,0,0,
     5, ITC_Z88O,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,0,0,0,0,
     6, ITC_DYN,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,0,0,0,0,
     7, ITC_HELP,  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,0,0,0,0,
     8, ITC_XIT,   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0, 0, 0,0,0,0,0
     } ;
#endif

/*----------------------------------------------------------------------
* Function InitToolBar
*---------------------------------------------------------------------*/
HWND InitToolBar (HWND hParent)
{
extern HINSTANCE hInstance;
HWND    hToolBar;
HBITMAP hBitmap;

hBitmap= LoadBitmap(hInstance,MAKEINTRESOURCE(BMP_Z88COM));

hToolBar= CreateToolbarEx (
               hParent,
               WS_CHILD | WS_VISIBLE       | WS_CLIPSIBLINGS |
               CCS_TOP  | TBSTYLE_TOOLTIPS | WS_BORDER | WS_EX_CLIENTEDGE,
               1,                    /* wID */
               9,                    /* nBitmaps */
               0,                    /* zu ladende Bitmap */
               (UINT)hBitmap,        /* zu ladende Bitmap */
               tbb,                  /* Pointer auf TBBUTTON Array */ 
               9,                    /* Anzahl Buttons */
               16,                   /* dxButton */
               16,                   /* dyButton */
               16,                   /* dxBitmap */ 
               16,                   /* dyBitmap */
               sizeof (TBBUTTON)) ;
  
return hToolBar ;
}

/*----------------------------------------------------------------------
* Function InitStatusBar
*---------------------------------------------------------------------*/
HWND InitStatusBar (HWND hParent)
{
HWND hStatusBar;

hStatusBar= CreateStatusWindow (
            WS_CHILD  | WS_VISIBLE    | WS_CLIPSIBLINGS |
            CCS_BOTTOM  |  SBARS_SIZEGRIP,
            "",
            hParent,
            2) ;

return hStatusBar ;
}

