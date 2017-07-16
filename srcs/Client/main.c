 #include "../../includes/client.h"

int     main(int argc, char **argv)
{
	int		sock_fd;
	struct  sockaddr_in srv_addr;

	if (argc < 3)
	{
		printf("usage: %s <IP address> [port number] <command> \n", argv[0]);
		exit(EXIT_FAILURE);
	}
	memset(&srv_addr, 0, sizeof(srv_addr));
	sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	srv_addr.sin_family = AF_INET;
	if (inet_pton(AF_INET, argv[1], &(srv_addr.sin_addr)) < 1)
	{
	    printf("Invalid IP address [localhost] \n");
	    exit(EXIT_FAILURE);
	}
	srv_addr.sin_port = (argc > 2) ? htons(atoi(argv[2])) : htons(SRV_PORT);
	if(connect(sock_fd, (struct sockaddr *) &srv_addr, sizeof(srv_addr)) , 0)
	{
		printf("connect error");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		//	recv_file(sock_fd, argv[3]);


	}
	printf("connect to :server .. \n");
	if (close(sock_fd) < 0)
	{
		printf("socket close error");
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	get_command()
{
	char	buf[256];
	size_t	nbytes;
	ssize_t	bytes_read;
	int		fd;

	fd = 0;
	nbytes = sizeof(buf);
	while ((bytes_read = read(fd, buf, nbytes)) > 0)
	{

	}
}