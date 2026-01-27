#include <stdio.h>
#include <stdlib.h>
// #include <string.h>
// #include <ctype.h>

#include "fu_arr.h"
#include "lexer_io.h"
#include "fu_err.h"
// #include "ast.h"

char* fgetstr(FILE* f);

int fuerr = FUERR_NULL;

int main(int args, char *argv[]) {
    FU_ARR *TkArr = fuarr_creat_arr(10);
    FILE* f= fopen(argv[1], "r");
    if(f==NULL) {
        return -1;
    }
    // char* mode = NULL;
    Token* mode;
    int index=0;
    do {
        mode = fe_lexer_next_token_io(f);

        if(mode!=NULL) {
            printf("%d  %s\n", mode->type, mode->value);
            printf("%s index: %d\n", fe_lexer_type_char(mode->type),index++);
            fuarr_push(TkArr, mode);
        }

    }while(fuerr != FUERR_FILE_END);
    // free(mode->value);
    printf("arr len: %ld\n", fuarr_len(TkArr));

    for(size_t i=0;i<fuarr_len(TkArr);i++) {
        fe_char *temp = ((Token*)fuarr_get(TkArr, i))->value;
        if(temp!=NULL) {
            free(temp);
        }
        // free(fuarr_get(TkArr,i));
    }
    // fuarr_free_container(TkArr);
    fuarr_free_all(TkArr);
    fclose(f);
    return 0;
}
