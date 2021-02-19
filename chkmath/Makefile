##############################################################################
##                           unilib checked maths                           ##
##                                                                          ##
##                      Copyright © 2019-2020 Aquefir                       ##
##                       Released under BSD-2-Clause.                       ##
##############################################################################

ifeq ($(strip $(AQ)),)
$(error "AQ was not found in your environment. You need to install the Slick Makefiles from github.com/aquefir/slick to continue.")
endif

# Target APE only
TP := APE

include $(AQ)/lib/slick/base.mk

PROJECT := uni_chkmath

# put a ‘1’ for the desired target types to compile
SOFILE :=
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
3PLIBS   := tes

# sources
SFILES    :=
CFILES    :=
CPPFILES  :=
PUBHFILES := \
	include/uni/chkmath.h
PRVHFILES :=

# test suite sources
TES_CFILES    :=
TES_CPPFILES  :=
TES_PUBHFILES :=
TES_PRVHFILES :=

APE_LDSCR := ../common/build/cosmo/ape.lds
APE_AFILE := ../common/build/cosmo/cosmopolitan.a
APE_HFILE := ../common/build/cosmo/cosmopolitan.h
APE_APEO  := ../common/build/cosmo/ape.o
APE_CRTO  := ../common/build/cosmo/crt.o

# this defines all our usual targets
include $(AQ)/lib/slick/targets.mk
