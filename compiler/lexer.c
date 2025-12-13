#include "lexer.h"

// int type_discern(TOKEN* tk);

int next_test(FILE* f, char* tk) {
    char *o_tk; o_tk = tk;
    int p = fgetc(f);
    while(p) {
        if(p == '\n' || p == '\t' || p == '\b' || p == '\a') {
            while(p == '\n' || p == '\t' || p == '\b' || p == '\a') {
                p = fgetc(f);
            }
        }
        if((p>='a' && p<='z')||(p>='A' && p<='Z')||p=='_') {
            while((p>='a' && p<='z')||(p>='A' && p<='Z')||(p>='0' && p<='9')||p=='_') {
                *o_tk++ = p;
                p = fgetc(f);
            }
            *o_tk = '\0';
            o_tk = tk;
            break;
        }
    p = fgetc(f); }
    return 0;
}

void token_left_value(TOKEN* tk) {
    strcpy(tk->ov->value, tk->cv->value);
    strcpy(tk->cv->value, tk->nv->value);
}

TOKEN_TYPE next_char(FILE* f, char* c) {
    int p;
    char* o_c = c;
    // char* value = malloc(10);
    do{
        p = fgetc(f);
        if(p == EOF) {
            strcpy(c, "EOF");
            return TOKEN_EOF;
        }
    }while(p == ' ' || p == '\t' || p == '\a' || p == '\b' || p == '\n' || p == '\r');

    if((p>='a'&&p<='z')||(p>='A'&&p<='Z')||p=='_') {
        while((p>='a'&&p<='z')||(p>='A'&&p<='Z')||(p>='0'&&p<='9')||p=='_') {
            *c++ = p;
            p = getc(f);
        }
        *c='\0';
        c = o_c;
        return TOKEN_PENDING_IDENTIFIER;
    }
    else if(p>='0'&&p<='9') {
        int a=0;
        while((p>='0'&&p<='9')|| p == '.') {
            *c++ = p;
            p = getc(f);
            if(a>0 && p == '.') {
                *c='\0';
                c = o_c;
                return TOKEN_ERROR_DEF_FOLAT;
            }
            if(p=='.') {
                a++;
            }
        }
        *c='\0';
        c = o_c;
        return TOKEN_PENDING_NUMBER;
    }
}


int fr_next_token(FILE* f, TOKEN* tk) {
    if(f == NULL || tk == NULL) {
        return -2;
    }
    char *cv = tk->cv->value;
    char *ov = tk->ov->value;
    char *nv = tk->nv->value;
    int p;

// /*    do {
// *       p = getc(f);
// *       if(p == EOF) {
// *           tk->t = TOKEN_EOF;
// *           strcpy(tk->cv, "EOF");
// *           return -3;
// *       }
// *   }while(p == ' ' || p == '\n' || p == '\a' || p == '\b' || p == '\r');
// */





    return 0;
}


int is_token_type(TOKEN_V* tkv) {

}


int fr_token_type_discern(TOKEN* tk) {
    printf("fr_token_type_discern t: %d\n", tk->t);
    printf("fr_token_type_discern cv: %s\n", tk->cv);
    if((strcmp(tk->cv, "if") == 0) ) {
        tk->t = TOKEN_IF; return 0;
    }
    else if((strcmp(tk->cv, "else")==0)) {
        tk->t = TOKEN_ELSE; return 0;
    }
    else if(tk->t == TOKEN_ELSE && !(strcmp(tk->cv, "if"))) {
        tk->t = TOKEN_ELSE_IF;
        return 0;
    }
    return -1;
}
