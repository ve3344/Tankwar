
export PATH=/busybox-virtual:(c4droid:DATADIR):(c4droid:GCCROOT)bin:(c4droid:GCCROOT)(c4droid:PREFIX)/bin/:$PATH
export CC="(c4droid:PREFIX)-gcc (c4droid:PIE) (c4droid:MAKEMODEARGS)"
export CXX="(c4droid:PREFIX)-g++ (c4droid:PIE) (c4droid:MAKEMODEARGS)"
export SHELL="(c4droid:DATADIR)sh"
cd (c4droid:CURSRCDIR)