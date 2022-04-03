#ifndef SERVICE_HPP
#define SERVICE_HPP
#include "utilities.hpp"
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <cstring>
#if defined(_linux)
#include <sys/epoll.h>
#endif

#define SERVER_IP "114.132.220.211"
#define PORT 6666
#define MAXSIZE 10000
extern int sfd;
typedef struct clientData
{
	pid_t pid;
	int sfd;
	short busy;
} data_t, *p_data;

typedef struct train
{
	int len;
	char buf[MAXSIZE];
} train_t, *p_train;

int send_n(int new_fd, char *buf, int len);
int recv_n(int new_fd, char *buf, int len);
int recvFile(int new_fd);
// download from teacher server
int sendFile(const char *buf);
// upload to teacher server
int displayProgress(int progress, int last_char_count);
// show the Progress
void initService(bool &is_online);

#endif /* SERVICE_HPP */