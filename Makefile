CC = gcc
CFLAGS = -Wall -Wextra -g

proxy: proxy.c
	$(CC) $(CFLAGS) -o proxy proxy.c functions.c

clean:
	rm -f proxy