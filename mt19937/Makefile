##############################################################################
##                 Mersenne-Twister Algorithm 19937, 32-bit                 ##
##                                                                          ##
##                      Copyright © 2019-2020 Aquefir.                      ##
##                       Released under BSD-2-Clause.                       ##
##############################################################################

ifeq ($(strip $(AQ)),)
$(error "AQ was not found in your environment. You need to install the Slick Makefiles from github.com/aquefir/slick to continue.")
endif

include $(AQ)/lib/slick/base.mk

PROJECT := mt19937

# put a ‘1’ for the desired target types to compile
SOFILE :=
AFILE  := 1

# space-separated path list for #includes
# <system> includes
INCLUDES := include ../decl/include ../err/include ../log/include \
	../himem/include
# "local" includes
INCLUDEL :=

# space-separated library name list
LIBS    :=
LIBDIRS :=

# frameworks (macOS target only)
FWORKS :=

# ‘3P’ are in-tree 3rd-party dependencies
# 3PLIBDIR is the base directory
# 3PLIBS is the folder names in the base directory for each library
3PLIBDIR := 3rdparty
3PLIBS   :=

# sources
CFILES    := \
	src/random.c
CPPFILES  :=
PUBHFILES := \
	include/mt19937/random.h
PRVHFILES :=

# test suite sources
TES_CFILES    :=
TES_PUBHFILES :=
TES_CPPFILES  :=
TES_PRVHFILES :=

NO_TES := 1

# this defines all our usual targets
include $(AQ)/lib/slick/targets.mk
