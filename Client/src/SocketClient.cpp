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

#include "SocketClient.hpp"

bool isStop = false;

WebClient::SocketClient::SocketClient(char *ip_, int port_, int backlog_):
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
    bzero(&serverIpv4Address, sizeof(serverIpv4Address));
    serverIpv4Address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &serverIpv4Address.sin_addr);
    serverIpv4Address.sin_port = htons(port);

    if(0 != connect(socketFd, (struct sockaddr*) &serverIpv4Address, sizeof(serverIpv4Address)))
    {
        printf("Error: Connect server socket! errno: %d\n", errno);
        return ;
    }

    return ;
}

int WebClient::SocketClient::SendData(const char *data, size_t dataSize)
{
    if(nullptr == data)
    {
        printf("Error: nullptr data!\n");
    }

    if(-1 == send(socketFd, data, dataSize, 0))
    {
        DEBUG_PRINT("Creating sockfd failed! errno: %d.\n", errno);
        return -1;
    }

    return 0;

}

int WebClient::SocketClient::Start()
{

    const char *dataFirst = "abc";
    const char *dataSecond = "123";

    printf("Client:Begin to send data.\n");

    SendData(dataSecond, strlen(dataSecond));
    SendData(dataFirst, strlen(dataFirst));
    SendData(dataSecond, strlen(dataSecond));

    printf("Client:Finished sending data.\n");

    return 0;
}

WebClient::SocketClient::~SocketClient()
{
    close(socketFd);
    return ;
}