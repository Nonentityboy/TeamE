//signal
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
// *** //˵˵������⣺
//���Ȱѷ���������ǰ�棬����˵�ź����˸���ô��
//һ���ź����ˣ�cpu�ǵ�ѹ���֮��ģ���ͣ���й�����Ȼ���������ķ�����
//���źŴ�������Ȼ��ִ���������

//SIGSTOP SIGKILL ���ܲ�׽��ֱ���˳� 
void mmm(int sign)
{
	switch(sign)
	{
		case SIGINT:
			printf("SIGINT Signal\n");
			exit(0);
		case SIGALRM:
			printf("SIGALRM Signal\n");
			//alarm(5);		//�����Ͷ�ʱ��  
			//STGALRM Ĭ���ǳ����˳� 
			break;
		case SIGKILL:	//ʵ��֤����ȷʵ�ǣ����ܱ�����ֻ���� 
			printf("SIGKILL signal\n");
			exit(0); 
	}
}
//raise	���Լ����ź�
//alarm Ҳ�Ǹ��Լ����ź�	(��1�Σ�����while)
//int alarm(unsigned int seconds)
//about SIGBRT ��ʹ��׽��������Ҳ���쳣�˳�
//�Զ���sleep���� 
//wait����Ҳ���źţ�pause��SIGCHID��ʲôҲ���ɣ�-�ӽ����Ѿ�ֹͣ����ֹ 
int main()
{
	signal(SIGINT,mmm);//��ʵSIGINT��SIGALRM����������ûɶ 
	signal(SIGALRM,mmm);//SIGINT��2��SIGALRM��14
	//���Ǹ�����ϵͳ˵�ˣ��Ǽ���
	signal(SIGKILL,mmm); 
	printf("SIGKILL = %d\n",SIGKILL);
	while(1)
	{
		alarm(5);
		pause(); 	//һֱ�ڵȴ� 
		//sleep(1);
		printf("hello...\n");
	}
	return 0;
}
