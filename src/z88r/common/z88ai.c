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
* z88ai.c
* 17.7.2011 Zimmermann-Rieg
***********************************************************************/

/***********************************************************************
* Fuer UNIX
***********************************************************************/
#ifdef FR_UNIX
#include <z88r.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
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
int wrim88r(FR_INT4,int);
int wlog88r(FR_INT4,int);
int wfor88i(FR_INT4,FR_INT4);

FR_INT4 exiter(FR_INT4);
int vergleich(FR_INT4AY a, FR_INT4AY b);

/***********************************************************************
*  externe Variable
***********************************************************************/
extern FR_INT4AY ip;
extern FR_INT4AY iez;
extern FR_INT4AY koi;
extern FR_INT4AY ioffs; 
extern FR_INT4AY ifrei; 
extern FR_INT4AY koffs;
extern FR_INT4AY ityp;

extern FR_INT4 nkp,ne,kfoun,nfg,ifnili;
extern FR_INT4 IDYNMEM,MAXIEZ;

/***********************************************************************
*  Variable
***********************************************************************/
struct str_node_struct
  {
  struct str_node_struct *next_str_node_struct;
  FR_INT4 elem;
  };

/*Anzahl Elementtypen und Anzahl Knoten je Element*/
const FR_INT4 nod_num_p_ele[]=
      {8,2,6,2,2,3,8,8,2,20,12,12,2,6,6,10,4,6,16,8,16,12,8,6};
const FR_INT4 elem_types= 24;

const FR_INT4 numb_flags= 2;

struct str_node_struct* main_node_struct;
struct str_node_struct* akt_node_struct,*akt_node_struct_clear;

FR_INT4AY node_crosses;
FR_INT4 num_node_crosses;
FR_INT4 memory_dyn=0;
FR_INT4 max_node_je_elem;

char flags[2], high_dyn_flag;

void * mem_pointers[2];

/***********************************************************************
* hier beginnt Function z88ai
***********************************************************************/
int z88ai(void)
{
FR_INT4 i,j,k,l,m;
FR_INT4 base_elem,numdoppelt,knot;
FR_INT4 zeile,spalte;
FR_INT4 dummy_counter;

high_dyn_flag=0;

flags[0]=0;
flags[1]=0;

/*----------------------------------------------------------------------
* Start Function
*---------------------------------------------------------------------*/
/***********************************************************************
* Berechnung maximale Anzahl Knoten je Element
***********************************************************************/

max_node_je_elem=0;
for(i= 0;i < elem_types;i++)
       if (max_node_je_elem<nod_num_p_ele[i])
           max_node_je_elem=nod_num_p_ele[i];

wrim88r(0,TX_Z88AI);
wlog88r(0,LOG_Z88AI);
wrim88r(IDYNMEM,TX_SUMMEMY);

mem_pointers[0]=main_node_struct=malloc(sizeof(struct str_node_struct)*nkp);
if (!main_node_struct) return exiter(0x20);
else {
     memset(main_node_struct,0,sizeof(struct str_node_struct)*nkp);
     flags[0]=1;
     memory_dyn+=sizeof(struct str_node_struct)*nkp;
     };

mem_pointers[1]=node_crosses=malloc(sizeof(FR_INT4)*(nkp+max_node_je_elem));
if (!node_crosses) return exiter(0x20);
else {
     memset(node_crosses,0,sizeof(FR_INT4)*(nkp+max_node_je_elem));
     flags[1]=1;
     memory_dyn+=sizeof(FR_INT4)*nkp;
     };

/***********************************************************************
* Berechnung des Offsetvektors ioffs
***********************************************************************/
ioffs[1]= 1;

for(i= 2;i <= nkp;i++)
  ioffs[i]= ioffs[i-1]+ifrei[i-1];

/***********************************************************************
* ueber die Elementkoinzidenz -> jedes Element den Knotenstrukturen zuordnen
***********************************************************************/
high_dyn_flag=1;
for (i=1;i<=ne;i++)
  for (j=0;j<nod_num_p_ele[ityp[i]-1];j++)
    {
    knot=koi[koffs[i]+j]-1;
    akt_node_struct=&main_node_struct[knot];
    while (akt_node_struct->next_str_node_struct)
      akt_node_struct=akt_node_struct->next_str_node_struct;
    akt_node_struct->next_str_node_struct=malloc(sizeof(struct str_node_struct));
    if (!akt_node_struct->next_str_node_struct) return exiter(0x21);
    else {
         memset(akt_node_struct->next_str_node_struct,0,sizeof(struct str_node_struct));
         memory_dyn+=sizeof(struct str_node_struct);
         };
    akt_node_struct->elem=i-1;
    };

k=1;
dummy_counter=200;

/***********************************************************************
* weiter wird jetzt über jeden Knoten gegangen um die Crossnodes zu bestimmen
***********************************************************************/
for (i=0;i<nkp;i++)
  {
  akt_node_struct=&main_node_struct[i];
  if (!akt_node_struct->next_str_node_struct) return exiter(0x10);
  num_node_crosses=0;
  /*das hier kann evt. entfallen
  memset(node_crosses,0,sizeof(FR_INT4)*(nkp+max_node_je_elem)); */
  while (akt_node_struct->next_str_node_struct)
    {
    base_elem=koffs[akt_node_struct->elem+1];
    for (j=0;j<nod_num_p_ele[ityp[akt_node_struct->elem+1]-1];j++)
      {
      node_crosses[num_node_crosses]=koi[base_elem++]-1;
      num_node_crosses++;
      };
    /*Primärsortieren*/
    qsort(node_crosses,num_node_crosses,sizeof(FR_INT4),vergleich);
    numdoppelt=0;
    for (j=0;j<num_node_crosses;j++)
      while ((j+1)<num_node_crosses)
        {
        if (node_crosses[j]!=node_crosses[j+1]) break;
        numdoppelt++;
        node_crosses[j]=nkp;
        j++;
        };
    /*Sekundärsortieren*/
    qsort(node_crosses,num_node_crosses,sizeof(FR_INT4),vergleich);
    num_node_crosses-=numdoppelt;
    akt_node_struct=akt_node_struct->next_str_node_struct;
    };

  if (dummy_counter==200)
    {
    wfor88i(nkp-1-i,k);
    dummy_counter=0;
    }
  else dummy_counter++;
		
  for (j=0;j<ifrei[i+1];j++)
    {
    zeile=ioffs[i+1]+j;
    for (m=0;m<num_node_crosses;m++)
      for (l=0;l<ifrei[node_crosses[m]+1];l++)
        {
        spalte=ioffs[node_crosses[m]+1]+l;
        if(ifnili != 9) if (k >= MAXIEZ) return exiter(0x01);
        if(ifnili != 9) iez[k]=spalte;
        k++;
        if (spalte<zeile) continue;
        else if (spalte==zeile) ip[zeile]= k-1;
	else
          {
          ip[zeile]=--k;
          if(ifnili != 9) if (k >= MAXIEZ) return exiter(0x01);
          if(ifnili != 9) iez[k]=zeile;
          k++;
          };
        m= num_node_crosses;
        break;
        };
      };
    };

kfoun=ip[nfg];
memory_dyn/=1024*1024;

wrim88r(memory_dyn,TX_DYNMEMY);
wrim88r(0,TX_GSSO);
wlog88r(0,LOG_EXITZ88AI);
	
return exiter(0x00);
}

/***********************************************************************
* Exiter
***********************************************************************/
/* Fehlerquellen
0x0x - Standardfehler
	0	alles i.o.
	1.	Struktur zu groß für Speicher MAXIEZ
0x1x - Strukturfehler
	0	Knoten hängt ohne Elemente in der Luft
0x2x
	0.	zu wenig Speicher - festdynamischer Speicherfehler
	1 	zu wenig Speicher - hochdynamsischer Speicherfehler */

FR_INT4 exiter (FR_INT4 error)
{
FR_INT4 i;	

if (high_dyn_flag)
  {
  i=nkp-1;
  while (1)
  {
  while (main_node_struct[i].next_str_node_struct)
    {
    akt_node_struct_clear=akt_node_struct=&main_node_struct[i];
    while (akt_node_struct->next_str_node_struct)
      {
      akt_node_struct_clear=akt_node_struct;
      akt_node_struct=akt_node_struct->next_str_node_struct;
      };
    akt_node_struct_clear->next_str_node_struct=0;
    free(akt_node_struct);
    }

  if (i) i--; else break;
  };
};

for (i=0;i<numb_flags;i++)
  {
  if (!flags[i]) continue;
  free(mem_pointers[i]);
  flags[i]=0;
  };

if(error == 0x01) error= AL_EXMAXIEZ;
return error;
}

/***********************************************************************
*Vergleich
***********************************************************************/
int vergleich(FR_INT4AY a, FR_INT4AY b)
  {
  if      (*a > *b) return  1;
  else if (*a < *b) return -1;
  else return 0;
  }

