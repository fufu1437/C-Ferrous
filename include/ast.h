#ifndef ast_ferrous_fufu1437_h
#define ast_ferrous_fufu1437_h

#include "config.h"

typedef struct AST_node{
    // TokenType type;
    Token *token;
    struct AST_node *left;
    struct AST_node *right;
}AST_node;

AST_node *creat_ast();

#endif
