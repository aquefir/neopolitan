##############################################################################
##                           Universal C Library™                           ##
##                                                                          ##
##                    Copyright © 2019-2020 ARQADIUM LLC                    ##
##                           All rights reserved.                           ##
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
	src/array.c \
	src/err.c \
	src/futils.c \
	src/log.c \
	src/sort.c
HFILES    := \
	include/unilib/array.h \
	include/unilib/decl.h \
	include/unilib/err.h \
	include/unilib/futils.h \
	include/unilib/geometry.h \
	include/unilib/log.h \
	include/unilib/option.h \
	include/unilib/shand.h \
	include/unilib/sort.h \
	src/array.h
CPPFILES :=
HPPFILES :=
OFILES   := $(CFILES:.c=.c.o) $(CPPFILES:.cpp=.cpp.o)

# test suite sources
TES_CFILES   := \
	test/array.c \
	test/main.c \
	test/sort.c
TES_HFILES   :=
TES_CPPFILES :=
TES_HPPFILES :=
TES_OFILES   := $(TES_CFILES:.c=.c.o) $(TES_CPPFILES:.cpp=.cpp.o)

# address-sanitisation metadata
GCNOFILES     := $(CFILES:.c=.c.gcno) $(CPPFILES:.cpp=.cpp.gcno)
GCDAFILES     := $(CFILES:.c=.c.gcda) $(CPPFILES:.cpp=.cpp.gcda)
TES_GCNOFILES := $(TES_CFILES:.c=.c.gcno) $(TES_CPPFILES:.cpp=.cpp.gcno)
TES_GCDAFILES := $(TES_CFILES:.c=.c.gcda) $(TES_CPPFILES:.cpp=.cpp.gcda)


# this defines all our usual targets
include targets.mk
