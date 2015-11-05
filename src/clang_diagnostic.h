#ifndef CLANG_DIAGNOSTIC_H_
#define CLANG_DIAGNOSTIC_H_

#include "clang-c/Index.h"

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

#endif  // CLANG_DIAGNOSTIC_H_
