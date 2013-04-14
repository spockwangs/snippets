# -*- Makefile -*-

JFLAGS = -g
CLASS_FILES = $(wildcard */*.class) $(wildcard */*~) Parse/Grm.java Parse/Yylex.java

all: Parse/Main.class

Parse/Main.class: $(wildcard Parse/*.java) Parse/Grm.java Parse/Yylex.java Absyn/Absyn.class \
	Semant/Semant.class ErrorMsg/ErrorMsg.class
	javac ${JFLAGS} Parse/*.java

Parse/Grm.java: Parse/Grm.cup
	cd Parse; java -jar java-cup-11a.jar -parser Grm -expect 4 -dump_grammar -dump_states <Grm.cup >Grm.out 2>Grm.err

Parse/Yylex.java: Parse/Tiger.lex ErrorMsg/ErrorMsg.class
	cd Parse; java JLex.Main Tiger.lex; mv Tiger.lex.java Yylex.java

ErrorMsg/ErrorMsg.class:  ErrorMsg/*.java
	javac ${JFLAGS} ErrorMsg/*.java

Absyn/Absyn.class: $(wildcard Absyn/*.java)
	javac ${JFLAGS} $^

Semant/Semant.class: Semant/*.java $($(wildcard Translate/*.java): .java=.class) Symbol/Table.class Symbol/Symbol.class
	javac ${JFLAGS} Semant/*.java

Translate/%.class: Translate/%.java Tree/Exp.class Tree/Stm.class Temp/Label.class \
	$($(wildcard Tree/*.java): .java=.class) $($(wildcard Frame/*.java): .java=.class)
	javac ${JFLAGS} $<

Symbol/%.class: Symbol/%.java
	javac ${JFLAGS} $^

Util/%.class: Util/%.java
	javac ${JFLAGS} $^

Temp/%.class: Temp/%.java
	javac ${JFLAGS} $^

Frame/%.class: Frame/%.java Util/BoolList.class Temp/Temp.class Mips/MipsFrame.class
	javac ${JFLAGS} $<

Mips/%.class: Mips/%.java
	javac ${JFLAGS} $<

Tree/%.class: Tree/%.java Temp/Temp.class Temp/Label.class
	javac ${JFLAGS} $<

clean: 
	$(RM) ${CLASS_FILES} 

.PHONY: clean