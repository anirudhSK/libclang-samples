#ifndef SRC_PKT_FUNC_TRANSFORM_H_
#define SRC_PKT_FUNC_TRANSFORM_H_

#include <utility>
#include <string>
#include <vector>
#include <functional>

#include "clang-c/Index.h"

/// Accumulate all declarations inside a translation_unit
std::vector<CXCursor> get_all_decls(const CXTranslationUnit & translation_unit);

/// Priority order of parsing declarations
/// --> state variables,
/// --> packet declaration,
/// --> scalar functions,
/// --> packet functions
int get_priority(const CXCursor & cursor,
                 const CXTranslationUnit & translation_unit);

/// Convenience typedef for a function that transforms a function body
typedef std::function<std::pair<std::string, std::vector<std::string>>(const CXCursor & function_body, const std::string & pkt_name)> FuncBodyTransform;

/// Tranform a translation unit by modifying packet functions
/// alone. Pass through the rest as such without modifications.
std::string pkt_func_transform(const CXTranslationUnit & translation_unit,
                               const FuncBodyTransform & func_body_transform);

#endif  // SRC_PKT_FUNC_TRANSFORM_H_
