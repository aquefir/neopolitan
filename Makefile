##############################################################################
##                           Universal C Library™                           ##
##                                                                          ##
##                      Copyright © 2019 ARQADIUM, LLC                      ##
##                           All rights reserved.                           ##
##############################################################################

include base.mk

PROJECT := unilib
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

# this defines all our usual targets
include targets.mk

clean:
	$(RM) $(TARGETS_DBG)
	$(RM) $(TARGETS_REL)
	$(RM) $(TARGETS_CHK)
	$(RM) $(TARGETS_COV)
	$(RM) $(TARGETS_ASAN)
	$(RM) $(OFILES)
	$(RM) $(GCNOFILES)
	$(RM) $(GCDAFILES)

format:
	for _file in $(CFILES) $(HFILES) $(CPPFILES) $(HPPFILES); do \
		$(FMT) -i -style=file $$_file ; \
	done
