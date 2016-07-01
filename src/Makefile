INC=-I.

LIBS=-L. -lnw_hash

VPATH=.

SRC=nw_hash.c main.c nw_util.c

OBJS=$(SRC:.c=.o)

OUTPUT=main libnw_hash.so libnw_hash.a

all:$(OUTPUT)
	
.SUFFIXES:.o .c .so .a

.c.o:
	gcc -fPIC $(INC) -g -c $^

main:main.o libnw_hash.a
	gcc -g $^ -o $@ -L.  -lnw_hash 

libnw_hash.so:nw_hash.o nw_util.o
	gcc -fPIc -shared -g $^ -o $@

libnw_hash.a:nw_hash.o nw_util.o
	ar -rcs $@  $^

test:main
	./main
	
clean:
	rm -f *.o *.a *.so  $(OUTPUT) 