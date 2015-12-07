# libclang-samples
[![Build Status](https://travis-ci.org/anirudhSK/libclang-samples.svg)](https://travis-ci.org/anirudhSK/libclang-samples)

Sample programs to use Clang's lowest-level stable C API (http://clang.llvm.org/doxygen/group__CINDEX.html)

Closing this for now.

Using libclang directly seems a little masochistic to be honest.
You need to reinvent data types for each AST node,
in essence redoing libtooling or the clang plugin interface on top of libclang.
That said, libclang is one of the better, more stable libraries I have found so far.

So, while it's tempting to start from scratch, I think going with a higher-level
C++ interface like libtooling is a better idea.

