package Parse;

public class Main {

    public static void main(String argv[]) {
        boolean isscan = true, isparse = false, isdebug = false;

        // Process command line options.
        int i = 0;
        while (i < argv.length && argv[i].charAt(0) == '-') {
            switch (argv[i].charAt(1)) {
            case 's':
                isscan = true;
                break;
            case 'p':
                isparse = true;
                isscan = true;
                break;
            case 'd':
                isdebug = true;
                break;
            default:
                throw new Error("Unknown option: " + argv[i]);
            }
            i++;
        }
        if (argv.length <= i)
            throw new Error("filename required");
      
        String filename = argv[i];
        java.io.InputStream inp;
        try {
            inp = new java.io.FileInputStream(filename);
        } catch (java.io.FileNotFoundException e) {
            throw new Error("File not found: " + filename);
        }

        Yylex lexer = new Yylex(inp, filename);
        Grm parser = new Grm(lexer);
        Absyn.Exp absyn = null;
        if (isparse == false) {
            for (;;) {
                Yytoken t = null;
                try {
                    t = lexer.next_token();
                } catch (java.io.IOException e) {
                    System.out.println(e);
                    System.exit(1);
                }
                if (t.sym == sym.EOF)
                    break;
                System.out.print(symnames[t.sym]);
                if (t.value != null)
                    System.out.print("(" + t.value + ")");
                System.out.println("");
            }
        } else {
            try {
                absyn = (Absyn.Exp) parser./*debug_*/parse().value;
            } catch (Throwable e) {
                e.printStackTrace();
                throw new Error(e.toString());
            } 
            finally {
                try {inp.close();} catch (java.io.IOException e) {}
            }
        }

        if (isparse && isdebug) {
            Absyn.Print printer = new Absyn.Print(System.out);
            printer.prExp(absyn, 0);
            System.out.println("");
        }
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
