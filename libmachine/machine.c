/*
 * machine - Universal Turing Machine (UTM)
 *
 * Main functions
 *
 * Copyright Michael Holzheu 2020
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#include <err.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "lib/machine.h"
#include "lib/util_base.h"
#include "lib/util_libc.h"

#include "helper.h"
#include "opts.h"

/* Machine state */

uint8_t *tape;	/* Tape memory */
int tape_size;	/* Tape size */

int tape_pos;	/* Scanned square */
int state_curr;	/* Current m-configuration / state */

bool has_substates;

/*
 * Print the Turing machine state, e.g. the current tape contents
 */
static void state_print(const struct instr *instr)
{
	char *color_green = "", *color_nrm = "";
	int i;

	if (!opts.print_substates && IS_SUBSTATE(state_curr))
		return;

	if (opts.color) {
		color_green = KGRN;
		color_nrm = KNRM;
	}
	if (has_substates && opts.print_substates) {
		printf("s=%c:%02d ", STATE_GET(state_curr), SUBSTATE_GET(state_curr));
	} else {
		printf("s=%c ", STATE_GET(state_curr));
	}
	for (i = 0; i < tape_size; i++) {
		if (i == tape_pos)
			printf("%s%c%s", color_green, tape[i], color_nrm);
		else
			printf("%c", tape[i]);
	}
	if (!(has_substates && !opts.print_substates))
		printf(" w=%c m=%c", instr->write, instr->move);
	if (has_substates && opts.print_substates) {
		printf(" s=%c:%02d",
				instr->state_new == FINAL ? '-' : STATE_GET(instr->state_new),
				instr->state_new == FINAL ? 0 : SUBSTATE_GET(instr->state_new));
	} else if (!has_substates) {
		printf(" s=%c", instr->state_new == FINAL ? '-' : instr->state_new);
	}
	if (instr->comment)
		printf(" # %s", instr->comment);
	printf("\n");
	usleep(opts.delay * 100000);
}

/*
 * Print one Turing machine instruction
 */
static void instr_print(const struct instr *instr)
{
	printf("s=%c:%02d r=%c w=%c m=%c, ns=%c:%02d",
		STATE_GET(instr->state_curr),
		SUBSTATE_GET(instr->state_curr),
		instr->read,
		instr->write,
		instr->move,
		instr->state_new == FINAL ? '-' : STATE_GET(instr->state_new),
		instr->state_new == FINAL ? 0 : SUBSTATE_GET(instr->state_new));
	if (instr->comment)
		printf(" # %s", instr->comment);
	printf("\n");
}

/*
 * Print the whole Turing machine program
 */
static void machine_prog_print(const struct instr *instr_vec, int instr_count)
{
	int i;

	for (i = 0; i < instr_count; i++) {
		instr_print(&instr_vec[i]);
	}
}

/*
 * Do the option parsing
 */
void machine_init(int argc, char *argv[], char *desc)
{
	opts_parse(argc, argv, desc);
	tape_pos = opts.tape_pos;
	tape_size = opts.tape_size;
}

/*
 * Run a Turing machine with a given input
 */
int machine_run(const struct instr *instr_vec, int instr_count,
		const uint8_t *input, int input_count, int state_init)
{
	const struct instr *instr = NULL;
	int i;

	/* Alloc tape */
	tape = util_malloc(tape_size);
	/* Initialize tape with blanks */
	memset(tape, BLANK, tape_size);
	/* Add input */
	if (input)
		memcpy(&tape[tape_pos], input, input_count);
	/* Set initial state */
	state_curr = state_init;

	/* Check for substates */
	for (i = 0; i < instr_count; i++) {
		if (IS_SUBSTATE(instr_vec[i].state_curr)) {
			has_substates = true;
			break;
		}
	}
	if (opts.list_prog) {
		machine_prog_print(instr_vec, instr_count);
		exit(EXIT_SUCCESS);
	}
	while (1) {
		for (i = 0; i < instr_count; i++) {
			instr = &instr_vec[i];
			/* Find matching configuration (state & scanned symbol) */
			if (instr->state_curr != state_curr)
				goto no_match;
			if (instr->read == tape[tape_pos])
				goto match;
			if (instr->read == '*')
				goto match;
			if (instr->read == '+' && tape[tape_pos] != BLANK)
				goto match;
no_match:
			continue;
match:
			state_print(instr);
			if (instr->state_new == FINAL) {
				exit(EXIT_SUCCESS);
			}
			/* Write new symobl */
			if (instr->write != '*')
				tape[tape_pos] = instr->write;
			/* Set new state */
			state_curr = instr->state_new;
			/* Move tape */
			switch (instr->move) {
			case LEFT:
				tape_pos--;
				break;
			case RIGHT:
				tape_pos++;
				break;
			case NO_SHIFT:
				break;
			}
			if (tape_pos >= tape_size || tape_pos < 0) {
				errx(EXIT_FAILURE, "Out of tape memory at position %d",
						tape_pos);
			}
			goto found;
		}
state_curr = 0;
			state_print(instr);
		errx(EXIT_FAILURE, "Invalid input word!");
found:
		continue;
	}
	return 0;
}
