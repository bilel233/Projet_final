CFLAGS = -g -Wall -Wextra -pedantic
CC = gcc

PROGRAMS = main

main : main.o part1.o part2.o part3.o part4.o
	$(CC) -c $(CFLAGS) part1.c


part1.o : part1.c part1.h
	$(CC) -c $(CFLAGS) part1.c

part2.o : part2.c part2.h
	$(CC) -c $(CFLAGS) part2.c 

part3.o : part3.c part3.h
	$(CC) -c $(CFLAGS) part3.c 
part4.o : part4.c part4.h
	$(CC) -c $(CFLAGS) part4.c

main.o : main.c part1.o part2.o part3.o part4.o
	$(CC) -c $(CFLAGS) main.c

cleanall: 
	rm -f *.o main *.txt

clean:
	rm -f *.o main


