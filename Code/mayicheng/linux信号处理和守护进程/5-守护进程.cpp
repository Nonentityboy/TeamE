//�����ػ����� 
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <syslog.h> 
//syslog�ṩ����
//openlog��������־��syslogд����־��closelog�ر���־
//Ҳ���Բ�����openlog��closelog 
int main()
{
	int pid = fork();
	if(pid > 0)
	{
		exit(0);
	}
	if(pid == 0)
	{
		setsid();
		chdir("/");
		umask(0);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
	syslog(LOG_INFO,"mydaemin is OK\n");
	while(1)
	{
		sleep(1);
	}
	return 0;
}
