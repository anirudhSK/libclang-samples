#include "src/pretty_printer.h"

#include "third_party/assert_exception.h"

#include "src/clang_string.h"

PrettyPrinter::PrettyPrinter(const CXTranslationUnit & translation_unit,
                             const CXCursor & cursor)
    : translation_unit_(translation_unit) {
  /// Get source range
  CXSourceRange src_range = clang_getCursorExtent(cursor);

  /// Extract tokens
  clang_tokenize(translation_unit_, src_range, &tokens_, &num_tokens_);

  // Either we have at least two tokens, current and the next one
  // Or it's empty (such as TypedefDecls at the beginning)
  assert_exception(num_tokens_ >= 2 or num_tokens_ == 0);

  /// Append to output_
  if (num_tokens_ >= 2) {
    for (unsigned i = 0; i < num_tokens_ - 1; i++) {
      output_ += ClangString(clang_getTokenSpelling(translation_unit_,
                           *(tokens_ + i))).stl_str() + " ";
    }
  } else if (num_tokens_ == 0) {
    output_ = "";
  }
}

PrettyPrinter::~PrettyPrinter() {
  if (translation_unit_ and tokens_) {
    clang_disposeTokens(translation_unit_,
                        tokens_,
                        num_tokens_);
  }
}

PrettyPrinter::PrettyPrinter(PrettyPrinter && other)
    : output_(other.output_),
      tokens_(other.tokens_),
      num_tokens_(other.num_tokens_),
      translation_unit_(other.translation_unit_) {
  // reset other
  other.output_ = "";
  other.tokens_ = nullptr;
  other.num_tokens_ = 0;
  other.translation_unit_ = nullptr;
}
