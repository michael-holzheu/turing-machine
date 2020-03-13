#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

/* Machine state */

#define BLANK		'.'
#define TAPE_START	8
#define FINAL		-1

uint8_t tape[16];
int tape_pos = TAPE_START;
int state_curr = 0;

/* Turing instruction */

enum move {LEFT = 'L', RIGHT = 'R', NO_SHIFT = 'N'};

struct instr {
	int state_curr;		/* Current state of machine */
	uint8_t read;		/* What is read from the tape */
	uint8_t write;		/* What we should write to tape */
	enum move move;		/* Move move */
	int state_new;		/* New state for machine */
};

void state_print(struct instr *instr)
{
	static int tape_pos_last = -1;
	char *color = KNRM;
	int i;

	printf("s=%d: ", state_curr);
	for (i = 0; i < ARRAY_LEN(tape); i++) {
		if (i == tape_pos_last) {
			printf(KRED "%c" KNRM, tape[i]);
		} else if (i == tape_pos) {
			printf(KGRN "%c" KNRM, tape[i]);
		} else {
			printf("%c", tape[i]);
		}
	}
	if (instr->write != tape[tape_pos] && instr->write != '*') {
		color = KRED;
		tape_pos_last = tape_pos;
	} else {
		color = KGRN;
		tape_pos_last = -1;
	}
	printf(" w=%s%c%s m=%c s=%d",
			color,
			instr->write,
			KNRM,
			instr->move,
			instr->state_new);
	printf("\n");
}

int machine_run(struct instr* instr_vec, int instr_count,
		uint8_t *input, int input_count)
{
	struct instr *instr;
	int i;

	/* Initialize tape with blanks */
	memset(tape, BLANK, sizeof(tape));
	/* Add input */
	memcpy(&tape[TAPE_START], input, input_count);

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
			if (instr->state_new == FINAL) {
				printf("END: State: %d\n", instr->state_curr);
				exit(0);
			}
			state_print(instr);
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
			goto found;
		}
		printf("Invalid input word!\n");
		exit(1);
found:
		continue;
	}
	return 0;
}

/* Action table */

struct instr instr_program[] = {
	/* State 0: Search rightmost digit */
	{0, '0',     '0',     RIGHT, 0}, /* Skip 0s */
	{0, '1',     '1',     RIGHT, 0}, /* Skip 1s */
	{0, BLANK,    BLANK,  LEFT,  1}, /* Found blank */
	/* State 1: Do addition with 1 */
	{1, '0',     '1',     LEFT,  2}, /* 0 + 1 = 1 > done */
	{1, '1',     '0',     LEFT,  1}, /* 1 + 1 = 0 + carry */
	/* State 2: Accepting State */
	{2, '*',     '*',     NO_SHIFT, FINAL},
};

uint8_t tape_input[] = {'1', '0', '1', '1'};

int main(void)
{
	return machine_run(instr_program, ARRAY_LEN(instr_program),
			tape_input, sizeof(tape_input));
}
