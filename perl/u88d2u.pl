#**********************************************************
# u88d2u: dos2unix fuer Z88 als Perl-Script
# UNIX-Version
# vgl. "Perl Kochbuch", 7.16
# 4.3.2012 Rieg
#**********************************************************
use open IN => ":raw";

@ARGV= glob("*.txt *.dxf *.dyn");
$^I= ".sik";

while (<>)
  {
  s/\r\n/\n/g;
  print;
  }

