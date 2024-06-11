CC = gcc
CFLAGS = -Wall -Wextra
TARGET = hifetch

.PHONY: all clean install

all: $(TARGET)

$(TARGET): main.o utils.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c utils.h
	$(CC) $(CFLAGS) -c $< -o $@

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

install:
	install -D -m 755 $(TARGET) $(DESTDIR)/usr/bin/$(TARGET)

