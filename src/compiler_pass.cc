#include "src/compiler_pass.h"

SinglePass::SinglePass(const Transformer & t_transformer __attribute__((unused)), const std::string & str)
    : CompilerPass(str),
      index_(clang_createIndex(0, 0)),
      translation_unit_(clang_parseTranslationUnit(index_, temp_file_.name().c_str(), diagnostics.data(), static_cast<int>(diagnostics.size()), nullptr, 0, CXTranslationUnit_None)) {}

SinglePass::~SinglePass() {
  clang_disposeTranslationUnit(translation_unit_);
  clang_disposeIndex(index_);
}
