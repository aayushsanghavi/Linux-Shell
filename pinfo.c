#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

extern char *user, *home, *t, *args[20];
extern char temp[30], buff[2], cwd[1000], executable[30], buf2[1000], background[10][20], system_name[10];
extern int back, backpid[10], backcount;

void pinfo(char *pid)
{
	FILE *fp,*exe;
	char buff[100],buf[100];
	int values[4]={0,1,4,12},i=0,k=0;
	char addr[30] = "/proc/";
	strcat(addr,pid);
	strcat(addr,"/status");
	fp = fopen(addr,"r");
	while(fgets(buff,sizeof(buff),fp)!=NULL)
	{
    	if (i==values[k])
    	{
    		printf("%s",buff);
    		k++;
    	}
    	i++;
	}
	pclose(fp);

	char path[50] = "readlink -f ";
	char adr[30] = "/proc/";
	strcat(adr,pid);
	strcat(adr,"/exe");
	strcat(path,adr);
	exe = popen(path,"r");
	while (fgets(buf,sizeof(buf),exe)!=NULL)

	if ((int)strlen(buf)>=(int)strlen(home))
	{
		tilda(buf,executable);
		printf("Executable path: %s",executable);
	}
	else
		printf("Executable path: %s",buf);
	pclose(exe);
	return;
}