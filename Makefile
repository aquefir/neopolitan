##############################################################################
##                           Aquefir One Library™                           ##
##                                                                          ##
##                      Copyright © 2019-2020 Aquefir                       ##
##                       Released under BSD-2-Clause.                       ##
##############################################################################

include base.mk

PROJECT := uni
EXEFILE :=
SOFILE  :=
AFILE   := 1

# <system> includes
INCLUDES := include
# "local" includes
INCLUDEL := src

# libraries
LIBS      :=
LIBDIRS   :=

# frameworks (macOS only)
FWORKS :=

# in-tree 3rd-party libraries
3PLIBDIR := 3rdparty
3PLIBS :=

# sources
CFILES    := \
	src/err.c \
	src/futils.c \
	src/log.c
HFILES    := \
	include/unilib/array.h \
	include/unilib/decl.h \
	include/unilib/err.h \
	include/unilib/futils.h \
	include/unilib/geometry.h \
	include/unilib/log.h \
	include/unilib/option.h \
	include/unilib/shand.h
CPPFILES :=
HPPFILES :=

# test suite sources
TES_CFILES   := \
	test/array.c \
	test/main.c \
	test/sort.c
TES_HFILES   :=
TES_CPPFILES :=
TES_HPPFILES :=

# this defines all our usual targets
include targets.mk
