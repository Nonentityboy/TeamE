//2-���ܵ������� 
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
//Ҳ����ֱ��echo ������cat������ִ����ͻ��˳��ˣ��ر��ˣ� 
//����һ���˳�������ϵͳ���Զ��������Զ�û�� 
void writefile()
{
	int fd = open("/home/ma/fssh/fifo1",O_WRONLY);
	if(fd < 0)
	printf("open file error,%s\n",strerror(errno));
	char buf[100] = { 0 };
	scanf("%s",buf);
	write(fd,buf,sizeof(buf));
	close(fd);	//�ر�������ܵ� 
	return;
}
int main()
{
	writefile();
	return 0;
}
