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
	int st = socket(AF_INET,SOCK_STREAM,0);	//��ʼ��socket 
	
	int on = 1;
	if(setsockopt(st,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)) == -1)
	{
		printf("setsocopt failed %s\n",strerror(errno));
		return 0;
	}
	
	struct sockaddr_in addr;	//����һ��IP��ַ�ṹ
	memset(&addr,0,sizeof(addr));
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);	//INADDR_ANY����server�����е�ַ
	//��IP��server����� 
	if(bind(st,(struct sockaddr *)&addr,sizeof(addr)) == -1)
	{
		printf("bin failed %s\n",strerror(errno));
		return 0;
	}
	//server�˿�ʼlisten��
	if(listen(st,20) == -1)
	{
		printf("listen failed %s\n",strerror(errno));
		return 0;
	}
	
	char s[1024];
	int client_st = 0;		//client��socket 
	socklen_t len = 0;
	struct sockaddr_in client_addr; 	//client��IP��ַ 
	void *p = &client_addr;
	int i;
	for(i = 0;i < 5;i++)
	{
		memset(&client_addr,0,sizeof(client_addr));
		socklen_t len = sizeof(client_addr);
		//accept��������ֱ���пͻ������ӹ�����accept����client��socket������ 
		client_st = accept(st,(struct sockaddr *)&client_addr,&len);
		if(client_st == -1)
		{
			printf("accept error,%s\n",strerror(errno));
			return 0;
		}
		memset(s,0,sizeof(s));
		if(recv(client_st,s,sizeof(s),0) == -1)	//������ 
		{
			printf("recv falied %s\n",strerror(errno));
			close(client_st);
			return 0;
		}
		printf("revc is %s\n",s);
		close(client_st);
	}
	return 0;
} 
