#include "src/compiler_pass.h"

#include "src/pretty_printer.h"

#include <iostream>

SinglePass::SinglePass(const Transformer & t_transformer __attribute__((unused)), const std::string & str)
    : CompilerPass(str),
      index_(clang_createIndex(0, 0)),
      translation_unit_(clang_parseTranslationUnit(index_,
                                                   temp_file_.name().c_str(),
                                                   diagnostics.data(),
                                                   static_cast<int>(diagnostics.size()),
                                                   nullptr,
                                                   0,
                                                   CXTranslationUnit_None)) {
  std::string all_diags = "";
  for (unsigned i = 0, n = clang_getNumDiagnostics(translation_unit_); i != n; ++i) {
    ClangDiagnostic diag(clang_getDiagnostic(translation_unit_, i));
    ClangString diag_str(clang_formatDiagnostic(diag.get_raw(),
                                                clang_defaultDiagnosticDisplayOptions()));
    all_diags += diag_str.stl_str() + "\n";
  }

  if (all_diags != "") {
    throw std::logic_error("Compilation failed with diagnostics\n" + all_diags);
  }

  /// Echo translation unit
  echo_translation_unit();
  std::cout << std::endl;
}

void SinglePass::echo_translation_unit(void) {
  std::cout<<PrettyPrinter(translation_unit_,
                           clang_getTranslationUnitCursor(translation_unit_)).output();
}

SinglePass::~SinglePass() {
  clang_disposeTranslationUnit(translation_unit_);
  clang_disposeIndex(index_);
}
