/***********************************************************************
* 
*               *****   ***    ***
*                  *   *   *  *   *
*                 *     ***    ***
*                *     *   *  *   *
*               *****   ***    ***
*
* A FREE Finite Elements Analysis Program in ANSI C for the Windows &
* UNIX OS.
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
* Z88 should compile and run under any UNIX OS and Windows.
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
* Diese Compilerunit enthaelt:
* scal88i
* siccg88
* part88
* cixa88
* sorcg88
* Konjugierte Gradienten mit entweder 
* - partieller Cholesky- Zerlegung oder
* - Vorkonditionierung mit SSOR
* basiert gedanklich auf FORTRAN-Programmen von H.R.Schwarz,Uni Zuerich
* 2.1.2010 Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>
#endif

/***********************************************************************
* Fuer Windows
***********************************************************************/
#ifdef FR_WIN
#include <z88r.h>
#endif

/***********************************************************************
* Fuer Windows und GTK+
***********************************************************************/
#ifdef FR_GTKWIN
#include <z88r.h>
#endif

/***********************************************************************
*  Functions
***********************************************************************/
int wlog88r(FR_INT4,int);
int wrim88r(FR_INT4,int);
int cixa88(void);
int part88(void);

/***********************************************************************
* hier beginnt Function scal88i
***********************************************************************/
int scal88i(void)
{
extern FR_DOUBLEAY GS;
extern FR_DOUBLEAY rs;
extern FR_DOUBLEAY fak;

extern FR_INT4AY ip;
extern FR_INT4AY iez;

extern FR_INT4 nfg;

FR_INT4 i,j;

/*----------------------------------------------------------------------
* Start Function
*---------------------------------------------------------------------*/

/***********************************************************************
* Scalierungsfaktoren berechnen und rechte Seite umrechnen
***********************************************************************/
for(i = 1;i <= nfg;i++)
  {
  if(GS[ip[i]] <= 0.) 
    {
    wlog88r(i,LOG_DIAGNULL);
    return(AL_DIAGNULL);
    }

  fak[i]= 1. / FR_SQRT(GS[ip[i]]);
  GS[ip[i]]= 1.0;
  rs[i]*= fak[i];

  if(i == 1) continue;
  
  for(j = ip[i-1]+1;j <= ip[i]-1;j++)
    GS[j]*= fak[i] * fak[iez[j]];

  }

return(0);
}
 
/***********************************************************************
* Function siccg88 loest Gleichungssysteme mit dem Konjugierte 
* Gradienten Verfahren und partieller Cholesky- Zerlegung, ruft
* part88 und cixa88 auf
***********************************************************************/ 
int siccg88(void)
{
extern FR_DOUBLEAY GS;
extern FR_DOUBLEAY CI;
extern FR_DOUBLEAY rs;
extern FR_DOUBLEAY xi;
extern FR_DOUBLEAY xa;
extern FR_DOUBLEAY v;
extern FR_DOUBLEAY pk;
extern FR_DOUBLEAY zz;

extern FR_INT4AY ip;
extern FR_INT4AY iez;

extern FR_DOUBLE rp,rpalpha,eps;
extern FR_INT4 nfg,maxit;

FR_DOUBLE sumnen,sumzae,q,rho0,rho1,e;

FR_INT4 j,i,k;

/*----------------------------------------------------------------------
* Start: partielle Cholesky- Zerlegung durchfuehren
*---------------------------------------------------------------------*/
rp= rpalpha;

for(k= 1;k <= 1000; k++)
  {
  wrim88r(k,TX_PART88);
  if(part88() == 0) break;
  else
    {  
    if(rp <= 1e-10) rp= 0.00005;
    rp+= rp;
   }
  }

wrim88r(0,TX_CR);

/*----------------------------------------------------------------------
* Vektoren v,xi,xa,pk und zz auf Null setzen
*---------------------------------------------------------------------*/
for(i= 1; i <= nfg; i++)
  {  
  xi[i]= -rs[i];
  v[i] = 0.;
  xa[i]= 0.;
  pk[i]= 0.;
  zz[i]= 0.;
  }

/*----------------------------------------------------------------------
* Iterationsschleife
*---------------------------------------------------------------------*/
for(k= 1; k <= maxit; k++)
  {
  wrim88r(k,TX_ITERA);

/*======================================================================
* Loese Gleichungssystem CI * CIt * xa = xi
*=====================================================================*/ 
  cixa88(); 

/*======================================================================
* r x rho
*=====================================================================*/
  sumzae= 0.;
  for(i= 1; i <= nfg; i++)
    sumzae+= xi[i] * xa[i];
    
/*======================================================================
* Sonderfall k= 1
*=====================================================================*/ 
  if(k == 1)
    {
    rho0= sumzae*eps;
    e= 0.;
    }
  else
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* e(k-1)= r(k-1) x rho(k-1) / r(k-2) x rho(k-2)
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    e= sumzae/rho1;

/*======================================================================
* Residuum erreicht ? Auf Wiedersehen.
*=====================================================================*/ 
  if(sumzae <= rho0)
    {
    for(i= 1; i <= nfg; i++)
      rs[i]= v[i];
    wrim88r(0,TX_JACOOK);
    wlog88r(k,LOG_ITERA);
    return 0;
    }

/*======================================================================
* ansonsten weitermachen
*=====================================================================*/ 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* g(k) = e(k-1) x g(k-1) - rho(k-1)
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for(i= 1; i <= nfg; i++)
    pk[i]= e*pk[i] - xa[i];
    
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Hilfsvektor zz(k)= A x g(k)
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  zz[1]= GS[1]*pk[1];

  for(i= 2; i <= nfg; i++)
    {
    zz[i]= GS[ip[i]] * pk[i];
    for(j= ip[i-1]+1; j <= ip[i]-1; j++)
      {
      zz[i]     += GS[j] * pk[iez[j]];
      zz[iez[j]]+= GS[j] * pk[i];
      }
    }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Nenner g(k) x zz(k) = g(k) x (A x g(k))
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  sumnen= 0.;
  for(i= 1; i <= nfg; i++)
    sumnen+= pk[i] * zz[i];

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* qk= r(k-1) x rho(k-1) / [g(k) x (A x g(k))]
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  q= sumzae/sumnen;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* v(k)= v(k-1) + qk x g(k)
* r(k)= r(k-1) + qk x (A x g(k))
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for(i= 1; i <= nfg; i++) 
    {
    v [i]+= q * pk[i];
    xi[i]+= q * zz[i];
    }   

  rho1= sumzae;
  }

/*----------------------------------------------------------------------
* Residuum nicht erreicht - auch auf Wiedersehen.
*---------------------------------------------------------------------*/
wrim88r(0,TX_JACONOTOK);
wlog88r((k-1),LOG_ITERA);

for(i= 1; i <= nfg; i++)
  rs[i]= v[i];

return(0);
}

/***********************************************************************
* Function part88 fuehrt die partieller Cholesky- Zerlegung aus
***********************************************************************/ 
int part88(void)
{
extern FR_DOUBLEAY GS;
extern FR_DOUBLEAY CI;

extern FR_INT4AY ip;
extern FR_INT4AY iez;

extern FR_DOUBLE rp;
extern FR_INT4 nfg;

FR_DOUBLE facto;

FR_INT4 j,i,k,l;

/*----------------------------------------------------------------------
* Start Function
*---------------------------------------------------------------------*/
facto= 1./(1.+rp);

CI[1]= GS[1];

for(i= 2; i <= nfg; i++)
  {
  CI[ip[i]]= GS[ip[i]];
  for(j = ip[i-1]+1; j <= ip[i]-1; j++)
    CI[j]= GS[j]*facto;
  }

for(i= 2; i <= nfg; i++)
  {
  for(j= ip[i-1]+1; j <= ip[i]-1; j++)
    {
    CI[j]= CI[j] / CI[ip[iez[j]]];
    for(k= j+1; k <= ip[i]; k++)
      {
      for(l= ip[iez[k]-1]+1; l <= ip[iez[k]]; l++)
        {
        if(iez[l] > iez[j]) goto L40;
        if(iez[l] < iez[j]) continue;
        CI[k]= CI[k] - CI[j] * CI[l];
        goto L40;
        }
      L40:;
      }
    }
  if(CI[ip[i]] < 1e-6) return 1;
  CI[ip[i]]= FR_SQRT(CI[ip[i]]);
  }

/*----------------------------------------------------------------------
* alles in Ordnung
*---------------------------------------------------------------------*/
return 0;   /* alles paletti */
}

/***********************************************************************
* Function cixa88 loest Gleichungssysteme CI * CIt * xa = pk
***********************************************************************/ 
int cixa88(void)
{
extern FR_DOUBLEAY CI;
extern FR_DOUBLEAY xa;
extern FR_DOUBLEAY xi;

extern FR_INT4AY ip;
extern FR_INT4AY iez;

extern FR_INT4 nfg;

FR_DOUBLE sum;

FR_INT4 j,k;

/*----------------------------------------------------------------------
* Start Function
*---------------------------------------------------------------------*/
xa[1]= xi[1];

for(k= 2; k <= nfg; k++)
  {
  sum= 0.;
  for(j= ip[k-1]+1; j <= ip[k]-1; j++)
    sum+= CI[j] * xa[iez[j]];
  xa[k]= (xi[k]-sum)/CI[ip[k]];
  }

for(k= nfg; k >= 2; k--)
  {
  xa[k]/= CI[ip[k]];
  for(j= ip[k-1]+1; j <= ip[k]-1; j++)
    xa[iez[j]]= xa[iez[j]] - CI[j] * xa[k]; 
  }

return 0;
}

/***********************************************************************
* Function sorcg88 loest Gleichungssysteme mit dem Konjugierte 
* Gradienten Verfahren und SSOR- Vorkonditionierung
***********************************************************************/ 
int sorcg88(void)
{
extern FR_DOUBLEAY GS;
extern FR_DOUBLEAY rs;
extern FR_DOUBLEAY xi;
extern FR_DOUBLEAY xa;
extern FR_DOUBLEAY v;
extern FR_DOUBLEAY pk;
extern FR_DOUBLEAY zz;

extern FR_INT4AY ip;
extern FR_INT4AY iez;

extern FR_DOUBLE rp,rpomega,eps;
extern FR_INT4 nfg,maxit;

FR_DOUBLE sumnen,sumzae,q,rho0,rho1,e;

FR_INT4 j,i,k;

/*----------------------------------------------------------------------
* Vektoren v,xi,xa,pk und zz auf Null setzen
*---------------------------------------------------------------------*/
rp= rpomega;

for(i= 1; i <= nfg; i++)
  {  
  xi[i]= -rs[i];
  v[i] = 0.;
  xa[i]= 0.;
  pk[i]= 0.;
  zz[i]= 0.;
  }

/*----------------------------------------------------------------------
* Iterationsschleife
*---------------------------------------------------------------------*/
for(k= 1; k <= maxit; k++)
  {
  wrim88r(k,TX_ITERA);

/*======================================================================
* Vorkonditionierung
*=====================================================================*/ 
  xa[1]= xi[1];

  for(i= 2; i <= nfg; i++)
    {
    sumzae= 0.; 
    for(j= ip[i-1]+1; j <= ip[i]-1; j++)
      sumzae+= GS[j] * xa[iez[j]];
    xa[i]= xi[i] - rp * sumzae;
    }

  for(i= nfg; i >= 2; i--)
    {
    sumzae= rp * xa[i];
    for(j= ip[i-1]+1; j <= ip[i]-1; j++)
      xa[iez[j]]-= sumzae * GS[j];
    }

/*======================================================================
* Nun Konjugierte Gradienten: r x rho
*=====================================================================*/
  sumzae= 0.;
  for(i= 1; i <= nfg; i++)
    sumzae+= xi[i] * xa[i];
    
/*======================================================================
* Sonderfall k= 1
*=====================================================================*/ 
  if(k == 1)
    {
    rho0= sumzae*eps;
    e= 0.;
    }
  else
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* e(k-1)= r(k-1) x rho(k-1) / r(k-2) x rho(k-2)
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    e= sumzae/rho1;

/*======================================================================
* Residuum erreicht ? Auf Wiedersehen.
*=====================================================================*/ 
  if(sumzae <= rho0)
    {
    for(i= 1; i <= nfg; i++)
      rs[i]= v[i];
    wrim88r(0,TX_JACOOK);
    wlog88r(k,LOG_ITERA);
    return 0;
    }

/*======================================================================
* ansonsten weitermachen
*=====================================================================*/ 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* g(k) = e(k-1) x g(k-1) - rho(k-1)
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for(i= 1; i <= nfg; i++)
    pk[i]= e*pk[i] - xa[i];
    
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Hilfsvektor zz(k)= A x g(k)
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  zz[1]= GS[1]*pk[1];

  for(i= 2; i <= nfg; i++)
    {
    zz[i]= GS[ip[i]] * pk[i];
    for(j= ip[i-1]+1; j <= ip[i]-1; j++)
      {
      zz[i]     += GS[j] * pk[iez[j]];
      zz[iez[j]]+= GS[j] * pk[i];
      }
    }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Nenner g(k) x zz(k) = g(k) x (A x g(k))
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  sumnen= 0.;
  for(i= 1; i <= nfg; i++)
    sumnen+= pk[i] * zz[i];

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* qk= r(k-1) x rho(k-1) / [g(k) x (A x g(k))]
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  q= sumzae/sumnen;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* v(k)= v(k-1) + qk x g(k)
* r(k)= r(k-1) + qk x (A x g(k))
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
  for(i= 1; i <= nfg; i++) 
    {
    v [i]+= q * pk[i];
    xi[i]+= q * zz[i];
    }   

  rho1= sumzae;
  }

/*----------------------------------------------------------------------
* Residuum nicht erreicht - auch auf Wiedersehen.
*---------------------------------------------------------------------*/
wrim88r(0,TX_JACONOTOK);
wlog88r((k-1),LOG_ITERA);

for(i= 1; i <= nfg; i++)
  rs[i]= v[i];

return(0);
}

