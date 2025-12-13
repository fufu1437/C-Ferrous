#ifndef lexer_ferrous_fufu1437_h
#define lexer_ferrous_fufu1437_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum TOKEN_TYPE {
    TOKEN_NULL = 0,                 // 空关键字
    TOKEN_KEYWORLDS,                // 关键字
    TOKEN_IDENTIFIER,               // 标识符
    TOKEN_PENDING_IDENTIFIER,       // 待处理标识符

    TOKEN_PENDING_NUMBER,           // 待处理数字

    TOKEN_IF,
    TOKEN_ELSE,
    // TOKEN_ELIF,
    TOKEN_ELSE_IF,

    TOKEN_FOR,
    TOKEN_WHILE,

    TOKEN_EOF,

    TOKEN_ERROR_DEF_FOLAT = 2048,
}TOKEN_TYPE;

// typedef enum{
// }TOKEN_ERROR;

typedef struct{
    char* value;      // TOKEN
    TOKEN_TYPE type;  // TOKEN 类型
    int line;         // 出现行
    int columnl;      // 出现时第一个字母的位置,作为编译报错的根据
    int len;
}TOKEN_V;

typedef struct{
    TOKEN_V* ov;     // 上一个 Token 值
    TOKEN_V* cv;     // 当前 Token 值
    TOKEN_V* nv;     // 下一个 Token 值
    // int line;        // 行
    // int column;      // 列 column
    TOKEN_TYPE t;
}TOKEN;

/*
* @name 判断token类型
*/
int fr_token_type_discern(TOKEN* tk);

/*
* @name 获取token
* @return  0 正常退出
* @return -1 未知错误
* @return -2 无效参数
* @return -3 文件结束
*/
int fr_next_token(FILE* f, TOKEN* tk);

#endif