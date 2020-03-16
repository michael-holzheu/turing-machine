#include <stdlib.h>

#include "helper.h"
#include "machine-paper.h"

static struct instr_paper instr_paper_program[] = {
	{'b', BLANK,   "P1,R,P0,R,P1,R,P1", 'c'},
	{'c', '0',     "P1,L",              'd'},
	{'c', '1',     "P0,L",              'c'},
	{'d', '*',     "",                FINAL},
};

int main(void)
{
	return machine_paper_run(instr_paper_program, ARRAY_LEN(instr_paper_program),
			         NULL, 0, 'b');
}
