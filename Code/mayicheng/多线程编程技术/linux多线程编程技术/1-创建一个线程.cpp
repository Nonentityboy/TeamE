#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "iostream"
//�߳�Ҳ���첽�ģ�û��˳��� 
void test()
{
	pthread_exit(NULL);	//���棬��������ǵ�3�ַ��������ǵڶ���
						//�ڶ����Ǳ������߳�ȡ�� 
}
using namespace std;
void *func(void *arg)//�߳���ں��� 
{
	printf("pthread start\n");
	test();
	printf("pthread end\n");
	return NULL;
}
void *func1(void *arg)//�߳���ں��� 
{
	while(1)
	{
		sleep(1);
		printf("pthread1 start\n");
	}
	return NULL;
}
//�������߳̽�������ô��������
//���������߳̽�������Ӱ������߳� 
//��һ�̵߳�����exit�������������̾ͻ���ֹ��
//����ź�Ĭ�϶�������ֹ���̣���ô���̾���ֹ�ˡ�

//�߳̽�������
//1.return
//2.�߳̿��Ա���ͬһ�����е������߳�ȡ��
//3.�̵߳���ptread_exit(NULL) 
int main()
{
	pthread_t thrd,thrd1;
	if(pthread_create(&thrd,NULL,func,NULL) != 0)
	{
 		cout << thrd <<  endl;	//û����������ɶ 
		printf("error is %s\n",strerror(errno));
	}
	if(pthread_create(&thrd1,NULL,func1,NULL) != 0)
	{
		printf("error is %s\n",strerror(errno));
	}
	while(1)
	sleep(1);
	return 0;
} 
