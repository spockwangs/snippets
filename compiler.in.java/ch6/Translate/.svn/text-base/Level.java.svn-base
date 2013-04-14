package Translate;

import Symbol.Symbol;

public class Level {
    Frame.Frame frame;
    public AccessList formals;

    public Level(Level parent, Symbol name, Util.BoolList fmls) {
        frame = parent.frame.newFrame(new Temp.Label(), new Util.BoolList(true, fmls));
        formals = accessList(frame.formals);
    }
    
    public Level(Frame.Frame f) {
        frame = f;
    }
    
    public Access allocLocal(boolean escape) {
        return new Access(this, frame.allocLocal(escape));
    }

    Translate.AccessList accessList(Frame.AccessList list) {
        if (list == null)
            return null;
        return new Translate.AccessList(new Translate.Access(this, list.head),
                                        accessList(list.tail));
    }
}