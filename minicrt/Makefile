CC = gcc
CFLAGS = -g -fno-builtin -nostdlib -fno-stack-protector
CXX = g++
CXXFLAGS = -g -fno-builtin -nostdlib -fno-stack-protector \
	-nostdinc++ -fno-rtti -fno-exceptions

all: entry.o crtbegin.o crtend.o sysdep.o libminicrt.so libminicrt++.so

test: test1 test2

test1 test2: all

%: %.c
	$(CC) $(CFLAGS) -c $<
	ld -o $@ -dynamic-linker /lib/ld-linux.so.2 -e entry \
		crtbegin.o $@.o entry.o sysdep.o crtend.o ./libminicrt.so

%: %.cc
	$(CXX) $(CXXFLAGS) -c $<
	ld -o $@ -dynamic-linker /lib/ld-linux.so.2 -e entry \
		crtbegin.o $@.o entry.o sysdep.o crtend.o ./libminicrt++.so

libminicrt.so: memory.o vfprintf.o stdio.o string.o atexit.o
	ld -shared -o $@ $^

libminicrt++.so: memory.o vfprintf.o stdio.o string.o new.o atexit.o iostream.o
	ld -shared -o $@ $^

clean:
	$(RM) *.o *.so *~ test1 test2 a.out