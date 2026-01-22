#ifndef config_fe_fufu1437_h
#define config_fe_fufu1437_h

typedef long long fe_int;
typedef char fe_char;

typedef enum TokenType{
        TOKEN_NULL,
        TOKEN_EOF ,

        // Operators : 0,

        /** 标识符 */ TOKEN_Identifier,

        // (
        TOKEN_LParen  ,
        // )
        TOKEN_RParen  ,
        // [
        TOKEN_LBracket,
        // ]
        TOKEN_RBracket,
        // {
        TOKEN_LBrace  ,
        // }
        TOKEN_RBrace  ,

        // =
        TOKEN_Ass,
        // \+
        TOKEN_Add,
        // \-
        TOKEN_Sub,
        // \*
        TOKEN_Mul,
        // \/
        TOKEN_Div,
        // %
        TOKEN_Mod,

        // ==
        TOKEN_Eq,
        // +=
        TOKEN_AddAss,
        // -=
        TOKEN_SubAss,
        // x=
        TOKEN_MulAss,
        // \/=
        TOKEN_DivAss,
        // %=
        TOKEN_ModAss,

        // \#
        TOKEN_Sharp,

        // <
        TOKEN_Lt,
        //>
        TOKEN_Gt,
        // .
        TOKEN_Dot,
        // '
        TOKEN_Simgle_Quote,
        // "
        TOKEN_Double_Quote,

        // 字符串
        TOKEN_String,
        // 数
        TOKEN_Number,
        // 二进制数
        TOKEN_BitNumber,
        // 十六进制数
        TOKEN_HexNumber,
        // ;
        TOKEN_Semi,
}TokenType;

typedef struct{
    TokenType type;
    fe_char *value;
    fe_int size;
    fe_int line; // token 列
    fe_int cow; // token 行
}Token;

const char *fe_lexer_type_char(TokenType t);


#endif
