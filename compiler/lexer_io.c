#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// #include <errno.h>

#include "lexer_io.h"
#include "fu_err.h"
#include "config.h"

int peek(FILE *f);


Token *fe_lexer_next_token_io(FILE *f) {
    Token *tk = malloc(sizeof(Token));
    if(tk==NULL) {fuerr = FUERR_NO_MEMRY; return NULL; }

    fe_int line=1; fe_int cow=0; fe_int size=400; TokenType mode=TOKEN_NULL;
    fe_char *buffer = malloc(size+1);
    if(buffer == NULL) {fuerr = FUERR_NO_MEMRY; return NULL; }

    fe_int index = 0;

    int ch;
    do{
        ch = fgetc(f);
        cow++;
        if(ch == '\n') { line++; cow=0; }
        if(ch == EOF) {
            fuerr = FUERR_FILE_END;
            mode = TOKEN_EOF;
            buffer[index++] = 'E';
            buffer[index++] = 'O';
            buffer[index++] = 'F';
            break;
        }
    }while(isspace(ch));

    if(ch=='\\' && peek(f)=='\\') {

        do{
            ch = fgetc(f);
        }while(ch!='\n');
        line++; cow++;

    }

    else if(ch=='\\'&&ch=='*') {
        do{
            ch = fgetc(f);
            cow++;
            if(ch=='\n') { line++; cow=0;}
        }while(ch=='*'&&peek(f)=='\\');

    }



    

    if(isalpha(ch)||ch=='_') {
        fe_int o_cow = cow;
        do{
            buffer[index++] = ch;
            ch = fgetc(f);
            cow++;
            if(ch == EOF) {fuerr = FUERR_FILE_END; mode = TOKEN_EOF; break;}
        }while(isalnum(ch)||ch == '_');
        if(ch == '\n') {line++;cow = 0;}
        ungetc(ch, f);
        mode = TOKEN_Identifier;
    }

    else if(isdigit(ch)) {
        if(ch=='0'&& (peek(f)=='x'||peek(f)=='X')) {
            mode = TOKEN_HexNumber;
        }
        else if(ch=='0'&& (peek(f)=='b'||peek(f)=='B')) {
            mode = TOKEN_BitNumber;
        }
        mode = TOKEN_Number;
        do{
            buffer[index++] = ch;
            ch = fgetc(f);
        }
        while (isdigit(ch)||
        (ch=='x'||ch=='X')||
        (ch=='b'||ch=='B'));
    }

    else if(ch=='/') { cow++; buffer[index++] = ch; mode = (peek(f) == '=' ? (ch = fgetc(f), buffer[index++]=ch, cow++, TOKEN_DivAss) : TOKEN_Div); }
    else if(ch=='%') { cow++; buffer[index++] = ch; mode = (peek(f) == '=' ? (ch = fgetc(f), buffer[index++]=ch, cow++, TOKEN_ModAss) : TOKEN_Mod); }
    else if(ch=='+') { cow++; buffer[index++] = ch; mode = (peek(f) == '=' ? (ch = fgetc(f), buffer[index++]=ch, cow++, TOKEN_AddAss) : TOKEN_Add); }
    else if(ch=='-') { cow++; buffer[index++] = ch; mode = (peek(f) == '=' ? (ch = fgetc(f), buffer[index++]=ch, cow++, TOKEN_SubAss) : TOKEN_Sub); }
    else if(ch=='*') { cow++; buffer[index++] = ch; mode = (peek(f) == '=' ? (ch = fgetc(f), buffer[index++]=ch, cow++, TOKEN_MulAss) : TOKEN_Mul); }
    else if(ch=='=') { cow++; buffer[index++] = ch; mode = (peek(f) == '=' ? (ch = fgetc(f), buffer[index++]=ch, cow++, TOKEN_Eq    ) : TOKEN_Ass); }

    else if(ch=='(') { cow++; buffer[index++] = ch; mode = TOKEN_LParen;   }
    else if(ch==')') { cow++; buffer[index++] = ch; mode = TOKEN_RParen;   }
    else if(ch=='{') { cow++; buffer[index++] = ch; mode = TOKEN_LBrace;   }
    else if(ch=='}') { cow++; buffer[index++] = ch; mode = TOKEN_RBrace;   }
    else if(ch=='[') { cow++; buffer[index++] = ch; mode = TOKEN_LBracket; }
    else if(ch==']') { cow++; buffer[index++] = ch; mode = TOKEN_RBracket; }

    else if(ch==';') { cow++; buffer[index++] = ch; mode = TOKEN_Semi;     }
    else if(ch=='#') { cow++; buffer[index++] = ch; mode = TOKEN_Sharp;    }
    else if(ch=='<') { cow++; buffer[index++] = ch; mode = TOKEN_Lt;       }
    else if(ch=='>') { cow++; buffer[index++] = ch; mode = TOKEN_Gt;       }
    else if(ch=='.') { cow++; buffer[index++] = ch; mode = TOKEN_Dot;      }
    else if(ch=='"')  { cow++; buffer[index++] = ch; mode = TOKEN_Double_Quote; }
    else if(ch=='\'') { cow++; buffer[index++] = ch; mode = TOKEN_Simgle_Quote; }

    else {
        if(mode != TOKEN_EOF) {
            mode = TOKEN_NULL;
            buffer[index++]='n';
            buffer[index++]='u';
            buffer[index++]='l';
            buffer[index++]='l';
        }
    }
    buffer[index] = '\0';
    fe_char *temp = realloc(buffer, strlen(buffer)+1);
    if(temp !=NULL) {
        buffer = temp;
    }
    tk->cow = cow;
    tk->line = line;
    tk->type = mode;
    tk->size = size;
    tk->value = buffer;
    return tk;


}

int peek(FILE *f) {
    int ch = fgetc(f);
    if(ch==EOF) return EOF;
    ungetc(ch, f);
    return ch;
}

// const char *fe_lexer_type_char(TokenType t) {
//     switch(t) {
//         case TOKEN_Add:
//             return "Add\0";
//         case TOKEN_AddAss:
//             return "AddAss\0";
//         case TOKEN_Ass:
//             return "Ass\0";
//         case TOKEN_Div:
//             return "Div\0";
//         case TOKEN_DivAss:
//             return "DivAss\0";
//         case TOKEN_EOF:
//             return "EOF\0";
//         case TOKEN_Eq:
//             return "Eq\0";
//         case TOKEN_Identifier:
//             return "Identifier\0";
//         case TOKEN_LBrace:
//             return "LBrace {\0";
//         case TOKEN_RBrace:
//             return "RBrace }\0";
//         case TOKEN_LBracket:
//             return "LBracket [\0";
//         case TOKEN_RBracket:
//             return "RBracket ]\0";
//         case TOKEN_LParen:
//             return "LParen (\0";
//         case TOKEN_RParen:
//             return "RParen )\0";
//         case TOKEN_Mod:
//             return "Mod\0";
//         case TOKEN_ModAss:
//             return "ModAss\0";
//         case TOKEN_Mul:
//             return "Mul\0";
//         case TOKEN_MulAss:
//             return "MulAss\0";
//         case TOKEN_NULL:
//             return "NULL\0";
//         case TOKEN_String:
//             return "String\0";
//         case TOKEN_Sub:
//             return "Sub\0";
//         case TOKEN_SubAss:
//             return "SubAss\0";
//         case TOKEN_Semi:
//             return "Semi ;\0";
//         case TOKEN_Number:
//             return "Number\0";
//     }
// }
