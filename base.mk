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

UNAME := $(shell uname -s)
# User can specify TP=Win32 at the command line
TP ?= $(UNAME)
TC ?= llvm
ifeq ($(strip $(UNAME)),Darwin)
ifneq ($(strip $(TC)),llvm)
ifneq ($(strip $(TC)),xcode)
$(error Invalid toolchain specified. macOS supports either llvm or xcode)
endif # $(TC) xcode
endif # $(TC) llvm
endif # $(UNAME)

## Specify the default host variables
## form: <var>.<host>[.<target>]
##

ifeq ($(strip $(TC)),llvm)
CC.DARWIN       := /usr/local/opt/llvm/bin/clang # brew LLVM
else
CC.DARWIN       := /usr/bin/clang # Xcode
endif
CC.LINUX        := /usr/bin/gcc
CC.DARWIN.WIN32 := /usr/local/bin/i686-w64-mingw32-gcc
CC.LINUX.WIN32  := /usr/bin/i686-w64-mingw32-gcc

ifeq ($(strip $(TC)),llvm)
CXX.DARWIN       := /usr/local/opt/llvm/bin/clang++ # brew LLVM
else
CXX.DARWIN       := /usr/bin/clang++ # Xcode
endif
CXX.LINUX        := /usr/bin/g++
CXX.DARWIN.WIN32 := /usr/local/bin/i686-w64-mingw32-g++
CXX.LINUX.WIN32  := /usr/bin/i686-w64-mingw32-g++

ifeq ($(strip $(TC)),llvm)
AR.DARWIN := /usr/local/opt/llvm/bin/llvm-ar # brew LLVM
else
AR.DARWIN := /usr/bin/ar # Xcode
endif
AR.LINUX        := /usr/bin/ar
AR.DARWIN.WIN32 := /usr/local/bin/i686-w64-mingw32-ar
AR.LINUX.WIN32  := /usr/bin/i686-w64-mingw32-ar

ifeq ($(strip $(TC)),llvm)
STRIP.DARWIN       := /usr/local/opt/llvm/bin/llvm-strip # brew LLVM
else
STRIP.DARWIN       := /usr/bin/strip # Xcode
endif
STRIP.LINUX        := /usr/bin/strip
STRIP.DARWIN.WIN32 := /usr/local/bin/i686-w64-mingw32-strip
STRIP.LINUX.WIN32  := /usr/bin/i686-w64-mingw32-strip

TC.DARWIN := $(TC) # see above for eval
TC.LINUX  := gnu
TC.WIN32  := mingw32

## Specify the default target variables
## form: <var>.<target>
##

SO.DARWIN := dylib
SO.LINUX  := so
SO.WIN32  := dll
SO.WIN32  := dll

CFLAGS.COMMON          := -O2 -pipe
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

LDFLAGS := -fPIE
ifeq ($(strip $(TC)),llvm)
LDFLAGS += -fprofile-arcs -ftest-coverage
else ifeq ($(strip $(TC)),xcode)
LDFLAGS += -fprofile-arcs -ftest-coverage
else
LDFLAGS += -fprofile-instr-generate -fcoverage-mapping
endif

## Resolve the correct host-target suffixes
##

ifeq ($(strip $(UNAME)),Darwin)
ifeq ($(strip $(TP)),Darwin)
suf := DARWIN
tsuf := DARWIN
else ifeq ($(strip $(TP)),Win32)
suf := DARWIN.WIN32
tsuf := WIN32
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
else
EXE :=
endif # $(TP)

## Set the host/target specific defaults and env customs
##

SO := $(SO.$(tsuf))
TC := $(TC.$(tsuf))

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

ifeq ($(strip $(TC)),gnu)
CFLAGS   += -ffile-prefix-map=OLD=NEW
CXXFLAGS += -ffile-prefix-map=OLD=NEW
else ifeq ($(strip $(TC)),mingw32)
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
