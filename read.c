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

void readCommand()
{
	char commands[2000],a;
	int v[100];
	int i=0,j=0,length,k,begin,end,l;
	while (1)
	{
		a = getchar();
		if (a=='\n'||a=='\0')
			break;
		else if (a==';')
		{
			v[j]=i;
			j++;
		}
		commands[i] = a;
		i++;
	}
	v[j]=i;
	commands[i]='\0';
	length = i;
	j=0;
	for (i=0;i<length;i++)
	{
		char *command = malloc(sizeof(char)*300);
		k=0;
		while(i<v[j])
		{
			command[k]=commands[i];
			k++;
			i++;
		}
		j++;
		command[k]='\0';
		begin = 0;
		end = strlen(command);
		while (isspace(command[begin]))
		    begin++;
		while ((end >= begin) && isspace(command[end]))
		   	end--;
		for (l=begin;l<=end;l++)
		    command[l-begin]=command[l];
		command[l-begin]='\0';
		runCommand(command);
		free(command);
	}
	return;
}