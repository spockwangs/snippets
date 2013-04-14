package Translate;

import Symbol.Symbol;

public class Level {
    Frame.Frame frame;
    public AccessList formals;  // static link and formal parameters
    public Level parent;
    
    public Level(Level p, Symbol name, Util.BoolList fmls) {
        frame = p.frame.newFrame(new Temp.Label(name), new Util.BoolList(true, fmls));
        formals = accessList(frame.formals);
        parent = p;
    }
    
    public Level(Frame.Frame f) {
        frame = f;
    }

    /**
     * Allocate local variables.
     */
    public Access allocLocal(boolean escape) {
        return new Access(this, frame.allocLocal(escape));
    }

    /**
     * Access to formal parameters.
     *
     * @param i the ith parameter
     */
    public Access accessParam(int i) {
        return new Access(this, frame.accessParam(i));
    }

    /**
     * Convert Frame.AccessList to Translate.AccessList.
     */
    Translate.AccessList accessList(Frame.AccessList list) {
        if (list == null)
            return null;
        return new Translate.AccessList(new Translate.Access(this, list.head),
                                        accessList(list.tail));
    }
}