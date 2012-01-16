#!/bin/sh

CC=i586-mingw32msvc-gcc
CXX=i586-mingw32msvc-g++
CPP=i586-mingw32msvc-cpp
LD=i586-mingw32msvc-ld
AR=i586-mingw32msvc-ar
AS=i586-mingw32msvc-as
NM=i586-mingw32msvc-nm
STRIP=i586-mingw32msvc-strip
RANLIB=i586-mingw32msvc-ranlib
DLLTOOL=i586-mingw32msvc-dlltool
OBJDUMP=i586-mingw32msvc-objdump
RESCOMP=i586-mingw32msvc-windres

make -f Makefile.win clean
make -f Makefile.win
