CC=cc
CFLAGS=-march=native -mtune=native -std=c11 -O3 -funsafe-math-optimizations -fprofile-use

all: mytest matrix

*.c:
	$(CC) $(CFLAGS) -o `basename $@` $@

clean:
	rm mytest matrix