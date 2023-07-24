#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <cstring>
#include <netdb.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include "Utils.hpp"
#include "SocketServer.hpp"

extern bool isStop;

static void HandleTerm(int sig)
{
    isStop = true;
}

int main(int argc, char **argv)
{
    printf("*****************************************\n");
    printf("*            Silent Server              *\n");
    printf("*                                       *\n");
    printf("*              By  Edgar                *\n");
    printf("*****************************************\n");

    char ip[IP_CHAR_MAX_LEN] = {0};

    signal(SIGTERM, HandleTerm);

    if (0 != GetLocalIp(ip))
    {
        printf("Error:[%s %d %s()] Get local ip failed!", __FILE__, __LINE__, __func__);
    }

    WebServer::SocketServer socketServer(ip, LOCAL_PORT_NUM, 5);

    socketServer.start();

    return 0;
}