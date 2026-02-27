program: main.o menu.o field_info.o polynomial.o tests.o tools.o
	gcc main.o menu.o field_info.o polynomial.o tests.o tools.o -o program

main.o: main.c menu.h
	gcc -c main.c
	
menu.o: menu.c menu.h field_info.h polynomial.h tests.h tools.h
	gcc -c menu.c

field_info.o: field_info.c field_info.h
	gcc -c field_info.c
	
polynomial.o: polynomial.c polynomial.h field_info.h
	gcc -c polynomial.c
	
tests.o: tests.c tests.h field_info.h polynomial.h tests.h tools.h
	gcc -c tests.c

clean:
	rm *.o program
