include ../common.mak

ALL_CPPFLAGS += -g

TARGETS=example-add-one \
	example-paper-add-one \
	example-paper-i \
	example-paper-ii

all: $(TARGETS)

libs =	\
	$(rootdir)/libmachine-paper/libmachine-paper.a \
	$(rootdir)/libmachine/libmachine.a \
	$(rootdir)/libutil/libutil.a

example-add-one: example-add-one.o $(libs)
example-paper-add-one: example-paper-add-one.o $(libs)
example-paper-i: example-paper-i.o $(libs)
example-paper-ii: example-paper-ii.o $(libs)

install: all

clean:
	rm -f *.o *~ $(TARGETS)

.PHONY: all install clean
