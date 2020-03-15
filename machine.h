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

int machine_run(const struct instr* instr_vec, int instr_count,
		const uint8_t *input, int input_count, int state_init);

void machine_prog_print(struct instr* instr_vec, int instr_count);

void machine_configuration_print();

#define IS_SUBSTATE(x) (x & 0xffffff00)
#define SUBSTATE(x,y) (x | (y << 8))

#define STATE_GET(x) (x & 0xff)
#define SUBSTATE_GET(x) (x>>8 & 0xffffff)

#endif /* MACHINE_H */
