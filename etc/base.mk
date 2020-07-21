# -*- coding: utf-8 -*-
## This Makefile provides multi-platform build normalisation for the C and C++
## compilation toolchains. It is included at the top of the main Makefile.

# Check Make version (we need at least GNU Make 3.82). Fortunately,
# ‘undefine’ directive has been introduced exactly in GNU Make 3.82.
ifeq ($(filter undefine,$(value .FEATURES)),)
$(error Unsupported Make version. \
The build system does not work properly with GNU Make $(MAKE_VERSION), \
please use GNU Make 3.82 or above)
endif

## UNAME -> host
## TP    -> target platform
## TC    -> toolchain
## TROOT -> target sysroot (include, lib, etc.)

## There are several target platforms $(TP) in use. By ident, these include:
# Darwin - Apple macOS on x86-64 [$(TC)s: gnu, xcode, llvm]
# Linux - GNU/Linux on i386 and x86-64 [$(TC)s: gnu, llvm]
# Win32 - Microsoft Windows on i386 [$(TC)s: mingw32]
# Win64 - Microsoft Windows on x86-64 [$(TC)s: mingw32]
# GBA - Nintendo Game Boy Advance on ARMv4T [$(TC)s: dkarm]

## There are two families of toolchains $(TC) in use: GNU and LLVM.
# GNU:
#   gnu - standard GCC toolchain for targeting UNIX
#   mingw32 - GCC for targeting Windows
#   dkarm - devkitARM, a GCC for targeting GBA and (3)DS
# LLVM:
#   xcode - Apple-provided Clang and tools
#   llvm - bona fide LLVM toolchain from homebrew
# additionally, TinyCC is supported as a C compiler with either family of
# tools for Unices using ELF (Linux, BSDs, ...).

# Host
UNAME := $(shell uname -s)

# Target platform
# User can specify TP={Win32,Win64,GBA} at the command line
TP ?= $(UNAME)

## Specify the default host variables
## form: <var>.<host>[.<target>]
##

ifeq ($(strip $(TC)),llvm)
CC.DARWIN       := /usr/local/opt/llvm/bin/clang # brew LLVM
else
CC.DARWIN       := /usr/bin/clang # Xcode
endif
ifeq ($(strip $(TC)),gnu)
CC.LINUX        := /usr/bin/gcc
else
CC.LINUX        := /usr/bin/clang
endif
CC.DARWIN.WIN32 := /usr/local/bin/i686-w64-mingw32-gcc
CC.LINUX.WIN32  := /usr/bin/i686-w64-mingw32-gcc
CC.DARWIN.WIN64 := /usr/local/bin/x86_64-w64-mingw32-gcc
CC.LINUX.WIN64  := /usr/bin/i686-w64-mingw32-gcc
CC.DARWIN.GBA   := /opt/devkitpro/devkitARM/bin/arm-none-eabi-gcc
CC.LINUX.GBA    := /opt/devkitpro/devkitARM/bin/arm-none-eabi-gcc

ifeq ($(strip $(TC)),llvm)
CXX.DARWIN       := /usr/local/opt/llvm/bin/clang++ # brew LLVM
else
CXX.DARWIN       := /usr/bin/clang++ # Xcode
endif
ifeq ($(strip $(TC)),gnu)
CXX.LINUX        := /usr/bin/g++
else
CXX.LINUX        := /usr/bin/clang++
endif
CXX.DARWIN.WIN32 := /usr/local/bin/i686-w64-mingw32-g++
CXX.LINUX.WIN32  := /usr/bin/i686-w64-mingw32-g++
CXX.DARWIN.WIN64 := /usr/local/bin/x86_64-w64-mingw32-g++
CXX.LINUX.WIN64  := /usr/bin/x86_64-w64-mingw32-g++
CXX.DARWIN.GBA   := /opt/devkitpro/devkitARM/bin/arm-none-eabi-g++
CXX.LINUX.GBA    := /opt/devkitpro/devkitARM/bin/arm-none-eabi-g++

ifeq ($(strip $(TC)),llvm)
AR.DARWIN := /usr/local/opt/llvm/bin/llvm-ar # brew LLVM
else
AR.DARWIN := /usr/bin/ar # Xcode
endif
AR.LINUX        := /usr/bin/ar
AR.DARWIN.WIN32 := /usr/local/bin/i686-w64-mingw32-ar
AR.LINUX.WIN32  := /usr/bin/i686-w64-mingw32-ar
AR.DARWIN.WIN64 := /usr/local/bin/x86_64-w64-mingw32-ar
AR.LINUX.WIN64  := /usr/bin/x86_64-w64-mingw32-ar
AR.DARWIN.GBA   := /opt/devkitpro/devkitARM/bin/arm-none-eabi-ar
AR.LINUX.GBA    := /opt/devkitpro/devkitARM/bin/arm-none-eabi-ar

ifeq ($(strip $(TC)),llvm)
STRIP.DARWIN       := /usr/local/opt/llvm/bin/llvm-strip # brew LLVM
else
STRIP.DARWIN       := /usr/bin/strip # Xcode
endif
STRIP.LINUX        := /usr/bin/strip
STRIP.DARWIN.WIN32 := /usr/local/bin/i686-w64-mingw32-strip
STRIP.LINUX.WIN32  := /usr/bin/i686-w64-mingw32-strip
STRIP.DARWIN.WIN64 := /usr/local/bin/x86_64-w64-mingw32-strip
STRIP.LINUX.WIN64  := /usr/bin/x86_64-w64-mingw32-strip
STRIP.DARWIN.GBA   := /opt/devkitpro/devkitARM/bin/arm-none-eabi-strip
STRIP.LINUX.GBA    := /opt/devkitpro/devkitARM/bin/arm-none-eabi-strip

## Specify the default target variables
## form: <var>.<target>
##

SO.DARWIN := dylib
SO.LINUX  := so
SO.WIN32  := dll
SO.WIN64  := dll
SO.GBA    := nosharedlibsforgba # deliberate. check urself

CFLAGS.COMMON          := -pipe
CFLAGS.GCOMMON         := -fPIC -ansi -Wpedantic -x c -frandom-seed=69420
CFLAGS.GCOMMON.DEBUG   := -O0 -g3 -Wall -Wpedantic
CFLAGS.GCOMMON.RELEASE := -O2 -w
CFLAGS.GCOMMON.CHECK   := -Wextra -Werror -Wno-unused-variable
ifeq ($(strip $(TC)),llvm)
CFLAGS.GCOMMON.COV     := -O1 -g3 -fprofile-arcs -ftest-coverage
else ifeq ($(strip $(TC)),xcode)
CFLAGS.GCOMMON.COV     := -O1 -g3 -fprofile-arcs -ftest-coverage
else
CFLAGS.GCOMMON.COV     := -O1 -g3 -fprofile-instr-generate \
	-fcoverage-mapping
endif
CFLAGS.GCOMMON.ASAN    := -O1 -g3 -fsanitize=address -fno-omit-frame-pointer
CFLAGS.GCOMMON.UBSAN   := -O1 -g3 -fsanitize=undefined \
	-fno-omit-frame-pointer
CFLAGS.DARWIN := -march=ivybridge -mtune=skylake
CFLAGS.LINUX  := -march=sandybridge -mtune=skylake
CFLAGS.WIN32  := -march=sandybridge -mtune=skylake
CFLAGS.WIN64  := -march=sandybridge -mtune=skylake
CFLAGS.GBA    := -march=armv4t -mcpu=arm7tdmi -mthumb-interwork

CXXFLAGS.COMMON := -pipe -fPIC -std=c++11 -x c++ -frandom-seed=69420
CXXFLAGS.COMMON.DEBUG   := -O0 -g3 -Wall -Wpedantic
CXXFLAGS.COMMON.RELEASE := -O2 -w
CXXFLAGS.COMMON.CHECK   := -Wextra -Werror -Wno-unused-variable
ifeq ($(strip $(TC)),llvm)
CXXFLAGS.COMMON.COV     := -O1 -g3 -fprofile-arcs -ftest-coverage
else ifeq ($(strip $(TC)),xcode)
CXXFLAGS.COMMON.COV     := -O1 -g3 -fprofile-arcs -ftest-coverage
else
CXXFLAGS.COMMON.COV     := -O1 -g3 -fprofile-instr-generate \
	-fcoverage-mapping
endif
CXXFLAGS.COMMON.ASAN    := -O1 -g3 -fsanitize=address -fno-omit-frame-pointer
CXXFLAGS.COMMON.UBSAN   := -O1 -g3 -fsanitize=undefined \
	-fno-omit-frame-pointer
CXXFLAGS.DARWIN := -march=ivybridge -mtune=skylake
CXXFLAGS.LINUX  := -march=sandybridge -mtune=skylake
CXXFLAGS.WIN32  := -march=sandybridge -mtune=skylake
CXXFLAGS.WIN64  := -march=sandybridge -mtune=skylake
CXXFLAGS.GBA    := -march=armv4t -mcpu=arm7tdmi -mthumb-interwork

LDFLAGS       := -fPIE
LDFLAGS.COV   :=
LDFLAGS.ASAN  := -fsanitize=address -fno-omit-frame-pointer
LDFLAGS.UBSAN := -fsanitize=undefined
ifeq ($(strip $(TC)),llvm)
LDFLAGS.COV += -fprofile-arcs -ftest-coverage
else ifeq ($(strip $(TC)),xcode)
LDFLAGS.COV += -fprofile-arcs -ftest-coverage
else
LDFLAGS.COV += -Wl,-fprofile-instr-generate -Wl,-fcoverage-mapping
endif

# Initialise $(TROOT)
TROOT.DARWIN.WIN32 := /usr/local/i686-w64-mingw32
TROOT.DARWIN.WIN64 := /usr/local/x86_64-w64-mingw32
TROOT.DARWIN.GBA   := /opt/devkitpro/devkitARM
TROOT.DARWIN       := /usr
TROOT.LINUX.WIN32  := /usr/i686-w64-mingw32
TROOT.LINUX.WIN64  := /usr/x86_64-w64-mingw32
TROOT.LINUX.GBA    := /opt/devkitpro/devkitARM
TROOT.LINUX        := /usr

# These are config.h synthetics to tell code about its particularities
CDEFS.DARWIN := DARWIN LILENDIAN AMD64
CDEFS.LINUX  := LINUX LILENDIAN
ifneq ($(strip $(shell uname -a | grep x86_64)),)
CDEFS.LINUX += AMD64
else ifneq ($(strip $(shell uname -a | grep i386)),)
CDEFS.LINUX += IA32
else
$(error Linux is not supported outside of x86.)
endif
CDEFS.WIN32  := WINDOWS WIN32 LILENDIAN IA32
CDEFS.WIN64  := WINDOWS WIN64 LILENDIAN AMD64
CDEFS.GBA    := GBA ARMV4T LILENDIAN

TC.DARWIN := llvm
TC.LINUX  := gnu
TC.WIN32  := mingw32
TC.WIN64  := mingw32
TC.GBA    := dkarm

## Resolve the correct host-target suffixes
##

ifeq ($(strip $(UNAME)),Darwin)
ifeq ($(strip $(TP)),Darwin)
suf := DARWIN
tsuf := DARWIN
else ifeq ($(strip $(TP)),Win32)
suf := DARWIN.WIN32
tsuf := WIN32
else ifeq ($(strip $(TP)),Win64)
suf := DARWIN.WIN64
tsuf := WIN64
else ifeq ($(strip $(TP)),GBA)
suf := DARWIN.GBA
tsuf := GBA
else ifeq ($(strip $(TP)),Linux)
$(error Cross-compilation to Linux is not supported on macOS)
else
$(error Unknown target platform "$(TP)")
endif # $(TP)
else ifeq ($(strip $(UNAME)),Linux)
ifeq ($(strip $(TP)),Linux)
suf := LINUX
tsuf := LINUX
else ifeq ($(strip $(TP)),Win32)
suf := LINUX.WIN32
tsuf := WIN32
else ifeq ($(strip $(TP)),Win64)
suf := LINUX.WIN64
tsuf := WIN64
else ifeq ($(strip $(TP)),GBA)
suf := DARWIN.GBA
tsuf := GBA
else ifeq ($(strip $(TP)),Darwin)
$(error Cross-compilation to macOS is not supported on Linux)
else
$(error Unknown target platform "$(TP)")
endif # $(TP)
else
$(error Unsupported host platform "$(UNAME)")
endif # $(UNAME)

ifeq ($(strip $(TP)),Win32)
EXE := .exe
else ifeq ($(strip $(TP)),Win64)
EXE := .exe
else
EXE :=
endif # $(TP)

## Set the host/target specific defaults and env customs
##

SO := $(SO.$(tsuf))
TC ?= $(TC.$(tsuf))

CC.DEFAULT    := $(CC.$(suf))
CC.CUSTOM     := $(CC)
CXX.DEFAULT   := $(CXX.$(suf))
CXX.CUSTOM    := $(CXX)
AR.DEFAULT    := $(AR.$(suf))
AR.CUSTOM     := $(AR)
STRIP.DEFAULT := $(STRIP.$(suf))
STRIP.CUSTOM  := $(STRIP)

ifeq ($(strip $(CC.CUSTOM)),tcc)
CFLAGS   := $(CFLAGS.COMMON) -std=c89
else
CFLAGS   := $(CFLAGS.GCOMMON) $(CFLAGS.$(tsuf))
endif # $(CC.CUSTOM)
CXXFLAGS := $(CXXFLAGS.COMMON) $(CXXFLAGS.$(tsuf))
#LDFLAGS
ARFLAGS  := -rcs
CDEFS    := $(CDEFS.$(tsuf))

# Make builds deterministic
ifeq ($(strip $(TC)),gnu)
CFLAGS   += -ffile-prefix-map=OLD=NEW
CXXFLAGS += -ffile-prefix-map=OLD=NEW
else ifeq ($(strip $(TC)),mingw32)
CFLAGS   += -ffile-prefix-map=OLD=NEW
CXXFLAGS += -ffile-prefix-map=OLD=NEW
else ifeq ($(strip $(TC)),dkarm)
CFLAGS   += -ffile-prefix-map=OLD=NEW
CXXFLAGS += -ffile-prefix-map=OLD=NEW
endif

## Resolve default and custom values
##

ifeq ($(origin CC),undefined)
CC := $(CC.DEFAULT)
else ifeq ($(origin CC),default)
CC := $(CC.DEFAULT)
else
# environment [override], file, command line, override, automatic
CC := $(CC.CUSTOM)
endif # $(origin CC)

ifeq ($(origin CXX),undefined)
CXX := $(CXX.DEFAULT)
else ifeq ($(origin CXX),default)
CXX := $(CXX.DEFAULT)
else
# environment [override], file, command line, override, automatic
CXX := $(CXX.CUSTOM)
endif # $(origin CXX)

ifeq ($(origin AR),undefined)
AR := $(AR.DEFAULT)
else ifeq ($(origin AR),default)
AR := $(AR.DEFAULT)
else
# environment [override], file, command line, override, automatic
AR := $(AR.CUSTOM)
endif # $(origin AR)

ifeq ($(origin STRIP),undefined)
STRIP := $(STRIP.DEFAULT)
else ifeq ($(origin STRIP),default)
STRIP := $(STRIP.DEFAULT)
else
# environment [override], file, command line, override, automatic
STRIP := $(STRIP.CUSTOM)
endif # $(origin STRIP)

# Deterministic build flags, for both clang and GCC
SOURCE_DATE_EPOCH := 0
ZERO_AR_DATE := 1

export ZERO_AR_DATE
export SOURCE_DATE_EPOCH

FMT := clang-format
DEFINES :=
UNDEFINES :=

ifeq ($(strip $(CC.CUSTOM)),tcc)
DEFINES += SDL_DISABLE_IMMINTRIN_H=1
endif

DEFINES += $(patsubst %,CFG_%,$(CDEFS))

$(info SYSTEM COMPILATION DEFAULTS PRINTOUT)
$(info =====================================)
$(info       Host machine := $(UNAME))
$(info     Target machine := $(TP))
$(info   Toolchain in use := $(TC))
$(info    Shlib extension := $(SO))
$(info      Autoformatter := $(FMT))
$(info         C compiler := $(CC))
$(info       C++ compiler := $(CXX))
$(info   Library archiver := $(AR))
$(info    Symbol stripper := $(STRIP))
$(info   C compiler flags := $(CFLAGS))
$(info C++ compiler flags := $(CXXFLAGS))
$(info       Linker flags := $(LDFLAGS))
$(info )

export UNAME
export TP
export TC

export SO
export EXE
export CC
export CXX
export AR
export STRIP
export CFLAGS
export CFLAGS.COMMON
export CFLAGS.GCOMMON
export CFLAGS.GCOMMON.DEBUG
export CFLAGS.GCOMMON.RELEASE
export CFLAGS.GCOMMON.CHECK
export CFLAGS.GCOMMON.COV
export CFLAGS.GCOMMON.ASAN
export CFLAGS.GCOMMON.UBSAN
export CXXFLAGS
export CXXFLAGS.COMMON
export CXXFLAGS.COMMON.DEBUG
export CXXFLAGS.COMMON.RELEASE
export CXXFLAGS.COMMON.CHECK
export CXXFLAGS.COMMON.COV
export CXXFLAGS.COMMON.ASAN
export CXXFLAGS.COMMON.UBSAN
export LDFLAGS
export DEFINES
export UNDEFINES
