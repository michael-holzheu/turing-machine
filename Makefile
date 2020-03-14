all: example_add_one

example_add_one: machine.o example_add_one.o

clean:
	rm -f *.o example_add_one
