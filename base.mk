# -*- coding: utf-8 -*-
## This Makefile provides multi-platform build normalisation for the C and C++
## compilation toolchains. It is included at the top of the main Makefile.

# Check Make version (we need at least GNU Make 3.82). Fortunately,
# 'undefine' directive has been introduced exactly in GNU Make 3.82.
ifeq ($(filter undefine,$(value .FEATURES)),)
$(error Unsupported Make version. \
    The build system does not work properly with GNU Make $(MAKE_VERSION), \
    please use GNU Make 3.82 or above)
endif

UNAME := $(shell uname -s)

# Set up the original variables
ifeq ($(strip $(UNAME)),Darwin)

## macOS
##

SO            := dylib
CC.DEFAULT    := $(shell whereis clang)
CC.CUSTOM     := $(CC)
CC.NAME       := clang
CXX.DEFAULT   := $(shell whereis clang++)
CXX.CUSTOM    := $(CXX)
CXX.NAME      := clang++
CPP.DEFAULT   := $(shell whereis clang) -E
CPP.CUSTOM    := $(CC) -E
CPP.NAME      := clang
LD.DEFAULT    := $(shell which clang)
LD.CUSTOM     := $(LD)
LD.NAME       := clang
AR.DEFAULT    := $(shell whereis ar)
AR.CUSTOM     := $(AR)
AR.NAME       := ar
STRIP.DEFAULT := $(shell whereis strip)
STRIP.CUSTOM  := $(STRIP)
STRIP.NAME    := strip

endif
ifeq ($(strip $(UNAME)),Linux)

## Linux
##

SO            := so
CC.DEFAULT    := $(shell which gcc)
CC.CUSTOM     := $(CC)
CC.NAME       := gcc
CXX.DEFAULT   := $(shell which g++)
CXX.CUSTOM    := $(CXX)
CXX.NAME      := g++
CPP.DEFAULT   := $(shell which gcc) -E
CPP.CUSTOM    := $(CC) -E
CPP.NAME      := gcc
LD.DEFAULT    := $(shell which gcc)
LD.CUSTOM     := $(LD)
LD.NAME       := gcc
AR.DEFAULT    := $(shell which ar)
AR.CUSTOM     := $(AR)
AR.NAME       := ar
STRIP.DEFAULT := $(shell which strip)
STRIP.CUSTOM  := $(STRIP)
STRIP.NAME    := strip

endif # $(UNAME)

# Set up the variables by defaults
ifeq ($(origin CC),undefined)
CC         := $(CC.DEFAULT)
CXX        := $(CXX.DEFAULT)
CPP        := $(CPP.DEFAULT)
LD         := $(LD.DEFAULT)
AR         := $(AR.DEFAULT)
STRIP      := $(STRIP.DEFAULT)
endif
ifeq ($(origin CC),default)
CC         := $(CC.DEFAULT)
CXX        := $(CXX.DEFAULT)
CPP        := $(CPP.DEFAULT)
LD         := $(LD.DEFAULT)
AR         := $(AR.DEFAULT)
STRIP      := $(STRIP.DEFAULT)
else
# environment [override], file, command line, override, automatic
CC         := $(CC.CUSTOM)
CXX        := $(CXX.CUSTOM)
CPP        := $(CPP.CUSTOM)
AR         := $(AR.CUSTOM)
STRIP      := $(STRIP.CUSTOM)
CC.NAME    := $(CC.CUSTOM)
CXX.NAME   := $(CXX.CUSTOM)
CPP.NAME   := $(CPP.CUSTOM)
LD.NAME    := $(LD.CUSTOM)
AR.NAME    := $(AR.CUSTOM)
STRIP.NAME := $(STRIP.CUSTOM)
endif # $(origin CC)

# Base build tool flags
CFLAGS   := -Wall -fPIC
CXXFLAGS := -Wall -fPIC
LDFLAGS  := -fPIE
ARFLAGS  := -rcs

# Deterministic build flags, for both clang and GCC
SOURCE_DATE_EPOCH := 0
ZERO_AR_DATE := 1

ifeq ($(CC.NAME),clang)
CFLAGS += -ansi -frandom-seed=0 -x c
else ifeq ($(CC.NAME),gcc)
CFLAGS += -ansi -ffile-prefix-map=OLD=NEW -frandom-seed=69 -x c
else ifeq ($(CC.CUSTOM),tcc)
CFLAGS += -std=c89 -x c
endif

ifeq ($(CXX.NAME),clang++)
CXXFLAGS += -std=c++11 -frandom-seed=0 -x c++
else ifeq ($(CXX.NAME),g++)
CXXFLAGS += -std=c++11 -ffile-prefix-map=OLD=NEW -frandom-seed=69 -x c++
endif

export ZERO_AR_DATE
export SOURCE_DATE_EPOCH

FMT := clang-format

$(info SYSTEM COMPILATION DEFAULTS PRINTOUT)
$(info =====================================)
$(info System := $(UNAME))
$(info Shared library extension := $(SO))
$(info Autoformatter := $(FMT))
$(info C compiler := cmd:$(CC) name:$(CC.NAME))
$(info C++ compiler := cmd:$(CXX) name:$(CXX.NAME))
$(info C preprocessor := cmd:$(CPP) name:$(CPP.NAME))
$(info Static library archiver := cmd:$(AR) name:$(AR.NAME))
$(info Program linker := cmd:$(LD) name:$(LD.NAME))
$(info Symbol stripper := cmd:$(STRIP) name:$(STRIP.NAME))
$(info C flags := $(CFLAGS))
$(info C++ flags := $(CXXFLAGS))
$(info Linker flags := $(LDFLAGS))

export UNAME
export SO
export FMT
export CC
export CXX
export CPP
export AR
export CCLD
export STRIP
export CC.NAME
export CXX.NAME
export CPP.NAME
export AR.NAME
export LD.NAME
export STRIP.NAME
export CFLAGS
export CXXFLAGS
export LDFLAGS
