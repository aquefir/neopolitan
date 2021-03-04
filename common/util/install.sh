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

if test "$(id -u)" = '0'; then
	_sudo='';
else
	_sudo='sudo ';
fi

common/util/cleanall.sh;
common/util/makeall.sh release;

if test "${PREFIX}" = ''; then
	PREFIX='/usr/local/x86_64-pc-ape';
fi

_prefix="${PREFIX}";

${_echo} -e 'Installing all sub-repositories.\n' >/dev/stderr;

_repos='arr chkmath clarg decl endian err futils himem log mt19937 str table
	text';

for repo in ${_repos}; do
	cd ${repo};
	${_echo} "Installing sub-repo ‘${repo}’..." >/dev/stderr;
	${_sudo} ${_make} install PREFIX="${_prefix}" AQ=/opt/aq;
	cd ..;
done

${_echo} 'All done. Exiting...' >/dev/stderr;

unset _repo _repos _sudo _echo _make;
exit 0;
