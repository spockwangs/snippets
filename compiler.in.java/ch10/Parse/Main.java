package Parse;

public class Main {

    static boolean debug = false;
    static Frame.Frame frame = new Mips.MipsFrame();
    
    public static void main(String argv[]) throws java.io.IOException {
        Parse parse = new Parse(argv[0]);
      
        // Print abstract syntax tree for debugging.
        if (debug) {
            Absyn.Print printer = new Absyn.Print(System.out);
            System.out.println("==== Abstract syntax tree ====");
            printer.prExp(parse.absyn, 0);
            System.out.println("");
        }

        Translate.Translator translator = new Translate.Translator(frame);
        Semant.Semant semant =
            new Semant.Semant(parse.errorMsg,
                              new Translate.Level(frame),
                              translator);
        Translate.Frag frags;
        try {
            frags = semant.transProg(parse.absyn);
        } catch (Error e) {
            if (semant.nerrors == 1)
                System.out.println("1 error");
            else
                System.out.println(semant.nerrors + " errors");
            throw e;
        }

        java.io.PrintStream out = new java.io.PrintStream(new java.io.FileOutputStream(argv[0] + ".s"));
        out.println("    .data\n");
        for (Translate.Frag f = frags; f != null; f=f.next) {
            if (f instanceof Translate.DataFrag)
                out.println(((Translate.DataFrag)f).str);
        }
        out.println("    .text\n");
        for (Translate.Frag f = frags; f != null; f=f.next) {
            if (f instanceof Translate.ProcFrag)
                emitProc(out, (Translate.ProcFrag)f);
        }
        out.close();
    }

    static void prStmList(Tree.Print print, Tree.StmList stms) {
        for(Tree.StmList l = stms; l!=null; l=l.tail)
            print.prStm(l.head);
    }

    static Assem.InstrList codegen(Frame.Frame f, Tree.StmList stms) {
        Assem.InstrList first = null, last = null;
        for (Tree.StmList s = stms; s!=null; s=s.tail) {
            Assem.InstrList i = f.codegen(s.head);
            if (last == null) {
                first=last=i;
            } else {
                while (last.tail != null)
                    last=last.tail;
                last = last.tail = i;
            }
        }
        return first;
    }
		
    static void emitProc(java.io.PrintStream out, Translate.ProcFrag f) {
        java.io.PrintStream debug = new java.io.PrintStream(new NullOutputStream());
        Temp.TempMap tempmap = new Temp.CombineMap(f.frame, new Temp.DefaultMap());
        Tree.Print print = new Tree.Print(debug, tempmap);
        debug.println("# Before canonicalization: ");
        print.prStm(f.body);
        debug.println("# After canonicalization: ");
        Tree.StmList stms = Canon.Canon.linearize(f.body);
        prStmList(print, stms);

        debug.println("# Basic Blocks: ");
        Canon.BasicBlocks b = new Canon.BasicBlocks(stms);
        for (Canon.StmListList l = b.blocks; l!=null; l=l.tail) {
            debug.println("#");
            prStmList(print,l.head);
        }       
        print.prStm(new Tree.LABEL(b.done));

        debug.println("# Trace Scheduled: ");
        Tree.StmList traced = (new Canon.TraceSchedule(b)).stms;
        prStmList(print,traced);

        Assem.InstrList instrs = f.frame.procEntryExit2(codegen(f.frame, traced));
        Temp.TempMap reg_alloc = new RegAlloc.RegAlloc(f.frame, instrs);
        Frame.Proc proc = f.frame.procEntryExit3(instrs);
        debug.println("# Instructions: ");
        proc.emit(out, reg_alloc);
    }

    
    static String symnames[] = new String[100];
    static {
        symnames[sym.FUNCTION] = "FUNCTION";
        symnames[sym.EOF] = "EOF";
        symnames[sym.INT] = "INT";
        symnames[sym.GT] = "GT";
        symnames[sym.DIVIDE] = "DIVIDE";
        symnames[sym.COLON] = "COLON";
        symnames[sym.ELSE] = "ELSE";
        symnames[sym.OR] = "OR";
        symnames[sym.NIL] = "NIL";
        symnames[sym.DO] = "DO";
        symnames[sym.GE] = "GE";
        symnames[sym.error] = "error";
        symnames[sym.LT] = "LT";
        symnames[sym.OF] = "OF";
        symnames[sym.MINUS] = "MINUS";
        symnames[sym.ARRAY] = "ARRAY";
        symnames[sym.TYPE] = "TYPE";
        symnames[sym.FOR] = "FOR";
        symnames[sym.TO] = "TO";
        symnames[sym.TIMES] = "TIMES";
        symnames[sym.COMMA] = "COMMA";
        symnames[sym.LE] = "LE";
        symnames[sym.IN] = "IN";
        symnames[sym.END] = "END";
        symnames[sym.ASSIGN] = "ASSIGN";
        symnames[sym.STRING] = "STRING";
        symnames[sym.DOT] = "DOT";
        symnames[sym.LPAREN] = "LPAREN";
        symnames[sym.RPAREN] = "RPAREN";
        symnames[sym.IF] = "IF";
        symnames[sym.SEMICOLON] = "SEMICOLON";
        symnames[sym.ID] = "ID";
        symnames[sym.WHILE] = "WHILE";
        symnames[sym.LBRACK] = "LBRACK";
        symnames[sym.RBRACK] = "RBRACK";
        symnames[sym.NEQ] = "NEQ";
        symnames[sym.VAR] = "VAR";
        symnames[sym.BREAK] = "BREAK";
        symnames[sym.AND] = "AND";
        symnames[sym.PLUS] = "PLUS";
        symnames[sym.LBRACE] = "LBRACE";
        symnames[sym.RBRACE] = "RBRACE";
        symnames[sym.LET] = "LET";
        symnames[sym.THEN] = "THEN";
        symnames[sym.EQ] = "EQ";
    }
}

class NullOutputStream extends java.io.OutputStream {
    public void write(int b) {}
}