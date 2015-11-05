#include "src/ast_traversal.h"

#include <iostream>

#include "src/clang_string.h"

CXChildVisitResult AstTraversal::echo_visitor(CXCursor cursor,
                                              CXCursor parent __attribute__((unused)),
                                              CXClientData translation_unit) {
  std::cout << ClangString(clang_getCursorKindSpelling(cursor.kind)).stl_str() << std::endl;
  std::cout << PrettyPrinter(reinterpret_cast<CXTranslationUnit>(translation_unit), cursor).output() << std::endl;
  std::cout << std::endl << std::endl;
  return CXChildVisit_Recurse;
}

AstTraversal::AstTraversal(const CXTranslationUnit & translation_unit,
                           const CXCursor & cursor)
    : translation_unit_(translation_unit) {
  clang_visitChildren(cursor,
                      echo_visitor,
                      translation_unit_);
}
