package Mips;

public class MipsFrame extends Frame.Frame {
    int local_offset = 0;       // max offset of local var
    
    public MipsFrame() {
        // do nothing
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
            local_offset -= machine.wordSize();
            return new InFrame(local_offset);
        } else
            return new InReg(new Temp.Temp());
    }

    public Frame.Access accessParam(int i) {
        return new InFrame(machine.wordSize() * i);
    }
                           
    Frame.AccessList boolList2accessList(Util.BoolList bl, int o) {
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

    public Tree.Stm procEntryExit1(Tree.Stm body) {
        // TODO
        assert (body != null) : "Function body cannot be null";

        // Generate store instructions to save callee-save registers.

        // Generate instructions to return the value of this function.

        return body;            // for testing
    }
}


class InFrame extends Frame.Access {
    int offset;

    InFrame(int o) {
        offset = o;
    }

    /**
     * Return instructions to access this variable.
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