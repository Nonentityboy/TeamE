//�ػ��͹ܵ�ͨ��-1
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

void readfile()
{
	int fd = open("/home/ma/fssh/fifo1",O_RDONLY);
	if(fd < 0)
	printf("open file error,%s\n",strerror(errno));
	char buf[100] = { 0 };
	int len;
	while((len = read(fd,buf,sizeof(buf))) > 0)
	{
		printf("%s",buf);
		memset(buf,0,sizeof(buf));
	}
	close(fd);
	return;
}
void daem()
{
	int pid = fork();	//1.fork��һ���ӽ��� 
	if(pid > 0)
	exit(0);			//2.�������˳� 
	if(pid == 0)
	{
		setsid();		//3.�ӽ���������� 
		chdir("/");		//4.�ı乤��Ŀ¼
						//5.�����Բ�Ū�����umask���رղ���Ҫ���ļ������� 
	}
	return;
}
int main()
{
	daem();
	readfile();
	return 0;
}
 
