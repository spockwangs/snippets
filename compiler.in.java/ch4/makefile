JFLAGS=-g


Parse/Main.class: Parse/*.java Parse/Grm.java Parse/Yylex.java
	javac ${JFLAGS} Parse/*.java

Parse/Grm.java: Parse/Grm.cup
	cd Parse; java -jar java-cup-11a.jar -parser Grm -expect 4 -dump_grammar -dump_states <Grm.cup >Grm.out 2>Grm.err

Parse/Yylex.java: Parse/Tiger.lex
	cd Parse; java JLex.Main Tiger.lex; mv Tiger.lex.java Yylex.java

ErrorMsg/ErrorMsg.class:  ErrorMsg/*.java
	javac ${JFLAGS} ErrorMsg/*.java

Absyn/Absyn.class: Absyn/*.java
	javac ${JFLAGS} Absyn/*.java

