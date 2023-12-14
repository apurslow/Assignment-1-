CC=gcc
CFLAGS=-pthread -I. -Wall
binaries=mash
all: $(binaries)
mash: mash.c
	$(CC) $(CFLAGS) -o $@ $<
clean:
	$(RM) -f $(binaries) *.o