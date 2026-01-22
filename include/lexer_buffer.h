#ifndef lexer_buffer__ferrous_fufu1437_h
#define lexer_buffer__ferrous_fufu1437_h

#include <stdio.h>

#include "config.h"

// typedef struct FileStream FileStream;

typedef struct FileStream{
    fe_int size;
    fe_char *buf1;
    fe_char *buf2;
    fe_int buf1_len;
    fe_int buf2_len;
    fe_int used;
}FileStream;

FileStream *fe_lexer_creat_file_stream(size_t size);

int fe_lexer_read_file_stream(FILE *f, FileStream *fs);

void fe_lexer_free_file_stream(FileStream *fs);

Token *fe_lexer_next_token_buffer(FILE *f, FileStream *fs);

#endif
