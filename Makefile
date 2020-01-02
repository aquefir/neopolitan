##############################################################################
##                           Universal C Library™                           ##
##                                                                          ##
##                      Copyright © 2019 ARQADIUM, LLC                      ##
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

ifeq ($(UNAME),Windows)
	LIBS     += mingw32
	LIBDIRS  += $(USERPROFILE)/sysroot/lib
	INCLUDES += $(USERPROFILE)/sysroot/include
endif
ifeq ($(UNAME),Linux)
	LIBS     += m pthread
endif

CFILES    := \
	src/err.c \
	src/futils.c \
	src/log.c
HFILES    := \
	include/unilib/array.h \
	include/unilib/err.h \
	include/unilib/futils.h \
	include/unilib/geometry.h \
	include/unilib/log.h \
	include/unilib/option.h \
	include/unilib/shand.h
CPPFILES  :=
HPPFILES  :=
OFILES    := $(CFILES:.c=.c.o) $(CPPFILES:.cpp=.cpp.o)
# address-sanitisation metadata
GCNOFILES := $(CFILES:.c=.c.gcno) $(CPPFILES:.cpp=.cpp.gcno)
GCDAFILES := $(CFILES:.c=.c.gcda) $(CPPFILES:.cpp=.cpp.gcda)

NO_TES := 1

# this defines all our usual targets
include targets.mk
