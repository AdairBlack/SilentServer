#pragma once

namespace WebServer
{
    namespace Utils
    {
        class SocketWrapper
        {
        public:
            explicit SocketWrapper(char *ip_, int port_, int backlog_);
            ~SocketWrapper();

            int socketBind();

        private:
            char *ip;
            int port;
            int backlog;

            int socketFd;
            struct sockaddr_in ipv4Address;
        };
    } // namespace Utils
} // namespace WebServer
