#***********************************************************************
# Z88VRY.PL - ein Perl-Verifier fuer Z88-Dateien Z88Aurora V2
# fuer Z88Aurora V2 und Z88 V14 OpenSource
# - anyway, not very perlish -
# folgende Subroutinen:
# G1I188: Checken 1.Zeile Z88I1.TXT/Z88NI.TXT.    Bei ~  350.
# G2I188: Checken Knoten Z88I1.TXT/Z88NI.TXT.     Bei ~  490.
# G3I188: Checken Koinzidenz Z88I1.TXT/Z88NI.TXT. Bei ~  560.
# G4I188: Checken Zerlegeinfos Z88NI.TXT.         Bei ~  920.
# GXI288: Checken Z88I2.                          Bei ~ 1210.
# GXI588: Checken Z88I5.                          Bei ~ 1370.
# GMAN88: Checken Z88MAN.TXT.                     Bei ~ 1650.
# GMAT88: Checken Z88MAT.TXT.                     Bei ~ 1790.
# GELP88: Checken Z88ELP.TXT.                     Bei ~ 1940.
# GINT88: Checken Z88INT.TXT.                     Bei ~ 2140.
## 17.1.12 Rieg
#***********************************************************************

#***********************************************************************
# Hauptprogramm
#***********************************************************************
{

#-----------------------------------------------------------------------
# Kommandozeile auswerten
#-----------------------------------------------------------------------
$LANG= 2;  # englisch als default
$MODE= 1;  # OpenSource als default

chomp($ARGV[0]);

if(@ARGV != 2) 
  { 
  print "use: perl z88vry.pl -german|-english and -os|-aurora\n";
  exit;
  }

if(!( ($ARGV[0] eq '-german' || $ARGV[0] eq '-english') && 
      ($ARGV[1] eq '-os' || $ARGV[1] eq '-aurora')))
  { 
  print "use: perl z88vry.pl -german|-english and -os|-aurora\n";
  exit;
  }

if($ARGV[0] eq '-german') { $LANG= 1; }
if($ARGV[0] eq '-english'){ $LANG= 2; }
if($ARGV[1] eq '-os')     { $MODE= 1; }
if($ARGV[1] eq '-aurora') { $MODE= 2; }

print "\n                *****   ***    ***\n";
print "                   *   *   *  *   *\n";
print "                  *     ***    ***\n";
print "                 *     *   *  *   *\n";
print "                *****   ***    ***\n";

if($LANG == 1) 
  { 
  print " von Univ.Prof.Dr.-Ing. FRANK RIEG (C),2012 V15\n"; 
  print " Z88VRY.PL: ein Z88-Filechecker als Perl-Prog.\n\n";
  }

if($LANG == 2) 
  { 
  print " by Prof. FRANK RIEG (C), Germany 2012, V15\n"; 
  print " Z88VRY.PL: a Perl-written Z88 file checker\n\n";
  }

#-----------------------------------------------------------------------
# der Prompt
#-----------------------------------------------------------------------
if($LANG == 1 && $MODE == 1) { print "Start Z88VRY.PL, OpenSource-Mode \n";}
if($LANG == 1 && $MODE == 2) { print "Start Z88VRY.PL, Aurora-Mode \n";}
if($LANG == 2 && $MODE == 1) { print "Start Z88VRY.PL, mode: Open source \n";}
if($LANG == 2 && $MODE == 2) { print "Start Z88VRY.PL, Aurora mode \n";}

Lomore:;

if($LANG == 1)
  {
  print " 1  -->  Checken der Eingaben, ohne Randbedingungen\n";
  print " 2  -->  Checken der Eingaben, mit Randbedingungen\n";
  print " 3  -->  Checken der Netzgeneratordatei z88ni.txt\n";
  print " 9  -->  Beende Z88VRY\n\n";
  print " Ihre Wahl: ";
  }

if($LANG == 2)
  {
  print " 1  -->  Check of input data, no boundary conditions\n";
  print " 2  -->  Check of input data, boundary conditions included\n";
  print " 3  -->  Check of mapped mesher file z88ni.txt\n";
  print " 9  -->  Quit Z88VRY\n\n";
  print " Your choice: ";
  }

chomp($zeile = <STDIN>);

if(!($zeile eq '1' || $zeile eq '2' || $zeile eq '3' || $zeile eq '9'))
  { goto Lomore; }

$CHOICE= 2*$zeile + $MODE ;

if($CHOICE == 8)  { $CHOICE= 7; }
if($zeile eq '9') { $CHOICE= 9; }

# Also bedeutet CHOICE:
# 3= 2*1 + 1: OpenSource, ohne RBD
# 4= 2*1 + 2: Aurora, ohne RBD 
# 5= 2*2 + 1: OpenSource, mit RBD
# 6= 2*2 + 2: Aurora, mit RBD
# 7= 2*3 + 1: Z88NI.TXT, gilt fuer OS und Aurora
# 9         : Stop

#print "CHOICE= $CHOICE\n";

#-----------------------------------------------------------------------
# Eingabedateien fuer den ersten grundlegenden Check oeffnen
#-----------------------------------------------------------------------
#=======================================================================
# OpenSource-Mode:
# CHOICE = 3: Z88I1.TXT,Z88MAN.TXT,Z88MAT.TXT,Z88INT.TXT,Z88ELP.TXT
# CHOICE = 5: + Z88I2.TXT,Z88I5.TXT
#=======================================================================
if($CHOICE == 3 || $CHOICE == 5)  
  {
  $ifnii1= 0;

  if($LANG == 1)
    {
    open I1 , "< z88i1.txt"
    or die "kann z88i1.txt nicht oeffnen...Stop!\n";
    open MAN, "< z88man.txt"
    or die "kann z88man.txt nicht oeffnen...Stop!\n";
    open MAT, "< z88mat.txt"
    or die "kann z88mat.txt nicht oeffnen...Stop!\n";
    open INT, "< z88int.txt"
    or die "kann z88int.txt nicht oeffnen...Stop!\n";
    open ELP, "< z88elp.txt"
    or die "kann z88elp.txt nicht oeffnen...Stop!\n";
    if($CHOICE == 5)
      {
      open I2 , "< z88i2.txt"
      or die "kann z88i2.txt nicht oeffnen...Stop!\n";
      open I5 , "< z88i5.txt"
      or die "kann z88i5.txt nicht oeffnen...Stop!\n";
      }
    }

  if($LANG == 2)
    {
    open I1 , "< z88i1.txt"
    or die "cannot open z88i1.txt...stop!\n";
    open MAN, "< z88man.txt"
    or die "cannot open z88man.txt...stop!\n";
    open MAT, "< z88mat.txt"
    or die "cannot open z88mat.txt...stop!\n";
    open INT, "< z88int.txt"
    or die "cannot open z88int.txt...stop!\n";
    open ELP, "< z88elp.txt"
    or die "cannot open z88elp.txt...stop!\n";
    if($CHOICE == 5)
      {
      open I2 , "< z88i2.txt"
      or die "cannot open z88i2.txt...stop!\n";
      open I5 , "< z88i5.txt"
      or die "cannot open z88i5.txt...stop!\n";
      }
    }
  }

#=======================================================================
# Aurora-Mode:
# CHOICE = 4: Z88I1.TXT
# CHOICE = 6: Z88I1.TXT,Z88I2.TXT,Z88I5.TXT
#=======================================================================
if($CHOICE == 4 || $CHOICE == 6)  
  {
  $ifnii1= 0;

  if($LANG == 1)
    {
    open I1 , "< z88i1.txt"
    or die "kann z88i1.txt nicht oeffnen...Stop!\n";
    if($CHOICE == 6)
      {
      open I2 , "< z88i2.txt"
      or die "kann z88i2.txt nicht oeffnen...Stop!\n";
      open I5 , "< z88i5.txt"
      or die "kann z88i5.txt nicht oeffnen...Stop!\n";
      }
    }

  if($LANG == 2)
    {
    open I1 , "< z88i1.txt"
    or die "cannot open z88i1.txt...stop!\n";
    if($CHOICE == 6)
      {
      open I2 , "< z88i2.txt"
      or die "cannot open z88i2.txt...stop!\n";
      open I5 , "< z88i5.txt"
      or die "cannot open z88i5.txt...stop!\n";
      }
    }
  }

#=======================================================================
# Netzgenerator-Mode:
# CHOICE = 7: Z88NI.TXT
#=======================================================================
if($CHOICE == 7)  
  {
  $ifnii1= 1;

  if($LANG == 1)
    {
    open I1 , "< z88ni.txt"
    or die "kann z88ni.txt nicht oeffnen...Stop!\n";
    }

  if($LANG == 2)
    {
    open I1 , "< z88ni.txt"
    or die "cannot open z88ni.txt...stop!\n";
    }
  }

#=======================================================================
# Quit
#=======================================================================
if($CHOICE == 9) { goto Lquit; }

#-----------------------------------------------------------------------
# Start der Untersuchung
#-----------------------------------------------------------------------
#=======================================================================
# die "normalen" Eingabedateien:
# Open Source Z88 V14:
# $CHOICE= 3: Z88I1.TXT,Z88MAN.TXT,Z88MAT.TXT,Z88INT.TXT,Z88ELP.TXT
# $CHOICE= 5: $CHOICE=3 + Z88I2.TXT,Z88I5.TXT
# Z88Aurora V2:
# $CHOICE= 4: Z88I1.TXT
# $CHOICE= 5: $CHOICE=4 + Z88I2.TXT,Z88I5.TXT
#=======================================================================
$ier= 0;

if($CHOICE >= 3 && $CHOICE <= 6)
  {
  if(&G1I188 == 1) { goto Lquit; }  # 1.Zeile Z88I1.TXT untersuchen
                                    # es ist $ifnii1= 0
# Speicher kommen lassen
  $ifrei[$nkp+1]= 0;
  $jtyp[$ne+1]= 0;
  $koi[21]= 0;
  $ctyp[25]= 0;
  $noi[9]= 0;

  if(&G2I188 == 1) { $ier= 1; goto Lquit; } # Knoten Z88I1.TXT untersuchen
  if(&G3I188 == 1) { $ier= 1; goto Lquit; } # Koinzi Z88I1.TXT untersuchen

  if($CHOICE == 3 || $CHOICE == 5)  # OpenSource
    {
    if(&GMAN88 == 1) { $ier= 1; goto Lquit; } # Z88MAN.TXT untersuchen
    if(&GMAT88 == 1) { $ier= 1; goto Lquit; } # Z88MAT.TXT untersuchen
    if(&GELP88 == 1) { $ier= 1; goto Lquit; } # Z88ELP.TXT untersuchen
    if(&GINT88 == 1) { $ier= 1; goto Lquit; } # Z88INT.TXT untersuchen
    }

  if($CHOICE == 5 || $CHOICE == 6)    # auch Randbedingungen checken 
    {
    if(&GXI288 == 1) { $ier= 1; goto Lquit; } # Z88I2.TXT untersuchen
    if(&GXI588 == 1) { $ier= 1; goto Lquit; } # Z88I5.TXT untersuchen
    }
  } # end $CHOICE >= 3 && $CHOICE <= 6

#=======================================================================
# die Netzgenerator-Eingabedatei:
# Open Source Z88 V14 und Z88Aurora V2::
# $CHOICE= 7: Z88NI.TXT
#=======================================================================
if($CHOICE == 7)
  {
  if(&G1I188 == 1) { $ier= 1; goto Lquit; } # 1.Zeile Z88I1.TXT untersuchen
                                            # es ist $ifnii1= 1
# Speicher kommen lassen
  $ifrei[$nkp+1]= 0;
  $jtyp[$ne+1]= 0;
  $koi[21]= 0;
  $ctyp[25]= 0;
  $noi[9]= 0;

  if(&G2I188 == 1) { $ier= 1; goto Lquit; } # 2.Gruppe Z88I1.TXT untersuchen
  if(&G3I188 == 1) { $ier= 1; goto Lquit; } # 3.Gruppe Z88I1.TXT untersuchen
  if(&G4I188 == 1) { $ier= 1; goto Lquit; } # 4.Gruppe Z88I1.TXT untersuchen
  }# end $CHOICE == 7

#-----------------------------------------------------------------------
# Ende: Schliessen aller Dateien
#-----------------------------------------------------------------------
if ($CHOICE == 3 )  # OpenSource-Mode, ohne RBD
  {
  close I1;
  close MAN;
  close MAT;
  close INT;
  close ELP;
  }

if ($CHOICE == 4)  # Aurora-Mode, ohne RBD
  {
  close I1;
  }

if ($CHOICE == 5 )  # OpenSource-Mode, mit RBD
  {
  close I1;
  close MAN;
  close MAT;
  close INT;
  close ELP;
  close I2;
  close I5;
  }

if ($CHOICE == 6 )  # Aurora-Mode, mit RBD
  {
  close I1;
  close I2;
  close I5;
  }

if ($CHOICE == 7 )  # Z88NI
  {
  close I1;
  }

Lquit:;
if($ier == 0)
  {
  if($LANG == 1) { print "\nalle Checks absolviert - keine Fehler entdeckt.\n" }
  if($LANG == 2) { print "\nall checks done - no errors detected.\n" }
  }
else
  {
  if($LANG == 1) { print "\nChecks teilweise absolviert - Fehler entdeckt!\n" }
  if($LANG == 2) { print "\nchecks partly done - errors detected!\n" }
  }

}

#***********************************************************************
# G1I188: erste Zeile Z88I1.TXT checken
#***********************************************************************
sub G1I188 {

print "\n***************************************************\n";

if($ifnii1 == 0)
  {
  if($LANG == 1) { print "untersuche 1.Zeile von z88i1.txt\n"; }
  if($LANG == 2) { print "investigating 1st line of z88i1.txt\n"; }
  }
if($ifnii1 == 1)
  {
  if($LANG == 1) { print "untersuche 1.Zeile von z88ni.txt\n"; }
  if($LANG == 2) { print "investigating 1st line of z88ni.txt\n"; }
  }

$kflagss= 0;
$niflag = 0;

chomp($zeile = <I1>);
@ts= split " ",$zeile;

if($ifnii1 == 0) { $jcou= 4; } # Z88I1.TXT
if($ifnii1 == 1) { $jcou= 6; } # Z88NI.TXT

for($i= 0; $i <= $jcou;$i++)
  {
  if($ts[$i]=~ /[A-DF-Za-df-z,_#;:]/)
    {
    if($LANG == 1) { print "Schreibfehler in 1.Zeile entdeckt...Stop\n"; }
    if($LANG == 2) { print "typing error in 1st line detected...stop\n"; }
    return 1;
    }
  }

$ndim = $ts[0];
$nkp  = $ts[1];
$ne   = $ts[2];
$nfg  = $ts[3];
$kflag= $ts[4];

if($ifnii1 == 1) # zusaetzlich fuer Z88NI.TXT
  {
  $kflagss= $ts[4];
  $niflag = $ts[5];
  $kflag  = $ts[6];
  }

if($LANG == 1) { print "Dimension $ndim entdeckt\n"; }
if($LANG == 2) { print "dimension $ndim detected\n"; }
if($LANG == 1) { print "$nkp Knoten entdeckt\n"; }
if($LANG == 2) { print "$nkp nodes detected\n"; }
if($LANG == 1) { print "$ne Elemente entdeckt\n"; }
if($LANG == 2) { print "$ne elements detected\n"; }
if($LANG == 1) { print "$nfg Freiheitsgrade entdeckt\n"; }
if($LANG == 2) { print "$nfg degrees of freedom detected\n"; }

if($kflagss == 1 && $ifnii1 == 1)
  {
  if($LANG == 1) { print "Radial- bzw. Zylinderkoordinaten fuer Superele. entdeckt\n"; }
  if($LANG == 2) { print "radial or cylinder coordinates for super ele. detected\n"; }
  }
if($kflagss == 0  && $ifnii1 == 1)
  {
  if($LANG == 1) { print "kartesische Koordinaten fuer Superele. entdeckt\n"; }
  if($LANG == 2) { print "cartesian coordinates for super ele. detected\n"; }
  }

if($kflag == 1)
  {
  if($LANG == 1) { print "Radial- bzw. Zylinderkoordinaten fuer finite E. entdeckt\n"; }
  if($LANG == 2) { print "radial or cylinder coordinates for finite ele. detected\n"; }
  }
if($kflag == 0)
  {
  if($LANG == 1) { print "kartesische Koordinaten fuer finite E. entdeckt\n"; }
  if($LANG == 2) { print "cartesian coordinates for finite ele. detected\n"; }
  }

if($niflag == 1  && $ifnii1 == 1)
  {
  if($LANG == 1) { print "Fangradienflag niflag fuer Netzgenerator entdeckt\n"; }
  if($LANG == 2) { print "trap flag niflag for mapped mesher detected\n"; }
  }

if(!($ndim == 2 || $ndim == 3))
  {
  if($LANG == 1) { print "Dimension ndim in 1.Zeile falsch...Stop\n"; }
  if($LANG == 2) { print "dimension ndim wrong in 1st line...stop\n"; }
  return 1;
  }

if($nkp <= 0)
  {
  if($LANG == 1) { print "Anzahl Knoten nkp in 1.Zeile <= 0...Stop\n"; }
  if($LANG == 2) { print "number of nodes nkp <= 0 in 1st line...stop\n"; }
  return 1;
  }

if($ne <= 0)
  {
  if($LANG == 1) { print "Anzahl Elemente ne in 1.Zeile <= 0...Stop\n"; }
  if($LANG == 2) { print "number of elements ne <= 0 in 1st line...stop\n"; }
  return 1;
  }

if(($ndim == 2 && $nfg < 2*$nkp) || ($ndim == 3 && $nfg < 3*$nkp)) # recht grob
  {
  if($LANG == 1) { print "Anzahl Freiheitsgrade nfg in 1.Zeile zu klein...Stop\n"; }
  if($LANG == 2) { print "too few DOF = nfg in 1st line...stop\n"; }
  return 1;
  }

if(!($kflag == 0 || $kflag == 1))
  {
  if($LANG == 1) { print "Koordinatenflag kflag in 1.Zeile falsch...Stop\n"; }
  if($LANG == 2) { print "coordinate flag kflag wrong in 1st line...stop\n"; }
  return 1;
  }

if(!($kflagss == 0 || $kflagss == 1))
  {
  if($LANG == 1) { print "Koordinatenflag kflagss in 1.Zeile falsch...Stop\n"; }
  if($LANG == 2) { print "coordinate flag kflagss wrong in 1st line...stop\n"; }
  return 1;
  }

if(!($niflag == 0 || $niflag == 1))
  {
  if($LANG == 1) { print "Fangradienflag niflag in 1.Zeile falsch...Stop\n"; }
  if($LANG == 2) { print "trap flag niflag wrong in 1st line...stop\n"; }
  return 1;
  }

return 0;
}

#***********************************************************************
# G2I188: zweite Gruppe = Knoteninfos von Z88I1.TXT/Z88NI.TXT checken
#***********************************************************************
sub G2I188 {

if($ifnii1 == 0)
  {
  if($LANG == 1) { print "untersuche Knoteninfos von z88i1.txt\n"; }
  if($LANG == 2) { print "investigating nodal infos of z88i1.txt\n"; }
  }
if($ifnii1 == 1)
  {
  if($LANG == 1) { print "untersuche Knoteninfos von z88ni.txt\n"; }
  if($LANG == 2) { print "investigating nodal infos of z88ni.txt\n"; }
  }

$sfrei= 0;

for($j= 1;$j <= $nkp; $j++)
  {
  chomp($zeile = <I1>);
  @ts= split " ",$zeile;

  if($ndim == 2) { $ibis= 3; }
  if($ndim == 3) { $ibis= 4; }

  $n= $j+1; # wg. Zeile 1

  for($i= 0; $i <= $ibis;$i++)
    {
    if($ts[$i]=~ /[A-DF-Za-df-z,_#;:]/)
      {
      if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
      if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
      return 1;
      }
    }

  $iknot    = $ts[0];
  $ifrei[$j]= $ts[1];

  $sfrei += $ifrei[$j];

  if($iknot != $j)
    {
    if($LANG == 1) { print "Zeile $n: Knotennummer stimmt nicht...Stop\n"; }
    if($LANG == 2) { print "line $n: nodal number wrong...stop\n"; }
    return 1;
    }

  if(!($ifrei[$j] == 2 || $ifrei[$j] == 3 || $ifrei[$j] == 6))
    {
    if($LANG == 1) { print "Zeile $n: Anzahl FG stimmt nicht...Stop\n"; }
    if($LANG == 2) { print "line $n: number of DOF wrong...stop\n"; }
    return 1;
    }
  }

if($sfrei != $nfg)
  {
  if($LANG == 1) { print "Summe FG stimmt nicht, vgl. Zeile 1...Stop\n"; }
  if($LANG == 2) { print "sum of DOF wrong, see line 1...stop\n"; }
  return 1;
  }

if($LANG == 1) { print "Knoteninfos koennten okay sein\n"; }
if($LANG == 2) { print "nodal infos may be okay\n"; }

return 0;
}

#***********************************************************************
# G3I188: dritte Gruppe = Koinzidenz von Z88I1.TXT/Z88NI.TXT checken
#***********************************************************************
sub G3I188 {

if($ifnii1 == 0)
  {
  if($LANG == 1) { print "untersuche Elementinfos von z88i1.txt\n"; }
  if($LANG == 2) { print "investigating element infos of z88i1.txt\n"; }
  }
if($ifnii1 == 1)
  {
  if($LANG == 1) { print "untersuche Superelementinfos von z88ni.txt\n"; }
  if($LANG == 2) { print "investigating super element infos of z88ni.txt\n"; }
  }

$n= 1+$nkp; # wg. Zeile 1 und Knoteninfos

for($j= 1;$j <= $ne; $j++)
  {
#-----------------------------------------------------------------------
# erste Zeile fuer Elementinfo
#-----------------------------------------------------------------------
  chomp($zeile1 = <I1>);
  @ts1= split " ",$zeile1;

  $n++;

  for($i= 0; $i <= 1;$i++)
    {
    if($ts1[$i]=~ /[A-DF-Za-df-z,_#;:]/)
      {
      if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
      if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
      return 1;
      }
    }

  $iele= $ts1[0];
  $ityp= $ts1[1];

  $jtyp[$j]= $ityp;  # sichern, aber mit $ityp weiterarbeiten (schneller)

  if($iele != $j)
    {
    if($LANG == 1) { print "Zeile $n: Elementnummer stimmt nicht...Stop\n"; }
    if($LANG == 2) { print "line $n: element number wrong...stop\n"; }
    return 1;
    }

  if(!($ityp >= 1 && $ityp <= 24))
    {
    if($LANG == 1) { print "Zeile $n: Elementtyp existiert nicht...Stop\n"; }
    if($LANG == 2) { print "line $n: element type does not exist...stop\n"; }
    return 1;
    }

  if($ndim == 2 && 
     !($ityp ==  3 || $ityp ==  6 || $ityp ==  7 || $ityp == 8  ||
       $ityp ==  9 || $ityp == 11 || $ityp == 12 || $ityp == 13 ||
       $ityp == 14 || $ityp == 15 || $ityp == 18 || $ityp == 19 ||
       $ityp == 20))
    {
    if($LANG == 1) { print "Zeile $n: Elementtyp passt nicht zu ndim=2...Stop\n"; }
    if($LANG == 2) { print "line $n: element type does not work with ndim=2...stop\n"; }
    return 1;
    }

  if($ndim == 3 && 
     !($ityp ==  1 || $ityp ==  2 || $ityp ==  4 || $ityp == 5  ||
       $ityp == 10 || $ityp == 16 || $ityp == 17 || $ityp == 21 ||
       $ityp == 22 || $ityp == 23 || $ityp == 24 ))
    {
    if($LANG == 1) { print "Zeile $n: Elementtyp passt nicht zu ndim=3...Stop\n"; }
    if($LANG == 2) { print "line $n: element type does not work with ndim=3...stop\n"; }
    return 1;
    }

#-----------------------------------------------------------------------
# zweite Zeile fuer Elementinfo
#-----------------------------------------------------------------------
  chomp($zeile2 = <I1>);
  @ts2= split " ",$zeile2;

  $n++;

#-----------------------------------------------------------------------
# Elemente mit 2 Knoten
#-----------------------------------------------------------------------
  if($ityp == 2 || $ityp == 4 || $ityp == 5 || $ityp == 9 || $ityp == 13)
    {
    for($i= 0; $i <= 1;$i++)
      {
      if($ts2[$i]=~ /[A-DF-Za-df-z,_#;:]/)
        {
        if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
        return 1;
        }
      $koi[$i+1] = $ts2[$i];
      }
    $jmax= 2;
    }  # Ende Elemente mit 2 Knoten

#-----------------------------------------------------------------------
# Elemente mit 3 Knoten
#-----------------------------------------------------------------------
  if($ityp == 6)
    {
    for($i= 0; $i <= 2;$i++)
      {
      if($ts2[$i]=~ /[A-DF-Za-df-z,_#;:]/)
        {
        if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
        return 1;
        }
      $koi[$i+1] = $ts2[$i];
      }
    $jmax= 3;
    }  # Ende Elemente mit 3 Knoten

#-----------------------------------------------------------------------
# Elemente mit 4 Knoten
#-----------------------------------------------------------------------
  if($ityp == 17)
    {
    for($i= 0; $i <= 3;$i++)
      {
      if($ts2[$i]=~ /[A-DF-Za-df-z,_#;:]/)
        {
        if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
        return 1;
        }
      $koi[$i+1] = $ts2[$i];
      }
    $jmax= 4;
    }  # Ende Elemente mit 4 Knoten

#-----------------------------------------------------------------------
# Elemente mit 6 Knoten
#-----------------------------------------------------------------------
  if($ityp == 3  || $ityp == 14 || $ityp == 15 || 
     $ityp == 18 || $ityp == 24)
    {
    for($i= 0; $i <= 5;$i++)
      {
      if($ts2[$i]=~ /[A-DF-Za-df-z,_#;:]/)
        {
        if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
        return 1;
        }
      $koi[$i+1] = $ts2[$i];
      }
    $jmax= 6;
    }  # Ende Elemente mit 6 Knoten

#-----------------------------------------------------------------------
# Elemente mit 8 Knoten
#-----------------------------------------------------------------------
  if($ityp == 1  || $ityp ==  7 || $ityp == 8 || 
     $ityp == 20 || $ityp == 23)
    {
    for($i= 0; $i <= 7;$i++)
      {
      if($ts2[$i]=~ /[A-DF-Za-df-z,_#;:]/)
        {
        if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
        return 1;
        }
      $koi[$i+1] = $ts2[$i];
      }
    $jmax= 8;
    }  # Ende Elemente mit 8 Knoten

#-----------------------------------------------------------------------
# Elemente mit 10 Knoten
#-----------------------------------------------------------------------
  if($ityp == 16)
    {
    for($i= 0; $i <= 9;$i++)
      {
      if($ts2[$i]=~ /[A-DF-Za-df-z,_#;:]/)
        {
        if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
        return 1;
        }
      $koi[$i+1] = $ts2[$i];
      }
    $jmax= 10;
    }  # Ende Elemente mit 10 Knoten

#-----------------------------------------------------------------------
# Elemente mit 12 Knoten
#-----------------------------------------------------------------------
  if($ityp == 11 || $ityp == 12 || $ityp == 22)
    {
    for($i= 0; $i <= 11;$i++)
      {
      if($ts2[$i]=~ /[A-DF-Za-df-z,_#;:]/)
        {
        if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
        return 1;
        }
      $koi[$i+1] = $ts2[$i];
      }
    $jmax= 12;
    }  # Ende Elemente mit 12 Knoten

#-----------------------------------------------------------------------
# Elemente mit 16 Knoten
#-----------------------------------------------------------------------
  if($ityp == 19 || $ityp == 21)
    {
    for($i= 0; $i <= 15;$i++)
      {
      if($ts2[$i]=~ /[A-DF-Za-df-z,_#;:]/)
        {
        if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
        return 1;
        }
      $koi[$i+1] = $ts2[$i];
      }
    $jmax= 16;
    }  # Ende Elemente mit 16 Knoten

#-----------------------------------------------------------------------
# Elemente mit 20 Knoten
#-----------------------------------------------------------------------
  if($ityp == 10)
    {
    for($i= 0; $i <= 19;$i++)
      {
      if($ts2[$i]=~ /[A-DF-Za-df-z,_#;:]/)
        {
        if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
        return 1;
        }
      $koi[$i+1] = $ts2[$i];
      }
    $jmax= 20;
    }  # Ende Elemente mit 16 Knoten

#-----------------------------------------------------------------------
# Knotennummern innerhalb logischer Grenzen ?
#----------------------------------------------------------------------- 
  for($k = 1;$k <= $jmax;$k++)
    {
    if(!($koi[$k] > 0 && $koi[$k] <= $nkp))
      {
      if($LANG == 1) { print "Knotennummer nicht 1 ~ $nkp in Zeile $n entdeckt...Stop\n"; }
      if($LANG == 2) { print "nodal number not 1 ~ $nkp in line $n detected...stop\n"; }
      return 1;
      }
    }

#-----------------------------------------------------------------------
# passen die Freiheitsgrade zum Elementtyp? Nicht sehr genau...
#----------------------------------------------------------------------- 
  for($k = 1;$k <= $jmax;$k++)
    {
    # echt nur 2 FG: Toruselemente
    if( ($ityp ==  6 || $ityp ==  8 || $ityp == 12 || $ityp == 15) 
    && $ifrei[$koi[$k]] == 2) 
      { next; }
    # 2 oder 3 FG, denn Scheiben und 2D-Staebe koennen an Balken Nr.13 angeschlossen werden
    if( ($ityp ==  3 || $ityp ==  7 || $ityp ==  9 || $ityp == 11 || 
         $ityp == 14) && ($ifrei[$koi[$k]] == 2 || $ifrei[$koi[$k]] == 3)) 
      { next; }
    # 3 oder 6 FG, denn Volumenele. koennen an Balken Nr.2 angeschlossen werden
    if( ($ityp ==  1 || $ityp == 2  || $ityp ==  4 || $ityp ==  5 ||
         $ityp == 10 || $ityp == 13 || $ityp == 16 || $ityp == 17 || 
         $ityp == 18 || $ityp == 19 || $ityp == 20 || $ityp == 21 ||
         $ityp == 22 || $ityp == 23 || $ityp == 24) &&
        ($ifrei[$koi[$k]] == 3 || $ifrei[$koi[$k]] == 6) ) 
      { next; }

    if($LANG == 1) { print "Zeile $n: FG passen nicht zum Element...Stop\n"; }
    if($LANG == 2) { print "line $n: DOF not correct for element typ...stop\n"; }
    return 1;
    }

#-----------------------------------------------------------------------
# doppelte Knotennummern ?
#----------------------------------------------------------------------- 
  for($k = 1;$k <= $jmax-1;$k++)
    {
    for($m= $k+1;$m <= $jmax;$m++)
      {
      if($koi[$k] == $koi[$m])
        {
        if($LANG == 1) { print "identische Knotennummern in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "identical nodal numbers in line $n detected...stop\n"; }
        return 1;
        }
      }
    }

  } # Ende grosse Schleife

#-----------------------------------------------------------------------
# ibflag_i1,ipflag_i1,ihflag_i1 feststellen und Elementtypen zaehlen
#----------------------------------------------------------------------- 
$ibflag_i1= 0;
$ipflag_i1= 0;
$ihflag_i1= 0;

for($j= 1;$j <= 25; $j++) { $ctyp[$j]= 0; }

for($j= 1;$j <= $ne; $j++)
  {
  if($jtyp[$j] ==  2 || $jtyp[$j] == 13)                    { $ibflag_i1= 1; }
  if($jtyp[$j] == 18 || $jtyp[$j] == 19 || $jtyp[$j] == 20) { $ipflag_i1= 1; }
  if($jtyp[$j] == 23 || $jtyp[$j] == 24)                    { $ihflag_i1= 1; }

  $ctyp[$jtyp[$j]]++;
  }

if($ifnii1 == 0) 
  {
  if($LANG == 1) { print "berechnet: ibflag=$ibflag_i1, ipflag=$ipflag_i1, ihflag=$ihflag_i1\n"; }
  if($LANG == 2) { print "computed: ibflag=$ibflag_i1, ipflag=$ipflag_i1, ihflag=$ihflag_i1\n"; }
  }

for($j= 1;$j <= 24; $j++)
  {
  if($ctyp[$j] > 0)
    {
    if($LANG == 1) { print "$ctyp[$j] Elemente vom Typ $j entdeckt\n"; }
    if($LANG == 2) { print "$ctyp[$j] elements of type $j detected\n"; }
    }
  }

if($ifnii1 == 0)
  {
  if($LANG == 1) { print "Elementinfos koennten okay sein\n"; }
  if($LANG == 2) { print "element infos may be okay\n"; }
  if($LANG == 1) { print "z88i1.txt gecheckt, keine Fehler entdeckt\n"; }
  if($LANG == 2) { print "z88i1.txt checked, no errors detected\n"; }
  }
if($ifnii1 == 1)
  {
  if($LANG == 1) { print "Superelementinfos koennten okay sein\n"; }
  if($LANG == 2) { print "super element infos may be okay\n"; }
  }

return 0;
}

#***********************************************************************
# G4I188: Zusatzinfos fuer Netzgenerator checken
#***********************************************************************
sub G4I188 {

if($LANG == 1) { print "untersuche Zerlegeinfos von z88ni.txt\n"; }
if($LANG == 2) { print "investigating mesher infos of z88ni.txt\n"; }

#-----------------------------------------------------------------------
# Schleife ueber alle Elemente: alle Elemente gleich ?
#----------------------------------------------------------------------- 
$jtypalt= $jtyp[1];
        
for($i = 2;$i <= $ne;$i++)
  {
  if($jtyp[$i] != $jtypalt)
    {
    if($LANG == 1) { print "ungleiche Superelementtypen entdeckt...Stop\n"; }
    if($LANG == 2) { print "different super element types detected...stop\n"; }
    return 1;
    }
  }

#-----------------------------------------------------------------------
# Schleife ueber alle Elemente: Zerlegeinfos untersuchen
#----------------------------------------------------------------------- 
for($j = 1;$j <= $ne;$j++)
  {  
  chomp($zeile1 = <I1>);
  @ts1= split " ",$zeile1;

  $n++;

  for($i= 0; $i <= 1;$i++)
    {
    if($ts1[$i]=~ /[A-DF-Za-df-z,_#;:]/)
      {
      if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
      if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
      return 1;
      }
    }

  $iele= $ts1[0];
  $ityp= $ts1[1];

#=======================================================================
# logische Pruefung 1.Zeile 4.Gruppe
#======================================================================= 
  if($iele != $j)
    {
    if($LANG == 1) { print "Superele-Nr. in Zeile $n falsch...Stop\n"; }
    if($LANG == 2) { print "super ele. no in line $n wrong...stop\n"; }
    return 1;
    }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# passen die angeforderten FE-Typen zu den Superelementen?
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  if($jtyp[$j] == 10)
    {
    if(!($ityp == 1 || $ityp == 10))
      {
      if($LANG == 1) { print "Nur Ele. Typ 1 oder 10 in Zeile $n moeglich...Stop\n"; }
      if($LANG == 2) { print "only ele. type 1 or 10 in line $n allowed...stop\n"; }
      return 1;
      }
    }
  elsif($jtyp[$j] == 1)
    {
    if(!($ityp == 1))
      {
      if($LANG == 1) { print "Nur Ele. Typ 1 in Zeile $n moeglich...Stop\n"; }
      if($LANG == 2) { print "only ele. type 1 in line $n allowed...stop\n"; }
      return 1;
      }
    }
  elsif($jtyp[$j] == 7 || $jtyp[$j] == 11)
    {
    if(!($ityp == 7))
      {
      if($LANG == 1) { print "Nur Ele. Typ 7 in Zeile $n moeglich...Stop\n"; }
      if($LANG == 2) { print "only ele. type 7 in line $n allowed...stop\n"; }
      return 1;
      }
    }
  elsif($jtyp[$j] == 8 || $jtyp[$j] == 12)
    {
    if(!($ityp == 8))
      {
      if($LANG == 1) { print "Nur Ele. Typ 8 in Zeile $n moeglich...Stop\n"; }
      if($LANG == 2) { print "only ele. type 8 in line $n allowed...stop\n"; }
      return 1;
      }
    }
  elsif($jtyp[$j] == 20)
    {
    if(!($ityp == 19 || $ityp == 20))
      {
      if($LANG == 1) { print "Nur Ele. Typ 19 oder 20 in Zeile $n moeglich...Stop\n"; }
      if($LANG == 2) { print "only ele. type 19 or 20 in line $n allowed...stop\n"; }
      return 1;
      }
    }
  elsif($jtyp[$j] == 21)
    {
    if(!($ityp == 21))
      {
      if($LANG == 1) { print "Nur Ele. Typ 21 in Zeile $n moeglich...Stop\n"; }
      if($LANG == 2) { print "only ele. type 21 in line $n allowed...stop\n"; }
      return 1;
      }
    }
  else
    {
    if($LANG == 1) { print "Elementtyp in Zeile $n nicht moeglich...Stop\n"; }
    if($LANG == 2) { print "element type in line $n not allowed...stop\n"; }
    return 1;
    }

#-----------------------------------------------------------------------
# logische Pruefung 2.Zeile 4.Gruppe
#----------------------------------------------------------------------- 
  chomp($zeile2 = <I1>);
  @ts2= split " ",$zeile2;

  $n++;

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 2D-Lesen
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  if($ndim == 2)
    {
    for($i= 0; $i <= 3;$i++)
      {
      if($ts2[$i]=~ /[A-DF-KM-Za-df-km-z,_#;:]/)
        {
        if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
        return 1;
        }
      }

    $ix    = $ts2[0];
    $cmodex= $ts2[1];
    $iy    = $ts2[2];
    $cmodey= $ts2[3];
    }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 3D-Lesen
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  if($ndim == 3)
    {
    for($i= 0; $i <= 5;$i++)
      {
      if($ts2[$i]=~ /[A-DF-KM-Za-df-km-z,_#;:]/)
        {
        if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
        return 1;
        }
      }

    $ix    = $ts2[0];
    $cmodex= $ts2[1];
    $iy    = $ts2[2];
    $cmodey= $ts2[3];
    $iz    = $ts2[4];
    $cmodez= $ts2[5];
    }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# 2.Zeile untersuchen
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
  if($ix < 1)
    {
    if($LANG == 1) { print "Unterteilung x in Zeile $n unzulaessig...Stop\n"; }
    if($LANG == 2) { print "subdivision x in line $n not allowed...stop\n"; }
    return 1;
    }

  if(!($cmodex eq "E" || $cmodex eq "e" || $cmodex eq "L" || $cmodex eq "l"))
    {
    if($LANG == 1) { print "Art der Unterteilung x in Zeile $n unzulaessig...Stop\n"; }
    if($LANG == 2) { print "type of subdivision x in line $n not allowed...stop\n"; }
    return 1;
    }

  if($iy < 1)
    {
    if($LANG == 1) { print "Unterteilung y in Zeile $n unzulaessig...Stop\n"; }
    if($LANG == 2) { print "subdivision y in line $n not allowed...stop\n"; }
    return 1;
    }

  if(!($cmodey eq "E" || $cmodey eq "e" || $cmodey eq "L" || $cmodey eq "l"))
    {
    if($LANG == 1) { print "Art der Unterteilung y in Zeile $n unzulaessig...Stop\n"; }
    if($LANG == 2) { print "type of subdivision y in line $n not allowed...stop\n"; }
    return 1;
    }

  if($ndim == 3)
    {
    if($iz < 1)
      {
      if($LANG == 1) { print "Unterteilung z in Zeile $n unzulaessig...Stop\n"; }
      if($LANG == 2) { print "subdivision z in line $n not allowed...stop\n"; }
      return 1;
      }

    if(!($cmodez eq "E" || $cmodez eq "e" || $cmodez eq "L" || $cmodez eq "l"))
      {
      if($LANG == 1) { print "Art der Unterteilung z in Zeile $n unzulaessig...Stop\n"; }
      if($LANG == 2) { print "type of subdivision z in line $n not allowed...stop\n"; }
      return 1;
      }
    }

  } # end for

#-----------------------------------------------------------------------
# Fangradien okay?
#----------------------------------------------------------------------- 
if($niflag == 1)
  {
  chomp($zeile3 = <I1>);
  @ts3= split " ",$zeile3;

  $n++;

  if($ndim == 2)
    {
    for($i= 0; $i <= 1;$i++)
      {
      if($ts3[$i]=~ /[A-DF-Za-df-z,_#;:]/)
        {
        if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
        return 1;
        }
      }
    $epsx= $ts3[0];
    $epsy= $ts3[1];

    if(abs($epsx) <= 1e-13 || abs($epsy) <= 1e-13)
      {
      if($LANG == 1) { print "Fangradien in Zeile $n sehr klein...Stop\n"; }
      if($LANG == 2) { print "trap radius in line $n very small...stop\n"; }
      return 1;
      }
    }

  if($ndim == 3)
    {
    for($i= 0; $i <= 2;$i++)
      {
      if($ts3[$i]=~ /[A-DF-Za-df-z,_#;:]/)
        {
        if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
        return 1;
        }
      }
    $epsx= $ts3[0];
    $epsy= $ts3[1];
    $epsz= $ts3[2];

    if(abs($epsx) <= 1e-13 || abs($epsy) <= 1e-13 || abs($epsz) <= 1e-13)
      {
      if($LANG == 1) { print "Fangradien in Zeile $n sehr klein...Stop\n"; }
      if($LANG == 2) { print "trap radius in line $n very small...stop\n"; }
      return 1;
      }
    }

  } # end if

if($LANG == 1) { print "Zerlegeinfos von z88ni.txt koennten okay sein\n"; }
if($LANG == 2) { print "mesher infos of z88ni.txt may be okay\n"; }
if($LANG == 1) { print "z88ni.txt gecheckt, keine Fehler entdeckt\n"; }
if($LANG == 2) { print "z88ni.txt checked, no errors detected\n"; }

return 0;
}

#***********************************************************************
# GXI288: Z88I2.TXT checken
#***********************************************************************
sub GXI288 {

#-----------------------------------------------------------------------
# 1.Zeile Z88I2.TXT untersuchen
#----------------------------------------------------------------------- 
print "\n***************************************************\n";
if($LANG == 1) { print "untersuche 1.Zeile von z88i2.txt\n"; }
if($LANG == 2) { print "investigating 1st line of z88i2.txt\n"; }

chomp($zeile = <I2>);
@ts= split " ",$zeile;

if($ts[0]=~ /[A-DF-Za-df-z,_#;:]/)
  {
  if($LANG == 1) { print "Schreibfehler in 1.Zeile entdeckt...Stop\n"; }
  if($LANG == 2) { print "typing error in 1st line detected...stop\n"; }
  return 1;
  }

$nrb = $ts[0];

if($LANG == 1) { print "$nrb Randbedingungen entdeckt\n"; }
if($LANG == 2) { print "$nrb constraints detected\n"; }

if($nrb > $nfg)
  {
  if($LANG == 1) { print "zuviele Randbedingungen in 1.Zeile endeckt...Stop\n"; }
  if($LANG == 2) { print "too many constraints in 1st line detected...stop\n"; }
  return 1;
  }

if($ndim == 2)
  {
  if($nrb < 4 && !($ctyp[6] > 0 || $ctyp[8] > 0 || $ctyp[12] > 0 || $ctyp[15] > 0))
    {
    if($LANG == 1) { print "zuwenig RB (<4) fuer 2D in 1.Zeile endeckt...Stop\n"; }
    if($LANG == 2) { print "too few BC (<4) for 2D in 1st line detected...stop\n"; }
    return 1;
    }
  if($nrb < 2 && ($ctyp[6] > 0 || $ctyp[8] > 0 || $ctyp[12] > 0 || $ctyp[15] > 0))
    {
    if($LANG == 1) { print "zuwenig RB (<2) fuer 2D in 1.Zeile endeckt...Stop\n"; }
    if($LANG == 2) { print "too few BC (<2) for 2D in 1st line detected...stop\n"; }
    return 1;
    }
  }

if($ndim == 3)
  {
  if($nrb < 6)
    {
    if($LANG == 1) { print "zuwenig RB (<6) fuer 3D in 1.Zeile endeckt...Stop\n"; }
    if($LANG == 2) { print "too few BC (<6) for 3D in 1st line detected...stop\n"; }
    return 1;
    }
  }

#-----------------------------------------------------------------------
# die Randbedingungen von Z88I2.TXT untersuchen
#----------------------------------------------------------------------- 
if($LANG == 1) { print "untersuche Randbedingungen von z88i2.txt\n"; }
if($LANG == 2) { print "investigating boundary conditions of z88i2.txt\n"; }

$nknalt= 0;
$ifgalt= 0;
$n= 1;
$forc= 0;
$disp= 0;

for($j= 1;$j <= $nrb; $j++)
  {
  $n++;

  chomp($zeile = <I2>);
  @ts= split " ",$zeile;

  for($i= 0; $i <= 3;$i++)
    {
    if($ts[$i]=~ /[A-DF-Za-df-z,_#;:]/)
      {
      if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
      if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
      return 1;
      }
    }

  if($j > 1)
    {
    $nknalt= $nkn;
    $ifgalt= $ifg;
    }

  $nkn   = $ts[0];
  $ifg   = $ts[1];
  $iflag1= $ts[2];

  if($iflag1 == 1) { $forc++; }
  if($iflag1 == 2) { $disp++; }

#=======================================================================
# logische Pruefung
#======================================================================= 
  if($nkn < 1 || $nkn > $nkp)
    {
    if($LANG == 1) { print "Knotennummer in Zeile $n ungueltig...Stop\n"; }
    if($LANG == 2) { print "nodal number in line $n out of range...stop\n"; }
    return 1;
    }

  if($j > 1)
    { 
    if($nkn < $nknalt)
      {
      if($LANG == 1) { print "Knotennummern in Zeile $n nicht aufsteigend...Stop\n"; }
      if($LANG == 2) { print "nodal number in line $n not ascending...stop\n"; }
      return 1;
      }
    }

  if($ifg < 1)
    {
    if($LANG == 1) { print "FG in Zeile $n < 1...Stop\n"; }
    if($LANG == 2) { print "DOF in line $n < 1...stop\n"; }
    return 1;
    }

  if($ifg > $ifrei[$nkn])
    {
    if($LANG == 1) { print "FG in Zeile $n > als in z88i1.txt...Stop\n"; }
    if($LANG == 2) { print "DOF in line $n > than in z88i1.txt...stop\n"; }
    return 1;
    }

  if($nkn == $nknalt)
    { 
    if($ifg <= $ifgalt)
      {
      if($LANG == 1) { print "#FG in Zeile $n nicht aufsteigend...Stop\n"; }
      if($LANG == 2) { print "#DOF in line $n not ascending...stop\n"; }
      return 1;
      }
    }

  if(!($iflag1 == 1 || $iflag1 == 2))
    {
    if($LANG == 1) { print "Steuerflag in Zeile $n nicht 1 oder 2...Stop\n"; }
    if($LANG == 2) { print "load/displacement flag in line $n not 1 or 2...stop\n"; }
    return 1;
    }
  }

if($LANG == 1) { print "$forc Kraft-RB und $disp Weg-RB entdeckt\n"; }
if($LANG == 2) { print "$forc BC/forces and $disp BC/displacements detected\n"; }

if($LANG == 1) { print "Randbedingungen koennten okay sein\n"; }
if($LANG == 2) { print "boundary conditions may be okay\n"; }

if($LANG == 1) { print "z88i2.txt gecheckt, keine Fehler entdeckt\n"; }
if($LANG == 2) { print "z88i2.txt checked, no errors detected\n"; }

return 0;
}

#***********************************************************************
# GXI588: Z88I5.TXT checken
#***********************************************************************
sub GXI588 {

#-----------------------------------------------------------------------
# 1.Zeile Z88I5.TXT untersuchen
#----------------------------------------------------------------------- 
print "\n***************************************************\n";
if($LANG == 1) { print "untersuche 1.Zeile von z88i5.txt\n"; }
if($LANG == 2) { print "investigating 1st line of z88i5.txt\n"; }

chomp($zeile = <I5>);
@ts= split " ",$zeile;

if($ts[0]=~ /[A-DF-Za-df-z,_#;:]/)
  {
  if($LANG == 1) { print "Schreibfehler in 1.Zeile entdeckt...Stop\n"; }
  if($LANG == 2) { print "typing error in 1st line detected...stop\n"; }
  return 1;
  }

$npr = $ts[0];

if($npr > 0) # Flaechenlasten 
  {
  if($LANG == 1) { print "$npr Flaechenlasten entdeckt\n"; }
  if($LANG == 2) { print "$npr surface loads detected\n"; }
  }

if($npr == 0) # keine Flaechenlasten, also zurueck 
  {
  if($LANG == 1) { print "keine Flaechenlasten entdeckt\n"; }
  if($LANG == 2) { print "no surface loads detected\n"; }
  return 0;
  }

if($npr > $ne)
  {
  if($LANG == 1) { print "zuviele Flaechenlasten in 1.Zeile endeckt...Stop\n"; }
  if($LANG == 2) { print "too many surface loads in 1st line detected...stop\n"; }
  return 1;
  }

if($npr < 0)
  {
  if($LANG == 1) { print "zuwenig Flaechenlasten in 1.Zeile endeckt...Stop\n"; }
  if($LANG == 2) { print "too few surface loads in 1st line detected...stop\n"; }
  return 1;
  }

#-----------------------------------------------------------------------
# die Flaechenlasten von Z88I5.TXT untersuchen
#----------------------------------------------------------------------- 
if($LANG == 1) { print "untersuche Flaechenlasten von z88i5.txt\n"; }
if($LANG == 2) { print "investigating surface loads of z88i5.txt\n"; }

$n= 1;

for($j= 1;$j <= $npr; $j++)
  {
  $n++;

  chomp($zeile = <I5>);
  @ts= split " ",$zeile;

  if($ts[$0]=~ /[A-DF-Za-df-z,_#;:]/)
    {
    if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
    if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
    return 1;
    }

  $jele= $ts[0];

#=======================================================================
# logische Pruefung
#======================================================================= 
  if($jele < 1 || $jele > $ne)
    {
    if($LANG == 1) { print "Elementnummer in Zeile $n ungueltig...Stop\n"; }
    if($LANG == 2) { print "element number in line $n out of range...stop\n"; }
    return 1;
    }

  $ityp= $jtyp[$jele];

  if($ityp == 2 || $ityp == 3 || $ityp == 4 || $ityp == 5 || $ityp == 6 ||
     $ityp == 9 || $ityp == 13)
    {
    if($LANG == 1) { print "Elementtyp in Zeile $n nicht fuer Flaechenlasten geeignet...Stop\n"; }
    if($LANG == 2) { print "element type in line $n not not allowed for surface loads...stop\n"; }
    return 1;
    }

#=======================================================================
# Elementtyp 1
#======================================================================= 
  if($ityp == 1)
    {
    for($i= 1; $i <= 7;$i++)  # $ts[0] wurde schon gecheckt
      {
      if($ts[$i]=~ /[A-DF-Za-df-z,_#;:]/)
        {
        if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
        return 1;
        }
      }
    
    for($i= 1; $i <= 4;$i++)
      {
      $noi[$i]= $ts[$i+3];
      }
    $jmax= 4;
    }

#=======================================================================
# Elementtyp 10 und 21
#======================================================================= 
  if($ityp == 10 || $ityp == 21)
    {
    for($i= 1; $i <= 11;$i++)  # $ts[0] wurde schon gecheckt
      {
      if($ts[$i]=~ /[A-DF-Za-df-z,_#;:]/)
        {
        if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
        return 1;
        }
      }
    
    for($i= 1; $i <= 8;$i++)
      {
      $noi[$i]= $ts[$i+3];
      }
    $jmax= 8;
    }

#=======================================================================
# Elementtyp 17
#======================================================================= 
  if($ityp == 17)
    {
    for($i= 1; $i <= 4;$i++)  # $ts[0] wurde schon gecheckt
      {
      if($ts[$i]=~ /[A-DF-Za-df-z,_#;:]/)
        {
        if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
        return 1;
        }
      }
    
    for($i= 1; $i <= 3;$i++)
      {
      $noi[$i]= $ts[$i+1];
      }
    $jmax= 3;
    }

#=======================================================================
# Elementtyp 16 und 22
#======================================================================= 
  if($ityp == 16 || $ityp == 22)
    {
    for($i= 1; $i <= 7;$i++)  # $ts[0] wurde schon gecheckt
      {

      if($ts[$i]=~ /[A-DF-Za-df-z,_#;:]/)
        {
        if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
        return 1;
        }
      }
    
    for($i= 1; $i <= 6;$i++)
      {
      $noi[$i]= $ts[$i+1];
      }
    $jmax= 6;
    }

#=======================================================================
# Elementtyp 7,8,14,15
#======================================================================= 
  if($ityp == 7 || $ityp == 8 || $ityp == 14 || $ityp == 15)
    {
    for($i= 1; $i <= 5;$i++)  # $ts[0] wurde schon gecheckt
      {
      if($ts[$i]=~ /[A-DF-Za-df-z,_#;:]/)
        {
        if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
        return 1;
        }
      }
    
    for($i= 1; $i <= 3;$i++)
      {
      $noi[$i]= $ts[$i+2];
      }
    $jmax= 3;
    }

#=======================================================================
# Elementtyp 11,12
#======================================================================= 
  if($ityp == 11 || $ityp == 12)
    {
    for($i= 1; $i <= 6;$i++)  # $ts[0] wurde schon gecheckt
      {
      if($ts[$i]=~ /[A-DF-Za-df-z,_#;:]/)
        {
        if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
        return 1;
        }
      }
    
    for($i= 1; $i <= 4;$i++)
      {
      $noi[$i]= $ts[$i+2];
      }
    $jmax= 4;
    }

#=======================================================================
# Elementtyp 18,19,20,23 und 24
#======================================================================= 
  if($ityp == 18 || $ityp == 19 || $ityp == 20 || $ityp == 23 || $ityp == 24)
    {
    if($ts[1]=~ /[A-DF-Za-df-z,_#;:]/)
      {
      if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
      if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
      return 1;
      }
    $jmax= 0;
    }

#=======================================================================
# noi(i) innerhalb logischer Grenzen ?
#=======================================================================
  for($i = 1;$i <= $jmax;$i++)
    {
    if(!($noi[$i] > 0 && $noi[$i] <= $nkp))
      {
      if($LANG == 1) { print "Knotennummer in Zeile $n nicht 1 ~ $nkp...Stop\n"; }
      if($LANG == 2) { print "nodal number in line $n not 1 ~ $nkp...stop\n"; }
      return 1;
      }
    }

  for($i = 1;$i <= $jmax-1;$i++)
    {
    for($k= $i+1;$k <= $jmax;$k++)
      {
      if($noi[$i] == $noi[$k])
        {
        if($LANG == 1) { print "identische Knoten in Zeile $n entdeckt...Stop\n"; }
        if($LANG == 2) { print "identical node in line $n detected...stop\n"; }
        return 1;
        }
      }
    }

  }  # Ende grosse Schleife

if($LANG == 1) { print "Flaechenlasten koennten okay sein\n"; }
if($LANG == 2) { print "surface loads may be okay\n"; }

if($LANG == 1) { print "z88i5.txt gecheckt, keine Fehler entdeckt\n"; }
if($LANG == 2) { print "z88i5.txt checked, no errors detected\n"; }

return 0;
}

#***********************************************************************
# GMAN88: Z88MAN.TXT checken
#***********************************************************************
sub GMAN88 {

print "\n***************************************************\n";
if($LANG == 1) { print "untersuche z88man.txt\n"; }
if($LANG == 2) { print "investigating z88man.txt\n"; }

while ($zeile = <MAN>)
  {
  chomp($zeile);  # chomp erst hier, nicht im while wg. -w
  @ts= split " ",$zeile;
  if(@ts == 0) { next; } # wg. -w

#-----------------------------------------------------------------------
# IBFLAG?
#----------------------------------------------------------------------- 
  if($ts[0] eq "IBFLAG")
    {
    $ibflag= $ts[1];
    print "IBFLAG=$ibflag\n";

    if(($ibflag != $ibflag_i1) && $ibflag_i1 == 1)
      {
      if($LANG == 1) { print "IBFLAG falsch, es wurden Balken in z88i1.txt entdeckt...Stop\n"; }
      if($LANG == 2) { print "IBFLAG wrong, beams were detected in z88i1.txt...stop\n"; }
      return 1;
      }
    if(($ibflag != $ibflag_i1) && $ibflag_i1 == 0)
      {
      if($LANG == 1) { print "IBFLAG falsch, es wurden keine Balken in z88i1.txt entdeckt...Stop\n"; }
      if($LANG == 2) { print "IBFLAG wrong, no beams were detected in z88i1.txt...stop\n"; }
      return 1;
      }
    }

#-----------------------------------------------------------------------
# IPFLAG?
#----------------------------------------------------------------------- 
  if($ts[0] eq "IPFLAG")
    {
    $ipflag= $ts[1];
    print "IPFLAG=$ipflag\n";

    if($ipflag >= 1) { $ipflag= 1; }  # ipflag kann 0,1,2,2,3,4 sein

    if(($ipflag != $ipflag_i1) && $ipflag_i1 == 1)
      {
      if($LANG == 1) { print "IPFLAG falsch, es wurden Platten in z88i1.txt entdeckt...Stop\n"; }
      if($LANG == 2) { print "IPFLAG wrong, plates were detected in z88i1.txt...stop\n"; }
      return 1;
      }
    if(($ipflag != $ipflag_i1) && $ipflag_i1 == 0)
      {
      if($LANG == 1) { print "IPFLAG falsch, es wurden keine Platten in z88i1.txt entdeckt...Stop\n"; }
      if($LANG == 2) { print "IPFLAG wrong, no plates were detected in z88i1.txt...stop\n"; }
      return 1;
      }
    }

#-----------------------------------------------------------------------
# IHFLAG?
#----------------------------------------------------------------------- 
  if($ts[0] eq "IHFLAG")
    {
    $ihflag= $ts[1];
    print "IHFLAG=$ihflag\n";

    if($ihflag >= 1) { $ihflag= 1; }  # ihflag kann 0,1,2,2,3,4 sein

    if(($ihflag != $ihflag_i1) && $ihflag_i1 == 1)
      {
      if($LANG == 1) { print "IHFLAG falsch, es wurden Schalen in z88i1.txt entdeckt...Stop\n"; }
      if($LANG == 2) { print "IHFLAG wrong, shells were detected in z88i1.txt...stop\n"; }
      return 1;
      }
    if(($ihflag != $ihflag_i1) && $ihflag_i1 == 0)
      {
      if($LANG == 1) { print "IHFLAG falsch, es wurden keine Schalen in z88i1.txt entdeckt...Stop\n"; }
      if($LANG == 2) { print "IHFLAG wrong, no shells were detected in z88i1.txt...stop\n"; }
      return 1;
      }
    }

#-----------------------------------------------------------------------
# KDFLAG?
#----------------------------------------------------------------------- 
  if($ts[0] eq "KDFLAG")
    {
    $kdflag= $ts[1];

    if($kdflag == 1 && !($ctyp[3] > 0 || $ctyp[7] > 0 || $ctyp[11] > 0 || $ctyp[14] > 0))
      {
      if($LANG == 1) { print "KDFLAG=1: nur sinnvoll fuer Scheiben Nr.3,7,11,14\n"; }
      if($LANG == 2) { print "KDFLAG=1: only usefull for plain stress ele 3,7,11,14\n"; }
      }
    else
      {
      print "KDFLAG=$kdflag\n";
      }
    }

#-----------------------------------------------------------------------
# ISFLAG?
#----------------------------------------------------------------------- 
  if($ts[0] eq "ISFLAG")
    {
    $isflag= $ts[1];

    if($isflag < 0 || $isflag > 3)
      {
      if($LANG == 1) { print "ISFLAG=$isflag, unzulaessig...Stop \n"; }
      if($LANG == 2) { print "ISFLAG=$isflag, out of range...stop\n"; }
      return 1;
      }

    if($isflag > 0 && ($ctyp[2] > 0 || $ctyp[5] > 0 || $ctyp[13] > 0))
      {
      if($LANG == 1) { print "ISFLAG=1: unnuetz fuer Balken Nr.2,5 und 13\n"; }
      if($LANG == 2) { print "ISFLAG=1: useless for beam ele 2,5 & 13\n"; }
      }
    else
      {
      print "ISFLAG=$isflag\n";
      }
    }

  } # end while

if($LANG == 1) { print "z88man.txt gecheckt, keine Fehler entdeckt\n"; }
if($LANG == 2) { print "z88man.txt checked, no errors detected\n"; }

return 0;
}

#***********************************************************************
# GMAT88: Z88MAT.TXT checken
#***********************************************************************
sub GMAT88 {

#-----------------------------------------------------------------------
# 1.Zeile Z88MAT.TXT untersuchen
#----------------------------------------------------------------------- 
print "\n***************************************************\n";
if($LANG == 1) { print "untersuche 1.Zeile von z88mat.txt\n"; }
if($LANG == 2) { print "investigating 1st line of z88mat.txt\n"; }

chomp($zeile = <MAT>);
@ts= split " ",$zeile;

if($ts[0]=~ /[A-DF-Za-df-z,_#;:]/)
  {
  if($LANG == 1) { print "Schreibfehler in 1.Zeile entdeckt...Stop\n"; }
  if($LANG == 2) { print "typing error in 1st line detected...stop\n"; }
  return 1;
  }

$mmat = $ts[0];

if($LANG == 1) { print "$mmat Material-Gruppen entdeckt\n"; }
if($LANG == 2) { print "$mmat material groups detected\n"; }

if($mmat > $ne)
  {
  if($LANG == 1) { print "zuviele Materialien in 1.Zeile endeckt...Stop\n"; }
  if($LANG == 2) { print "too many materials in 1st line detected...stop\n"; }
  return 1;
  }

if($mmat < 1)
  {
  if($LANG == 1) { print "zuwenig Materialien in 1.Zeile endeckt...Stop\n"; }
  if($LANG == 2) { print "too few materials in 1st line detected...stop\n"; }
  return 1;
  }

#-----------------------------------------------------------------------
# die Materialzeilen von Z88MAT.TXT untersuchen
#----------------------------------------------------------------------- 
if($LANG == 1) { print "untersuche Materialgruppen von z88mat.txt\n"; }
if($LANG == 2) { print "investigating material groups of z88mat.txt\n"; }

$n= 1;
$ibisalt= 0;
$ibis= 0;

for($j= 1;$j <= $mmat; $j++)
  {
  $n++;
  
  if($j > 1) { $ibisalt= $ibis; }

  chomp($zeile = <MAT>);
  @ts= split " ",$zeile;

  for($i= 0; $i <= 1;$i++)  # nur ivon und ibis checken
    {
    if($ts[$i]=~ /[A-DF-Za-df-z,_#;:]/)
      {
      if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
      if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
      return 1;
      }
    }

  $ivon= $ts[0];
  $ibis= $ts[1];
  $ccsv= $ts[2];

  if($LANG == 1) { print "Materialgruppe $j: von $ivon bis $ibis mit $ccsv\n"; }
  if($LANG == 2) { print "material group $j: from $ivon to $ibis using $ccsv\n"; }

#=======================================================================
# ivon?
#=======================================================================
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Sonderfall 1. E-Gesetz:
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($j == 1)
    {
    if($ivon != 1)
      {
      if($LANG == 1) { print "Startwert 1.E-Gesetz in Zeile $n nicht 1...Stop\n"; }
      if($LANG == 2) { print "start value 1st mat group in line $n not 1...stop\n"; }
      return 1;
      }
    }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ivon groesser als ibis?
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($ivon > $ibis)
    {
    if($LANG == 1) { print "Anfangswert in Zeile $n groesser als Endwert...Stop\n"; }
    if($LANG == 2) { print "start value in line $n bigger than end value...stop\n"; }
    return 1;
    }

#=======================================================================
# ibis?
#=======================================================================
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ibis groesser als ne?
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($ibis > $ne)
    {
    if($LANG == 1) { print "Endwert in Zeile $n groesser als Anzahl Elemente entdeckt...Stop\n"; }
    if($LANG == 2) { print "end value in line $n bigger than no. of elements detected...stop\n"; }
    return 1;
    }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# j > 1: ivon nicht ibisalt +1 ?
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($j > 1)
    {
    if($ivon != $ibisalt+1)
      {
      $n1= $n-1;
      if($LANG == 1) { print "Endwert in Zeile $n1 nicht Anfangswert-1 der Zeile $n entdeckt...Stop\n"; }
      if($LANG == 2) { print "end value in line $n1 not (start value-1) of line $n detected...stop\n"; }
      return 1;
      }
    }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Sonderfall letztes E-Gesetz:
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($j == $mmat)
    {
    if($ibis != $ne)
      {
      if($LANG == 1) { print "Endwert in Zeile $n nicht Anzahl Elemente entdeckt...Stop\n"; }
      if($LANG == 2) { print "end value in line $n not no. of elements detected...stop\n"; }
      return 1;
      }
    }


  }  # end for

if($LANG == 1) { print "Materialgruppen koennten okay sein\n"; }
if($LANG == 2) { print "material groups may be okay\n"; }

if($LANG == 1) { print "z88mat.txt gecheckt, keine Fehler entdeckt\n"; }
if($LANG == 2) { print "z88mat.txt checked, no errors detected\n"; }

return 0;
}

#***********************************************************************
# GELP88: Z88ELP.TXT checken
#***********************************************************************
sub GELP88 {

#-----------------------------------------------------------------------
# 1.Zeile Z88ELP.TXT untersuchen
#----------------------------------------------------------------------- 
print "\n***************************************************\n";
if($LANG == 1) { print "untersuche 1.Zeile von z88elp.txt\n"; }
if($LANG == 2) { print "investigating 1st line of z88elp.txt\n"; }

chomp($zeile = <ELP>);
@ts= split " ",$zeile;

if($ts[0]=~ /[A-DF-Za-df-z,_#;:]/)
  {
  if($LANG == 1) { print "Schreibfehler in 1.Zeile entdeckt...Stop\n"; }
  if($LANG == 2) { print "typing error in 1st line detected...stop\n"; }
  return 1;
  }

$melp = $ts[0];

if($LANG == 1) { print "$melp Elementparameter-Gruppen entdeckt\n"; }
if($LANG == 2) { print "$melp element parameter groups detected\n"; }

if($melp > $ne)
  {
  if($LANG == 1) { print "zuviele Elementparameter-Gruppen in 1.Zeile endeckt...Stop\n"; }
  if($LANG == 2) { print "too many element parameter groups in 1st line detected...stop\n"; }
  return 1;
  }

if($melp < 1)
  {
  if($LANG == 1) { print "zuwenig Elementparameter-Gruppen in 1.Zeile endeckt...Stop\n"; }
  if($LANG == 2) { print "too few element parameter groups in 1st line detected...stop\n"; }
  return 1;
  }

#-----------------------------------------------------------------------
# die Elementparameter-Gruppen von Z88ELP.TXT untersuchen
#----------------------------------------------------------------------- 
if($LANG == 1) { print "untersuche Elementparameter-Gruppen von z88elp.txt\n"; }
if($LANG == 2) { print "investigating element parameter groups of z88elp.txt\n"; }

$n= 1;
$ibisalt_elp= 0;
$ibis_elp= 0;

for($j= 1;$j <= $melp; $j++)
  {
  $n++;
  
  if($j > 1) { $ibisalt_elp= $ibis_elp; }

  chomp($zeile = <ELP>);
  @ts= split " ",$zeile;

  for($i= 0; $i <= 8;$i++) 
    {
    if($ts[$i]=~ /[A-DF-Za-df-z,_#;:]/)
      {
      if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
      if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
      return 1;
      }
    }

  $ivon_elp= $ts[0];
  $ibis_elp= $ts[1];
  $qpara   = $ts[2];
  $riyy    = $ts[3];
  $eyy     = $ts[4];
  $rizz    = $ts[5];
  $ezz     = $ts[6];
  $rit     = $ts[7];
  $wt      = $ts[8];

  if($LANG == 1) { print "Elementparameter-Gruppe $j: von $ivon_elp bis $ibis_elp\n"; }
  if($LANG == 2) { print "element parameter group $j: from $ivon_elp to $ibis_elp\n"; }

#=======================================================================
# Parameter-Tests
#=======================================================================
  for($i= $ivon_elp;$i <= $ibis_elp;$i++)
    {
    $ityp= $jtyp[$i];

    if(($ityp ==  2 || $ityp ==  3 || $ityp ==  4 || $ityp ==  5 ||
        $ityp ==  7 || $ityp ==  9 || $ityp == 11 || $ityp == 13 ||
        $ityp == 14 || $ityp == 18 || $ityp == 19 || $ityp == 20 ||
        $ityp == 22 || $ityp == 24) && $qpara <= 0)
      {
      if($LANG == 1) { print "falsches qpara (3.Wert) in Zeile $n entdeckt...Stop\n"; }
      if($LANG == 2) { print "wrong qpara (3rd entry) in line $n detected...stop\n"; }
      return 1;
      }

    if($ityp ==  2 && ($riyy <= 0 || $eyy <= 0 || $rizz <= 0 ||
                       $ezz <= 0 || $rit <= 0 || $wt <= 0))
      {
      if($LANG == 1) { print "Balkenparameter fuer Element-Typ 2 in Zeile $n falsch...Stop\n"; }
      if($LANG == 2) { print "beam parameter for element type 2 in line $n wrong...stop\n"; }
      return 1;
      }

    if($ityp ==  13 && ($riyy != 0 || $eyy != 0 || $rizz <= 0 ||
                       $ezz <= 0 || $rit != 0 || $wt != 0))
      {
      if($LANG == 1) { print "Balkenparameter fuer Element-Typ 13 in Zeile $n falsch...Stop\n"; }
      if($LANG == 2) { print "beam parameter for element type 13 in line $n wrong...stop\n"; }
      return 1;
      }

    } # end for i

#=======================================================================
# ivon_elp?
#=======================================================================
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Sonderfall 1. Elementparameter-Zeile:
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($j == 1)
    {
    if($ivon_elp != 1)
      {
      if($LANG == 1) { print "Startwert 1.EP-Gruppe in Zeile $n nicht 1...Stop\n"; }
      if($LANG == 2) { print "start value 1st ep-group in line $n not 1...stop\n"; }
      return 1;
      }
    }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ivon_elp groesser als ibis_elp?
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($ivon_elp > $ibis_elp)
    {
    if($LANG == 1) { print "Anfangswert in Zeile $n groesser als Endwert...Stop\n"; }
    if($LANG == 2) { print "start value in line $n bigger than end value...stop\n"; }
    return 1;
    }

#=======================================================================
# ibis_elp?
#=======================================================================
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ibis_elp groesser als ne?
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($ibis_elp > $ne)
    {
    if($LANG == 1) { print "Endwert in Zeile $n groesser als Anzahl Elemente entdeckt...Stop\n"; }
    if($LANG == 2) { print "end value in line $n bigger than no. of elements detected...stop\n"; }
    return 1;
    }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# j > 1: ivon_elp nicht ibisalt_elp +1 ?
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($j > 1)
    {
    if($ivon_elp != $ibisalt_elp+1)
      {
      $n1= $n-1;
      if($LANG == 1) { print "Endwert in Zeile $n1 nicht Anfangswert-1 der Zeile $n entdeckt...Stop\n"; }
      if($LANG == 2) { print "end value in line $n1 not (start value-1) of line $n detected...stop\n"; }
      return 1;
      }
    }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Sonderfall letzte Elementparameter-Gruppe:
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($j == $melp)
    {
    if($ibis_elp != $ne)
      {
      if($LANG == 1) { print "Endwert in Zeile $n nicht Anzahl Elemente entdeckt...Stop\n"; }
      if($LANG == 2) { print "end value in line $n not no. of elements detected...stop\n"; }
      return 1;
      }
    }

  } # end for j

if($LANG == 1) { print "Elementparameter-Gruppen koennten okay sein\n"; }
if($LANG == 2) { print "element parameter groups may be okay\n"; }

if($LANG == 1) { print "z88elp.txt gecheckt, keine Fehler entdeckt\n"; }
if($LANG == 2) { print "z88elp.txt checked, no errors detected\n"; }

return 0;
}

#***********************************************************************
# GINT88: Z88INT.TXT checken
#***********************************************************************
sub GINT88 {

#-----------------------------------------------------------------------
# 1.Zeile Z88INT.TXT untersuchen
#----------------------------------------------------------------------- 
print "\n***************************************************\n";
if($LANG == 1) { print "untersuche 1.Zeile von z88int.txt\n"; }
if($LANG == 2) { print "investigating 1st line of z88int.txt\n"; }

chomp($zeile = <INT>);
@ts= split " ",$zeile;

if($ts[0]=~ /[A-DF-Za-df-z,_#;:]/)
  {
  if($LANG == 1) { print "Schreibfehler in 1.Zeile entdeckt...Stop\n"; }
  if($LANG == 2) { print "typing error in 1st line detected...stop\n"; }
  return 1;
  }

$mint = $ts[0];

if($LANG == 1) { print "$mint Integrationsordnungs-Gruppen entdeckt\n"; }
if($LANG == 2) { print "$mint integration order groups detected\n"; }

if($mint > $ne)
  {
  if($LANG == 1) { print "zuviele Integrationsordnungs-Gruppen in 1.Zeile endeckt...Stop\n"; }
  if($LANG == 2) { print "too many integration order groups in 1st line detected...stop\n"; }
  return 1;
  }

if($mint < 1)
  {
  if($LANG == 1) { print "zuwenig Integrationsordnungs-Gruppen in 1.Zeile endeckt...Stop\n"; }
  if($LANG == 2) { print "too few integration order groups in 1st line detected...stop\n"; }
  return 1;
  }

#-----------------------------------------------------------------------
# die Integrationsordnungs-Gruppen von Z88INT.TXT untersuchen
#----------------------------------------------------------------------- 
if($LANG == 1) { print "untersuche Integrationsordnungs-Gruppen von z88int.txt\n"; }
if($LANG == 2) { print "investigating integration order groups of z88int.txt\n"; }

$n= 1;
$ibisalt_int= 0;
$ibis_int= 0;

for($j= 1;$j <= $mint; $j++)
  {
  $n++;
  
  if($j > 1) { $ibisalt_int= $ibis_int; }

  chomp($zeile = <INT>);
  @ts= split " ",$zeile;

  for($i= 0; $i <= 3;$i++) 
    {
    if($ts[$i]=~ /[A-DF-Za-df-z,_#;:]/)
      {
      if($LANG == 1) { print "Schreibfehler in Zeile $n entdeckt...Stop\n"; }
      if($LANG == 2) { print "typing error in line $n detected...stop\n"; }
      return 1;
      }
    }

  $ivon_int= $ts[0];
  $ibis_int= $ts[1];
  $intord  = $ts[2];
  $intos   = $ts[3];

  if($LANG == 1) { print "Integrationsordnungs-Gruppe $j: von $ivon_int bis $ibis_int\n"; }
  if($LANG == 2) { print "integration order group $j: from $ivon_int to $ibis_int\n"; }

#=======================================================================
# Parameter-Tests
#=======================================================================
  for($i= $ivon_int;$i <= $ibis_int;$i++)
    {
    $ityp= $jtyp[$i];

    if(($ityp ==  1 || $ityp ==  7 || $ityp ==  8 || $ityp == 10 ||
        $ityp == 11 || $ityp == 12 || $ityp == 19 || $ityp == 20 ||
        $ityp == 21 || $ityp == 23) && ($intord < 1 || $intord > 4) )
      {
      if($LANG == 1) { print "falsches intord (3.Wert) fuer Ele-Typ $ityp in Zeile $n entdeckt...Stop\n"; }
      if($LANG == 2) { print "wrong intord (3rd entry) for ele type $ityp in line $n detected...stop\n"; }
      return 1;
      }

    if(($ityp ==  1 || $ityp ==  7 || $ityp ==  8 || $ityp == 10 ||
        $ityp == 11 || $ityp == 12 || $ityp == 19 || $ityp == 20 ||
        $ityp == 21 || $ityp == 23) && ($intos < 0 || $intos > 4) )
      {
      if($LANG == 1) { print "falsches intos (4.Wert) fuer Ele-Typ $ityp in Zeile $n entdeckt...Stop\n"; }
      if($LANG == 2) { print "wrong intos (4th entry) for ele type $ityp in line $n detected...stop\n"; }
      return 1;
      }

    if(($ityp == 14 || $ityp == 15 || $ityp == 18 || 
        $ityp == 22 || $ityp == 24) && 
      !($intord == 3 || $intord == 7 || $intord == 13) )
      {
      if($LANG == 1) { print "falsches intord (3.Wert) fuer Ele-Typ $ityp in Zeile $n entdeckt...Stop\n"; }
      if($LANG == 2) { print "wrong intord (3rd entry) for ele type $ityp in line $n detected...stop\n"; }
      return 1;
      }

    if(($ityp == 14 || $ityp == 15 || $ityp == 18 || 
        $ityp == 22 || $ityp == 24) && 
      !($intos == 0 || $intos == 3 || $intos == 7 || $intos == 13) )
      {
      if($LANG == 1) { print "falsches intord (3.Wert) fuer Ele-Typ $ityp in Zeile $n entdeckt...Stop\n"; }
      if($LANG == 2) { print "wrong intord (3rd entry) for ele type $ityp in line $n detected...stop\n"; }
      return 1;
      }

    if(($ityp == 16 || $ityp == 17) && 
      !($intord == 1 || $intord == 4 || $intord == 5) )
      {
      if($LANG == 1) { print "falsches intord (3.Wert) fuer Ele-Typ $ityp in Zeile $n entdeckt...Stop\n"; }
      if($LANG == 2) { print "wrong intord (3rd entry) for ele type $ityp in line $n detected...stop\n"; }
      return 1;
      }

    if(($ityp == 16 || $ityp == 17) && 
      !($intos == 0 || $intos == 1 || $intos == 4 || $intos == 5) )
      {
      if($LANG == 1) { print "falsches intord (3.Wert) fuer Ele-Typ $ityp in Zeile $n entdeckt...Stop\n"; }
      if($LANG == 2) { print "wrong intord (3rd entry) for ele type $ityp in line $n detected...stop\n"; }
      return 1;
      }

    } # end for i

#=======================================================================
# ivon_int?
#=======================================================================
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Sonderfall 1. Integrationsordnungs-Zeile:
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($j == 1)
    {
    if($ivon_int != 1)
      {
      if($LANG == 1) { print "Startwert 1.IO-Gruppe in Zeile $n nicht 1...Stop\n"; }
      if($LANG == 2) { print "start value 1st io-group in line $n not 1...stop\n"; }
      return 1;
      }
    }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ivon_int groesser als ibis_int?
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($ivon_int > $ibis_int)
    {
    if($LANG == 1) { print "Anfangswert in Zeile $n groesser als Endwert...Stop\n"; }
    if($LANG == 2) { print "start value in line $n bigger than end value...stop\n"; }
    return 1;
    }

#=======================================================================
# ibis_int?
#=======================================================================
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# ibis_int groesser als ne?
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($ibis_int > $ne)
    {
    if($LANG == 1) { print "Endwert in Zeile $n groesser als Anzahl Elemente entdeckt...Stop\n"; }
    if($LANG == 2) { print "end value in line $n bigger than no. of elements detected...stop\n"; }
    return 1;
    }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# j > 1: ivon_int nicht ibisalt_int +1 ?
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($j > 1)
    {
    if($ivon_int != $ibisalt_int+1)
      {
      $n1= $n-1;
      if($LANG == 1) { print "Endwert in Zeile $n1 nicht Anfangswert-1 der Zeile $n entdeckt...Stop\n"; }
      if($LANG == 2) { print "end value in line $n1 not (start value-1) of line $n detected...stop\n"; }
      return 1;
      }
    }

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Sonderfall letzte Gruppe:
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  if($j == $mint)
    {
    if($ibis_int != $ne)
      {
      if($LANG == 1) { print "Endwert in Zeile $n nicht Anzahl Elemente entdeckt...Stop\n"; }
      if($LANG == 2) { print "end value in line $n not no. of elements detected...stop\n"; }
      return 1;
      }
    }

  } # end for j

if($LANG == 1) { print "Integrationsordnungs-Gruppen koennten okay sein\n"; }
if($LANG == 2) { print "integration order groups may be okay\n"; }

if($LANG == 1) { print "z88int.txt gecheckt, keine Fehler entdeckt\n"; }
if($LANG == 2) { print "z88int.txt checked, no errors detected\n"; }

return 0;
}






