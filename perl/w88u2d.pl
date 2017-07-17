#**********************************************************
# w88u2d: unix2dos fuer Z88 als Perl-Script
# Windows-Version (nicht so perlish wie die UNIX-Version)
# vgl. "Perl Kochbuch", 7.15
# 4.3.2012 Rieg
#**********************************************************
print "W88U2D for Z88: UNIX files to Windows files\n";

@list= glob("*.txt *.dxf *.dyn");

foreach $datei (@list)
  {
  open FIN, "<:raw", $datei;
  open FOUT,">:raw", "hugo.tmp";

  while (<FIN>)
    {
    if(m/\r\n/) 
      { 
      print FOUT "$_";
      next; 
      }
    s/\n/\r\n/g;
    print FOUT "$_";
    }

  close FIN;
  close FOUT;
  rename($datei, "$datei.sik");
  rename("hugo.tmp", $datei);

  print "$datei processed\n";
  }

