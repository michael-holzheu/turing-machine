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

#include "lib/util_opt.h"
#include "lib/util_prg.h"

#include "opts.h"

/*
 * Program configuration
 */
struct util_prg prg = {
	.desc	= "Run a Turing machine",
	.copyright_vec = {
		{
			.owner = "Michael Holzheu",
			.pub_first = 2020,
			.pub_last = 2020,
		},
		UTIL_PRG_COPYRIGHT_END
	}
};

/*
 * Options with defaults
 */
struct opts opts = {
	.delay = 0,
	.color = true,
	.tape_pos = 0,
	.list_prog = false,
	.tape_size = 64,
	.print_substates = false,
};

/*
 * Command line options
 */
static struct util_opt opt_vec[] = {
	UTIL_OPT_SECTION("OPTIONS"),
	{
		.option = { "delay", required_argument, NULL, 'd'},
		.argument = "SECONDS",
		.desc = "Wait time after each rule"
	},
	{
		.option = { "list-program", no_argument, NULL, 'l'},
		.desc = "List the program / action table",
	},
	{
		.option = { "no-color", no_argument, NULL, 'n'},
		.desc = "Disable color output",
	},
	{
		.option = { "print-substates", no_argument, NULL, 't'},
		.desc = "Print substates",
	},
	{
		.option = { "tape-pos", required_argument, NULL, 'p'},
		.argument = "BYTE-NR",
		.desc = "Start position of read-write head"
	},
	{
		.option = { "tape-size", required_argument, NULL, 's'},
		.argument = "BYTES",
		.desc = "Size of tape in BYTES"
	},
	UTIL_OPT_HELP,
	UTIL_OPT_VERSION,
	UTIL_OPT_END
};

/*
 * Parse command line options
 */
void opts_parse(int argc, char *argv[], char *desc)
{
	int c;

	prg.desc = desc;
	util_prg_init(&prg);
	util_opt_init(opt_vec, NULL);

	while (1) {
		c = util_opt_getopt_long(argc, argv);
		if (c == -1)
			break;
		switch (c) {
		case 'h':
			util_prg_print_help();
			util_opt_print_help();
			exit(EXIT_SUCCESS);
		case 'v':
			util_prg_print_version();
			exit(EXIT_SUCCESS);
		case 'n':
			opts.color = false;
			break;
		case 'd':
			if (sscanf(optarg, "%d", &opts.delay) != 1)
				errx(EXIT_FAILURE, "Invalid delay specified: %s", optarg);
			break;
		case 'l':
			opts.list_prog = true;
			break;
		case 'p':
			if (sscanf(optarg, "%u", &opts.tape_pos) != 1)
				errx(EXIT_FAILURE, "Invalid tape position specified: %s",
						optarg);
			break;
		case 's':
			if (sscanf(optarg, "%u", &opts.tape_size) != 1)
				errx(EXIT_FAILURE, "Invalid tape size specified: %s", optarg);
			break;
		case 't':
			opts.print_substates = true;
			break;
		default:
			util_opt_print_parse_error(c, argv);
			exit(EXIT_FAILURE);
		}
	}
	if (opts.tape_pos >= opts.tape_size)
		errx(EXIT_FAILURE, "Invalid tape size / pos specified: %u/%u",
				opts.tape_size, opts.tape_pos);
}
