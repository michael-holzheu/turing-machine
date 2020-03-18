#include <stdlib.h>

#include "lib/machine-paper.h"
#include "lib/util_base.h"

static struct instr_paper instr_paper_program[] = {
	{'b', BLANK,   "P1,R,P0,R,P1,R,P1", 'c'},
	{'c', '0',     "P1,L",              'd'},
	{'c', '1',     "P0,L",              'c'},
	{'d', '*',     "",                FINAL},
};

int main(void)
{
	return machine_paper_run(instr_paper_program, (int) UTIL_ARRAY_SIZE(instr_paper_program),
			         NULL, 0, 'b');
}
