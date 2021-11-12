#include "server.h"

void AvoidBindError(int *server_socket)
{
	int on = 1;
	setsockopt(*server_socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
}
void InitServerSocket(int *server_socket, struct sockaddr_in *server_addr)
{
	server_addr->sin_family = AF_INET;
	server_addr->sin_port = htons(9999);
	server_addr->sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(*server_socket, (struct sockaddr *)(server_addr),
		 sizeof(*server_addr)))
	{
		printf("bind() error!\n");
		exit(-1);
	}

	if (listen(*server_socket, OPEN_MAX))
	{
		printf("listen() error!\n");
		exit(-1);
	}
}
int recv_n(int new_fd, char *buf, int len)
{
	int ret;
	int total = 0;
	while (total < len)
	{
		ret = recv(new_fd, buf + total, len - total, 0);
		if (ret >= 0)
		{
			total = total + ret;
		}
		else
		{
			return -1;
		}
	}
	return 0;
}

int recv_file(int new_fd, char *path)
{
	DIR *dir;
	dir = opendir(path);
	if (NULL == dir)
	{
		return -1;
	}
	int dfd = dirfd(dir);
	int fd;
	int ret;
	train t;
	memset(&t, 0, sizeof(t));
	int len;
	char buf[10000] = {0};
	int flag = 0;
	int fileErrorFlag = 0;
	struct stat statbuf;
	long recvsize = 0;
	recv(new_fd, &fileErrorFlag, sizeof(int), 0);
	if (1 == fileErrorFlag)
	{
		return -1;
	}
	recv(new_fd, &len, sizeof(int), 0);
	memset(buf, 0, sizeof(buf));
	int res;
	if ((res = recv(new_fd, buf, len, 0)) <= 0)
	{

		return res;
	}
	char filename[128];
	sprintf(filename, "./repo/%s", buf + 8);
	fd = open(filename, O_RDWR);
	printf("buf = %s\n", filename);
	if (-1 == fd)
	{
		fd = openat(dfd, filename, O_RDWR | O_CREAT, 0666);
		if (fd == -1)
		{
			perror("open error");
			return -1;
		}
	}
	else
	{
		flag = 1;
		stat(filename, &statbuf);
		recvsize = statbuf.st_size;
	}

	send(new_fd, &flag, sizeof(int), 0);
	if (1 == flag)
	{
		send(new_fd, &recvsize, sizeof(long), 0);
	}
	lseek(fd, (int)recvsize, SEEK_SET);

	while (1)
	{
		recv(new_fd, &len, sizeof(int), 0);
		if (len == 0)
			break;
		recv_n(new_fd, buf, len);
		write(fd, buf, len);
	}
	close(fd);
	return 0;
}
