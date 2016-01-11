/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the UNIX and
* the Windows OS.
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
* mc588n: zweidimensional: Typ 20 --> Typ 19
* 21.7.2011 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88n.h>
#include <stdio.h>   
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88n.h>
#include <stdio.h>   
#endif

/***********************************************************************
* Formatbeschreiber
***********************************************************************/	
#ifdef FR_XINT
#define PDB "%d "
#define PD "%d"
#define PD5B "%5d "
#define PD5 "%5d"
#define PD2B "%2d "
#define PD2 "%2d"
#endif

#ifdef FR_XLONG
#define PDB "%ld "
#define PD "%ld"
#define PD5B "%5ld "
#define PD5 "%5ld"
#define PD2B "%2ld "
#define PD2 "%2ld"
#endif

#ifdef FR_XLOLO
#define PDB "%lld "
#define PD "%lld"
#define PD5B "%5lld "
#define PD5 "%5lld"
#define PD2B "%2lld "
#define PD2 "%2lld"
#endif

#ifdef FR_XDOUB
#define PFB "%lf "
#define PF "%lf"
#define PE13B "%+#13.5lE "
#define PE13 "%+#13.5lE"
#endif

#ifdef FR_XQUAD
#define PFB "%Lf "
#define PF "%Lf"
#define PE13B "%+#13.5LE "
#define PE13 "%+#13.5LE"
#endif

/***********************************************************************
* Functions
***********************************************************************/
FR_DOUBLE cpkl88(char cmode,FR_INT4 jel);
FR_DOUBLE ikl88(char cmode,FR_DOUBLE xinc,FR_INT4 j,FR_INT4 jmax);
int fq88(FR_DOUBLE r,FR_DOUBLE s);
int wrim88n(FR_INT4,int);
int wlog88n(FR_INT4,int);
 
/***********************************************************************
* hier beginnt Function mc588n
***********************************************************************/
int mc588n(void)
{
extern FILE *fi1,*fwlo;

/*--------------------------------------------------------------------------
* globale Pointer
*-------------------------------------------------------------------------*/
extern FR_DOUBLEAY x;
extern FR_DOUBLEAY y;
extern FR_DOUBLEAY xss;
extern FR_DOUBLEAY yss;

extern FR_INT4AY koima;
extern FR_INT4AY join; 
extern FR_INT4AY koiss;
extern FR_INT4AY ioffss;
extern FR_INT4AY koffss;
extern FR_INT4AY jel;
extern FR_INT4AY iel;

extern FR_CHARAY cjmode;
extern FR_CHARAY cimode;

/*--------------------------------------------------------------------------
* globale Arrays
*-------------------------------------------------------------------------*/
extern FR_DOUBLE h[];

extern FR_INT4 jklsta[];
extern FR_INT4 iklsta[];

/*--------------------------------------------------------------------------
* globale Variable
*-------------------------------------------------------------------------*/
extern FR_DOUBLE epsx,epsy;
extern FR_INT4 MAXSE,MAXAN,LANG;
extern FR_INT4 ness,ndim,kflag,ifrei,ityp,idyn;

/*--------------------------------------------------------------------------
* lokale Arrays
*-------------------------------------------------------------------------*/
FR_INT4 koilo[20];

/*--------------------------------------------------------------------------
* lokale Variable
*-------------------------------------------------------------------------*/
FR_DOUBLE xinc,yinc,r,s,xsp,ysp,x4,y4,xmax,xmin,xist,ymax,ymin,yist,rx,py;
FR_INT4 index,nkp,ne,nfg,koimax,k,le,je,ie,jmax,imax,iss,isum;
FR_INT4 j,i,m,joffs,icount,macoun,jndex,kk,min,max,n;

/*--------------------------------------------------------------------------
* Start Function
*-------------------------------------------------------------------------*/
wlog88n(0,LOG_SMC588N);
if(idyn == 2) wrim88n(0,TX_BERKOOR);

/*--------------------------------------------------------------------------
* Koordinaten berechnen
*-------------------------------------------------------------------------*/
for(iss = 1;iss <= ness;iss++)
  {        
  if(idyn == 2) wrim88n(iss,TX_SUPERELE);
  
/*----------------------------------------------------------------------
* max. Anzahl Knoten/Elementseite, ioffs & incremente
*---------------------------------------------------------------------*/ 
  jmax= jel[iss]*3+1;
  imax= iel[iss]*3+1;
           
  xinc= cpkl88(cjmode[iss],jel[iss]);
  yinc= cpkl88(cimode[iss],iel[iss]);

/*----------------------------------------------------------------------
* Offsetvektor berechnen
*---------------------------------------------------------------------*/
  if(iss == 1)
    ioffss[1]= 1;
  else
    ioffss[iss]= ioffss[iss-1] + (jel[iss-1]*3+1)*(iel[iss-1]*3+1);
                    
/*----------------------------------------------------------------------
* Berechnen der Formfunktionen fuer die komplette "Matrix"
* dabei ist a1,1 <=> Knoten 1 des Superelements unten links 
* und a imax,jmax <=> Knoten 3 des Superelements oben rechts
* beginnend bei a1,1 folgt a2,1, a3,1, ..., dann a2,1, a2,2 ..
*---------------------------------------------------------------------*/
  n= 0;
  for(j = 1;j <= jmax;j++)
    {
    r= ikl88(cjmode[iss],xinc,j,jmax);

    for(i = 1;i <= imax;i++)
      {
      n++;
      s= ikl88(cimode[iss],yinc,i,imax);

      /* formfunktionen berechnen */

      fq88(r,s);

      /* echte Koordinaten aus nat. Koordinaten & Formfunktionen */

      xsp= 0.;
      ysp= 0.;

      for(m = 1;m <= 8;m++)
        {
        index= koiss[koffss[iss]+m-1];
        xsp= xsp + h[m] * xss[index];
        ysp= ysp + h[m] * yss[index];
        }

      /* in "Matrix" x und y speichern */

      index= (ioffss[iss]-1) + i+imax*(j-1);

      if(idyn == 2) x[index]= xsp;
      if(idyn == 2) y[index]= ysp;
      }
    }
  } 
if(idyn == 1) 
  {
  MAXSE= index + 2;
  return(0);
  }

/***********************************************************************
* Koinzidenzvektor koima fuer die Superelemente aufstellen
***********************************************************************/
wrim88n(0,TX_BERKOIN);
wlog88n(0,LOG_BERKOIN);

icount= 0;
macoun= 0;
for(iss = 1;iss <= ness;iss++)                        /* 690 */
  {
  wrim88n(iss,TX_SUPERELE);
  jmax= jel[iss]*3 + 1;
  imax= iel[iss]*3 + 1;
  joffs= MAXAN*(iss-1);
          
  if(iss == 1) 
    {
/*----------------------------------------------------------------------
*   1.Element braucht Sonderbehandlung
*---------------------------------------------------------------------*/
    for(j = 1;j <= jmax;j++)
      {
      for(i = 1;i <= imax;i++)
        {
        icount++;
        macoun++;
        koima[icount]= macoun;
        }
      }
    }
  else
    {
/*-----------------------------------------------------------------------
*   Superelement 2 bis Ende
*---------------------------------------------------------------------*/
    for(j = 1;j <= jmax;j++)
      {
      for(i = 1;i <= imax;i++)
        {
        icount++;
        for(kk = 1;kk <= MAXAN;kk++)
          {
/*======================================================================
*           Schleife ueber die Nachbar-Superelemente
*=====================================================================*/ 
          jndex= join[joffs+kk];
          if(jndex > 0 && jndex < iss)
            {
            /* nur wenn Nachbar > 0 und < als aktuelles Superele */     
            min= ioffss[jndex];
            max= ioffss[jndex+1] -1;

            for(index = min;index <= max;index++)
              {
              xmax= x[index] + epsx;
              xmin= x[index] - epsx;
              ymax= y[index] + epsy;
              ymin= y[index] - epsy;
              xist= x[icount];
              yist= y[icount];
              if(xist >= xmin && xist <= xmax &&
                 yist >= ymin && yist <= ymax)
                {
                /* alten Knoten gefunden,dessen Index zuweisen */
                koima[icount]= koima[index];
                goto L670;
                }
              }
            }
          }
        /* neuer Knoten; macoun incrementieren */
        macoun++;
        koima[icount]= macoun;

        L670:;
        }
      }
    }
  }
/*----------------------------------------------------------------------
* ende if <1.Element> oder <2.bis letztes Element>
*---------------------------------------------------------------------*/

/***********************************************************************
* Beschreiben von Z88I1.TXT
***********************************************************************/
/*----------------------------------------------------------------------
* 1.Zeile
*---------------------------------------------------------------------*/
wrim88n(0,TX_WRII1);
wlog88n(0,LOG_WRII1);

nkp= macoun;

ne= 0;
for(i = 1;i <= ness;i++)
  {
  ne= ne + jel[i]*iel[i];
  }

nfg= 3*nkp;

fprintf(fi1,PD5B PD5B PD5B PD5B PD5 " Z88I1.TXT <-- Z88N V15.0\n",
  ndim,nkp,ne,nfg,kflag);
        
/*----------------------------------------------------------------------
* Koordinaten
*---------------------------------------------------------------------*/
koimax= 1;

for(i = 1;i <= icount;i++)
  {
  if(i == 1)
    {
    if(FR_FABS(x[1]) < 1e-21)
      x4= 0.;
    else
      x4= x[1];
    if(FR_FABS(y[1]) < 1e-21)
      y4= 0.;
    else
      y4= y[1];
    if(kflag == 1)
      {
      rx= FR_SQRT(x4*x4 + y4*y4);
      py= FR_ATAN2(y4,x4)*180/3.141593;
      x4= rx;
      y4= py;
      }
    fprintf(fi1,PD5B PD2B PE13B PE13 "\n",koimax,ifrei,x4,y4);
    }
  else
    {
    if(koima[i] > koimax)
      {
      koimax= koima[i];
      if(FR_FABS(x[i]) < 1e-21)
        x4= 0.;
      else
        x4= x[i];
      if(FR_FABS(y[i]) < 1e-21)
        y4= 0.;
      else
        y4= y[i];
      if(kflag == 1)
        {
        rx= FR_SQRT(x4*x4 + y4*y4);
        py= FR_ATAN2(y4,x4)*180/3.141593;
        x4= rx;
        y4= py;
        }
      fprintf(fi1,PD5B PD2B PE13B PE13 "\n",koimax,ifrei,x4,y4);
      }
    }
  }
              
/*-----------------------------------------------------------------------
* Elementdaten & Koinzidenzliste
*---------------------------------------------------------------------*/
k= 0;
        
for(iss = 1;iss <= ness;iss++)
  {
  jmax= jel[iss]*3+1;
  imax= iel[iss]*3+1;

  for(je = 1;je <= jel[iss];je++)
    {
    for(ie = 1;ie <= iel[iss];ie++)
      {
      k++;
      for(le = 1;le <= 16;le++)
        {
        j= jklsta[le] + 3*(je-1);
        i= iklsta[le] + 3*(ie-1);
        index= (ioffss[iss]-1) + i+imax*(j-1);
        koilo[le]= koima[index];
        }

        fprintf(fi1,PD5B PD5 "\n",k,ityp);
        fprintf(fi1,PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5B
 PD5B PD5B PD5B PD5B PD5B PD5B PD5B PD5 "\n",
        koilo[ 1],koilo[ 2],koilo[ 3],koilo[ 4],
        koilo[ 5],koilo[ 6],koilo[ 7],koilo[ 8],
        koilo[ 9],koilo[10],koilo[11],koilo[12],
        koilo[13],koilo[14],koilo[15],koilo[16]);
      }
    }
  }
    
/*-----------------------------------------------------------------------
* normales Ende
*---------------------------------------------------------------------*/
return(0);
}
