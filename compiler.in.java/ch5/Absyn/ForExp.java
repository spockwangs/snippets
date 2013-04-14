package Absyn;
import Symbol.Symbol;
public class ForExp extends Exp {
    public VarDec var;
    public Exp hi, body;
    public ForExp(int p, VarDec v, Exp h, Exp b) {pos=p; var=v; hi=h; body=b;}

    // public void display(int depth) {
    //     String pad = "";
    //     for (int i = 0; i < depth; i++)
    //         pad += " ";

    //     System.out.println(pad + "ForExp");
    //     var.display(depth+2);
    //     System.out.println("");
    //     pad += "  ";
    //     System.out.println(pad + "hi: ");
    //     hi.display(depth+4);
    //     System.out.println("");
    //     System.out.println(pad + "body: ");
    //     body.display(depth+4);
    // }
}
