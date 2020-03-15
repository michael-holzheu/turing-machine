CFLAGS += -g

TARGETS= example-add-one  \
	 example-paper-i  \
	 example-paper-ii \

all: ${TARGETS}

example-add-one: machine.o example-add-one.o
example-paper-i: machine.o machine-paper.o example-paper-i.o
example-paper-ii: machine.o machine-paper.o example-paper-ii.o
machine-paper: machine.o machine-paper.o

clean:
	rm -f *.o ${TARGETS}
