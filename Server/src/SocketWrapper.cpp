#include <signal.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <errno.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include "SocketWrapper.hpp"

WebServer::Utils::SocketWrapper::SocketWrapper(char *ip_, int port_, int backlog_) : ip(ip_), port(port_), backlog(backlog_)
{
    printf("Socket constructed......\n");
    printf("IP:      %s\n", ip);
    printf("PORT:    %d\n", port);
    printf("BACKLOG: %d\n", backlog);
    printf("*****************************************\n");

    // Open Socket
    socketFd = socket(PF_INET, SOCK_STREAM, 0);
    if (-1 == socketFd)
    {
        printf("Error: Creating sockfd failed! errno: %d\n", errno);
        strerror(errno);
        return;
    }
    printf("SocketFd: %d\n", socketFd);
    printf("*****************************************\n");

    return;
}

WebServer::Utils::SocketWrapper::~SocketWrapper()
{
    close(socketFd);
}