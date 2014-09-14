//===-- 8051TargetMachine.cpp - Define TargetMachine for 8051 -----------===//
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

#include "8051TargetMachine.h"
//#include "8051.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/PassManager.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

extern "C" void LLVMInitialize8051Target() {
    // Register the target.
    RegisterTargetMachine<8051TargetMachine> X(The8051Target);
}

8051TargetMachine::8051TargetMachine(const Target &T, StringRef TT,
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
/// 8051 Code Generator Pass Configuration Options.
    class 8051PassConfig : public TargetPassConfig {
    public:
        8051PassConfig(8051TargetMachine *TM, PassManagerBase &PM)
        : TargetPassConfig(TM, PM) {}

        8051TargetMachine &get8051TargetMachine() const {
            return getTM<8051TargetMachine>();
        }

        bool addInstSelector() override;
    };  // end class 8051PassConfig
} // namespace

TargetPassConfig *8051TargetMachine::createPassConfig(PassManagerBase &PM) {
    return new 8051PassConfig(this, PM);
}

bool 8051PassConfig::addInstSelector() {
    addPass(create8051ISelDag(get8051TargetMachine(), getOptLevel()));
    return false;
}
