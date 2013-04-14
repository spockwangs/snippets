package Absyn;
import Symbol.Symbol;
public class FieldExpList extends Absyn {
    public Symbol name;
    public Exp init;
    public FieldExpList tail;
    public FieldExpList(int p, Symbol n, Exp i, FieldExpList t) {pos=p; 
        name=n; init=i; tail=t;
    }

    // public void display(int depth) {
    //     String pad = "";
    //     for (int i = 0; i < depth; i++)
    //         pad += " ";

    //     System.out.println(pad + "field: " + name);
    //     init.display(depth+2);
    //     System.out.println("");
    //     if (tail != null)
    //         tail.display(depth+2);
    // }
}
