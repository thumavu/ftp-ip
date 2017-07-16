#include "../../includes/client.h"

int     recv_file(int sock, char *file_name)
{
    char    send_str[MAX_SEND_BUF];
    int     f;
    ssize_t send_bytes;
    ssize_t rcvd_bytes;
    ssize_t recv_file_size;
    int     recv_count;
    char    recv_str[MAX_RECV_BUF];
    size_t  send_strlen;

    send_strlen = strlen(send_str);
    if ((send_bytes = send(sock, file_name, send_strlen, 0)) < 0)
    {
        printf("send error\n");
        return (-1);
    }
    if ((f = open(file_name, O_WRONLY|O_CREAT , 0644)) < 0)
    {
        printf("error creating file\n");
        return (-1);
    }
    recv_count = 0;
    recv_file_size = 0;
    while((rcvd_bytes = recv(sock, recv_str, MAX_RECV_BUF, 0)) > 0)
    {
        recv_count = 0;
        recv_file_size = 0;
        if (write(f, recv_str, rcvd_bytes) < 0)
        {
            printf("error writing to file\n");
            return (-1);
        }
    }
    close(f);
    printf("Client Received: %zd bytes in %d recv(s)\n", recv_file_size, recv_count);
    return (recv_file_size);
}