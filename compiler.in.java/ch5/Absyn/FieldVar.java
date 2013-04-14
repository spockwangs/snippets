package Absyn;
import Symbol.Symbol;
public class FieldVar extends Var {
    public Var var;
    public Symbol field;
    public FieldVar(int p, Var v, Symbol f) {pos=p; var=v; field=f;}

    // public void display(int depth) {
    //     String pad = "";
    //     for (int i = 0; i < depth; i++)
    //         pad += " ";

    //     System.out.println(pad + "FieldVar");
    //     pad += "  ";
    //     System.out.println(pad + "var: ");
    //     var.display(depth+4);
    //     System.out.println("");
    //     System.out.print(pad + "field: " + field);
    // }
}
