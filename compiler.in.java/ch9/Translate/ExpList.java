package Translate;

public class ExpList {
    Exp head;
    ExpList tail;

    public ExpList() {
        head = null;
        tail = null;
    }
    
    public ExpList(Exp h, ExpList t) {
        head = h;
        tail = t;
    }

    public ExpList push(Exp e) {
        ExpList p = this;
        if (p.head == null) {
            p.head = e;
        } else {
            while (p.tail != null)
                p = p.tail;
            p.tail = new ExpList(e, null);
        }
        return this;
    }
}

