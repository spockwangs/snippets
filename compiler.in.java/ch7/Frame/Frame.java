package Frame;

import Temp.Temp;
import Temp.Label;

public abstract class Frame {
    public Label name;
    public AccessList formals;
    
    abstract public Frame newFrame(Label name, Util.BoolList formals);
    abstract public Access allocLocal(boolean escape);
    abstract public Access accessParam(int i);
    
    // Generate items 5-7.  See p.176 of "Tiger" book.
    abstract public Tree.Stm procEntryExit1(Tree.Stm body);
    
    public static Machine machine = new Mips.MipsMachine();
}

