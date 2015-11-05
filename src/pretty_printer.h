#ifndef SRC_PRETTY_PRINTER_H_
#define SRC_PRETTY_PRINTER_H_

#include <string>

#include "clang-c/Index.h"

#include "clang_diagnostic.h"

/// Turn CXCursor objects into strings.
/// Used to print AST nodes into their textual form.
class PrettyPrinter {
 public:
  /// Construct PrettyPrinter for CXCursor object
  PrettyPrinter(const CXTranslationUnit & translation_unit,
                const CXCursor & cursor);

  /// Destruct PrettyPrinter by freeing tokens
  ~PrettyPrinter();

  /// Delete copy constructor and copy assignment
  PrettyPrinter(const PrettyPrinter &) = delete;
  PrettyPrinter & operator=(const PrettyPrinter &) = delete;

  /// Permit move constructor
  PrettyPrinter(PrettyPrinter && other);

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

#endif  // SRC_PRETTY_PRINTER_H_
