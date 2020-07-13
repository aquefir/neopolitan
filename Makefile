##############################################################################
##                           Aquefir One Library™                           ##
##                                                                          ##
##                      Copyright © 2019-2020 Aquefir                       ##
##                       Released under BSD-2-Clause.                       ##
##############################################################################

include etc/base.mk

PROJECT := uni

# put a ‘1’ for the desired target types to compile
SOFILE := 1
AFILE  := 1

# space-separated path list for #includes
# <system> includes
INCLUDES := include
# "local" includes
INCLUDEL := src

# space-separated library name list
LIBS      :=
LIBDIRS   :=

# frameworks (macOS target only)
FWORKS :=

# ‘3P’ are in-tree 3rd-party dependencies
# 3PLIBDIR is the base directory
# 3PLIBS is the folder names in the base directory for each library
3PLIBDIR := 3rdparty
3PLIBS   :=

# sources
CFILES   := \
	src/err.c \
	src/futils.c \
	src/log.c
HFILES   := \
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
include etc/targets.mk
