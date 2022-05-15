namespace WebClient{

#define DEBUG_SILENT_PRINT    (1)
#define DEBUG_PRINT(fmt, ...)\
        do{\
            if(DEBUG_SILENT_PRINT) \
                fprintf(stdout, "[%s:%s():%d]" \
                    fmt, __FILE__, __func__, __LINE__, __VA_ARGS__);\
        } while(0)

class SocketClient{
public:
    SocketClient() = delete;
    SocketClient(
        char *ip_, int port_, int backlog_ 
    );
    ~SocketClient();

    int Start();

private:
    char *ip;
    int port;
    int backlog;

    struct sockaddr_in serverIpv4Address;
    int socketFd;

    int SendData(const char *, size_t);
};

}