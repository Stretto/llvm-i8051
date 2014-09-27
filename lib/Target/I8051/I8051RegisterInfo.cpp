//===-- I8051RegisterInfo.cpp - I8051 Register Information ----------------===//
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

#include "I8051RegisterInfo.h"
//#include "I8051.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/Target/TargetFrameLowering.h"
#include "llvm/Support/CommandLine.h"

#define GET_REGINFO_TARGET_DESC
#include "I8051GenRegisterInfo.inc"

using namespace llvm;

typedef enum {
    IX,
    IY
} FrameUseRegister;

static cl::opt<FrameUseRegister>
FrameRegister("i8051-frame-register",
              cl::desc("Frame register (IX by default)"),
              cl::init(IX),
              cl::values(
                  clEnumValN(IX, "ix", "IX register"),
                  clEnumValN(IY, "iy", "IY register"),
                  clEnumValEnd));

I8051RegisterInfo::I8051RegisterInfo(I8051TargetMachine &tm,
                                     const TargetInstrInfo &tii)
    : I8051GenRegisterInfo(I8051::PC), TM(tm), TII(tii)
{}

const uint16_t* I8051RegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const
{
    static const uint16_t CalleeSavedRegs[] = {
        I8051::BC, I8051::DE, I8051::IX, I8051::IY,
        0
    };
    return CalleeSavedRegs;
}

const uint32_t* I8051RegisterInfo::getCallPreservedMask(CallingConv::ID CallConv) const
{
    return CSR_16_RegMask;
}

BitVector I8051RegisterInfo::getReservedRegs(const MachineFunction &MF) const
{
    BitVector Reserved(getNumRegs());

    Reserved.set(I8051::PC);
    Reserved.set(I8051::SP);
    Reserved.set(I8051::FLAGS);
    Reserved.set(getFrameRegister(MF));

    return Reserved;
}

void I8051RegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator I,
                                            int SPAdj, unsigned FIOperandNum, RegScavenger *RS) const
{
    assert(SPAdj == 0 && "Not implemented yet!");

    unsigned i = 0;
    MachineInstr &MI = *I;
    MachineBasicBlock &MBB = *MI.getParent();
    MachineFunction &MF = *MBB.getParent();
    const TargetFrameLowering *TFI = MF.getTarget().getFrameLowering();

    while (!MI.getOperand(i).isFI())
    {
        i++;
        assert(i < MI.getNumOperands() && "Instr doesn't have FrameIndex operand!");
    }

    int FrameIndex = MI.getOperand(i).getIndex();
    uint64_t Offset = MF.getFrameInfo()->getObjectOffset(FrameIndex);
    Offset += 2; // Skip the saved PC
    Offset += MF.getFrameInfo()->getStackSize();
    Offset += MI.getOperand(i+1).getImm();

    if (TFI->hasFP(MF))
    {
        MI.getOperand(i).ChangeToRegister(getFrameRegister(MF), false);
        MI.getOperand(i+1).ChangeToImmediate(Offset);
    }
    else assert(0 && "Not implemented yet !");
}

unsigned I8051RegisterInfo::getFrameRegister(const MachineFunction &MF) const
{
    return (FrameRegister == IX) ? I8051::IX : I8051::IY;
}
