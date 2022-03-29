all: PSDD

PSDD: proj.o rsa.o key.o
	gcc -Werror -o PSDD proj.o rsa.o key.o

proj.o: proj.c proj.h
	gcc -c proj.c -o proj.o

rsa.o: rsa.c rsa.h
	gcc -c rsa.c -o rsa.o

key.o: key.c key.h rsa.h proj.h
	gcc -c key -o key.o

clean:
	rm -rf *.o