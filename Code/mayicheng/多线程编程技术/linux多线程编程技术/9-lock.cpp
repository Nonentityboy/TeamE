#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
//������ؼ���ʱ����һ�£�����ʱ��ͱ����ˣ����� 
//pthread_cancel
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//֮��lock��unclock�йأ�ֻҪ++��������Ҫ�����Ŷ�
//����עɶʱ���
//���Ǳ���򿪣����򿪾ͳ����� 
void *func(void *t)		 
{
	pthread_mutex_lock(&mutex);	//��mutex����������һ��ԭ�Ӳ����������ܳ��������߳�ͬʱִ��������� 
	int i = 7;					//�첽�� 
	while(i--)
	{
		sleep(1);
		printf("hello %d\n",*((int *)t));
	}
	pthread_mutex_unlock(&mutex);
}
void *func2(void *t)		 
{
	pthread_mutex_lock(&mutex);
	int i = 7;					 
	while(i--)
	{
		sleep(1);
		printf("hello %d\n",*((int *)t));
	}
	pthread_mutex_unlock(&mutex);
}
int main()
{
	pthread_t thr1,thr2;
	int a,b;
	a = 1;
	b = 2;
	if(pthread_create(&thr1,NULL,func,&a) != 0)
	{
		printf("error pthread_create\n");
	}
	if(pthread_create(&thr2,NULL,func2,&b) != 0)
	{
		printf("error pthread_create\n");
	}
	pthread_join(thr1,NULL);
	pthread_join(thr2,NULL);
	printf("main exit\n");
	return 0;
}
