JFLAGS=-g

Parse/Main.class: Parse/*.java Parse/Grm.java Parse/Yylex.java Translate/Exp.class Absyn/Absyn.class Semant/Semant.class \
	Symbol/Table.class
	javac ${JFLAGS} Parse/*.java

Parse/Grm.java: Parse/Grm.cup
	cd Parse; java -jar java-cup-11a.jar -parser Grm -expect 4 -dump_grammar -dump_states <Grm.cup >Grm.out 2>Grm.err

Parse/Yylex.java: Parse/Tiger.lex ErrorMsg/ErrorMsg.class
	cd Parse; java JLex.Main Tiger.lex; mv Tiger.lex.java Yylex.java

ErrorMsg/ErrorMsg.class:  ErrorMsg/*.java
	javac ${JFLAGS} ErrorMsg/*.java

Absyn/Absyn.class: Absyn/*.java
	javac ${JFLAGS} Absyn/*.java

Semant/Semant.class: Semant/*.java
	javac ${JFLAGS} Semant/*.java

Translate/Exp.class: Translate/*.java
	javac ${JFLAGS} $^

Symbol/Table.class: Symbol/*.java
	javac ${JFLAGS} $^