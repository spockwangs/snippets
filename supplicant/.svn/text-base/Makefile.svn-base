
CC = gcc -g -W -Wall -lpcap -lnet

all: supplicant

supplicant: md5.c supplicant.c send.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	@echo Cleanning ... 
	@$(RM) *.out *.o *~ supplicant

.PHONY: all clean
