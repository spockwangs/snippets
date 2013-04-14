# -*- Makefile -*-

JFLAGS = -g
CLASS_FILES = $(wildcard */*.class) $(wildcard */*~) Parse/Grm.java Parse/Yylex.java Parse/Grm.err

all: Parse/Main.class

Parse/Main.class: $(wildcard Parse/*.java) Parse/Grm.java Parse/Yylex.java Absyn/Absyn.class \
	Semant/Semant.class ErrorMsg/ErrorMsg.class Canon/Canon.class Parse/Parse.class \
	Frame/Frame.class Mips/Codegen.class Translate/ProcFrag.class Translate/DataFrag.class \
	Absyn/Print.class FlowGraph/AssemFlowGraph.class Translate/Translator.class \
	Frame/Proc.class RegAlloc/RegAlloc.class
	javac ${JFLAGS} Parse/*.java

Parse/Grm.java: Parse/Grm.cup
	cd Parse; java -jar java-cup-11a.jar -parser Grm -expect 4 -dump_grammar -dump_states <Grm.cup >Grm.out 2>Grm.err

Parse/Yylex.java: Parse/Tiger.lex ErrorMsg/ErrorMsg.class
	cd Parse; java JLex.Main Tiger.lex; mv Tiger.lex.java Yylex.java

ErrorMsg/ErrorMsg.class:  ErrorMsg/*.java
	javac ${JFLAGS} ErrorMsg/*.java

Absyn/Absyn.class: $(wildcard Absyn/*.java)
	javac ${JFLAGS} $^

Semant/Semant.class: Semant/*.java Translate/Level.class Symbol/Table.class Symbol/Symbol.class
	javac ${JFLAGS} Semant/*.java

Translate/%.class: Translate/%.java Tree/Exp.class Tree/Stm.class Temp/Label.class
	javac ${JFLAGS} $<

Translate/Level.class: Temp/Label.class

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

Canon/%.class: Canon/%.java
	javac ${JFLAGS} $<

Codegen/%.class: Codegen/%.java $($(wildcard Assem/*.java) .java = .class)
	javac ${JFLAGS} $<

Assem/%.class: Assem/%.java
	javac ${JFLAGS} $<

AssemFlowGraph.class: FlowGraph/AssemFlowGraph.java FlowGraph/FlowGraph.class

FlowGraph/FlowGraph.class: FlowGraph/FlowGraph.java $(patsubst %.java, %.class, $(wildcard Graph/*.java))

RegAlloc/Liveness.class: RegAlloc/InterferenceGraph.class RegAlloc/Move.class

RegAlloc/RegAlloc.class: RegAlloc/Liveness.class

%.class: %.java
	javac ${JFLAGS} $<

clean: 
	$(RM) ${CLASS_FILES} *~ \#*\# core a.out runtime.s

.PHONY: clean