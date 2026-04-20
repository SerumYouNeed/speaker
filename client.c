#define _POSIX_C_SOURCE 200112L // for POSIX functions, eg. getaddrinfo

#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

// get IPv4 or IPv6 address
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int main(void)
{
    int status, sockfd, numbytes;
    char buf[101];
    struct addrinfo hints, *serverinfo, *p;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo("localhost", "3490", &hints, &serverinfo)) != 0)
    {
        fprintf(stderr, "gai error: %s\n", gai_strerror(status));
        exit(1);
    }
// write fork
    for (p = serverinfo; p != NULL; p = p->ai_next)
    {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
        {
            perror("client: socket");
            continue;
        }

        // converts an IPv4 or IPv6 Internet network address into a string in the standard text format
        inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
        printf("client: connecting to %s\n", s);

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            perror("client: connect");
            close(sockfd);
            continue;
        }
        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "client: failed to connect\n");
        return (2);
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
    printf("client: connected to %s\n", s);

    freeaddrinfo(serverinfo);

    if ((numbytes = recv(sockfd, buf, sizeof buf, 0)) == -1)
    {
        perror("recv");
        close(sockfd);
        exit(1);
    }

    if (numbytes == 0)
    {
        printf("client: connection closed\n");
        close(sockfd);
        return (0);
    }

    buf[numbytes] = '\0';

    printf("client: received '%s'\n", buf);

    
    close(sockfd);

    return (0);
}