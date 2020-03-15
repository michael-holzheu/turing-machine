#ifndef MACHINE_PAPER_H
#define MACHINE_PAPER_H

#include <stdint.h>

#include "machine.h"

struct instr_paper {
	int m_config;		/* Current state of machine */
	uint8_t symbol_scanned;	/* What is read from the tape */
	char *operations;	/* List of move and print instructions */
	int m_config_final;	/* New state for machine */
};

int machine_paper_run(const struct instr_paper *instr_vec, int instr_count,
		      const uint8_t *input, int input_count, int state_init);

#endif /* MACHINE_PAPER_H */
