#ifndef lexer_buffer__ferrous_fufu1437_h
#define lexer_buffer__ferrous_fufu1437_h

#include <stdio.h>

#include "config.h"

// typedef struct FileStream FileStream;

typedef enum State{
    State_Null = 100,

    State_Read_Buf1,
    State_Read_Buf2,

    State_Buf1_End,
    State_Buf2_End,
}State;

typedef struct FileStream{
    State used;
    fe_int size;
    fe_char *buf1;
    fe_char *buf2;
    fe_int buf1_len;
    fe_int buf2_len;
}FileStream;

// 状态
extern State pattern;

FileStream *fe_lexer_creat_file_stream(size_t size);

void fe_lexer_free_file_stream(FileStream *fs);

Token *fe_lexer_next_token_buffer(FILE *f, FileStream *fs);

#endif
