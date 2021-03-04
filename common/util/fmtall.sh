#!/bin/sh
# -*- coding: utf-8 -*-

if test "$(uname -s)" = 'Darwin'; then
	_make=gmake;
	if command -v gecho >/dev/null 2>&1; then
		_echo=gecho;
	else
		_echo='/bin/echo'; # ensure it is not a bashism
	fi
else
	_make=make;
	_echo='/bin/echo'; # ensure it is not a bashism
fi

${_echo} -e 'Auto-formatting all sub-repositories.\n' >/dev/stderr;

_repos='arr chkmath clarg decl endian err futils himem log mt19937 str table
	text';

for _repo in ${_repos}; do
	cd ${_repo};
	${_echo} -n "Formatting sub-repo ‘${_repo}’... " >/dev/stderr;
	${_make} format 2>&1 >/dev/null;
	${_echo} 'done.' >/dev/stderr;
	cd ..;
done

${_echo} 'All done. Exiting...' >/dev/stderr;
unset _repo _repos _echo _make;
