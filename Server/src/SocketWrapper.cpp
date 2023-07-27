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

int WebServer::Utils::SocketWrapper::socketBind()
{
    // Set ip data
    bzero(&ipv4Address, sizeof(ipv4Address));
    ipv4Address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &ipv4Address.sin_addr);
    ipv4Address.sin_port = htons(port);

    // Bind socket fd to ip
    int ret = bind(socketFd, (struct sockaddr *)&ipv4Address, sizeof(ipv4Address));
    if (-1 == ret)
    {
        printf("Error: Binding sockfd to ip failed! errno: %d\n", errno);
        return -1;
    }
    return 0;
}

WebServer::Utils::SocketWrapper::~SocketWrapper()
{
    close(socketFd);
}