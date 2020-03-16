#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helper.h"
#include "machine.h"

/* Machine state */

#define TAPE_START	8

uint8_t tape[64];
int tape_pos = TAPE_START;
int state_curr;

void state_print(const struct instr *instr)
{
	static int tape_pos_last = -1;
	char *color = KNRM;
	int i;

	if (IS_SUBSTATE(state_curr))
		return;

	printf("s=%c: ", state_curr);
	for (i = 0; i < ARRAY_LEN(tape); i++) {
		if (i == tape_pos_last)
			printf(KRED "%c" KNRM, tape[i]);
		else if (i == tape_pos)
			printf(KGRN "%c" KNRM, tape[i]);
		else
			printf("%c", tape[i]);
	}
	if (instr->write != tape[tape_pos] && instr->write != '*') {
		color = KRED;
		tape_pos_last = tape_pos;
	} else {
		color = KGRN;
		tape_pos_last = -1;
	}
	printf(" w=%s%c%s m=%c s=%c",
			color,
			instr->write,
			KNRM,
			instr->move,
			instr->state_new);
	printf("\n");
}

void instr_print(const struct instr *instr)
{
	printf("s=%c:%d r=%c w=%c m=%c, ns=%c:%d\n",
		STATE_GET(instr->state_curr),
		SUBSTATE_GET(instr->state_curr),
		instr->read,
		instr->write,
		instr->move,
		STATE_GET(instr->state_new),
		SUBSTATE_GET(instr->state_new));
}

void machine_prog_print(struct instr *instr_vec, int instr_count)
{
	int i;

	for (i = 0; i < instr_count; i++) {
		instr_print(&instr_vec[i]);
	}
}

int machine_run(const struct instr *instr_vec, int instr_count,
		const uint8_t *input, int input_count, int state_init)
{
	const struct instr *instr;
	int i;

	/* Initialize tape with blanks */
	memset(tape, BLANK, sizeof(tape));
	/* Add input */
	if (input)
		memcpy(&tape[TAPE_START], input, input_count);
	/* Set initial state */
	state_curr = state_init;

	while (1) {
		for (i = 0; i < instr_count; i++) {
			instr = &instr_vec[i];
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
				printf("END: State: %c\n", instr->state_curr);
				exit(0);
			}
			/* Write new data */
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
			if (tape_pos > (ARRAY_LEN(tape) - 1) || tape_pos < 0) {
				printf("Out of tape: pos=%d\n", tape_pos);
				exit(1);
			}
			goto found;
		}
state_curr = 0;
			state_print(instr);
		printf("Invalid input word!\n");
		exit(1);
found:
		continue;
	}
	return 0;
}

