/*
 * machine-paper - Universal Turing Machine from Alan Turing's paper
 *
 * Example: Add one to binary number
 *
 * Copyright Michael Holzheu 2020
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#include <stdlib.h>

#include "lib/machine-paper.h"
#include "lib/util_base.h"

static struct instr_paper program[] = {
	{'b', NONE,    "P1,R,P0,R,P1,R,P1", 'c'},
	{'c', '0',     "P1,L",              'd'},
	{'c', '1',     "P0,L",              'c'},
	{'d', '*',     "",                FINAL},
};

int main(int argc, char *argv[])
{
	machine_init(argc, argv, "Binary add one example");
	return machine_paper_run(program, UTIL_ARRAY_SIZE(program),
			         NULL, 0, 'b');
}
