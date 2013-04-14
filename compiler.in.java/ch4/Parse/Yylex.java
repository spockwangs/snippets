/*
 * Tiger.lex -- Lexer for the programming language Tiger
 *
 * Author: wbb
 * Time-stamp: <2010-06-12 16:44:16 wbb>
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


class Yylex implements java_cup.runtime.Scanner {
	private final int YY_BUFFER_SIZE = 512;
	private final int YY_F = -1;
	private final int YY_NO_STATE = -1;
	private final int YY_NOT_ACCEPT = 0;
	private final int YY_START = 1;
	private final int YY_END = 2;
	private final int YY_NO_ANCHOR = 4;
	private final int YY_BOL = 128;
	private final int YY_EOF = 129;

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
    Yylex(java.io.InputStream s, String file) {
        this(s);
        filename = file;
    }
    private int comment_count = 0;
    private Yytoken last_token = null;
    private String last_str = "";
    private char oct_escape(String s) {
        int c = 0;
        for (int i = 0; i < s.length(); i++) {
            c = c*8 + (s.charAt(i)-'0');
        }
        return (char) c;
    }
    private int hex2dec(char hex) {
        if (hex >= '0' && hex <= '9')
            return hex-'0';
        if (hex >= 'A' && hex <= 'F')
            return hex-'A'+10;
        if (hex >= 'a' && hex <= 'f')
            return hex-'a'+10;
        assert false: "invalid hex: " + hex;
        return 0;
    }
    private char hex_escape(String s) {
        int c = 0;
        for (int i = 0; i < s.length(); i++) {
            c = c*16 + hex2dec(s.charAt(i));
        }
        return (char) c;
    }
	private java.io.BufferedReader yy_reader;
	private int yy_buffer_index;
	private int yy_buffer_read;
	private int yy_buffer_start;
	private int yy_buffer_end;
	private char yy_buffer[];
	private int yychar;
	private int yyline;
	private boolean yy_at_bol;
	private int yy_lexical_state;

	Yylex (java.io.Reader reader) {
		this ();
		if (null == reader) {
			throw (new Error("Error: Bad input stream initializer."));
		}
		yy_reader = new java.io.BufferedReader(reader);
	}

	Yylex (java.io.InputStream instream) {
		this ();
		if (null == instream) {
			throw (new Error("Error: Bad input stream initializer."));
		}
		yy_reader = new java.io.BufferedReader(new java.io.InputStreamReader(instream));
	}

	private Yylex () {
		yy_buffer = new char[YY_BUFFER_SIZE];
		yy_buffer_read = 0;
		yy_buffer_index = 0;
		yy_buffer_start = 0;
		yy_buffer_end = 0;
		yychar = 0;
		yyline = 0;
		yy_at_bol = true;
		yy_lexical_state = YYINITIAL;
	}

	private boolean yy_eof_done = false;
	private void yy_do_eof () {
		if (false == yy_eof_done) {

    if (comment_count > 0) {
        err(last_token, "unterminated comment");
    }
		}
		yy_eof_done = true;
	}
	private final int STRING = 2;
	private final int YYINITIAL = 0;
	private final int COMMENT = 1;
	private final int yy_state_dtrans[] = {
		0,
		49,
		72
	};
	private void yybegin (int state) {
		yy_lexical_state = state;
	}
	private int yy_advance ()
		throws java.io.IOException {
		int next_read;
		int i;
		int j;

		if (yy_buffer_index < yy_buffer_read) {
			return yy_buffer[yy_buffer_index++];
		}

		if (0 != yy_buffer_start) {
			i = yy_buffer_start;
			j = 0;
			while (i < yy_buffer_read) {
				yy_buffer[j] = yy_buffer[i];
				++i;
				++j;
			}
			yy_buffer_end = yy_buffer_end - yy_buffer_start;
			yy_buffer_start = 0;
			yy_buffer_read = j;
			yy_buffer_index = j;
			next_read = yy_reader.read(yy_buffer,
					yy_buffer_read,
					yy_buffer.length - yy_buffer_read);
			if (-1 == next_read) {
				return YY_EOF;
			}
			yy_buffer_read = yy_buffer_read + next_read;
		}

		while (yy_buffer_index >= yy_buffer_read) {
			if (yy_buffer_index >= yy_buffer.length) {
				yy_buffer = yy_double(yy_buffer);
			}
			next_read = yy_reader.read(yy_buffer,
					yy_buffer_read,
					yy_buffer.length - yy_buffer_read);
			if (-1 == next_read) {
				return YY_EOF;
			}
			yy_buffer_read = yy_buffer_read + next_read;
		}
		return yy_buffer[yy_buffer_index++];
	}
	private void yy_move_end () {
		if (yy_buffer_end > yy_buffer_start &&
		    '\n' == yy_buffer[yy_buffer_end-1])
			yy_buffer_end--;
		if (yy_buffer_end > yy_buffer_start &&
		    '\r' == yy_buffer[yy_buffer_end-1])
			yy_buffer_end--;
	}
	private boolean yy_last_was_cr=false;
	private void yy_mark_start () {
		int i;
		for (i = yy_buffer_start; i < yy_buffer_index; ++i) {
			if ('\n' == yy_buffer[i] && !yy_last_was_cr) {
				++yyline;
			}
			if ('\r' == yy_buffer[i]) {
				++yyline;
				yy_last_was_cr=true;
			} else yy_last_was_cr=false;
		}
		yychar = yychar
			+ yy_buffer_index - yy_buffer_start;
		yy_buffer_start = yy_buffer_index;
	}
	private void yy_mark_end () {
		yy_buffer_end = yy_buffer_index;
	}
	private void yy_to_mark () {
		yy_buffer_index = yy_buffer_end;
		yy_at_bol = (yy_buffer_end > yy_buffer_start) &&
		            ('\r' == yy_buffer[yy_buffer_end-1] ||
		             '\n' == yy_buffer[yy_buffer_end-1] ||
		             2028/*LS*/ == yy_buffer[yy_buffer_end-1] ||
		             2029/*PS*/ == yy_buffer[yy_buffer_end-1]);
	}
	private java.lang.String yytext () {
		return (new java.lang.String(yy_buffer,
			yy_buffer_start,
			yy_buffer_end - yy_buffer_start));
	}
	private int yylength () {
		return yy_buffer_end - yy_buffer_start;
	}
	private char[] yy_double (char buf[]) {
		int i;
		char newbuf[];
		newbuf = new char[2*buf.length];
		for (i = 0; i < buf.length; ++i) {
			newbuf[i] = buf[i];
		}
		return newbuf;
	}
	private final int YY_E_INTERNAL = 0;
	private final int YY_E_MATCH = 1;
	private java.lang.String yy_error_string[] = {
		"Error: Internal error.\n",
		"Error: Unmatched input.\n"
	};
	private void yy_error (int code,boolean fatal) {
		java.lang.System.out.print(yy_error_string[code]);
		java.lang.System.out.flush();
		if (fatal) {
			throw new Error("Fatal Error.\n");
		}
	}
	private int[][] unpackFromString(int size1, int size2, String st) {
		int colonIndex = -1;
		String lengthString;
		int sequenceLength = 0;
		int sequenceInteger = 0;

		int commaIndex;
		String workString;

		int res[][] = new int[size1][size2];
		for (int i= 0; i < size1; i++) {
			for (int j= 0; j < size2; j++) {
				if (sequenceLength != 0) {
					res[i][j] = sequenceInteger;
					sequenceLength--;
					continue;
				}
				commaIndex = st.indexOf(',');
				workString = (commaIndex==-1) ? st :
					st.substring(0, commaIndex);
				st = st.substring(commaIndex+1);
				colonIndex = workString.indexOf(':');
				if (colonIndex == -1) {
					res[i][j]=Integer.parseInt(workString);
					continue;
				}
				lengthString =
					workString.substring(colonIndex+1);
				sequenceLength=Integer.parseInt(lengthString);
				workString=workString.substring(0,colonIndex);
				sequenceInteger=Integer.parseInt(workString);
				res[i][j] = sequenceInteger;
				sequenceLength--;
			}
		}
		return res;
	}
	private int yy_acpt[] = {
		/* 0 */ YY_NOT_ACCEPT,
		/* 1 */ YY_NO_ANCHOR,
		/* 2 */ YY_NO_ANCHOR,
		/* 3 */ YY_NO_ANCHOR,
		/* 4 */ YY_NO_ANCHOR,
		/* 5 */ YY_NO_ANCHOR,
		/* 6 */ YY_NO_ANCHOR,
		/* 7 */ YY_NO_ANCHOR,
		/* 8 */ YY_NO_ANCHOR,
		/* 9 */ YY_NO_ANCHOR,
		/* 10 */ YY_NO_ANCHOR,
		/* 11 */ YY_NO_ANCHOR,
		/* 12 */ YY_NO_ANCHOR,
		/* 13 */ YY_NO_ANCHOR,
		/* 14 */ YY_NO_ANCHOR,
		/* 15 */ YY_NO_ANCHOR,
		/* 16 */ YY_NO_ANCHOR,
		/* 17 */ YY_NO_ANCHOR,
		/* 18 */ YY_NO_ANCHOR,
		/* 19 */ YY_NO_ANCHOR,
		/* 20 */ YY_NO_ANCHOR,
		/* 21 */ YY_NO_ANCHOR,
		/* 22 */ YY_NO_ANCHOR,
		/* 23 */ YY_NO_ANCHOR,
		/* 24 */ YY_NO_ANCHOR,
		/* 25 */ YY_NO_ANCHOR,
		/* 26 */ YY_NO_ANCHOR,
		/* 27 */ YY_NO_ANCHOR,
		/* 28 */ YY_NO_ANCHOR,
		/* 29 */ YY_NO_ANCHOR,
		/* 30 */ YY_NO_ANCHOR,
		/* 31 */ YY_NO_ANCHOR,
		/* 32 */ YY_NO_ANCHOR,
		/* 33 */ YY_NO_ANCHOR,
		/* 34 */ YY_NO_ANCHOR,
		/* 35 */ YY_NO_ANCHOR,
		/* 36 */ YY_NO_ANCHOR,
		/* 37 */ YY_NO_ANCHOR,
		/* 38 */ YY_NO_ANCHOR,
		/* 39 */ YY_NO_ANCHOR,
		/* 40 */ YY_NO_ANCHOR,
		/* 41 */ YY_NO_ANCHOR,
		/* 42 */ YY_NO_ANCHOR,
		/* 43 */ YY_NO_ANCHOR,
		/* 44 */ YY_NO_ANCHOR,
		/* 45 */ YY_NO_ANCHOR,
		/* 46 */ YY_NO_ANCHOR,
		/* 47 */ YY_NO_ANCHOR,
		/* 48 */ YY_NO_ANCHOR,
		/* 49 */ YY_NO_ANCHOR,
		/* 50 */ YY_NO_ANCHOR,
		/* 51 */ YY_NO_ANCHOR,
		/* 52 */ YY_NO_ANCHOR,
		/* 53 */ YY_NO_ANCHOR,
		/* 54 */ YY_NO_ANCHOR,
		/* 55 */ YY_NO_ANCHOR,
		/* 56 */ YY_NO_ANCHOR,
		/* 57 */ YY_NO_ANCHOR,
		/* 58 */ YY_NO_ANCHOR,
		/* 59 */ YY_NO_ANCHOR,
		/* 60 */ YY_NO_ANCHOR,
		/* 61 */ YY_NO_ANCHOR,
		/* 62 */ YY_NO_ANCHOR,
		/* 63 */ YY_NO_ANCHOR,
		/* 64 */ YY_NO_ANCHOR,
		/* 65 */ YY_NOT_ACCEPT,
		/* 66 */ YY_NO_ANCHOR,
		/* 67 */ YY_NO_ANCHOR,
		/* 68 */ YY_NO_ANCHOR,
		/* 69 */ YY_NO_ANCHOR,
		/* 70 */ YY_NO_ANCHOR,
		/* 71 */ YY_NO_ANCHOR,
		/* 72 */ YY_NOT_ACCEPT,
		/* 73 */ YY_NO_ANCHOR,
		/* 74 */ YY_NO_ANCHOR,
		/* 75 */ YY_NO_ANCHOR,
		/* 76 */ YY_NO_ANCHOR,
		/* 77 */ YY_NO_ANCHOR,
		/* 78 */ YY_NO_ANCHOR,
		/* 79 */ YY_NO_ANCHOR,
		/* 80 */ YY_NO_ANCHOR,
		/* 81 */ YY_NO_ANCHOR,
		/* 82 */ YY_NO_ANCHOR,
		/* 83 */ YY_NO_ANCHOR,
		/* 84 */ YY_NO_ANCHOR,
		/* 85 */ YY_NO_ANCHOR,
		/* 86 */ YY_NO_ANCHOR,
		/* 87 */ YY_NO_ANCHOR,
		/* 88 */ YY_NO_ANCHOR,
		/* 89 */ YY_NO_ANCHOR,
		/* 90 */ YY_NO_ANCHOR,
		/* 91 */ YY_NO_ANCHOR,
		/* 92 */ YY_NO_ANCHOR,
		/* 93 */ YY_NO_ANCHOR,
		/* 94 */ YY_NO_ANCHOR,
		/* 95 */ YY_NO_ANCHOR,
		/* 96 */ YY_NO_ANCHOR,
		/* 97 */ YY_NO_ANCHOR,
		/* 98 */ YY_NO_ANCHOR,
		/* 99 */ YY_NO_ANCHOR,
		/* 100 */ YY_NO_ANCHOR,
		/* 101 */ YY_NO_ANCHOR,
		/* 102 */ YY_NO_ANCHOR,
		/* 103 */ YY_NO_ANCHOR,
		/* 104 */ YY_NO_ANCHOR,
		/* 105 */ YY_NO_ANCHOR,
		/* 106 */ YY_NO_ANCHOR,
		/* 107 */ YY_NO_ANCHOR,
		/* 108 */ YY_NO_ANCHOR,
		/* 109 */ YY_NO_ANCHOR,
		/* 110 */ YY_NO_ANCHOR,
		/* 111 */ YY_NO_ANCHOR
	};
	private int yy_cmap[] = unpackFromString(1,130,
"51:8,1:2,2,51:2,42,51:18,1,51,46,51:3,40,51,26,27,35,33,23,34,32,36,48:8,45" +
":2,24,25,38,37,39,51:2,50:6,44:20,28,47,29,51,43,51,13,12,18,16,7,8,44,4,5," +
"44,14,6,44,15,9,21,44,10,22,11,17,19,3,49,20,44,30,41,31,51:2,0:2")[0];

	private int yy_rmap[] = unpackFromString(1,112,
"0,1:3,2,1,3,1:11,4,1,5,6,1:2,7,1:2,8:5,1:5,8:12,9,1:2,10,1:2,11,1:7,12,13,1" +
"4,15,16,17,18,1:2,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37," +
"38,39,40,41,42,43,44,45,46,47,48,8,49,50,51,52,53,54,8,55,56")[0];

	private int yy_nxt[][] = unpackFromString(57,52,
"1,2,3,4,109,66,88,90,91,73,109,74,110,111,109,92,75,109:2,93,109:3,5,6,7,8," +
"9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,-1,109:2,24,25,26,24,109:2,26,-" +
"1:55,109,101,109:18,-1:21,109,102,-1:2,102,109:2,-1:38,32,-1:49,33,-1:53,34" +
",-1,35,-1:49,36,-1:59,24,-1:2,24,-1:6,109:20,-1:21,109,102,-1:2,102,109:2,-" +
"1,1,68,50,68:32,67,68:16,-1,52,-1,52:43,-1:2,52:4,-1,56,57,56:8,58,59,56:2," +
"60,56:26,-1,56:3,61,62,63,69,56:2,-1:48,89,-1:10,71:2,-1:3,71:2,-1:2,71,-1," +
"71,-1:26,71,-1:2,71,-1,71,-1:2,68:35,-1,68:15,-1:3,109:5,27,109:6,28,109:7," +
"-1:21,109,102,-1:2,102,109:2,-1:2,68:35,51,68:15,-1,68,-1,68:32,65,68:16,-1" +
":7,64:2,-1:3,64:2,-1:2,64,-1,64,-1:26,64,-1:2,64,-1,64,-1,1,52,53,52:43,54," +
"55,52:4,-1:3,109:5,29,109:14,-1:21,109,102,-1:2,102,109:2,-1:4,109,95,109:4" +
",30,109:10,96,109:2,-1:21,109,102,-1:2,102,109:2,-1:4,109:6,31,109:13,-1:21" +
",109,102,-1:2,102,109:2,-1:4,109:8,37,109:11,-1:21,109,102,-1:2,102,109:2,-" +
"1:4,109:13,38,109:6,-1:21,109,102,-1:2,102,109:2,-1:4,109:7,39,109:12,-1:21" +
",109,102,-1:2,102,109:2,-1:4,109:3,40,109:16,-1:21,109,102,-1:2,102,109:2,-" +
"1:4,109:7,41,109:12,-1:21,109,102,-1:2,102,109:2,-1:4,109:4,42,109:15,-1:21" +
",109,102,-1:2,102,109:2,-1:4,109:12,43,109:7,-1:21,109,102,-1:2,102,109:2,-" +
"1:4,109:4,44,109:15,-1:21,109,102,-1:2,102,109:2,-1:4,109:4,45,109:15,-1:21" +
",109,102,-1:2,102,109:2,-1:4,109:11,46,109:8,-1:21,109,102,-1:2,102,109:2,-" +
"1:4,109:17,47,109:2,-1:21,109,102,-1:2,102,109:2,-1:4,109:12,48,109:7,-1:21" +
",109,102,-1:2,102,109:2,-1:4,109:4,76,109:15,-1:21,109,102,-1:2,102,109:2,-" +
"1:49,70,-1:6,109:3,94,109:8,77,109:7,-1:21,109,102,-1:2,102,109:2,-1:4,109:" +
"6,78,109:7,103,109:5,-1:21,109,102,-1:2,102,109:2,-1:4,109:2,79,109:17,-1:2" +
"1,109,102,-1:2,102,109:2,-1:4,109:10,80,109:9,-1:21,109,102,-1:2,102,109:2," +
"-1:4,109:19,81,-1:21,109,102,-1:2,102,109:2,-1:4,109:4,82,109:15,-1:21,109," +
"102,-1:2,102,109:2,-1:4,109:18,83,109,-1:21,109,102,-1:2,102,109:2,-1:4,109" +
":3,84,109:16,-1:21,109,102,-1:2,102,109:2,-1:4,109:10,85,109:9,-1:21,109,10" +
"2,-1:2,102,109:2,-1:4,109:10,86,109:9,-1:21,109,102,-1:2,102,109:2,-1:4,109" +
":6,87,109:13,-1:21,109,102,-1:2,102,109:2,-1:4,109:2,97,109:17,-1:21,109,10" +
"2,-1:2,102,109:2,-1:4,109:12,106,109:7,-1:21,109,102,-1:2,102,109:2,-1:4,10" +
"9:4,98,109:15,-1:21,109,102,-1:2,102,109:2,-1:4,109:7,99,109:12,-1:21,109,1" +
"02,-1:2,102,109:2,-1:4,109:15,107,109:4,-1:21,109,102,-1:2,102,109:2,-1:4,1" +
"09:8,108,109:11,-1:21,109,102,-1:2,102,109:2,-1:4,109:2,100,109:17,-1:21,10" +
"9,102,-1:2,102,109:2,-1:4,109:7,104,109:12,-1:21,109,102,-1:2,102,109:2,-1:" +
"4,109:7,105,109:12,-1:21,109,102,-1:2,102,109:2,-1");

	public Yytoken next_token ()
		throws java.io.IOException {
		int yy_lookahead;
		int yy_anchor = YY_NO_ANCHOR;
		int yy_state = yy_state_dtrans[yy_lexical_state];
		int yy_next_state = YY_NO_STATE;
		int yy_last_accept_state = YY_NO_STATE;
		boolean yy_initial = true;
		int yy_this_accept;

		yy_mark_start();
		yy_this_accept = yy_acpt[yy_state];
		if (YY_NOT_ACCEPT != yy_this_accept) {
			yy_last_accept_state = yy_state;
			yy_mark_end();
		}
		while (true) {
			if (yy_initial && yy_at_bol) yy_lookahead = YY_BOL;
			else yy_lookahead = yy_advance();
			yy_next_state = YY_F;
			yy_next_state = yy_nxt[yy_rmap[yy_state]][yy_cmap[yy_lookahead]];
			if (YY_EOF == yy_lookahead && true == yy_initial) {
				yy_do_eof();

    return tok(sym.EOF, "EOF", null);
			}
			if (YY_F != yy_next_state) {
				yy_state = yy_next_state;
				yy_initial = false;
				yy_this_accept = yy_acpt[yy_state];
				if (YY_NOT_ACCEPT != yy_this_accept) {
					yy_last_accept_state = yy_state;
					yy_mark_end();
				}
			}
			else {
				if (YY_NO_STATE == yy_last_accept_state) {
					throw (new Error("Lexical Error: Unmatched Input."));
				}
				else {
					yy_anchor = yy_acpt[yy_last_accept_state];
					if (0 != (YY_END & yy_anchor)) {
						yy_move_end();
					}
					yy_to_mark();
					switch (yy_last_accept_state) {
					case 1:
						
					case -2:
						break;
					case 2:
						{ }
					case -3:
						break;
					case 3:
						{ newline(); }
					case -4:
						break;
					case 4:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -5:
						break;
					case 5:
						{ return tok(sym.COMMA, yytext(), null); }
					case -6:
						break;
					case 6:
						{ return tok(sym.COLON, yytext(), null); }
					case -7:
						break;
					case 7:
						{ return tok(sym.SEMICOLON, yytext(), null); }
					case -8:
						break;
					case 8:
						{ return tok(sym.LPAREN, yytext(), null); }
					case -9:
						break;
					case 9:
						{ return tok(sym.RPAREN, yytext(), null); }
					case -10:
						break;
					case 10:
						{ return tok(sym.LBRACK, yytext(), null); }
					case -11:
						break;
					case 11:
						{ return tok(sym.RBRACK, yytext(), null); }
					case -12:
						break;
					case 12:
						{ return tok(sym.LBRACE, yytext(), null); }
					case -13:
						break;
					case 13:
						{ return tok(sym.LBRACE, yytext(), null); }
					case -14:
						break;
					case 14:
						{ return tok(sym.DOT, yytext(), null); }
					case -15:
						break;
					case 15:
						{ return tok(sym.PLUS, yytext(), null); }
					case -16:
						break;
					case 16:
						{ return tok(sym.MINUS, yytext(), null); }
					case -17:
						break;
					case 17:
						{ return tok(sym.TIMES, yytext(), null); }
					case -18:
						break;
					case 18:
						{ return tok(sym.DIVIDE, yytext(), null); }
					case -19:
						break;
					case 19:
						{ return tok(sym.EQ, yytext(), null); }
					case -20:
						break;
					case 20:
						{ return tok(sym.LT, yytext(), null); }
					case -21:
						break;
					case 21:
						{ return tok(sym.GT, yytext(), null); }
					case -22:
						break;
					case 22:
						{ return tok(sym.AND, yytext(), null); }
					case -23:
						break;
					case 23:
						{ return tok(sym.OR, yytext(), null); }
					case -24:
						break;
					case 24:
						{ return tok(sym.INT, yytext(), new Integer(yytext())); }
					case -25:
						break;
					case 25:
						{ yybegin(STRING); last_str = "\""; }
					case -26:
						break;
					case 26:
						{ err("syntax error"); }
					case -27:
						break;
					case 27:
						{ return tok(sym.IF, yytext(), null); }
					case -28:
						break;
					case 28:
						{ return tok(sym.IN, yytext(), null); }
					case -29:
						break;
					case 29:
						{ return tok(sym.OF, yytext(), null); }
					case -30:
						break;
					case 30:
						{ return tok(sym.TO, yytext(), null); }
					case -31:
						break;
					case 31:
						{ return tok(sym.DO, yytext(), null); }
					case -32:
						break;
					case 32:
						{ return tok(sym.ASSIGN, yytext(), null); }
					case -33:
						break;
					case 33:
						{ yybegin(COMMENT); last_token = tok(0, yytext(), null); comment_count++; }
					case -34:
						break;
					case 34:
						{ return tok(sym.LE, yytext(), null); }
					case -35:
						break;
					case 35:
						{ return tok(sym.NEQ, yytext(), null); }
					case -36:
						break;
					case 36:
						{ return tok(sym.GE, yytext(), null); }
					case -37:
						break;
					case 37:
						{ return tok(sym.LET, yytext(), null); }
					case -38:
						break;
					case 38:
						{ return tok(sym.END, yytext(), null); }
					case -39:
						break;
					case 39:
						{ return tok(sym.FOR, yytext(), null); }
					case -40:
						break;
					case 40:
						{ return tok(sym.NIL, yytext(), null); }
					case -41:
						break;
					case 41:
						{ return tok(sym.VAR, yytext(), null); }
					case -42:
						break;
					case 42:
						{ return tok(sym.ELSE, yytext(), null); }
					case -43:
						break;
					case 43:
						{ return tok(sym.THEN, yytext(), null); }
					case -44:
						break;
					case 44:
						{ return tok(sym.TYPE, yytext(), null); }
					case -45:
						break;
					case 45:
						{ return tok(sym.WHILE, yytext(), null); }
					case -46:
						break;
					case 46:
						{ return tok(sym.BREAK, yytext(), null); }
					case -47:
						break;
					case 47:
						{ return tok(sym.ARRAY, yytext(), null); }
					case -48:
						break;
					case 48:
						{ return tok(sym.FUNCTION, yytext(), null); }
					case -49:
						break;
					case 49:
						{ }
					case -50:
						break;
					case 50:
						{ newline(); }
					case -51:
						break;
					case 51:
						{ 
        if (comment_count <= 0) {
            err(last_token, "unterminated comment");
        }
        comment_count--; 
        yybegin(YYINITIAL);
}
					case -52:
						break;
					case 52:
						{ last_str += yytext(); }
					case -53:
						break;
					case 53:
						{ newline(); err("unterminated string"); yybegin(YYINITIAL); }
					case -54:
						break;
					case 54:
						{ yybegin(YYINITIAL); return tok(sym.STRING, last_str, last_str+"\""); }
					case -55:
						break;
					case 55:
						{ err("invalid string"); }
					case -56:
						break;
					case 56:
						{ err("unrecognized escape sequence: " + yytext()); }
					case -57:
						break;
					case 57:
						{ newline(); }
					case -58:
						break;
					case 58:
						{ last_str += "\t"; }
					case -59:
						break;
					case 59:
						{ last_str += "\b"; }
					case -60:
						break;
					case 60:
						{ last_str += "\n"; }
					case -61:
						break;
					case 61:
						{ last_str += "\""; }
					case -62:
						break;
					case 62:
						{ last_str += "\\"; }
					case -63:
						break;
					case 63:
						{ last_str += oct_escape(yytext().substring(1)); }
					case -64:
						break;
					case 64:
						{ last_str += hex_escape(yytext().substring(2)); }
					case -65:
						break;
					case 66:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -66:
						break;
					case 67:
						{ err("syntax error"); }
					case -67:
						break;
					case 68:
						{ }
					case -68:
						break;
					case 69:
						{ err("unrecognized escape sequence: " + yytext()); }
					case -69:
						break;
					case 70:
						{ last_str += oct_escape(yytext().substring(1)); }
					case -70:
						break;
					case 71:
						{ last_str += hex_escape(yytext().substring(2)); }
					case -71:
						break;
					case 73:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -72:
						break;
					case 74:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -73:
						break;
					case 75:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -74:
						break;
					case 76:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -75:
						break;
					case 77:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -76:
						break;
					case 78:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -77:
						break;
					case 79:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -78:
						break;
					case 80:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -79:
						break;
					case 81:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -80:
						break;
					case 82:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -81:
						break;
					case 83:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -82:
						break;
					case 84:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -83:
						break;
					case 85:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -84:
						break;
					case 86:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -85:
						break;
					case 87:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -86:
						break;
					case 88:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -87:
						break;
					case 89:
						{ last_str += oct_escape(yytext().substring(1)); }
					case -88:
						break;
					case 90:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -89:
						break;
					case 91:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -90:
						break;
					case 92:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -91:
						break;
					case 93:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -92:
						break;
					case 94:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -93:
						break;
					case 95:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -94:
						break;
					case 96:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -95:
						break;
					case 97:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -96:
						break;
					case 98:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -97:
						break;
					case 99:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -98:
						break;
					case 100:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -99:
						break;
					case 101:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -100:
						break;
					case 102:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -101:
						break;
					case 103:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -102:
						break;
					case 104:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -103:
						break;
					case 105:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -104:
						break;
					case 106:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -105:
						break;
					case 107:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -106:
						break;
					case 108:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -107:
						break;
					case 109:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -108:
						break;
					case 110:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -109:
						break;
					case 111:
						{ return tok(sym.ID, yytext(), new String(yytext())); }
					case -110:
						break;
					default:
						yy_error(YY_E_INTERNAL,false);
					case -1:
					}
					yy_initial = true;
					yy_state = yy_state_dtrans[yy_lexical_state];
					yy_next_state = YY_NO_STATE;
					yy_last_accept_state = YY_NO_STATE;
					yy_mark_start();
					yy_this_accept = yy_acpt[yy_state];
					if (YY_NOT_ACCEPT != yy_this_accept) {
						yy_last_accept_state = yy_state;
						yy_mark_end();
					}
				}
			}
		}
	}
}
