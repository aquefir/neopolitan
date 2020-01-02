# -*- coding: utf-8 -*-
## This Makefile provides the bodies of a variety of build targets (or
## ‘recipes’) normally used in building native executables and libraries.
## These include: debug, release, sanity check, code coverage, and address
## sanitisation tunings. Using the conventional *FILES and *FLAGS Makefile
## variables, the toolchain program variables (like ‘$(CC)’), the $(PROJECT)
## variable, and some miscellaneous helpers, it will fill out all of the
## typical details for these targets automatically, just by including it in
## the main Makefile.
## This works with both C and C++ code, and is continuously tested on macOS
## Mojave and Arch Linux.
## this file expects the following variables to be defined:
## CFILES, CPPFILES, HFILES, HPPFILES, GCNOFILES, GCDAFILES, CFLAGS, CXXFLAGS,
## LDFLAGS, CC, CXX, AR, FMT, INCLUDES, INCLUDEL, LIBDIRS, LIBS, FWORKS,
## OFILES, PROJECT, EXEFILE, AFILE, SOFILE, 3PLIBS, 3PLIBDIR, TES_CFILES,
## TES_CPPFILES, TES_HFILES, TES_HPPFILES, TES_GCNOFILES, TES_GCDAFILES

# Add 3rd-party includes
INCLUDES += $(patsubst %,$(3PLIBDIR)/%lib/include,$(3PLIBS)) \
	$(3PLIBDIR)/teslib/include

# Add 3rd-party library directories
LIBDIRS += $(patsubst %,$(3PLIBDIR)/%lib,$(3PLIBS))
LIBS += $(3PLIBS)

# Variable transformations for command invocation
LIB := $(patsubst %,-l%,$(LIBS)) $(patsubst %,-L%,$(LIBDIRS))
INCLUDE := $(patsubst %,-isystem %,$(INCLUDES)) \
	$(patsubst %,-iquote %,$(INCLUDEL))
FWORK := $(patsubst %,-framework %,$(FWORKS))

# Populated below
TARGETS :=

TESTARGET := $(PROJECT)_test

# specify all target filenames
EXETARGET := $(PROJECT)$(EXE)
SOTARGET  := lib$(PROJECT).$(SO)
ATARGET   := lib$(PROJECT).$(A)

ifeq ($(strip $(EXEFILE)),1)
TARGETS += $(EXETARGET)
endif
ifeq ($(strip $(SOFILE)),1)
TARGETS += $(SOTARGET)
endif
ifeq ($(strip $(AFILE)),1)
TARGETS += $(ATARGET)
endif

# Use ?= so that this can be overridden. This is useful when some projects in
# a solution need $(CXX) linkage when the main project lacks any $(CPPFILES)
ifeq ($(strip $(CPPFILES)),)
	CCLD ?= $(CC)
else
	CCLD ?= $(CXX)
endif

.PHONY: debug release check cov asan clean format

debug: CFLAGS += -O0 -g3 -UNDEBUG
debug: REALSTRIP := ':' ; # : is a no-op
debug: $(TARGETS)

release: CFLAGS += -O2 -DNDEBUG=1
release: REALSTRIP := $(STRIP) ;
release: $(TARGETS)

check: CFLAGS += -Wextra -Werror -Os -DNDEBUG=1
check: REALSTRIP := ':' ; # : is a no-op
check: $(TARGETS)

cov: CFLAGS += -O0 -g3 -UNDEBUG -fprofile-arcs -ftest-coverage
cov: LDFLAGS += -fprofile-arcs
cov: REALSTRIP := ':' ; # : is a no-op
ifeq ($(strip $(NO_TES)),)
cov: CFLAGS += -DTES_BUILD=1
cov: LDFLAGS += -L$(3PLIBDIR)/teslib
cov: LIB += -ltes
cov: $(TESTARGET)
else
cov: $(TARGETS)
endif

# address sanitised build for valgrind
ifeq ($(CC),clang)
asan: CFLAGS += -fsanitize=address -fno-omit-frame-pointer -O1 -g3 \
	-fno-common -fno-optimize-sibling-calls -fsanitize=undefined \
	-fno-sanitize-recover=all
else
asan: CFLAGS += -fsanitize=address -fno-omit-frame-pointer -O1 -g \
	-fno-common -fno-optimize-sibling-calls
endif
asan: LDFLAGS += -fsanitize=address
asan: REALSTRIP := ':' ; # : is a no-op
ifeq ($(strip $(NO_TES)),)
asan: CFLAGS += -DTES_BUILD=1
asan: LDFLAGS += -L$(3PLIBDIR)/teslib
asan: LIB += -ltes
asan: $(TESTARGET)
else
asan: $(TARGETS)
endif

# Object file builds
%.cpp.o: %.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $(INCLUDE) $<

%.c.o: %.c
	$(CC) -c -o $@ $(CFLAGS) $(INCLUDE) $<

# Static library builds
$(ATARGET): $(OFILES)
	$(AR) $(ARFLAGS) $@ $^

# Shared library builds
$(SOTARGET): $(OFILES)
	$(CCLD) $(LDFLAGS) -shared -o $@ $(LIB) $^
	$(REALSTRIP) -s $^

# Executable builds
$(EXETARGET): $(OFILES)
	$(CCLD) $(LDFLAGS) -o $@ $(LIB) $^
	$(REALSTRIP) -s $^

$(TESTARGET): $(OFILES) $(TES_OFILES)
	$(CCLD) $(LDFLAGS) -o $@ $(LIB) $^

clean:
	$(RM) $(TARGETS)
	$(RM) $(TESTARGET)
	$(RM) $(OFILES)
	$(RM) $(GCNOFILES)
	$(RM) $(GCDAFILES)
	$(RM) $(TES_OFILES)
	$(RM) $(TES_GCNOFILES)
	$(RM) $(TES_GCDAFILES)

format:
	for _file in $(CFILES) $(HFILES) $(CPPFILES) $(HPPFILES); do \
		$(FMT) -i -style=file $$_file ; \
	done
