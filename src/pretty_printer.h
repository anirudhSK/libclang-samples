#ifndef PRETTY_PRINTER_H_
#define PRETTY_PRINTER_H_

#include "clang-c/Index.h"

#include "clang_diagnostic.h"

/// Turn CXCursor objects into strings.
/// Used to print AST nodes into their textual form.
class PrettyPrinter {
 public:
  /// Construct PrettyPrinter for CXCursor object
  PrettyPrinter(const CXTranslationUnit & translation_unit,
                const CXCursor & cursor)
    : translation_unit_(translation_unit) {
    /// Get source range
    CXSourceRange src_range = clang_getCursorExtent(cursor);

    /// Extract tokens
    clang_tokenize(translation_unit_, src_range, &tokens_, &num_tokens_);

    /// Append to output_
    for (unsigned i = 0; i < num_tokens_; i++) {
      output_ += ClangString(clang_getTokenSpelling(translation_unit_,
                             *(tokens_ + i))).stl_str() + " ";
    }
  }

  /// Destruct PrettyPrinter by freeing tokens
  ~PrettyPrinter() { clang_disposeTokens(translation_unit_, tokens_, num_tokens_); }

  /// Delete copy constructor and copy assignment
  PrettyPrinter(const PrettyPrinter &) = delete;
  PrettyPrinter & operator=(const PrettyPrinter &) = delete;

  /// Output string
  auto output(void) const { return output_; }

 private:
  /// Pretty printed output
  std::string output_ = "";

  /// Token array consisting of generated tokens
  CXToken * tokens_ = nullptr;

  /// Number of generated tokens
  unsigned num_tokens_ = 0;

  /// Reference to translation unit, for destructor
  CXTranslationUnit translation_unit_ = nullptr;
};

#endif  // PRETTY_PRINTER_H_
