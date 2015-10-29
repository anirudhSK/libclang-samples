#ifndef SRC_COMPILER_PASS_H_
#define SRC_COMPILER_PASS_H_

#include <functional>
#include <string>

#include "clang-c/Index.h"

#include "third_party/temp_file.hh"

#include "clang_string.h"
#include "clang_diagnostic.h"

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
