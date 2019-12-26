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
## OFILES, PROJECT, EXEFILE, AFILE, SOFILE, 3PLIBS, 3PLIBDIR

# Variable transformations for command invocation
LIB := $(patsubst %,-l%,$(LIBS)) $(patsubst %,-L%,$(LIBDIRS))
INCLUDE := $(patsubst %,-isystem %,$(INCLUDES)) \
	$(patsubst %,-iquote %,$(INCLUDEL))
FWORK := $(patsubst %,-framework %,$(FWORKS))

# Populated below
TARGETS_DBG  :=
TARGETS_REL  :=
TARGETS_CHK  :=
TARGETS_COV  :=
TARGETS_ASAN :=

# This variable is used to specify the main project directory (such as the
# repository root), into which the executable, and any subproject binaries
# will be output. This is useful in subproject Makefiles to cleanly get the
# library binary to be output in a parent directory where the parent Make job
# can reach it, without muddling the project name (which would break lib
# naming conventions).
ifneq ($(PROJDIR),)
PATHPRE := $(PROJDIR)/
else
PATHPRE :=
endif

# Transform 3rd-party library names for linkage
# NOTE: The libraries must end up in the same directory as the depending
# executable! See the $(PROJDIR) variable below.
3PLIB_DBG  := $(patsubst %,$(PATHPRE)lib%_dbg.$(A),$(3PLIBS))
3PLIB_REL  := $(patsubst %,$(PATHPRE)lib%_rel.$(A),$(3PLIBS))
3PLIB_CHK  := $(patsubst %,$(PATHPRE)lib%_chk.$(A),$(3PLIBS))
3PLIB_COV  := $(patsubst %,$(PATHPRE)lib%_cov.$(A),$(3PLIBS))
3PLIB_ASAN := $(patsubst %,$(PATHPRE)lib%_asan.$(A),$(3PLIBS))

# specify all target filenames
EXEFILE_DBG  := $(PATHPRE)$(PROJECT)_dbg$(EXE)
EXEFILE_REL  := $(PATHPRE)$(PROJECT)_rel$(EXE)
EXEFILE_CHK  := $(PATHPRE)$(PROJECT)_chk$(EXE)
EXEFILE_COV  := $(PATHPRE)$(PROJECT)_cov$(EXE)
EXEFILE_ASAN := $(PATHPRE)$(PROJECT)_asan$(EXE)
SOFILE_DBG   := $(PATHPRE)lib$(PROJECT)_dbg.$(SO)
SOFILE_REL   := $(PATHPRE)lib$(PROJECT)_rel.$(SO)
SOFILE_CHK   := $(PATHPRE)lib$(PROJECT)_chk.$(SO)
SOFILE_COV   := $(PATHPRE)lib$(PROJECT)_cov.$(SO)
SOFILE_ASAN  := $(PATHPRE)lib$(PROJECT)_asan.$(SO)
AFILE_DBG    := $(PATHPRE)lib$(PROJECT)_dbg.$(A)
AFILE_REL    := $(PATHPRE)lib$(PROJECT)_rel.$(A)
AFILE_CHK    := $(PATHPRE)lib$(PROJECT)_chk.$(A)
AFILE_COV    := $(PATHPRE)lib$(PROJECT)_cov.$(A)
AFILE_ASAN   := $(PATHPRE)lib$(PROJECT)_asan.$(A)

ifeq ($(strip $(EXEFILE)),1)
TARGETS_DBG  += $(EXEFILE_DBG)
TARGETS_REL  += $(EXEFILE_REL)
TARGETS_CHK  += $(EXEFILE_CHK)
TARGETS_COV  += $(EXEFILE_COV)
TARGETS_ASAN += $(EXEFILE_ASAN)
endif
ifeq ($(strip $(SOFILE)),1)
TARGETS_DBG  += $(SOFILE_DBG)
TARGETS_REL  += $(SOFILE_REL)
TARGETS_CHK  += $(SOFILE_CHK)
TARGETS_COV  += $(SOFILE_COV)
TARGETS_ASAN += $(SOFILE_ASAN)
endif
ifeq ($(strip $(AFILE)),1)
TARGETS_DBG  += $(AFILE_DBG)
TARGETS_REL  += $(AFILE_REL)
TARGETS_CHK  += $(AFILE_CHK)
TARGETS_COV  += $(AFILE_COV)
TARGETS_ASAN += $(AFILE_ASAN)
endif

# Use ?= so that this can be overridden. This is useful when some projects in
# a solution need $(CXX) linkage when the main project lacks any $(CPPFILES)
ifeq ($(strip $(CPPFILES)),)
	LD := $(CC)
else
	LD := $(CXX)
endif

.PHONY: debug release check cov asan

ifeq ($(NDEBUG),1)
	CFLAGS += -DNDEBUG=1 -O2 -Wall
else
	CFLAGS += -O0 -g -w
endif

debug: CFLAGS += -O0 -g3 -UNDEBUG
debug: $(TARGETS_DBG)

release: CFLAGS += -O2 -DNDEBUG=1
release: $(TARGETS_REL)

check: CFLAGS += -Wextra -Werror -Os -DNDEBUG=1
check: $(TARGETS_CHK)

cov: CFLAGS += -O0 -g3 -UNDEBUG -fprofile-arcs -ftest-coverage
cov: LDFLAGS += -fprofile-arcs
cov: $(TARGETS_COV)

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
asan: $(TARGETS_ASAN)

# Object file builds
%.cpp.o: %.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $(INCLUDE) $<

%.c.o: %.c
	$(CC) -c -o $@ $(CFLAGS) $(INCLUDE) $<

# Static library builds
$(AFILE_DBG): $(OFILES) $(3PLIB_DBG)
	$(AR) $(ARFLAGS) $@ $(OFILES)

$(AFILE_REL): $(OFILES)
	$(STRIP) -s $(OFILES) $(3PLIB_REL)
	$(AR) $(ARFLAGS) $@ $(OFILES)

$(AFILE_CHK): $(OFILES) $(3PLIB_CHK)
	$(AR) $(ARFLAGS) $@ $(OFILES)

$(AFILE_COV): $(OFILES) $(3PLIB_COV)
	$(AR) $(ARFLAGS) $@ $(OFILES)

$(AFILE_ASAN): $(OFILES) $(3PLIB_ASAN)
	$(AR) $(ARFLAGS) $@ $(OFILES)

# Shared library builds
$(SOFILE_DBG): $(OFILES) $(3PLIB_DBG)
	$(LD) $(LDFLAGS) -shared -o $@ $(LIB) $(OFILES) $(3PLIB_DBG)

$(SOFILE_REL): $(OFILES) $(3PLIB_REL)
	$(LD) $(LDFLAGS) -shared -o $@ $(LIB) $(OFILES) $(3PLIB_REL)
	$(STRIP) -s $(OFILES)

$(SOFILE_CHK): $(OFILES) $(3PLIB_CHK)
	$(LD) $(LDFLAGS) -shared -o $@ $(LIB) $(OFILES) $(3PLIB_CHK)

$(SOFILE_COV): $(OFILES) $(3PLIB_COV)
	$(LD) $(LDFLAGS) -shared -o $@ $(LIB) $(OFILES) $(3PLIB_COV)

$(SOFILE_ASAN): $(OFILES) $(3PLIB_ASAN)
	$(LD) $(LDFLAGS) -shared -o $@ $(LIB) $(OFILES) $(3PLIB_ASAN)

# Executable builds
$(EXEFILE_DBG): $(OFILES) $(3PLIB_DBG)
	$(LD) $(LDFLAGS) -o $@ $(LIB) $(OFILES) $(3PLIB_DBG)

$(EXEFILE_REL): $(OFILES) $(3PLIB_REL)
	$(LD) $(LDFLAGS) -o $@ $(LIB) $(OFILES) $(3PLIB_REL)
	$(STRIP) -s $(OFILES)

$(EXEFILE_CHK): $(OFILES) $(3PLIB_CHK)
	$(LD) $(LDFLAGS) -o $@ $(LIB) $(OFILES) $(3PLIB_CHK)

$(EXEFILE_COV): $(OFILES) $(3PLIB_COV)
	$(LD) $(LDFLAGS) -o $@ $(LIB) $(OFILES) $(3PLIB_COV)

$(EXEFILE_ASAN): $(OFILES) $(3PLIB_ASAN)
	$(LD) $(LDFLAGS) -o $@ $(LIB) $(OFILES) $(3PLIB_ASAN)
