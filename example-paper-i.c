#include <stdlib.h>

#include "helper.h"
#include "machine-paper.h"

static struct instr_paper instr_paper_program[] = {
	{'b', BLANK,   "P0,R", 'c'},
	{'c', BLANK,   "R",    'e'},
	{'e', BLANK,   "P1,R", 'f'},
	{'f', BLANK,   "R",    'b'},
};

static struct instr_paper instr_paper_program_mod[] = {
	{'b', BLANK, "P0",     'b'},
	{'b', '0',   "R,R,P1", 'b'},
	{'b', '1',   "R,R,P0", 'b'},
};


int main(void)
{
	return machine_paper_run(instr_paper_program_mod, ARRAY_LEN(instr_paper_program_mod),
			         NULL, 0, 'b');
}
