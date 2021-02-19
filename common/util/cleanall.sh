#!/bin/sh
# -*- coding: utf-8 -*-

echo -e 'Cleaning all sub-repositories.\n' >/dev/stderr;

REPOS='arr clarg err futils himem log mt19937 str table';

for repo in ${REPOS}; do
	cd ${repo};
	echo -n "Cleaning sub-repo ‘${repo}’... " >/dev/stderr;
	make clean 2>&1 >/dev/null;
	echo 'done.' >/dev/stderr;
	cd ..;
done

echo -e 'All done. Exiting...' >/dev/stderr;
exit 0;
