#include <sys/types.h>
#include <sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#define CHAT_O 4	//私聊功能
#define REGISTER 1  // 注册
#define LOGIN 2		//  登录
#define QUIT 3		//退出  //用户下线
#define ADD_FRI 5   //添加好友
#define DEL_FRI 6   //删除好友
#define DIS_FRI 7   //显示(刷新)好友列表
#define CRE_GRO 8   //创建一个群
#define DIS_GRO 9   //显示(刷新)群列表
#define CHAT_GRO 10 //群聊
#define QUIT_GRO 11 //退群
#define SEND_FILE 12 //发送文件 

#define REG_SUC 10001	  //注册成功
#define LOG_SUC 10002	  //登陆成功
#define LOG_FAU 10003	  //登录失败
#define ADD_FRI_SCU 10004  //添加好友成功
#define ADD_FRI_FAU 10005  //添加好友失败
#define ACC_ADD 10006	  //好友请求
#define DEL_FRI_MASG 10007 //删除好友通知
#define DEL_FRI_SCU 10008  //删除成功通知
#define MASG_ACC 10009	 //消息提示
#define OUT_ROOM 10010	 //离开聊天室通知
#define A_MESS 10011	   //保存为普通消息
#define OFF_MESS 10012	 //保存为未读消息
//#define DIS_MES_HISS 10013 //读自己的历史消息(美观需求)
#define DIS_MES_ON 10014   //显示未读消息
#define DIS_MES_OFF 10015  //读取未读消息
#define DIS_MES_HIS 10016  //读取历史记录
#define CRE_GRO_SUC 10017  //创建群成功
#define INV_MEM 10018	  //邀请进群
#define DIS_OFF_MES 10019  //提示未读群通知//第一层通知
#define DIS_ON_MES 10020   //查看未读群通知 //群聊界面
#define A_GRO_MESS 10021   //保存为普通群消息
#define OFF_GRO_MESS 10022 //保存为未读群消息
#define DIS_GRO_MEM 10023  //显示群成员
#define TIPS 10024		   //离线拉群通知
#define DIS_GRO_HIS 10025 //查看群历史记录
#define RECV_FILE 10026 //接受文件



int room_status = 0;
char client_name[20] = {0};
char group[20] = {0};

#define PORT 8848
/*请求-数据包  包含 操作标记 发送方 接收方  信息
*/
typedef struct masg
{
	int flag;
	char recv_mem[20];
	char send_mem[20];
	char group[20];
	char data[1024];
	int lenth;
} MASG;
/***********请求-数据包**************/
/*退出函数**********/
void quit(MASG *masg, int socket, int flag)
{
	masg->flag = flag;
	send(socket, masg, sizeof(MASG), 0);
}
/************/
/***************个人界面******************/
void meun_per(void)
{
	//system("clear");
	puts("\t>>>>个人主页<<<<<<");
	puts(">我的好友\t\t>9.注销登录");
	//puts("----------------------------------------------");
	puts("| >1.添加好友\t>2.删除好友\t\t|");
	puts("| >0.私聊>\t3.显示(刷新)好友列表\t|");
	//puts("----------------------------------------------");
	puts(">我的群");
	//puts("----------------------------------------------");
	puts("| >4.创建群\t>5.显示(刷新)群列表\t|");
	puts("| >6.进入群聊\t>7. 退出群聊\t\t|");
	//puts("----------------------------------------------");
	puts("|>>>8.发送文件");
	//puts("--------------------------------------------");
	puts("|tips---：");
}
/***********收文件***************/
void recv_file(MASG*masg,int socket)
{
	char file_name[20];
	int fd = 0;
	memcpy(file_name,masg->group,sizeof(masg->group));
	if((fd = open(file_name,O_CREAT|O_APPEND|O_WRONLY,S_IRUSR|S_IWUSR))==-1)
	{
		perror("open");
	}else{
		printf("create file success\n");
	}
	//printf("%s\n",masg->data);
	int count =write(fd,masg->data,masg->lenth);
	//printf("count_write = %d\n masglenth = %d\n",count,masg->lenth);
	close(fd);
}
/*************发文件****************/
void send_file(MASG*masg,int socket)
{
	int fd = 0;
	char pathname[20] = {0};
	char send_buf[1024] = {0};
	system("clear");
	printf("发送文件给?:");
	scanf("%s",masg->recv_mem);
	getchar();
	printf("请输入你要发送的路径:");
	scanf("%s",pathname);
	getchar();
    printf("文件名:");
	scanf("%s",masg->group);
	getchar();
	masg->flag = SEND_FILE;
	
	if((fd = open(pathname,O_RDONLY))==-1)
	{
		perror("open");
		return;
	}else{
		printf("open file success\n");
	}
	
	int count  = 0;
	masg->lenth = 0;
	while((count = read(fd,send_buf,sizeof(send_buf)))!=0)
	{
	masg->lenth = count;
	//printf("after count %d\nmasglenth  = %d\n",count,masg->lenth);
	memcpy(masg->data,send_buf,count);
	//printf("%s\n",masg->data);
	//printf("after count %d\nmasglenth  = %d\n",count,masg->lenth);
	send(socket,masg,sizeof(MASG),0);
	}
	close(fd);

}
/*************退群******************/
void quit_group(MASG*masg,int socket)
{
	printf("请输入要退出的群名:");
	scanf("%s",masg->group);
	masg->flag = QUIT_GRO;
	send(socket,masg,sizeof(MASG),0);

}
/*************群聊******************/
void chat_group(MASG *masg, int socket)
{
	printf("请输入要进入的群名：");
	scanf("%s", masg->group);
	getchar();
	masg->flag = CHAT_GRO;
	system("clear");

	printf("+---h to history----群聊：%s-----------q to quit-+\n", masg->group);
	puts(">群成员:                             +-'*'邀请进群-+");
	strcpy(group,masg->group);
	masg->flag = DIS_GRO_MEM; //显示群成员
	send(socket, masg, sizeof(MASG), 0);
	masg->flag = DIS_OFF_MES; //读取未读消息
	send(socket, masg, sizeof(MASG), 0);
	masg->flag = CHAT_GRO;
	room_status = 1;
	while (1)
	{
		scanf("%s", masg->data);
		getchar();
		if (strcmp(masg->data, "q") == 0)
		{
			//masg->flag = OUT_ROOM;   //退出聊天室通知
			//send(socket, masg, sizeof(MASG), 0);
			memset(group,0,sizeof(group));
			break;
		}
		if (strcmp(masg->data, "h") == 0)
		{
			masg->flag = DIS_GRO_HIS;  //获取群聊天记录
			send(socket,masg,sizeof(MASG),0);
			masg->flag = CHAT_GRO;
			continue;
		}
		if (strcmp(masg->data, "*") == 0)
		{
			printf("被邀请人：");
			scanf("%s", masg->recv_mem);
			masg->flag = INV_MEM;
			send(socket, masg, sizeof(MASG), 0);
			masg->flag = CHAT_GRO;
			continue;
		}
		send(socket, masg, sizeof(MASG), 0);
	}
	room_status = 0;
	return;
}

/***********显示(刷新)群列表**********/
void dis_group(MASG *masg, int socket)
{
	masg->flag = DIS_GRO;
	send(socket, masg, sizeof(MASG), 0);
}
/************创建群********************/
void create_group(MASG *masg, int socket)
{
	printf("请输入想要创建的群名:");
	scanf("%s", masg->data);
	masg->flag = CRE_GRO;
	send(socket, masg, sizeof(MASG), 0);
}
/***********私聊*************************/
void chat_only(MASG *masg, int socket)
{
	printf("请选择聊天对象(name):");
	scanf("%s", masg->recv_mem);
	masg->flag = CHAT_O;

	system("clear");
	printf("+---h to history----正在与%s聊天-----------q to quit-+\n", masg->recv_mem);
	strcpy(client_name,masg->recv_mem);
	masg->flag = DIS_MES_OFF;
	send(socket, masg, sizeof(MASG), 0);
	masg->flag = CHAT_O;
	room_status = 1;
	while (1)
	{
		scanf("%s", masg->data);
		getchar();
		if (strcmp(masg->data, "q") == 0)
		{
			masg->flag = OUT_ROOM;
			send(socket, masg, sizeof(MASG), 0);
			memset(client_name,0,sizeof(client_name));
			break;
		}
		if (strcmp(masg->data, "h") == 0)
		{
			masg->flag = DIS_MES_HIS;
			send(socket, masg, sizeof(MASG), 0);
			masg->flag = CHAT_O;
			continue;
		}
		send(socket, masg, sizeof(MASG), 0);
	}
	room_status = 0;
	return;
}
/***********显示(刷新)好友列表***********/
void dis_fir_list(MASG *masg, int socket)
{
	masg->flag = DIS_FRI;
	send(socket, masg, sizeof(MASG), 0);
}

/************删除好友*******************/
void del_fri(MASG *masg, int socket)
{
	printf("请输入你想要删除的好友:");
	scanf("%s", masg->recv_mem);
	masg->flag = DEL_FRI;
	send(socket, masg, sizeof(MASG), 0);
}
/*****************************/

/**********加好友******/
void add_fri(MASG *masg, int socket)
{
	printf("send_mem=%s\n", masg->send_mem);
	printf("flag = %d\n", masg->flag);
	printf("请输入你想要添加的好友（名字）：");
	scanf("%s", masg->recv_mem);
	masg->flag = ADD_FRI;
	printf("after flag = %d\n", masg->flag);
	send(socket, masg, sizeof(MASG), 0);
}


/*****************登录注册界面**************/
void meun_rll(void)
{
	system("clear");
	puts("\t\twelcome");
	puts("\t+------------------------------+");
	puts("\t|\t1.注册\t2.登录\t\t|");
	puts("\t|\t3.退出\t\t\t|");
	puts("\t+-------------------------------+");
	puts("\t\tmy_chat v1.2  ");
}
/********************************/

/*********
注册函数
成功返回1 失败返回-1
参数为一个已连接的套接字
int login(int socket, int flag)
{
	MASG masg;
	while(1)
{
	
	printf("**************login**********\n");
	masg.flag = flag;
	//输入flag
	printf("请输入用户名：");
	scanf("%s", masg.send_mem);
	getchar();
	//输入用户名
	printf("请输入密码：");
	scanf("%s", masg.data);
	getchar();
	//输入密码

	send(socket, &masg, sizeof(MASG), 0);
	//发包
	recv(socket,&masg,sizeof(MASG),0);
	if(masg.flag == LOG_FAU)
	{

	printf("登录失败！\n");
	continue;
	}
	if(masg.flag == LOG_SUC)
	break;
	}

	//传回信息，是否成功 //交给主接收函数;
	//printf("******************log_end\n");
	per(&masg, socket); //进入个人界面
}
*/
int reg(int socket, int flag)
{
	MASG masg;
	system("clear");
	printf("---------------注册--------------\n");

	masg.flag = flag;
	//输入flag
	printf("请输入用户名：");
	scanf("%s", masg.send_mem);
	getchar();
	//输入用户名
	printf("请输入密码：");
	scanf("%s", masg.data);
	getchar();
	//输入密码

	send(socket, &masg, sizeof(MASG), 0);
	//发包
	//传回信息，是否成功 //交给主接收函数

	printf("--------------------------------\n");
}
/*********************注册函数*****************/

void my_err(const char *err_string, int line)
{
	fprintf(stderr, "line:%d ", line);
	perror(err_string);
	exit(1);
}

void *show_client(void *arg)
{
	MASG masg;
	int socket_c = *(int *)arg;
	while (1)
	{
	int count = 0;
		//do
		//{
		count +=recv(socket_c, &masg+count, sizeof(MASG)-count, MSG_WAITALL);
		//}while(count!=sizeof(MASG)&&count!=0);
		//printf("count = %d\n",count);
		count = 0;
		 //printf(".%s\n",masg.data);
		//printf("return number = %d\n",masg.flag);
		int flag = masg.flag;
		if (flag==0)
		break;
		switch (flag)
		{
		case REG_SUC:
			printf("注册成功！\n");
			break;
		case LOG_SUC:
			printf("登陆成功!\n");
			break;
		case LOG_FAU:
			printf("账号或密码不存在，请重新输入!\n");
			break;
		case QUIT:
			printf("%s 已注销\n", masg.send_mem);
			pthread_exit(0);                      
			break;
		case ADD_FRI_SCU:
			printf("%s 已接受了你的添加请求\n", masg.recv_mem);
			break;
		case ADD_FRI_FAU:
			printf("对方拒绝了你的好友请求\n");
			break;
		case ACC_ADD:
			printf("%s 向你发来一个好友请求\n", masg.send_mem);
			char acc;
			printf("是否同意(y/n)\n");
			scanf("%c", &acc);
			getchar();
			if (acc == 'y')
			{
				masg.flag = ADD_FRI_SCU;
				send(socket_c, &masg, sizeof(MASG), 0);
			}
			else if (acc == 'n')
			{
				masg.flag = ADD_FRI_FAU;
				send(socket_c, &masg, sizeof(MASG), 0);
			}
			break;

		case DEL_FRI_MASG:
			printf("%s 将你移出友好友列表\n", masg.send_mem);
			break;
		case DEL_FRI_SCU:
			printf("你已经成功将 %s 移出好友\n", masg.recv_mem);
			break;
		case DIS_FRI:
			printf("%s\n", masg.data);
			break;
		case CHAT_O:
			if (room_status && strcmp(masg.send_mem,client_name)==0)
			{
				printf("                                      %s:%s\n", masg.send_mem, masg.data);
				masg.flag = A_MESS;
				send(socket_c, &masg, sizeof(MASG), 0);
			}
			else 
			//if (!room_status)
			{
				printf("%s 给你发来一条消息\n", masg.send_mem);
				masg.flag = OFF_MESS;
				send(socket_c, &masg, sizeof(MASG), 0);
			}
			break;
		case OUT_ROOM:
			if (room_status)
				printf("对方已退出聊天!(仍可接受消息)\n");
			break;
		case DIS_MES_ON:
			printf("有一条来自 %s 的消息\n", masg.recv_mem);
			break;
		case DIS_MES_OFF:
			printf("                                     %s:%s\n", masg.recv_mem, masg.data);
			break;
		case DIS_MES_HIS:
			printf("%s:%s\n", masg.send_mem, masg.data);
			break;
		//case DIS_MES_HISS:
		//	printf("me:%s",masg.data);
		//	break;
		case CRE_GRO_SUC:
			printf("群创建成功！\n");
			break;
		case DIS_GRO:
			printf("%s\n", masg.data);
			break;
		case INV_MEM:
			printf("%s 将你拉入群聊 %s\n", masg.send_mem, masg.group);
			break;
		case CHAT_GRO:
			if (room_status && strcmp(masg.group,group)==0)
			{
				printf("                                      %s:%s\n", masg.send_mem, masg.data);
				masg.flag = A_GRO_MESS;
				send(socket_c, &masg, sizeof(MASG), 0);
			}
			else 
			//if (!room_status)
			{
				printf("%s 群有一条新消息\n", masg.group);
				masg.flag = OFF_GRO_MESS;
				send(socket_c, &masg, sizeof(MASG), 0);
			}
			break;
		case DIS_GRO_MEM:
			printf("|%s|\n", masg.data);
			break;
		case TIPS:
			printf("%s 将你拉如群聊 %s\n", masg.send_mem, masg.group);
			break;
		case DIS_ON_MES:
			printf("%s 有一条来自 %s 的消息\n", masg.group, masg.recv_mem);
			break;
		case DIS_OFF_MES:
			printf("                                     %s:%s\n", masg.recv_mem, masg.data);
			break;
		case DIS_GRO_HIS:
			printf("%s:%s(history)\n", masg.send_mem, masg.data);
			break;
		case RECV_FILE:
			recv_file(&masg,socket_c);
			printf("正在接受文件\n");
			break;

		default:
			printf("errno! flag = %d\n",masg.flag);
			break;
		}
	}
}
/***********个人界面*******************/
void per(MASG *masg, int socket)
{
	pthread_t id1, id2;
	int err = pthread_create(&id1, NULL, show_client,&socket);
	if (err != 0)
		printf("%d\n", errno);
	int status = 0;
	while (1)
	{
		//system("clear");
		meun_per();
		masg->flag = DIS_MES_ON; //提示个人未读消息
		send(socket, masg, sizeof(MASG), 0);
		masg->flag = DIS_ON_MES; //提示群未读消息
		send(socket, masg, sizeof(MASG), 0);
		char flag ;
		scanf("%c", &flag);
		switch (flag-'0' + 4)
		{
		case ADD_FRI:
			add_fri(masg, socket);
			break;
		case DEL_FRI:
			del_fri(masg, socket);
			break;
		case 13:
			quit(masg, socket, 3);
			return;
		case DIS_FRI:
			dis_fir_list(masg, socket);
			break;
		case CHAT_O:
			chat_only(masg, socket);
			break;
		case CRE_GRO:
			create_group(masg, socket);
			break;
		case DIS_GRO:
			dis_group(masg, socket);
			break;
		case CHAT_GRO:
			chat_group(masg, socket);
			break;
		case QUIT_GRO:
			quit_group(masg,socket);
			break;
		case SEND_FILE:
			send_file(masg,socket);
			break;
		default:
			fflush(stdin);
			break;
		}
	}
	//pthread_exit(0);
	pthread_join(id1, (void *)&status);
}
/**************************************/
int login(int socket, int flag)
{
	MASG masg;
	while(1)
{
	
	system("clear");
		printf("-----------登录----------\n");
		masg.flag = flag;
		//输入flag
		printf("请输入用户名：");
		scanf("%s", masg.send_mem);
		getchar();
		//输入用户名
		printf("请输入密码：");
		scanf("%s", masg.data);
		getchar();
		//输入密码

		send(socket, &masg, sizeof(MASG), 0);
		//发包
		recv(socket,&masg,sizeof(MASG),0);
		if(masg.flag == LOG_FAU)
		{

		printf("账号不存在或密码错误！\n");
		continue;
		}
		if(masg.flag == LOG_SUC)
		break;
	}

	//传回信息，是否成功 //交给主接收函数;
	//printf("******************log_end\n");
	per(&masg, socket); //进入个人界面
}

/*
void* far_client(void*arg)
{
  MASG masg;

  int socket_c = *(int*)arg;
   printf("请输入你要操作的数字：");
   scanf("%d",&masg.flag);
   getchar();
   switch (masg.flag)
   {
   c
   }
}
*/
int main(int argc, char *argv[])
{
	int socket_c;
	int serv_port;
	struct sockaddr_in serv_addr;
	//int status;
	int flag;
	//char    recv_buf[1024];
	//初始化服务端的地址结构
	memset(&serv_addr, 0, sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	//创建一个套接字
	socket_c = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_c < 0)
	{
		my_err("socket", __LINE__);
	}
	if (connect(socket_c, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) < 0)
	{
		my_err("connect", __LINE__);
	}

	//pthread_t id1, id2;
	//int err = pthread_create(&id1, NULL, show_client, &socket_c);
	//if (err != 0)
	//	printf("%d\n", errno);

	//pthread_create(&id2,NULL,far_client,&socket_c);
	//pthread_join(id2,(void *)&status);
	while (1)
	{
		meun_rll(); //打印第一层目录

		//printf("请输入选项:");
		scanf("%d", &flag);
        getchar();

		switch (flag)
		{
		case REGISTER:
			reg(socket_c, flag);
			break;
		case LOGIN:
			login(socket_c, flag);
			break;
		case QUIT:
			return 0;
		default:
			fflush(stdin);
			break;
		}
	}

	//pthread_join(id1, (void *)&status);
}
