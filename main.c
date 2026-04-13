#include "header.h"

int main(int argc, char *argv[])
{
    printf("Testing my debug setup...");
    int listen_fd, port;
    struct sockaddr_in server_addr;

    if (argc != 2) { //insufficient cmd args 
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    //arg 1 is the port  
    port = atoi(argv[1]);

    listen_fd = socket(AF_INET, SOCK_STREAM, 0); //create socket type, protocol chosen automatically
    if (listen_fd < 0) { //-1 means failed
        perror("socket");
        exit(1);
    }


    memset(&server_addr, 0, sizeof(server_addr)); //set all butes of server_addr to 0 
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port); //convert port number to match network  

    bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)); //bind local address to remote socket
    listen(listen_fd, 10); //allows 10 requests 

    printf("Proxy listening on port %d\n", port);

    while (1) {
        int client_fd = accept(listen_fd, NULL, NULL);
        handle_client(client_fd); //handle request
        close(client_fd);
    }
}