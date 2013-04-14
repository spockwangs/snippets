package Temp;

public class TempList {
    public Temp head;
    public TempList tail;

    public TempList(Temp h, TempList t) {
        head=h;
        tail=t;
    }

    public int size() {
        int s = 0;
        for (TempList p = this; p != null; p = p.tail) {
            s++;
        }
        return s;
    }
}

