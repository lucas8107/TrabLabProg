CC=gcc

main: main.o ast.o hash.o
	$(CC) -o main main.o ast.o hash.o

clean:
	rm main

test:
	./main fib
