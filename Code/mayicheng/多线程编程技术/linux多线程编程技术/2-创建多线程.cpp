#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "iostream"
//�����ʱ��Ҫ�� -lpthread 
//ldd�鿴
//nmȫ���� 
using namespace std;
void *func(void *t)			//���룬�˳� 
{
	printf("ptherad_create ok\n");
	return NULL;
}
int main()
{
	pthread_t thrd;			//��Ū����� 
	if(pthread_create(&thrd,NULL,func,NULL) != 0)	//�������߳�ģʽ 
	{
		printf("error\n");
	}
	sleep(1); 			//������첽�ģ������߳̽�����ʲô��û��
						//�����߳̽�����Ӱ������߳� 
						//�����߳�˯һ�룬�������Ǹ���ִ������� 
	return 0;
} 
