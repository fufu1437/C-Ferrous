#define __USE_POSIX
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include "fu_arr.h"
#include "fu_err.h"
#include "lexer_buffer.h"

int main(void) {
    FileStream *fs = fe_lexer_creat_file_stream(400);
    FILE *f = fopen("tets.fe", "r");
    struct stat st;
    fstat(fileno(f), &st);
    printf("size: %d\n", st.st_size);
    fe_lexer_read_file_stream(f, fs);
    printf(fs->buf1);
    fe_lexer_free_file_stream(fs);
    fclose(f);
    return 0;
}
