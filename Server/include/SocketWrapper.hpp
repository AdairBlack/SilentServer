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

            int bind();

        private:
            char *ip;
            int port;
            int backlog;
            int socketFd;
        };
    } // namespace Utils
} // namespace WebServer
