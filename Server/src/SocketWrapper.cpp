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

WebServer::Utils::SocketWrapper::SocketWrapper(int socketFd_) : socketFd(socketFd_)
{
    printf("SocketFd: %d\n", socketFd);
    printf("*****************************************\n");
}

WebServer::Utils::SocketWrapper::~SocketWrapper()
{
    printf("SocketFd: %d\n", socketFd);
    printf("*****************************************\n");
    close(socketFd);
}