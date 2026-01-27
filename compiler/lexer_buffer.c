#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// #include "file.h"
#include "config.h"
#include "fu_err.h"
#include "lexer_buffer.h"

State Pattern = State_Null;

FileStream *fe_lexer_creat_file_stream(size_t size) {
    FileStream *fs = malloc(sizeof(FileStream));
    fs->buf1 = malloc((size * sizeof(fe_char))+1);
    if(fs->buf1 == NULL) return NULL;
    fs->buf2 = malloc((size * sizeof(fe_char))+1);
    if(fs->buf2 == NULL) return NULL;
    fs->buf1[size] = '\0';
    fs->buf2[size] = '\0';
    fs->buf1_len = 0;
    fs->buf2_len = 0;
    fs->size = size;
    fs->used = State_Null;
    return fs;
}

int fe_lexer_read_buf1(FILE *f, FileStream *fs) {
    if(f  == NULL) { fuerr = FUERR_NULL_PRT; return 1; }
    if(fs == NULL) { fuerr = FUERR_NULL_PRT; return 1; }
    fread(fs->buf1, fs->size, sizeof(fe_char), f);
    if(fs->buf1 == NULL) {
        fuerr = FUERR_FILE_READ_FAIL;
        return 2;
    }
    fs->buf1_len = strlen(fs->buf1);
    fs->buf1[fs->buf1_len] = '\0';
    return 0;
}

int fe_lexer_read_buf2(FILE *f, FileStream *fs) {
    if(f  == NULL) { fuerr = FUERR_NULL_PRT; return 1; }
    if(fs == NULL) { fuerr = FUERR_NULL_PRT; return 1; }
    fread(fs->buf2, fs->size, sizeof(fe_char), f);
    if(fs->buf2 == NULL) {
        fuerr = FUERR_FILE_READ_FAIL;
        return 2;
    }
    fs->buf2_len = strlen(fs->buf2);
    fs->buf2[fs->buf2_len] = '\0';
    return 0;
}

void fe_lexer_free_file_stream(FileStream *fs) {
    free(fs->buf1);
    free(fs->buf2);
    free(fs);
    fs = NULL;
}

int fe_getc(FileStream *fs) {
    if(fs==NULL) { fuerr = FUERR_NULL_PRT; return -1; }

    return 0;
}

Token *fe_lexer_next_token_buffer(FILE *f, FileStream *fs) {
    Token *tk = malloc(sizeof(Token));
    fe_int size = 0;
    fe_int line = 0;
    fe_int cow = 0;
    TokenType mode = TOKEN_NULL;
    fe_int buf_size = 400;
    fe_char *buffer = malloc(buf_size * sizeof(fe_char) + 1);
    fe_int use_buf = 0;
    fe_int index = 0;
    buffer[buf_size] = '\0';
    fe_char *buf;
    #define peek() buf[index+1]
    #define next() buf[index++]
    #define back() buf[index-1]
    switch(fs->used) {
        case State_Null: do{ Pattern = State_Read_Buf1;
            buf = fs->buf1;
        }while(0); break;
        case State_Read_Buf1: do{
            buf = fs->buf1;
        }while(0); break;
        case State_Read_Buf2: do{
            buf = fs->buf2;
        }while(0); break;
        case State_Buf1_End: do{
            buf = fs->buf2;
        }while(0); break;
        case State_Buf2_End: do{
            buf = fs->buf2;
        }while(0); break;
    }
    int ch = next();
    buffer[strlen(buffer)] = '\0';
    fe_char *temp = realloc(buffer, strlen(buffer) * sizeof(fe_char)+1);
    if(temp != NULL) {
        buffer = temp;
    }

    tk->cow = cow;
    tk->line = line;
    tk->type = mode;
    tk->value = buffer;
    return tk;
}
