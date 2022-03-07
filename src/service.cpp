#include "service.hpp"
int sfd;
int send_n(int new_fd, char *buf, int len)
{
	int ret;
	int total = 0;
	while (total < len)
	{
		ret = send(new_fd, buf + total, len - total, 0);
		if (ret >= 0)
		{
			total += ret;
		}
		else
		{
			return -1;
		}
	}
	return 0;
}

int recv_n(int new_fd, char *buf, int len)
{
	int ret;
	int total = 0;
	while (total < len)
	{
		ret = recv(new_fd, buf + total, len, 0);
		if (ret >= 0)
		{
			total += ret;
		}
		else
		{
			return -1;
		}
	}
	return 0;
}

int recvFile(int new_fd)
{
	return 0;
}
int sendFile(const char *buf)
{
	int fd;
	int fileErrorFlag = 0;
	train_t t;
	char filename[128];
	memset(&t, 0, sizeof(t));
	memset(filename, 0, sizeof(filename));
	printf("buf = %s\n", buf);
	strcpy(filename, buf);
	printf("Upload files %s to the repository\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		fileErrorFlag = 1;
		perror("open file error");
		send(sfd, &fileErrorFlag, sizeof(int), 0);
		return -1;
	}
	else
	{
		send(sfd, &fileErrorFlag, sizeof(int), 0);
	}
	struct stat statbuf;
	int ret = fstat(fd, &statbuf);
	if (ret == -1)
	{
		perror("fstat error");
		return -1;
	}
	long sendsize = 0;
	long totalsize = statbuf.st_size;
	int percent;
	int char_count = 0;
	t.len = strlen(filename);
	strcpy(t.buf, filename);
	send(sfd, &t, 4 + t.len, 0);
	int fflag = 0;
	long len = 0;
	recv(sfd, &fflag, sizeof(int), 0);
	if (fflag == 1)
	{
		recv(sfd, &len, sizeof(long), 0);
	}
	lseek(fd, (off_t)len, SEEK_SET);
	sendsize += len;

	while (memset(&t, 0, sizeof(t)), (t.len = read(fd, t.buf, sizeof(t.buf))) > 0)
	{
		sendsize += (long)t.len;
		percent = 100 * (1.0 * sendsize / totalsize);
		char_count = displayProgress(percent, char_count);
		if (send_n(sfd, (char *)&t, 4 + t.len))
		{
			printf("send_n error\n");
			return -1;
		}
	}

	int flag = 0;
	send(sfd, &flag, sizeof(flag), 0);
	close(fd);
	return 0;
}
int displayProgress(int progress, int last_char_count)
{
	int i = 0;

	for (i = 0; i < last_char_count; i++)
	{
		printf("\b");
	}

	for (i = 0; i < progress; i++)
	{
		printf("=");
	}
	printf(">>");
	for (i += 2; i < 104; i++)
	{
		printf(" ");
	}
	i = i + printf("[%d%%]", progress);
	fflush(stdout);

	return i;
}
void initService()
{
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr);

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1)
	{
		printf("socket error\n");
	}

	if (connect(sfd, (struct sockaddr *)(&serv_addr), sizeof(serv_addr)))
	{
		perror("connect error\n");
		exit(-1);
	}
}