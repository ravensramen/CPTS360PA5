#include "header.h"
//main function to set up proxy, taken from starter code

int main(int argc, char *argv[])
{
    
    int listen_fd, port;
    struct sockaddr_in server_addr;

    if (argc != 2) { //insufficient cmd args 
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    //arg 1 is the port  
    port = atoi(argv[1]);

    listen_fd = socket(AF_INET, SOCK_STREAM, 0); //create socket type, protocol chosen automatically
    if (listen_fd < 0) { //
        perror("socket");
        exit(1); //end program, indicate failure
    }


    memset(&server_addr, 0, sizeof(server_addr)); //init bytes of server_addr to 0 
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port); //convert port number to match network  

    // bind socket to port and listen for connection 
    if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("bind"); 
    exit(1); //end program if bind failed
    }

    if (listen(listen_fd, 10) < 0) { //max of 10 requests  
        perror("listen");
        exit(1);
    }


    printf("Proxy listening on port %d\n", port);

    while (1) { //infinite loop to allow client conenctions 
        int client_fd = accept(listen_fd, NULL, NULL);
        handle_client(client_fd); //handle request
        close(client_fd);
    }
}