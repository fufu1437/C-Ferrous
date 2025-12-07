#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#include <sys/stat.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

long long getFileSize(const char *filename) {
#ifdef _WIN32
    // Windows 实现
    WIN32_FILE_ATTRIBUTE_DATA fileInfo;
    if (GetFileAttributesExA(filename, GetFileExInfoStandard, &fileInfo)) {
        LARGE_INTEGER size;
        size.LowPart = fileInfo.nFileSizeLow;
        size.HighPart = fileInfo.nFileSizeHigh;
        return size.QuadPart;
    }
#else
    // Linux/macOS 实现
    struct stat st;
    if (stat(filename, &st) == 0) {
        return st.st_size;
    }
#endif
    return -1;
}
