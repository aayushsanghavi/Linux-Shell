#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

char *user, *home, *t, *args[20];
char temp[30], buff[2], cwd[1000], executable[30], buf2[1000], background[10][20], system_name[10];
int back, backpid[10], backcount;

int main()
{
	char buf1[PATH_MAX+1];
	home = getcwd(buf1,PATH_MAX+1);
	home[strlen(home)+1]='\0';
	backcount=0;
	int x,y,number;

	for (x=0;x<10;x++)
	{
		background[x][0]='\0';
		backpid[x]=0;
	}
	while(1)
	{
		startPrint();
		readCommand();
		printBackground();
	}
	return 0;
}