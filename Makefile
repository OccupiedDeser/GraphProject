search-cli: main.o search.o stats.o extra.o
	gcc -o search-cli main.o search.o stats.o extra.o

main.o: main.c
	gcc -c main.c

search.o: search.c
	gcc -c search.c

stats.o: stats.c
	gcc -c stats.c

extra.o: extra.c
	gcc -c extra.c

clean:
	rm *.o search-cli