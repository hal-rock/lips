CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ilib

lips: interpret.o print.o eval.o builtins.o parse.o env.o func.o hash.o list.o 
	$(CC) $(CFLAGS) -o lips interpret.o print.o eval.o parse.o env.o func.o hash.o list.o \
		                  builtins.o

clean:
	rm *.o
