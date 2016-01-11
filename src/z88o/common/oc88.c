/***********************************************************************
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
***********************************************************************/ 
/***********************************************************************
* diese compilerunit oc88 enthaelt:
*   vu3b88  -  unverformt
*   vv3b88  -  verformt
*   vgpc88  -  Gausspunkte, unverformt
*   vsca88
*   vcur88
* 17.7.2011 Rieg
***********************************************************************/
/*****************************************************************************
* Windows
*****************************************************************************/
#ifdef FR_WIN
#include <z88o.h>
#endif

/*****************************************************************************
* UNIX
*****************************************************************************/
#ifdef FR_UNIX
#include <z88o.h>
#endif

/***********************************************************************
*  function vu3b88
***********************************************************************/
int vu3b88(void)
{
extern FR_DOUBLEAY x;
extern FR_DOUBLEAY y;
extern FR_DOUBLEAY z;
extern FR_DOUBLEAY xv;
extern FR_DOUBLEAY yv;
extern FR_DOUBLEAY zv;

extern FR_DOUBLE facx,facy,facz,cx,cy,cz;

extern FR_INT4 nkp;

FR_INT4 i;

for(i= 1; i <= nkp; i++)
  {
  xv[i]= (x[i] - cx) * facx;
  yv[i]= (y[i] - cy) * facy;
  zv[i]= (z[i] - cz) * facz;
  }

return 0;
}

/***********************************************************************
*  function vv3b88
***********************************************************************/
int vv3b88(void)
{
extern FR_DOUBLEAY x;
extern FR_DOUBLEAY y;
extern FR_DOUBLEAY z;
extern FR_DOUBLEAY xv;
extern FR_DOUBLEAY yv;
extern FR_DOUBLEAY zv;
extern FR_DOUBLEAY ux;
extern FR_DOUBLEAY uy;
extern FR_DOUBLEAY uz;

extern FR_DOUBLE facx,facy,facz,cx,cy,cz,fux,fuy,fuz;

extern FR_INT4 nkp;
       
FR_INT4 i;

for(i= 1; i <= nkp; i++)
  {
  xv[i]= (x[i] + fux * ux[i] - cx) * facx;
  yv[i]= (y[i] + fuy * uy[i] - cy) * facy;
  zv[i]= (z[i] + fuz * uz[i] - cz) * facz;
  }

return 0;
}

/***********************************************************************
*  function vgpc88
***********************************************************************/
int vgpc88(void)
{
extern FR_DOUBLEAY xgp;
extern FR_DOUBLEAY ygp;
extern FR_DOUBLEAY zgp;
extern FR_DOUBLEAY xgpo;
extern FR_DOUBLEAY ygpo;
extern FR_DOUBLEAY zgpo;

extern FR_DOUBLE facx,facy,facz,cx,cy,cz;

extern FR_INT4 igpanz;

FR_INT4 i;

for(i= 1; i <= igpanz; i++)
  {
  xgpo[i]= (xgp[i] - cx) * facx;
  ygpo[i]= (ygp[i] - cy) * facy;
  zgpo[i]= (zgp[i] - cz) * facz;
  }

return 0;
}

/***********************************************************************
*  function vsca88
***********************************************************************/
int vsca88(void)
{
extern FR_DOUBLEAY x;
extern FR_DOUBLEAY y;
extern FR_DOUBLEAY z;

extern FR_DOUBLE facx,facy,facz,cx,cy,cz;
extern FR_DOUBLE xmin,xmax,ymin,ymax,zmin,zmax;

extern FR_INT4 ndim,nkp;
extern int  ifscale;

FR_DOUBLE eps= 1e-10;

FR_INT4 i;

if(ndim == 2L)
  {
  xmin= x[1];
  xmax= x[1];
  ymin= y[1];
  ymax= y[1];

  for(i= 1L; i <= nkp; i++)
    {
    if( x[i] < xmin) xmin= x[i];
    if( x[i] > xmax) xmax= x[i];
    if( y[i] < ymin) ymin= y[i];
    if( y[i] > ymax) ymax= y[i];
    }

  if(fabs(ymax - ymin) > eps)
    {
    facx= 100./(xmax - xmin);
    facy= 100./(ymax - ymin);

    if(facx > facy) facx= facy;
    else            facy= facx;
    facz= 0.;
    }
  else
    {
    facx= 100./(xmax - xmin);
    facy= facx;
    facz= 0.;
    }  

  cx= (xmin + xmax)*0.5;
  cy= (ymin + ymax)*0.5;
  cz= 0.;
  }

else    
  {
  xmin= x[1];
  xmax= x[1];
  ymin= y[1];
  ymax= y[1];
  zmin= z[1];
  zmax= z[1];

  for(i= 1L; i <= nkp; i++)
    {
    if( x[i] < xmin) xmin= x[i];
    if( x[i] > xmax) xmax= x[i];
    if( y[i] < ymin) ymin= y[i];
    if( y[i] > ymax) ymax= y[i];
    if( z[i] < zmin) zmin= z[i];
    if( z[i] > zmax) zmax= z[i];
    }

  if(fabs(ymax -ymin) > eps && fabs(zmax - zmin) > eps)
    {
    facx= 100./(xmax - xmin);
    facy= 100./(ymax - ymin);
    facz= 100./(zmax - zmin);

    if     (facx <= facy && facx <= facz) facy= facz= facx;
    else if(facy <= facx && facy <= facz) facx= facz= facy;
    else if(facz <= facy && facz <= facx) facy= facx= facz;
    }
  else
    {
    facx= 100./(xmax - xmin);
    facy= facx;
    facz= facx;
    }  

  cx= (xmin + xmax)*0.5;
  cy= (ymin + ymax)*0.5;
  cz= (zmin + zmax)*0.5;
  }

ifscale= IDM_NOSCALE;
return 0;
}

/***********************************************************************
*  function vcur88
***********************************************************************/
int vcur88(void)
{
extern FR_DOUBLEAY x;
extern FR_DOUBLEAY y;
extern FR_DOUBLEAY z;

extern FR_DOUBLE xmin,xmax,ymin,ymax,zmin,zmax;

extern FR_INT4 ndim,nkp;
extern int  ifvcur;

FR_INT4 i;

if(ndim == 2L)
  {
  xmin= x[1];
  xmax= x[1];
  ymin= y[1];
  ymax= y[1];

  for(i= 1L; i <= nkp; i++)
    {
    if( x[i] < xmin) xmin= x[i];
    if( x[i] > xmax) xmax= x[i];
    if( y[i] < ymin) ymin= y[i];
    if( y[i] > ymax) ymax= y[i];
    }
  }
else    
  {
  xmin= x[1];
  xmax= x[1];
  ymin= y[1];
  ymax= y[1];
  zmin= z[1];
  zmax= z[1];

  for(i= 1L; i <= nkp; i++)
    {
    if( x[i] < xmin) xmin= x[i];
    if( x[i] > xmax) xmax= x[i];
    if( y[i] < ymin) ymin= y[i];
    if( y[i] > ymax) ymax= y[i];
    if( z[i] < zmin) zmin= z[i];
    if( z[i] > zmax) zmax= z[i];
    }
  }

ifvcur= 1;
return 0;
}

