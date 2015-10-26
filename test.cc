#include "clang-c/Index.h"
int main(int argc, char* argv[]) {
  CXIndex Index = clang_createIndex(0, 0);
  clang_disposeIndex(Index);
}
