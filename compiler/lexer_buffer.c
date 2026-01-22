#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "config.h"
#include "fu_err.h"
#include "lexer_buffer.h"

FileStream *fe_lexer_creat_file_stream(size_t size) {
    FileStream* fs = malloc(sizeof(FileStream));
    fs->buf1 = malloc((size * sizeof(fe_char))+1);
    if(fs->buf1 == NULL) return NULL;
    fs->buf2 = malloc((size * sizeof(fe_char))+1);
    if(fs->buf2 == NULL) return NULL;
    fs->buf1[fs->size] = '\0';
    fs->buf2[fs->size] = '\0';
    fs->buf1_len = 0;
    fs->buf2_len = 0;
    fs->size = size;
    fs->used = 0;
    return fs;
}

int fe_lexer_read_file_stream(FILE *f, FileStream *fs) {
    fread(fs->buf1,fs->size,sizeof(fe_char),f);
    fs->buf1_len = strlen(fs->buf1);
    if(fs->buf1_len < fs->size) {
        fe_char *temp = realloc(fs->buf1, fs->buf1_len + 1);
        if(temp!=NULL) {
            fs->buf1 = temp;
        }
        fs->buf1[fs->buf1_len] = '\0';
        fs->used = 1;
        return 0;
    }
    fread(fs->buf2,fs->size,sizeof(fe_char),f);
    fs->buf2_len = strlen(fs->buf2);
    if(fs->buf2_len < fs->size) {
        fe_char *temp = realloc(fs->buf2, fs->buf2_len + 1);
        if(temp!=NULL) {
            fs->buf2 = temp;
        }
        fs->buf2[fs->buf2_len] = '\0';
    }
    fs->used = 2;
    return 0;
}

void fe_lexer_free_file_stream(FileStream *fs) {
    free(fs->buf1);
    free(fs->buf2);
    fs->buf1 = NULL;
    fs->buf2 = NULL;
    fs->size = 0;
    fs->used = 0;
}

Token *fe_lexer_next_token_buffer(FILE *f, FileStream *fs) {
    Token *tk = malloc(sizeof(Token));
    fe_int size = 0;
    fe_int line = 0;
    fe_int cow = 0;
    TokenType mode = TOKEN_NULL;
    fe_int buf_size = 400;
    fe_char *buffer = malloc((buf_size * sizeof(fe_char)) + 1);
    buffer[buf_size] = '\0';






    buffer[strlen(buffer)] = '\0';
    fe_char *temp = realloc(buffer, (strlen(buffer)*size)+1);
    if(temp!=NULL) {
        buffer = temp;
    }

    tk->cow = cow;
    tk->line = line;
    tk->type = mode;
    tk->value = buffer;
    return tk;
}
