all: exec

exec:	fila.o	grafo.o	main.o
	gcc -o exec fila.o grafo.o main.o -lm

main.o:	main.c
	gcc -c main.c

grafo.o: grafo.c
	gcc -c grafo.c

fila.o:	fila.c
	gcc -c fila.c

run:	exec
	./exec

clean:
	rm -rf *.o exec