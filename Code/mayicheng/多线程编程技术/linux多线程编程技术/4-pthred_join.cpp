#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "iostream"
using namespace std;
void *func(void *t)
{
	int m = 3; 				//����Ǹ�3�Σ�ջ��ߵ� 
	//static int m = 3;		//��̬���ģ�һ��3�� 
	while(m--)
	{
 		sleep(1);
		printf("ptherad_create ok\n");
	}
	return NULL;
}
int main()
{
	pthread_t thrd,thrd1;		
	if(pthread_create(&thrd,NULL,func,NULL) != 0)	
	{
		printf("error\n");
	}
	if(pthread_create(&thrd1,NULL,func,NULL) != 0)	
	{
		printf("error\n");
	}
	pthread_join(thrd,NULL);		//���˾Ͳ�����
	//pthread_join������������ 
	pthread_join(thrd1,NULL);		//���̹߳��𣬵ȴ�thrd1�˳������ȣ�
									//����wait 
	printf("main end!\n"); 			
	return 0;
} 
