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

int redirection(int len)
{
	int i,count=0;

	for (i=1;i<len;i++)
	{
		if (!(strcmp(args[i],"<")))
		{
			args[i]=NULL;
			strcpy(file,args[i+1]);
			if (count == 0)
				count = 1;
			else
				return 0;
		}
		else if (!(strcmp(args[i],">")))
		{
			if (count == 1)
			{
				args[i]=NULL;
				strcpy(file2,args[i+1]);
				count += 10;
			}
			else
			{
				args[i]=NULL;
				strcpy(file,args[i+1]);
				count = 10;
			}
		}
		else if (!(strcmp(args[i],">>")))
		{
			args[i]=NULL;
			strcpy(file,args[i+1]);
			if (count == 1)
				count += 100;
			else
				count = 100;
		}
	}
	if (count == 1)
		return 1;
	else if (count == 10)
		return 2;
	else if (count == 100)
		return 3;
	else if (count == 11)
		return 4;	
	else if (count == 101)
		return 5;
	else
		return 0;
}

void runRedirect(int type)
{
	pid_t child;
	int fd,c,cstatus,fd2;
	
	child = fork();
	if (child == 0)
	{
		if (type == 1)
	    {   
	        if ((fd = open(file, O_RDONLY, 0)) < 0)
	    	{
	        	perror("Couldn't open input file");
	        	exit(0);
	    	}           
			dup2(fd, STDIN_FILENO);
	    }
		else if (type == 2)
	    {
	        if ((fd = creat(file, 00644)) < 0)
	    	{
	        	perror("Couldn't open output file");
	        	exit(0);
	    	}           
			dup2(fd, STDOUT_FILENO);
	    }
		else if (type == 3)
	    {
	        if ((fd = open(file, O_CREAT|O_RDWR|O_APPEND, 00644)) < 0)
	    	{
	        	perror("Couldn't open output file");
	        	exit(0);
	    	}           
			dup2(fd, STDOUT_FILENO);
	    }
	    else if (type > 3)
	    {
	        if ((fd = open(file, O_RDONLY)) < 0)
	    	{
	        	perror("Couldn't open input file");
	        	exit(0);
	    	}           
			dup2(fd, STDIN_FILENO);
		   	if (type == 4)
		    {
		        if ((fd2 = creat(file2, 00644)) < 0)
		        {
		        	perror("Couldn't open output file");
		        	exit(0);
		    	}           
				dup2(fd2, STDOUT_FILENO);
		    }
		   	else if (type == 5)
		    {
		        if ((fd2 = open(file, O_CREAT|O_RDWR|O_APPEND, 00644)) < 0)
		        {
		        	perror("Couldn't open output file");
		        	exit(0);
		    	}           
				dup2(fd2, STDOUT_FILENO);
		    }
		}
		close(fd);
		if (type > 3)
			close(fd2);
		execvp(args[0], args);
	}
	else if (child < 0)
	{
		fprintf(stderr,"Some error occured.\n");
		exit(1);
	}
	else
		c = wait(&cstatus);
}