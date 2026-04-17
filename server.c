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
#include <sys/wait.h>

// waiting connections
#define BACKLOG 10

// get IPv4 or IPv6 address
void *get_in_addr(struct sockaddr *sa)
{
    if(sa->sa_family == AF_INET)
    {
	    return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
    int status, sockfd, newfd;
    struct addrinfo hints;
    struct addrinfo *serverinfo, *p;
    struct sockaddr_storage their_addr;
    socklen_t sin_size;
    char s [INET6_ADDRSTRLEN];
    int yes = 1;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // ask kernel for addresses
    if((status = getaddrinfo(NULL, "3490", &hints, &serverinfo)) != 0)
    {
        fprintf(stderr, "gai error: %s\n", gai_strerror(status));
	    exit(1);
    }

    for(p = serverinfo; p != NULL; p = p->ai_next)
    {
        // create socket
        if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
	    {
	        perror("server: socket");
	        continue;
	    }
        if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) 
        {
            perror("server: socket");
            exit(1);
        }
        // bind socket to the port
        if(bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
        {
            close(sockfd);
	        perror("server: bind");
	        continue;
        }
	
	    break;
    }
     
    freeaddrinfo(serverinfo);

    if(p == NULL)
    {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }

    if(listen(sockfd, BACKLOG) == -1)
    {
	    perror("listen");
	    exit(1);
    }

    printf("waiting for connection...\n");

    while(1)
    {
	    sin_size = sizeof their_addr;
        newfd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
	
        if(newfd == -1)
        {
            perror("accept");
            continue;
        }

        // converts an IPv4 or IPv6 Internet network address into a string in the standard text format
        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
        printf("server: connection from %s\n", s);

        send(newfd, "Hello from my first server in C!\n", 34, 0);
    	close(newfd);
    } 

    return (0);
}
