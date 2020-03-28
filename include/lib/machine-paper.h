/*
 * machine-paper - Universal Turing Machine from Alan Turing's paper
 *
 * Copyright Michael Holzheu 2020
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#ifndef MACHINE_PAPER_H
#define MACHINE_PAPER_H

#include <stdint.h>

#include "lib/machine.h"

#define NONE BLANK

struct instr_paper {
	int m_config;		/* Current state of machine */
	uint8_t symbol_scanned;	/* What is read from the tape */
	char *operations;	/* List of move and print instructions */
	int m_config_final;	/* New state for machine */
};

int machine_paper_run(const struct instr_paper *instr_vec, int instr_count,
		      const uint8_t *input, int input_count, int state_init);

#endif /* MACHINE_PAPER_H */
