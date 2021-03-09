#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serverAddr;
    struct hostent *server;

    char buffer[2048];
    if (argc < 3)
    {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("Error creating socket!!");

    server = gethostbyname(argv[1]);
    if (server == NULL)
        fprintf(stderr, "Error no such host !!\n");

    bzero((char *)&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    //bcopy((char *)server->h_addr, (char *)&serverAddr.sin_addr.s_addr, server->h_lenght);
    serverAddr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
        error("Connection failer");

    while (1)
    {
        bzero(buffer, 2048);
        fgets(buffer, 2048, stdin);
        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0)
            error("Error in write!!\n");

        bzero(buffer, 2048);
        n = read(sockfd, buffer, 2048);
        if (n < 0)
            error("Error in write!!\n");
        printf("Server : %s", buffer);

        int i = strncmp("Bye", buffer, 3);
        if (i == 0)
            break;
    }
    close(sockfd);
    return 0;
}