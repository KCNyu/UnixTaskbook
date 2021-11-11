#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <winsock.h>
//#include <winsock2.h>
#include <sys/select.h>
#include <sys/epoll.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <syslog.h>
#include <shadow.h>
#include <time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <dirent.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <ctype.h>

#define MAX_MSG 10000
#define OPEN_MAX 128
void AvoidBindError(int *server_socket);
void InitServerSocket(int *server_socket, struct sockaddr_in *server_addr);
int recv_file(int new_fd, char *path);
typedef struct{
	int len;
	char buf[1000];
}train,*ptrain;