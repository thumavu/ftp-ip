#ifndef SERVER_H
# define SERVER_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <netinet/in.h>

# define SRV_PORT 5103
# define LISTEN_ENQ 5
# define MAX_RECV_BUF 256
# define MAX_SEND_BUF 256

void    get_file_name(int sock, char *file_name);
int     send_file(int sock, char *file_name);
void    sig_chld();

#endif