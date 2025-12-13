#include "args.h"

#include <stdlib.h>

int get_args(char** s, ARG* a) {
    if(**s == '-') {
        switch(*(*s+1)) {
            case 'o': a->value = *(s+1); a->type = ARGS_OUTFILE; return 0;
        }
    }
    a->value = *s;
    a->type = ARGS_READ_FILE;
    return 0;
}