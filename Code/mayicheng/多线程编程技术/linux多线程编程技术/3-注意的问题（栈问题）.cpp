#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "iostream"
using namespace std;
//Ϊʲô��ͬʱ���������������
//��Ϊ��������Ǵ���Σ�ϵͳ���������̣߳��ͻ��������ջ��Ȼ����Ǹ��ģ���Ӱ��	
//ͬʱҲ���첽�� 
void *func(void *t)			
{
	cout << t << endl; 
	int i = *(int *)t;
	while(1)
	{
		sleep(1); 
		printf("ptherad_create ok  %d\n",i);
	}
	return NULL;
}
void threadcreat()		//���棡��ǧ��ǵ����i1i2(ջ�ģ�������������û��)��һ���и����⣬�Ͷδ����� 
{						//Ҳ����Ū��ȫ�ֻ��߶��� 
	int i1 = 1,i2 = 2;
	pthread_t thrd1,thrd2;			//��Ū����� 
	cout << "&i1 = " << &i1 << " &i2 = " << &i2 << endl;
	if(pthread_create(&thrd1,NULL,func,&i1) != 0)	//�������߳�ģʽ 
	{
		printf("error\n");
	}
	if(pthread_create(&thrd2,NULL,func,&i2) != 0)	//�������߳�ģʽ 
	{
		printf("error\n");
	}
	while(1)
	sleep(1);
}
int main()
{
	int i1 = 1,i2 = 2;
	pthread_t thrd1,thrd2;			//��Ū����� 
	if(pthread_create(&thrd1,NULL,func,&i1) != 0)	//�������߳�ģʽ 
	{
		printf("error\n");
	}
	if(pthread_create(&thrd2,NULL,func,&i2) != 0)	//�������߳�ģʽ 
	{
		printf("error\n");
	}
	//threadcreat();
	while(1)
	sleep(1); 		
	return 0;
} 
