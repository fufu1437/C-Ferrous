#include "fe_err.h"
#include <stdio.h>
// int fuerr;

const char *feerr_char(FE_ERR err) {
    switch(err) {
        case FEERR_NULL:
            return "null err";
        case FEERR_FILE_END:
            return "file end";
        case FEERR_NO_MEMRY:
            return "no memry";
        case FEERR_NULL_PRT:
            return "null prt";
        case FEERR_FILE_READ_FAIL:
            return "file read dail";
        case FEERR_BUF_END:
            return "buf end";
    }
}

// int fuerr_set_err(FE_ERR err) {
//     fuerr = err;
//     return err;
// }

