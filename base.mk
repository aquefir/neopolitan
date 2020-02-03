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
CPP.CUSTOM    := $(CPP)
CPP.NAME      := clang
AR.DEFAULT    := $(shell whereis ar)
AR.CUSTOM     := $(AR)
AR.NAME       := ar
STRIP.DEFAULT := $(shell whereis strip)
STRIP.CUSTOM  := $(STRIP)
STRIP.NAME    := strip

else ifeq ($(strip $(UNAME)),Linux)

## Linux
##

SO            := so
CC.DEFAULT    := $(shell which gcc)
CC.CUSTOM     := $(CC)
CXX.DEFAULT   := $(shell which g++)
CXX.CUSTOM    := $(CXX)
CPP.DEFAULT   := $(shell which gcc) -E
CPP.CUSTOM    := $(CC) -E
AR.DEFAULT    := $(shell which ar)
AR.CUSTOM     := $(AR)
STRIP.DEFAULT := $(shell which strip)
STRIP.CUSTOM  := $(STRIP)

# Set up the variables by defaults
ifeq ($(origin CC),undefined)
CC         := $(CC.DEFAULT)
CXX        := $(CXX.DEFAULT)
CPP        := $(CPP.DEFAULT)
AR         := $(AR.DEFAULT)
STRIP      := $(STRIP.DEFAULT)
CC.NAME    := gcc
CXX.NAME   := g++
CPP.NAME   := gcc
AR.NAME    := ar
STRIP.NAME := strip
else ifeq ($(origin CC),default)
CC         := $(CC.DEFAULT)
CXX        := $(CXX.DEFAULT)
CPP        := $(CPP.DEFAULT)
AR         := $(AR.DEFAULT)
STRIP      := $(STRIP.DEFAULT)
CC.NAME    := gcc
CXX.NAME   := g++
CPP.NAME   := gcc
AR.NAME    := ar
STRIP.NAME := strip
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
AR.NAME    := $(AR.CUSTOM)
STRIP.NAME := $(STRIP.CUSTOM)
endif # $(origin CC)
endif # $(UNAME)

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

export UNAME
export SO
export FMT
export CC
export CXX
export CPP
export AR
export CCLD
export CXXLD
export STRIP
export CC.NAME
export CXX.NAME
export CPP.NAME
export AR.NAME
export CCLD.NAME
export CXXLD.NAME
export STRIP.NAME
export CFLAGS
export CXXFLAGS
export LDFLAGS
