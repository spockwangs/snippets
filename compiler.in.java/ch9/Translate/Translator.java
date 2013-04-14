
package Translate;

import Temp.Label;
import Temp.Temp;

public class Translator {
    private Frag frags;
    private Frame.Frame frame;
    
    // Natural word size (in bytes) of target machine.
    static int wordSize = Frame.Frame.machine.wordSize();

    public Translator(Frame.Frame f) {
        frame = f;
    }
    
    public void procEntryExit(Level level, Exp body) {
        frags = new Translate.ProcFrag(level.frame.procEntryExit1(body.unNx()), level.frame, frags);
    }

    public Frag getResult() {
        return frags;
    }

    public Tree.Stm irFromExp(Exp e) {
        return e.unNx();
    }
    
    /**
     * Generate IR of accessing a simple var.
     *
     * The level 'l' is where this variable is accessed, not where it is declared.
     */
    public Exp simpleVar(Access a, Level l) {
        if (a == null || l == null)
            return null;
        
        // Calculate the frame pointer where the variable is declared.
        Tree.Exp fp = new Tree.TEMP(Frame.Frame.machine.FP()); // frame pointer of this level
        while (l != a.home) {
            fp = l.formals.head.acc.exp(fp);
            l = l.parent;
        }

        return new Ex(a.acc.exp(fp));
    }

    public Exp subscriptVar(Exp var, Exp idx) {
        if (var == null || idx == null)
            return null;

        return new Ex(new Tree.MEM(new Tree.BINOP(Tree.BINOP.PLUS,
                                                  new Tree.MEM(var.unEx()),
                                                  new Tree.BINOP(Tree.BINOP.MUL,
                                                                 idx.unEx(),
                                                                 new Tree.CONST(wordSize)))));
    }

    public Exp fieldVar(Exp var, Exp idx) {
        if (var == null || idx == null)
            return null;
        
        return subscriptVar(var, idx);
    }

    /**
     * It is a runtime checked error to use Nil exp to access a record
     * field. So it is acceptable to use 0 to represent it.  When running
     * it will invoke segmentation fault.
     */
    public Exp nilExp() {
        return new Ex(new Tree.CONST(0));
    }

    public Exp intExp(int i) {
        return new Ex(new Tree.CONST(i));
    }

    public Exp stringExp(String s) {
        Label l = new Label();
        frags = new Translate.DataFrag(frame.string(l, s), frags);
        return new Ex(new Tree.NAME(l));
    }

    public Exp callExp(Label name, Level dec_level, Level call_level, ExpList explist) {
        if (name == null || dec_level == null || call_level == null || explist == null)
            return null;
        
        // Arguments.
        Tree.ExpList el = trans2tree(explist);

        // Calculate the static link.
        Level l = call_level;
        Tree.Exp sl = new Tree.TEMP(Frame.Frame.machine.FP());
        while (l != dec_level) {
            sl = l.formals.head.acc.exp(sl); // access static link
            l = l.parent;
        }

        return new Ex(new Tree.CALL(new Tree.NAME(name),
                                    new Tree.ExpList(sl, el)));
    }

    /**
     * Convert Translate.ExpList to Tree.ExpList.
     */
    private static Tree.ExpList trans2tree(Translate.ExpList el) {
        if (el == null || el.head == null)
            return null;
        else
            return new Tree.ExpList(el.head.unEx(), trans2tree(el.tail));
    }
    
    /**
     * 'operator' is Absyn.OpExp.PLUS, etc.
     */
    public Exp opExp(int operator, Exp left, Exp right) {
        if (left == null || right == null)
            return null;
        
        switch (operator) {
        case Absyn.OpExp.PLUS:
            return new Ex(new Tree.BINOP(Tree.BINOP.PLUS, left.unEx(), right.unEx()));
        case Absyn.OpExp.MINUS:
            return new Ex(new Tree.BINOP(Tree.BINOP.MINUS, left.unEx(), right.unEx()));
        case Absyn.OpExp.MUL:
            return new Ex(new Tree.BINOP(Tree.BINOP.MUL, left.unEx(), right.unEx()));
        case Absyn.OpExp.DIV:
            return new Ex(new Tree.BINOP(Tree.BINOP.DIV, left.unEx(), right.unEx()));
        case Absyn.OpExp.EQ:
            return new RelCx(Tree.CJUMP.EQ, left.unEx(), right.unEx());
        case Absyn.OpExp.NE:
            return new RelCx(Tree.CJUMP.NE, left.unEx(), right.unEx());
        case Absyn.OpExp.LT:
            return new RelCx(Tree.CJUMP.LT, left.unEx(), right.unEx());
        case Absyn.OpExp.LE:
            return new RelCx(Tree.CJUMP.LE, left.unEx(), right.unEx());
        case Absyn.OpExp.GT:
            return new RelCx(Tree.CJUMP.GT, left.unEx(), right.unEx());
        case Absyn.OpExp.GE:
            return new RelCx(Tree.CJUMP.GE, left.unEx(), right.unEx());
        default:
            throw new Error("in Translate.opExp: unrecognized operator");
        }
    }

    /**
     * Genrate instructions to create a record and initialize each field
     * from the init expressions 'el'.
     */
    public Exp recordExp(ExpList el) {
        if (el == null)
            return null;
        
        Tree.TEMP r = new Tree.TEMP(new Temp());

        int n = 0;

        for (ExpList p = el; p != null; p = p.tail) {
            n++;
        }

        Tree.ExpList args = new Tree.ExpList(new Tree.CONST(n*wordSize), null);
        Tree.Exp alloc_exp = Frame.Frame.machine.externalCall("malloc", args);

        Tree.Stm exp = new Tree.MOVE(r, alloc_exp);
        exp = new Tree.SEQ(exp, seqExp(el).unNx());
        return new Ex(new Tree.ESEQ(exp, r));
    }

    public Exp seqExp(ExpList el) {
        if (el == null)
            return null;
        
        // Void exp
        if (el.head == null)
            return new Ex(new Tree.CONST(0));

        if (el.tail == null)
            return el.head;
        else 
            return new Nx(new Tree.SEQ(el.head.unNx(), seqExp(el.tail).unNx()));
    }

    public Exp assignExp(Exp l, Exp r) {
        if (l == null || r == null)
            return null;
        return new Nx(new Tree.MOVE(l.unEx(), r.unEx()));
    }
    
    /**
     * 'false_exp' may be null.
     */
    public Exp ifExp(Exp cond, Exp true_exp, Exp false_exp) {
        if (cond == null || true_exp == null)
            return null;
        return new IfThenElseExp(cond, true_exp, false_exp);
    }

    public Exp whileExp(Exp cond, Exp body, Label done) {
        if (cond == null || body == null || done == null)
            return null;
        
        Tree.Stm testStm, ifStm, bodyStm, loopStm, doneStm;
        Exp if_exp;
        Label test = new Label();

        testStm = new Tree.LABEL(test);
        if_exp = new IfThenElseExp(opExp(Absyn.OpExp.EQ, cond, intExp(0)),
                                   new Nx(new Tree.JUMP(done)),
                                   null);
        ifStm = if_exp.unNx();
        bodyStm = body.unNx();
        loopStm = new Tree.JUMP(test);
        doneStm = new Tree.LABEL(done);
        return new Nx(new Tree.SEQ(testStm,
                                   new Tree.SEQ(ifStm,
                                                new Tree.SEQ(bodyStm,
                                                             new Tree.SEQ(loopStm, doneStm)))));
    }

    public Exp breakExp(Label done) {
        if (done == null)
            return null;
        return new Nx(new Tree.JUMP(done));
    }

    public Exp letExp(ExpList dec_list, Exp body) {
        if (dec_list == null || body == null)
            return null;
        
        Tree.Stm dec_stm = seqExp(dec_list).unNx();
        Tree.Stm body_stm = body.unNx();
        return new Nx(new Tree.SEQ(dec_stm, body_stm));
    }

    public Exp arrayExp(Exp size, Exp init) {
        if (size == null || init == null)
            return null;
        
        Tree.ExpList args = new Tree.ExpList(size.unEx(), new Tree.ExpList(init.unEx(), null));
        return new Ex(Frame.Frame.machine.externalCall("initArray", args));
    }

    public Exp functionDec(Level level, Exp body) {
        if (level == null || body == null)
            return null;
        
        Tree.Stm stm_body = body.unNx();
        Tree.Stm stm_fun = level.frame.procEntryExit1(stm_body);
        procEntryExit(level, body);

        return new Nx(stm_fun);
    }

    public Exp varDec(Access a, Level l, Exp init) {
        if (a == null || l == null || init == null)
            return null;
                
        Tree.Exp var = simpleVar(a, l).unEx();
        Tree.Stm assign = new Tree.MOVE(var, init.unEx());
        
        return new Nx(assign);
    }

    public Exp typeDec() {
        return new Ex(new Tree.CONST(0)); // just return a no-op
    }
}