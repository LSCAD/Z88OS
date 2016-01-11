/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows
* and UNIX OS.
*
* Composed and edited and copyright by 
* Professor Dr.-Ing. Frank Rieg, University of Bayreuth, Germany
*
* eMail: 
* frank.rieg@uni-bayreuth.de
* dr.frank.rieg@t-online.de
* 
* V14.0 January 14, 2011
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
* z88er.c
* 3.8.2011 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>    /* FILE,fclose */
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#include <stdio.h>    /* FILE,fclose */
#endif

/***********************************************************************
* Fuer Windows und GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88r.h>
#include <stdio.h>    /* FILE,fclose */
#endif

/***********************************************************************
* Formate
***********************************************************************/
#define NL "\n"

#ifdef FR_XINT
#define P5D "%5d"
#define P5DB "%5d "
#endif

#ifdef FR_XLONG
#define P5D "%5ld"
#define P5DB "%5ld "
#endif

#ifdef FR_XLOLO
#define P5D "%5lld"
#define P5DB "%5lld "
#endif

#ifdef FR_XDOUB
#define B213E "  %+#13.5lE"
#endif

#ifdef FR_XQUAD
#define B213E "  %+#13.5LE"
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int  wrim88r(FR_INT4,int);
int  wlog88r(FR_INT4,int);
int  wtye88j(FR_INT4,FR_INT4);
int  ale88r(int);
int  lqua88(void);
int  balk88(void);
int  shei88(void);
int  stab88(void);
int  well88(void);
int  ring88(void);
int  qshe88(void);
int  esta88(void);
int  hexa88(void);
int  cshe88(void);
int  ebal88(void);
int  isod88(void);
int  tetr88(void);
int  spur88(void);
int  spla88(void);
int  hpla88(void);
int  apla88(void);
void stop88r(void);
int  forc88(void);  
int  shaq88(void);
int  shad88(void);
int  shaf88(void);
int  shav88(void);

/****************************************************************************
*  globale Variable
****************************************************************************/
/*--------------------------------------------------------------------------
* Files
*-------------------------------------------------------------------------*/
extern FILE *fwlo,*fo4;
extern char co4[];
  
/*--------------------------------------------------------------------------
* Pointer
*-------------------------------------------------------------------------*/
extern FR_DOUBLEAY se;
extern FR_DOUBLEAY u;
extern FR_DOUBLEAY x;
extern FR_DOUBLEAY y;
extern FR_DOUBLEAY z;
extern FR_DOUBLEAY emod;
extern FR_DOUBLEAY rnue;
extern FR_DOUBLEAY qpara;
extern FR_DOUBLEAY riyy;
extern FR_DOUBLEAY eyy;
extern FR_DOUBLEAY rizz;
extern FR_DOUBLEAY ezz;
extern FR_DOUBLEAY rit;
extern FR_DOUBLEAY wt;
extern FR_DOUBLEAY fsum1;
extern FR_DOUBLEAY fsum2;
extern FR_DOUBLEAY fsum3;
extern FR_DOUBLEAY fsum4;
extern FR_DOUBLEAY fsum5;
extern FR_DOUBLEAY fsum6;

extern FR_INT4AY koi;
extern FR_INT4AY ifrei; 
extern FR_INT4AY ioffs;
extern FR_INT4AY koffs;
extern FR_INT4AY ityp;
extern FR_INT4AY ivon_mat;
extern FR_INT4AY ibis_mat;
extern FR_INT4AY ivon_elp;
extern FR_INT4AY ibis_elp; 
extern FR_INT4AY ivon_int;
extern FR_INT4AY ibis_int;   
extern FR_INT4AY intord;

/*--------------------------------------------------------------------------
* Arrays
*-------------------------------------------------------------------------*/
extern FR_DOUBLE f[]; 
extern FR_DOUBLE ul[]; 

extern FR_INT4 mcomp[]; 

/* Diese Arrays werden in HEXA88,LQUA88,QSHE88 und CSHE88 verwendet */

extern FR_DOUBLE xk[], yk[], zk[]; 
extern FR_DOUBLE h[];
extern FR_DOUBLE b[]; 
extern FR_DOUBLE xx[];
extern FR_DOUBLE d[]; 
extern FR_DOUBLE p[]; 

/* fuer Plattenberechnung */
extern FR_DOUBLE be[];                     /* fuer 16-Knoten Platte  */
extern FR_DOUBLE hi[];
extern FR_DOUBLE bbi[];
extern FR_DOUBLE bsv[];
extern FR_DOUBLE dbi[];
extern FR_DOUBLE dsv[];

/*--------------------------------------------------------------------------
* Variable
*-------------------------------------------------------------------------*/
extern FR_DOUBLE emode,rnuee,qparae,riyye,eyye,rizze,ezze,rite,wte;
extern FR_INT4 intore,nel,ktyp;
extern FR_INT4 IDYNMEM,LANG,jpri,ifnili;
extern FR_INT4 ndim,nkp,ne,nfg,mmat,mint,melp,nfgp1,nkoi,ibflag,ipflag;
extern FR_INT4 mxknot,mxfrei,mxfe,kch1,kch2,kch3,iqflag,ihflag;

/***********************************************************************
* hier beginnt z88er
***********************************************************************/
int z88er(void)
{
FR_INT4 i,k,j;

int iret;

/***********************************************************************
* Berechnen der Elementsteifigkeitsmatrizen, Compilation  
***********************************************************************/
wrim88r(0,TX_KNOTENK);
wlog88r(0,LOG_KNOTENK);

if(jpri == 1)
  {
  if(LANG == 1)
    {
    fprintf(fo4,"Ausgabedatei Z88O4.TXT : Knotenkraefte, erzeugt mit Z88R V14OS\n");
    fprintf(fo4,"                         *************\n\n");
    }
  if(LANG == 2)
    {
    fprintf(fo4,"output file Z88O4.TXT : nodal forces, computed by Z88R V14OS\n");
    fprintf(fo4,"                        ************\n\n");
    }
  }

if(ifnili == 0)
  {
  if(LANG == 1)
    {
    fprintf(fo4,"Zunaechst die Knotenkraefte elementweise\n");
    fprintf(fo4,"----------------------------------------\n");
    }
  if(LANG == 2)
    {
    fprintf(fo4,"starting with nodal forces computed for each element\n");
    fprintf(fo4,"----------------------------------------------------\n");
    }
  }

for(k= 1;k <= ne;k++)
  {

/*----------------------------------------------------------------------
*  es ist ityp(k):    1  isoparametrischer hexaeder, linearer ansatz
*                     2  balken
*                     3  scheibe, dreieckig, quadratischer ansatz
*                     4  raeumlicher stab
*                     5  welle
*                     6  torus, dreieckig, linearer ansatz
*                     7  isoparametrische scheibe, quadratischer ansatz
*                     8  isoparametrischer torus , quadratischer ansatz
*                     9  ebenes stabelement 
*                    10  isop. serendipity hexaeder, quadratischer ans.
*                    11  isoparametrische scheibe, kubischer ansatz
*                    12  isoparametrischer torus,  kubischer ansatz 
*                    13  ebenes balkenelement
*                    14  krummlinige dreiecksscheibe, quadr. ansatz
*                    15  krummliniger dreieckstorus, quadr. ansatz
*                    16  krummliniger tetraeder, quadr. ansatz
*                    17  tetraeder, linearer ansatz
*                    18  6-knoten serendipity reissner mindlin platte
*                    19  16-knoten lagrange reissner mindlin platte
*                    20  8-knoten serendipity reissner mindlin platte
*                    21  16-knoten volumenschalenele.
*                    22  12-knoten volumenschalenele.
*                    23  4-knoten ahmad-element
*                    24  6-knoten flache Schale (Schei-Pla)
*---------------------------------------------------------------------*/
/*----------------------------------------------------------------------
* E-modul und Nue feststellen
*---------------------------------------------------------------------*/
for(i = 1;i <= mmat;i++)
  {
  if(k >= ivon_mat[i] && k <= ibis_mat[i])
    {
    emode = emod[i];
    rnuee = rnue[i];
    }
  }

/*----------------------------------------------------------------------
* Integrationsordnung feststellen
*---------------------------------------------------------------------*/
for(i = 1;i <= mint;i++)
  {
  if(k >= ivon_int[i] && k <= ibis_int[i])
    {
    intore= intord[i];
    }
  }

/*----------------------------------------------------------------------
* Elementparameter feststellen
*---------------------------------------------------------------------*/
for(i = 1;i <= melp;i++)
  {
  if(k >= ivon_elp[i] && k <= ibis_elp[i])
    {    
    qparae= qpara[i];

    if(ibflag == 1)

      {
      riyye= riyy[i];
      eyye = eyy[i];
      rizze= rizz[i];
      ezze = ezz[i];
      rite = rit[i];
      wte  = wt[i];
      } 

    if(ipflag != 0 || ihflag != 0)
      {
      riyye= riyy[i];
      } 

    goto L60;
    }
  }

L60:;

/*----------------------------------------------------------------------
* Start 8-Knoten Quader, isoparametrischer linearer Ansatz
*---------------------------------------------------------------------*/
  if(ityp[k]== 1)
    {
    wtye88j(k,1);

/*----------------------------------------------------------------------
* isopara 8-Knoten Hexaeder: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }
            
/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer iso-8-Knoten Hexaeder berechen
*---------------------------------------------------------------------*/
    iret= lqua88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

/*----------------------------------------------------------------------
* Compilation fuer lqua88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 8;
    mxfrei= 3;            
    mxfe  = 24;
    
    forc88();

    if(ifnili == 0)
      {
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = " P5D "     Typ = 8-K Hexaeder",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = " P5D "     type = 8-n hexahedron",k);
        fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
        }
    
      j= 1;
      for(i = 1;i <= 8;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
        j+= 3;   
        }
      }
 
    j= 1;
    for(i = 1;i <= 8;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      j+= 3;   
      }
    
    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-8-Knoten Hexaeder
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start Balkenelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 2)
    {
    wtye88j(k,2);

/*----------------------------------------------------------------------
* Balkenelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]]];
    yk[1] = y [koi[koffs[k]]];
    zk[1] = z [koi[koffs[k]]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
    zk[2] = z [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* Elementsteifigkeitsmatrix fuer Balkenelement berechen
*---------------------------------------------------------------------*/
    balk88();

/*----------------------------------------------------------------------
* Compilation fuer balk88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 6;
    mxfe  = 12;

    forc88();

    if(ifnili == 0)
      {
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = " P5D "     Typ = Balken im Raum",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)\
           F(4)           F(5)           F(6)");
        }
      if(LANG == 2)
      {
        fprintf(fo4,"\nelement # = " P5D "     type = beam in space",k);
        fprintf(fo4,"\nnode         F(1)           F(2)           F(3)\
           F(4)           F(5)           F(6)");
        }
 
      j= 1;
      for(i = 1;i <= 2;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E B213E B213E B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1],f[j+2],f[j+3],f[j+4],f[j+5]);
        j+= 6;   
        }
      }
  
    j= 1;
    for(i = 1;i <= 2;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      fsum4[koi[koffs[k]+i-1]] += f[j+3];
      fsum5[koi[koffs[k]+i-1]] += f[j+4];
      fsum6[koi[koffs[k]+i-1]] += f[j+5];
      j+= 6;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende Balkenelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start Dreieck-Scheibenelement, quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 3)
    {
    wtye88j(k,3);

/*----------------------------------------------------------------------
* Scheibenelement: zutreffende Koordinaten bestimmen 
* die Mittenknoten werden nicht gebraucht
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]  ]];
    yk[1] = y [koi[koffs[k]  ]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
    xk[3] = x [koi[koffs[k]+2]];
    yk[3] = y [koi[koffs[k]+2]];

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer Scheibenelement berechnen
*---------------------------------------------------------------------*/
    iret= shei88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

/*-----------------------------------------------------------------------
* Compilation fuer shei88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;
         
    mxknot= 6;
    mxfrei= 2;
    mxfe  = 12;
            
    forc88();

    if(ifnili == 0)
      {
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = " P5D "     Typ = 6-K Scheibe",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = " P5D "     type = 6-n plane stress",k);
        fprintf(fo4,"\nnode         F(1)           F(2)");
        }
  
      j= 1;
      for(i = 1;i <= 6;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1]);
        j+= 2;   
        }
      }
  
    j= 1;
    for(i = 1;i <= 6;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      j+= 2;   
      }
            
    goto L7000;

/*----------------------------------------------------------------------
* Ende 6-k Scheibenelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start raeumliches Stabelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 4)
    {
    wtye88j(k,4);

/*----------------------------------------------------------------------
* raeumliches Stabelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]]];
    yk[1] = y [koi[koffs[k]]];
    zk[1] = z [koi[koffs[k]]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
    zk[2] = z [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer raeumliches Stabelement berechen
*---------------------------------------------------------------------*/
    stab88();

/*----------------------------------------------------------------------
* Compilation fuer stab88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 3;
    mxfe  = 6;
            
    forc88();
  
    if(ifnili == 0)
      {
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = " P5D "     Typ = Stab im Raum",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = " P5D "     type = truss in space",k);
        fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
        }
  
      j= 1;
      for(i = 1;i <= 2;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
        j+= 3;   
        }
      }

    j= 1;
    for(i = 1;i <= 2;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      j+= 3;   
      }
            
    goto L7000;

/*----------------------------------------------------------------------
* Ende raeumliches Stabelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start Wellenelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 5)
    {
    wtye88j(k,5);

/*----------------------------------------------------------------------
* Wellenelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]]];
    xk[2] = x [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer Wellenelement berechen
*---------------------------------------------------------------------*/
    well88();

/*----------------------------------------------------------------------
* Compilation fuer well88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[ koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[ koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 6;
    mxfe  = 12;

    forc88();
 
    if(ifnili == 0)
      {
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = " P5D "     Typ = Welle",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)\
           F(4)           F(5)           F(6)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = " P5D "     type = shaft",k);
        fprintf(fo4,"\nnode         F(1)           F(2)           F(3)\
           F(4)           F(5)           F(6)");
        }
    
      j= 1;
      for(i = 1;i <= 2;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E B213E B213E B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1],f[j+2],f[j+3],f[j+4],f[j+5]);
        j+= 6;   
        }
      }
  
    j= 1;
    for(i = 1;i <= 2;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      fsum4[koi[koffs[k]+i-1]] += f[j+3];
      fsum5[koi[koffs[k]+i-1]] += f[j+4];
      fsum6[koi[koffs[k]+i-1]] += f[j+5];
      j+= 6;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende Wellenelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start Toruselement, linearer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 6)
    {
    wtye88j(k,6);

/*----------------------------------------------------------------------
* Toruselement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]  ]];
    yk[1] = y [koi[koffs[k]  ]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
    xk[3] = x [koi[koffs[k]+2]];
    yk[3] = y [koi[koffs[k]+2]];
          
/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer Toruselement berechen
*---------------------------------------------------------------------*/
    ring88();

/*----------------------------------------------------------------------
* Compilation fuer ring88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[koi[koffs[k]+1]] -1;
    mcomp[3]= ioffs[koi[koffs[k]+2]] -1;
         
    mxknot= 3;
    mxfrei= 2;
    mxfe  = 6;

    forc88();

    if(ifnili == 0)
      {
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = " P5D "     Typ = 3-K Torus",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = " P5D "     type = 3-n torus",k);
        fprintf(fo4,"\nnode         F(1)           F(2)");
        }
   
      j= 1;
      for(i = 1;i <= 3;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1]);
        j+= 2;   
        }
      }
    
    j= 1;
    for(i = 1;i <= 3;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      j+= 2;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende Toruselement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 8-knoten Scheibe/Torus, isoparametrischer quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 7 || ityp[k]== 8)
    {
    if (ityp[k]== 7)
      {
      wtye88j(k,7);
      ktyp= 2;
      }
    else
      {
      wtye88j(k,8);
      ktyp= 0;
      }

/*----------------------------------------------------------------------
* isopara 8-Knoten Scheibe/Torus: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer iso-8-knoten Scheibe/Tor  berechen
*---------------------------------------------------------------------*/
    iret= qshe88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }
    
/*----------------------------------------------------------------------
* Compilation fuer qshe88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;
         
    mxknot= 8;
    mxfrei= 2;
    mxfe  = 16;
            
    forc88();

    if(ifnili == 0)
      {
      if(ktyp == 2)
        {    
        if(LANG == 1)
          {
          fprintf(fo4,"\nElement # = " P5D "     Typ = 8-K Scheibe",k);
          fprintf(fo4,"\nKnoten       F(1)           F(2)");
          }
        if(LANG == 2)
          {
          fprintf(fo4,"\nelement # = " P5D "     type = 8-n plane stress",k);
          fprintf(fo4,"\nnode         F(1)           F(2)");
          }
         }
      if(ktyp == 0)
        {    
        if(LANG == 1)
          {
          fprintf(fo4,"\nElement # = " P5D "     Typ = 8-K Torus",k);
          fprintf(fo4,"\nKnoten       F(1)           F(2)");
          }
        if(LANG == 2)
          {
          fprintf(fo4,"\nelement # = " P5D "     type = 8-n torus",k);
          fprintf(fo4,"\nnode         F(1)           F(2)");
          }
         }
       
      j= 1;
      for(i = 1;i <= 8;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1]);
        j+= 2;   
        }
      }

    j= 1;
    for(i = 1;i <= 8;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      j+= 2;   
      }
            
    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-8-Knoten Scheibe/Torus
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start ebenes Stabelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 9)
    {
    wtye88j(k,9);

/*----------------------------------------------------------------------
* ebenes Stabelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]  ]];
    yk[1] = y [koi[koffs[k]  ]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer e. Stabelement berechen
*---------------------------------------------------------------------*/
    esta88();

/*----------------------------------------------------------------------
* Compilation fuer esta88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[ koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[ koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 2;
    mxfe  = 4;

    forc88();
  
    if(ifnili == 0)
      {
      if(LANG == 1)
        {  
        fprintf(fo4,"\nElement # = " P5D "     Typ = Stab in der Ebene",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)");
        }
      if(LANG == 2)
        {  
        fprintf(fo4,"\nelement # = " P5D "     type = truss in plane",k);
        fprintf(fo4,"\nnode         F(1)           F(2)");
        }
      
      j= 1;
      for(i = 1;i <= 2;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1]);
        j+= 2;   
        }
      }

    j= 1;
    for(i = 1;i <= 2;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      j+= 2;   
      }

    goto L7000;
    
/*----------------------------------------------------------------------
* Ende ebenes Stabelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 20-Knoten Hexaeder, isoparametrischer quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 10)
    {
    wtye88j(k,10);
 
/*----------------------------------------------------------------------
* isopara 20-Knoten Hexaeder: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 20;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer iso-20-Knoten Hexaeder berechen
*---------------------------------------------------------------------*/
    iret= hexa88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

/*----------------------------------------------------------------------
* Compilation fuer hexa88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 20;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 20;
    mxfrei= 3;
    mxfe  = 60; 

    forc88();

    if(ifnili == 0)
      {
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = " P5D "     Typ = 20-K Hexaeder",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = " P5D "     type = 20-n hexahedron",k);
        fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
        }
     
      j= 1;
      for(i = 1;i <= 20;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
        j+= 3;   
        }
      }

    j= 1;
    for(i = 1;i <= 20;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      j+= 3;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-20-Knoten Hexaeder
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 12-knoten Scheibe/Torus, isoparametrischer kubischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 11 || ityp[k]== 12)
    {
    if (ityp[k]== 11)
      {
      wtye88j(k,11);
      ktyp= 2;
      }
    else
      {
      wtye88j(k,12);
      ktyp= 0;
      }
      
/*----------------------------------------------------------------------
* isopara 12-Knoten Scheibe/Torus: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 12;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer iso-12-Knoten Scheibe/Tor  ber.
*---------------------------------------------------------------------*/
    iret= cshe88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

/*----------------------------------------------------------------------
* Compilation fuer cshe88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 12;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;
         
    mxknot= 12;
    mxfrei= 2;
    mxfe  = 24;
            
    forc88();

    if(ifnili == 0)
      {
      if(ktyp == 2)
        {    
        if(LANG == 1)
          {
          fprintf(fo4,"\nElement # = " P5D "     Typ = 12-K Scheibe",k);
          fprintf(fo4,"\nKnoten       F(1)           F(2)");
          }
        if(LANG == 2)
          {
          fprintf(fo4,"\nelement # = " P5D "     type = 12-n plane stress",k);
          fprintf(fo4,"\nnode         F(1)           F(2)");
          }
        }
      if(ktyp == 0)
        {    
        if(LANG == 1)
          {
          fprintf(fo4,"\nElement # = " P5D "     Typ = 12-K Torus",k);
          fprintf(fo4,"\nKnoten       F(1)           F(2)");
          }
        if(LANG == 2)
          {
          fprintf(fo4,"\nelement # = " P5D "     type = 12-n torus",k);
          fprintf(fo4,"\nnode         F(1)           F(2)");
          }
        }
       
      j= 1;
      for(i = 1;i <= 12;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1]);
        j+= 2;   
        }
      }

    j= 1;
    for(i = 1;i <= 12;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      j+= 2;   
      }
            
    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-12-Knoten Scheibe/Torus
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start ebenes Balkenelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 13)
    {
    wtye88j(k,13);

/*----------------------------------------------------------------------
* Balkenelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    xk[1] = x [koi[koffs[k]]];
    yk[1] = y [koi[koffs[k]]];
    xk[2] = x [koi[koffs[k]+1]];
    yk[2] = y [koi[koffs[k]+1]];
           
/*----------------------------------------------------------------------
* Elementsteifigkeitsmatrix fuer ebenes Balkenelement berechen
*---------------------------------------------------------------------*/
    ebal88();

/*----------------------------------------------------------------------
* Compilation fuer ebal88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    mcomp[1]= ioffs[koi[koffs[k]  ]] -1;
    mcomp[2]= ioffs[koi[koffs[k]+1]] -1;
         
    mxknot= 2;
    mxfrei= 3;
    mxfe  = 6;

    forc88();
    
    if(ifnili == 0)
      {
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = " P5D "     Typ = Balken in der Ebene",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = " P5D "     type = beam in plane",k);
        fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
        }
      
      j= 1;
      for(i = 1;i <= 2;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
        j+= 3;   
        }
      }

    j= 1;
    for(i = 1;i <= 2;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      j+= 3;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende ebenes Balkenelement
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 6-knoten Dreieck-Scheibe/Torus, isop. quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 14 || ityp[k]== 15)
    {
    if (ityp[k]== 14)
      {
      wtye88j(k,14);
      ktyp= 2;
      }
    else
      {
      wtye88j(k,15);
      ktyp= 0;
      }



/*----------------------------------------------------------------------
* iso 6-Knoten Dreieck-Scheibe/Torus: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer iso-6-knoten Scheibe/Tor  berechnen
*---------------------------------------------------------------------*/
    iret= isod88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }
    
/*----------------------------------------------------------------------
* Compilation fuer isod88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;
         
    mxknot= 6;
    mxfrei= 2;
    mxfe  = 12;
            
    forc88();

    if(ifnili == 0)
      {
      if(ktyp == 2)
        {    
        if(LANG == 1)
          {
          fprintf(fo4,"\nElement # = " P5D "     Typ = 6-K isop. Scheibe",k);
          fprintf(fo4,"\nKnoten       F(1)           F(2)");
          }
        if(LANG == 2)
          {
          fprintf(fo4,"\nelement # = " P5D "     type = 6-n isop. plane stress",k);
          fprintf(fo4,"\nnode         F(1)           F(2)");
          }
        }
      if(ktyp == 0)
        {    
        if(LANG == 1)
          {
          fprintf(fo4,"\nElement # = " P5D "     Typ = 6-K isop. Torus",k);
          fprintf(fo4,"\nKnoten       F(1)           F(2)");
          }
        if(LANG == 2)
          {
          fprintf(fo4,"\nelement # = " P5D "     type = 6-n isop. torus",k);
          fprintf(fo4,"\nnode         F(1)           F(2)");
          }
        }
       
      j= 1;
      for(i = 1;i <= 6;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1]);
        j+= 2;   
        }
      }

    j= 1;
    for(i = 1;i <= 6;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      j+= 2;   
      }
            
    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-6-Knoten Dreieck-Scheibe/Torus
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 10-Knoten Tetraeder, isoparametrischer quadratischer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 16)
    {
    wtye88j(k,16);
 
/*----------------------------------------------------------------------
* isopara 10-Knoten Tetraeder: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 10;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer iso-10-Knoten Tetraeder berechen
*---------------------------------------------------------------------*/
    iret= tetr88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

/*----------------------------------------------------------------------
* Compilation fuer tetr88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 10;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 10;
    mxfrei= 3;
    mxfe  = 30; 

    forc88();

    if(ifnili == 0)
      {
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = " P5D "     Typ = 10-K Tetraeder",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = " P5D "     type = 10-n tetrahedron",k);
        fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
        }
      
      j= 1;
      for(i = 1;i <= 10;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
        j+= 3;   
        }
      }

    j= 1;
    for(i = 1;i <= 10;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      j+= 3;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-10-Knoten Tetraeder
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 4-Knoten Tetraeder, lineaer Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 17)
    {
    wtye88j(k,17);
 
/*----------------------------------------------------------------------
* 4-Knoten Tetraeder: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 4;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer 4-Knoten Tetraeder berechen
*---------------------------------------------------------------------*/
    iret= spur88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

/*----------------------------------------------------------------------
* Compilation fuer spur88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 4;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 4;
    mxfrei= 3;
    mxfe  = 12; 

    forc88();

    if(ifnili == 0)
      {
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = " P5D "     Typ = 4-K Tetraeder",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = " P5D "     type = 4-n tetrahedron",k);
        fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
        }
      
      j= 1;
      for(i = 1;i <= 4;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
        j+= 3;   
        }
      }

    j= 1;
    for(i = 1;i <= 4;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];

      j+= 3;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 4-Knoten Tetraeder
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 6-Knoten Reissner- Mindlin Platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 18)
    {
    wtye88j(k,18);

/*----------------------------------------------------------------------
* 6-Knoten Plattenelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }
          
/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer 6-Knoten Plattenelement berechen
*---------------------------------------------------------------------*/
    iret= spla88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

/*----------------------------------------------------------------------
* Compilation fuer spla88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;
         
    mxknot= 6;
    mxfrei= 3;
    mxfe  = 18;
         
    forc88();
    
    if(ifnili == 0)
      {
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = " P5D "     Typ = 6-K Mindlin- Platte",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = " P5D "     type = 6-n Mindlin plate",k);
        fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
        }
    
      j= 1;
      for(i = 1;i <= 6;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
        j+= 3;   
        }
      }

    j= 1;
    for(i = 1;i <= 6;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      j+= 3;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 6-Knoten Reissner- Mindlin Platte
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 16-Knoten Reissner Mindlin Platte, kubischer Lagrange Ansatz
*---------------------------------------------------------------------*/
  else if(ityp[k]== 19)
    {
    wtye88j(k,19);
 
/*----------------------------------------------------------------------
* 16-Knoten Platte: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 16;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer 16-Knoten Platte berechen
*---------------------------------------------------------------------*/
    iret= hpla88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

/*----------------------------------------------------------------------
* Compilation fuer hpla88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 16;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 16;
    mxfrei= 3;
    mxfe  = 48; 

    forc88();

    if(ifnili == 0)
      {
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = " P5D "     Typ = 16-K Mindlin Platte",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = " P5D "     type = 16-n Mindlin plate",k);
        fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
        }
      
      j= 1;
      for(i = 1;i <= 16;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
        j+= 3;   
        }
      }

    j= 1;
    for(i = 1;i <= 16;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      j+= 3;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 16-Knoten Lagrange Reissner Mindlin Platte
*---------------------------------------------------------------------*/
    }

/*----------------------------------------------------------------------
* Start 8-Knoten Reissner- Mindlin Serendipity Platte
*---------------------------------------------------------------------*/
  else if(ityp[k]== 20)
    {
    wtye88j(k,20);

/*----------------------------------------------------------------------
* 8-Knoten Plattenelement : zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      }
          
/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer 8-Knoten Plattenelement berechen
*---------------------------------------------------------------------*/
    iret= apla88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

/*----------------------------------------------------------------------
* Compilation fuer apla88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;
         
    mxknot= 8;
    mxfrei= 3;
    mxfe  = 24;
         
    forc88();
    
    if(ifnili == 0)
      {
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = " P5D "     Typ = 8-K Mindlin- Platte",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = " P5D "     type = 8-n Mindlin plate",k);
        fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
        }
    
      j= 1;
      for(i = 1;i <= 8;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
        j+= 3;   
        }
      }

    j= 1;
    for(i = 1;i <= 8;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      j+= 3;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 8-Knoten Reissner- Mindlin Serendipity Platte
*---------------------------------------------------------------------*/

    }

/*----------------------------------------------------------------------
* Start 16-Knoten Volumenschalenelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 21)
    {
    wtye88j(k,21);
 
/*----------------------------------------------------------------------
* 16-Knoten Vol.Scha.ele: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 16;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer 16-Knoten Vol.Scha.ele berechen
*---------------------------------------------------------------------*/
    iret= shaq88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

/*----------------------------------------------------------------------
* Compilation fuer shaq88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 16;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 16;
    mxfrei=  3;
    mxfe  = 48; 

    forc88();

    if(ifnili == 0)
      {
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = " P5D "     Typ = 16-K Schale",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = " P5D "     type = 16-n shell",k);
        fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
        }

      j= 1;
      for(i = 1;i <= 16;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
        j+= 3;   
        }
      }

    j= 1;
    for(i = 1;i <= 16;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      j+= 3;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-16-Knoten Volumenschalenele.
*---------------------------------------------------------------------*/
  }

/*----------------------------------------------------------------------
* Start 12-Knoten Volumenschalenelement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 22)
    {
    wtye88j(k,22);
 
/*----------------------------------------------------------------------
* 12-Knoten Vol.Scha.ele: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 12;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer 12-Knoten Vol.Scha.ele berechen
*---------------------------------------------------------------------*/
    iret= shad88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

/*----------------------------------------------------------------------
* Compilation fuer shad88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 12;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot= 12;
    mxfrei=  3;
    mxfe  = 36; 

    forc88();

    if(ifnili == 0)
      {
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = " P5D "     Typ = 12-K Schale",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = " P5D "     type = 12-n shell",k);
        fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
        }
      
      j= 1;
      for(i = 1;i <= 12;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1],f[j+2]);
        j+= 3;   
        }
      }

    j= 1;
    for(i = 1;i <= 12;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      j+= 3;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende isopara-12-Knoten Volumenschalenele.
*---------------------------------------------------------------------*/
  }
 
/*----------------------------------------------------------------------
* Start 8-Knoten Schalenlement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 23)
    {
    wtye88j(k,23);

    ktyp= 2; /* zum Ansteuern von QSHE88 */
 
/*----------------------------------------------------------------------
* 8-Knoten Schale: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer 8-Knoten Schale berechen
*---------------------------------------------------------------------*/
    iret= shav88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

/*----------------------------------------------------------------------
* Compilation fuer shav88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 8;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot=  8;
    mxfrei=  6;
    mxfe  = 48; 

    forc88();

    if(ifnili == 0)
      {
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = " P5D "     Typ = 8-K Schale",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = " P5D "     type = 8-n shell",k);
        fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
        }
      
      j= 1;
      for(i = 1;i <= 8;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E B213E B213E B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1],f[j+2],f[j+3],f[j+4],f[j+5]);
        j+= 6;   
        }
      }
  
    j= 1;
    for(i = 1;i <= 8;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      fsum4[koi[koffs[k]+i-1]] += f[j+3];
      fsum5[koi[koffs[k]+i-1]] += f[j+4];
      fsum6[koi[koffs[k]+i-1]] += f[j+5];
      j+= 6;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 8-Knoten Schale
*---------------------------------------------------------------------*/
    }
    
/*----------------------------------------------------------------------
* Start 6-Knoten Schalenlement
*---------------------------------------------------------------------*/
  else if(ityp[k]== 24)
    {
    wtye88j(k,24);

    ktyp= 2; /* zum Ansteuern von ISOD88 */
 
/*----------------------------------------------------------------------
* 6-Knoten Schale: zutreffende Koordinaten bestimmen 
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      {
      xk[i] = x [koi[koffs[k]+i-1]];
      yk[i] = y [koi[koffs[k]+i-1]];
      zk[i] = z [koi[koffs[k]+i-1]];
      }

/*----------------------------------------------------------------------
* nun Elementsteifigkeitsmatrix fuer 6-Knoten Schale berechen
*---------------------------------------------------------------------*/
    iret= shaf88();
    if(iret != 0)
      {
      wlog88r(0,LOG_JACNEG);
      fclose(fwlo);
      ale88r(iret);
      stop88r();
      }

/*----------------------------------------------------------------------
* Compilation fuer shaf88, kompakte Speicherung mit Pointervektor
*---------------------------------------------------------------------*/
    for(i = 1;i <= 6;i++)
      mcomp[i]= ioffs[ koi[koffs[k]+i-1]] -1;

    mxknot=  6;
    mxfrei=  6;
    mxfe  = 36; 

    forc88();

    if(ifnili == 0)
      {
      if(LANG == 1)
        {
        fprintf(fo4,"\nElement # = " P5D "     Typ = 6-K Schale",k);
        fprintf(fo4,"\nKnoten       F(1)           F(2)           F(3)");
        }
      if(LANG == 2)
        {
        fprintf(fo4,"\nelement # = " P5D "     type = 6-n shell",k);
        fprintf(fo4,"\nnode         F(1)           F(2)           F(3)");
        }
      
      j= 1;
      for(i = 1;i <= 6;i++)
        {
        fprintf(fo4,NL P5DB B213E B213E B213E B213E B213E B213E,
        koi[koffs[k]+i-1],f[j],f[j+1],f[j+2],f[j+3],f[j+4],f[j+5]);
        j+= 6;   
        }
      }
  
    j= 1;
    for(i = 1;i <= 6;i++)
      {
      fsum1[koi[koffs[k]+i-1]] += f[j];
      fsum2[koi[koffs[k]+i-1]] += f[j+1];
      fsum3[koi[koffs[k]+i-1]] += f[j+2];
      fsum4[koi[koffs[k]+i-1]] += f[j+3];
      fsum5[koi[koffs[k]+i-1]] += f[j+4];
      fsum6[koi[koffs[k]+i-1]] += f[j+5];
      j+= 6;   
      }

    goto L7000;

/*----------------------------------------------------------------------
* Ende 6-Knoten Schale
*---------------------------------------------------------------------*/
    }
    

L7000:;
if(ifnili == 0) fprintf(fo4,"\n");
  
/***********************************************************************
* Ende der Schleife ueber alle Elemente
***********************************************************************/
  }

/***********************************************************************
* Schleife ueber alle Knoten
***********************************************************************/
if(jpri == 1) 
  {
  if(ifnili == 0) fprintf(fo4,"\n");

  if(LANG == 1)
    {
    fprintf(fo4,"Die aufsummierten Knotenkraefte je Knoten\n");
    fprintf(fo4,"-----------------------------------------\n\n");
    fprintf(fo4,"Knoten       F(1)           F(2)           F(3)\
           F(4)           F(5)           F(6)\n\n");
    }
  if(LANG == 2)
    {
    fprintf(fo4,"the nodal sums for each node\n");
    fprintf(fo4,"----------------------------\n");
    fprintf(fo4,"  node       F(1)           F(2)           F(3)\
           F(4)           F(5)           F(6)\n\n");
    }

  for(i = 1;i <= nkp;i++)
    {
    fprintf(fo4,P5DB B213E B213E B213E B213E B213E B213E NL,
    i,fsum1[i],fsum2[i],fsum3[i],fsum4[i],fsum5[i],fsum6[i]);
    }
  }

/*----------------------------------------------------------------------
* Ende Z88ER
*---------------------------------------------------------------------*/
wrim88r(0,TX_EXITZ88E);
wlog88r(0,LOG_EXITZ88E);

return(0);
}

