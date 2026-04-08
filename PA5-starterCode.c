#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 8192

void handle_client(int client_fd);

int main(int argc, char *argv[])
{
    int listen_fd, port;
    struct sockaddr_in server_addr;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    port = atoi(argv[1]);

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        perror("socket");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(listen_fd, 10);

    printf("Proxy listening on port %d\n", port);

    while (1) {
        int client_fd = accept(listen_fd, NULL, NULL);
        handle_client(client_fd);
        close(client_fd);
    }
}

void handle_client(int client_fd)
{
    char buffer[MAXLINE];
    char method[16], uri[256], version[16];
    char hostname[256], path[256];
    int server_fd;
    struct hostent *server;

    /* TODO: Read request from client */

    /* TODO: Parse HTTP request line */

    /* TODO: Extract hostname and path from URI */

    /* TODO: Connect to remote server */

    /* TODO: Forward request to server */

    /* TODO: Relay response back to client */

    /* TODO: Close server socket */
}