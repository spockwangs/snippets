
package Translate;

public class Frag {
    public Frag next;
}


class ProcFrag extends Frag {
    Tree.Stm body;
    Frame.Frame frame;
    
    public ProcFrag(Tree.Stm b, Frame.Frame f, Frag next) {
        body = b;
        frame = f;
        this.next = next;
    }
}


class DataFrag extends Frag {
    String str;

    public DataFrag(String data, Frag next) {
        str = data;
        this.next = next;
    }
}