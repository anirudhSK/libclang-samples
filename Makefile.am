AM_CXXFLAGS = $(PICKY_CXXFLAGS)
AM_CPPFLAGS = -I/usr/lib/llvm-3.5/include/
bin_PROGRAMS = dummy
common_source =
dummy_SOURCES = $(common_source) dummy.cc
dummy_LDFLAGS = -L/usr/lib/llvm-3.5/lib/
dummy_LDADD   = -lclang
