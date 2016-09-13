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

void printBackground()
{
	int x;
	for (x=0;x<backcount;x++)
	{
		if (background[x][0]!='\0')
		{
			if (check_background(backpid[x])==1)
			{
				printf("%s with pid %d exited normally.\n",background[x],backpid[x]);
				background[x][0]='\0';
				backpid[x]=0;
			}
		}
	}
}

int check_background(int num)
{
	char pid[10];
	char path[30] = "/proc/";
	pid_t child;
	struct stat sts;
	sprintf(pid,"%d",num);
	strcat(path,pid);
	stat(path,&sts);
	if (S_ISDIR(sts.st_mode))
		return 0;
	else
		return 1;
}