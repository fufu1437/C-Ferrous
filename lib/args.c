#include "args.h"

#include <stdlib.h>

int get_args(char** s, ARG* a) {
    if(**s == '-') {
        switch(*(*s+1)) {
            case 'o': a->v = *(s+1); a->t = ARGS_OUTFILE; return 0;
        }
    }
    a->v = *s;
    a->t = ARGS_READ_FILE;
    return 0;
}