Z88 is a compact finite element program for Linux, Windows and Mac OS X.  
Open Source Version 15

#### About

Z88 is a compact, cross-platform finite element program including several submodules (converter, mapped mesher, solver ...) by Prof. Frank Rieg. This repository is not used for development but for distribution, it just gets updated on major releases. It is distributed under GNU GPL, so feel free to fork, modify and redistribute.  
For further information please see the included readme PDF-file or our website [www.z88.de](http://www.z88.de) where you also find our other free finite element software products.  

Z88 currently supports the following platforms:
- Windows (tested on Windows XP - Windows 10)
- MacOS (tested on Sierra 10.12.3)
- Linux (tested on OpenSUSE 13.1 and Ubuntu 16.04)

#### What's included

The Git repository includes:
```
Z88OS/             - root directory
├── bin/           - binaries for supported platforms
├── docu/          - detailed documentation both in English and German
├── examples/      - example projects
├── make/          - makefiles for supported platforms
├── perl/          - useful Perl scripts (such as converters and file-checkers)
├── src/           - source directory
│   ├── z88com/    - z88-commander
│   ├── z88g/      - 3D-converter for NASTRAN- and COSMOS- files
│   ├── z88n/      - mapped mesher
│   ├── z88o/      - plot program
│   ├── z88r/      - linear solver
│   └── z88x/      - DXF converter
├── LICENSE        - license
├── liesmich.pdf   - readme in German
├── readme.pdf     - readme in English
└── readme.md      - brief markdown readme
```

#### Support

If you have problems building or using z88 you get help by developers and other users at the [z88-board](http://forum.z88.de/).

---
Author:  
Prof. Dr.-Ing. Frank Rieg  
Department for engineering design and CAD  
University Bayreuth - Germany
