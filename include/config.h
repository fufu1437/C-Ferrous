#ifndef config_fe_fufu1437_h
#define config_fe_fufu1437_h

// #define _BOOL

#include <stdint.h>

typedef int32_t i32;
typedef int64_t i64;
typedef char fe_char;


enum{
    // 文件读取完毕
    E_FEILE_END = 1024000,
    // Number格式错误
    E_NUMBER_FORMAT,
};

// #define True 1
// #define False 0
// 
// typedef char bool;

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
        // 十进制数
        TOKEN_Number,
        // 浮点数
        TOKEN_Float,
        // ;
        TOKEN_Semi,
}TokenType;

typedef struct{
    TokenType type;
    fe_char *val;
    double val_num;
    i32 size;
    i32 line; // token 列
    i32 row; // token 行
    i32 err;// 错误码
}Token;

const char *fe_lexer_type_char(TokenType t);


#endif
