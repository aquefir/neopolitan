#!/bin/sh
# -*- coding: utf-8 -*-

echo -e 'Auto-formatting all sub-repositories.\n' >/dev/stderr;

REPOS='arr chkmath clarg decl endian err futils himem log mt19937 str table
	text';

for repo in ${REPOS}; do
	cd ${repo};
	echo -n "Formatting sub-repo ‘${repo}’... " >/dev/stderr;
	make format 2>&1 >/dev/null;
	echo 'done.' >/dev/stderr;
	cd ..;
done

echo -e 'All done. Exiting...' >/dev/stderr;
exit 0;
