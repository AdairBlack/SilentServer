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

#include "SocketClient.hpp"
#define IP_CHAR_MAX_LEN       (16)
#define LOCAL_ETH_INERFACE    ("enp0s31f6\0")
#define LOCAL_PORT_NUM        (7777)


extern bool isStop;

static void HandleTerm(int sig)
{
    isStop = true;
}

static int GetLocalIp(char ip[IP_CHAR_MAX_LEN])
{
    printf("Get local eth intfs...\n");
    if(nullptr == ip)
    {
        printf("Error:[%s %d %s()] nullptr!!!", __FILE__, __LINE__, __func__);
        return -1;
    }

    int sockfd;
    struct ifconf ifconf;
    struct ifreq *pIfreq;
    char buf[512];
    
    ifconf.ifc_len = 512;
    ifconf.ifc_buf = buf;

    if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        return -1;
    }

    ioctl(sockfd, SIOCGIFCONF, &ifconf);

    pIfreq = (struct ifreq*)ifconf.ifc_buf;

    for(int i = (ifconf.ifc_len/sizeof(struct ifreq)); i > 0; i--)
    {
        if(AF_INET == pIfreq->ifr_flags)
        {
            if(!strncmp(pIfreq->ifr_name, LOCAL_ETH_INERFACE, sizeof(LOCAL_ETH_INERFACE)))
            {
                strncpy(ip, inet_ntoa(((struct sockaddr_in*)&(pIfreq->ifr_addr))->sin_addr), IP_CHAR_MAX_LEN);
            }

            printf("-------------\n");
            printf("name = [%s]\n", pIfreq->ifr_name);
            printf("addr = [%s]\n", inet_ntoa(((struct sockaddr_in*)&(pIfreq->ifr_addr))->sin_addr));
            pIfreq++;
        }
    }
    printf("*****************************************\n");

    return 0;
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

    if(0 != GetLocalIp(ip))
    {
        printf("Error:[%s %d %s()] Get local ip failed!", __FILE__, __LINE__, __func__);
    }

    WebClient::SocketClient socketClient(ip, LOCAL_PORT_NUM, 5);

    socketClient.Start();

    return 0;

}