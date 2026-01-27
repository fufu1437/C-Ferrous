#include "fu_err.h"
#include <stdio.h>
int fuerr;

const char *fuerr_char(FU_ERR err) {
    switch(err) {
        case FUERR_NULL:
            return "null err";
        case FUERR_FILE_END:
            return "file end";
        case FUERR_NO_MEMRY:
            return "no memry";
        case FUERR_NULL_PRT:
            return "null prt";
        case FUERR_FILE_READ_FAIL:
            return "file read dail";
        case FUERR_BUF_END:
            return "buf end";
    }
}

// int fuerr_set_err(FU_ERR err) {
//     fuerr = err;
//     return err;
// }

