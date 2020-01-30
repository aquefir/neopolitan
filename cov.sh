#!/bin/sh
#

_proj='uni_test'

if [ "$1" = 'run' ]; then
	LLVM_PROFILE_FILE="${_proj}.profraw" "./${_proj}_test";
elif [ "$1" = 'index' ]; then
	llvm-profdata merge -sparse "${_proj}.profraw" -o "${_proj}.profdata";
else
	echo 'Usage: ./cov.sh <run|index>';
	exit 0;
fi

undef _proj;
