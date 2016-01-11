/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows & 
* the UNIX OS.
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
* Compilerunit m16.c fuer Z88O enthaelt:
* mrbd88
* ri5x88
* mko88
* magp88
* 19.7.2011 Rieg
***********************************************************************/ 
/***********************************************************************
* Leseformate fuer ri5x88
***********************************************************************/
#define NL "\n"

#ifdef FR_XINT
#define PD "%d"
#define BPD " %d"
#endif

#ifdef FR_XLONG
#define PD "%ld"
#define BPD " %ld"
#endif

#ifdef FR_XDOUB
#define BPG " %lg"
#endif

#ifdef FR_XQUAD
#define BPG " %Lg"
#endif

/***********************************************************************
* Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88o.h>
#include <windows.h>
#include <commctrl.h>
#include <gl\gl.h>
#include <stdio.h>  
#endif

/***********************************************************************
* UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88o.h>
#include <stdio.h>  
#include <GL/gl.h>
#include <GL/glx.h>
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wlog88o(FR_INT4,int);

/***********************************************************************
* hier beginnt Function mrbd88: Randbedingungen malen
***********************************************************************/
int mrbd88(void)
{
extern FILE *fwlo;
extern FR_DOUBLEAY xv;
extern FR_DOUBLEAY yv;
extern FR_DOUBLEAY zv;
extern FR_DOUBLEAY rwert;

extern GLfloat     rot[];
extern GLfloat     gruen[];
extern GLfloat     blau[];

extern FR_INT4AY   ityp;
extern FR_INT4AY   koi;
extern FR_INT4AY   koffs;
extern FR_INT4AY   noi;
extern FR_INT4AY   nep;
extern FR_INT4AY   nkn;
extern FR_INT4AY   ifg;
extern FR_INT4AY   iflag1;

extern FR_DOUBLE   zorbd,fazoo;

extern FR_INT4     nkp,nrb,ipflag,iqflag,nnp,npr,neg;

extern int         ifwbc;

FR_DOUBLE          xmin= +1e+10,xmax= -1e+10;

GLfloat            xps;

FR_INT4            i,j,k,m;

/*----------------------------------------------------------------------
* Grenzen feststellen
*---------------------------------------------------------------------*/
for(i= 1;i <= nkp;i++)
  {
  if(xv[i] < xmin) xmin= xv[i];
  if(xv[i] > xmax) xmax= xv[i];
  }

/*----------------------------------------------------------------------
* Punktgroesse setzen
*---------------------------------------------------------------------*/
xps= (GLfloat) (zorbd*(xmax-xmin)*fazoo);
glPointSize(xps);

/*----------------------------------------------------------------------
* Punkte malen: Randbedingungen aus Z88I2.TXT
*---------------------------------------------------------------------*/
for(i= 1;i <= nrb;i++)
  {
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verschiebung X ist 0 
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  if((ifwbc == IDM_RBDUX || ifwbc == IDM_RBDALL) && ifg[i] == 1 && 
     iflag1[i]== 2 && fabs(rwert[i]) < 1e-7) 
    glColor3f(rot[1],gruen[1],blau[1]);  
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verschiebung Y ist 0 
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  else if((ifwbc == IDM_RBDUY || ifwbc == IDM_RBDALL) && ifg[i] == 2 && 
     iflag1[i]== 2 && fabs(rwert[i]) < 1e-7) 
    glColor3f(rot[2],gruen[2],blau[2]);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verschiebung Z ist 0 
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  else if((ifwbc == IDM_RBDUZ || ifwbc == IDM_RBDALL) && ifg[i] == 3 && 
     iflag1[i]== 2 && fabs(rwert[i]) < 1e-7) 
    glColor3f(rot[3],gruen[3],blau[3]);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verschiebung U4 ist 0 
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  else if((ifwbc == IDM_RBDU4 || ifwbc == IDM_RBDALL) && ifg[i] == 4 && 
     iflag1[i]== 2 && fabs(rwert[i]) < 1e-7) 
    glColor3f(rot[4],gruen[4],blau[4]);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verschiebung U5 ist 0 
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  else if((ifwbc == IDM_RBDU5 || ifwbc == IDM_RBDALL) && ifg[i] == 5 && 
     iflag1[i]== 2 && fabs(rwert[i]) < 1e-7) 
    glColor3f(rot[5],gruen[5],blau[5]);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verschiebung U4 ist 0 
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  else if((ifwbc == IDM_RBDU6 || ifwbc == IDM_RBDALL) && ifg[i] == 6 && 
     iflag1[i]== 2 && fabs(rwert[i]) < 1e-7) 
    glColor3f(rot[6],gruen[6],blau[6]);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Verschiebung vorgegeben 
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  else if((ifwbc == IDM_RBDUA || ifwbc == IDM_RBDALL) && 
     iflag1[i]== 2 && fabs(rwert[i]) > 1e-7) 
    glColor3f(rot[7],gruen[7],blau[7]);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Kraft X 
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  else if((ifwbc == IDM_RBDFX || ifwbc == IDM_RBDALL) && 
     iflag1[i]==1 && ifg[i]==1) 
    glColor3f(rot[9],gruen[9],blau[9]);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Kraft Y 
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  else if((ifwbc == IDM_RBDFY || ifwbc == IDM_RBDALL) && 
     iflag1[i]==1 && ifg[i]==2) 
    glColor3f(rot[10],gruen[10],blau[10]);
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Kraft Z 
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  else if((ifwbc == IDM_RBDFZ || ifwbc == IDM_RBDALL) && 
     iflag1[i]==1 && ifg[i]==3) 
    glColor3f(rot[11],gruen[11],blau[11]);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* nichts tun
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  else
    continue;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Punkt malen
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  glBegin(GL_POINTS);
    glVertex3d(xv[nkn[i]],yv[nkn[i]],zv[nkn[i]]);
  glEnd();
  }

/*----------------------------------------------------------------------
* Punkte malen: Randbedingungen aus Z88I5.TXT
* Dabei werden nur stur die Punkte gemalt, obwohl alle Infos auch fuer
* die Elemente da sind. Dies fuer ggf. spaeter. 
*---------------------------------------------------------------------*/
if(iqflag == 1 && (ifwbc == IDM_RBDOL || ifwbc == IDM_RBDALL))
  {
  glColor3f(rot[8],gruen[8],blau[8]);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* alle Elemente mit Flaechenlasten ausser Platten 18,29 und 20
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  glBegin(GL_POINTS);
    for(i= 1; i <= nnp; i++) glVertex3d(xv[noi[i]],yv[noi[i]],zv[noi[i]]);
  glEnd();

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Platten 18,19 und 20, wenn Druecke in Z88I5.TXT
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for(i= 1; i <= npr; i++)
    {
    if(ityp[nep[i]]== 18) 
      {
      glBegin(GL_POINTS);
        for(j= 0; j < 6; j++)
          {
          m= koi[koffs[nep[i]]+j];
          glVertex3d(xv[m],yv[m],zv[m]);
          }
      glEnd();     
      }
    if(ityp[nep[i]]== 19) 
      {
      glBegin(GL_POINTS);
        for(j= 0; j < 16; j++) 
          {
          m= koi[koffs[nep[i]]+j];
          glVertex3d(xv[m],yv[m],zv[m]);
          }
      glEnd();     
      }
    if(ityp[nep[i]]== 20) 
      {
      glBegin(GL_POINTS);
        for(j= 0; j < 8; j++) 
          {
          m= koi[koffs[nep[i]]+j];
          glVertex3d(xv[m],yv[m],zv[m]);
          }
      glEnd();     
      }
    }
  }  /* Ende iqflag */

return 0;
}

/***********************************************************************
* ri5x88
***********************************************************************/
/***********************************************************************
* hier beginnt Function ri5x88; sie ist gegenueber den aehnlichen
* Funktionen RI588 und RI588I etwas vereinfacht, weil die Double-Arrays
* (noch) nicht gebraucht werden.
*
* ri5x88.c liest z88i5.txt ein
* hier wird File z88i5.txt geoeffnet 
***********************************************************************/
int ri5x88(void)
{
extern FILE *fi5,*fwlo;
extern char ci5[];

extern FR_INT4AY noi;
extern FR_INT4AY noffs;
extern FR_INT4AY ityp;
extern FR_INT4AY nep;

extern FR_INT4   npr,nnp;
extern FR_INT4   MAXPR;

FR_DOUBLE        rdummy,sdummy,tdummy;
FR_INT4          i,idummy,nofold= 0;

char cline[256];

/*----------------------------------------------------------------------
* Einlesen der allgemeinen Strukturdaten
*---------------------------------------------------------------------*/
fgets(cline,256,fi5);
sscanf(cline,PD,&npr);

if(npr >= MAXPR-1)
  {
  wlog88o(MAXPR,LOG_EXMAXPR);
  return(AL_EXMAXPR);
  }

/***********************************************************************
* Einlesen des Lastvektors
***********************************************************************/
nnp= 0;   /* Anzahl der Knoten mit Drucklasten, auch doppelte */
for(i= 1; i <= npr; i++)
  {
  fgets(cline,256,fi5);
  sscanf(cline,PD,&nep[i]); 

/*----------------------------------------------------------------------
* den koinzidenzvektor noi & den zugehoerigen pointervektor noffs
* auffuellen
*---------------------------------------------------------------------*/

/*======================================================================
* Elementtypen 7, 8, 14, 15
*=====================================================================*/
  if(ityp[nep[i]]== 7  || ityp[nep[i]]== 8 ||
     ityp[nep[i]]== 14 || ityp[nep[i]]== 15) 
    {
    if(i== 1)  noffs[1]= 1;
    else       noffs[i]= noffs[i-1] + nofold;
    
    sscanf(cline,PD BPG BPG BPD BPD BPD,&idummy,&rdummy,&sdummy,
    &noi[noffs[i]],&noi[noffs[i]+1],&noi[noffs[i]+2]);  
    
    nnp+=3;
    nofold= 3;
    }

/*======================================================================
* Elementtyp 17
*=====================================================================*/
  if(ityp[nep[i]]== 17) 
    {
    if(i== 1)  noffs[1]= 1;
    else       noffs[i]= noffs[i-1] + nofold;
    
    sscanf(cline,PD BPG BPD BPD BPD,&idummy,&rdummy,
    &noi[noffs[i]],&noi[noffs[i]+1],&noi[noffs[i]+2]); 

    nnp+=3;
    nofold= 3;
    }
          
/*======================================================================
* Elementtyp 16 und 22
*=====================================================================*/
  if(ityp[nep[i]]== 16 || ityp[nep[i]]== 22) 
    {
    if(i== 1)  noffs[1]= 1;
    else       noffs[i]= noffs[i-1] + nofold;
    
    sscanf(cline,PD BPG BPD BPD BPD BPD BPD BPD,
    &idummy,&rdummy,
    &noi[noffs[i]  ], &noi[noffs[i]+1], 
    &noi[noffs[i]+2], &noi[noffs[i]+3], 
    &noi[noffs[i]+4], &noi[noffs[i]+5]); 

    nnp+=6;
    nofold= 6;
    }

/*======================================================================
* Elementtyp 10 u. 21
*=====================================================================*/
  if(ityp[nep[i]]== 10 || ityp[nep[i]]== 21) 
    {
    if(i== 1)  noffs[1]= 1;
    else       noffs[i]= noffs[i-1] + nofold;
    
    sscanf(cline,PD BPG BPG BPG BPD BPD BPD BPD BPD BPD BPD BPD,
    &idummy,&rdummy,&sdummy,&tdummy,
    &noi[noffs[i]  ], &noi[noffs[i]+1], 
    &noi[noffs[i]+2], &noi[noffs[i]+3], 
    &noi[noffs[i]+4], &noi[noffs[i]+5],
    &noi[noffs[i]+6], &noi[noffs[i]+7]); 

    nnp+=8;
    nofold= 8;
    }

/*======================================================================
* Elementtyp 1
*=====================================================================*/
  if(ityp[nep[i]]== 1) 
    {
    if(i== 1)  noffs[1]= 1;
    else       noffs[i]= noffs[i-1] + nofold;
    
    sscanf(cline,PD BPG BPG BPG BPD BPD BPD BPD,
    &idummy,&rdummy,&sdummy,&tdummy,
    &noi[noffs[i]  ], &noi[noffs[i]+1], 
    &noi[noffs[i]+2], &noi[noffs[i]+3]); 

    nnp+=4;
    nofold= 4;
    }

/*======================================================================
* Elementtypen 11 und 12
*=====================================================================*/
  if(ityp[nep[i]]== 11 || ityp[nep[i]]== 12) 
    {
    if(i== 1)  noffs[1]= 1;
    else       noffs[i]= noffs[i-1] + nofold;
    
    sscanf(cline,PD BPG BPG BPD BPD BPD BPD,
    &idummy,&rdummy,&sdummy,
    &noi[noffs[i]  ], &noi[noffs[i]+1], 
    &noi[noffs[i]+2], &noi[noffs[i]+3]); 

    nnp+=4;
    nofold= 4;
    }

/*======================================================================
* Elementtyp 18,19,20,23 und 24
*=====================================================================*/
  if(ityp[nep[i]]== 18 || ityp[nep[i]]== 19 || 
     ityp[nep[i]]== 20 || ityp[nep[i]]== 23 || ityp[nep[i]]== 24) 
    {
    sscanf(cline,PD BPG,&idummy,&rdummy); 
    }


  } /* Ende Schleife ueber alle Flaechenlasten */

wlog88o(0,LOG_EXITRI588);
return (0);
}

/***********************************************************************
* hier beginnt Function mko88
***********************************************************************/
int mko88(void)
{
extern FR_DOUBLEAY xv;
extern FR_DOUBLEAY yv;
extern FR_DOUBLEAY zv;

extern FR_INT4     nkp;

FR_DOUBLE          xmin= +1e+10,xmax= -1e+10;
FR_DOUBLE          ymin= +1e+10;
FR_DOUBLE          zmin= +1e+10;
FR_DOUBLE          xinc,xar,yar,zar,xr,yr,zr;
FR_DOUBLE          yap,xap;

FR_INT4            i;

/*----------------------------------------------------------------------
* Grenzen feststellen, es richtet sich alles nach der X-Achse
*---------------------------------------------------------------------*/
for(i= 1;i <= nkp;i++)
  {
  if(xv[i] < xmin) xmin= xv[i];
  if(xv[i] > xmax) xmax= xv[i];
  if(yv[i] < ymin) ymin= yv[i];
  if(zv[i] < zmin) zmin= zv[i];
  }

xinc= (xmax-xmin)*0.1;
xar = xinc*0.2;
yar=  xar;
zar=  xar;

yap=  xinc*0.05;
xap= yap;

xr= xmin+xinc;
yr= ymin+xinc;
zr= zmin+xinc;

/*----------------------------------------------------------------------
* Koordinatensystem malen
*---------------------------------------------------------------------*/
    glBegin(GL_LINES);
      /* X-Koordinate */
      /* Linie */
      glVertex3d(xmin,ymin,zmin);
      glVertex3d(xr,  ymin,zmin);
      /* Pfeil */
      glVertex3d(xr,    ymin,    zmin);
      glVertex3d(xr-xar,ymin+yap,zmin);
      glVertex3d(xr,    ymin,    zmin);
      glVertex3d(xr-xar,ymin-yap,zmin);
      /* X */
      glVertex3d(xr+xar,ymin+xar,zmin);      
      glVertex3d(xr+3*xar,ymin-xar,zmin);   
      glVertex3d(xr+xar,ymin-xar,zmin);      
      glVertex3d(xr+3*xar,ymin+xar,zmin);   

      /* Y-Koordinate */
      glVertex3d(xmin,ymin,zmin);
      glVertex3d(xmin,yr  ,zmin);
      /* Pfeil */
      glVertex3d(xmin,    yr,    zmin);
      glVertex3d(xmin-xap,yr-yar,zmin);
      glVertex3d(xmin,    yr,    zmin);
      glVertex3d(xmin+xap,yr-yar,zmin);
      /* Y */
      glVertex3d(xmin,    yr+  yar,zmin);    
      glVertex3d(xmin,    yr+2*yar,zmin);  
      glVertex3d(xmin,    yr+2*yar,zmin);  
      glVertex3d(xmin-xar,yr+3*yar,zmin);  
      glVertex3d(xmin,    yr+2*yar,zmin);  
      glVertex3d(xmin+xar,yr+3*yar,zmin);  

      /* Z-Koordinate */
      glVertex3d( xmin,ymin,zmin);
      glVertex3d( xmin,ymin,zr  );
      /* Pfeil */
      glVertex3d(xmin,    ymin,zr    );
      glVertex3d(xmin-xap,ymin,zr-zar);
      glVertex3d(xmin,    ymin,zr    );
      glVertex3d(xmin+xap,ymin,zr-zar);
      /* Z */
      glVertex3d(xmin-xar,ymin+yar,zr+zar);
      glVertex3d(xmin+xar,ymin+yar,zr+zar);
      glVertex3d(xmin+xar,ymin+yar,zr+zar);
      glVertex3d(xmin-xar,ymin-yar,zr+zar);
      glVertex3d(xmin-xar,ymin-yar,zr+zar);
      glVertex3d(xmin+xar,ymin-yar,zr+zar);
    glEnd();

return 0;
}

/***********************************************************************
* hier beginnt Function magp88: Gausspunkte malen
***********************************************************************/
int magp88(void)
{
extern FILE *fwlo;
extern FR_DOUBLEAY xgpo;
extern FR_DOUBLEAY ygpo;
extern FR_DOUBLEAY zgpo;
extern FR_DOUBLEAY xv;

extern FR_INT4AY   kfarbe;

extern FR_DOUBLE   zoogp,fazoo;
extern FR_INT4     nkp,igpanz;

extern GLfloat     rot[];
extern GLfloat     gruen[];
extern GLfloat     blau[];

GLfloat            xps;

FR_DOUBLE          xmin= +1e+10,xmax= -1e+10;

FR_INT4            i;

/*----------------------------------------------------------------------
* Grenzen feststellen
*---------------------------------------------------------------------*/
for(i= 1;i <= nkp;i++)
  {
  if(xv[i] < xmin) xmin= xv[i];
  if(xv[i] > xmax) xmax= xv[i];
  }

/*----------------------------------------------------------------------
* Punktgroesse setzen
*---------------------------------------------------------------------*/
xps= (GLfloat) (zoogp*(xmax-xmin)*fazoo);
glPointSize(xps);

/*----------------------------------------------------------------------
* Gausspunkte malen
*---------------------------------------------------------------------*/
for(i= 1;i <= igpanz;i++)
  {
  glColor3f(rot[kfarbe[i]],gruen[kfarbe[i]],blau[kfarbe[i]]);  
  glBegin(GL_POINTS);
    glVertex3d(xgpo[i],ygpo[i],zgpo[i]);
  glEnd();
  }

return 0;
}
