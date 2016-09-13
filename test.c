#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
#include <string.h>

int main(void)
{
	pid_t child;
	int cstatus;
	pid_t c;
	char *args[2];
	args[0] = "ls";
	//args[1] = "-l";
	args[1] = NULL;
	if ((child = fork()) == 0)
	{
		printf("Child: PID of Child = %ld\n", (long) getpid());
		execvp(args[0], args); /* arg[0] has the command name. */
		/* If the child process reaches this point, then */
		/* execvp must have failed. */
		fprintf(stderr, "Child process could not do execvp.\n");
		exit(1);
	}
	else
	{
		if (child == (pid_t)(-1))
		{
			fprintf(stderr, "Fork failed.\n");
			exit(1);
		}
		else
		{
			c = wait(&cstatus); /* Wait for child to complete. */
			printf("Parent: Child %ld exited with status = %d\n",(long) c, cstatus);
		}
	}
	return 0;
}