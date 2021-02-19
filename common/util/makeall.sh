#!/bin/sh
# -*- coding: utf-8 -*-

echo 'Building all sub-repositories.' >/dev/stderr;
if [ "$1" = 'release' ]; then
	target=release;
	echo 'Building optimised release target.' >/dev/stderr;
elif [ "$1" = 'check' ]; then
	target=check;
	echo 'Building sanity check target.' >/dev/stderr;
elif [ "$1" = 'cov' ]; then
	target=cov;
	echo 'Building code coverage target.' >/dev/stderr;
elif [ "$1" = 'asan' ]; then
	target=asan;
	echo 'Building A-san target.' >/dev/stderr;
elif [ "$1" = 'ubsan' ]; then
	target=ubsan;
	echo 'Building UB-san target.' >/dev/stderr;
elif [ "$1" = '' ] || [ "$1" = 'debug' ]; then
	target=debug;
	echo 'Building debug target.' >/dev/stderr;
else
	echo "Unknown target ‘$1’. Exiting..." >/dev/stderr;
	exit 127;
fi

REPOS='arr clarg err futils himem log mt19937 str table';

if [ "$(uname -s)" = 'Darwin' ]; then
	jobs=$(($(sysctl -n hw.ncpu)))
else
	jobs=$(($(nproc) * 2));
fi

for repo in ${REPOS}; do
	cd ${repo};
	echo "Building sub-repo ‘${repo}’..." >/dev/stderr;
	make ${target} -j${jobs};
	cd ..;
done

echo -e 'All done. Exiting...' >/dev/stderr;

unset target jobs;
exit 0;
