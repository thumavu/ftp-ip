#include "../../includes/server.h"

int main(int argc, char **argv)
{
    int                 listed_fd;
    int                 conn_fd;
    struct  sockaddr_in srv_addr;
    struct  sockaddr_in cli_addr;
    socklen_t           cli_len;
    pid_t               child_pid;
    char                file_name[MAX_RECV_BUF];
    char                print_addr[INET_ADDRSTRLEN];

    memset(&srv_addr, 0, sizeof(srv_addr));
    memset(&cli_addr, 0, sizeof(cli_addr));
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    srv_addr.sin_port = (argc > 1) ? htons(atoi(argv[1])) : htons(SRV_PORT);
    if ((listed_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("socket failure");
        exit(EXIT_FAILURE);
    }
    if (bind(listed_fd, (struct sockaddr*) &srv_addr, sizeof(srv_addr)) < 0)
    {
        printf("bind error");
        exit(EXIT_FAILURE);
    }
    printf("Listening on port number %d ... \n", ntohs(srv_addr.sin_port));
    if (listen(listed_fd, LISTEN_ENQ) < 0)
    {
        printf("listen error");
        exit(EXIT_FAILURE);
    }
    signal(SIGCHLD, sig_chld);
    while(1)
    {
        cli_len = sizeof(cli_addr);
        printf("Waiting for a client to connect...\n\n");
        if ((conn_fd = accept(listed_fd, (struct sockaddr*) &cli_addr, &cli_len)) < 0)
        {
            printf("accept error");
            break;
        }
        inet_ntop(AF_INET, &(cli_addr.sin_addr), print_addr, INET_ADDRSTRLEN);
        printf("Client connected from %s:%d\n", print_addr, ntohs(cli_addr.sin_port));
        if ((child_pid = fork()) == 0) /*fork return 0 for child*/
        {
            close(listed_fd); //
            get_file_name(conn_fd, file_name);
            send_file(conn_fd, file_name);
            printf("Closing connect\n");
            close(conn_fd);
            exit(0);
        }
        close(conn_fd);
    }
    close(listed_fd);
    return (0);
}