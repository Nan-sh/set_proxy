#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define PROXY_FILE		"/etc/profile"

int main()
{
	int fd;
	char *msg_old = "#设置http和https全局代理\nexport http_proxy='http://localhost:8118'\nexport https_proxy='http://localhost:8118'\n";
	char *msg_new = "#设置http和https全局代理\nexport http_proxy='' #0000000000000000000\nexport https_proxy='' #0000000000000000000\n";
	char buf[256];
		
	fd = open(PROXY_FILE, O_RDWR);
	
	lseek(fd, -(strlen(msg_old)), SEEK_END);
	read(fd, buf, strlen(msg_old));
	if(strcmp(buf, msg_old) == 0)
	{
		lseek(fd, -(strlen(msg_old)), SEEK_END);
		write(fd, msg_new, strlen(msg_new));	
		printf("已关闭代理\n");
	}
	else
	{
		memset(buf, 0, 256);
		lseek(fd, -(strlen(msg_new)), SEEK_END);
		read(fd, buf, strlen(msg_new));
		if(strcmp(buf, msg_new) == 0)
		{
			lseek(fd, -(strlen(msg_new)), SEEK_END);
			write(fd, msg_old, strlen(msg_old));	
			printf("已打开代理\n");
		}
		else
		{
			lseek(fd, 0, SEEK_END);
			write(fd, msg_old, strlen(msg_old));
			printf("已打开代理\n");	
		}	
	}	
	
	close(fd);
}
