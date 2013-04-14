/*
 * Tiger.lex -- Lexer for the programming language Tiger
 *
 * Author: wbb
 * Time-stamp: <2010-07-11 17:03:55 wbb>
 */

package Parse;

class Yytoken extends java_cup.runtime.Symbol {
    String my_text;
    int my_line, my_begin, my_end;

    Yytoken(int kind, Object value, String t, int linenumber, int begin,
            int end, int left, int right) {
        super(kind, left, right, value);
        my_text = new String(t);
        my_line = linenumber;
        my_begin = begin;
        my_end = end;
    }

    public String toString() {
        return my_text + " " + "(" + my_line + ":" + my_begin + ")";
    }
}

class LineList {
    int head;
    LineList tail;

    LineList(int h, LineList t) {
        head=h; 
        tail=t;
    }
}

%% 

%implements java_cup.runtime.Scanner
%function next_token
%type Yytoken
%char
%line
%{
    private LineList linePos = new LineList(-1,null);
    private int lineNum = 1;

    private Yytoken tok(int kind, String str, Object value) {
        return new Yytoken(kind, value, str, lineNum, lineIndex(yychar),
                           lineIndex(yychar)+yylength(), yychar,
                           yychar+yylength());
    }

    private void newline() {
        lineNum++;
        linePos = new LineList(yychar, linePos);
        errMsg.newline(yychar);
    }

    private int lineIndex(int pos) {
        int n = lineNum;
        LineList p = linePos;

        while (p != null) {
            if (p.head<pos) {
                break;
            }
            p = p.tail;
            n--;
        }
        return pos-p.head;
    }

    private void err(String s) {
        System.out.println(filename + ":" + lineNum + ":" + lineIndex(yychar) + ": error: " + s);
    }

    private void err(Yytoken t, String s) {
        System.out.println(filename + ":" + t.my_line + ":" + t.my_begin + ": error: " + s);
    }

    private String filename = null;
    private ErrorMsg.ErrorMsg errMsg;
    
    Yylex(java.io.InputStream s, String file, ErrorMsg.ErrorMsg errmsg) {
        this(s);
        filename = file;
        errMsg = errmsg;
    }
    
    private int comment_count = 0;
    private Yytoken last_token = null;
    private String last_str = "";

    /**
     * Convert a hex escape string "\xhh" to a oct escape string "\ooo".
     */
    private String octEscFromHexEsc(String s) {
        s = s.substring(2);     // skip "\x"
        Integer i = Integer.parseInt(s, 16);
        return "\\" + Integer.toOctalString(i.intValue());
    }

    /**
     * Validate a octal escape sequence "\ooo".  If invalid return an
     * acceptable octal escape sequence.
     */
    private String checkOctEsc(String s) {
        Integer i = Integer.parseInt(s.substring(1));
        if (i.intValue() > 255) {
            // Out of range.
            err("octal escape sequence out of range");
            return "\\377";
        } else
            return s;
    }
%}

%eof{
    if (comment_count > 0) {
        err(last_token, "unterminated comment");
    }
%eof}
%eofval{
    return tok(sym.EOF, "EOF", null);
%eofval}

ALPHA = [a-zA-Z]
DIGIT = [0-9]
OCT = [0-7]
HEX = [0-9a-fA-F]
SPACE = [ \n\t\b]
STRING_TEXT = ([^\n\"]|\\\n|\\\")*
COMMENT_TEXT = ([^*\n]|"*"[^/])*
ESCAPE_SEQ = \\([\"bnta]|[0-7][0-7]?[0-7]?|x[0-9a-fA-F][0-9a-fA-F]?)

%state COMMENT
%state STRING
%%

<YYINITIAL> [ \t\b] { }
<YYINITIAL> \n { newline(); }

<YYINITIAL> while { return tok(sym.WHILE, yytext(), null); }
<YYINITIAL> for   { return tok(sym.FOR, yytext(), null); }
<YYINITIAL> to    { return tok(sym.TO, yytext(), null); }
<YYINITIAL> break { return tok(sym.BREAK, yytext(), null); }
<YYINITIAL> let   { return tok(sym.LET, yytext(), null); }
<YYINITIAL> in    { return tok(sym.IN, yytext(), null); }
<YYINITIAL> end   { return tok(sym.END, yytext(), null); }
<YYINITIAL> function { return tok(sym.FUNCTION, yytext(), null); }
<YYINITIAL> var   { return tok(sym.VAR, yytext(), null); }
<YYINITIAL> type  { return tok(sym.TYPE, yytext(), null); }
<YYINITIAL> array { return tok(sym.ARRAY, yytext(), null); }
<YYINITIAL> if    { return tok(sym.IF, yytext(), null); }
<YYINITIAL> then  { return tok(sym.THEN, yytext(), null); }
<YYINITIAL> else  { return tok(sym.ELSE, yytext(), null); }
<YYINITIAL> do    { return tok(sym.DO, yytext(), null); }
<YYINITIAL> of    { return tok(sym.OF, yytext(), null); }
<YYINITIAL> nil   { return tok(sym.NIL, yytext(), null); }

<YYINITIAL> ","	  { return tok(sym.COMMA, yytext(), null); }
<YYINITIAL> ":"   { return tok(sym.COLON, yytext(), null); }
<YYINITIAL> ";"   { return tok(sym.SEMICOLON, yytext(), null); }
<YYINITIAL> "("   { return tok(sym.LPAREN, yytext(), null); }
<YYINITIAL> ")"   { return tok(sym.RPAREN, yytext(), null); }
<YYINITIAL> "["   { return tok(sym.LBRACK, yytext(), null); }
<YYINITIAL> "]"   { return tok(sym.RBRACK, yytext(), null); }
<YYINITIAL> "{"   { return tok(sym.LBRACE, yytext(), null); }
<YYINITIAL> "}"   { return tok(sym.RBRACE, yytext(), null); }
<YYINITIAL> "."   { return tok(sym.DOT, yytext(), null); }
<YYINITIAL> "+"   { return tok(sym.PLUS, yytext(), null); }
<YYINITIAL> "-"   { return tok(sym.MINUS, yytext(), null); }
<YYINITIAL> "*"   { return tok(sym.TIMES, yytext(), null); }
<YYINITIAL> "/"   { return tok(sym.DIVIDE, yytext(), null); }
<YYINITIAL> "="   { return tok(sym.EQ, yytext(), null); }
<YYINITIAL> "<>"  { return tok(sym.NEQ, yytext(), null); }
<YYINITIAL> "<"   { return tok(sym.LT, yytext(), null); }
<YYINITIAL> "<="  { return tok(sym.LE, yytext(), null); }
<YYINITIAL> ">"   { return tok(sym.GT, yytext(), null); }
<YYINITIAL> ">="  { return tok(sym.GE, yytext(), null); }
<YYINITIAL> "&"   { return tok(sym.AND, yytext(), null); }
<YYINITIAL> "|"   { return tok(sym.OR, yytext(), null); }
<YYINITIAL> ":="  { return tok(sym.ASSIGN, yytext(), null); }

<YYINITIAL> "/*"  { yybegin(COMMENT); last_token = tok(0, yytext(), null); comment_count++; }
<COMMENT> {COMMENT_TEXT} { }
<COMMENT> \n { newline(); }
<COMMENT> "*/" { 
        if (comment_count <= 0) {
            err(last_token, "unterminated comment");
        }
        comment_count--; 
        yybegin(YYINITIAL);
}

<YYINITIAL> (_|{ALPHA})({ALPHA}|{DIGIT})*  { return tok(sym.ID, yytext(), new String(yytext())); }
<YYINITIAL> {DIGIT}+ { return tok(sym.INT, yytext(), new Integer(yytext())); }

<YYINITIAL> \" { yybegin(STRING); last_str = "\""; }
<STRING> \\\n { newline(); }
<STRING> "\n" { last_str += yytext(); }
<STRING> "\t" { last_str += yytext(); }
<STRING> "\b" { last_str += yytext(); }
<STRING> \\\" { last_str += yytext(); }
<STRING> \\\\ { last_str += yytext(); }
<STRING> \\{OCT}{OCT}?{OCT}? { last_str += checkOctEsc(yytext()); }
<STRING> \\x{HEX}{HEX}? { last_str += octEscFromHexEsc(yytext()); }
<STRING> \\. { err("unrecognized escape sequence: " + yytext()); }
<STRING> [^\"\\\n]+ { last_str += yytext(); }
<STRING> \n { newline(); err("unterminated string"); yybegin(YYINITIAL); }
<STRING> \" { yybegin(YYINITIAL); return tok(sym.STRING, last_str, last_str+"\""); }
<STRING> . { err("invalid string"); }

. { err("syntax error"); }

