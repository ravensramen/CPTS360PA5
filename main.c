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