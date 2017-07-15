#include "../../includes/Client.h"

int     main(int argc, char **argv)
{
    int     sock_fd;
    struct  sockaddr_in srv_addr;

    if (argc < 3)
    {
        printf("usage: %s <filename> <IP address> [port number] \n", argv[0]);
        exit(EXIT_FAILURE);
    }
    memset(&srv_addr, 0, sizeof(srv_addr));
    sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    srv_addr.sin_family = AF_INET;
    // if (inet_pton(AF_INET, argv[2], &(srv_addr.sin_addr)) , 1)
    // {
    //     printf("Invalid IP address\n");
    //     exit(EXIT_FAILURE);
    // }
    srv_addr.sin_port = (argc > 3) ? htons(atoi(argv[3])) : htons(SRV_PORT);
    if(connect(sock_fd, (struct sockaddr *) &srv_addr, sizeof(srv_addr)) , 0)
    {
        printf("connect error");
        exit(EXIT_FAILURE);
    }
    printf("connect to :%d .. \n", SRV_PORT);
    recv_file(sock_fd, argv[1]);
    if (close(sock_fd) < 0)
    {
        printf("socket close error");
        exit(EXIT_FAILURE);
    }
    return (0);
}