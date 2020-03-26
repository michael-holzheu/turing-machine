/*
 * machine - Universal Turing Machine (UTM)
 *
 * Copyright Michael Holzheu 2020
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

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
	enum move move;		/* Move read-write head */
	int state_new;		/* New state for machine */
	char *comment;		/* Comment that describes instruction */
};

void machine_init(int argc, char *argv[], char *desc);
int machine_run(const struct instr* instr_vec, int instr_count,
		const uint8_t *input, int input_count, int state_init);

/* Full state: 3 bytes substate and 1 byte state */

#define IS_SUBSTATE(x) ((x) & 0xffffff00)
#define SUBSTATE(x,y) ((x) | ((y) << 8))

#define STATE_GET(x) ((x) & 0xff)
#define SUBSTATE_GET(x) ((x)>>8 & 0xffffff)

#endif /* MACHINE_H */
