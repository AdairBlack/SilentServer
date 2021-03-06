#include <signal.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <errno.h>

#include "SocketServer.hpp"

bool isStop = false;

WebServer::SocketServer::SocketServer(char *ip_, int port_, int backlog_):
                    ip(ip_), port(port_), backlog(backlog_)
{
    printf("WebServer starts......\n");
    printf("IP:      %s\n",ip);
    printf("PORT:    %d\n", port);        
    printf("BACKLOG: %d\n", backlog);   
    printf("*****************************************\n");

    //Open Socket
    socketFd = socket(PF_INET, SOCK_STREAM, 0);
    if(-1 == socketFd)
    {
        printf("Error: Creating sockfd failed! errno: %d\n", errno);
        return ;
    }
    printf("SocketFd: %d", socketFd);

    //Set ip data
    bzero(&ipv4Address, sizeof(ipv4Address));
    ipv4Address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &ipv4Address.sin_addr);
    ipv4Address.sin_port = htons(port);

    //Bind socket fd to ip
    int ret = bind(socketFd, (struct sockaddr*)&ipv4Address, sizeof(ipv4Address));
    if(-1 == ret)
    {
        printf("Error: Binding sockfd to ip failed! errno: %d\n", errno);
        return ;
    }

    return ;
}

int WebServer::SocketServer::Start()
{
    int ret = listen(socketFd, backlog);
    if(-1 == ret)
    {
        printf("Error: Listening! errno: %d\n", errno);
        return -1;
    }

    clientAddrLen = sizeof(clientAddress);
    int connfd = accept(socketFd, (struct sockaddr*) &clientAddress, &clientAddrLen);
    if(0 > connfd)
    {
        DEBUG_PRINT("errno: %d", errno);
        return -1;
    }

    char buffer[BUFFER_SIZE];

    memset(buffer, '\0', BUFFER_SIZE);
    ret = recv(connfd, buffer, BUFFER_SIZE - 1, 0);
    printf("got %d bytes of normal data '%s'\n", ret, buffer);

    memset(buffer, '\0', BUFFER_SIZE);
    ret = recv(connfd, buffer, BUFFER_SIZE - 1, MSG_OOB);
    printf("got %d bytes of normal data '%s'\n", ret, buffer);

    memset(buffer, '\0', BUFFER_SIZE);
    ret = recv(connfd, buffer, BUFFER_SIZE - 1, 0);
    printf("got %d bytes of normal data '%s'\n", ret, buffer);

    close(connfd);

    while(!isStop)
    {
        sleep(1);
    }

    printf("SilentServer closed by receiving signal.\n");
    close(socketFd);

    return 0;
}

// int WebServer::SocketServer::ReceiveData()
// {

// }