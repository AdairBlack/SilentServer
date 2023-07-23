#include "Utils.hpp"

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

int GetLocalIp(char ip[IP_CHAR_MAX_LEN])
{
    printf("Get local eth intfs...\n");
    if (nullptr == ip)
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

    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        return -1;
    }

    ioctl(sockfd, SIOCGIFCONF, &ifconf);

    pIfreq = (struct ifreq *)ifconf.ifc_buf;

    for (int i = (ifconf.ifc_len / sizeof(struct ifreq)); i > 0; i--)
    {
        if (AF_INET == pIfreq->ifr_flags)
        {
            if (!strncmp(pIfreq->ifr_name, LOCAL_ETH_INERFACE, sizeof(LOCAL_ETH_INERFACE)))
            {
                strncpy(ip, inet_ntoa(((struct sockaddr_in *)&(pIfreq->ifr_addr))->sin_addr), IP_CHAR_MAX_LEN);
            }

            printf("-------------\n");
            printf("name = [%s]\n", pIfreq->ifr_name);
            printf("addr = [%s]\n", inet_ntoa(((struct sockaddr_in *)&(pIfreq->ifr_addr))->sin_addr));
            pIfreq++;
        }
    }
    printf("*****************************************\n");

    return 0;
}