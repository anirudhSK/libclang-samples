#include "src/ast_traversal.h"

#include <iostream>

AstTraversal::AstTraversal(const CXTranslationUnit & translation_unit,
                           const CXCursor & cursor)
    : translation_unit_(translation_unit) {
  std::cout << PrettyPrinter(translation_unit_, cursor).output() << std::endl;
}
