a.out: main.o func.o
	gcc main.o func.o -o a.out

main.o: main.c func.h
	gcc -c main.c

func.o: func.c func.h
	gcc -c func.c

test.o:
	gcc main.c eqlib.c -o b.out

clean:
	rm -f *.o a.out

