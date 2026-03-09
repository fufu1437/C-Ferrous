#define STBDS_NO_SHORT_NAMES 
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "config.h"
#define FEARR_IMPLEMENTATION
#include "fe_arr.h"
#include "lexer_io.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

// #include "fe_err.h"
// #include "ast.h"

// char* fgetstr(FILE* f);

// int fuerr = FEERR_NULL;

int main(int args, char *argv[]) {
    FE_ARR *tokens = fearr_creat_arr(10);
    if(args <= 1) {
        printf("no file\n");
        return 1;
    }
    FILE *f= fopen(argv[1], "r");
    if(f == NULL) {
        return -1;
    }
    // char* mode = NULL;
    typedef struct {
        char *key;
        int value;
    }hmmap;
    hmmap *fa= NULL;
    stbds_hmput(fa, "asd", 12);
    printf("%d\n", stbds_hmget(fa, "asd"));
    Token *mode;
    int index=0;
    do {
        errno = 0;
        mode = fe_lexer_next_token_io(f);



        if(mode != NULL) {
            // if(mode->type == TOKEN_Number) {
            //     printf("%s  %f\n", fe_lexer_type_char(mode->type), mode->val_num);
            // }
            // else {
            //     printf("%s  %s\n", fe_lexer_type_char(mode->type), mode->val);
            // }
            fearr_put(tokens, mode);
        }


    } while(errno != E_FEILE_END);
    // free(mode->val);
    printf("len: %d\n", fearr_len(tokens));
    // printf("val: %f\n", ;
    ((fearr_get(tokens, 0)));
    int len = fearr_len(tokens);
    // for(int i=0; i < len; i++) {
    //     if(mode->type == TOKEN_Number) {
    //         printf("%s  %f\n", fe_lexer_type_char(mode->type), mode->val_num);
    //     }
    //     else {
    //         printf("%s  %s\n", fe_lexer_type_char(mode->type), mode->val);
    //     }
    // }
    for(int i=0; i < len; i++) {
        if(fearr_get(tokens, i) == NULL) break;
        printf("i: %d\n", i);
        if((((Token *)(fearr_get(tokens, i)))->type == TOKEN_Number)||((Token *)(fearr_get(tokens, i)))->type == TOKEN_EOF) continue;
        free(((Token *)(fearr_get(tokens, i)))->val);
    }
    fearr_free_all(tokens);

    fclose(f);
    return 0;
}
