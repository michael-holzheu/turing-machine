/*
 * machine - Universal Turing Machine (UTM)
 *
 * Option parsing
 *
 * Copyright Michael Holzheu 2020
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#ifndef OPTS_H
#define OPTS_H

#include <stdbool.h>

/*
 * Options
 */
struct opts {
	int delay;		/* Delay in seconds */
	int tape_pos;		/* Start position of tape */
	int tape_size;		/* Size of tape in bytes */
	bool print_substates;	/* Print substates */
	bool list_prog;		/* List the program / action table */
	bool color;		/* Use color output */
};

extern struct opts opts;

void opts_parse(int argc, char *argv[], char *desc);

#endif /* OPTS_H */
