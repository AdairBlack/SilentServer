# SilentServer

Silent Dust is silent.

------------------------
#### Getting Started

+ Linux

The project contains a Server and a Client. The Server is a daemon that runs in the background and listens for incoming connections. The Client is a command line tool that connects to the Server and sends commands to it.

##### compile #####
```sh
meson setup builddir
meson compile -C builddir
```

##### execute #####
```sh
./builddir/server
./builddir/client
```