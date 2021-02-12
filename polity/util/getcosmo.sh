#!/bin/sh
# -*- coding: utf-8 -*-

command -v curl >/dev/null 2>&1 || { \
	echo 'curl was not found on your system. exiting...'; \
	exit 127; }
command -v unzip >/dev/null 2>&1 || { \
	echo 'unzip was not found on your system. exiting...'; \
	exit 127; }

echo 'Downloading the Cosmopolitan amalgamated binaries...' >/dev/stderr;
curl -fso common/build/cosmo.zip https://justine.lol/cosmopolitan/cosmopolitan-amalgamation-0.2.zip;

mkdir common/build/cosmo;

echo 'Extracting the binaries...' >/dev/stderr;
unzip -q common/build/cosmo.zip -x cosmopolitan.h -d common/build/cosmo;

echo 'Done.' >/dev/stderr;

exit 0;
