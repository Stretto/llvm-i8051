##===- lib/Target/8051/Makefile ---------------------------*- Makefile -*-===##
#
#                     The LLVM Compiler Infrastructure
#
# This file is distributed under the University of Illinois Open Source
# License. See LICENSE.TXT for details.
#
##===----------------------------------------------------------------------===##

LEVEL = ../../..
LIBRARYNAME = LLVM8051CodeGen
TARGET = 8051

# Make sure that tblgen is run, first thing.
BUILT_SOURCES = 8051GenRegisterInfo.inc 8051GenInstrInfo.inc \
		8051GenAsmWriter.inc 8051GenAsmMatcher.inc \
		8051GenDAGISel.inc 8051GenDisassemblerTables.inc \
		8051GenSubtargetInfo.inc 8051GenCallingConv.inc \
		8051GenMCCodeEmitter.inc

DIRS = InstPrinter AsmParser Disassembler TargetInfo MCTargetDesc

include $(LEVEL)/Makefile.common
