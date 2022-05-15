namespace WebServer{

class SocketServer{
public:
    SocketServer = delete;
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
};

}