#pragma once

namespace WebServer
{
    namespace Utils
    {
        class SocketWrapper
        {
        public:
            SocketWrapper(int socketFd_);
            ~SocketWrapper();

        private:
            int socketFd;
        };
    } // namespace Utils
} // namespace WebServer
