#ifndef SRC_COMPILER_PASS_H_
#define SRC_COMPILER_PASS_H_

#include <functional>
#include <string>

#include "clang-c/Index.h"

#include "third_party/temp_file.hh"

/// RAII wrapper around CXDiagnostic
class ClangDiagnostic {
 public:
  /// Constructor for clang diagnostic object
  ClangDiagnostic(const CXDiagnostic & t_diag) : cx_diag_(t_diag) {}

  /// Destructor
  ~ClangDiagnostic() { clang_disposeDiagnostic(cx_diag_); }

  /// Delete copy constructor and copy assignment
  ClangDiagnostic(const ClangDiagnostic &) = delete;
  ClangDiagnostic & operator=(const ClangDiagnostic &) = delete;

  /// Get underlying CXDiagnostic object
  auto get_raw() const { return cx_diag_; }

 private:
  /// Underlying CXDiagnostic object
  CXDiagnostic cx_diag_;
};

/// RAII wrapper around CXString
class ClangString {
 public:
  /// Constructor for clang string
  ClangString(const CXString & t_cx_string) : cx_string_(t_cx_string) {}

  /// Destructor
  ~ClangString() { clang_disposeString(cx_string_); }

  /// Delete copy constructor and copy assignment
  ClangString(const ClangString &) = delete;
  ClangString & operator=(const ClangString &) = delete;

  /// Get STL string
  auto stl_str(void) const { return std::string(clang_getCString(cx_string_)); }

  /// Get underlying CXString object
  auto get_raw() const { return cx_string_; }

 private:
  /// Underlying CXString object
  CXString cx_string_;
};

/// Convenience typedef for transforming a translation unit
typedef std::function<std::string(const CXTranslationUnit &)> Transformer;

/// Base class for a pass of the Clang compiler,
/// a function object that takes a string corresponding to a translation unit
/// and returns another string as another translation unit.
class CompilerPass {
 public:
  /// Construct CompilerPass with string contents
  CompilerPass(const std::string & str) { temp_file_.write(str); }

  /// Returned parsed output
  std::string output(void) const { return output_; };

 protected:
  /// Output as a string
  std::string output_ = "";

  /// TempFile to hold string to be parsed
  /// libclang can only parse strings, not files
  TempFile temp_file_ = TempFile("tmp", ".c");
};

/// Single pass over a translation unit.
class SinglePass  : public CompilerPass {
 public:
  /// Construct a SinglePass using a Transformer object
  SinglePass(const Transformer & t_transformer, const std::string & str);

  /// Destructor to free up libclang data structs
  ~SinglePass();

  /// Delete copy constructor and copy assignment
  SinglePass(const SinglePass &) = delete;
  SinglePass & operator=(const SinglePass &) = delete;

 private:
  /// Echo entire translation unit
  void echo_translation_unit(void);

  /// Diagnostics options to report warnings.
  const std::vector<const char *> diagnostics = {"-Werror", "-Wall"};

  /// libclang index object for parsing
  CXIndex index_;

  /// libclang reference to parsed translation unit
  CXTranslationUnit translation_unit_;
};

#endif  // SRC_COMPILER_PASS_H_
