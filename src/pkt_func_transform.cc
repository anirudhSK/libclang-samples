#include "src/pkt_func_transform.h"

#include <algorithm>

#include "third_party/assert_exception.h"

using namespace clang;

std::vector<CXCursor> get_all_decls(const CXTranslationUnit & translation_unit) {
  std::vector<CXCursor> ret;

  // Create an anonymous function to accumulate declarations into ret
  // as the AST rooted under translation_unit is traversed
  auto decl_accumulator = [&ret]
                          (CXCursor cursor,
                           CXCursor parent __attribute__ ((unused)),
                           CXClientData translation_unit __attribute__((unused)))
                           { ret.emplace_back(cursor); return CXChildVisit_Continue; };

  // Start traversing nodes starting from translation_unit
  clang_visitChildren(clang_getTranslationUnitCursor(translation_unit),
                      decl_accumulator,
                      translation_unit);

  return ret;
}

int get_priority(const CXCursor & cursor,
                 const CXTranslationUnit & translation_unit) {
  assert_exception(clang_isDeclaration(cursor.kind));
  switch(cursor_kind) {
    case CXCursor_VarDecl      : return 1;
    case CXCursor_FunctionDecl : is_packet_func(cursor) ? return 2 : return 3;
    case CXCursor_StructDecl   : return 4;
    case CXCursor_TypedefDecl  : return 5;
    default : throw std::logic_error("get_priority in pkt_func_transform.cc cannot handle decl " +
                                     PrettyPrinter::pretty_print(translation_unit, cursor) + " of type " +
                                     ClangString::get_str(clang_getCursorKindSpelling(cursor.kind));
  }
}

std::string pkt_func_transform(const CXTranslationUnit & translation_unit,
                               const FuncBodyTransform & func_body_transform) {
  // Accumulate all declarations
  std::vector<CXCursor> all_decls = get_all_decls(translation_unit);

  // Sort all_decls
  std::sort(all_decls.begin(),
            all_decls.end(),
            [] (const auto & decl1, const auto & decl2)
            { return get_priority(decl1, translation_unit) < get_priority(decl2, translation_unit); });

  // Loop through sorted vector of declarations
  std::string state_var_str = "";
  std::string scalar_func_str = "";
  std::string pkt_func_str = "";
  std::string record_decl_str = "";
  std::vector<std::string> new_decls;
  for (const auto & child_decl : all_decls) {
    assert_exception(clang_isDeclaration(child_decl.kind));
    if (child_decl.kind = CXCursor_VarDecl) {
      state_var_str += PrettyPrinter::pretty_print(translation_unit, child_decl) + ";";
    } else if (child_decl.kind == CXCursor_FunctionDecl and not is_packet_func(child_decl)) {
      // TODO: Implement generate_scalar_func_def
      scalar_func_str += generate_scalar_func_def(dyn_cast<FunctionDecl>(child_decl));
    } else if (child_decl.kind == CXCursor_FunctionDecl and is_packet_func(child_decl)) {
      // TODO: Everything below
      // Extract function signature
      assert_exception(clang_Cursor_getNumArguments(child_decl) == 1);
      const CXCursor    pkt_param = clang_Cursor_getArgument(child_decl, 0);
      const std::string pkt_type  = ClangString::get_str(clang_getTypeSpelling(clang_getCursorType(pkt_param)));
      const std::string pkt_name  = PrettyPrinter::pretty_print(pkt_param, translation_unit);

      // Transform function body
      // TODO: Implement get_body
      const auto transform_pair   = func_body_transform(child_decl->getBody(), pkt_name);
      const auto transformed_body = transform_pair.first;
      new_decls = transform_pair.second;

      // Rewrite function with new body
      // TODO: Implement getNameInfo
      pkt_func_str += function_decl->getReturnType().getAsString() + " " +
                      function_decl->getNameInfo().getName().getAsString() +
                      "( " + pkt_type + " " +  pkt_name + ") " +
                      transformed_body;
    } else if (child_decl.kind == CXCursor_StructDecl) {
      // Open struct definition
      // TODO: Everything below
      assert_exception(dyn_cast<RecordDecl>(child_decl)->isStruct());
      record_decl_str += "struct " + dyn_cast<RecordDecl>(child_decl)->getNameAsString() + "{\n";

      // acummulate current fields in struct
      for (const auto * field_decl : dyn_cast<DeclContext>(child_decl)->decls())
        record_decl_str += dyn_cast<ValueDecl>(field_decl)->getType().getAsString() + " " + clang_value_decl_printer(dyn_cast<ValueDecl>(field_decl)) + ";";

      // Add newly created fields
      for (const auto & new_decl : new_decls)
        record_decl_str += new_decl;

      // Close struct definition
      record_decl_str += "};";
    }
  }
  return state_var_str + scalar_func_str + record_decl_str + pkt_func_str;
}
