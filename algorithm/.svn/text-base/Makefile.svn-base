# Top Makefile

all:
	@$(MAKE) -C src
	@$(MAKE) -C test

test:
	@$(MAKE) -C test test

clean:
	-@$(RM) core* a.out *~
	@$(MAKE) -C src clean
	@$(MAKE) -C test clean

dist-clean:
	@$(MAKE) clean
	@$(RM) libalgo.a
	@$(RM) cscope.out

cscope:
	@echo Generating cscope database ...
	@find . -name '*.[hc]' -o -name '*.cpp' > cscope.files
	@cscope -bR -i cscope.files
	@$(RM) cscope.files

.PHONY: all test clean
