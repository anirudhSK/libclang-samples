#ifndef SRC_COMPILER_PASS_H_
#define SRC_COMPILER_PASS_H_

#include <functional>
#include <string>

#include "clang-c/Index.h"

#include "third_party/temp_file.hh"

/// Convenience typedef for transforming a translation unit
typedef std::function<std::string(const CXTranslationUnit &)> Transformer;


/// Abstract base class for a pass of the Clang compiler,
/// a function object that takes a string corresponding to a translation unit
/// and returns another string as another translation unit.
class CompilerPass {
 public:
  /// Run the compiler pass on a string and return a new string
  virtual std::string operator()(const std::string &) = 0;

  /// Virtual destructor to shut up g++
  virtual ~CompilerPass() {};
};

/// Single pass over a translation unit.
class SinglePass  : public CompilerPass {
 public:
  /// Construct a SinglePass using a Transformer object
  SinglePass(const Transformer & t_transformer);

  /// Execute SinglePass object overriding function call operator
  std::string operator() (const std::string & string_to_parse) final override;

 private:
  /// TempFile to hold string to be parsed
  /// libclang can only parse strings, not files
  TempFile temp_file_;
};

#endif  // SRC_COMPILER_PASS_H_
