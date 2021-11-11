#include "server.h"

int main(int argc, char const *argv[])
{
	int server_socket = socket(PF_INET, SOCK_STREAM, 0);
	if (server_socket == -1)
	{
		perror("socket() error!\n");
		exit(-1);
	}
	struct sockaddr_in server_addr, client_addr;
	InitServerSocket(&server_socket, &server_addr);
	AvoidBindError(&server_socket);
	// avoid Bind error

	////////////////////////////////////////////////////////////////////

	int num = 0;
	char str[INET_ADDRSTRLEN];
	ssize_t efd = epoll_create(OPEN_MAX);
	struct epoll_event tep, ep[OPEN_MAX];
	if (efd == -1)
	{
		perror("epoll_create error\n");
		exit(1);
	}
	tep.events = EPOLLIN;
	tep.data.fd = server_socket;
	ssize_t res = epoll_ctl(efd, EPOLL_CTL_ADD, server_socket, &tep);
	if (res == -1)
	{
		perror("epoll_ctl error\n");
		exit(1);
	}
	char message[MAX_MSG];
	ssize_t nready;
	printf("Accepting client connect\n");
	while (1)
	{
		nready = epoll_wait(efd, ep, OPEN_MAX, -1);
		if (nready < 0)
		{
			perror("select error\n");
			exit(1);
		}
		for (int i = 0; i < nready; i++)
		{
			if (!(ep[i].events & EPOLLIN))
			{
				continue;
			}

			if (ep[i].data.fd == server_socket)
			{
				socklen_t clt_addr_len = sizeof(client_addr);
				int connfd = accept(server_socket, (struct sockaddr *)(&client_addr), &clt_addr_len);
				printf("received from %s at PORT %d\n",
				       inet_ntop(AF_INET, &client_addr.sin_addr, str, sizeof(str)),
				       ntohs(client_addr.sin_port));
				printf("cfd %d---client %d\n", connfd, ++num);

				tep.events = EPOLLIN;
				tep.data.fd = connfd;
				res = epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &tep);
				if (res == -1)
				{
					perror("epoll_ctl error\n");
					exit(1);
				}
			}
			else
			{
				bzero(message, sizeof(message));
				int sockfd = ep[i].data.fd;
				int n = recv_file(sockfd, "./");

				if (n == 0)
				{
					res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);
					if (res == -1)
					{
						perror("epoll_ctl error\n");
						exit(1);
					}
					close(sockfd);
					printf("client[%d] closed connection\n", sockfd);
				}
				else if (n < 0)
				{
					res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);
					if (res == -1)
					{
						perror("epoll_ctl error\n");
						exit(1);
					}
					if (errno == ECONNRESET)
					{
						printf("client[%d] aborted connection\n", i);
						close(sockfd);
					}
				}
			}
		}
	}
	close(server_socket);
	return 0;
}
