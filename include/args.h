#ifndef args_ferrous_fufu1437_h
#define args_ferrous_fufu1437_h

enum{
    // ARGS_OUT,
    ARGS_READ_FILE = 1024,
    ARGS_OUTFILE,
};

typedef struct{
    char* value; // 参数
    int type;   // 类型
}ARG;

int get_args(char** s, ARG* a);

#endif