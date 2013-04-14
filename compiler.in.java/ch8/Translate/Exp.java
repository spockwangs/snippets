/*
 * Exp.java - Translate exp to IR
 *
 * Time-stamp: <2010-07-02 17:47:26 wbb>
 */

package Translate;

import Temp.Label;
import Temp.Temp;

abstract public class Exp {
    abstract Tree.Exp unEx();
    abstract Tree.Stm unNx();
    abstract Tree.Stm unCx(Label t, Label f);
}


class Ex extends Exp {
    Tree.Exp exp;

    Ex(Tree.Exp e) {
        exp = e;
    }

    Tree.Exp unEx() {
        return exp;
    }

    Tree.Stm unNx() {
        return new Tree.EXP(exp);
    }

    Tree.Stm unCx(Label t, Label f) {
        return new Tree.CJUMP(Tree.CJUMP.EQ, exp, new Tree.CONST(0), t, f);
    }
}


class Nx extends Exp {
    Tree.Stm stm;

    Nx(Tree.Stm s) {
        stm = s;
    }

    Tree.Exp unEx() {
        throw new Error("valueless exp converted to an value-exp");
    }

    Tree.Stm unNx() {
        return stm;
    }

    Tree.Stm unCx(Label t, Label f) {
        throw new Error("valueless exp converted to condition exp");
    }
}


abstract class Cx extends Exp {
    Tree.Exp unEx() {
        Temp r = new Temp();
        Label t = new Label();
        Label f = new Label();

        return new Tree.ESEQ(new Tree.SEQ(new Tree.MOVE(new Tree.TEMP(r), new Tree.CONST(1)),
                                          new Tree.SEQ(unCx(t, f),
                                                       new Tree.SEQ(new Tree.LABEL(f),
                                                                    new Tree.SEQ(new Tree.MOVE(new Tree.TEMP(r),
                                                                                               new Tree.CONST(0)),
                                                                                 new Tree.LABEL(t))))),
                             new Tree.TEMP(r));
    }

    Tree.Stm unNx() {
        Label l = new Label();
        return new Tree.SEQ(unCx(l, l), new Tree.LABEL(l));
    }

    abstract Tree.Stm unCx(Label t, Label f);
}


class RelCx extends Cx {
    private Tree.Exp left, right;
    private int operator;   // Tree.CJUMP.LT, etc.

    RelCx(int op, Tree.Exp l, Tree.Exp r) {
        operator = op;
        left = l;
        right = r;
    }

    Tree.Stm unCx(Label t, Label f) {
        return new Tree.CJUMP(operator, left, right, t, f);
    }
}


class IfThenElseExp extends Exp {
    Exp cond, a, b;             // b may be null
    Label t = new Label();
    Label f = new Label();
    Label join = new Label();

    IfThenElseExp(Exp cc, Exp aa, Exp bb) {
        cond = cc;
        a = aa;
        b = bb;
    }

    Tree.Stm unCx(Label tt, Label ff) {
        return new Tree.CJUMP(Tree.CJUMP.EQ, unEx(), new Tree.CONST(0), tt, ff);        
    }

    /**
     * Translate to a value exp.
     *     cond, t, f
     *  t:
     *     r <- a
     *     jump join
     *  f:
     *     r <- b
     *  join:
     */
    Tree.Exp unEx() {
        assert (b != null) : "The false-exp of If-exp should not be null";
        
        Temp r = new Temp();
        Tree.Stm test_stm = cond.unCx(t, f);
        Tree.Stm true_stm = new Tree.SEQ(new Tree.MOVE(new Tree.TEMP(r), a.unEx()),
                                         new Tree.JUMP(join));
        Tree.Stm false_stm = new Tree.MOVE(new Tree.TEMP(r), b.unEx());

        // Accumulate all these statements from the end.
        Tree.Stm stm = new Tree.SEQ(false_stm, new Tree.LABEL(join));
        stm = new Tree.SEQ(new Tree.LABEL(f), stm);
        stm = new Tree.SEQ(true_stm, stm);
        stm = new Tree.SEQ(new Tree.LABEL(t), stm);
        stm = new Tree.SEQ(test_stm, stm);
        
        return new Tree.ESEQ(stm, new Tree.TEMP(r));
    }

    /**
     * Translate to a valueless exp.
     */
    Tree.Stm unNx() {
        /*
         * Similar as unEx(), except that do not has 'r' as the value.
         * Note: 'b' may be null.
         */
        
        Tree.Stm test_stm = cond.unCx(t, f);
        Tree.Stm true_stm = new Tree.SEQ(a.unNx(), new Tree.JUMP(join));
        Tree.Stm false_stm = b == null ? null : b.unNx();

        // Accumulate all these statements from the end.
        Tree.Stm stm = false_stm == null ?
            new Tree.LABEL(join) : new Tree.SEQ(false_stm, new Tree.LABEL(join));
        stm = new Tree.SEQ(new Tree.LABEL(f), stm);
        stm = new Tree.SEQ(true_stm, stm);
        stm = new Tree.SEQ(new Tree.LABEL(t), stm);
        stm = new Tree.SEQ(test_stm, stm);
        return stm;
    }
}