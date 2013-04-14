package Absyn;
import Symbol.Symbol;
public class IfExp extends Exp {
    public Exp test;
    public Exp thenclause;
    public Exp elseclause; /* optional */
    public IfExp(int p, Exp x, Exp y) {pos=p; test=x; thenclause=y; elseclause=null;}
    public IfExp(int p, Exp x, Exp y, Exp z) {pos=p; test=x; thenclause=y; elseclause=z;}

    // public void display(int depth) {
    //     String pad = "";
    //     for (int i = 0; i < depth; i++)
    //         pad += " ";

    //     System.out.println(pad + "IfExp");
    //     pad += "  ";
    //     System.out.println(pad + "test: ");
    //     test.display(depth+4);
    //     System.out.println("\n" + pad + "then: ");
    //     thenclause.display(depth+4);
    //     if (elseclause == null)
    //         System.out.print("\n" + pad + "else: (null)");
    //     else {
    //         System.out.println("\n" + pad + "else: ");
    //         elseclause.display(depth+4);
    //     }
    // }
}
