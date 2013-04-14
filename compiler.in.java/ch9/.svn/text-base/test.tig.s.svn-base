# Before canonicalization: 
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    BINOP(PLUS,
     TEMP %ebp,
     CONST 0)),
   CONST -4)),
 CALL(
  NAME L1,
   MEM(
    BINOP(PLUS,
     TEMP %ebp,
     CONST 0))))
# After canonicalization: MOVE(
 TEMP t1,
 BINOP(PLUS,
  MEM(
   BINOP(PLUS,
    TEMP %ebp,
    CONST 0)),
  CONST -4))
MOVE(
 TEMP t0,
 CALL(
  NAME L1,
   MEM(
    BINOP(PLUS,
     TEMP %ebp,
     CONST 0))))
MOVE(
 MEM(
  TEMP t1),
 TEMP t0)
# Basic Blocks: 
#
LABEL L6
MOVE(
 TEMP t1,
 BINOP(PLUS,
  MEM(
   BINOP(PLUS,
    TEMP %ebp,
    CONST 0)),
  CONST -4))
MOVE(
 TEMP t0,
 CALL(
  NAME L1,
   MEM(
    BINOP(PLUS,
     TEMP %ebp,
     CONST 0))))
MOVE(
 MEM(
  TEMP t1),
 TEMP t0)
JUMP(
 NAME L5)
LABEL L5
# Trace Scheduled: 
LABEL L6
MOVE(
 TEMP t1,
 BINOP(PLUS,
  MEM(
   BINOP(PLUS,
    TEMP %ebp,
    CONST 0)),
  CONST -4))
MOVE(
 TEMP t0,
 CALL(
  NAME L1,
   MEM(
    BINOP(PLUS,
     TEMP %ebp,
     CONST 0))))
MOVE(
 MEM(
  TEMP t1),
 TEMP t0)
JUMP(
 NAME L5)
LABEL L5
# Instructions: 
Tree.LABEL@c2a132:
    movl $0, t3
    addl %ebp, t3
    movl (t3), t2
    movl $-4, t4
    addl t2, t4
    movl t4, t1
    movl L1, t5
    movl $0, t7
    addl %ebp, t7
    movl (t7), t6
    pushl t6
    call *t5
    movl %eax, t0
    movl (t0), t1
    movl L5, t8
    jmp *t8
Tree.LABEL@b166b5:
# Before canonicalization: 
EXP(
 CONST 0)
# After canonicalization: EXP(
 CONST 0)
# Basic Blocks: 
#
LABEL L8
EXP(
 CONST 0)
JUMP(
 NAME L7)
LABEL L7
# Trace Scheduled: 
LABEL L8
EXP(
 CONST 0)
JUMP(
 NAME L7)
LABEL L7
# Instructions: 
Tree.LABEL@fa7e74:
    movl $0, t9
    movl L7, t10
    jmp *t10
Tree.LABEL@183f74d:
L0:  .ascii "abc\377\377\n"

