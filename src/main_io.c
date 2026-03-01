#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "config.h"
#include "fu_arr.h"
#include "lexer_io.h"
// #include "fe_err.h"
// #include "ast.h"

// char* fgetstr(FILE* f);

// int fuerr = FEERR_NULL;

int main(int args, char *argv[]) {
    // FU_ARR *TkArr = fuarr_creat_arr(10);
    FILE* f= fopen(argv[1], "r");
    if(f==NULL) {
        return -1;
    }
    // char* mode = NULL;
    Token* mode;
    int index=0;
    do {
        errno = 0;
        mode = fe_lexer_next_token_io(f);


        if(mode!=NULL) {
            if(mode->type == TOKEN_Number) {
                printf("%s  %f\n", fe_lexer_type_char(mode->type), mode->val_num);
            }
            else{
                printf("%s  %s\n", fe_lexer_type_char(mode->type), mode->val);
            }
        }

        
    }while(errno != E_FEILE_END);
    // free(mode->val);


    // fuarr_free_container(TkArr);
    fclose(f);
    return 0;
}
