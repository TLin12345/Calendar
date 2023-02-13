CC=gcc
CFLAGS=-I.
DEPS = calendar.h
OBJ = calendar.o count.o print.o

%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

calendar: $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS)
