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
## CFILES, CPPFILES, HFILES, HPPFILES, CFLAGS, CXXFLAGS, LDFLAGS, CC, CXX, AR,
## FMT, INCLUDES, INCLUDEL, DEFINES, UNDEFINES, LIBDIRS, LIBS, FWORKS,
## PROJECT, EXEFILE, AFILE, SOFILE, 3PLIBS, 3PLIBDIR, SO, EXE, UNAME, TP, TC,
## TES_CFILES, TES_CPPFILES, TES_HFILES, TES_HPPFILES

# Incorporate 3rdparty dependencies
INCLUDES += $(patsubst %,$(3PLIBDIR)/%lib/include,$(3PLIBS))
LIBDIRS  += $(patsubst %,$(3PLIBDIR)/%lib,$(3PLIBS))
LIBS     += $(3PLIBS)

# Variable transformations for command invocation
LIB := $(patsubst %,-L%,$(LIBDIRS)) $(patsubst %,-l%,$(LIBS))
ifeq ($(CC),tcc)
INCLUDE := $(patsubst %,-I%,$(INCLUDES)) $(patsubst %,-isystem %,$(INCLUDEL))
else
INCLUDE := $(patsubst %,-isystem %,$(INCLUDES)) \
	$(patsubst %,-iquote %,$(INCLUDEL))
endif
DEFINE := $(patsubst %,-D%,$(DEFINES)) $(patsubst %,-U%,$(UNDEFINES))
FWORK := $(patsubst %,-framework %,$(FWORKS))

# Populated below
TARGETS :=

TESTARGETS := $(TES_CFILES:.tes.c=.c.tes) $(TES_CPPFILES:.tes.cpp=.cpp.tes)

# specify all target filenames
EXETARGET := $(PROJECT)$(EXE)
SOTARGET  := lib$(PROJECT).$(SO)
ATARGET   := lib$(PROJECT).a

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

.PHONY: debug release check cov asan ubsan clean format

## Debug build
## useful for: normal testing, valgrind, LLDB
##
debug: DEFINE += -UNDEBUG
debug: CFLAGS += $(CFLAGS.COMMON)
ifneq ($(CC),tcc)
debug: CFLAGS += $(CFLAGS.GCOMMON) $(CFLAGS.GCOMMON.DEBUG)
endif # tcc
debug: CXXFLAGS += $(CXXFLAGS.COMMON) $(CXXFLAGS.COMMON.DEBUG)
debug: REALSTRIP := ':' ; # : is a no-op
debug: $(TARGETS)

## Release build
## useful for: deployment
##
release: DEFINE += -DNDEBUG=1
release: CFLAGS += $(CFLAGS.COMMON)
ifneq ($(CC),tcc)
release: CFLAGS += $(CFLAGS.GCOMMON) $(CFLAGS.GCOMMON.RELEASE)
endif # tcc
release: CXXFLAGS += $(CXXFLAGS.COMMON) $(CXXFLAGS.COMMON.RELEASE)
release: REALSTRIP := $(STRIP)
release: $(TARGETS)

## Sanity check build
## useful for: pre-tool bug squashing
##
check: DEFINE += -UNDEBUG
check: CFLAGS += $(CFLAGS.COMMON)
ifneq ($(CC),tcc)
check: CFLAGS += $(CFLAGS.GCOMMON) $(CFLAGS.GCOMMON.CHECK)
endif # tcc
check: CXXFLAGS += $(CXXFLAGS.COMMON) $(CXXFLAGS.COMMON.CHECK)
check: REALSTRIP := ':' ; # : is a no-op
check: $(TARGETS)

## Code coverage build
## useful for: checking coverage of test suite
##
cov: DEFINE += -UNDEBUG -D_CODECOV
cov: CFLAGS += $(CFLAGS.COMMON)
ifneq ($(CC),tcc)
cov: CFLAGS += $(CFLAGS.GCOMMON) $(CFLAGS.GCOMMON.COV)
endif # tcc
cov: CXXFLAGS += $(CXXFLAGS.COMMON) $(CXXFLAGS.COMMON.COV)
cov: LDFLAGS += $(LDFLAGS.COV)
cov: REALSTRIP := ':' ; # : is a no-op
ifeq ($(strip $(NO_TES)),)
cov: DEFINE += -DTES_BUILD=1
cov: $(TESTARGETS)
else
cov: DEFINE += -UTES_BUILD
cov: $(TARGETS)
endif # $(NO_TES)

## Address sanitised build
## useful for: squashing memory issues
##
asan: DEFINE += -UNDEBUG -D_ASAN
asan: CFLAGS += $(CFLAGS.COMMON)
ifneq ($(CC),tcc)
asan: CFLAGS += $(CFLAGS.GCOMMON) $(CFLAGS.GCOMMON.ASAN)
endif # tcc
asan: CXXFLAGS += $(CXXFLAGS.COMMON) $(CXXFLAGS.COMMON.ASAN)
asan: LDFLAGS += $(LDFLAGS.ASAN)

asan: REALSTRIP := ':' ; # : is a no-op
ifeq ($(strip $(NO_TES)),)
asan: DEFINE += -DTES_BUILD=1
ifneq ($(strip $(EXEFILE)),)
asan: $(TARGETS)
endif
asan: $(TESTARGETS)
else
asan: DEFINE += -UTES_BUILD
asan: $(TARGETS)
endif # $(NO_TES)

## Undefined Behaviour sanitised build
## useful for: squashing UB :-)
##
ubsan: DEFINE += -UNDEBUG -D_UBSAN
ubsan: CFLAGS += $(CFLAGS.COMMON)
ifneq ($(CC),tcc)
ubsan: CFLAGS += $(CFLAGS.GCOMMON) $(CFLAGS.GCOMMON.UBSAN)
endif # tcc
ubsan: CXXFLAGS += $(CXXFLAGS.COMMON) $(CXXFLAGS.COMMON.UBSAN)
ubsan: LDFLAGS += $(LDFLAGS.UBSAN)
ubsan: REALSTRIP := ':' ; # : is a no-op
ifeq ($(strip $(NO_TES)),)
ubsan: DEFINE += -DTES_BUILD=1
ifneq ($(strip $(EXEFILE)),)
ubsan: $(TARGETS)
endif
ubsan: $(TESTARGETS)
else
ubsan: DEFINE += -UTES_BUILD
ubsan: $(TARGETS)
endif # $(NO_TES)

# Define object files
OFILES     := $(CFILES:.c=.c.o) $(CPPFILES:.cpp=.cpp.o)
TES_OFILES := $(TES_CFILES:.c=.c.o) $(TES_CPPFILES:.cpp=.cpp.o)

# Object file builds
%.cpp.o: %.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $(INCLUDE) $<

%.c.o: %.c
	$(CC) -c -o $@ $(CFLAGS) $(INCLUDE) $<

%.tes.cpp.o: %.tes.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $(INCLUDE) $<

%.tes.c.o: %.tes.c
	$(CC) -c -o $@ $(CFLAGS) $(INCLUDE) $<

%.cpp.tes: %.tes.cpp.o $(ATARGET)
	$(CCLD) $(LDFLAGS) -o $@ $^ $(LIB)

%.c.tes: %.tes.c.o $(ATARGET)
	$(CCLD) $(LDFLAGS) -o $@ $^ $(LIB)

# Static library builds
$(ATARGET): $(OFILES)
	$(REALSTRIP) -s $^
	$(AR) $(ARFLAGS) $@ $^

# Shared library builds
$(SOTARGET): $(OFILES)
	$(CCLD) $(LDFLAGS) -shared -o $@ $^ $(LIB)
	$(REALSTRIP) -s $@

# Executable builds
$(EXETARGET): $(OFILES)
	$(CCLD) $(LDFLAGS) -o $@ $^ $(LIB)
	$(REALSTRIP) -s $@

DSYMS := $(patsubst %,%.dSYM,$(TARGETS)) $(patsubst %,%.dSYM,$(TESTARGETS))

clean:
	$(RM) $(TARGETS)
	$(RM) $(TESTARGETS)
	$(RM) -r $(DSYMS)
	$(RM) $(OFILES)
	$(RM) $(CFILES:.c=.c.gcno) $(CPPFILES:.cpp=.cpp.gcno)
	$(RM) $(CFILES:.c=.c.gcda) $(CPPFILES:.cpp=.cpp.gcda)
	$(RM) $(TES_OFILES)
	$(RM) $(TES_CFILES:.c=.c.gcno) $(TES_CPPFILES:.cpp=.cpp.gcno)
	$(RM) $(TES_CFILES:.c=.c.gcda) $(TES_CPPFILES:.cpp=.cpp.gcda)

ifeq ($(strip $(NO_TES)),)
format: $(TES_CFILES) $(TES_HFILES) $(TES_CPPFILES) $(TES_HPPFILES)
endif
format: $(CFILES) $(HFILES) $(CPPFILES) $(HPPFILES)
	for _file in $^; do \
		$(FMT) -i -style=file $$_file ; \
	done
	unset _file
