#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
//pthread_detach(pthread_t th);			//�����Լ����Լ�detach�� 
//һ���̳߳�Ϊ�˿ɷ����̣߳��ͺͿ����̣߳����������̣߳�û��ϵ�ˣ�����ʹ��pthread_join�� 

//�ɷ����̵߳�ʹ�ó��������˲���¼struct��Ϣ�� 
//1.���̲߳���Ҫ�ȴ����߳�
//2.���̲߳���ϵ���̵߳ķ����� 
void *func(void *t)
{
	printf("hello\n");
	return NULL;
}
int main()
{
	pthread_t thr;
	if(pthread_create(&thr,NULL,func,NULL) != 0)
	{
		printf("error pthread_create\n");
	}
	pthread_detach(thr);
	pthread_join(thr,NULL);
	printf("no guanxi\n");
	sleep(2);
	return 0;
} 
