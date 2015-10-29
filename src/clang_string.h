#ifndef CLANG_STRING_H_
#define CLANG_STRING_H_

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

#endif  // CLANG_STRING_H_
