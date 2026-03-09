#include <stdlib.h>
#include <stdlib.h>
#include <errno.h>

#include "ast.h"

#include "fe_arr.h"

typedef struct AST_node {
    // TokenType type;
    Token *token;
    struct AST_node *left;
    struct AST_node *right;
}AST_node;

AST_node *creat_ast(FE_ARR *arr) {
    if(arr == NULL) {
        errno = EINVAL;
        return NULL;
    }
    int arr_len = fearr_len(arr);
    AST_node *root_node = malloc(sizeof(AST_node));
    if(root_node == NULL) {
        errno = ENOMEM;
        return NULL;
    }
    for(int i = 0; i < arr_len; i++) {
        
    }



    return root_node;
}
