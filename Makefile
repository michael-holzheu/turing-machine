CFLAGS += -g

all: example-add-one example-paper-ii

example-add-one: machine.o example-add-one.o
example-paper-ii: machine.o machine-paper.o example-paper-ii.o
machine-paper: machine.o machine-paper.o

clean:
	rm -f *.o example-add-one example-paper-ii
