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

void tilda(char *t, char *dest)
{
	int i,j,k,check;
	for (j=0;j<(int)strlen(home);j++)
	{
		if(t[j]==home[j])
			check=1;
		else
		{
			check=0;
			break;
		}
	}
	if (check==1)
	{
		k=0;
		dest[k]='~';
		i=strlen(home);
		while(i<strlen(t))
		{
			dest[++k]=t[i];
			i++;
		}
		dest[++k]='\0';
	}
	else
	{
		i=0;
		while (t[i]!='\0')
		{
			dest[i]=t[i];
			i++;
		}
		dest[i]='\0';
	}
}