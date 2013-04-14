package Absyn;
import Symbol.Symbol;
public class ExpList {
    public Exp head;
    public ExpList tail;
    public ExpList(Exp h, ExpList t) {head=h; tail=t;}

    // public void display(int depth) {
    //     head.display(depth+4);
    //     System.out.println("");
    //     if (tail != null)
    //         tail.display(depth+4);
    // }
}
