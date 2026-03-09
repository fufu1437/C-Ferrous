#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "lexer_io.h"
#include "config.h"

int peek(FILE *f);

Token *fe_lexer_next_token_io(FILE *f) {
    Token *tk = malloc(sizeof(Token));
    if(tk==NULL) { errno = ENOMEM; return NULL; }

    i64 line=1, row=0, size=400;
    i32 err = 0;
    double val_num = 0.0;
    TokenType mode = TOKEN_NULL;
    fe_char *buffer = malloc(size+1);
    if(buffer == NULL) {err = errno = ENOMEM; return NULL; }

    i64 index = 0;

    int ch;
    do{
        ch = fgetc(f);
        row++;
        if(ch == '\n') { line++; row=0; }
        if(ch == EOF) {
            err = errno = E_FEILE_END;
            mode = TOKEN_EOF;
            buffer[index++] = 'E';
            buffer[index++] = 'O';
            buffer[index++] = 'F';
            break;
        }
    }while(isspace(ch));

    if(ch=='/' && peek(f)=='/') {

        do{
            ch = fgetc(f);
        }while(ch!='\n');
        line++; row++;

    }

    else if(ch=='/'&&ch=='*') {
        do{
            ch = fgetc(f);
            row++;
            if(ch=='\n') { line++; row=0;}
        }while(ch=='*'&&peek(f)=='\\');

    }

    if(isalpha(ch)||ch=='_') {
        i32 o_cow = row;
        do{
            buffer[index++] = ch;
            ch = fgetc(f);
            row++;
            if(ch == EOF) {err = errno = E_FEILE_END; mode = TOKEN_EOF; break;}
        }while(isalnum(ch)||ch == '_');
        if(ch == '\n') {line++;row = 0;}
        ungetc(ch, f);
        mode = TOKEN_Identifier;
    }

    else if(isdigit(ch)) {
        mode = TOKEN_Number;
        int m = 0;
        do{
            buffer[index++] = ch;
            ch = fgetc(f);
            row++;
            if(ch == EOF) { err = errno = E_FEILE_END; }
            if(ch == 'b' || ch == 'B' || ch == 'x' || ch == 'X' || ch == 'o' || ch == 'O') {
                m = 1;
            }
            if((('a' <= ch && ch >= 'f') || ('a' <= ch && ch >= 'F')) && m != 1) {
                err = E_NUMBER_FORMAT;
                goto lexer_io_err;
            }
        }while (isdigit(ch) || (('a' <= ch && ch >= 'f') || ('a' <= ch && ch >= 'F')) || ch == '.');
        ungetc(ch, f);
        
        // 十六进制转十进制
        if(buffer[0] =='0' &&(buffer[1] =='x' || buffer[1] =='X')) {
            double t_out = 0.0;
            i64 base = 1;
            i64 t_index = 2;
            for(i64 i = index -1; i >=2;i--) {
                fe_char ch = buffer[i];
                if(ch>='A'&&ch<='Z') {
                    t_out += (ch - 55) * base;
                }
                else if(ch>='a'&&ch<='z') {
                    t_out += (ch - 87) * base;
                }
                else if(ch>='0'&&ch<='9') {
                    t_out += (ch - '0') * base;
                }
                else{
                    err = errno = E_NUMBER_FORMAT;
                    row = i + 1;
                    t_out = 0;
                    break;
                }
                base <<= 4;
            }
            val_num = t_out;
        }
        // 二进制转十进制
        else if(buffer[0] =='0' &&(buffer[1] =='b' || buffer[1] =='B')) {
            i64 t_out = 0;
            for(i64 i= 2;i < index ; i++) {
                if(!(buffer[i] == '1' || buffer[i] == '0')) {
                    err = errno = E_NUMBER_FORMAT;
                    row = i + 1;
                    t_out = 0;
                    break;
                }
                t_out <<= 1;
                t_out |= buffer[i] - '0';
            }
            val_num = (double)t_out;
        }
        // 十进制字符串转十进制
        else{
            i64 dot = 1;
            i32 m_dot = 0;
            i64 float_num = 1;
            for(i64 i=0; i< index; i++) {
                char ch = buffer[i];
                if(ch == '.') {
                    mode = TOKEN_Float;
                    continue;
                }
                if(!(ch>='0'&&ch<='9')) {
                    err = err = errno = E_NUMBER_FORMAT;
                    row--;
                    break;
                }
                if(mode == TOKEN_Float) {
                    val_num += (ch-'0') / (10 * float_num);
                    float_num *= 10;
                    continue;
                }
                val_num = val_num * 10 + (ch - '0');
            }
        }
    }


    else if(ch=='/') { row++; buffer[index++] = ch; mode = (peek(f) == '=' ? (ch = fgetc(f), buffer[index++]=ch, row++, TOKEN_DivAss) : TOKEN_Div); }
    else if(ch=='%') { row++; buffer[index++] = ch; mode = (peek(f) == '=' ? (ch = fgetc(f), buffer[index++]=ch, row++, TOKEN_ModAss) : TOKEN_Mod); }
    else if(ch=='+') { row++; buffer[index++] = ch; mode = (peek(f) == '=' ? (ch = fgetc(f), buffer[index++]=ch, row++, TOKEN_AddAss) : TOKEN_Add); }
    else if(ch=='-') { row++; buffer[index++] = ch; mode = (peek(f) == '=' ? (ch = fgetc(f), buffer[index++]=ch, row++, TOKEN_SubAss) : TOKEN_Sub); }
    else if(ch=='*') { row++; buffer[index++] = ch; mode = (peek(f) == '=' ? (ch = fgetc(f), buffer[index++]=ch, row++, TOKEN_MulAss) : TOKEN_Mul); }
    else if(ch=='=') { row++; buffer[index++] = ch; mode = (peek(f) == '=' ? (ch = fgetc(f), buffer[index++]=ch, row++, TOKEN_Eq    ) : TOKEN_Ass); }

    else if(ch=='(') { row++; buffer[index++] = ch; mode = TOKEN_LParen;   }
    else if(ch==')') { row++; buffer[index++] = ch; mode = TOKEN_RParen;   }
    else if(ch=='{') { row++; buffer[index++] = ch; mode = TOKEN_LBrace;   }
    else if(ch=='}') { row++; buffer[index++] = ch; mode = TOKEN_RBrace;   }
    else if(ch=='[') { row++; buffer[index++] = ch; mode = TOKEN_LBracket; }
    else if(ch==']') { row++; buffer[index++] = ch; mode = TOKEN_RBracket; }

    else if(ch==';') { row++; buffer[index++] = ch; mode = TOKEN_Semi;     }
    else if(ch=='#') { row++; buffer[index++] = ch; mode = TOKEN_Sharp;    }
    else if(ch=='<') { row++; buffer[index++] = ch; mode = TOKEN_Lt;       }
    else if(ch=='>') { row++; buffer[index++] = ch; mode = TOKEN_Gt;       }
    else if(ch=='.') { row++; buffer[index++] = ch; mode = TOKEN_Dot;      }
    else if(ch=='"')  { row++; buffer[index++] = ch; mode = TOKEN_Double_Quote; }
    else if(ch=='\'') { row++; buffer[index++] = ch; mode = TOKEN_Simgle_Quote; }

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
    tk->err = err;
    tk->row = row;
    tk->line = line;
    tk->type = mode;
    tk->size = size;
    tk->val = buffer;
    tk->val_num = val_num;
    return tk;




lexer_io_err:

    if(err == E_NUMBER_FORMAT) {
        ungetc(ch, f);
    }

    temp = realloc(buffer, 1);
    if(temp !=NULL) {
        buffer = temp;
    }
    buffer[0] = '\0';
    val_num = 0;
    tk->err = err;
    tk->row = row;
    tk->line = line;
    tk->type = mode;
    tk->size = size;
    tk->val = buffer;
    tk->val_num = val_num;
    return tk;
}

int peek(FILE *f) {
    int ch = fgetc(f);
    ungetc(ch, f);
    if(ch==EOF) return EOF;
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
