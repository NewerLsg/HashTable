INC=.

LIBS=-L. -lnw_hash

VPATH=.

SRC=nw_hash.c main.c

OBJS=$(SRC:.c=.o)

OUTPUT=main libnw_hash.so libnw_hash.a

all:$(OUTPUT)

#main:main.o
#	gcc -g $^ -o $@ -L. -lnw_hash 

#libnw_hash.so:nw_hash.o
#	gcc -fPIc -shared -g $^ -o $@

#libnw_hash.a:nw_hash.o
#	ar -crl  -$^

.SUFFIXES:.o .c .so .a

.c.o:
	gcc -fPIc $(INC) -g -c $^

.so.a:
	gcc -g -fPIc -shared $(INC) lib$@ $^ 

.o.a:
	ar -crl lib$@ $^

.o:
	gcc -o $@  $^ $(LIBS) 

clean:
	rm -f *.o *.a *.so  $(OUTPUT) 