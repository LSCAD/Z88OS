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
*  function who88g gibt Ueberschrift aus
*  21.7.2011 Rieg
***********************************************************************/ 

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88g.h>
#include <stdio.h>    /* printf */
#endif

/****************************************************************************
*  Function-Declarationen
****************************************************************************/
void clr88(void);

/***********************************************************************
*  hier beginnt Function who88g
***********************************************************************/
int who88g(void)
{
extern FR_INT4 LANG;

int *p;

clr88();

printf("\n                *****   ***    ***\n");
printf("                   *   *   *  *   *\n");
printf("                  *     ***    ***\n");
printf("                 *     *   *  *   *\n");
printf("                *****   ***    ***\n");

if(LANG==1) 
  {
  printf(" von Univ.Prof.Dr.-Ing. FRANK RIEG (C),2011 V14OS\n");
  printf("    Z88G : der COSMOS- und NASTRAN-Konverter\n\n");
}

if(LANG==2) 
  {
  printf("   by Prof.Dr.FRANK RIEG (C), Germany,2011 V14OS\n");
  printf("      Z88G : the COSMOS and NASTRAN converter\n\n");   
}

#ifdef FR_XQUAD
  printf("                 Floats:   %d Bytes\n",(int)sizeof(long double));     
#endif

#ifdef FR_XDOUB
  printf("                 Floats:   %d Bytes\n",(int)sizeof(double));     
#endif

#ifdef FR_XINT
  printf("                 Integers: %d Bytes\n",(int)sizeof(int));  
#endif

#ifdef FR_XLONG
  printf("                 Integers: %d Bytes\n",(int)sizeof(long));   
#endif

#ifdef FR_XLOLO
  printf("                 Integers: %d Bytes\n",(int)sizeof(long long));   
#endif

  printf("                 Pointers: %d Bytes\n",(int)sizeof(p));     

return(0);
}
