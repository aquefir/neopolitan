#!/bin/sh
# -*- coding: utf-8 -*-

if test "$(uname -s)" = 'Darwin'; then
	_make=gmake;
	_jobs=$(($(sysctl -n hw.ncpu)))
	if command -v gecho >/dev/null 2>&1; then
		_echo=gecho;
	else
		_echo='/bin/echo'; # ensure it is not a bashism
	fi
else
	_make=make;
	_jobs=$(($(nproc) * 2));
	_echo='/bin/echo'; # ensure it is not a bashism
fi

${_echo} 'Building all sub-repositories.' >/dev/stderr;
if [ "$1" = 'release' ]; then
	_target=release;
	${_echo} 'Building optimised release target.' >/dev/stderr;
elif [ "$1" = 'check' ]; then
	_target=check;
	${_echo} 'Building sanity check target.' >/dev/stderr;
elif [ "$1" = 'cov' ]; then
	_target=cov;
	${_echo} 'Building code coverage target.' >/dev/stderr;
elif [ "$1" = 'asan' ]; then
	_target=asan;
	${_echo} 'Building A-san target.' >/dev/stderr;
elif [ "$1" = 'ubsan' ]; then
	_target=ubsan;
	${_echo} 'Building UB-san target.' >/dev/stderr;
elif [ "$1" = '' ] || [ "$1" = 'debug' ]; then
	_target=debug;
	${_echo} 'Building debug target.' >/dev/stderr;
else
	${_echo} "Unknown target ‘$1’. Exiting..." >/dev/stderr;
	exit 127;
fi

_repos='arr clarg err futils himem log mt19937 str table';

for _repo in ${_repos}; do
	cd ${_repo};
	${_echo} "Building sub-repo ‘${repo}’..." >/dev/stderr;
	${_make} ${_target} -j${_jobs};
	cd ..;
done

${_echo} 'All done. Exiting...' >/dev/stderr;

unset _repo _repos _target _echo _jobs _make;
