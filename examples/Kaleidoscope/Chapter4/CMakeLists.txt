set(LLVM_LINK_COMPONENTS
  Analysis
  Core
  ExecutionEngine
  InstCombine
  MC
  ScalarOpts
  Support
  nativecodegen
  )

add_llvm_example(Kaleidoscope-Ch4
  toy.cpp
  )
