namespace WebServer{

#define DEBUG_SILENT_PRINT    (1)
#define DEBUG_PRINT(fmt, ...)\
        do{\
            if(DEBUG_SILENT_PRINT) \
                fprintf(stdout, "[%s:%s():%d]" \
                    fmt, __FILE__, __func__, __LINE__, __VA_ARGS__);\
        } while(0)

#define BUFFER_SIZE     (1024)

class SocketServer{
public:
    SocketServer() = delete;
    SocketServer(
        char *ip_, int port_, int backlog_ 
    );

    int Start();

private:
    char *ip;
    int port;
    int backlog;

    struct sockaddr_in ipv4Address;
    int socketFd;

    struct sockaddr_in clientAddress;
    socklen_t clientAddrLen;

    // int ReceiveData();
};

}