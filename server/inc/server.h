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
#define PORT 9999
#define MAX_EVENTS 1024 //监听上限数
#define BUFLEN 4096
#define SERV_PORT 6666

struct myevent_s
{
    int fd;                                           //要监听的文件描述符
    int events;                                       //对应的监听事件
    void *arg;                                        //泛型参数 可传递myevent_s结构体指针
    void (*call_back)(int fd, int events, void *arg); //回调函数
    int status;                                       //是否在监听:1->在红黑树上(监听), 0->不在(不监听)
    char buf[BUFLEN];
    int len;
    long last_active; //记录每次加入红黑树 g_efd 的时间值
};
int g_efd;                                 //全局变量, 保存epoll_create返回的文件描述符
struct myevent_s g_events[MAX_EVENTS + 1]; //自定义结构体类型数组. +1-->listen fd
void eventset(struct myevent_s *ev, int fd, void (*call_back)(int, int, void *), void *arg);
void eventadd(int efd, int events, struct myevent_s *ev);
void eventdel(int efd, struct myevent_s *ev);
void acceptconn(int lfd, int events, void *arg);
void initlistensocket(int efd, short port);
void AvoidBindError(int *server_socket);

////////////////////////////////////////////

int recv_n(int new_fd, char *buf, int len);
void recvFile(int new_fd, int events, void *arg);
typedef struct
{
    int len;
    char buf[1000];
} train, *ptrain;