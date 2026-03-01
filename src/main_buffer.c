#include <stdio.h>

// #include "fu_arr.h"
// #include "fe_err.h"
#include "lexer_buffer.h"

int main(void) {
    FileStream *fs = fe_lexer_creat_file_stream(400);
    FILE *f = fopen("tets.fe", "r");

    printf("%s\n", fs->buf1);
    fe_lexer_free_file_stream(fs);
    fclose(f);
    return 0;
}
