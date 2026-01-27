#include "config.h"

const char *fe_lexer_type_char(TokenType type) {
    switch(type) {
        case TOKEN_Add:
            return "Add";
        case TOKEN_AddAss:
            return "AddAss";
        case TOKEN_Ass:
            return "Ass";
        case TOKEN_Div:
            return "Div";
        case TOKEN_DivAss:
            return "DivAss";
        case TOKEN_EOF:
            return "EOF";
        case TOKEN_Eq:
            return "Eq";
        case TOKEN_Identifier:
            return "Identifier";
        case TOKEN_LBrace:
            return "LBrace {";
        case TOKEN_RBrace:
            return "RBrace }";
        case TOKEN_LBracket:
            return "LBracket [";
        case TOKEN_RBracket:
            return "RBracket ]";
        case TOKEN_LParen:
            return "LParen (";
        case TOKEN_RParen:
            return "RParen )";
        case TOKEN_Mod:
            return "Mod";
        case TOKEN_ModAss:
            return "ModAss";
        case TOKEN_Mul:
            return "Mul";
        case TOKEN_MulAss:
            return "MulAss";
        case TOKEN_NULL:
            return "NULL";
        case TOKEN_String:
            return "String";
        case TOKEN_Sub:
            return "Sub";
        case TOKEN_SubAss:
            return "SubAss";
        case TOKEN_Semi:
            return "Semi ;";
        case TOKEN_Number:
            return "Number";
        case TOKEN_Sharp:
            return "Sharp";
        case TOKEN_Lt:
            return "Lt <";
        case TOKEN_Gt:
            return "Gt >";
        case TOKEN_Dot:
            return "Dot";
        case TOKEN_Simgle_Quote:
            return "Simgle_Quote '";
        case TOKEN_Double_Quote:
            return "Double_Quote \"";
    }
}
