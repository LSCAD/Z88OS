#**********************************************************
# w88d2u: dos2unix fuer Z88 als Perl-Script
# Windows-Version (nicht so perlish wie die UNIX-Version)
# vgl. "Perl Kochbuch", 7.15
# 4.3.2012 Rieg
#**********************************************************
print "W88D2U for Z88: Windows files to UNIX files\n";

@list= glob("*.txt *.dxf *.dyn");

foreach $datei (@list)
  {
  open FIN, "<:raw", $datei;
  open FOUT,">:raw", "hugo.tmp";

  while (<FIN>)
    {
    s/\r\n/\n/g;
    print FOUT "$_";
    }

  close FIN;
  close FOUT;
  rename($datei, "$datei.sik");
  rename("hugo.tmp", $datei);

  print "$datei processed\n";
  }

