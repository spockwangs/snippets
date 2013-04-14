package Absyn;
import Symbol.Symbol;
public class FunctionDec extends Dec {
    public Symbol name;
    public FieldList params;
    public NameTy result;  /* optional */
    public Exp body;
    public FunctionDec next;
    public FunctionDec(int p, Symbol n, FieldList a, NameTy r, Exp b, FunctionDec x)
    {pos=p; name=n; params=a; result=r; body=b; next=x;}

    // public void display(int depth) {
    //     String pad = "";
    //     for (int i = 0; i < depth; i++)
    //         pad += " ";

    //     System.out.println(pad + "FunctionDec: " + name);
    //     pad += "  ";
    //     if (result == null)
    //         System.out.println(pad + "ReturnType: void");
    //     else {
    //         System.out.print(pad + "ReturnType: ");
    //         result.display(0);
    //         System.out.println("");
    //     }
    //     System.out.println(pad + "Parameters: ");
    //     params.display(depth+4);
    //     System.out.println(pad + "Body: ");
    //     body.display(depth+4);
    // }
}
