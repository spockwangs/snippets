package Mips;

public class MipsFrame extends Frame.Frame {
    int local_offset = 0;       // max offset of local var

    public MipsFrame() {
        name = new Temp.Label("tigermain");
        formals = null;
    }

    MipsFrame(Temp.Label n, Util.BoolList f) {
        name = n;
        formals = boolList2accessList(f, 0);
    }
    
    public MipsFrame newFrame(Temp.Label name, Util.BoolList f) {
        return new MipsFrame(name, f);
    }

    public Frame.Access allocLocal(boolean escape) {
        if (escape) {
            local_offset -= wordSize();
            return new InFrame(local_offset);
        } else
            return new InReg(new Temp.Temp());
    }

    public Frame.Access accessParam(int i) {
        return new InFrame(wordSize() * (i+2));
    }
                           
    public Tree.Stm procEntryExit1(Tree.Stm body) {
        // TODO
        assert (body != null) : "Function body cannot be null";

        // Generate store instructions to save callee-save registers and
        // load instructions to store them.
        Tree.Exp fp = new Tree.TEMP(FP());
        for (Temp.TempList p = Codegen.calleesaves; p != null; p = p.tail) {
            Frame.Access acc = allocLocal(true);
            Tree.MOVE store = new Tree.MOVE(acc.exp(fp), new Tree.TEMP(p.head));
            Tree.MOVE load = new Tree.MOVE(new Tree.TEMP(p.head), acc.exp(fp));
            body = new Tree.SEQ(store, body);
            body = new Tree.SEQ(body, load);
        }

        // Generate instructions to return the value of this function.
        
        return body;
    }

    public Assem.InstrList procEntryExit2(Assem.InstrList body) {
        return append(body,
                      new Assem.InstrList(new Assem.OPER("",
                                                         null,
                                                         Codegen.returnSink),
                                          null));
    }

    public Frame.Proc procEntryExit3(Assem.InstrList body) {
        String prologue, epilogue;

        prologue = ".globl " + name.toString() + "\n";
        prologue += name.toString() + ":\n";
        prologue += "    pushl %ebp\n";
        prologue += "    movl %esp, %ebp\n";
        prologue += "    addl $" + local_offset + ", %esp\n";

        epilogue = "    leave\n";
        epilogue += "    ret\n";
        
        return new Frame.Proc(prologue, body, epilogue);
                                  
    }
    
    public String string(Temp.Label lab, String str) {
        return lab.toString() + ":  .string " + str + "\n";
    }

    public int wordSize() {
        return 4;
    }

    public Tree.Exp externalCall(String func, Tree.ExpList args) {
        return new Tree.CALL(new Tree.NAME(new Temp.Label(func)), args);
    }

    public Temp.Temp FP() {
        return Codegen.ebp;
    }

    public Temp.Temp RV() {
        return Codegen.eax;
    }

    public Temp.TempList registers() {
        return Codegen.allregs;
    }
    
    /**
     * Concatecate 2 instruction list.
     */
    static Assem.InstrList append(Assem.InstrList a, Assem.InstrList b) {
        if (a == null)
            return b;
        else {
            Assem.InstrList p;
            for (p = a; p.tail != null; p = p.tail)
                /* do nothing */;
            p.tail = b;
            return a;
        }
    }

    /**
     * Return name for special registers, or null for others.
     */
    public String tempMap(Temp.Temp t) {
        if (t == Codegen.eax)
            return "%eax";
        if (t == Codegen.ebx)
            return "%ebx";
        if (t == Codegen.ecx)
            return "%ecx";
        if (t == Codegen.edx)
            return "%edx";
        if (t == Codegen.ebp)
            return "%ebp";
        if (t == Codegen.esp)
            return "%esp";
        if (t == Codegen.esi)
            return "%esi";
        if (t == Codegen.edi)
            return "%edi";
        return null;
    }

    public Assem.InstrList codegen(Tree.Stm stm) {
        return (new Codegen(this)).codegen(stm);
    }

    private Frame.AccessList boolList2accessList(Util.BoolList bl, int o) {
        if (bl == null)
            return null;
        
        Frame.Access a;
        if (bl.head) {
            a = new InFrame(o);
        } else {
            a = new InReg(new Temp.Temp());
        }
        return new Frame.AccessList(a, boolList2accessList(bl.tail, o+4));
    }

    static private Temp.TempList L(Temp.Temp h, Temp.TempList t) {
        return new Temp.TempList(h, t);
    }
}


class InFrame extends Frame.Access {
    int offset;

    InFrame(int o) {
        offset = o;
    }

    /**
     * Return instructions to access this variable.
     *
     * @param framep frame pointer
     */
    public Tree.Exp exp(Tree.Exp framep) {
        return new Tree.MEM(new Tree.BINOP(Tree.BINOP.PLUS,
                                           framep,
                                           new Tree.CONST(offset)));
    }
}


class InReg extends Frame.Access {
    Temp.Temp temp;

    InReg(Temp.Temp t) {
        temp = t;
    }

    public Tree.Exp exp(Tree.Exp framep) {
        return new Tree.TEMP(temp);
    }
}