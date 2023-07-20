#pragma once
#define DEBUG_SILENT_PRINT (1)
#define DEBUG_PRINT(fmt, ...)                                                               \
    do                                                                                      \
    {                                                                                       \
        if (DEBUG_SILENT_PRINT)                                                             \
            fprintf(stdout, "[%s:%s():%d]" fmt, __FILE__, __func__, __LINE__, __VA_ARGS__); \
    } while (0)