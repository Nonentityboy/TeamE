#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
int pthread_join(pthread_t th,void **thr_return);
//Ӧ���Ƿ���ֵ������ 
//�̷߳��ص��������͵�ָ��
void test()
{
	int  *a = (int *)malloc(sizeof(a));
	*a = 300;
	//pthreda_exit(void *)
	pthread_exit((void *)a);
 } 
void *func(void *t)
{
	test();			//�����д��p�ǿգ����þʹ��� 
	return NULL;
}
int main()
{
	pthread_t trd;
	int i = 100000;			//��67000���� 
	//while(i--)
	if(pthread_create(&trd,NULL,func,NULL) != 0)		//&,==0�ǳɹ� 
	{
		printf("error %d\n",100 - i);
	}
	int *p = NULL;
	pthread_join(trd,(void **)&p);				//�ͽ���һ�����ͷŵ��̡߳�
	//�������ͷţ�����֮�󣬺ͽ���һ������һ���ṹ����ά�����أ� 
	printf("*p = %d\n",*p);
	printf("success\n");		//�����ͳɹ��� 
	return 0;
} 
