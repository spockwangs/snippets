/*
 * Codegen.java - Code generator
 *
 * Time-stamp: <2010-07-16 15:49:30 wbb>
 */

package Mips;

public class Codegen {
    Frame.Frame frame;

    static Temp.Temp eax = new Temp.Temp();
    static Temp.Temp ebx = new Temp.Temp();
    static Temp.Temp ecx = new Temp.Temp();
    static Temp.Temp edx = new Temp.Temp();
    static Temp.Temp ebp = new Temp.Temp();
    static Temp.Temp esp = new Temp.Temp();
    static Temp.Temp edi = new Temp.Temp();
    static Temp.Temp esi = new Temp.Temp();
    
    static Temp.TempList specialregs = L(ebp, L(esp, null));
    static Temp.TempList argregs = L(eax, null);
    static Temp.TempList calleesaves = L(ebx, L(edi, L(esi, null)));
    static Temp.TempList callersaves = L(ecx, L(edx, null));
    static Temp.TempList returnSink = L(esp, L(eax, calleesaves));
    static Temp.TempList allregs = L(eax, L(ebx, L(ecx, L(edx, L(ebp, L(esp, L(edi, L(esi, null))))))));

    public Codegen(Frame.Frame f) {
        frame = f;
    }

    private Assem.InstrList ilist = null, last = null;

    /**
     * Append a new instruction.
     */
    private void emit(Assem.Instr inst) {
        if (last != null) {
            // Append 'inst' at the end.
            last = last.tail = new Assem.InstrList(inst, null);
        } else {
            // Insert first instruction
            last = ilist = new Assem.InstrList(inst, null);
        }
    }

    /**
     * Translate IR languages to abstract assembly language.
     *
     * @param s Linearized tree statement so there is no SEQ or ESEQ nodes.
     */
    void munchStm(Tree.Stm s) {
        if (s instanceof Tree.MOVE) {
            munchMove((Tree.MOVE) s);
        } else if (s instanceof Tree.EXP) {
            munchEXP((Tree.EXP)s);
        } else if (s instanceof Tree.JUMP) {
            munchJump((Tree.JUMP) s);
        } else if (s instanceof Tree.CJUMP) {
            munchCjump((Tree.CJUMP) s);
        } else if (s instanceof Tree.LABEL) {
            munchLabel((Tree.LABEL) s);
        } else
            throw new Error("Bad Tree.Stm statement");
    }

    void munchMove(Tree.MOVE s) {
        if (s.dst instanceof Tree.MEM) {
            // MOVE(MEM, e)
            munchMove((Tree.MEM) s.dst, s.src);
        } else if (s.src instanceof Tree.MEM) {
            // MOVE(e, MEM)
            munchMove(s.dst, (Tree.MEM) s.src);
        } else if (s.src instanceof Tree.CALL &&
                   s.dst instanceof Tree.TEMP) {
            // MOVE(TEMP, CALL(f, args))
            munchMove((Tree.TEMP) s.dst, (Tree.CALL) s.src);
        } else {
            // MOVE(e1, e2)
            Temp.Temp r1 = munchExp(s.src);
            Temp.Temp r2 = munchExp(s.dst);
            emit(new Assem.MOVE("    movl %s0, %d0\n", r2, r1));
        }
    }

    /**
     * Translate move instruction "move m <- e".
     */
    void munchMove(Tree.MEM m, Tree.Exp e) {
        Temp.Temp r_src = munchExp(e);
        
        if (m.exp instanceof Tree.BINOP) {
            // Process special cases.

            Tree.BINOP bin_exp = (Tree.BINOP) m.exp;
            Temp.Temp r1;
            int i;
            if (bin_exp.binop == Tree.BINOP.PLUS) {
                // MOVE(MEM(+, e1, CONST), e2) or MOVE(MEM(+, CONST, e1), e2)
                if (bin_exp.right instanceof Tree.CONST) {
                    r1 = munchExp(bin_exp.left);
                    i = ((Tree.CONST) bin_exp.right).value;
                    emit(new Assem.OPER("    movl %s0, " + i + "(%s1)\n",
                                        null, L(r_src, L(r1, null))));
                    return;
                } else if (bin_exp.left instanceof Tree.CONST) {
                    r1 = munchExp(bin_exp.right);
                    i = ((Tree.CONST) bin_exp.left).value;
                    emit(new Assem.OPER("    movl %s0, " + i + "(%s1)\n",
                                        null, L(r_src, L(r1, null))));
                    return;
                }
            } else if (bin_exp.binop == Tree.BINOP.MINUS) {
                // MOVE(MEM(-, e1, CONST), e2)
                if (bin_exp.right instanceof Tree.CONST) {
                    r1 = munchExp(bin_exp.left);
                    i = ((Tree.CONST) bin_exp.right).value;
                    emit(new Assem.OPER("    movl %s0, " + (-i) + "(%s1)\n",
                                        null, L(r_src, L(r1, null))));
                    return;
                }
            }
        }

        Temp.Temp r_dst = munchExp(m.exp);
        emit(new Assem.OPER("    movl %s0, (%s1)\n", null, L(r_src, L(r_dst, null))));
    }

    /**
     * Translate a special move-exp.
     *
     * @param dst a tree exp which is not MEM
     */
    void munchMove(Tree.Exp dst, Tree.MEM m) {
        Temp.Temp r_dst = munchExp(dst);

        if (m.exp instanceof Tree.BINOP) {
            // Process special cases.

            Tree.BINOP bin_exp = (Tree.BINOP) m.exp;
            Temp.Temp r1;
            int i;
            if (bin_exp.binop == Tree.BINOP.PLUS) {
                // MOVE(MEM(+, e1, CONST), e2) or MOVE(MEM(+, CONST, e1), e2)
                if (bin_exp.right instanceof Tree.CONST) {
                    r1 = munchExp(bin_exp.left);
                    i = ((Tree.CONST) bin_exp.right).value;
                    emit(new Assem.OPER("    movl " + i + "(%s0), %d0\n",
                                        L(r_dst, null), L(r1, null)));
                    return;
                } else if (bin_exp.left instanceof Tree.CONST) {
                    r1 = munchExp(bin_exp.right);
                    i = ((Tree.CONST) bin_exp.left).value;
                    emit(new Assem.OPER("    movl " + i + "(%s0), %d0\n",
                                        L(r_dst, null), L(r1, null)));
                    return;
                }
            } else if (bin_exp.binop == Tree.BINOP.MINUS) {
                // MOVE(MEM(-, e1, CONST), e2)
                if (bin_exp.right instanceof Tree.CONST) {
                    r1 = munchExp(bin_exp.left);
                    i = ((Tree.CONST) bin_exp.right).value;
                    emit(new Assem.OPER("    movl " + (-i) + "(%s0), %d0\n",
                                        L(r1, null), L(r_dst, null)));
                    return;
                }
            }
        }

        Temp.Temp r_src = munchMem(m);
        emit(new Assem.MOVE("    movl %s0, %d0\n", r_dst, r_src));
    }

    void munchMove(Tree.TEMP t, Tree.CALL call) {
        Temp.Temp f = munchExp(call.func);
        Temp.TempList l = munchArgs(call.args);
        Temp.TempList calldefs = L(eax, callersaves);
        emit(new Assem.OPER("    call *%s0\n", calldefs, L(f, l)));
        emit(new Assem.MOVE("    movl %s0, %d0\n", t.temp, eax));
    }

    void munchEXP(Tree.EXP s) {
        if (s.exp instanceof Tree.CALL) {
            Tree.CALL ce = (Tree.CALL) s.exp;
            Temp.Temp r = munchExp(ce.func);
            Temp.TempList l = munchArgs(ce.args);
            Temp.TempList calldefs = L(frame.RV(), callersaves);
            emit(new Assem.OPER("    call *%s0\n",
                                calldefs, L(r, l)));
        } else {
            munchExp(s.exp);
        }
    }

    /**
     * Generate code to pass arguments to a function.
     */
    private Temp.TempList munchArgs(Tree.ExpList args) {
        if (args == null || args.head == null)
            return null;

        /*
         * Munch each argument and pass each result to a temp register.
         * Then accumulate them to a temp list in reverse order so that we
         * can push the first argument last.
         */
        Temp.TempList l = null;
        while (args != null && args.head != null) {
            l = new Temp.TempList(munchExp(args.head), l);
            args = args.tail;
        }

        /*
         * Push the arguments into stack.  The first argument is pushed last.
         */
        Temp.TempList p = l;    // saved for return
        while (l != null) {
            emit(new Assem.OPER("    pushl %s0\n", null, L(l.head, null)));
            l = l.tail;
        }

        return p;
    }
    
    void munchJump(Tree.JUMP s) {
        Temp.Temp r = munchExp(s.exp);
        emit(new Assem.OPER("    jmp *%s0\n", null, L(r, null), s.targets));
    }

    void munchCjump(Tree.CJUMP s) {
        Temp.Temp l, r;

        l = munchExp(s.left);
        r = munchExp(s.right);
        
        String instr;
        switch (s.relop) {
        case Tree.CJUMP.EQ:
            instr = "je ";
            break;
        case Tree.CJUMP.NE:
            instr = "jne ";
            break;
        case Tree.CJUMP.LT:
            instr = "jl ";
            break;
        case Tree.CJUMP.GT:
            instr = "jg ";
            break;
        case Tree.CJUMP.LE:
            instr = "jle ";
            break;
        case Tree.CJUMP.GE:
            instr = "jge ";
            break;
        case Tree.CJUMP.ULT:
            instr = "jb ";
            break;
        case Tree.CJUMP.ULE:
            instr = "jbe ";
            break;
        case Tree.CJUMP.UGT:
            instr = "ja ";
            break;
        case Tree.CJUMP.UGE:
            instr = "jae ";
            break;
        default:
            throw new Error("bad condition jump instruction");
        }

        emit(new Assem.OPER("    cmpl %s0, %s1\n",
                            null, L(r, L(l, null))));
        emit(new Assem.OPER("    " + instr + s.iftrue + "\n",
                            null, null, new Temp.LabelList(s.iftrue, new Temp.LabelList(s.iffalse, null))));
    }

    void munchLabel(Tree.LABEL s) {
        emit(new Assem.LABEL(s.label.toString() + ":\n", s.label));
    }

    /**
     * Translate tree languages to abstract assembly languages.
     *
     * @param e linearized tree languages
     * @return a temp register holding the result
     */
    Temp.Temp munchExp(Tree.Exp e) {
        if (e instanceof Tree.CONST) {
            return munchConst((Tree.CONST) e);
        } else if (e instanceof Tree.NAME) {
            return munchName((Tree.NAME) e);
        } else if (e instanceof Tree.TEMP) {
            return munchTemp((Tree.TEMP) e);
        } else if (e instanceof Tree.BINOP) {
            return munchBinop((Tree.BINOP) e);
        } else if (e instanceof Tree.MEM) {
            return munchMem((Tree.MEM) e);
        } else {
            throw new Error("Bad tree exp");
        }
    }

    Temp.Temp munchConst(Tree.CONST e) {
        Temp.Temp r = new Temp.Temp();
        emit(new Assem.OPER("    movl $" + e.value + ", %d0\n",
                            L(r, null), null));
        return r;
    }

    Temp.Temp munchName(Tree.NAME e) {
        Temp.Temp r = new Temp.Temp();
        emit(new Assem.OPER("    movl $" + e.label.toString() + ", %d0\n",
                            L(r, null), null));
        return r;
    }

    Temp.Temp munchTemp(Tree.TEMP e) {
        return e.temp;
    }

    Temp.Temp munchBinop(Tree.BINOP e) {
        Temp.Temp l, r, result;

        l = munchExp(e.left);
        r = munchExp(e.right);
        switch (e.binop) {
        case Tree.BINOP.PLUS:
            emit(new Assem.OPER("    addl %s0, %d0\n",
                                L(r, null), L(l, L(r, null))));
            return r;
        case Tree.BINOP.MINUS:
            emit(new Assem.OPER("    subl %s0, %d0\n",
                                L(l, null), L(r, L(l, null))));
            return l;
        case Tree.BINOP.MUL:
            emit(new Assem.MOVE("    movl %s0, %d0\n",
                                eax, l));
            emit(new Assem.OPER("    mull %s0\n",
                                L(eax, L(edx, null)), L(r, null)));
            return eax;
        default:
            throw new Error("not implemented yet");
        }
    }

    Temp.Temp munchMem(Tree.MEM e) {
        Temp.Temp r = new Temp.Temp();
        emit(new Assem.OPER("    movl (%s0), %d0\n",
                            L(r, null), L(munchExp(e.exp), null)));
        return r;
    }

    public Assem.InstrList codegen(Tree.Stm s) {
        Assem.InstrList l;
        munchStm(s);
        l = ilist;
        ilist = last = null;
        return l;
    }

    static private Temp.TempList L(Temp.Temp h, Temp.TempList t) {
        return new Temp.TempList(h, t);
    }
}
