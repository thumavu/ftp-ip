#include "../../includes/server.h"

void    get_file_name(int sock, char *file_name)
{
	char        recv_str[MAX_RECV_BUF];
	ssize_t     rcvd_bytes;

	if ((rcvd_bytes = recv(sock, recv_str, MAX_RECV_BUF, 0)) < 0)
	{
		printf("RECEIVED ERROR");
		return ;
	}
	//sscanf(recv_str, "%s\n", file_name);
}

int     send_file(int sock, char *file_name)
{
	int     sent_count;
	ssize_t read_bytes;
	ssize_t sent_bytes;
	ssize_t sent_file_size;
	char    send_buf[MAX_SEND_BUF];
	char    *errmsg_notfound;
	int     f;

	sent_count = 0;
	sent_file_size = 0;
	errmsg_notfound= "File not found\n";
	if ((f = open(file_name, O_WRONLY)) < 0) // open the file so its read
	{
		printf("requested file: %s",file_name);
		if ((sent_bytes = send(sock, errmsg_notfound, strlen(errmsg_notfound), 0)) < 0)
		{
			printf("send error");
			return (-1);
		}
	}
	else
	{
		printf("Sending file: %s\n", file_name);
		while((read_bytes = read(f, send_buf, MAX_RECV_BUF)) > 0)
		{
			if ((sent_bytes = send(sock, send_buf, read_bytes, 0)) < read_bytes)
			{
				printf("send error");
				return (-1);
			}
			sent_count++;
			sent_file_size += sent_bytes;
		}
		close(f);
	}
	printf("Done with this client. Send %zd bytes in %d send(s)\n\n", sent_file_size, sent_count);
	return sent_count; 
}

void    sig_chld()
{
	pid_t   pid;
	int     stat;

	while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated\n", pid);
}