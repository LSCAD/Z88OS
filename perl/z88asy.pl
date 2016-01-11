#***********************************************************************
# Z88ASY.PL - ein Perl-Konverter: ANSYS in Z88Aurora V2
# hat die gleiche Funktionalitaet wie Z88ASY.C, also
# - Tetaeder Nr. 16 und 17, mit Flaechenlasten
# - Scheiben 7 u. 14 und Tori 8 u. 15, ohne Flaechenlasten
# - Platten 18 u. 20 und Schalen 23 u. 24 mit Flaechenlasten
#
# Aufruf: perl z88asy.pl -tetra|-schei|-plate|-torus|-shell
#
# Dieses Quick'nDirty-Programm ist nicht very perlish, 
# aber es funktioniert - and that counts!
#
# 7.1.12 Rieg
#***********************************************************************

#***********************************************************************
# Hauptprogramm
#***********************************************************************
{
print "\n                *****   ***    ***\n";
print "                   *   *   *  *   *\n";
print "                  *     ***    ***\n";
print "                 *     *   *  *   *\n";
print "                *****   ***    ***\n";

print " von Univ.Prof.Dr.-Ing. FRANK RIEG (C),2012 V15\n";
print " Z88ASY.PL : der ANSYS-Konverter als Perl-Prog.\n\n";

open ANS, "< z88asy.ans"
or die "kann z88asy.ans nicht oeffnen...Stop!\n\n";

open I1 , "> z88i1.txt"
or die "kann z88i1.txt nicht oeffnen...Stop!\n\n";

open I2 , "> z88i2.txt"
or die "kann z88i2.txt nicht oeffnen...Stop!\n\n";

open I5 , "> z88i5.txt"
or die "kann z88i5.txt nicht oeffnen...Stop!\n\n";

$nkp= 0;
$ne = 0;
$nrb= 0;
$npr= 0;

#-----------------------------------------------------------------------
# Kommandozeile auswerten
#-----------------------------------------------------------------------
chomp($ARGV[0]);

if(!($ARGV[0] eq '-tetra' || $ARGV[0] eq '-schei' || $ARGV[0] eq '-plate' ||
     $ARGV[0] eq '-torus' || $ARGV[0] eq '-shell'))
  { 
  print "Aufruf: perl z88asy.pl -tetra|-schei|-plate|-torus|-shell\n\n";
  exit; 
  }

if($ARGV[0] eq '-tetra') 
  { 
  $ICFLAG= 1;
  print "Tetraeder-Erzeugung\n";
  &dansy; 
  }

if($ARGV[0] eq '-schei') 
  { 
  $ICFLAG= 2;
  print "Scheiben-Erzeugung\n";
  &eansy; 
  }

if($ARGV[0] eq '-plate') 
  { 
  $ICFLAG= 3;
  print "Platten-Erzeugung\n";
  &pansy; 
  }

if($ARGV[0] eq '-torus') 
  { 
  $ICFLAG= 4;
  print "Torus-Erzeugung\n";
  &eansy; 
  }

if($ARGV[0] eq '-shell') 
  { 
  $ICFLAG= 6;
  print "Schalen-Erzeugung\n";
  &pansy; 
  }

#-----------------------------------------------------------------------
# Ende: Schliessen aller Dateien
#-----------------------------------------------------------------------
close ANS;
close I1;
close I2;
close I5;

print "Z88ASY.PL fertig, alle Z88-Dateien geschrieben.\n"
}

#***********************************************************************
# DANSY: Tetraeder
#***********************************************************************
sub dansy {

#-----------------------------------------------------------------------
# 1.Durchlauf: Scannen der Zaehler
#-----------------------------------------------------------------------
while ($zeile= <ANS>)
{
chomp($zeile);
if($zeile=~/^ET,/) 
  {
  @tstring= split /,/,$zeile;
  print "Elementtyp $tstring[1] ist $tstring[2]\n";
  }

if($zeile=~/^N,/)     { $nkp++; }
if($zeile=~/^EN,/)    { $ne++;  }
if($zeile=~/^F,/)     { $nrb++; }
if($zeile=~/^D,/)     { $nrb++; }
if($zeile=~/^SFE,/)   { $npr++; }
}

$ndim=  3;
$nfg=   3*$nkp;
$kflag= 0;

print "$nkp Knoten und $ne Elemente entdeckt\n";
print "$nrb Randbedingungen entdeckt\n";
print "$npr Flaechenlasten entdeckt\n"; 

printf I1 "%5d %5d %5d %5d %5d     Z88I1.TXT via Z88ASY.PL\n",
  $ndim,$nkp,$ne,$nfg,$kflag;

#-----------------------------------------------------------------------
# Speicher anfordern
#-----------------------------------------------------------------------
$koi[$ne*10+1]= 0;
$koffs[$ne+1] = 0;
$nep[$npr+1]  = 0;
$pres[$npr+1] = 0;
$knn[$npr+1]  = 0;

#-----------------------------------------------------------------------
# 2.Durchlauf: Knoten schreiben
#-----------------------------------------------------------------------
seek ANS, 0, 0; # rewind

print "Knoten decodieren..\n";

while ($zeile= <ANS>)
{
chomp($zeile);
if($zeile=~/^N,/) 
  {
  @ts= split /,/,$zeile;
  printf I1 "%5d  3  %+13.5E  %+13.5E  %+13.5E\n",$ts[1],$ts[2],$ts[3],$ts[4];
  }
}

#-----------------------------------------------------------------------
# 3.Durchlauf: Koinzidenz schreiben
#-----------------------------------------------------------------------
seek ANS, 0, 0; # rewind

print "Koinzidenz decodieren..\n";

$i= 0;
$ktyp16= 0;
$ktyp17= 0;

while ($zeile= <ANS>)
{
chomp($zeile);
if($zeile=~/^EN,/) 
  {
  $i++;

  if($i == 1) { $koffs[1]= 1; }
  else        { $koffs[$i]= $koffs[$i-1] + $kofold;}

  @ts1= split /,/,$zeile;

  if(@ts1 > 6) # Tetraeder mit 10 Knoten
    {
    $ktyp16++;
    chomp($zeile2= <ANS>);
    @ts2= split /,/,$zeile2;

    if(@ts1 != 10) { print "Fehler in $zeile\n"; }
    if(@ts2 !=  3) { print "Fehler in $zeile2\n";}

    printf I1 "%5d   16\n",$ts1[1];
    printf I1 "%5d %5d %5d %5d %5d %5d %5d %5d %5d %5d\n",
      $ts1[2],$ts1[3],$ts1[4],$ts1[5],$ts1[6],
      $ts1[7],$ts1[8],$ts2[1],$ts2[2],$ts1[9];

    $koi[$koffs[$i]   ]= $ts1[2]; # nur sichern fuer Flaechenlasten
    $koi[$koffs[$i] +1]= $ts1[3]; # sonst waere das garnicht noetig
    $koi[$koffs[$i] +2]= $ts1[4];
    $koi[$koffs[$i] +3]= $ts1[5];
    $koi[$koffs[$i] +4]= $ts1[6];
    $koi[$koffs[$i] +5]= $ts1[7];
    $koi[$koffs[$i] +6]= $ts1[8];
    $koi[$koffs[$i] +7]= $ts2[1];
    $koi[$koffs[$i] +8]= $ts2[2];
    $koi[$koffs[$i] +9]= $ts1[9];

    $kofold= 10;
    }
  else                 # Tetraeder mit 4 Knoten
    {
    $ktyp17++;

    printf I1 "%5d   17\n%5d %5d %5d %5d\n",$ts1[1],$ts1[2],$ts1[3],$ts1[4],$ts1[5];

    $koi[$koffs[$i]   ]= $ts1[2]; # nur sichern fuer Flaechenlasten
    $koi[$koffs[$i] +1]= $ts1[3]; # sonst waere das garnicht noetig
    $koi[$koffs[$i] +2]= $ts1[4];
    $koi[$koffs[$i] +3]= $ts1[5];

    $kofold= 4;
    }
  }
}

print "$ktyp16 Tetraeder Nr.16 gefunden\n";
print "$ktyp17 Tetraeder Nr.17 gefunden\n";

#-----------------------------------------------------------------------
# 4.Durchlauf: Randbedingungen schreiben
#-----------------------------------------------------------------------
seek ANS, 0, 0; # rewind

print "Randbedingungen decodieren..\n";

printf I2 "%5d     Z88I2.TXT via Z88ASY.PL\n",$nrb;

while ($zeile= <ANS>)
{
chomp($zeile);

if($zeile=~/^D,/) 
  {
  $iflag1= 2;

  if($zeile=~/UX,/) { $ifg= 1; }
  if($zeile=~/UY,/) { $ifg= 2; }
  if($zeile=~/UZ,/) { $ifg= 3; }

  @ts= split /,/,$zeile;
  printf I2 "%5d %5d %5d   %+13.5E\n",$ts[1],$ifg, $iflag1,$ts[3];
  }

if($zeile=~/^F,/) 
  {
  $iflag1= 1;

  if($zeile=~/FX,/) { $ifg= 1; }
  if($zeile=~/FY,/) { $ifg= 2; }
  if($zeile=~/FZ,/) { $ifg= 3; }

  @ts= split /,/,$zeile;
  printf I2 "%5d %5d %5d   %+13.5E\n",$ts[1],$ifg, $iflag1,$ts[3];
  }
}

#-----------------------------------------------------------------------
# 5.Durchlauf: Flaechenlasten schreiben
#-----------------------------------------------------------------------
seek ANS, 0, 0; # rewind

print "Flaechenlasten decodieren\n";

$n= 0;

while ($zeile= <ANS>)
{
chomp($zeile);

if($zeile=~/^SFE,/) 
  {
  @ts= split /,/,$zeile;
  $n++;
  $nep[$n] = $ts[1];
  $knn[$n] = $ts[2];
  $pres[$n]= $ts[5];
  }
}

printf I5 "%5d     Z88I5.TXT via Z88ASY.PL\n",$npr;

if($npr == 0) 
  {
  goto Lnopr;
  }

for($i= 1; $i <= $npr; $i++)
  {
  $k1= $koi[$koffs[$nep[$i]]  ];         # die vier Eckknoten
  $k2= $koi[$koffs[$nep[$i]]+1];
  $k3= $koi[$koffs[$nep[$i]]+2];
  $k4= $koi[$koffs[$nep[$i]]+3];  
  if($ktyp16 > 0)
    {
    $k5 = $koi[$koffs[$nep[$i]]+4];      # die sechs Mittenknoten
    $k6 = $koi[$koffs[$nep[$i]]+5];
    $k7 = $koi[$koffs[$nep[$i]]+6];
    $k8 = $koi[$koffs[$nep[$i]]+7]; 
    $k9 = $koi[$koffs[$nep[$i]]+8];
    $k10= $koi[$koffs[$nep[$i]]+9];
    }

  if($knn[$i] == 1)                  # Dreieck 1-3-2-7-6-5
    {
    $n1= $k1;
    $n2= $k3;
    $n3= $k2;
    if($ktyp16 > 0)
      {
      $n4= $k7;
      $n5= $k6;
      $n6= $k5;
      }
    }  

  if($knn[$i] == 2)                  # Dreieck 1-2-4-5-8-10
    {
    $n1= $k1;
    $n2= $k2;
    $n3= $k4;
    if($ktyp16 > 0)
      {
      $n4= $k5;
      $n5= $k8;
      $n6= $k10;
      }
    }  

  if($knn[$i] == 3)                  # Dreieck 2-3-4-6-9-8 
    {
    $n1= $k2;
    $n2= $k3;
    $n3= $k4;
    if($ktyp16 > 0)
      {
      $n4= $k6;
      $n5= $k9;
      $n6= $k8;
      }
    }  

  if($knn[$i] == 4)                  # Dreieck 3-1-4-7-10-9
    {
    $n1= $k3;
    $n2= $k1;
    $n3= $k4;
    if($ktyp16 > 0)
      {
      $n4= $k7;
      $n5= $k10;
      $n6= $k9;
      }
    }  

  if($ktyp17 > 0)
    {
    printf I5 "%5d   %+13.5E   %5d %5d %5d\n",$nep[$i],$pres[$i],$n1,$n2,$n3;
    }
  if($ktyp16 > 0)
    {
    printf I5 "%5d   %+13.5E   %5d %5d %5d %5d %5d %5d\n",$nep[$i],$pres[$i],
      $n1,$n2,$n3,$n4,$n5,$n6;
    }
  }

Lnopr:;
} # Ende Subroutine DANSY

#***********************************************************************
# EANSY: Scheiben und Tori
#***********************************************************************
sub eansy {

#-----------------------------------------------------------------------
# 1.Durchlauf: Scannen der Zaehler
#-----------------------------------------------------------------------
while ($zeile= <ANS>)
{
chomp($zeile);
if($zeile=~/^ET,/) 
  {
  @tstring= split /,/,$zeile;
  print "Elementtyp $tstring[1] ist $tstring[2], ";
  }


if($zeile=~/^N,/)     { $nkp++; }
if($zeile=~/^EN,/)    { $ne++;  }
if($zeile=~/^F,/)     { $nrb++; }
if($zeile=~/^D,/)     { $nrb++; }
}

$ndim=  2;
$nfg=   2*$nkp;
$kflag= 0;

print "$nkp Knoten und $ne Elemente entdeckt\n";
print "$nrb Randbedingungen entdeckt\n";
print "$npr Flaechenlasten entdeckt\n"; 
printf I1 "%5d %5d %5d %5d %5d     Z88I1.TXT via Z88ASY.PL\n",
  $ndim,$nkp,$ne,$nfg,$kflag;

#-----------------------------------------------------------------------
# Speicher anfordern
#-----------------------------------------------------------------------
$koi[$ne*8+1]= 0;
$koffs[$ne+1]= 0;

#-----------------------------------------------------------------------
# 2.Durchlauf: Knoten schreiben
#-----------------------------------------------------------------------
seek ANS, 0, 0; # rewind

print "Knoten decodieren..\n";

while ($zeile= <ANS>)
{
chomp($zeile);
if($zeile=~/^N,/) 
  {
  @ts= split /,/,$zeile;
  printf I1 "%5d   2   %+13.5E  %+13.5E  %+13.5E\n",$ts[1],$ts[2],$ts[3],$ts[4];
  }
}

#-----------------------------------------------------------------------
# 3.Durchlauf: Koinzidenz schreiben
#-----------------------------------------------------------------------
seek ANS, 0, 0; # rewind

print "Koinzidenz decodieren..\n";

$i     = 0;
$ktyp7 = 0;
$ktyp14= 0;
$ktyp8 = 0;
$ktyp15= 0;

while ($zeile= <ANS>)
{
chomp($zeile);
if($zeile=~/^EN,/) 
  {
  @ts= split /,/,$zeile;
  $k= $ts[1];
  for($j= 1; $j <= 8; $j++)
    {
    $ja[$j]= $ts[$j+1];
    }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# feststellen, ob 3 gleiche Zahlen vorkommen --> Ele Typ 14 und Typ 15
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  $m1= $m2= $m3= 0;

  for($n= 1; $n <= 6; $n++)
    {
    for($m= $n+1; $m <= 8;$m++)
      {
      if($ja[$n] == $ja[$m]) 
        {
        if($m2 == 0) 
          {
          $m1= $n;
          $m2= $m;
          }
        else 
          {
          $m3= $m;
          goto Lfou;
          }
        }
      }
    }

Lfou:;

  if($m1 == 0) { $ityp= 7;}   # bis jetzt noch keine Unterscheidung in 
  else         { $ityp= 14; } # Scheiben- und Toruselemente, wird erst 
                              # beim Ausschreiben gemacht            
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Koinzidenz vorbereiten
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  $i++;

  if($i == 1) { $koffs[1]= 1; }
  else        { $koffs[$i]= $koffs[$i-1] + $kofold;}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Koinzidenz zuweisen für Ele Typ 7 und Typ 8
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($ityp == 7)
    {
    $koi[$koffs[$i]   ]= $ja[1];
    $koi[$koffs[$i] +1]= $ja[2]; 
    $koi[$koffs[$i] +2]= $ja[3];
    $koi[$koffs[$i] +3]= $ja[4]; 
    $koi[$koffs[$i] +4]= $ja[5];
    $koi[$koffs[$i] +5]= $ja[6];
    $koi[$koffs[$i] +6]= $ja[7];
    $koi[$koffs[$i] +7]= $ja[8]; 

    if($ICFLAG == 2) # Scheibe
      {
      $ityp= 7;
      $ktyp7++;
      }

    if($ICFLAG == 4) # Torus
      {
      $ityp= 8;
      $ktyp8++;
      }

    printf I1 "%5d  %5d\n%5d %5d %5d %5d %5d %5d %5d %5d\n",
    $k,$ityp,$koi[$koffs[$i]   ], $koi[$koffs[$i] +1], 
             $koi[$koffs[$i] +2], $koi[$koffs[$i] +3], 
             $koi[$koffs[$i] +4], $koi[$koffs[$i] +5], 
             $koi[$koffs[$i] +6], $koi[$koffs[$i] +7]; 

    $kofold= 8;
    }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Koinzidenz zuweisen für Ele Typ 14 und Typ 15
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($ityp == 14)
    {
    $koi[$koffs[$i]   ]= $ja[1];
    $koi[$koffs[$i] +1]= $ja[2]; 
    $koi[$koffs[$i] +2]= $ja[3];
    $koi[$koffs[$i] +3]= $ja[5]; 
    $koi[$koffs[$i] +4]= $ja[6];
    $koi[$koffs[$i] +5]= $ja[8];

    if($ICFLAG == 2) # Scheibe
      {
      $ityp= 14;
      $ktyp14++;
      }

    if($ICFLAG == 4) # Torus
      {
      $ityp= 15;
      $ktyp15++;
      }

    printf I1 "%5d  %5d\n%5d %5d %5d %5d %5d %5d\n",
    $k,$ityp,$koi[$koffs[$i]   ], $koi[$koffs[$i] +1], 
             $koi[$koffs[$i] +2], $koi[$koffs[$i] +3], 
             $koi[$koffs[$i] +4], $koi[$koffs[$i] +5]; 

    $kofold= 6;
    }
  } # end if
}  # end while: Ende 3. Durchlauf

print "$ktyp7 Scheiben Nr.7 gefunden\n";
print "$ktyp14 Scheiben Nr.14 gefunden\n";
print "$ktyp8 Tori Nr.8 gefunden\n";
print "$ktyp15 Tori Nr.15 gefunden\n";

#-----------------------------------------------------------------------
# 4.Durchlauf: Randbedingungen schreiben
#-----------------------------------------------------------------------
seek ANS, 0, 0; # rewind

print "Randbedingungen decodieren..\n";

printf I2 "%5d     Z88I2.TXT via Z88ASY.PL\n",$nrb;

while ($zeile= <ANS>)
{
chomp($zeile);

if($zeile=~/^D,/) 
  {
  $iflag1= 2;

  if($zeile=~/UX,/) { $ifg= 1; }
  if($zeile=~/UY,/) { $ifg= 2; }

  @ts= split /,/,$zeile;
  printf I2 "%5d %5d %5d   %+13.5E\n",$ts[1],$ifg, $iflag1,$ts[3];
  }

if($zeile=~/^F,/) 
  {
  $iflag1= 1;

  if($zeile=~/FX,/) { $ifg= 1; }
  if($zeile=~/FY,/) { $ifg= 2; }

  @ts= split /,/,$zeile;
  printf I2 "%5d %5d %5d   %+13.5E\n",$ts[1],$ifg, $iflag1,$ts[3];
  }
}

#-----------------------------------------------------------------------
# Z88I5.TXT, Streckenlasten sind momentan nicht vorgesehen
#-----------------------------------------------------------------------
#=======================================================================
# Z88I5.TXT: erste Zeile
#=======================================================================
seek ANS, 0, 0; # rewind

$n= 0;

printf I5 "%5d     Z88I5.TXT via Z88ASY.PL\n",$n;
}

#***********************************************************************
# PANSY: Platten und Schalen
#***********************************************************************
sub pansy {

#-----------------------------------------------------------------------
# 1.Durchlauf: Scannen der Zaehler
#-----------------------------------------------------------------------
while ($zeile= <ANS>)
{
chomp($zeile);
if($zeile=~/^ET,/) 
  {
  @tstring= split /,/,$zeile;
  print "Elementtyp $tstring[1] ist $tstring[2], ";
  }

if($zeile=~/^N,/)     { $nkp++; }
if($zeile=~/^EN,/)    { $ne++;  }
if($zeile=~/^F,/)     { $nrb++; }
if($zeile=~/^D,/)     { $nrb++; }
if($zeile=~/^SFE,/)   { $npr++; }
}

if($ICFLAG == 3) # Platten 
  {
  $ndim= 2;
  $nfg=  $nkp*3;
  }

if($ICFLAG == 6) # Schalen
  {
  $ndim= 3;
  $nfg=  $nkp*6;
  }

$kflag= 0;

print "$nkp Knoten und $ne Elemente entdeckt\n";
print "$nrb Randbedingungen entdeckt\n";
print "$npr Flaechenlasten entdeckt\n"; 

printf I1 "%5d %5d %5d %5d %5d     Z88I1.TXT via Z88ASY.PL\n",
  $ndim,$nkp,$ne,$nfg,$kflag;

#-----------------------------------------------------------------------
# Speicher anfordern
#-----------------------------------------------------------------------
$koi[$ne*8+1]= 0;
$koffs[$ne+1]= 0;
$nep[$npr+1] = 0;
$pres[$npr+1]= 0;
$knn[$npr+1] = 0;

#-----------------------------------------------------------------------
# 2.Durchlauf: Knoten schreiben
#-----------------------------------------------------------------------
seek ANS, 0, 0; # rewind

print "Knoten decodieren..\n";

while ($zeile= <ANS>)
{
if($ICFLAG == 3) { $ifrei= 3; }  # Platten
if($ICFLAG == 6) { $ifrei= 6; }  # Schalen

chomp($zeile);
if($zeile=~/^N,/) 
  {
  @ts= split /,/,$zeile;
  printf I1 "%5d  %5d   %+13.5E   %+13.5E   %+13.5E\n",
    $ts[1],$ifrei,$ts[2],$ts[3],$ts[4];
  }
}

#-----------------------------------------------------------------------
# 3.Durchlauf: Koinzidenz schreiben
#-----------------------------------------------------------------------
seek ANS, 0, 0; # rewind

print "Koinzidenz decodieren..\n";

$i     = 0;
$ktyp18= 0;
$ktyp20= 0;
$ktyp23= 0;
$ktyp24= 0;

while ($zeile= <ANS>)
{
chomp($zeile);
if($zeile=~/^EN,/) 
  {
  @ts= split /,/,$zeile;
  $k= $ts[1];
  for($j= 1; $j <= 8; $j++)
    {
    $ja[$j]= $ts[$j+1];
    }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# feststellen, ob 3 gleiche Zahlen vorkommen --> Ele Typ 18 bzw. Typ 24
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  $m1= $m2= $m3= 0;

  for($n= 1; $n <= 6; $n++)
    {
    for($m= $n+1; $m <= 8;$m++)
      {
      if($ja[$n] == $ja[$m]) 
        {
        if($m2 == 0) 
          {
          $m1= $n;
          $m2= $m;
          }
        else 
          {
          $m3= $m;
          goto Lfoup;
          }
        }
      }
    }

Lfoup:;

  if($m1 == 0) { $ityp= 20; } # bis jetzt noch keine Unterscheidung in 
  else         { $ityp= 18; } # Schalen- und Plattenelemente, wird erst 
                              # beim Ausschreiben gemacht            
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Koinzidenz vorbereiten
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  $i++;

  if($i == 1) { $koffs[1]= 1; }
  else        { $koffs[$i]= $koffs[$i-1] + $kofold;}

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Koinzidenz zuweisen für Ele Ele Typ 20 und Typ 23
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($ityp == 20)
    {
    $koi[$koffs[$i]   ]= $ja[1];
    $koi[$koffs[$i] +1]= $ja[2]; 
    $koi[$koffs[$i] +2]= $ja[3];
    $koi[$koffs[$i] +3]= $ja[4]; 
    $koi[$koffs[$i] +4]= $ja[5];
    $koi[$koffs[$i] +5]= $ja[6];
    $koi[$koffs[$i] +6]= $ja[7];
    $koi[$koffs[$i] +7]= $ja[8]; 

    if($ICFLAG == 3) # Platte
      {
      $ityp[$i]= 20;
      $ktyp20++;
      }

    if($ICFLAG == 6) # Schale 
      {
      $ityp[$i]= 23;
      $ktyp23++;
      }

    printf I1 "%5d  %5d\n%5d %5d %5d %5d %5d %5d %5d %5d\n",
    $k,$ityp[$i],$koi[$koffs[$i]   ], $koi[$koffs[$i] +1], 
                 $koi[$koffs[$i] +2], $koi[$koffs[$i] +3], 
                 $koi[$koffs[$i] +4], $koi[$koffs[$i] +5], 
                 $koi[$koffs[$i] +6], $koi[$koffs[$i] +7]; 

    $kofold= 8;
    }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Koinzidenz zuweisen für Ele Ele Typ 18 und Typ 24
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($ityp == 18)
    {
    $koi[$koffs[$i]   ]= $ja[1];
    $koi[$koffs[$i] +1]= $ja[2]; 
    $koi[$koffs[$i] +2]= $ja[3];
    $koi[$koffs[$i] +3]= $ja[5]; 
    $koi[$koffs[$i] +4]= $ja[6];
    $koi[$koffs[$i] +5]= $ja[8];

    if($ICFLAG == 3) # Platte 
      {
      $ityp[$i]= 18;
      $ktyp18++;
      }

    if($ICFLAG == 6) # Schale
      {
      $ityp[$i]= 24;
      $ktyp24++;
      }

    printf I1 "%5d  %5d\n%5d %5d %5d %5d %5d %5d\n",
    $k,$ityp[$i],$koi[$koffs[$i]   ], $koi[$koffs[$i] +1], 
                 $koi[$koffs[$i] +2], $koi[$koffs[$i] +3], 
                 $koi[$koffs[$i] +4], $koi[$koffs[$i] +5]; 

    $kofold= 6;
    }
  } # end if
}  # end while: Ende 3. Durchlauf

print "$ktyp18 Platten Nr.18 gefunden\n";
print "$ktyp20 Platten Nr.20 gefunden\n";
print "$ktyp23 Schalen Nr.23 gefunden\n";
print "$ktyp24 Schalen Nr.24 gefunden\n";

#-----------------------------------------------------------------------
# 4.Durchlauf: Randbedingungen schreiben
#-----------------------------------------------------------------------
seek ANS, 0, 0; # rewind

print "Randbedingungen decodieren..\n";

printf I2 "%5d     Z88I2.TXT via Z88ASY.PL\n",$nrb;

while ($zeile= <ANS>)
{
chomp($zeile);

if($zeile=~/^D,/) 
  {
  $iflag1= 2;

  if($zeile=~/UX,/) { $ifg= 1; }
  if($zeile=~/UY,/) { $ifg= 2; }
  if($zeile=~/UZ,/) 
    {
    if($ICFLAG == 3) { $ifg= 1; }
    if($ICFLAG == 6) { $ifg= 3; }
    }         		

  if($zeile=~/ROTX,/)
    {
    if($ICFLAG == 3) { $ifg= 2; }
    if($ICFLAG == 6) { $ifg= 4; }
    }
  if($zeile=~/ROTY,/)
    {
    if($ICFLAG == 3) { $ifg= 3; }
    if($ICFLAG == 6) { $ifg= 5; }
    }
  if($zeile=~/ROTZ,/)
    {
    if($ICFLAG == 6) { $ifg= 6; }
    }

  @ts= split /,/,$zeile;
  printf I2 "%5d %5d %5d   %+13.5E\n",$ts[1],$ifg, $iflag1,$ts[3];
  }

if($zeile=~/^F,/) 
  {
  $iflag1= 1;

  if($zeile=~/FX,/) { $ifg= 1; }
  if($zeile=~/FY,/) { $ifg= 2; }
  if($zeile=~/FZ,/) { $ifg= 3; }

  @ts= split /,/,$zeile;
  printf I2 "%5d %5d %5d   %+13.5E\n",$ts[1],$ifg, $iflag1,$ts[3];
  }
}

#-----------------------------------------------------------------------
# 5.Durchlauf: Flaechenlasten schreiben
#-----------------------------------------------------------------------
seek ANS, 0, 0; # rewind

print "Flaechenlasten decodieren..\n";

$n= 0;

while ($zeile= <ANS>)
{
chomp($zeile);

if($zeile=~/^SFE,/) 
  {
  @ts= split /,/,$zeile;
  $n++;
  $nep[$n] = $ts[1];
  $knn[$n] = $ts[2];
  $pres[$n]= $ts[5];
  }
}

printf I5 "%5d     Z88I5.TXT via Z88ASY.PL\n",$npr;

if($npr == 0) 
  {
  goto Lnopr;
  }

for($i= 1; $i <= $npr; $i++)
  {
  $ntyp= $ityp[$nep[$i]];

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Platten 18 und 20 ausschreiben
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($ntyp == 18 || $ntyp == 20)
    {
    if($knn[$i] == 1) # Flaeche 1: Unterseite 
      {
      printf I5 "%5d   %+13.5E\n",$nep[$i],-$pres[$i];
      }
    if($knn[$i] == 2) # Flaeche 2: Oberseite
      {
      printf I5 "%5d   %+13.5E\n",$nep[$i],$pres[$i];
      }
    }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Schalen Typ 23 und 24 ausschreiben
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($ntyp == 23)
    {
    if($knn[$i] == 1) # Flaeche 1: Unterseite 
      {
      $wert= -$pres[$i];
      }
    if($knn[$i] == 2) # Flaeche 2: Oberseite 
      {
      $wert=  $pres[$i];
      }

    printf I5 "%5d   %+13.5E  %5d %5d %5d %5d %5d %5d %5d %5d\n",
    $nep[$i],$wert,$koi[$koffs[$nep[$i]]  ],$koi[$koffs[$nep[$i]]+1],
                   $koi[$koffs[$nep[$i]]+2],$koi[$koffs[$nep[$i]]+3],
                   $koi[$koffs[$nep[$i]]+4],$koi[$koffs[$nep[$i]]+5],
                   $koi[$koffs[$nep[$i]]+6],$koi[$koffs[$nep[$i]]+7];
    }

  if($ntyp == 24)
    {
    if($knn[$i] == 1) # Flaeche 1: Unterseite 
      {
      $wert= -$pres[$i];
      }
    if($knn[$i] == 2) # Flaeche 2: Oberseite 
      {
      $wert=  $pres[$i];
      }

    printf I5 "%5d   %+13.5E  %5d %5d %5d %5d %5d %5d\n",
    $nep[$i],$wert,$koi[$koffs[$nep[$i]]  ],$koi[$koffs[$nep[$i]]+1],
                   $koi[$koffs[$nep[$i]]+2],$koi[$koffs[$nep[$i]]+3],
                   $koi[$koffs[$nep[$i]]+4],$koi[$koffs[$nep[$i]]+5];
    }
  } # end for


Lnopr:;
} # Ende Subroutine PANSY



