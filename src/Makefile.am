AM_CXXFLAGS = $(PICKY_CXXFLAGS)
AM_CPPFLAGS = -I/usr/lib/llvm-3.4/include/
bin_PROGRAMS = domino

common_source = compiler_pass.h compiler_pass.cc util.cc util.h clang_string.h clang_diagnostic.h pretty_printer.h pretty_printer.cc ast_traversal.h ast_traversal.cc pkt_func_transform.h pkt_func_transform.cc
domino_SOURCES = $(common_source) domino.cc
domino_LDFLAGS = -L/usr/lib/llvm-3.4/lib/
domino_LDADD   = -lclang $(top_srcdir)/third_party/libutils.a
