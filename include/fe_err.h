#ifndef FEERR_ferrous_fufu1437_h
#define FEERR_ferrous_fufu1437_h

typedef enum FE_ERR{
    FEERR_NULL = 1024000,     // 无错误

    FEERR_FILE_END, // 文件读取完成
    FEERR_FILE_READ_FAIL, // 文件读取失败
    FEERR_NO_MEMRY,   // 无法分配内存
    FEERR_BUF_END, // 缓冲区使用完毕

    FEERR_NUMBER_FORMAT, // 数字格式错误

    FEERR_NULL_PRT, // 空指针
}FE_ERR;

extern int feerr;

const char *feerr_char(FE_ERR err);

// int FEERR_set_err(FE_ERR err);

#endif
