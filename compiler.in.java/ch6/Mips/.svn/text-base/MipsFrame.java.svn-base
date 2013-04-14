package Mips;

public class MipsFrame extends Frame.Frame {
    int local_offset = 0;
    
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
            local_offset -= 4;
            return new InFrame(local_offset);
        } else
            return new InReg(new Temp.Temp());
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
}


class InFrame extends Frame.Access {
    int offset;

    InFrame(int o) {
        offset = o;
    }
}


class InReg extends Frame.Access {
    Temp.Temp temp;

    InReg(Temp.Temp t) {
        temp = t;
    }
}