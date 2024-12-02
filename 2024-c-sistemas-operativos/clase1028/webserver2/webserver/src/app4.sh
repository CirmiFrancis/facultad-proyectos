#!/bin/bash
# script para compilacion de aplicacion app4
#
# Atte. Guillermo Cherencio
#
gcc -fPIC -Wall -g -c -o cgi.o cgi.c -I ../include
gcc -fPIC -Wall -g -c -o util.o util.c -I ../include
gcc -fPIC -Wall -g -c -o app4.o app4.c -I ../include
gcc -fPIC -shared -Wl,-soname,libapp4.so -o libapp4.so app4.o util.o cgi.o -lc
mv -f libapp4.so ../lib
rm app4.o
