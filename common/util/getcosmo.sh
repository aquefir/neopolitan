#!/bin/sh
# -*- coding: utf-8 -*-

# sha256sum of cosmo.zip from the 0.2.0 release
_sum=27fc6e23898b8e0b5a7ca42b932c88ddfa0f2f7f306f72abe931128b72149c27

command -v curl >/dev/null 2>&1 || { \
	echo 'curl was not found on your system. Exiting...' >/dev/stderr; \
	exit 127; }
command -v unzip >/dev/null 2>&1 || { \
	echo 'unzip was not found on your system. Exiting...' >/dev/stderr; \
	exit 127; }
command -v sha256sum >/dev/null 2>&1 || {\
	echo 'sha256sum was not found on your system. Exiting...' >/dev/stderr; \
	exit 127; }

if [ -f common/build/cosmo.zip ]; then
	echo 'Cosmopolitan amalgamated binaries already downloaded. Skipping...' \
	>/dev/stderr;
else
	echo -n 'Downloading the Cosmopolitan amalgamated binaries... ' \
	>/dev/stderr;
	curl -sD common/build/headers.tmp -o common/build/cosmo.zip \
		https://justine.lol/cosmopolitan/cosmopolitan-amalgamation-0.2.zip;
	_x=$?;
	if [ ! -f common/build/headers.tmp ]; then
		echo -e 'failed!\ncommon/build/headers.tmp was not found on disk.' \
		' Exiting...' \
		>/dev/stderr;
		exit 127;
	elif [ "$(cat common/build/headers.tmp | head -n 1 | awk '{print $2}')" \
	!= '200' ]; then
		echo -e "failed!\nHTTP status code was $(cat common/build/headers.tmp \
		| head -n 1 | awk '{print $2}'). Exiting..." >/dev/stderr;
		exit 127;
	elif [ "$_x" != '0' ]; then
		echo -e "failed!\nExit code was $_x. Exiting..." >/dev/stderr;
		exit 127;
	fi
	echo 'done.' >/dev/stderr;
fi

echo -n 'Verifying the integrity of the archive... ' >/dev/stderr;
if [ "$_sum" != \
"$(sha256sum common/build/cosmo.zip | awk '{print $1}')" ]; then
	echo -e 'failed!\nSHA2-256 checksums did not match. Exiting...' \
	>/dev/stderr;
	exit 127;
fi

echo 'passed!' >/dev/stderr;

if [ -d common/build/cosmo ]; then
	echo 'Cosmopolitan extract directory already exists. Skipping...' \
	>/dev/stderr;
else
	echo -n 'Making Cosmopolitan extract directory... ' >/dev/stderr;
	mkdir common/build/cosmo;
	_x=$?;
	if [ "$_x" != '0' ]; then
		echo -e "failed!\nExit code was $_x. Exiting..." >/dev/stderr;
		exit 127;
	fi
	echo 'done.' >/dev/stderr;
fi

echo -n 'Extracting the binaries... ' >/dev/stderr;
unzip -qu common/build/cosmo.zip -d common/build/cosmo;
_x=$?;

if [ "$_x" = '0' ]; then
	echo 'done.' >/dev/stderr;
else
	echo -e "failed!\nExit code was $_x. Exiting..." >/dev/stderr;
	exit 127;
fi

echo -n 'Cleaning up... ' >/dev/stderr;
rm -f common/build/headers.tmp;
echo 'done.' >/dev/stderr;

unset _x _sum;
exit 0;
