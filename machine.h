#ifndef MACHINE_H
#define MACHINE_H

#include <stdint.h>

#define BLANK		'.'
#define FINAL		-1

/* Turing instruction */

enum move {LEFT = 'L', RIGHT = 'R', NO_SHIFT = 'N'};

struct instr {
	int state_curr;		/* Current state of machine */
	uint8_t read;		/* What is read from the tape */
	uint8_t write;		/* What we should write to tape */
	enum move move;		/* Move move */
	int state_new;		/* New state for machine */
};

int machine_run(struct instr* instr_vec, int instr_count,
		uint8_t *input, int input_count);

#endif /* MACHINE_H */
