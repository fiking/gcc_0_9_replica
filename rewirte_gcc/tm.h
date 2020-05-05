/* Definitions of target machine for GNU compiler.  Sun 68000/68020 version.
   Copyright (C) 1987 Free Software Foundation, Inc.

This file is part of GNU CC.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.  No author or distributor
accepts responsibility to anyone for the consequences of using it
or for whether it serves any particular purpose or works at all,
unless he says so in writing.  Refer to the GNU CC General Public
License for full details.

Everyone is granted permission to copy, modify and redistribute
GNU CC, but only under the conditions described in the
GNU CC General Public License.   A copy of this license is
supposed to have been given to you along with GNU CC so you
can know your rights and responsibilities.  It should be in a
file named COPYING.  Among other things, the copyright notice
and this notice must be preserved on all copies.  */


/* Names to predefine in the preprocessor for this target machine.  */

#define CPP_PREDEFINES "-Dmc68000 -Dsun"

/* Run-time compilation parameters selecting different hardware subsets.  */

extern int target_flags;

extern int reg_mentioned_p ();

/* Macros used in the machine description to test the flags.  */

#define TARGET_68020 (target_flags & 1)
#define TARGET_68881 (target_flags & 2)
#define TARGET_BITFIELD (target_flags & 4)
#define TARGET_DEFER_POP (target_flags & 040)

/* Macro to define tables used to set the flags.
   This is a list in braces of pairs in braces,
   each pair being { "NAME", VALUE }
   where VALUE is the bits to set or minus the bits to clear.
   An empty string NAME is used to identify the default VALUE.  */

#define TARGET_SWITCHES  \
  { { "68020", 5},				\
    { "68881", 2},				\
    { "bitfield", 4},				\
    { "68000", -5},				\
    { "soft-float", -2},			\
    { "nobitfield", -4},			\
    { "defer-pop", 040},			\
    { "", 067}}

/* target machine storage layout */

/* Define this if most significant bit is lowest numbered
   in instructions that operate on numbered bit-fields.
   This is true for 68020 insns such as bfins and bfexts.
   We make it true always by avoiding using the single-bit insns
   except in special cases with constant bit numbers.  */
#define BITS_BIG_ENDIAN

/* Define this if most significant byte of a word is the lowest numbered.  */
/* That is true on the 68000.  */
#define BYTES_BIG_ENDIAN

/* Define this if most significant word of a multiword number is numbered.  */
/* For 68000 we can decide arbitrarily
   since there are no machine instructions for them.  */
/* #define WORDS_BIG_ENDIAN */

/* number of bits in an addressible storage unit */
#define BITS_PER_UNIT 8

/* Width in bits of a "word", which is the contents of a machine register.
   Note that this is not necessarily the width of data type `int';
   if using 16-bit ints on a 68000, this would still be 32.
   But on a machine with 16-bit registers, this would be 16.  */
#define BITS_PER_WORD 32

/* Width of a word, in units (bytes).  */
#define UNITS_PER_WORD 4

/* Width in bits of a pointer.
   See also the macro `Pmode' defined below.  */
#define POINTER_SIZE 32

/* Allocation boundary (in *bits*) for storing pointers in memory.  */
#define POINTER_BOUNDARY 16

/* Allocation boundary (in *bits*) for storing arguments in argument list.  */
#define PARM_BOUNDARY 32

/* Allocation boundary (in *bits*) for the code of a function.  */
#define FUNCTION_BOUNDARY 16

/* There is no point aligning anything to a rounder boundary than this.  */
#define BIGGEST_ALIGNMENT 16

/* Define this if move instructions will actually fail to work
   when given unaligned data.  */
#define STRICT_ALIGNMENT

/* Standard register usage.  */

/* Number of actual hardware registers.
   The hardware registers are assigned numbers for the compiler
   from 0 to just below FIRST_PSEUDO_REGISTER.
   All registers that the compiler knows about must be given numbers,
   even those that are not normally considered general registers.
   For the 68000, we give the data registers numbers 0-7,
   the address registers numbers 010-017,
   and the 68881 floating point registers numbers 020-027.  */
#define FIRST_PSEUDO_REGISTER 24

/* 1 for registers that have pervasive standard uses
   and are not available for the register allocator.
   On the 68000, these are the stack pointer and frame pointer.  */
#define FIXED_REGISTERS  \
 {0, 0, 0, 0, 0, 0, 0, 0, \
  0, 0, 0, 0, 0, 0, 1, 1, \
  0, 0, 0, 0, 0, 0, 0, 0}

/* 1 for registers not available across function calls.
   These must include the FIXED_REGISTERS and also any
   registers that can be used without being saved.
   The latter must include the registers where values are returned
   and the register where structure-value addresses are passed.
   Aside from that, you can include as many other registers as you like.  */
#define CALL_USED_REGISTERS \
 {1, 1, 0, 0, 0, 0, 0, 0, \
  1, 1, 0, 0, 0, 0, 1, 1, \
  1, 1, 0, 0, 0, 0, 0, 0}

/* Return number of consecutive hard regs needed starting at reg REGNO
   to hold something of mode MODE.
   This is ordinarily the length in words of a value of mode MODE
   but can be less for certain modes in special long registers.

   On the 68000, ordinary registers hold 32 bits worth;
   for the 68881 registers, a single register is always enough for
   anything that can be stored in them at all.  */
#define HARD_REGNO_NREGS(REGNO, MODE)   \
  ((REGNO) >= 16 ? 1				\
   : ((GET_MODE_SIZE (MODE) + UNITS_PER_WORD - 1) / UNITS_PER_WORD))

/* Value is 1 if hard register REGNO can hold a value of machine-mode MODE.
   On the 68000, the cpu registers can hold any mode but the 68881 registers
   can hold only SFmode or DFmode.  And the 68881 registers can't hold anything
   if 68881 use is disabled.  */
#define HARD_REGNO_MODE_OK(REGNO, MODE) \
  ((REGNO) < 16 || (TARGET_68881 && ((MODE) == SFmode || (MODE) == DFmode)))

/* Value is 1 if it is a good idea to tie two pseudo registers
   when one has mode MODE1 and one has mode MODE2.
   If HARD_REGNO_MODE_OK could produce different values for MODE1 and MODE2,
   for any hard reg, then this must be 0 for correct output.  */
#define MODES_TIEABLE_P(MODE1, MODE2) \
  (((MODE1) == SFmode || (MODE1) == DFmode) \
   == ((MODE2) == SFmode || (MODE2) == DFmode))

/* Specify the registers used for certain standard purposes.
   The values of these macros are register numbers.  */

/* m68000 pc isn't overloaded on a register.  */
/* #define PC_REGNUM  */

/* Register to use for pushing function arguments.  */
#define STACK_POINTER_REGNUM 15

/* Base register for access to local variables of the function.  */
#define FRAME_POINTER_REGNUM 14

/* Base register for access to arguments of the function.  */
#define ARG_POINTER_REGNUM 14

/* Register in which static-chain is passed to a function.  */
#define STATIC_CHAIN_REGNUM 8

/* Register in which function's value is returned.
   Actually, multiple registers starting with this one may be used
   depending on the machine mode of the value.  */
#define FUNCTION_VALUE_REGNUM 0

/* Register in which address to store a structure value
   is passed to a function.  */
#define STRUCT_VALUE_REGNUM 9

/* Define the classes of registers for register constraints in the
   machine description.  Also define ranges of constants.

   One of the classes must always be named ALL_REGS and include all hard regs.
   If there is more than one class, another class must be named NO_REGS
   and contain no registers.

   The name GENERAL_REGS must be the name of a class (or an alias for
   another name such as ALL_REGS).  This is the class of registers
   that is allowed by "g" or "r" in a register constraint.
   Also, registers outside this class are allocated only when
   instructions express preferences for them.

   The classes must be numbered in nondecreasing order; that is,
   a larger-numbered class must never be contained completely
   in a smaller-numbered class.

   For any two classes, it is very desirable that there be another
   class that represents their union.  */
   
/* The 68000 has three kinds of registers, so eight classes would be
   a complete set.  One of them is not needed.  */

enum reg_class { NO_REGS, DATA_REGS, ADDR_REGS, GENERAL_REGS, FP_REGS, FP_OR_DATA_REGS, ALL_REGS, LIM_REG_CLASSES };

#define N_REG_CLASSES (int) LIM_REG_CLASSES

/* Give names of register classes as strings for dump file.   */

#define REG_CLASS_NAMES \
 {"NO_REGS", "DATA_REGS", "ADDR_REGS", "GENERAL_REGS",  \
  "FP_REGS", "FP_OR_DATA_REGS", "ALL_REGS" }

/* Define which registers fit in which classes.
   This is an initializer for a vector of HARD_REG_SET
   of length N_REG_CLASSES.  */

#define REG_CLASS_CONTENTS {0, 0xff, 0xff00, 0xffff, 0xff0000, 0xff00ff, 0xffffff}

/* The same information, inverted:
   Return the class number of the smallest class containing
   reg number REGNO.  This could be a conditional expression
   or could index an array.  */

#define REGNO_REG_CLASS(REGNO) \
 ((REGNO) >= 16 ? FP_REGS : (REGNO) < 8 ? DATA_REGS : ADDR_REGS)

/* Define a table that lets us find quickly all the reg classes
   containing a given one.  This is the initializer for an
   N_REG_CLASSES x N_REG_CLASSES array of reg class codes.
   Row N is a sequence containing all the class codes for
   classes that contain all the regs in class N.  Each row
   contains no duplicates, and is terminated by LIM_REG_CLASSES.  */

/* We give just a dummy for the first element, which is for NO_REGS.  */
#define REG_CLASS_SUPERCLASSES \
 {{LIM_REG_CLASSES}, \
  {GENERAL_REGS, FP_OR_DATA_REGS, ALL_REGS, LIM_REG_CLASSES}, \
  {GENERAL_REGS, ALL_REGS, LIM_REG_CLASSES}, \
  {ALL_REGS, LIM_REG_CLASSES}, \
  {FP_OR_DATA_REGS, ALL_REGS, LIM_REG_CLASSES}, \
  {ALL_REGS, LIM_REG_CLASSES}, \
  {LIM_REG_CLASSES}}

/* The inverse relationship:
   for each class, a list of all reg classes contained in it.  */
#define REG_CLASS_SUBCLASSES \
 {{LIM_REG_CLASSES}, \
  {LIM_REG_CLASSES}, \
  {LIM_REG_CLASSES}, \
  {DATA_REGS, ADDR_REGS, LIM_REG_CLASSES}, \
  {LIM_REG_CLASSES}, \
  {DATA_REGS, FP_REGS, LIM_REG_CLASSES}, \
  {DATA_REGS, ADDR_REGS, FP_REGS, GENERAL_REGS, FP_OR_DATA_REGS, LIM_REG_CLASSES}}

/* Define a table that lets us find quickly the class
   for the subunion of any two classes.

   We say "subunion" because the result need not be exactly
   the union; it may instead be a subclass of the union
   (though the closer to the union, the better).
   But if it contains anything beyond union of the two classes,
   you will lose!

   This is an initializer for an N_REG_CLASSES x N_REG_CLASSES
   array of reg class codes.  The subunion of classes C1 and C2
   is just element [C1, C2].  */

#define REG_CLASS_SUBUNION  \
{{NO_REGS, DATA_REGS, ADDR_REGS, GENERAL_REGS, FP_REGS, FP_OR_DATA_REGS, ALL_REGS}, \
 {DATA_REGS, DATA_REGS, GENERAL_REGS, GENERAL_REGS, FP_OR_DATA_REGS, FP_OR_DATA_REGS, ALL_REGS}, \
 {ADDR_REGS, GENERAL_REGS, ADDR_REGS, GENERAL_REGS, ADDR_REGS, ADDR_REGS, ALL_REGS}, \
 {GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, GENERAL_REGS, ALL_REGS, ALL_REGS, ALL_REGS},\
 {FP_REGS, FP_OR_DATA_REGS, FP_REGS, FP_OR_DATA_REGS, FP_REGS, FP_OR_DATA_REGS, ALL_REGS}, \
 {FP_OR_DATA_REGS, FP_OR_DATA_REGS, FP_OR_DATA_REGS, ALL_REGS, FP_OR_DATA_REGS, FP_OR_DATA_REGS, ALL_REGS}, \
 {ALL_REGS, ALL_REGS, ALL_REGS, ALL_REGS, ALL_REGS, ALL_REGS, ALL_REGS}}

/* The class value for index registers, and the one for base regs.  */

#define INDEX_REG_CLASS GENERAL_REGS
#define BASE_REG_CLASS ADDR_REGS

/* Get reg_class from a letter such as appears in the machine description.  */

#define REG_CLASS_FROM_LETTER(C) \
  ((C) == 'a' ? ADDR_REGS : ((C) == 'd' ? DATA_REGS : ((C) == 'f' ? FP_REGS : NO_REGS)))

/* The letters I, J, K, L and M in a register constraint string
   can be used to stand for particular ranges of immediate operands.
   This macro defines what the ranges are.
   C is the letter, and VALUE is a constant value.
   Return 1 if VALUE is in the range specified by C.

   For the 68000, `I' is used for the range 1 to 8
   allowed as immediate shift counts and in addq.
   `J' is used for the range of signed numbers that fit in 16 bits.
   `K' is for numbers that moveq can't handle.
   `L' is for range -8 to -1, range of values that can be added with subq.  */

#define CONST_OK_FOR_LETTER_P(VALUE, C)  \
  ((C) == 'I' ? (VALUE) > 0 && (VALUE) <= 8 :    \
   (C) == 'J' ? (VALUE) >= -0x8000 && (VALUE) <= 0x7FFF :	\
   (C) == 'K' ? (VALUE) < -0x80 || (VALUE) >= 0x80 :	\
   (C) == 'L' ? (VALUE) < 0 && (VALUE) >= -8 : 0)

/* Similar, but for floating constants, and defining letters G and H.
   Here VALUE is the CONST_DOUBLE rtx itself.  */

#define CONST_DOUBLE_OK_FOR_LETTER_P(VALUE, C)  \
  ((C) == 'G' ? ! (TARGET_68881 && standard_68881_constant_p (VALUE)) : 1)

/* Given an rtx X being reloaded into a reg required to be
   in class CLASS, return the class of reg to actually use.
   In general this is just CLASS; but on some machines
   in some cases it is preferable to use a more restrictive class.
   On the 68000 series, use a data reg if possible when the
   value is a constant in the range where moveq could be used.  */
#define PREFERRED_RELOAD_CLASS(X,CLASS)  \
  ((GET_CODE (X) == CONST_INT				\
    && (unsigned) (INTVAL (X) + 0x80) < 0x100	\
    && (CLASS) != ADDR_REGS)				\
   ? DATA_REGS : (CLASS))

/* Stack layout; function entry, exit and calling.  */

/* Define this if pushing a word on the stack
   makes the stack pointer a smaller address.  */
#define STACK_GROWS_DOWNWARD

/* Define this if the nominal address of the stack frame
   is at the high-address end of the local variables;
   that is, each additional local variable allocated
   goes at a more negative offset in the frame.  */
#define FRAME_GROWS_DOWNWARD

/* Offset within stack frame to start allocating local variables at.
   If FRAME_GROWS_DOWNWARD, this is the offset to the END of the
   first local allocated.  Otherwise, it is the offset to the BEGINNING
   of the first local allocated.  */
#define STARTING_FRAME_OFFSET 0

/* If we generate an insn to push BYTES bytes,
   this says how many the stack pointer really advances by.
   On the 68000, sp@- in a byte insn really pushes a word.  */
#define PUSH_ROUNDING(BYTES) (((BYTES) + 1) & ~1)

/* Offset of first parameter from the argument pointer register value.  */
#define FIRST_PARM_OFFSET 8

/* Define if returning from a function call automatically
   pops the arguments described by the number-of-args field in the call.  */

/* #define RETURN_POPS_ARGS   On the 68000, the caller must pop them.  */

/* This macro generates the assembly code for function entry.
   FILE is a stdio stream to output the code to.
   SIZE is an int: how many units of temporary storage to allocate.
   Refer to the array `regs_ever_live' to determine which registers
   to save; `regs_ever_live[I]' is nonzero if register number I
   is ever used in the function.  This macro is responsible for
   knowing which registers should not be saved even if used.  */

#define FUNCTION_PROLOGUE(FILE, SIZE)     \
{ register int regno;						\
  register int mask = 0;					\
  static char dont_save_regs[] = CALL_USED_REGISTERS;		\
  static char *reg_names[] = REGISTER_NAMES;			\
  fprintf (FILE, "\tlink a6,#%d\n", (SIZE));			\
  for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)	\
    if (regs_ever_live[regno] && ! dont_save_regs[regno])	\
       mask |= 1 << (23 - regno);				\
  if (mask & 0xff)						\
    fprintf (FILE, "\tfmovem #0x%x,sp@-\n", mask & 0xff);       \
  mask >>= 8;							\
  if (exact_log2 (mask) >= 0)					\
    fprintf (FILE, "\tmovl %s,sp@-\n", reg_names[15 - exact_log2 (mask)]);  \
  else if (mask) fprintf (FILE, "\tmoveml #0x%x,sp@-\n", mask); }

/* This macro generates the assembly code for function exit,
   on machines that need it.  If FUNCTION_EPILOGUE is not defined
   then individual return instructions are generated for each
   return statement.  Args are same as for FUNCTION_PROLOGUE.

   The function epilogue should not depend on the current stack pointer!
   It should use the frame pointer only.  This is mandatory because
   of alloca; we also take advantage of it to omit stack adjustments
   before returning.  */

#define FUNCTION_EPILOGUE(FILE, SIZE) \
{ register int regno;						\
  register int mask;						\
  register int nregs;						\
  int offset;							\
  static char dont_save_regs[] = CALL_USED_REGISTERS;		\
  static char *reg_names[] = REGISTER_NAMES;			\
  nregs = 0;  mask = 0;						\
  for (regno = 16; regno < FIRST_PSEUDO_REGISTER; regno++)	\
    if (regs_ever_live[regno] && ! dont_save_regs[regno])	\
      { nregs++; mask |= 1 << (regno - 16); }			\
  offset = nregs * 12;						\
  if (mask)							\
    fprintf (FILE, "\tfmovem a6@(-%d),#0x%x\n",			\
	     offset - (SIZE), mask);				\
  nregs = 0;  mask = 0;						\
  for (regno = 0; regno < 16; regno++)				\
    if (regs_ever_live[regno] && ! dont_save_regs[regno])	\
      { nregs++; mask |= 1 << regno; }				\
  offset += nregs * 4;						\
  if (exact_log2 (mask) >= 0)					\
    fprintf (FILE, "\tmovl a6@(-%d),%s\n",			\
             offset - (SIZE), reg_names[exact_log2 (mask)]);	\
  else if (mask)						\
    fprintf (FILE, "\tmoveml a6@(-%d),#0x%x\n",			\
	     offset - (SIZE), mask);				\
  fprintf (FILE, "\tunlk a6\n\trts\n"); }

/* Addressing modes, and classification of registers for them.  */

#define HAVE_POST_INCREMENT
/* #define HAVE_POST_DECREMENT */

#define HAVE_PRE_DECREMENT
/* #define HAVE_PRE_INCREMENT */

/* These assume that REGNO is a hard or pseudo reg number.
   They give nonzero only if REGNO is a hard reg of the suitable class
   or a pseudo reg currently allocated to a suitable hard reg.
   These definitions are NOT overridden anywhere.  */
#define REGNO_OK_FOR_INDEX_P(REGNO) \
((REGNO) < 16 || (unsigned) reg_renumber[REGNO] < 16)
#define REGNO_OK_FOR_BASE_P(REGNO) \
(((REGNO) ^ 010) < 8 || ((unsigned) reg_renumber[REGNO] ^ 010) < 8)
#define REGNO_OK_FOR_DATA_P(REGNO) \
((REGNO) < 8 || (unsigned) reg_renumber[REGNO] < 8)
#define REGNO_OK_FOR_FP_P(REGNO) \
(((REGNO) ^ 020) < 8 || ((unsigned) reg_renumber[REGNO] ^ 020) < 8)

/* GO_IF_LEGITIMATE_ADDRESS recognizes an RTL expression
   that is a valid memory address for an instruction.
   The MODE argument is the machine mode for the MEM expression
   that wants to use this address.

   The other macros defined here are used only in GO_IF_LEGITIMATE_ADDRESS,
   except for CONSTANT_ADDRESS_P which is actually machine-independent.  */

#define MAX_REGS_PER_ADDRESS 2

/* The macros REG_OK_FOR..._P assume that the arg is a REG rtx
   and check its validity for a certain class.
   We have two alternate definitions for each of them.
   The usual definition accepts all pseudo regs; the other rejects them all.
   The symbol REG_OK_STRICT causes the latter definition to be used.

   Most source files want to accept pseudo regs in the hope that
   they will get allocated to the class that the insn wants them to be in.
   Some source files that are used after register allocation
   need to be strict.  */

#ifndef REG_OK_STRICT

/* Nonzero if X is a hard reg that can be used as an index or if
   it is a pseudo reg.  */
#define REG_OK_FOR_INDEX_P(X) ((REGNO (X) ^ 020) >= 8)
/* Nonzero if X is a hard reg that can be used as a base reg
   of if it is a pseudo reg.  */
#define REG_OK_FOR_BASE_P(X) ((REGNO (X) & ~027) != 0)
/* Nonzero if X is a data reg or a pseudo reg.  */
#define REG_OK_FOR_DATA_P(X) ((unsigned) (REGNO (X) - 8) >= 16)
/* Nonzero if X is a floating point reg or a pseudo reg.  */
#define REG_OK_FOR_FP_P(X) (REGNO (X) >= 16)

#else

/* Nonzero if X is a hard reg that can be used as an index.  */
#define REG_OK_FOR_INDEX_P(X) REGNO_OK_FOR_INDEX_P (REGNO (X))
/* Nonzero if X is a hard reg that can be used as a base reg.  */
#define REG_OK_FOR_BASE_P(X) REGNO_OK_FOR_BASE_P (REGNO (X))
/* Nonzero if X is a data reg.  */
#define REG_OK_FOR_DATA_P(X) REGNO_OK_FOR_DATA_P (REGNO (X))
/* Nonzero if X is a floating point reg.  */
#define REG_OK_FOR_FP_P(X) REGNO_OK_FOR_FP_P (REGNO (X))

#endif

#define REG_OK_FOR_CLASS_P(X, C)  \
 (((C) == 'd' && REG_OK_FOR_DATA_P(X))		\
  || (C) == 'a' && REG_OK_FOR_BASE_P(X)		\
  || (C) == 'f' && REG_OK_FOR_FP_P(X))

#define REGNO_OK_FOR_CLASS_P(X, C)  \
 (((C) == 'd' && REGNO_OK_FOR_DATA_P(X))	\
  || (C) == 'a' && REGNO_OK_FOR_BASE_P(X)	\
  || (C) == 'f' && REGNO_OK_FOR_FP_P(X))

#define CONSTANT_ADDRESS_P(X)   \
  (GET_CODE (X) == LABEL_REF || GET_CODE (X) == SYMBOL_REF		\
   || GET_CODE (X) == CONST_INT						\
   || GET_CODE (X) == CONST)

#define REG_P(X)	\
  (GET_CODE (X) == REG)

#define DATA_REG_P(X)	\
  (GET_CODE (X) == REG && REGNO_OK_FOR_DATA_P (REGNO (X)))

#define FP_REG_P(X)	\
  (GET_CODE (X) == REG && REGNO_OK_FOR_FP_P (REGNO (X)))

#define ADDRESS_REG_P(X)	\
  (GET_CODE (X) == REG && REGNO_OK_FOR_BASE_P (REGNO (X)))

#define INDIRECTABLE_1_ADDRESS_P(X)  \
  (CONSTANT_ADDRESS_P (X)						\
   || (GET_CODE (X) == REG && REG_OK_FOR_BASE_P (X))			\
   || ((GET_CODE (X) == PRE_DEC || GET_CODE (X) == POST_INC)		\
       && REG_P (XEXP (X, 0))						\
       && REG_OK_FOR_BASE_P (XEXP (X, 0)))				\
   || (GET_CODE (X) == PLUS						\
       && REG_P (XEXP (X, 0)) && REG_OK_FOR_BASE_P (XEXP (X, 0))	\
       && GET_CODE (XEXP (X, 1)) == CONST_INT				\
       && ((unsigned) INTVAL (XEXP (X, 1)) + 0x8000) < 0x10000))

#if 0
/* This should replace the last two lines
   except that Sun's assembler does not seem to handle such operands.  */
       && (TARGET_68020 ? CONSTANT_ADDRESS_P (XEXP (X, 1))		\
	   : (GET_CODE (XEXP (X, 1)) == CONST_INT			\
	      && ((unsigned) INTVAL (XEXP (X, 1)) + 0x8000) < 0x10000))))
#endif


#define GO_IF_NONINDEXED_ADDRESS(X, ADDR)  \
{ if (INDIRECTABLE_1_ADDRESS_P (X)) goto ADDR; }

#define GO_IF_INDEXABLE_BASE(X, ADDR)	\
{ if (GET_CODE (X) == LABEL_REF) goto ADDR;				\
  if (GET_CODE (X) == REG && REG_OK_FOR_BASE_P (X)) goto ADDR; }

#define GO_IF_INDEXING(X, ADDR)	\
{ if (GET_CODE (X) == PLUS && LEGITIMATE_INDEX_P (XEXP (X, 0)))		\
    { GO_IF_INDEXABLE_BASE (XEXP (X, 1), ADDR); }			\
  if (GET_CODE (X) == PLUS && LEGITIMATE_INDEX_P (XEXP (X, 1)))		\
    { GO_IF_INDEXABLE_BASE (XEXP (X, 0), ADDR); } }

#define GO_IF_INDEXED_ADDRESS(X, ADDR)	 \
{ GO_IF_INDEXING (X, ADDR);						\
  if (GET_CODE (X) == PLUS)						\
    { if (GET_CODE (XEXP (X, 1)) == CONST_INT				\
	  && (unsigned) INTVAL (XEXP (X, 1)) + 0x80 < 0x100)		\
	GO_IF_INDEXING (XEXP (X, 0), ADDR);				\
      if (GET_CODE (XEXP (X, 0)) == CONST_INT				\
	  && (unsigned) INTVAL (XEXP (X, 0)) + 0x80 < 0x100)		\
	GO_IF_INDEXING (XEXP (X, 1), ADDR); } }


#if 0
/* Note we allow a constant address here if it is a LABEL_REF.
   That is not strictly correct, since the CODE_LABEL has to be less than
   2**7 bytes away from this insn.  But that is true in the only cases
   that matter, which occur in switch statements.  */

#define GO_IF_INDEXABLE_ADDRESS(X, ADDR)   \
{ if (GET_CODE (X) == LABEL_REF) goto ADDR;				\
  if (GET_CODE (X) == REG && REG_OK_FOR_BASE_P (X)) goto ADDR;		\
  if (GET_CODE (X) == PLUS &&						\
      ((REG_P (XEXP (X, 0)) && REG_OK_FOR_BASE_P (XEXP (X, 0))		\
	&& GET_CODE (XEXP (X, 1)) == CONST_INT				\
	&& (unsigned) INTVAL (XEXP (X, 1)) + 0x80 < 0x100)		\
       ||								\
       (REG_P (XEXP (X, 1)) && REG_OK_FOR_BASE_P (XEXP (X, 1))		\
	&& GET_CODE (XEXP (X, 0)) == CONST_INT				\
	&& (unsigned) INTVAL (XEXP (X, 0)) + 0x80 < 0x100)))		\
     goto ADDR; }


#define GO_IF_INDEXABLE_ADDRESS(X, ADDR)   \
{ if (GET_CODE (X) == LABEL_REF) goto ADDR;				\
  if (GET_CODE (X) == REG && REG_OK_FOR_BASE_P (X)) goto ADDR;		\
  if (GET_CODE (X) == PLUS &&						\
      ((REG_P (XEXP (X, 0)) && REG_OK_FOR_BASE_P (XEXP (X, 0))		\
	&& (TARGET_68020 ? CONSTANT_ADDRESS_P (XEXP (X, 1))		\
	    : (GET_CODE (XEXP (X, 1)) == CONST_INT			\
	       && (unsigned) INTVAL (XEXP (X, 1)) + 0x80 < 0x100)))	\
       ||								\
       (REG_P (XEXP (X, 1)) && REG_OK_FOR_BASE_P (XEXP (X, 1))		\
	&& (TARGET_68020 ? CONSTANT_ADDRESS_P (XEXP (X, 0))		\
	    : (GET_CODE (XEXP (X, 0)) == CONST_INT			\
	       && (unsigned) INTVAL (XEXP (X, 0)) + 0x80 < 0x100)))))	\
     goto ADDR; }
#endif

#define LEGITIMATE_INDEX_REG_P(X)   \
  ((GET_CODE (X) == REG && REG_OK_FOR_INDEX_P (X))	\
   || (GET_CODE (X) == SIGN_EXTEND			\
       && GET_CODE (XEXP (X, 0)) == REG			\
       && GET_MODE (XEXP (X, 0)) == HImode		\
       && REG_OK_FOR_INDEX_P (XEXP (X, 0))))

#define LEGITIMATE_INDEX_P(X)   \
   (LEGITIMATE_INDEX_REG_P (X)				\
    || (TARGET_68020 && GET_CODE (X) == MULT		\
	&& LEGITIMATE_INDEX_REG_P (XEXP (X, 0))		\
	&& GET_CODE (XEXP (X, 1)) == CONST_INT		\
	&& (INTVAL (XEXP (X, 1)) == 2			\
	    || INTVAL (XEXP (X, 1)) == 4		\
	    || INTVAL (XEXP (X, 1)) == 8)))

#define GO_IF_LEGITIMATE_ADDRESS(MODE, X, ADDR)  \
{ GO_IF_NONINDEXED_ADDRESS (X, ADDR);			\
  GO_IF_INDEXED_ADDRESS (X, ADDR); }

#if 0
  if (GET_CODE (X) == PLUS && LEGITIMATE_INDEX_P (XEXP (X, 0)))		\
    { GO_IF_INDEXABLE_ADDRESS (XEXP (X, 1), ADDR); }			\
  if (GET_CODE (X) == PLUS && LEGITIMATE_INDEX_P (XEXP (X, 1)))		\
    { GO_IF_INDEXABLE_ADDRESS (XEXP (X, 0), ADDR); } }
#endif

/* Try machine-dependent ways of modifying an illegitimate address
   to be legitimate.  If we find one, return the new, valid address.
   This macro is used in only one place: `memory_address' in explow.c.

   OLDX is the address as it was before break_out_memory_refs was called.
   In some cases it is useful to look at this to decide what needs to be done.

   MODE and WIN are passed so that this macro can use
   GO_IF_LEGITIMATE_ADDRESS.

   It is always safe for this macro to do nothing.  It exists to recognize
   opportunities to optimize the output.

   For the 68000, we handle X+REG by loading X into a register R and
   using R+REG.  R will go in an address reg and indexing will be used.
   However, if REG is a broken-out memory address or multiplication,
   nothing needs to be done because REG can certainly go in an address reg.  */

#define LEGITIMIZE_ADDRESS(X,OLDX,MODE,WIN)   \
{ register int ch = (X) != (OLDX);					\
  if (GET_CODE (X) == PLUS)						\
    { if (GET_CODE (XEXP (X, 0)) == MULT)				\
	ch = 1, XEXP (X, 0) = force_operand (XEXP (X, 0), 0);		\
      if (GET_CODE (XEXP (X, 1)) == MULT)				\
	ch = 1, XEXP (X, 1) = force_operand (XEXP (X, 1), 0);		\
      if (ch && GET_CODE (XEXP (X, 1)) == REG				\
	  && GET_CODE (XEXP (X, 0)) == REG)				\
	return X;							\
      if (ch) { GO_IF_LEGITIMATE_ADDRESS (MODE, X, WIN); }		\
      if (GET_CODE (XEXP (X, 0)) == REG					\
	       || (GET_CODE (XEXP (X, 0)) == SIGN_EXTEND		\
		   && GET_CODE (XEXP (XEXP (X, 0), 0)) == REG		\
		   && GET_MODE (XEXP (XEXP (X, 0), 0)) == HImode))	\
	{ register rtx temp = gen_reg_rtx (Pmode);			\
	  register rtx val = force_operand (XEXP (X, 1), temp);		\
	  if (val != temp) emit_move_insn (temp, val, 0);		\
	  XEXP (X, 1) = temp;						\
	  return X; }							\
      else if (GET_CODE (XEXP (X, 1)) == REG				\
	       || (GET_CODE (XEXP (X, 1)) == SIGN_EXTEND		\
		   && GET_CODE (XEXP (XEXP (X, 1), 0)) == REG		\
		   && GET_MODE (XEXP (XEXP (X, 1), 0)) == HImode))	\
	{ register rtx temp = gen_reg_rtx (Pmode);			\
	  register rtx val = force_operand (XEXP (X, 0), temp);		\
	  if (val != temp) emit_move_insn (temp, val, 0);		\
	  XEXP (X, 0) = temp;						\
	  return X; }}}

/* Specify the machine mode that this machine uses
   for the index in the tablejump instruction.  */
#define CASE_VECTOR_MODE HImode

/* Define this if the tablejump instruction expects the table
   to contain offsets from the address of the table.
   Do not define this if the table should contain absolute addresses.  */
#define CASE_VECTOR_PC_RELATIVE

/* Specify the tree operation to be used to convert reals to integers.  */
#define IMPLICIT_FIX_EXPR FIX_ROUND_EXPR

/* This is the kind of divide that is easiest to do in the general case.  */
#define EASY_DIV_EXPR TRUNC_DIV_EXPR

/* Max number of bytes we can move from memory to memory
   in one reasonably fast instruction.  */
#define MOVE_MAX 4

/* Define this if zero-extension is slow (more than one real instruction).  */
#define SLOW_ZERO_EXTEND

/* Define if shifts truncate the shift count
   which implies one can omit a sign-extension or zero-extension
   of a shift count.  */
#define SHIFT_COUNT_TRUNCATED

/* Value is 1 if truncating an integer of INPREC bits to OUTPREC bits
   is done just by pretending it is already truncated.  */
#define TRULY_NOOP_TRUNCATION(OUTPREC, INPREC) 1

/* Specify the machine mode that pointers have.
   After generation of rtl, the compiler makes no further distinction
   between pointers and any other objects of this machine mode.  */
#define Pmode SImode

/* A function address in a call instruction
   is a byte address (for indexing purposes)
   so give the MEM rtx a byte's mode.  */
#define FUNCTION_MODE QImode

/* Compute the cost of computing a constant rtl expression RTX
   whose rtx-code is CODE.  The body of this macro is a portion
   of a switch statement.  If the code is computed here,
   return it with a return statement.  Otherwise, break from the switch.  */

#define CONST_COSTS(RTX,CODE) \
  case CONST_INT:						\
    /* Constant zero is super cheap due to clr instruction.  */	\
    if (RTX == const0_rtx) return 0;				\
    if ((unsigned) INTVAL (RTX) < 077) return 1;		\
  case CONST:							\
  case LABEL_REF:						\
  case SYMBOL_REF:						\
    return 3;							\
  case CONST_DOUBLE:						\
    return 5;

/* Tell final.c how to eliminate redundant test instructions.  */

/* Here we define machine-dependent flags and fields in cc_status
   (see `conditions.h').  */

/* Set if the cc value is actually in the 68881, so a floating point
   conditional branch must be output.  */
#define CC_IN_68881 040

/* Store in cc_status the expressions
   that the condition codes will describe
   after execution of an instruction whose pattern is EXP.
   Do not alter them if the instruction would not alter the cc's.  */

/* On the 68000, all the insns to store in an address register
   fail to set the cc's.  However, in some cases these instructions
   can make it possibly invalid to use the saved cc's.  In those
   cases we clear out some or all of the saved cc's so they won't be used.  */

#define NOTICE_UPDATE_CC(EXP) \
{ if (GET_CODE (EXP) == SET)					\
    { if (ADDRESS_REG_P (XEXP (EXP, 0)))			\
	{ if (cc_status.value1					\
	      && reg_mentioned_p (XEXP (EXP, 0), cc_status.value1)) \
	    cc_status.value1 = 0;				\
	  if (cc_status.value2					\
	      && reg_mentioned_p (XEXP (EXP, 0), cc_status.value2)) \
	    cc_status.value2 = 0; }				\
      else if (XEXP (EXP, 0) != pc_rtx)				\
	{ cc_status.flags = 0;					\
	  cc_status.value1 = XEXP (EXP, 0);			\
	  cc_status.value2 = XEXP (EXP, 1); } }			\
  else if (GET_CODE (EXP) == PARALLEL				\
	   && GET_CODE (XVECEXP (EXP, 0, 0)) == SET)		\
    { if (ADDRESS_REG_P (XEXP (XVECEXP (EXP, 0, 0), 0)))	\
	CC_STATUS_INIT;						\
      else if (XEXP (XVECEXP (EXP, 0, 0), 0) != pc_rtx)		\
	{ cc_status.flags = 0;					\
	  cc_status.value1 = XEXP (XVECEXP (EXP, 0, 0), 0);	\
	  cc_status.value2 = XEXP (XVECEXP (EXP, 0, 0), 1); } }	\
  else CC_STATUS_INIT;						\
  if (cc_status.value2 != 0					\
      && ADDRESS_REG_P (cc_status.value2)			\
      && GET_MODE (cc_status.value2) == QImode)			\
    CC_STATUS_INIT;						\
  if (cc_status.value1 && GET_CODE (cc_status.value1) == REG	\
      && cc_status.value2					\
      && reg_mentioned_p (cc_status.value1, cc_status.value2))	\
    cc_status.value2 = 0;					\
  if ((cc_status.value1 && FP_REG_P (cc_status.value1))		\
      || (cc_status.value2 && FP_REG_P (cc_status.value2)))	\
    cc_status.flags = CC_IN_68881;				\
  if (cc_status.value2 != 0)					\
    switch (GET_CODE (cc_status.value2))			\
      { case PLUS: case MINUS: case MULT: case UMULT:		\
	case DIV: case UDIV: case ASHIFT: case LSHIFT:		\
	case NEG:						\
	  if (GET_MODE (cc_status.value2) != VOIDmode)		\
	    cc_status.flags |= CC_NO_OVERFLOW; }}

#define OUTPUT_JUMP(NORMAL, FLOAT, NO_OV)  \
{ if (cc_status.flags & CC_IN_68881)				\
    return FLOAT;						\
  if (cc_status.flags & CC_NO_OVERFLOW)				\
    return NO_OV;						\
  return NORMAL; }

/* Control the assembler format that we output.  */

#define TEXT_SECTION_ASM_OP ".text"

#define DATA_SECTION_ASM_OP ".data"

/* How to refer to registers in assembler output.
   This sequence is indexed by compiler's hard-register-number (see above).  */

#define REGISTER_NAMES \
{"d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7",	\
 "a0", "a1", "a2", "a3", "a4", "a5", "a6", "sp",	\
 "fp0", "fp1", "fp2", "fp3", "fp4", "fp5", "fp6", "fp7"}

/* How to renumber registers for dbx and gdb.
   On the Sun-3, the floating point registers have numbers
   18 to 25, not 16 to 23 as they do in the compiler.  */

#define DBX_REGISTER_NUMBER(REGNO) ((REGNO) < 16 ? (REGNO) : (REGNO) + 2)

/* This is how to output an assembler line defining a `double' constant.  */

#define ASM_OUTPUT_DOUBLE(FILE,VALUE)  \
  fprintf (FILE, "\t.double 0r%e\n", (VALUE))

/* This is how to output an assembler line defining a `float' constant.  */

#define ASM_OUTPUT_FLOAT(FILE,VALUE)  \
do { union { float f; long l;} tem;			\
     tem.f = (VALUE);					\
     fprintf (FILE, "\t.long 0x%x\n", tem.l);	\
   } while (0)

/* This is how to output an assembler line
   that says to advance the location counter
   to a multiple of 2**LOG bytes.  */

#define ASM_OUTPUT_ALIGN(FILE,LOG)	\
  if ((LOG) == 1)			\
    fprintf (FILE, "\t.even\n");	\
  else if ((LOG) != 0)			\
    abort ();

#define ASM_OUTPUT_SKIP(FILE,SIZE)  \
  fprintf (FILE, "\t.skip %d\n", (SIZE))

/* Define the parentheses used to group arithmetic operations
   in assembler code.  */

#define ASM_OPEN_PAREN "("
#define ASM_CLOSE_PAREN ")"

/* Specify what to precede various sizes of constant with
   in the output file.  */

#define ASM_INT_OP ".long "
#define ASM_SHORT_OP ".word "
#define ASM_CHAR_OP ".byte "

/* Define results of standard character escape sequences.  */
#define TARGET_BELL 007
#define TARGET_BS 010
#define TARGET_TAB 011
#define TARGET_NEWLINE 012
#define TARGET_VT 013
#define TARGET_FF 014
#define TARGET_CR 015

#define PRINT_OPERAND(FILE, X)  \
{ if (GET_CODE (X) == REG)						\
    fprintf (FILE, "%s", reg_name [REGNO (X)]);				\
  else if (GET_CODE (X) == MEM)						\
    output_address (XEXP (X, 0));					\
  else if (GET_CODE (X) == CONST_DOUBLE && GET_MODE (X) == SFmode)	\
    { union { double d; int i[2]; } u;					\
      union { float f; int i; } u1;					\
      u.i[0] = XINT (X, 0); u.i[1] = XINT (X, 1);			\
      u1.f = u.d;							\
      fprintf (FILE, "#0x%x", u1.i); }					\
  else if (GET_CODE (X) == CONST_DOUBLE)				\
    { union { double d; int i[2]; } u;					\
      u.i[0] = XINT (X, 0); u.i[1] = XINT (X, 1);			\
      fprintf (FILE, "#0r%g", u.d); }					\
  else { putc ('#', FILE); output_addr_const (FILE, X); }}

/* Note that this contains a kludge that knows that the only reason
   we have an address (plus (label_ref...) (reg...))
   is in the insn before a tablejump, and the displacement must be 6.  */
#define PRINT_OPERAND_ADDRESS(FILE, ADDR)  \
{ register rtx reg1, reg2, breg, ireg;					\
  register rtx addr = ADDR;						\
  rtx offset;								\
  switch (GET_CODE (addr))						\
    {									\
    case REG:								\
      fprintf (FILE, "%s@", reg_name [REGNO (addr)]);			\
      break;								\
    case PRE_DEC:							\
      fprintf (FILE, "%s@-", reg_name [REGNO (XEXP (addr, 0))]);	\
      break;								\
    case POST_INC:							\
      fprintf (FILE, "%s@+", reg_name [REGNO (XEXP (addr, 0))]);	\
      break;								\
    case PLUS:								\
      reg1 = 0;	reg2 = 0;						\
      ireg = 0;	breg = 0;						\
      offset = 0;							\
      if (CONSTANT_ADDRESS_P (XEXP (addr, 0)))				\
	{								\
	  offset = XEXP (addr, 0);					\
	  addr = XEXP (addr, 1);					\
	}								\
      else if (CONSTANT_ADDRESS_P (XEXP (addr, 1)))			\
	{								\
	  offset = XEXP (addr, 1);					\
	  addr = XEXP (addr, 0);					\
	}								\
      if (GET_CODE (addr) != PLUS) ;					\
      else if (GET_CODE (XEXP (addr, 0)) == SIGN_EXTEND)		\
	{								\
	  reg1 = XEXP (addr, 0);					\
	  addr = XEXP (addr, 1);					\
	}								\
      else if (GET_CODE (XEXP (addr, 1)) == SIGN_EXTEND)		\
	{								\
	  reg1 = XEXP (addr, 1);					\
	  addr = XEXP (addr, 0);					\
	}								\
      else if (GET_CODE (XEXP (addr, 0)) == MULT)			\
	{								\
	  reg1 = XEXP (addr, 0);					\
	  addr = XEXP (addr, 1);					\
	}								\
      else if (GET_CODE (XEXP (addr, 1)) == MULT)			\
	{								\
	  reg1 = XEXP (addr, 1);					\
	  addr = XEXP (addr, 0);					\
	}								\
      else if (GET_CODE (XEXP (addr, 0)) == REG)			\
	{								\
	  reg1 = XEXP (addr, 0);					\
	  addr = XEXP (addr, 1);					\
	}								\
      else if (GET_CODE (XEXP (addr, 1)) == REG)			\
	{								\
	  reg1 = XEXP (addr, 1);					\
	  addr = XEXP (addr, 0);					\
	}								\
      if (GET_CODE (addr) == REG || GET_CODE (addr) == MULT		\
	  || GET_CODE (addr) == SIGN_EXTEND)				\
	{ if (reg1 == 0) reg1 = addr; else reg2 = addr; addr = 0; }	\
/*  for OLD_INDEXING							\
      else if (GET_CODE (addr) == PLUS)					\
	{								\
	  if (GET_CODE (XEXP (addr, 0)) == REG)				\
	    {								\
	      reg2 = XEXP (addr, 0);					\
	      addr = XEXP (addr, 1);					\
	    }								\
	  else if (GET_CODE (XEXP (addr, 1)) == REG)			\
	    {								\
	      reg2 = XEXP (addr, 1);					\
	      addr = XEXP (addr, 0);					\
	    }								\
	}								\
  */									\
      if (offset != 0) { if (addr != 0) abort (); addr = offset; }	\
      if ((reg1 && (GET_CODE (reg1) == SIGN_EXTEND			\
		    || GET_CODE (reg1) == MULT))			\
	  || (reg2 != 0 && REGNO_OK_FOR_BASE_P (REGNO (reg2))))		\
	{ breg = reg2; ireg = reg1; }					\
      else if (reg1 != 0 && REGNO_OK_FOR_BASE_P (REGNO (reg1)))		\
	{ breg = reg1; ireg = reg2; }					\
      if (ireg != 0 && breg == 0 && GET_CODE (addr) == LABEL_REF)	\
        { int scale = 1;						\
	  if (GET_CODE (ireg) == MULT)					\
	    { scale = INTVAL (XEXP (ireg, 1));				\
	      ireg = XEXP (ireg, 0); }					\
	  if (GET_CODE (ireg) == SIGN_EXTEND)				\
	    fprintf (FILE, "pc@(6,%s:w", reg_name[REGNO (XEXP (ireg, 0))]); \
	  else								\
	    fprintf (FILE, "pc@(6,%s:l", reg_name[REGNO (ireg)]);	\
	  if (scale != 1) fprintf (FILE, ":%d", scale);			\
	  putc (')', FILE);						\
	  break; }							\
      if (ireg != 0 || breg != 0)					\
	{ int scale = 1;						\
	  if (breg == 0)						\
	    abort ();							\
	  fprintf (FILE, "%s@(", reg_name[REGNO (breg)]);		\
	  if (addr != 0)						\
	    output_addr_const (FILE, addr);				\
	  if (addr != 0 && ireg != 0)					\
	    putc (',', FILE);						\
	  if (ireg != 0 && GET_CODE (ireg) == MULT)			\
	    { scale = INTVAL (XEXP (ireg, 1));				\
	      ireg = XEXP (ireg, 0); }					\
	  if (ireg != 0 && GET_CODE (ireg) == SIGN_EXTEND)		\
	    fprintf (FILE, "%s:w", reg_name[REGNO (XEXP (ireg, 0))]);	\
	  else if (ireg != 0)						\
	    fprintf (FILE, "%s:l", reg_name[REGNO (ireg)]);		\
	  if (scale != 1) fprintf (FILE, ":%d", scale);			\
	  putc (')', FILE);						\
	  break;							\
	}								\
      else if (reg1 != 0 && GET_CODE (addr) == LABEL_REF)		\
        { fprintf (FILE, "pc@(6,%s:w)", reg_name[REGNO (reg1)]);	\
	  break; }							\
    default:								\
      if (GET_CODE (addr) == CONST_INT					\
	  && INTVAL (addr) < 0x8000					\
	  && INTVAL (addr) >= -0x8000)					\
	fprintf (FILE, "%d:w", INTVAL (addr));				\
      else								\
        output_addr_const (FILE, addr);					\
    }}

/*
Local variables:
version-control: t
End:
*/
