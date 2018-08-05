#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main()
{ 
	int st = socket(AF_INET,SOCK_STREAM,0);	//AF_INET����internet���磬SICK_STREAM��TCPЭ�� 
	
	struct sockaddr_in addr;	//����һ��IP��ַ�ṹ
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;	//���ýṹ��ַ����ΪTCP/IP��ַ
	addr.sin_port = htons(8080);	//ָ��һ���˿ںţ�8080��htons����short���ʹ�host�ֽ�����ת��Ϊnet�ֽ����� 
	addr.sin_addr.s_addr = inet_addr("192.168.122.1");	//ת���ַ�������addr�ṹ
	
	if(connect(st,(struct sockaddr *)&addr,sizeof(addr)) == -1)
	{
		printf("connect faile,%s\n",strerror(errno));
		return 0;
	}
	char s[100];
	memset(s,0,sizeof(s));
	strcpy(s,"Hello world!");
	if(send(st,s,strlen(s),0) == -1)
	{
		printf("send faile,%s\n",strerror(errno));
		return 0;		
	} 
	return 0;
}
