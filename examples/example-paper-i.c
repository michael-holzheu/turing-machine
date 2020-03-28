/*
 * machine-paper - Universal Turing Machine from Alan Turing's paper
 *
 * Example: Print pattern 0 1 0 1 0 1 ...
 *
 * Copyright Michael Holzheu 2020
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#include <stdlib.h>

#include "lib/machine-paper.h"
#include "lib/util_base.h"

#if 1
static struct instr_paper program[] = {
	{'b', NONE,   "P0,R", 'c'},
	{'c', NONE,   "R",    'e'},
	{'e', NONE,   "P1,R", 'f'},
	{'f', NONE,   "R",    'b'},
};
#else
static struct instr_paper program[] = {
	{'b', NONE,  "P0",     'b'},
	{'b', '0',   "R,R,P1", 'b'},
	{'b', '1',   "R,R,P0", 'b'},
};
#endif

int main(int argc, char *argv[])
{
	machine_init(argc, argv, "Print infinite zeroes and ones");
	return machine_paper_run(program, UTIL_ARRAY_SIZE(program),
			         NULL, 0, 'b');
}
