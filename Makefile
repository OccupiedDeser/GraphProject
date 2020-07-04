# search-cli: main.o
# 	cc -o search-cli main.o

# main.o:
# 	cc -c main.c search.c stats.c

# clean:

CC = gcc

CFLAGS = -g -Wall

.PHONY: clean

search-cli: main.o
	$(CC) $(CFLAGS) -o search-cli main.o

main.o: 
	$(CC) $(CFLAGS) -c -o main.o main.c search.c stats.c extra.c

clean:
	rm -f main.o search-cli
