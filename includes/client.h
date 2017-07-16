#ifndef CLIENT_H
# define CLIENT_H

# include <stdio.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# define SRV_PORT 5103
# define MAX_RECV_BUF 256
# define MAX_SEND_BUF 256

int     recv_file(int sock, char *file_name);
#endif