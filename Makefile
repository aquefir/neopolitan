##############################################################################
##                                  unilib                                  ##
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
LIBS    :=
LIBDIRS :=

# frameworks (macOS target only)
FWORKS :=

# ‘3P’ are in-tree 3rd-party dependencies
# 3PLIBDIR is the base directory
# 3PLIBS is the folder names in the base directory for each library
3PLIBDIR := 3rdparty
3PLIBS   := mt19937 tes

# sources
SFILES   := \
	src/gbabios.s \
	src/memcpy.s \
	src/memset.s
CFILES   := \
	src/arr.c \
	src/err.c \
	src/futils.c \
	src/log.c \
	src/memory.c \
	src/str.c \
	src/utf8.c
HFILES   := \
	include/uni/types/float.h \
	include/uni/types/geo.h \
	include/uni/types/int.h \
	include/uni/types/mathprim.h \
	include/uni/types/opt.h \
	include/uni/types/options.h \
	include/uni/types/vec.h \
	include/uni/arr.h \
	include/uni/chkmath.h \
	include/uni/decl.h \
	include/uni/endian.h \
	include/uni/err.h \
	include/uni/futils.h \
	include/uni/log.h \
	include/uni/memory.h \
	include/uni/option.h \
	include/uni/str.h \
	include/uni/utf8.h \
	include/uni/ver.h \
	src/arr.h \
	src/str.h \
	src/utf8.h
CPPFILES :=
HPPFILES :=

# test suite sources
TES_CFILES   := \
	src/arr.tes.c \
	src/str.tes.c \
	src/utf8.tes.c
TES_HFILES   :=
TES_CPPFILES :=
TES_HPPFILES :=

# this defines all our usual targets
include etc/targets.mk
