#include "header.h"

//takes in client file descriptor 

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