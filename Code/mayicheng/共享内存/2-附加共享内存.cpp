//2-���ӹ����ڴ��� (���������ͷ�)
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
//void *shmat(int shmid,const void *shmaddr,int shmflg);
//int shmdt(const void *shmaddr);
int main(int argc,char *argv[])
{
	char *buf = NULL;
	int shmid = 0;
	if(argc > 1)	//������㹲���ڴ��Ǹ� 
	{
		shmid  = atoi(argv[1]);
		buf = (char *)shmat(shmid,0,0);
		sleep(60);
		shmdt(buf);
	}
	return 0;
} 
