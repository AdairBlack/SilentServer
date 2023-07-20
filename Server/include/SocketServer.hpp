#pragma once

#include "Utils.hpp"

namespace WebServer
{

#define BUFFER_SIZE (1024)

    class SocketServer
    {
    public:
        SocketServer() = delete;
        SocketServer(char *ip_, int port_, int backlog_);

        int start();

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