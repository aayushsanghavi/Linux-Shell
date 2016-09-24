#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

extern char *user, *home, *t, *args[20], file[20], file2[20];
extern char temp[30], buff[2], cwd[1000], executable[30], buf2[1000], background[10][20], system_name[10];
extern int back, backpid[10], backcount;

int piping(int len)
{
	int i,count=0;

	for (i=1;i<len;i++)
	{
		if (!(strcmp(args[i],"|")))
			count++;
	}
	if (count == 0)
		return 0;
	else
		return 1;
}

void runPipes(char command[])
{
	pid_t child,pid;
	int c,cstatus,i,len,j,k;
	i=0;
	char *argv[20],*token, *arg[20][20];

	token = strtok(command,"|");
	argv[i] = token;
	i++;
	while(token!=NULL)
	{
		token = strtok(NULL,"|");
		argv[i] = token;
		i++;
	}
	argv[i] = NULL;
	len = i-1;
	for (i=0;i<len;i++)
	{
		j=0;
		token = strtok(argv[i]," ");
		arg[i][j] = token;
		j++;
		while(token!=NULL)
		{
			token = strtok(NULL," ");
			arg[i][j] = token;
			j++;
		}
		arg[i][j] = NULL;
	}

	int fd[2*len];
	for(i=0;i<len;i++)
		pipe(fd+i*2);

    j = 0;
	for(i=0;i<len;i++)
	{
	    child = fork();
		if (child == 0)
		{
			if (i+1<len)
				dup2(fd[j+1],STDOUT_FILENO);

			if (j!=0)
				dup2(fd[j-2],STDIN_FILENO);

			for(k=0;k<2*len;k++)
				close(fd[k]);

			execvp(arg[i][0], arg[i]);
		}
		else if (child < 0)
		{
			fprintf(stderr,"Some error occured.\n");
			exit(1);
		}
		j += 2;
	}
	
	for(i=0;i<2*len;i++)
        close(fd[i]);

    for(i=0;i<len+1;i++)
        c = wait(&cstatus);
}