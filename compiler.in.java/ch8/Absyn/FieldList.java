package Absyn;
import Symbol.Symbol;
public class FieldList extends Absyn {
    public Symbol name;
    public Symbol typ;
    public FieldList tail;
    public boolean escape = true;
    public FieldList(int p, Symbol n, Symbol t, FieldList x) {pos=p; name=n; typ=t; tail=x;}

    // public void display(int depth) {
    //     String pad = "";
    //     for (int i = 0; i < depth; i++)
    //         pad += " ";

    //     System.out.println(pad + name + ": " + typ);
    //     if (tail != null)
    //         tail.display(depth);
    // }
}
