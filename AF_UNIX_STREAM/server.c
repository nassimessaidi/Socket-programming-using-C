#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
    int serverSockfd, clientSockfd;
    int serverLen, clientLen;
    struct sockaddr_un serverAddr;
    struct sockaddr_un clientAddr;

    //remove any old socket and create an unamed socket for the server
    unlink("server_socket");
    serverSockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    //name the socket
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, "server_socket");
    serverLen = sizeof(serverAddr);
    bind(serverSockfd, (struct sockaddr *)&serverAddr, serverLen);

    //create a connection queue and wait for clients
    listen(serverSockfd, 5);

    while (1)
    {
        char msg;
        printf("server waiting\n");

        //accept connection
        clientLen = sizeof(clientAddr);
        clientSockfd = accept(serverSockfd, (struct sockaddr *)&clientAddr, &clientLen);

        //we can now read/write to client on clientSockfd

        read(clientSockfd, &msg, 1);
        msg++;
        write(clientSockfd, &msg, 1);
        }
    close(clientSockfd);
}
