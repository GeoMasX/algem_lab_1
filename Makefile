MyProject : main.o paint.o stack.o
	gcc main.o paint.o stack.o -o MyProject

main.o : main.c
	gcc -c main.c -o main.o

paint.o : paint.c stack.o
	gcc -c paint.c -o paint.o

stack.o : stack.c
	gcc -c stack.c -o stack.o