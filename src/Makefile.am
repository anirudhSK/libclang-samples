AM_CXXFLAGS = $(PICKY_CXXFLAGS)
AM_CPPFLAGS = -I/usr/lib/llvm-3.4/include/
bin_PROGRAMS = dummy

common_source = compiler_pass.h
dummy_SOURCES = $(common_source) dummy.cc
dummy_LDFLAGS = -L/usr/lib/llvm-3.4/lib/
dummy_LDADD   = -lclang
