#**********************************************************
# z88u2d: unix2dos fuer Z88 als Perl-Script
# fuer UNIX
# vgl. "Perl Kochbuch", 7.16
# 4.3.2012 Rieg
#**********************************************************
use open IN => ":raw";

@ARGV= glob("*.txt *.dxf *.dyn");
$^I= ".sik";

while (<>)
  {
  if(m/\r\n/) 
    { 
    print;
    next; 
    }
  s/\n/\r\n/g;
  print;
  }

