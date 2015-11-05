#ifndef SRC_AST_TRAVERSAL_H_
#define SRC_AST_TRAVERSAL_H_

#include "clang-c/Index.h"

#include "src/pretty_printer.h"

/// Traverse an AST starting at a CXCursor,
/// printing out CXKind of each CXCursor as you traverse.
class AstTraversal {
 public:
  /// Construct AstTraversal for CXCursor object
  AstTraversal(const CXTranslationUnit & translation_unit,
               const CXCursor & cursor);

  /// Delete copy constructor and copy assignment
  AstTraversal(const AstTraversal &) = delete;
  AstTraversal & operator=(const AstTraversal &) = delete;

 private:
  /// Dummy echo visitor
  /// that prints out type of cursor
  /// and pretty prints the cursor itself
  static CXChildVisitResult echo_visitor(CXCursor cursor,
                                         CXCursor parent,
                                         CXClientData client_data);

  /// Reference to translation unit, for destructor
  CXTranslationUnit translation_unit_ = nullptr;

  /// PrettyPrinter object for printing
  PrettyPrinter pretty_printer_ = PrettyPrinter();
};

#endif  // SRC_AST_TRAVERSAL_H_
