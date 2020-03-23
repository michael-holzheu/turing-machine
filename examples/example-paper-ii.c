/*
 * machine-paper - Universal Turing Machine from Alan Turing's paper
 *
 * Example: Print pattern 0 1 0 1 1 0 1 1 1 0 1 1 1 1 ...
 *
 * Copyright Michael Holzheu 2020
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#include <stdlib.h>

#include "lib/machine-paper.h"
#include "lib/util_base.h"

static struct instr_paper instr_paper_program[] = {
	{'b', '*',   "Pe,R,Pe,R,P0,R,R,P0,L,L", 'o'},
	{'o', '1',   "R,Px,L,L,L",              'o'},
	{'o', '0',   "",                        'q'},
	{'q', '+',   "R,R",                     'q'},
	{'q', BLANK, "P1,L",                    'p'},
	{'p', 'x',   "E,R",                     'q'},
	{'p', 'e',   "R",                       'f'},
	{'p', BLANK, "L,L",                     'p'},
	{'f', '+',   "R,R",                     'f'},
	{'f', BLANK, "P0,L,L",                  'o'},
};

int main(int argc, char *argv[])
{
	machine_init(argc, argv, "Print pattern 0 1 0 1 1 0 1 1 1 0 1 1 1 1 ...");
	return machine_paper_run(instr_paper_program,
			UTIL_ARRAY_SIZE(instr_paper_program),
			NULL, 0, 'b');
}
