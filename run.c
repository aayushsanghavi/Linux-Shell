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

void runCommand(char *command)
{
	pid_t child;
	int y, redirect;
	int cstatus,i=1,check,k;
	pid_t c;
	char *token, *value, *process;
	char variable[30];
	token = strtok(command, " ");
	args[0] = token;
	process = token;

	if (!(strcmp(process,"cd")))
		check=1;
	else if (!(strcmp(process,"pwd")))
		check=2;
	else if (!(strcmp(process,"echo")))
		check=3;
	else if (!strcmp(process,"pinfo"))
		check=4;
	else
		check=5;
	token = strtok(NULL," ");
	while(token != NULL)
   	{
   		if (strcmp("&",token))
   		{
			args[i] = token;
			i++;
			back=0;
		}
		else
			back=1;
		token = strtok(NULL," ");
	}
	args[i]=NULL;

	redirect = redirection(i);
	if (redirect != 0)
	{
		runRedirect(redirect);
		return;
	}

	if (check==1) //cd
	{
		if (args[1][0]=='~')
			chdir(home);
		else
			chdir(args[1]);
	}
	else if (check==2) //pwd
		printf("%s\n",getcwd(buf2,PATH_MAX+1));
	else if (check==3) //echo
	{
		if (args[1][0]=='$')
		{
			for (k=1;k<(int)strlen(args[1]);k++)
				variable[k-1]=args[1][k];
			variable[k-1]='\0';
			if (getenv(variable)!=NULL)
				printf("%s\n",getenv(variable));
			else
				printf("No such environment variable found.\n");
		}
		else if(args[1][0]=='"')
		{
			int j;
			if (i>2)
			{
				for (j=1;j<(int)strlen(args[1]);j++)
					printf("%c",args[1][j]);
				for (k=2;k<i-1;k++)
					printf(" %s",args[k]);
				printf(" ");
				for (j=0;j<(int)strlen(args[i-1])-1;j++)
					printf("%c",args[i-1][j]);
			}
			else
			{
				for (j=1;j<(int)strlen(args[1])-1;j++)
					printf("%c",args[1][j]);
			}
			printf("\n");
		}
		else
		{
			for (k=1;k<i;k++)
				printf("%s ",args[k]);
			printf("\n");
		}
	}
	else if (check==4)
		pinfo(args[1]);
	else if (check==5) //others
	{
		child = fork();
		if (child==0)
		{
			execvp(args[0], args);
			fprintf(stderr,"Requested process could not do execvp.\n");
			exit(1);
		}
		else
		{
			if (back==0)
				c = wait(&cstatus);
			else if (back==1)
			{
				for (y=0;y<strlen(process);y++)
					background[backcount][y]=process[y];
				background[backcount][y]='\0';
				backpid[backcount]=child;
				backcount++;
				back=0;
			}

		}
	}
}