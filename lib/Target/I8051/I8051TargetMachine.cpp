//===-- I8051TargetMachine.cpp - Define TargetMachine for I8051 -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "I8051TargetMachine.h"
//#include "I8051.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/PassManager.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

extern "C" void LLVMInitializeI8051Target() {
    // Register the target.
    RegisterTargetMachine<I8051TargetMachine> X(TheI8051Target);
}

I8051TargetMachine::I8051TargetMachine(const Target &T, StringRef TT,
                                     StringRef CPU, StringRef FS,
                                     const TargetOptions &Options,
                                     Reloc::Model RM, CodeModel::Model CM,
                                     CodeGenOpt::Level OL,
                                     bool is64bit)
: LLVMTargetMachine(T, TT, CPU, FS, Options, RM, CM, OL),
    DL("e-p:16:8:8-i8:8:8-i16:8:8-n8:16"),
    FrameLowering(*this), InstrInfo(*this), TSInfo(*this),
    Subtarget(TT, CPU, FS), TLInfo(*this) {
    initAsmInfo();
}

namespace {
/// I8051 Code Generator Pass Configuration Options.
    class I8051PassConfig : public TargetPassConfig {
    public:
        I8051PassConfig(I8051TargetMachine *TM, PassManagerBase &PM)
        : TargetPassConfig(TM, PM) {}

        I8051TargetMachine &getI8051TargetMachine() const {
            return getTM<I8051TargetMachine>();
        }

        bool addInstSelector() override;
    };  // end class I8051PassConfig
} // namespace

TargetPassConfig *I8051TargetMachine::createPassConfig(PassManagerBase &PM) {
    return new I8051PassConfig(this, PM);
}

bool I8051PassConfig::addInstSelector() {
    addPass(createI8051ISelDag(getI8051TargetMachine(), getOptLevel()));
    return false;
}
