include ../common.mak

lib = libmachine.a

all: $(lib)

objects = machine.o opts.o

$(lib): $(objects)

install: all

clean:
	rm -f *.o $(lib)
