package Frame;

public class Proc {
    String prologue;
    String epilogue;
    Assem.InstrList body;
    
    public Proc(String prologue, Assem.InstrList body, String epilogue) {
        this.prologue = prologue;
        this.body = body;
        this.epilogue = epilogue;
    }

    public void emit(java.io.PrintStream out, Temp.TempMap tempmap) {
        out.print(prologue);
        for (Assem.InstrList p = body; p!=null; p=p.tail)
            out.print(p.head.format(tempmap));
        out.print(epilogue);
    }
}