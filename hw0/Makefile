all: main.o map.o wc.o
	gcc -o all main.o map.o wc.o

main.o: main.c
	gcc -c main.c

map.o: map.c
	gcc -c map.c
	
wc.o: wc.c
	gcc -c wc.c

clean:
	rm -rf *o all
