#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

/* Machine state */

#define BLANK		'.'
#define TAPE_START	8
uint8_t tape[16];
int tape_pos = TAPE_START;
int state_curr = 0;

/* Turing instruction */

enum move {LEFT = 'L', RIGHT = 'R', HALT = 'H'};

struct instr {
	int state_curr;		/* Current state of machine */
	uint8_t read;		/* What is read from the tape */
	uint8_t write;		/* What we should write to tape */
	enum move move;		/* Move move */
	int state_new;		/* New state for machine */
};

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
	{2, '*',     '*',     HALT,  2},
};

uint8_t tape_input[] = {'1', '0', '1', '1'};

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


int main(void)
{
	struct instr *instr;
	int i;

	/* Initialize tape with blanks */
	memset(tape, BLANK, sizeof(tape));
	/* Add input */
	memcpy(&tape[TAPE_START], tape_input, sizeof(tape_input));

	while (1) {
		for (i = 0; i < ARRAY_LEN(instr_program); i++) {
			instr = &instr_program[i];
			if (instr->state_curr != state_curr)
				continue;
			if (instr->read != tape[tape_pos] && instr->read != '*')
				continue;
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
				case HALT:
					printf("END: State: %d\n", state_curr);
					exit(0);
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
