
CXX = g++
CXXFLAGS = -g -W -Wall -std=c++98 -pedantic
PROGRAMS = testinput testadd testsub testmul testdiv testresidue

all: $(PROGRAMS)

retest: big-integer.o

testinput: big-integer.o

testadd: big-integer.o

testsub: big-integer.o

testmul: big-integer.o

testdiv: big-integer.o

testresidue: big-integer.o

clean: 
	$(RM) *.o *~ core *.out $(PROGRAMS) test.* *.class

.PHONY: all clean
