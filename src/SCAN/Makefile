SRC=$(wildcard *.c)
OBJS=$(SRC:.c=.o)
CC=gcc
#CCFLAGS=-Wall -g
LDFLAGS=-fPIC -shared
LIBS=-lwiringPi
TARGET=libscan.so

$(TARGET):$(SRC)
	$(CC) $(CCFLAGS) $(LDFLAGS) -o $@ $(SRC) $(LIBS)

.PHONY:clean
clean:
	-rm -f *.so
