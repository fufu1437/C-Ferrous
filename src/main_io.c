#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "config.h"
#include "fu_arr.h"
#include "lexer_io.h"
// #include "fu_err.h"
// #include "ast.h"

// char* fgetstr(FILE* f);

// int fuerr = FUERR_NULL;

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

        if(errno == E_number_err) {
            char buf[1000] = {'\0'};
            printf("%s-%d:%d ", argv[1], mode->line, mode->cow);
            printf("%s\n", mode->val);
            for(i64 i=0;i < mode->cow-1;i++) {
                buf[i] = ' ';
            }
            printf("%s^\n", buf);
        }
        else{
            if(mode!=NULL) {
                if(mode->type == TOKEN_Number) {
                    printf("%d  %f\n", mode->type, mode->val_num);
                }
                else{
                    printf("%d  %s\n", mode->type, mode->val);
                }
            }
        }
        
    }while(errno != E_FEILE_END);
    // free(mode->val);


    // fuarr_free_container(TkArr);
    fclose(f);
    return 0;
}
