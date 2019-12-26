# -*- coding: utf-8 -*-
## This Makefile provides multi-platform build normalisation for the C and C++
## compilation toolchains. It is included at the top of the main Makefile.

ifneq ($(OS),Windows_NT)
A     := a
EXE   :=
UNAME := $(shell uname -s)
ifeq ($(strip $(UNAME)),Darwin)
# macOS
SO := dylib
ifeq "$(origin CC)" "default"
CC := $(shell whereis clang)
endif
ifeq "$(origin CXX)" "default"
CXX := $(shell whereis clang++)
endif
ifeq "$(origin CPP)" "default"
CPP := $(shell whereis clang) -E
endif
ifndef AR
AR := $(shell whereis ar)
endif
ifdef AR
ifeq "$(origin AR)" "default"
AR := $(shell whereis ar)
endif
endif
ifndef STRIP
# if GNU binutils is installed, $(which strip) returns GNU strip
# this will trash Mach-O binaries, so don’t use it
STRIP := $(shell whereis strip)
endif
ifdef STRIP
ifeq "$(origin STRIP)" "default"
STRIP := $(shell whereis strip)
endif
endif
else
# non-macOS *nix
SO := so
ifeq "$(origin CC)" "default"
CC := gcc
endif
ifeq "$(origin CXX)" "default"
CXX := g++
endif
ifeq "$(origin CPP)" "default"
CPP := gcc -E
endif
ifndef AR
AR := ar
endif
ifdef AR
ifeq "$(origin AR)" "default"
AR := ar
endif
endif
ifndef STRIP
STRIP := strip
endif
ifdef STRIP
ifeq "$(origin STRIP)" "default"
STRIP := strip
endif
endif

# Deterministic build flags, for both clang and GCC
SOURCE_DATE_EPOCH := 0
ZERO_AR_DATE := 1
CFLAGS := -ffile-prefix-map=OLD=NEW -std=c89 -x c
CXXFLAGS := -std=c++11 -x c++
LDFLAGS :=
ARFLAGS := -rcs

ifeq ($(CC),clang)
CFLAGS += -frandom-seed
CXXFLAGS += -frandom-seed
endif

export ZERO_AR_DATE
export SOURCE_DATE_EPOCH

endif # non-WinNT
else

UNAME    := Windows
CFLAGS   :=
CXXFLAGS :=
LDFLAGS  :=
EXE      := .exe
SO       := dll
A        := lib

endif # uname -s

FMT := clang-format$(EXE)

export UNAME
export SO
export A
export EXE
export FMT
export CC
export CXX
export CPP
export AR
export STRIP
export CFLAGS
export CXXFLAGS
export LDFLAGS
