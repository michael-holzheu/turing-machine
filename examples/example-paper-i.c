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

#if 0
static struct instr_paper instr_paper_program[] = {
	{'b', BLANK,   "P0,R", 'c'},
	{'c', BLANK,   "R",    'e'},
	{'e', BLANK,   "P1,R", 'f'},
	{'f', BLANK,   "R",    'b'},
};
#else
static struct instr_paper instr_paper_program[] = {
	{'b', BLANK, "P0",     'b'},
	{'b', '0',   "R,R,P1", 'b'},
	{'b', '1',   "R,R,P0", 'b'},
};
#endif

int main(int argc, char *argv[])
{
	machine_init(argc, argv, "Print infinite zeroes and ones");
	return machine_paper_run(instr_paper_program, (int) UTIL_ARRAY_SIZE(instr_paper_program),
			         NULL, 0, 'b');
}
