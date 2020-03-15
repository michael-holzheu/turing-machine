#include <stdlib.h>

#include "helper.h"
#include "machine-paper.h"

static struct instr_paper instr_paper_program[] = {
	{'b', '*',   "Pe,R,Pe,R,P0,R,R,P0,L,L", 'o'},
	{'o', '1',   "R,Px,L,L,L",              'o'},
	{'o', '0',   "",                        'q'},
	{'q', '+',   "R,R",                     'q'},
	{'q', BLANK, "P1,L",                    'p'},
	{'p', 'x',   "E,R",                     'q'},
	{'p', 'e',   "R",                       'f'},
	{'p', BLANK, "L,L",                     'p'},
	{'f', '+',   "R,R",                     'f'},
	{'f', BLANK, "P0,L,L",                  'o'},
};

int main(void)
{
	return machine_paper_run(instr_paper_program, ARRAY_LEN(instr_paper_program),
			         NULL, 0, 'b');
}
