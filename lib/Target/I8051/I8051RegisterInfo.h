//===-- I8051RegisterInfo.h - I8051 Register Information Impl -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the I8051 implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef I8051REGISTERINFO_H
#define I8051REGISTERINFO_H

#define GET_REGINFO_HEADER
#include "I8051GenRegisterInfo.inc"

namespace llvm {
  class TargetInstrInfo;
  class I8051TargetMachine;

  class I8051RegisterInfo : public I8051GenRegisterInfo {
    I8051TargetMachine &TM;
    const TargetInstrInfo &TII;
  public:
    I8051RegisterInfo(I8051TargetMachine &tm, const TargetInstrInfo &tii);

    // Code Generation virtual methods...
    const uint16_t *getCalleeSavedRegs(const MachineFunction *MF = 0) const;
    const uint32_t *getCallPreservedMask(CallingConv::ID CallConv) const;

    BitVector getReservedRegs(const MachineFunction &MF) const;

    void eliminateFrameIndex(MachineBasicBlock::iterator I,
      int SPAdj, unsigned FIOperandNum, RegScavenger *RS = NULL) const;

    // Debug information queries
    unsigned getFrameRegister(const MachineFunction &MF) const;
  }; // end class I8051RegisterInfo
} // end namespace llvm

#endif
