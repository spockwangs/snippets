# Before canonicalization: 
SEQ(
 SEQ(
  SEQ(
   MOVE(
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST -20)),
    CONST 0),
   MOVE(
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST -24)),
    BINOP(MINUS,
     MEM(
      BINOP(PLUS,
       MEM(
        BINOP(PLUS,
         TEMP sp,
         CONST 0)),
       CONST -4)),
     CONST 1))),
  SEQ(
   CJUMP(LE,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST -20)),
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST -24)),
    L96,L97),
   SEQ(
    LABEL L96,
    SEQ(
     SEQ(
      SEQ(
       LABEL L92,
       SEQ(
        SEQ(
         CJUMP(EQ,
          CONST 1,
          CONST 0,
          L93,L94),
         SEQ(
          LABEL L93,
          SEQ(
           SEQ(
            JUMP(
             NAME L65),
            JUMP(
             NAME L95)),
           SEQ(
            LABEL L94,
            LABEL L95)))),
        SEQ(
         SEQ(
          SEQ(
           SEQ(
            SEQ(
             MOVE(
              MEM(
               BINOP(PLUS,
                TEMP sp,
                CONST -32)),
              CONST 0),
             MOVE(
              MEM(
               BINOP(PLUS,
                TEMP sp,
                CONST -36)),
              BINOP(MINUS,
               MEM(
                BINOP(PLUS,
                 MEM(
                  BINOP(PLUS,
                   TEMP sp,
                   CONST 0)),
                 CONST -4)),
               CONST 1))),
            SEQ(
             CJUMP(LE,
              MEM(
               BINOP(PLUS,
                TEMP sp,
                CONST -32)),
              MEM(
               BINOP(PLUS,
                TEMP sp,
                CONST -36)),
              L85,L86),
             SEQ(
              LABEL L85,
              SEQ(
               SEQ(
                SEQ(
                 LABEL L81,
                 SEQ(
                  SEQ(
                   CJUMP(EQ,
                    CONST 1,
                    CONST 0,
                    L82,L83),
                   SEQ(
                    LABEL L82,
                    SEQ(
                     SEQ(
                      JUMP(
                       NAME L72),
                      JUMP(
                       NAME L84)),
                     SEQ(
                      LABEL L83,
                      LABEL L84)))),
                  SEQ(
                   SEQ(
                    EXP(
                     CALL(
                      NAME print,
                       MEM(
                        BINOP(PLUS,
                         TEMP sp,
                         CONST 0)),
                       ESEQ(
                        SEQ(
                         CJUMP(EQ,
                          MEM(
                           BINOP(PLUS,
                            MEM(
                             MEM(
                              BINOP(PLUS,
                               MEM(
                                BINOP(PLUS,
                                 TEMP sp,
                                 CONST 0)),
                               CONST -12))),
                            BINOP(MUL,
                             MEM(
                              BINOP(PLUS,
                               TEMP sp,
                               CONST -20)),
                             CONST 4))),
                          MEM(
                           BINOP(PLUS,
                            TEMP sp,
                            CONST -32)),
                          L75,L76),
                         SEQ(
                          LABEL L75,
                          SEQ(
                           SEQ(
                            MOVE(
                             TEMP t7,
                             NAME L73),
                            JUMP(
                             NAME L77)),
                           SEQ(
                            LABEL L76,
                            SEQ(
                             MOVE(
                              TEMP t7,
                              NAME L74),
                             LABEL L77))))),
                        TEMP t7))),
                    SEQ(
                     SEQ(
                      CJUMP(GE,
                       MEM(
                        BINOP(PLUS,
                         TEMP sp,
                         CONST -32)),
                       MEM(
                        BINOP(PLUS,
                         TEMP sp,
                         CONST -36)),
                       L78,L79),
                      SEQ(
                       LABEL L78,
                       SEQ(
                        SEQ(
                         JUMP(
                          NAME L72),
                         JUMP(
                          NAME L80)),
                        SEQ(
                         LABEL L79,
                         LABEL L80)))),
                     MOVE(
                      MEM(
                       BINOP(PLUS,
                        TEMP sp,
                        CONST -32)),
                      BINOP(PLUS,
                       MEM(
                        BINOP(PLUS,
                         TEMP sp,
                         CONST -32)),
                       CONST 1)))),
                   SEQ(
                    JUMP(
                     NAME L81),
                    LABEL L72)))),
                JUMP(
                 NAME L87)),
               SEQ(
                LABEL L86,
                LABEL L87))))),
           EXP(
            CALL(
             NAME print,
              MEM(
               BINOP(PLUS,
                TEMP sp,
                CONST 0)),
              NAME L88))),
          SEQ(
           SEQ(
            CJUMP(GE,
             MEM(
              BINOP(PLUS,
               TEMP sp,
               CONST -20)),
             MEM(
              BINOP(PLUS,
               TEMP sp,
               CONST -24)),
             L89,L90),
            SEQ(
             LABEL L89,
             SEQ(
              SEQ(
               JUMP(
                NAME L65),
               JUMP(
                NAME L91)),
              SEQ(
               LABEL L90,
               LABEL L91)))),
           MOVE(
            MEM(
             BINOP(PLUS,
              TEMP sp,
              CONST -20)),
            BINOP(PLUS,
             MEM(
              BINOP(PLUS,
               TEMP sp,
               CONST -20)),
             CONST 1)))),
         SEQ(
          JUMP(
           NAME L92),
          LABEL L65)))),
      JUMP(
       NAME L98)),
     SEQ(
      LABEL L97,
      LABEL L98))))),
 EXP(
  CALL(
   NAME print,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST 0)),
    NAME L99)))
# After canonicalization: MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -20)),
 CONST 0)
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -24)),
 BINOP(MINUS,
  MEM(
   BINOP(PLUS,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST 0)),
    CONST -4)),
  CONST 1))
CJUMP(LE,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -20)),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -24)),
 L96,L97)
LABEL L96
LABEL L92
CJUMP(EQ,
 CONST 1,
 CONST 0,
 L93,L94)
LABEL L93
JUMP(
 NAME L65)
JUMP(
 NAME L95)
LABEL L94
LABEL L95
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -32)),
 CONST 0)
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -36)),
 BINOP(MINUS,
  MEM(
   BINOP(PLUS,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST 0)),
    CONST -4)),
  CONST 1))
CJUMP(LE,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -32)),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -36)),
 L85,L86)
LABEL L85
LABEL L81
CJUMP(EQ,
 CONST 1,
 CONST 0,
 L82,L83)
LABEL L82
JUMP(
 NAME L72)
JUMP(
 NAME L84)
LABEL L83
LABEL L84
MOVE(
 TEMP t8,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST 0)))
CJUMP(EQ,
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -12))),
   BINOP(MUL,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST -20)),
    CONST 4))),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -32)),
 L75,L76)
LABEL L75
MOVE(
 TEMP t7,
 NAME L73)
JUMP(
 NAME L77)
LABEL L76
MOVE(
 TEMP t7,
 NAME L74)
LABEL L77
EXP(
 CALL(
  NAME print,
   TEMP t8,
   TEMP t7))
CJUMP(GE,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -32)),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -36)),
 L78,L79)
LABEL L78
JUMP(
 NAME L72)
JUMP(
 NAME L80)
LABEL L79
LABEL L80
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -32)),
 BINOP(PLUS,
  MEM(
   BINOP(PLUS,
    TEMP sp,
    CONST -32)),
  CONST 1))
JUMP(
 NAME L81)
LABEL L72
JUMP(
 NAME L87)
LABEL L86
LABEL L87
EXP(
 CALL(
  NAME print,
   MEM(
    BINOP(PLUS,
     TEMP sp,
     CONST 0)),
   NAME L88))
CJUMP(GE,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -20)),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -24)),
 L89,L90)
LABEL L89
JUMP(
 NAME L65)
JUMP(
 NAME L91)
LABEL L90
LABEL L91
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -20)),
 BINOP(PLUS,
  MEM(
   BINOP(PLUS,
    TEMP sp,
    CONST -20)),
  CONST 1))
JUMP(
 NAME L92)
LABEL L65
JUMP(
 NAME L98)
LABEL L97
LABEL L98
EXP(
 CALL(
  NAME print,
   MEM(
    BINOP(PLUS,
     TEMP sp,
     CONST 0)),
   NAME L99))
# Basic Blocks: 
#
LABEL L101
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -20)),
 CONST 0)
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -24)),
 BINOP(MINUS,
  MEM(
   BINOP(PLUS,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST 0)),
    CONST -4)),
  CONST 1))
CJUMP(LE,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -20)),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -24)),
 L96,L97)
#
LABEL L96
JUMP(
 NAME L92)
#
LABEL L92
CJUMP(EQ,
 CONST 1,
 CONST 0,
 L93,L94)
#
LABEL L93
JUMP(
 NAME L65)
#
LABEL L102
JUMP(
 NAME L95)
#
LABEL L94
JUMP(
 NAME L95)
#
LABEL L95
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -32)),
 CONST 0)
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -36)),
 BINOP(MINUS,
  MEM(
   BINOP(PLUS,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST 0)),
    CONST -4)),
  CONST 1))
CJUMP(LE,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -32)),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -36)),
 L85,L86)
#
LABEL L85
JUMP(
 NAME L81)
#
LABEL L81
CJUMP(EQ,
 CONST 1,
 CONST 0,
 L82,L83)
#
LABEL L82
JUMP(
 NAME L72)
#
LABEL L103
JUMP(
 NAME L84)
#
LABEL L83
JUMP(
 NAME L84)
#
LABEL L84
MOVE(
 TEMP t8,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST 0)))
CJUMP(EQ,
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -12))),
   BINOP(MUL,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST -20)),
    CONST 4))),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -32)),
 L75,L76)
#
LABEL L75
MOVE(
 TEMP t7,
 NAME L73)
JUMP(
 NAME L77)
#
LABEL L76
MOVE(
 TEMP t7,
 NAME L74)
JUMP(
 NAME L77)
#
LABEL L77
EXP(
 CALL(
  NAME print,
   TEMP t8,
   TEMP t7))
CJUMP(GE,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -32)),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -36)),
 L78,L79)
#
LABEL L78
JUMP(
 NAME L72)
#
LABEL L104
JUMP(
 NAME L80)
#
LABEL L79
JUMP(
 NAME L80)
#
LABEL L80
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -32)),
 BINOP(PLUS,
  MEM(
   BINOP(PLUS,
    TEMP sp,
    CONST -32)),
  CONST 1))
JUMP(
 NAME L81)
#
LABEL L72
JUMP(
 NAME L87)
#
LABEL L86
JUMP(
 NAME L87)
#
LABEL L87
EXP(
 CALL(
  NAME print,
   MEM(
    BINOP(PLUS,
     TEMP sp,
     CONST 0)),
   NAME L88))
CJUMP(GE,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -20)),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -24)),
 L89,L90)
#
LABEL L89
JUMP(
 NAME L65)
#
LABEL L105
JUMP(
 NAME L91)
#
LABEL L90
JUMP(
 NAME L91)
#
LABEL L91
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -20)),
 BINOP(PLUS,
  MEM(
   BINOP(PLUS,
    TEMP sp,
    CONST -20)),
  CONST 1))
JUMP(
 NAME L92)
#
LABEL L65
JUMP(
 NAME L98)
#
LABEL L97
JUMP(
 NAME L98)
#
LABEL L98
EXP(
 CALL(
  NAME print,
   MEM(
    BINOP(PLUS,
     TEMP sp,
     CONST 0)),
   NAME L99))
JUMP(
 NAME L100)
LABEL L100
# Trace Scheduled: 
LABEL L101
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -20)),
 CONST 0)
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -24)),
 BINOP(MINUS,
  MEM(
   BINOP(PLUS,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST 0)),
    CONST -4)),
  CONST 1))
CJUMP(LE,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -20)),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -24)),
 L96,L97)
LABEL L97
LABEL L98
EXP(
 CALL(
  NAME print,
   MEM(
    BINOP(PLUS,
     TEMP sp,
     CONST 0)),
   NAME L99))
JUMP(
 NAME L100)
LABEL L96
LABEL L92
CJUMP(EQ,
 CONST 1,
 CONST 0,
 L93,L94)
LABEL L94
LABEL L95
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -32)),
 CONST 0)
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -36)),
 BINOP(MINUS,
  MEM(
   BINOP(PLUS,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST 0)),
    CONST -4)),
  CONST 1))
CJUMP(LE,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -32)),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -36)),
 L85,L86)
LABEL L86
LABEL L87
EXP(
 CALL(
  NAME print,
   MEM(
    BINOP(PLUS,
     TEMP sp,
     CONST 0)),
   NAME L88))
CJUMP(GE,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -20)),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -24)),
 L89,L90)
LABEL L90
LABEL L91
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -20)),
 BINOP(PLUS,
  MEM(
   BINOP(PLUS,
    TEMP sp,
    CONST -20)),
  CONST 1))
JUMP(
 NAME L92)
LABEL L93
LABEL L65
JUMP(
 NAME L98)
LABEL L102
JUMP(
 NAME L95)
LABEL L85
LABEL L81
CJUMP(EQ,
 CONST 1,
 CONST 0,
 L82,L83)
LABEL L83
LABEL L84
MOVE(
 TEMP t8,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST 0)))
CJUMP(EQ,
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -12))),
   BINOP(MUL,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST -20)),
    CONST 4))),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -32)),
 L75,L76)
LABEL L76
MOVE(
 TEMP t7,
 NAME L74)
LABEL L77
EXP(
 CALL(
  NAME print,
   TEMP t8,
   TEMP t7))
CJUMP(GE,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -32)),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -36)),
 L78,L79)
LABEL L79
LABEL L80
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -32)),
 BINOP(PLUS,
  MEM(
   BINOP(PLUS,
    TEMP sp,
    CONST -32)),
  CONST 1))
JUMP(
 NAME L81)
LABEL L82
LABEL L72
JUMP(
 NAME L87)
LABEL L103
JUMP(
 NAME L84)
LABEL L75
MOVE(
 TEMP t7,
 NAME L73)
JUMP(
 NAME L77)
LABEL L78
JUMP(
 NAME L72)
LABEL L104
JUMP(
 NAME L80)
LABEL L89
JUMP(
 NAME L65)
LABEL L105
JUMP(
 NAME L91)
LABEL L100
# Instructions: 
Tree.LABEL@1a626f:
movl 0, t9
movl t9, -20(sp)
movl 0, t12
addl sp, t12
movl (t12), t11
movl -4, t13
addl t11, t13
movl (t13), t10
movl 1, t14
subl t10, t10
movl t14, -24(sp)
movl -20, t16
addl sp, t16
movl (t16), t15
movl -24, t18
addl sp, t18
movl (t18), t17
movl L96, t19
cmpl t15, t17
jle L96
Tree.LABEL@116471f:
Tree.LABEL@1975b59:
movl print, t20
movl 0, t22
addl sp, t22
movl (t22), t21
movl L99, t23
pushl t23
pushl t21
call *t20
movl L100, t24
jmp *t24
Tree.LABEL@1ee3914:
Tree.LABEL@e5855a:
movl 1, t25
movl 0, t26
movl L93, t27
cmpl t25, t26
je L93
Tree.LABEL@95fd19:
Tree.LABEL@11b9fb1:
movl 0, t28
movl t28, -32(sp)
movl 0, t31
addl sp, t31
movl (t31), t30
movl -4, t32
addl t30, t32
movl (t32), t29
movl 1, t33
subl t29, t29
movl t33, -36(sp)
movl -32, t35
addl sp, t35
movl (t35), t34
movl -36, t37
addl sp, t37
movl (t37), t36
movl L85, t38
cmpl t34, t36
jle L85
Tree.LABEL@913fe2:
Tree.LABEL@1f934ad:
movl print, t39
movl 0, t41
addl sp, t41
movl (t41), t40
movl L88, t42
pushl t42
pushl t40
call *t39
movl -20, t44
addl sp, t44
movl (t44), t43
movl -24, t46
addl sp, t46
movl (t46), t45
movl L89, t47
cmpl t43, t45
jge L89
Tree.LABEL@1f14ceb:
Tree.LABEL@f0eed6:
movl -20, t49
addl sp, t49
movl (t49), t48
movl 1, t50
addl t48, t50
movl t50, -20(sp)
movl L92, t51
jmp *t51
Tree.LABEL@1d05c81:
Tree.LABEL@691f36:
movl L98, t52
jmp *t52
Tree.LABEL@18020cc:
movl L95, t53
jmp *t53
Tree.LABEL@e94e92:
Tree.LABEL@12558d6:
movl 1, t54
movl 0, t55
movl L82, t56
cmpl t54, t55
je L82
Tree.LABEL@eb7859:
Tree.LABEL@12a54f9:
movl 0(sp), t8
movl 0, t61
addl sp, t61
movl (t61), t60
movl -12, t62
addl t60, t62
movl (t62), t59
movl (t59), t58
movl -20, t64
addl sp, t64
movl (t64), t63
movl 4, t65
movl t63, eax
mull t65
addl t58, eax
movl (eax), t57
movl -32, t67
addl sp, t67
movl (t67), t66
movl L75, t68
cmpl t57, t66
je L75
Tree.LABEL@30e280:
movl L74, t69
movl t69, t7
Tree.LABEL@16672d6:
movl print, t70
pushl t7
pushl t8
call *t70
movl -32, t72
addl sp, t72
movl (t72), t71
movl -36, t74
addl sp, t74
movl (t74), t73
movl L78, t75
cmpl t71, t73
jge L78
Tree.LABEL@fd54d6:
Tree.LABEL@1ccb029:
movl -32, t77
addl sp, t77
movl (t77), t76
movl 1, t78
addl t76, t78
movl t78, -32(sp)
movl L81, t79
jmp *t79
Tree.LABEL@1415de6:
Tree.LABEL@7bd9f2:
movl L87, t80
jmp *t80
Tree.LABEL@121cc40:
movl L84, t81
jmp *t81
Tree.LABEL@1e893df:
movl L73, t82
movl t82, t7
movl L77, t83
jmp *t83
Tree.LABEL@443226:
movl L72, t84
jmp *t84
Tree.LABEL@1386000:
movl L80, t85
jmp *t85
Tree.LABEL@26d4f1:
movl L65, t86
jmp *t86
Tree.LABEL@1662dc8:
movl L91, t87
jmp *t87
Tree.LABEL@147c5fc:
"
"
"
"
" ."
" O"
" ."
" O"
"
"
" ."
" O"
" ."
" O"
# Before canonicalization: 
SEQ(
 CJUMP(EQ,
  MEM(
   BINOP(PLUS,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST 0)),
    CONST 4)),
  MEM(
   BINOP(PLUS,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST 0)),
    CONST -4)),
  L37,L38),
 SEQ(
  LABEL L37,
  SEQ(
   SEQ(
    EXP(
     CALL(
      NAME L1,
       MEM(
        BINOP(PLUS,
         TEMP sp,
         CONST 0)))),
    JUMP(
     NAME L39)),
   SEQ(
    LABEL L38,
    SEQ(
     SEQ(
      SEQ(
       MOVE(
        MEM(
         BINOP(PLUS,
          TEMP sp,
          CONST -8)),
        CONST 0),
       MOVE(
        MEM(
         BINOP(PLUS,
          TEMP sp,
          CONST -12)),
        BINOP(MINUS,
         MEM(
          BINOP(PLUS,
           MEM(
            BINOP(PLUS,
             TEMP sp,
             CONST 0)),
           CONST -4)),
         CONST 1))),
      SEQ(
       CJUMP(LE,
        MEM(
         BINOP(PLUS,
          TEMP sp,
          CONST -8)),
        MEM(
         BINOP(PLUS,
          TEMP sp,
          CONST -12)),
        L34,L35),
       SEQ(
        LABEL L34,
        SEQ(
         SEQ(
          SEQ(
           LABEL L30,
           SEQ(
            SEQ(
             CJUMP(EQ,
              CONST 1,
              CONST 0,
              L31,L32),
             SEQ(
              LABEL L31,
              SEQ(
               SEQ(
                JUMP(
                 NAME L13),
                JUMP(
                 NAME L33)),
               SEQ(
                LABEL L32,
                LABEL L33)))),
            SEQ(
             SEQ(
              SEQ(
               CJUMP(EQ,
                ESEQ(
                 SEQ(
                  CJUMP(EQ,
                   ESEQ(
                    SEQ(
                     CJUMP(EQ,
                      MEM(
                       BINOP(PLUS,
                        MEM(
                         MEM(
                          BINOP(PLUS,
                           MEM(
                            BINOP(PLUS,
                             TEMP sp,
                             CONST 0)),
                           CONST -8))),
                        BINOP(MUL,
                         MEM(
                          BINOP(PLUS,
                           TEMP sp,
                           CONST -8)),
                         CONST 4))),
                      CONST 0,
                      L14,L15),
                     SEQ(
                      LABEL L14,
                      SEQ(
                       SEQ(
                        MOVE(
                         TEMP t1,
                         ESEQ(
                          SEQ(
                           MOVE(
                            TEMP t2,
                            CONST 1),
                           SEQ(
                            CJUMP(EQ,
                             MEM(
                              BINOP(PLUS,
                               MEM(
                                MEM(
                                 BINOP(PLUS,
                                  MEM(
                                   BINOP(PLUS,
                                    TEMP sp,
                                    CONST 0)),
                                  CONST -16))),
                               BINOP(MUL,
                                BINOP(PLUS,
                                 MEM(
                                  BINOP(PLUS,
                                   TEMP sp,
                                   CONST -8)),
                                 MEM(
                                  BINOP(PLUS,
                                   MEM(
                                    BINOP(PLUS,
                                     TEMP sp,
                                     CONST 0)),
                                   CONST 4))),
                                CONST 4))),
                             CONST 0,
                             L26,L27),
                            SEQ(
                             LABEL L27,
                             SEQ(
                              MOVE(
                               TEMP t2,
                               CONST 0),
                              LABEL L26)))),
                          TEMP t2)),
                        JUMP(
                         NAME L16)),
                       SEQ(
                        LABEL L15,
                        SEQ(
                         MOVE(
                          TEMP t1,
                          CONST 0),
                         LABEL L16))))),
                    TEMP t1),
                   CONST 0,
                   L17,L18),
                  SEQ(
                   LABEL L17,
                   SEQ(
                    SEQ(
                     MOVE(
                      TEMP t0,
                      ESEQ(
                       SEQ(
                        MOVE(
                         TEMP t3,
                         CONST 1),
                        SEQ(
                         CJUMP(EQ,
                          MEM(
                           BINOP(PLUS,
                            MEM(
                             MEM(
                              BINOP(PLUS,
                               MEM(
                                BINOP(PLUS,
                                 TEMP sp,
                                 CONST 0)),
                               CONST -20))),
                            BINOP(MUL,
                             BINOP(MINUS,
                              BINOP(PLUS,
                               MEM(
                                BINOP(PLUS,
                                 TEMP sp,
                                 CONST -8)),
                               CONST 7),
                              MEM(
                               BINOP(PLUS,
                                MEM(
                                 BINOP(PLUS,
                                  TEMP sp,
                                  CONST 0)),
                                CONST 4))),
                             CONST 4))),
                          CONST 0,
                          L28,L29),
                         SEQ(
                          LABEL L29,
                          SEQ(
                           MOVE(
                            TEMP t3,
                            CONST 0),
                           LABEL L28)))),
                       TEMP t3)),
                     JUMP(
                      NAME L19)),
                    SEQ(
                     LABEL L18,
                     SEQ(
                      MOVE(
                       TEMP t0,
                       CONST 0),
                      LABEL L19))))),
                 TEMP t0),
                CONST 0,
                L20,L21),
               SEQ(
                LABEL L20,
                SEQ(
                 SEQ(
                  SEQ(
                   MOVE(
                    MEM(
                     BINOP(PLUS,
                      MEM(
                       MEM(
                        BINOP(PLUS,
                         MEM(
                          BINOP(PLUS,
                           TEMP sp,
                           CONST 0)),
                         CONST -8))),
                      BINOP(MUL,
                       MEM(
                        BINOP(PLUS,
                         TEMP sp,
                         CONST -8)),
                       CONST 4))),
                    CONST 1),
                   SEQ(
                    MOVE(
                     MEM(
                      BINOP(PLUS,
                       MEM(
                        MEM(
                         BINOP(PLUS,
                          MEM(
                           BINOP(PLUS,
                            TEMP sp,
                            CONST 0)),
                          CONST -16))),
                       BINOP(MUL,
                        BINOP(PLUS,
                         MEM(
                          BINOP(PLUS,
                           TEMP sp,
                           CONST -8)),
                         CONST 1),
                        CONST 4))),
                     CONST 1),
                    SEQ(
                     MOVE(
                      MEM(
                       BINOP(PLUS,
                        MEM(
                         MEM(
                          BINOP(PLUS,
                           MEM(
                            BINOP(PLUS,
                             TEMP sp,
                             CONST 0)),
                           CONST -20))),
                        BINOP(MUL,
                         BINOP(MINUS,
                          BINOP(PLUS,
                           MEM(
                            BINOP(PLUS,
                             TEMP sp,
                             CONST -8)),
                           CONST 7),
                          MEM(
                           BINOP(PLUS,
                            MEM(
                             BINOP(PLUS,
                              TEMP sp,
                              CONST 0)),
                            CONST 4))),
                         CONST 4))),
                      CONST 1),
                     SEQ(
                      MOVE(
                       MEM(
                        BINOP(PLUS,
                         MEM(
                          MEM(
                           BINOP(PLUS,
                            MEM(
                             BINOP(PLUS,
                              TEMP sp,
                              CONST 0)),
                            CONST -12))),
                         BINOP(MUL,
                          MEM(
                           BINOP(PLUS,
                            MEM(
                             BINOP(PLUS,
                              TEMP sp,
                              CONST 0)),
                            CONST 4)),
                          CONST 4))),
                       MEM(
                        BINOP(PLUS,
                         TEMP sp,
                         CONST -8))),
                      SEQ(
                       EXP(
                        CALL(
                         NAME L0,
                          MEM(
                           BINOP(PLUS,
                            TEMP sp,
                            CONST 0)),
                          BINOP(PLUS,
                           MEM(
                            BINOP(PLUS,
                             MEM(
                              BINOP(PLUS,
                               TEMP sp,
                               CONST 0)),
                             CONST 4)),
                           CONST 1))),
                       SEQ(
                        MOVE(
                         MEM(
                          BINOP(PLUS,
                           MEM(
                            MEM(
                             BINOP(PLUS,
                              MEM(
                               BINOP(PLUS,
                                TEMP sp,
                                CONST 0)),
                              CONST -8))),
                           BINOP(MUL,
                            MEM(
                             BINOP(PLUS,
                              TEMP sp,
                              CONST -8)),
                            CONST 4))),
                         CONST 0),
                        SEQ(
                         MOVE(
                          MEM(
                           BINOP(PLUS,
                            MEM(
                             MEM(
                              BINOP(PLUS,
                               MEM(
                                BINOP(PLUS,
                                 TEMP sp,
                                 CONST 0)),
                               CONST -16))),
                            BINOP(MUL,
                             BINOP(PLUS,
                              MEM(
                               BINOP(PLUS,
                                TEMP sp,
                                CONST -8)),
                              MEM(
                               BINOP(PLUS,
                                MEM(
                                 BINOP(PLUS,
                                  TEMP sp,
                                  CONST 0)),
                                CONST 4))),
                             CONST 4))),
                          CONST 0),
                         MOVE(
                          MEM(
                           BINOP(PLUS,
                            MEM(
                             MEM(
                              BINOP(PLUS,
                               MEM(
                                BINOP(PLUS,
                                 TEMP sp,
                                 CONST 0)),
                               CONST -20))),
                            BINOP(MUL,
                             BINOP(MINUS,
                              BINOP(PLUS,
                               MEM(
                                BINOP(PLUS,
                                 TEMP sp,
                                 CONST -8)),
                               CONST 7),
                              MEM(
                               BINOP(PLUS,
                                MEM(
                                 BINOP(PLUS,
                                  TEMP sp,
                                  CONST 0)),
                                CONST 4))),
                             CONST 4))),
                          CONST 0)))))))),
                  JUMP(
                   NAME L22)),
                 SEQ(
                  LABEL L21,
                  LABEL L22)))),
              SEQ(
               SEQ(
                CJUMP(GE,
                 MEM(
                  BINOP(PLUS,
                   TEMP sp,
                   CONST -8)),
                 MEM(
                  BINOP(PLUS,
                   TEMP sp,
                   CONST -12)),
                 L23,L24),
                SEQ(
                 LABEL L23,
                 SEQ(
                  SEQ(
                   JUMP(
                    NAME L13),
                   JUMP(
                    NAME L25)),
                  SEQ(
                   LABEL L24,
                   LABEL L25)))),
               MOVE(
                MEM(
                 BINOP(PLUS,
                  TEMP sp,
                  CONST -8)),
                BINOP(PLUS,
                 MEM(
                  BINOP(PLUS,
                   TEMP sp,
                   CONST -8)),
                 CONST 1)))),
             SEQ(
              JUMP(
               NAME L30),
              LABEL L13)))),
          JUMP(
           NAME L36)),
         SEQ(
          LABEL L35,
          LABEL L36))))),
     LABEL L39)))))
# After canonicalization: CJUMP(EQ,
 MEM(
  BINOP(PLUS,
   MEM(
    BINOP(PLUS,
     TEMP sp,
     CONST 0)),
   CONST 4)),
 MEM(
  BINOP(PLUS,
   MEM(
    BINOP(PLUS,
     TEMP sp,
     CONST 0)),
   CONST -4)),
 L37,L38)
LABEL L37
EXP(
 CALL(
  NAME L1,
   MEM(
    BINOP(PLUS,
     TEMP sp,
     CONST 0))))
JUMP(
 NAME L39)
LABEL L38
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -8)),
 CONST 0)
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -12)),
 BINOP(MINUS,
  MEM(
   BINOP(PLUS,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST 0)),
    CONST -4)),
  CONST 1))
CJUMP(LE,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -8)),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -12)),
 L34,L35)
LABEL L34
LABEL L30
CJUMP(EQ,
 CONST 1,
 CONST 0,
 L31,L32)
LABEL L31
JUMP(
 NAME L13)
JUMP(
 NAME L33)
LABEL L32
LABEL L33
CJUMP(EQ,
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -8))),
   BINOP(MUL,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST -8)),
    CONST 4))),
 CONST 0,
 L14,L15)
LABEL L14
MOVE(
 TEMP t2,
 CONST 1)
CJUMP(EQ,
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -16))),
   BINOP(MUL,
    BINOP(PLUS,
     MEM(
      BINOP(PLUS,
       TEMP sp,
       CONST -8)),
     MEM(
      BINOP(PLUS,
       MEM(
        BINOP(PLUS,
         TEMP sp,
         CONST 0)),
       CONST 4))),
    CONST 4))),
 CONST 0,
 L26,L27)
LABEL L27
MOVE(
 TEMP t2,
 CONST 0)
LABEL L26
MOVE(
 TEMP t1,
 TEMP t2)
JUMP(
 NAME L16)
LABEL L15
MOVE(
 TEMP t1,
 CONST 0)
LABEL L16
CJUMP(EQ,
 TEMP t1,
 CONST 0,
 L17,L18)
LABEL L17
MOVE(
 TEMP t3,
 CONST 1)
CJUMP(EQ,
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -20))),
   BINOP(MUL,
    BINOP(MINUS,
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST -8)),
      CONST 7),
     MEM(
      BINOP(PLUS,
       MEM(
        BINOP(PLUS,
         TEMP sp,
         CONST 0)),
       CONST 4))),
    CONST 4))),
 CONST 0,
 L28,L29)
LABEL L29
MOVE(
 TEMP t3,
 CONST 0)
LABEL L28
MOVE(
 TEMP t0,
 TEMP t3)
JUMP(
 NAME L19)
LABEL L18
MOVE(
 TEMP t0,
 CONST 0)
LABEL L19
CJUMP(EQ,
 TEMP t0,
 CONST 0,
 L20,L21)
LABEL L20
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -8))),
   BINOP(MUL,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST -8)),
    CONST 4))),
 CONST 1)
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -16))),
   BINOP(MUL,
    BINOP(PLUS,
     MEM(
      BINOP(PLUS,
       TEMP sp,
       CONST -8)),
     CONST 1),
    CONST 4))),
 CONST 1)
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -20))),
   BINOP(MUL,
    BINOP(MINUS,
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST -8)),
      CONST 7),
     MEM(
      BINOP(PLUS,
       MEM(
        BINOP(PLUS,
         TEMP sp,
         CONST 0)),
       CONST 4))),
    CONST 4))),
 CONST 1)
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -12))),
   BINOP(MUL,
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST 4)),
    CONST 4))),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -8)))
EXP(
 CALL(
  NAME L0,
   MEM(
    BINOP(PLUS,
     TEMP sp,
     CONST 0)),
   BINOP(PLUS,
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST 4)),
    CONST 1)))
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -8))),
   BINOP(MUL,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST -8)),
    CONST 4))),
 CONST 0)
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -16))),
   BINOP(MUL,
    BINOP(PLUS,
     MEM(
      BINOP(PLUS,
       TEMP sp,
       CONST -8)),
     MEM(
      BINOP(PLUS,
       MEM(
        BINOP(PLUS,
         TEMP sp,
         CONST 0)),
       CONST 4))),
    CONST 4))),
 CONST 0)
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -20))),
   BINOP(MUL,
    BINOP(MINUS,
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST -8)),
      CONST 7),
     MEM(
      BINOP(PLUS,
       MEM(
        BINOP(PLUS,
         TEMP sp,
         CONST 0)),
       CONST 4))),
    CONST 4))),
 CONST 0)
JUMP(
 NAME L22)
LABEL L21
LABEL L22
CJUMP(GE,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -8)),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -12)),
 L23,L24)
LABEL L23
JUMP(
 NAME L13)
JUMP(
 NAME L25)
LABEL L24
LABEL L25
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -8)),
 BINOP(PLUS,
  MEM(
   BINOP(PLUS,
    TEMP sp,
    CONST -8)),
  CONST 1))
JUMP(
 NAME L30)
LABEL L13
JUMP(
 NAME L36)
LABEL L35
LABEL L36
LABEL L39
# Basic Blocks: 
#
LABEL L107
CJUMP(EQ,
 MEM(
  BINOP(PLUS,
   MEM(
    BINOP(PLUS,
     TEMP sp,
     CONST 0)),
   CONST 4)),
 MEM(
  BINOP(PLUS,
   MEM(
    BINOP(PLUS,
     TEMP sp,
     CONST 0)),
   CONST -4)),
 L37,L38)
#
LABEL L37
EXP(
 CALL(
  NAME L1,
   MEM(
    BINOP(PLUS,
     TEMP sp,
     CONST 0))))
JUMP(
 NAME L39)
#
LABEL L38
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -8)),
 CONST 0)
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -12)),
 BINOP(MINUS,
  MEM(
   BINOP(PLUS,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST 0)),
    CONST -4)),
  CONST 1))
CJUMP(LE,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -8)),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -12)),
 L34,L35)
#
LABEL L34
JUMP(
 NAME L30)
#
LABEL L30
CJUMP(EQ,
 CONST 1,
 CONST 0,
 L31,L32)
#
LABEL L31
JUMP(
 NAME L13)
#
LABEL L108
JUMP(
 NAME L33)
#
LABEL L32
JUMP(
 NAME L33)
#
LABEL L33
CJUMP(EQ,
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -8))),
   BINOP(MUL,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST -8)),
    CONST 4))),
 CONST 0,
 L14,L15)
#
LABEL L14
MOVE(
 TEMP t2,
 CONST 1)
CJUMP(EQ,
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -16))),
   BINOP(MUL,
    BINOP(PLUS,
     MEM(
      BINOP(PLUS,
       TEMP sp,
       CONST -8)),
     MEM(
      BINOP(PLUS,
       MEM(
        BINOP(PLUS,
         TEMP sp,
         CONST 0)),
       CONST 4))),
    CONST 4))),
 CONST 0,
 L26,L27)
#
LABEL L27
MOVE(
 TEMP t2,
 CONST 0)
JUMP(
 NAME L26)
#
LABEL L26
MOVE(
 TEMP t1,
 TEMP t2)
JUMP(
 NAME L16)
#
LABEL L15
MOVE(
 TEMP t1,
 CONST 0)
JUMP(
 NAME L16)
#
LABEL L16
CJUMP(EQ,
 TEMP t1,
 CONST 0,
 L17,L18)
#
LABEL L17
MOVE(
 TEMP t3,
 CONST 1)
CJUMP(EQ,
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -20))),
   BINOP(MUL,
    BINOP(MINUS,
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST -8)),
      CONST 7),
     MEM(
      BINOP(PLUS,
       MEM(
        BINOP(PLUS,
         TEMP sp,
         CONST 0)),
       CONST 4))),
    CONST 4))),
 CONST 0,
 L28,L29)
#
LABEL L29
MOVE(
 TEMP t3,
 CONST 0)
JUMP(
 NAME L28)
#
LABEL L28
MOVE(
 TEMP t0,
 TEMP t3)
JUMP(
 NAME L19)
#
LABEL L18
MOVE(
 TEMP t0,
 CONST 0)
JUMP(
 NAME L19)
#
LABEL L19
CJUMP(EQ,
 TEMP t0,
 CONST 0,
 L20,L21)
#
LABEL L20
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -8))),
   BINOP(MUL,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST -8)),
    CONST 4))),
 CONST 1)
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -16))),
   BINOP(MUL,
    BINOP(PLUS,
     MEM(
      BINOP(PLUS,
       TEMP sp,
       CONST -8)),
     CONST 1),
    CONST 4))),
 CONST 1)
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -20))),
   BINOP(MUL,
    BINOP(MINUS,
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST -8)),
      CONST 7),
     MEM(
      BINOP(PLUS,
       MEM(
        BINOP(PLUS,
         TEMP sp,
         CONST 0)),
       CONST 4))),
    CONST 4))),
 CONST 1)
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -12))),
   BINOP(MUL,
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST 4)),
    CONST 4))),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -8)))
EXP(
 CALL(
  NAME L0,
   MEM(
    BINOP(PLUS,
     TEMP sp,
     CONST 0)),
   BINOP(PLUS,
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST 4)),
    CONST 1)))
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -8))),
   BINOP(MUL,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST -8)),
    CONST 4))),
 CONST 0)
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -16))),
   BINOP(MUL,
    BINOP(PLUS,
     MEM(
      BINOP(PLUS,
       TEMP sp,
       CONST -8)),
     MEM(
      BINOP(PLUS,
       MEM(
        BINOP(PLUS,
         TEMP sp,
         CONST 0)),
       CONST 4))),
    CONST 4))),
 CONST 0)
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -20))),
   BINOP(MUL,
    BINOP(MINUS,
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST -8)),
      CONST 7),
     MEM(
      BINOP(PLUS,
       MEM(
        BINOP(PLUS,
         TEMP sp,
         CONST 0)),
       CONST 4))),
    CONST 4))),
 CONST 0)
JUMP(
 NAME L22)
#
LABEL L21
JUMP(
 NAME L22)
#
LABEL L22
CJUMP(GE,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -8)),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -12)),
 L23,L24)
#
LABEL L23
JUMP(
 NAME L13)
#
LABEL L109
JUMP(
 NAME L25)
#
LABEL L24
JUMP(
 NAME L25)
#
LABEL L25
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -8)),
 BINOP(PLUS,
  MEM(
   BINOP(PLUS,
    TEMP sp,
    CONST -8)),
  CONST 1))
JUMP(
 NAME L30)
#
LABEL L13
JUMP(
 NAME L36)
#
LABEL L35
JUMP(
 NAME L36)
#
LABEL L36
JUMP(
 NAME L39)
#
LABEL L39
JUMP(
 NAME L106)
LABEL L106
# Trace Scheduled: 
LABEL L107
CJUMP(EQ,
 MEM(
  BINOP(PLUS,
   MEM(
    BINOP(PLUS,
     TEMP sp,
     CONST 0)),
   CONST 4)),
 MEM(
  BINOP(PLUS,
   MEM(
    BINOP(PLUS,
     TEMP sp,
     CONST 0)),
   CONST -4)),
 L37,L38)
LABEL L38
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -8)),
 CONST 0)
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -12)),
 BINOP(MINUS,
  MEM(
   BINOP(PLUS,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST 0)),
    CONST -4)),
  CONST 1))
CJUMP(LE,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -8)),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -12)),
 L34,L35)
LABEL L35
LABEL L36
LABEL L39
JUMP(
 NAME L106)
LABEL L37
EXP(
 CALL(
  NAME L1,
   MEM(
    BINOP(PLUS,
     TEMP sp,
     CONST 0))))
JUMP(
 NAME L39)
LABEL L34
LABEL L30
CJUMP(EQ,
 CONST 1,
 CONST 0,
 L31,L32)
LABEL L32
LABEL L33
CJUMP(EQ,
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -8))),
   BINOP(MUL,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST -8)),
    CONST 4))),
 CONST 0,
 L14,L15)
LABEL L15
MOVE(
 TEMP t1,
 CONST 0)
LABEL L16
CJUMP(EQ,
 TEMP t1,
 CONST 0,
 L17,L18)
LABEL L18
MOVE(
 TEMP t0,
 CONST 0)
LABEL L19
CJUMP(EQ,
 TEMP t0,
 CONST 0,
 L20,L21)
LABEL L21
LABEL L22
CJUMP(GE,
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -8)),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -12)),
 L23,L24)
LABEL L24
LABEL L25
MOVE(
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -8)),
 BINOP(PLUS,
  MEM(
   BINOP(PLUS,
    TEMP sp,
    CONST -8)),
  CONST 1))
JUMP(
 NAME L30)
LABEL L31
LABEL L13
JUMP(
 NAME L36)
LABEL L108
JUMP(
 NAME L33)
LABEL L14
MOVE(
 TEMP t2,
 CONST 1)
CJUMP(EQ,
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -16))),
   BINOP(MUL,
    BINOP(PLUS,
     MEM(
      BINOP(PLUS,
       TEMP sp,
       CONST -8)),
     MEM(
      BINOP(PLUS,
       MEM(
        BINOP(PLUS,
         TEMP sp,
         CONST 0)),
       CONST 4))),
    CONST 4))),
 CONST 0,
 L26,L27)
LABEL L27
MOVE(
 TEMP t2,
 CONST 0)
LABEL L26
MOVE(
 TEMP t1,
 TEMP t2)
JUMP(
 NAME L16)
LABEL L17
MOVE(
 TEMP t3,
 CONST 1)
CJUMP(EQ,
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -20))),
   BINOP(MUL,
    BINOP(MINUS,
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST -8)),
      CONST 7),
     MEM(
      BINOP(PLUS,
       MEM(
        BINOP(PLUS,
         TEMP sp,
         CONST 0)),
       CONST 4))),
    CONST 4))),
 CONST 0,
 L28,L29)
LABEL L29
MOVE(
 TEMP t3,
 CONST 0)
LABEL L28
MOVE(
 TEMP t0,
 TEMP t3)
JUMP(
 NAME L19)
LABEL L20
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -8))),
   BINOP(MUL,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST -8)),
    CONST 4))),
 CONST 1)
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -16))),
   BINOP(MUL,
    BINOP(PLUS,
     MEM(
      BINOP(PLUS,
       TEMP sp,
       CONST -8)),
     CONST 1),
    CONST 4))),
 CONST 1)
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -20))),
   BINOP(MUL,
    BINOP(MINUS,
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST -8)),
      CONST 7),
     MEM(
      BINOP(PLUS,
       MEM(
        BINOP(PLUS,
         TEMP sp,
         CONST 0)),
       CONST 4))),
    CONST 4))),
 CONST 1)
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -12))),
   BINOP(MUL,
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST 4)),
    CONST 4))),
 MEM(
  BINOP(PLUS,
   TEMP sp,
   CONST -8)))
EXP(
 CALL(
  NAME L0,
   MEM(
    BINOP(PLUS,
     TEMP sp,
     CONST 0)),
   BINOP(PLUS,
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST 4)),
    CONST 1)))
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -8))),
   BINOP(MUL,
    MEM(
     BINOP(PLUS,
      TEMP sp,
      CONST -8)),
    CONST 4))),
 CONST 0)
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -16))),
   BINOP(MUL,
    BINOP(PLUS,
     MEM(
      BINOP(PLUS,
       TEMP sp,
       CONST -8)),
     MEM(
      BINOP(PLUS,
       MEM(
        BINOP(PLUS,
         TEMP sp,
         CONST 0)),
       CONST 4))),
    CONST 4))),
 CONST 0)
MOVE(
 MEM(
  BINOP(PLUS,
   MEM(
    MEM(
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST 0)),
      CONST -20))),
   BINOP(MUL,
    BINOP(MINUS,
     BINOP(PLUS,
      MEM(
       BINOP(PLUS,
        TEMP sp,
        CONST -8)),
      CONST 7),
     MEM(
      BINOP(PLUS,
       MEM(
        BINOP(PLUS,
         TEMP sp,
         CONST 0)),
       CONST 4))),
    CONST 4))),
 CONST 0)
JUMP(
 NAME L22)
LABEL L23
JUMP(
 NAME L13)
LABEL L109
JUMP(
 NAME L25)
LABEL L106
# Instructions: 
Tree.LABEL@50d89c:
movl 0, t90
addl sp, t90
movl (t90), t89
movl 4, t91
addl t89, t91
movl (t91), t88
movl 0, t94
addl sp, t94
movl (t94), t93
movl -4, t95
addl t93, t95
movl (t95), t92
movl L37, t96
cmpl t88, t92
je L37
Tree.LABEL@1bd0dd4:
movl 0, t97
movl t97, -8(sp)
movl 0, t100
addl sp, t100
movl (t100), t99
movl -4, t101
addl t99, t101
movl (t101), t98
movl 1, t102
subl t98, t98
movl t102, -12(sp)
movl -8, t104
addl sp, t104
movl (t104), t103
movl -12, t106
addl sp, t106
movl (t106), t105
movl L34, t107
cmpl t103, t105
jle L34
Tree.LABEL@d70d7a:
Tree.LABEL@b5f53a:
Tree.LABEL@1f6f0bf:
movl L106, t108
jmp *t108
Tree.LABEL@137c60d:
movl L1, t109
movl 0, t111
addl sp, t111
movl (t111), t110
pushl t110
call *t109
movl L39, t112
jmp *t112
Tree.LABEL@ab853b:
Tree.LABEL@b82368:
movl 1, t113
movl 0, t114
movl L31, t115
cmpl t113, t114
je L31
Tree.LABEL@11c8a71:
Tree.LABEL@c53dce:
movl 0, t120
addl sp, t120
movl (t120), t119
movl -8, t121
addl t119, t121
movl (t121), t118
movl (t118), t117
movl -8, t123
addl sp, t123
movl (t123), t122
movl 4, t124
movl t122, eax
mull t124
addl t117, eax
movl (eax), t116
movl 0, t125
movl L14, t126
cmpl t116, t125
je L14
Tree.LABEL@15cda3f:
movl 0, t127
movl t127, t1
Tree.LABEL@fc9944:
movl 0, t128
movl L17, t129
cmpl t1, t128
je L17
Tree.LABEL@1b26af3:
movl 0, t130
movl t130, t0
Tree.LABEL@8b819f:
movl 0, t131
movl L20, t132
cmpl t0, t131
je L20
Tree.LABEL@eb017e:
Tree.LABEL@aeffdf:
movl -8, t134
addl sp, t134
movl (t134), t133
movl -12, t136
addl sp, t136
movl (t136), t135
movl L23, t137
cmpl t133, t135
jge L23
Tree.LABEL@120a47e:
Tree.LABEL@f73c1:
movl -8, t139
addl sp, t139
movl (t139), t138
movl 1, t140
addl t138, t140
movl t140, -8(sp)
movl L30, t141
jmp *t141
Tree.LABEL@789144:
Tree.LABEL@1893efe:
movl L36, t142
jmp *t142
Tree.LABEL@186c6b2:
movl L33, t143
jmp *t143
Tree.LABEL@15ee671:
movl 1, t144
movl t144, t2
movl 0, t149
addl sp, t149
movl (t149), t148
movl -16, t150
addl t148, t150
movl (t150), t147
movl (t147), t146
movl -8, t152
addl sp, t152
movl (t152), t151
movl 0, t155
addl sp, t155
movl (t155), t154
movl 4, t156
addl t154, t156
movl (t156), t153
addl t151, t153
movl 4, t157
movl t153, eax
mull t157
addl t146, eax
movl (eax), t145
movl 0, t158
movl L26, t159
cmpl t145, t158
je L26
Tree.LABEL@16b13c7:
movl 0, t160
movl t160, t2
Tree.LABEL@df8f5e:
movl t2, t1
movl L16, t161
jmp *t161
Tree.LABEL@13d93f4:
movl 1, t162
movl t162, t3
movl 0, t167
addl sp, t167
movl (t167), t166
movl -20, t168
addl t166, t168
movl (t168), t165
movl (t165), t164
movl -8, t170
addl sp, t170
movl (t170), t169
movl 7, t171
addl t169, t171
movl 0, t174
addl sp, t174
movl (t174), t173
movl 4, t175
addl t173, t175
movl (t175), t172
subl t171, t171
movl 4, t176
movl t172, eax
mull t176
addl t164, eax
movl (eax), t163
movl 0, t177
movl L28, t178
cmpl t163, t177
je L28
Tree.LABEL@1bca5f1:
movl 0, t179
movl t179, t3
Tree.LABEL@329f3d:
movl t3, t0
movl L19, t180
jmp *t180
Tree.LABEL@1749757:
movl 1, t181
movl 0, t185
addl sp, t185
movl (t185), t184
movl -8, t186
addl t184, t186
movl (t186), t183
movl (t183), t182
movl -8, t188
addl sp, t188
movl (t188), t187
movl 4, t189
movl t187, eax
mull t189
addl t182, eax
movl (t181), eax
movl 1, t190
movl 0, t194
addl sp, t194
movl (t194), t193
movl -16, t195
addl t193, t195
movl (t195), t192
movl (t192), t191
movl -8, t197
addl sp, t197
movl (t197), t196
movl 1, t198
addl t196, t198
movl 4, t199
movl t198, eax
mull t199
addl t191, eax
movl (t190), eax
movl 1, t200
movl 0, t204
addl sp, t204
movl (t204), t203
movl -20, t205
addl t203, t205
movl (t205), t202
movl (t202), t201
movl -8, t207
addl sp, t207
movl (t207), t206
movl 7, t208
addl t206, t208
movl 0, t211
addl sp, t211
movl (t211), t210
movl 4, t212
addl t210, t212
movl (t212), t209
subl t208, t208
movl 4, t213
movl t209, eax
mull t213
addl t201, eax
movl (t200), eax
movl -8, t215
addl sp, t215
movl (t215), t214
movl 0, t219
addl sp, t219
movl (t219), t218
movl -12, t220
addl t218, t220
movl (t220), t217
movl (t217), t216
movl 0, t223
addl sp, t223
movl (t223), t222
movl 4, t224
addl t222, t224
movl (t224), t221
movl 4, t225
movl t221, eax
mull t225
addl t216, eax
movl (t214), eax
movl L0, t226
movl 0, t228
addl sp, t228
movl (t228), t227
movl 0, t231
addl sp, t231
movl (t231), t230
movl 4, t232
addl t230, t232
movl (t232), t229
movl 1, t233
addl t229, t233
pushl t233
pushl t227
call *t226
movl 0, t234
movl 0, t238
addl sp, t238
movl (t238), t237
movl -8, t239
addl t237, t239
movl (t239), t236
movl (t236), t235
movl -8, t241
addl sp, t241
movl (t241), t240
movl 4, t242
movl t240, eax
mull t242
addl t235, eax
movl (t234), eax
movl 0, t243
movl 0, t247
addl sp, t247
movl (t247), t246
movl -16, t248
addl t246, t248
movl (t248), t245
movl (t245), t244
movl -8, t250
addl sp, t250
movl (t250), t249
movl 0, t253
addl sp, t253
movl (t253), t252
movl 4, t254
addl t252, t254
movl (t254), t251
addl t249, t251
movl 4, t255
movl t251, eax
mull t255
addl t244, eax
movl (t243), eax
movl 0, t256
movl 0, t260
addl sp, t260
movl (t260), t259
movl -20, t261
addl t259, t261
movl (t261), t258
movl (t258), t257
movl -8, t263
addl sp, t263
movl (t263), t262
movl 7, t264
addl t262, t264
movl 0, t267
addl sp, t267
movl (t267), t266
movl 4, t268
addl t266, t268
movl (t268), t265
subl t264, t264
movl 4, t269
movl t265, eax
mull t269
addl t257, eax
movl (t256), eax
movl L22, t270
jmp *t270
Tree.LABEL@17bd6a1:
movl L13, t271
jmp *t271
Tree.LABEL@147ee05:
movl L25, t272
jmp *t272
Tree.LABEL@15b9e68:
