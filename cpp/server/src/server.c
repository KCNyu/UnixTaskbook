#include "server.h"

int g_efd;								   //全局变量, 保存epoll_create返回的文件描述符
struct myevent_s g_events[MAX_EVENTS + 1]; //自定义结构体类型数组. +1-->listen fd

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

void eventset(struct myevent_s *ev, int fd, void (*call_back)(int, int, void *), void *arg)
{
	ev->fd = fd;
	ev->call_back = call_back;
	ev->events = 0;
	ev->arg = arg;
	ev->status = 0;
	// memset(ev->buf, 0, sizeof(ev->buf));
	// ev->len = 0;
	ev->last_active = time(NULL); //调用eventset函数的时间

	return;
}

/* 向 epoll监听的红黑树 添加一个 文件描述符 */

void eventadd(int efd, int events, struct myevent_s *ev)
{
	struct epoll_event epv = {0, {0}};
	int op;
	epv.data.ptr = ev;
	epv.events = ev->events = events; // EPOLLIN 或 EPOLLOUT

	if (ev->status == 1)
	{						//已经在红黑树 g_efd 里
		op = EPOLL_CTL_MOD; //修改其属性
	}
	else
	{						//不在红黑树里
		op = EPOLL_CTL_ADD; //将其加入红黑树 g_efd, 并将status置1
		ev->status = 1;
	}

	if (epoll_ctl(efd, op, ev->fd, &epv) < 0) //实际添加/修改
		printf("event add failed [fd=%d], events[%d]\n", ev->fd, events);
	else
		printf("event add OK [fd=%d], op=%d, events[%0X]\n", ev->fd, op, events);

	return;
}
void eventdel(int efd, struct myevent_s *ev)
{
	struct epoll_event epv = {0, {0}};

	if (ev->status != 1) //不在红黑树上
		return;

	epv.data.ptr = ev;
	ev->status = 0;								 //修改状态
	epoll_ctl(efd, EPOLL_CTL_DEL, ev->fd, &epv); //从红黑树 efd 上将 ev->fd 摘除

	return;
}
void rek_mkdir(char *path)
{
	char *sep = strrchr(path, '/');
	if (sep != NULL)
	{
		*sep = 0;
		rek_mkdir(path);
		*sep = '/';
	}
	if (mkdir(path, 0777) && errno != EEXIST)
		printf("error while trying to create '%s'\n%m\n", path);
}

int fopen_mkdir(char *path)
{
	char *sep = strrchr(path, '/');
	if (sep)
	{
		char *path0 = strdup(path);
		path0[sep - path] = 0;
		rek_mkdir(path0);
		free(path0);
	}
	return open(path, 0666);
}
void recvFile(int new_fd, int events, void *arg)
{
	struct myevent_s *ev = (struct myevent_s *)arg;
	DIR *dir;
	dir = opendir("./");
	if (NULL == dir)
	{
		return;
	}
	int dfd = dirfd(dir);
	int fd;
	int ret;
	train t;
	memset(&t, 0, sizeof(t));
	int len;
	int flag = 0;
	int fileErrorFlag = 0;
	struct stat statbuf;
	long recvsize = 0;
	recv(new_fd, &fileErrorFlag, sizeof(int), 0);
	if (1 == fileErrorFlag)
	{
		return;
	}
	recv(new_fd, &len, sizeof(int), 0);
	memset(ev->buf, 0, sizeof(ev->buf));
	int res;
	if ((res = recv(new_fd, ev->buf, len, 0)) <= 0)
	{

		return;
	}
	char filename[128];
	sprintf(filename, "./repo/%s", ev->buf);
	fd = fopen_mkdir(filename);
	printf("buf = %s\n", filename);
	if (-1 == fd)
	{
		fd = openat(dfd, filename, O_RDWR | O_CREAT, 0666);
		if (fd == -1)
		{
			perror("open error");
			return;
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
		recv_n(new_fd, ev->buf, len);
		write(fd, ev->buf, len);
	}
	eventdel(g_efd, ev);
	close(new_fd);
	close(fd);
	return;
}
/*  当有文件描述符就绪, epoll返回, 调用该函数 与客户端建立链接 */

void acceptconn(int lfd, int events, void *arg)
{
	struct sockaddr_in cin;
	socklen_t len = sizeof(cin);
	int cfd, i;

	if ((cfd = accept(lfd, (struct sockaddr *)&cin, &len)) == -1)
	{
		if (errno != EAGAIN && errno != EINTR)
		{
			/* 暂时不做出错处理 */
		}
		printf("%s: accept, %s\n", __func__, strerror(errno));
		return;
	}

	do
	{
		for (i = 0; i < MAX_EVENTS; i++) //从全局数组g_events中找一个空闲元素
			if (g_events[i].status == 0) //类似于select中找值为-1的元素
				break;					 //跳出 for

		if (i == MAX_EVENTS)
		{
			printf("%s: max connect limit[%d]\n", __func__, MAX_EVENTS);
			break; //跳出do while(0) 不执行后续代码
		}
		/*
		int flag = 0;
		if ((flag = fcntl(cfd, F_SETFL, O_NONBLOCK)) < 0)
		{ //将cfd也设置为非阻塞
			printf("%s: fcntl nonblocking failed, %s\n", __func__, strerror(errno));
			break;
		}
		*/
		/* 给cfd设置一个 myevent_s 结构体, 回调函数 设置为 recvdata 即在创建一开始，服务器只接受来自客户端所写数据 */

		eventset(&g_events[i], cfd, recvFile, &g_events[i]);
		eventadd(g_efd, EPOLLIN, &g_events[i]); //将cfd添加到红黑树g_efd中,监听读事件

	} while (0);

	printf("new connect [%s:%d][time:%ld], pos[%d]\n",
		   inet_ntoa(cin.sin_addr), ntohs(cin.sin_port), g_events[i].last_active, i);
	return;
}
/* 从epoll 监听的 红黑树中删除一个 文件描述符*/

void initlistensocket(int efd, short port)
{
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	AvoidBindError(&lfd);
	fcntl(lfd, F_SETFL, O_NONBLOCK);
	//将socket设为非阻塞 故需忙轮询

	/* void eventset(struct myevent_s *ev, int fd, void (*call_back)(int, int, void *), void *arg);  */
	eventset(&g_events[MAX_EVENTS], lfd, acceptconn, &g_events[MAX_EVENTS]); // 初始化设置监听套接字对应事件结构体,回调函数为accept即接受客户端套接字

	/* void eventadd(int efd, int events, struct myevent_s *ev) */
	eventadd(efd, EPOLLIN, &g_events[MAX_EVENTS]); // 将监听套接字置于红黑树上,监听读事件

	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin)); // bzero(&sin, sizeof(sin))
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);

	bind(lfd, (struct sockaddr *)&sin, sizeof(sin));

	listen(lfd, 20);

	return;
}
void AvoidBindError(int *server_socket)
{
	int on = 1;
	setsockopt(*server_socket, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
}