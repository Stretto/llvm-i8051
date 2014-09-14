##===- lib/Target/I8051/Makefile ---------------------------*- Makefile -*-===##
#
#                     The LLVM Compiler Infrastructure
#
# This file is distributed under the University of Illinois Open Source
# License. See LICENSE.TXT for details.
#
##===----------------------------------------------------------------------===##

LEVEL = ../../..
LIBRARYNAME = LLVMI8051CodeGen
TARGET = I8051

# Make sure that tblgen is run, first thing.
BUILT_SOURCES = I8051GenRegisterInfo.inc I8051GenInstrInfo.inc \
		I8051GenAsmWriter.inc I8051GenAsmMatcher.inc \
		I8051GenDAGISel.inc I8051GenDisassemblerTables.inc \
		I8051GenSubtargetInfo.inc I8051GenCallingConv.inc \
		I8051GenMCCodeEmitter.inc

DIRS = InstPrinter AsmParser Disassembler TargetInfo MCTargetDesc

include $(LEVEL)/Makefile.common
