//===- I8051RegisterInfo.td - Describe the I8051 Register Info ----*- tblgen -*-==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Declaration that describes the I8051 register file
//===----------------------------------------------------------------------===//

class I8051Reg<string n, bits<16> Enc = 0, int Cost = 0>
  : Register<n> {
  let Namespace  = "I8051";
  let HWEncoding = Enc;
  let CostPerUse = Cost;
}

class I8051SubRegIndex<int size, int offset = 0> : SubRegIndex<size, offset> {
  let Namespace = "I8051";
}

def subreg_hi : I8051SubRegIndex<8, 8>;
def subreg_lo : I8051SubRegIndex<8, 0>;

class I8051RegWithSubRegs<string n, bits<16> Enc = 0, list<Register> subregs = [], int Cost = 0>
  : I8051Reg<n, Enc, Cost> {
  let SubRegs = subregs;
  let SubRegIndices = [subreg_hi, subreg_lo];
  let CoveredBySubRegs = 1;
}

class I8051Reg8Class<dag reglist>
  : RegisterClass<"I8051", [i8], 8, reglist> {
}

class I8051Reg16Class<dag reglist>
  : RegisterClass<"I8051", [i16], 8, reglist> {
}

//===----------------------------------------------------------------------===//
//  Registers
//===----------------------------------------------------------------------===//

// 8 bit registers
def A : I8051Reg<"a", 7>;
def B : I8051Reg<"b", 8>;
def R0 : I8051Reg<"r0", 0>;
def R1 : I8051Reg<"r1", 1>;
def R2 : I8051Reg<"r2", 2>;
def R3 : I8051Reg<"r3", 3>;
def R4 : I8051Reg<"r4", 4>;
def R5 : I8051Reg<"r5", 5>;
def R6 : I8051Reg<"r6", 6>;
def R7 : I8051Reg<"r7", 7>;
def SP : I8051Reg<"sp">;
def DPH : I8051Reg<"dph", 9>;
def DPL : I8051Reg<"dpl", 9>;


// 16 bit registers
// The Data Pointer (DPTR)
def DPTR : I8051RegWithSubRegs<"dptr", 0, [DPH, DPL]>;
def PC : I8051Reg<"pc">;

def GR8  : I8051Reg8Class<(add A, B, R0, R1, R2, R3, R4, R5, R6, R7, SP, DPH, DPL)>;
def GR16 : I8051Reg16Class<(add DPTR, PC)>;
