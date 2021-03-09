#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Missing port number!!\nExiting from program .....\n");
        exit(1);
    }
    int sockfd, newsockfd, portno, n;
    char buffer[2048];

    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientLen; //32 bits data type ; internet address

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("Error in creating socket\n");
    }
    bzero((char *)&serverAddr, sizeof(serverAddr));
    portno = atoi(argv[1]); //all to int string to int

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(portno); //host to network short

    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        error("Binding Error !!\n");
    }

    listen(sockfd, 5); ///max client can connect to server at the time
    clientLen = sizeof(clientAddr);

    newsockfd = accept(sockfd, (struct sockaddr *)&clientAddr, &clientLen);

    if (newsockfd < 0)
        error("Error on accept!!\n");

    while ((1))
    {
        bzero(buffer, 2048);
        n = read(newsockfd, buffer, 2048);
        if (n < 0)
            error("Error on read");
        printf("Client : %s", buffer);
        bzero(buffer, 2048);
        fgets(buffer, 2048, stdin);

        n = write(newsockfd, buffer, strlen(buffer));
        if (n < 0)
            error("Error on write!!\n");
        int i = strncmp("Bye", buffer, 3);
        if (i == 0)
            break;
    }
    close(newsockfd);
    close(sockfd);
    return 0;
}
