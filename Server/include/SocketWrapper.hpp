#pragma once

namespace WebServer
{
    namespace Utils
    {
        class SocketWrapper
        {
        public:
            SocketWrapper(char *ip_, int port_, int backlog_);
            ~SocketWrapper();

        private:
            char *ip;
            int port;
            int backlog;
            int socketFd;
        };
    } // namespace Utils
} // namespace WebServer
