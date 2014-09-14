//===-- I8051TargetMachine.h - Define TargetMachine for I8051 ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the I8051 specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_I8051_I8051TARGETMACHINE_H
#define LLVM_LIB_TARGET_I8051_I8051TARGETMACHINE_H

//#include "I8051InstrInfo.h"
//#include "I8051Subtarget.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

    class Module;

    class I8051TargetMachine : public LLVMTargetMachine {
        const DataLayout DataLayout;       // Calculates type size & alignment
        I8051Subtarget Subtarget;
        I8051InstrInfo InstrInfo;
        TargetFrameInfo FrameInfo;

    public:
        I8051TargetMachine(const Module &M, const std::string &FS);

        virtual const I8051InstrInfo *getInstrInfo() const {return &InstrInfo; }
        virtual const TargetFrameInfo *getFrameInfo() const {return &FrameInfo; }
        virtual const TargetSubtarget *getSubtargetImpl() const{return &Subtarget; }
        virtual const TargetRegisterInfo *getRegisterInfo() const {
            return &InstrInfo.getRegisterInfo();
        }
        virtual const DataLayout *getDataLayout() const { return &DataLayout; }
        virtual const I8051FrameLowering *getFrameLowering() const {
            return &FrameLowering;
        }

        static unsigned getModuleMatchQuality(const Module &M);

        // Pass Pipeline Configuration
        virtual bool addInstSelector(PassManagerBase &PM, bool Fast);
        virtual bool addPreEmitPass(PassManagerBase &PM, bool Fast);
    };

} // end namespace llvm
