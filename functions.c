#include "header.h"

//takes in client file descriptor

void handle_client(int client_fd)
{
    char buffer[MAXLINE];
    char method[16], uri[256], version[16];
    char hostname[256], path[256];
    int server_fd, n;
    struct hostent *server;
    struct sockaddr_in server_addr;


    
    read(client_fd, buffer, MAXLINE - 1); //read client request into buffer
    sscanf(buffer, "%s %s %s", method, uri, version); //parses method, uri and version with spaces

    strcpy(path, "/"); //default path  
    sscanf(uri, "http://%[^/]/%s", hostname, path); //read chars until / for hostname, remainder after / for path


    server = gethostbyname(hostname); //get server info by hostname
    if (server == NULL){
        printf("Invalid host");
        return;
    }

    //connect remote to server
    server_fd = socket(AF_INET, SOCK_STREAM, 0); //create socket for server connection
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80); 

    memcpy(&server_addr.sin_addr.s_addr, server->h_addr_list[0], server->h_length); //copy server IP address to server_addr
    
    if(connect(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) { //connect to server
        perror("connect");
        close(server_fd);
        return;
    }

    //forward properly formatted request -> server 
    char request[MAXLINE];
    snprintf(request, sizeof(request), 
        "GET /%s HTTP/1.0\r\n"
        "Host: %s\r\n"
        "Connection: close\r\n"
        "\r\n"
        ,path, hostname);
    write(server_fd, request, strlen(request));

    //send server response to client
    while((n = read(server_fd, buffer, MAXLINE)) >0){
        write(client_fd, buffer, n);
    }

    //close server connection
    close(server_fd);
}