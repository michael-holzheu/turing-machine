/*
 * machine-paper - Universal Turing Machine from Alan Turing's paper
 *
 * Convert the paper version to simpler machine instructions
 *
 * Copyright Michael Holzheu 2020
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/machine-paper.h"
#include "lib/util_base.h"
#include "lib/util_libc.h"

/*
 * Convert the paper version to simpler machine instructions by inserting substates
 */
static struct instr *paper_to_machine(const struct instr_paper *instr_paper_vec,
				      int instr_paper_count, int *instr_machine_count)
{
	struct instr *instr_machine, *instr_machine_vec = NULL;
	const struct instr_paper *instr_paper;
	int i, instr_count = 0;
	bool first;
	char *ptr;

	for (i = 0; i < instr_paper_count; i++) {
		instr_paper = &instr_paper_vec[i];
		ptr = instr_paper->operations;

		first = true;
		while (true) {
			instr_machine_vec = util_realloc(instr_machine_vec, ++instr_count *
							 sizeof(*instr_machine_vec));
			instr_machine = &instr_machine_vec[instr_count - 1];
			instr_machine->comment = instr_paper->operations;
			if (first) {
				instr_machine->read = instr_paper->symbol_scanned;
				instr_machine->state_curr = SUBSTATE(instr_paper->m_config, 0);
				first = false;
			} else {
				instr_machine->state_curr = SUBSTATE(instr_paper->m_config,
								     instr_count - 1);
				instr_machine->read = '*';
			}
			instr_machine->write = '*';
			instr_machine->move = NO_SHIFT;
			instr_machine->state_new = SUBSTATE(instr_paper->m_config, instr_count);
			if (*ptr == 'P') {
				ptr++;
				instr_machine->write = *ptr;
				ptr++;
			} else if (*ptr == 'E') {
				instr_machine->write = BLANK;
				ptr++;
			} else if (*ptr == 'L') {
				instr_machine->move = LEFT;
				ptr++;
			} else if (*ptr == 'R') {
				instr_machine->move = RIGHT;
				ptr++;
			} else if (*ptr != 0) {
				fprintf(stderr, "Invalid symbol: %s\n", ptr);
				exit(1);
			}
			if (*ptr == ',')
				ptr++;
			if (*ptr == 0)
				break;
		}
		instr_machine->state_new = instr_paper->m_config_final;
	}
	*instr_machine_count = instr_count;
	return instr_machine_vec;
}

/*
 * Run a paper Turing machine with a given input
 */
int machine_paper_run(const struct instr_paper *instr_vec, int instr_count,
		      const uint8_t *input, int input_count, int state_init)
{
	struct instr *instr_machine_vec;
	int instr_machine_count;

	instr_machine_vec = paper_to_machine(instr_vec, instr_count, &instr_machine_count);
	return machine_run(instr_machine_vec, instr_machine_count, input, input_count, state_init);
}
