#ifndef fuerr_ferrous_fufu1437_h
#define fuerr_ferrous_fufu1437_h

typedef enum FU_ERR{
    FUERR_NULL = 102400,     // 无错误

    FUERR_FILE_END, // 文件读取完成
    FUERR_FILE_READ_FAIL, // 文件读取失败
    FUERR_NO_MEMRY,   // 无法分配内存
    FUERR_BUF_END, // 缓冲区使用完毕

    FUERR_NULL_PRT, // 空指针
}FU_ERR;

extern int fuerr;

const char *fuerr_char(FU_ERR err);

// int fuerr_set_err(FU_ERR err);

#endif
