#include "clang-c/Index.h"

#include "compiler_pass.h"

#include <cstdio>
#include <iostream>

#include <string>

int main(int argc, const char **argv) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: " << argv[0] << " <source_file>" << std::endl;
      return EXIT_FAILURE;
    } else {
      CXIndex Index = clang_createIndex(0, 0);
      const char* options[] = {"-Werror", "-Wall"};
      CXTranslationUnit TU = clang_parseTranslationUnit(Index, argv[1], options, 2, nullptr, 0, CXTranslationUnit_None);
      std::string all_diags = "";
      for (unsigned I = 0, N = clang_getNumDiagnostics(TU); I != N; ++I) {
        CXDiagnostic Diag = clang_getDiagnostic(TU, I);
        CXString String = clang_formatDiagnostic(Diag,
        clang_defaultDiagnosticDisplayOptions());
        all_diags += std::string(clang_getCString(String)) + "\n";
        clang_disposeString(String);
      }

      clang_disposeTranslationUnit(TU);
      clang_disposeIndex(Index);
      if (all_diags != "") {
        throw std::logic_error("Compilation failed with diagnostics\n" + all_diags);
      } else {
        return EXIT_SUCCESS;
      }
    }
  } catch (const std::exception & e) {
    std::cerr << "Caught exception in main " << std::endl << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
