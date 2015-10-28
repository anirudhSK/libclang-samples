#include <cstdio>
#include <iostream>

#include <string>

#include "clang-c/Index.h"

#include "util.h"
#include "compiler_pass.h"

std::string dummy(const CXTranslationUnit & t __attribute__((unused))) { return ""; }

int main(int argc, const char **argv) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: " << argv[0] << " <source_file>" << std::endl;
      return EXIT_FAILURE;
    } else {
      const std::string source_file(argv[1]);
      SinglePass(dummy, file_to_str(source_file));
    }
  } catch (const std::exception & e) {
    std::cerr << "Caught exception in main " << std::endl << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
