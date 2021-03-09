#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <stdlib.h>

int main()
{
    int sockfd;
    int len;
    struct sockaddr_un address;
    int result;
    char msg = 'A';

    //create a socket for the client
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

    //name the socket as agree with server
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
    len = sizeof(address);
   
        //now connect our socket to the server's socket

        result = connect(sockfd, (struct sockaddr *)&address, len);

        if (result == -1)
        {
            perror("oops : client1");
            exit(1);
        }

        //we can now read/write via sockfd

        write(sockfd, &msg, 1);
        read(sockfd, &msg, 1);
        printf("msg from server = %c\n", msg);
       
    close(sockfd);
}
