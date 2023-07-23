project('SilentServer', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3','cpp_std=c++20'])

Server = executable('server', 
                 'Server/src/main.cpp',
                 'Server/src/SocketServer.cpp',
                 'Server/src/SocketWrapper.cpp',
                 'Server/src/Utils.cpp',
                 include_directories : ['Server/include'],
                 install : false)

Client = executable('client', 
                 'Client/src/main.cpp',
                 'Client/src/SocketClient.cpp',
                 include_directories : ['Client/include'],
                 install : false)
