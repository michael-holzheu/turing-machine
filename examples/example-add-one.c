/*
 * machine - Universal Turing Machine (UTM)
 *
 * Example: Add one to binary number
 *
 * Copyright Michael Holzheu 2020
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#include "lib/machine.h"
#include "lib/util_base.h"

/* Action table */

struct instr instr_program[] = {
	/* State a: Search rightmost digit */
	{'a', '0',     '0',     RIGHT, 'a', "Skip 0s"},
	{'a', '1',     '1',     RIGHT, 'a', "Skip 1s"},
	{'a', BLANK,    BLANK,  LEFT,  'b', "Found blank"},
	/* State b: Do addition with 1 */
	{'b', '0',     '1',     LEFT,  'c', "0 + 1 = 1 > done"},
	{'b', '1',     '0',     LEFT,  'b', "1 + 1 = 0 + carry"},
	/* State 2: Accepting State */
	{'c', '*',     '*',     NO_SHIFT, FINAL, "Accpeting state"},
};

uint8_t tape_input[] = {'1', '0', '1', '1'};

int main(int argc, char *argv[])
{
	machine_init(argc, argv, "Binary add one example");
	return machine_run(instr_program, (int)UTIL_ARRAY_SIZE(instr_program),
			tape_input, sizeof(tape_input), 'a');
}
