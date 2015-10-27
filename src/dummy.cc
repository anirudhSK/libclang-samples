#include "clang-c/Index.h"

#include "compiler_pass.h"

#include <cstdio>
#include <iostream>

int main() {
  CXIndex Index = clang_createIndex(0, 0);
  const char* options[] = {"-Werror", "-Wall"};
  CXTranslationUnit TU = clang_parseTranslationUnit(Index, "input.c", options, 2, nullptr, 0, CXTranslationUnit_None);
  for (unsigned I = 0, N = clang_getNumDiagnostics(TU); I != N; ++I) {
    CXDiagnostic Diag = clang_getDiagnostic(TU, I);
    CXString String = clang_formatDiagnostic(Diag,
    clang_defaultDiagnosticDisplayOptions());
    fprintf(stderr, "%s\n", clang_getCString(String));
    clang_disposeString(String);
  }

  clang_disposeTranslationUnit(TU);
  clang_disposeIndex(Index);
}
