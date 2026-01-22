#include "config.h"

const char *fe_lexer_type_char(TokenType t) {
    switch(t) {
        case TOKEN_Add:
            return "Add\0";
        case TOKEN_AddAss:
            return "AddAss\0";
        case TOKEN_Ass:
            return "Ass\0";
        case TOKEN_Div:
            return "Div\0";
        case TOKEN_DivAss:
            return "DivAss\0";
        case TOKEN_EOF:
            return "EOF\0";
        case TOKEN_Eq:
            return "Eq\0";
        case TOKEN_Identifier:
            return "Identifier\0";
        case TOKEN_LBrace:
            return "LBrace {\0";
        case TOKEN_RBrace:
            return "RBrace }\0";
        case TOKEN_LBracket:
            return "LBracket [\0";
        case TOKEN_RBracket:
            return "RBracket ]\0";
        case TOKEN_LParen:
            return "LParen (\0";
        case TOKEN_RParen:
            return "RParen )\0";
        case TOKEN_Mod:
            return "Mod\0";
        case TOKEN_ModAss:
            return "ModAss\0";
        case TOKEN_Mul:
            return "Mul\0";
        case TOKEN_MulAss:
            return "MulAss\0";
        case TOKEN_NULL:
            return "NULL\0";
        case TOKEN_String:
            return "String\0";
        case TOKEN_Sub:
            return "Sub\0";
        case TOKEN_SubAss:
            return "SubAss\0";
        case TOKEN_Semi:
            return "Semi ;\0";
        case TOKEN_Number:
            return "Number\0";
        case TOKEN_Sharp:
            return "Sharp\0";
        case TOKEN_Lt:
            return "Lt <\0";
        case TOKEN_Gt:
            return "Gt >\0";
        case TOKEN_Dot:
            return "Dot\0";
        case TOKEN_Simgle_Quote:
            return "Simgle_Quote '\0";
        case TOKEN_Double_Quote:
            return "Double_Quote \"\0";
    }
}
