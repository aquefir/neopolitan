#!/bin/sh
# -*- coding: utf-8 -*-

common/util/cleanall.sh;
common/util/makeall.sh release;

if test "${PREFIX}" = ''; then
	PREFIX='/usr/local/x86_64-pc-ape';
fi

_prefix="${PREFIX}";

echo 'Installing all sub-repositories.' >/dev/stderr;

REPOS='arr chkmath clarg decl endian err futils himem log mt19937 str table
	text';

for repo in ${REPOS}; do
	cd ${repo};
	echo "Installing sub-repo ‘${repo}’..." >/dev/stderr;
	make install PREFIX="${_prefix}" AQ=/opt/aq;
	cd ..;
done
unset repo;

echo -e 'All done. Exiting...' >/dev/stderr;

unset REPOS;
exit 0;
