package Frame;

import Temp.Temp;
import Temp.Label;
import Temp.TempMap;
import Temp.TempList;

public abstract class Frame implements TempMap {
    public Label name;
    public AccessList formals;
    
    abstract public Frame newFrame(Label name, Util.BoolList formals);
    abstract public Access allocLocal(boolean escape);
    abstract public Access accessParam(int i);
    abstract public Assem.InstrList codegen(Tree.Stm stm);

    // natural word size of target machine
    abstract public int wordSize();

    // Generate a tree exp to call an runtime function.
    abstract public Tree.Exp externalCall(String func, Tree.ExpList args);

    // Return frame pointer register
    abstract public Temp FP();

    // Return the register holding return value of a function.
    abstract public Temp RV();

    // Return all registers of target machine.
    abstract public TempList registers();
    
    // Generate a pseudo instruction to create a string lieteral.
    abstract public String string(Label lab, String str);

    // Generate items 5-7.  See p.176 of "Tiger" book.
    abstract public Tree.Stm procEntryExit1(Tree.Stm body);

    abstract public Assem.InstrList procEntryExit2(Assem.InstrList body);

    abstract public Proc procEntryExit3(Assem.InstrList body);
}

