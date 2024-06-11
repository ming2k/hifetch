CC = gcc
CFLAGS = -Wall -Wextra

all: hifetch

hifetch: main.o utils.o
	$(CC) $(CFLAGS) -o hifetch main.o utils.o

main.o: main.c utils.h
	$(CC) $(CFLAGS) -c main.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f *.o hifetch
