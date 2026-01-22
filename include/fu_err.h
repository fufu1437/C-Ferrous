#ifndef fuerr_ferrous_fufu1437_h
#define fuerr_ferrous_fufu1437_h
#include <errno.h>
enum FU_ERR{
    FUERR_NULL = 102400,     // 无错误

    FUERR_FILE_END, // 文件读取完成
    FUERR_NO_MEMRY,   // 无法分配内存
};

extern int fuerr;

#endif
