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

#include "Utils.hpp"
#include "SocketServer.hpp"

bool isStop = false;

WebServer::SocketServer::SocketServer(char *ip_, int port_, int backlog_) : ip(ip_), port(port_), backlog(backlog_)
{
    printf("WebServer starts......\n");
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

    // Set ip data
    bzero(&ipv4Address, sizeof(ipv4Address));
    ipv4Address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &ipv4Address.sin_addr);
    ipv4Address.sin_port = htons(port);

    //get receive buffer size
    int recvBufSize = 0;
    socklen_t optlen = sizeof(recvBufSize);
    int retval = getsockopt(socketFd, SOL_SOCKET, SO_RCVBUF, &recvBufSize, &optlen);
    if (-1 == retval)
    {
        printf("Error: Getting receive buffer size failed! errno: %d\n", errno);
        return;
    }
    printf("Receive buffer size: %d\n", recvBufSize);

    // get socket name
    struct sockaddr_in localAddr;
    socklen_t addrLen = sizeof(localAddr);
    retval = getsockname(socketFd, (struct sockaddr *)&localAddr, &addrLen);
    if (-1 == retval)
    {
        printf("Error: Getting socket name failed! errno: %d\n", errno);
        return;
    }
    printf("Local IP:   %s\n", inet_ntoa(localAddr.sin_addr));
    printf("Local Port: %d\n", ntohs(localAddr.sin_port));

    // Bind socket fd to ip
    int ret = bind(socketFd, (struct sockaddr *)&ipv4Address, sizeof(ipv4Address));
    if (-1 == ret)
    {
        printf("Error: Binding sockfd to ip failed! errno: %d\n", errno);
        return;
    }

    return;
}

int WebServer::SocketServer::start()
{
    printf("%s\n", __func__);
    int ret = 0;
    int connfd = 0;
    char buffer[BUFFER_SIZE];

    while (!isStop)
    {
        ret = listen(socketFd, backlog);
        if (-1 == ret)
        {
            DEBUG_PRINT("Error: Listening! errno: %d\n", errno);
            return -1;
        }

        clientAddrLen = sizeof(clientAddress);
        connfd = accept(socketFd, (struct sockaddr *)&clientAddress, &clientAddrLen);
        if (0 > connfd)
        {
            DEBUG_PRINT("errno: %d", errno);
            return -1;
        }

        memset(buffer, '\0', BUFFER_SIZE);
        ret = recv(connfd, buffer, BUFFER_SIZE - 1, 0);
        printf("[Normal]got %d bytes of normal data '%s'\n", ret, buffer);
        sleep(1);

        close(connfd);
    }

    close(socketFd);

    printf("SilentServer closed by receiving signal.\n");

    return 0;
}

// int WebServer::SocketServer::ReceiveData()
// {

// }
