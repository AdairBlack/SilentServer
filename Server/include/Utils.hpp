#pragma once

// which interface to use
#define LOCAL_ETH_INERFACE ("enp0s31f6\0")
#define LOCAL_PORT_NUM (7777)

#define DEBUG_SILENT_PRINT (1)
#define DEBUG_PRINT(fmt, ...)                                                               \
    do                                                                                      \
    {                                                                                       \
        if (DEBUG_SILENT_PRINT)                                                             \
            fprintf(stdout, "[%s:%s():%d]" fmt, __FILE__, __func__, __LINE__, __VA_ARGS__); \
    } while (0)

#define IP_CHAR_MAX_LEN (16)

int GetLocalIp(char ip[IP_CHAR_MAX_LEN]);