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

#include "WebServer.hpp"
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

    signal(SIGTERM, HandleTerm);

    char ip[20] = {0};
    strncpy(ip, "192.168.0.10", sizeof("192.168.0.10\0"));

    SocketServer::WebServer webServer(ip, 7777, 5);

    webServer.Start();

    return 0;

}