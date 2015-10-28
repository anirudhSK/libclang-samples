AM_CXXFLAGS = $(PICKY_CXXFLAGS)
AM_CPPFLAGS = -I/usr/lib/llvm-3.4/include/
bin_PROGRAMS = domino

common_source = compiler_pass.h compiler_pass.cc util.cc util.h
domino_SOURCES = $(common_source) domino.cc
domino_LDFLAGS = -L/usr/lib/llvm-3.4/lib/
domino_LDADD   = -lclang $(top_srcdir)/third_party/libutils.a
