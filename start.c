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

void startPrint()
{
	int i,j,check,k;
	FILE *os;

	//get the username
	user = getenv("USERNAME");

	//get the system name
	/*os = popen("lsb_release -i", "r");
	i=0;
	while (fgets(buff, sizeof(buff), os)!=NULL)
    {
	  	temp[i] = buff[0];
		i++;
    }
	pclose(os);
	for (j=16;j<i-1;j++)
		system_name[j-16] = temp[j];*/

	//get hostname
	gethostname(system_name,(size_t)sizeof(system_name));

	//get the current working directory
	t = getcwd(buf2,1000);
	t[(int)strlen(t)+1]='\0';

	if ((int)strlen(home)<=(int)strlen(t))
	{
		tilda(t,cwd);
		printf("<%s@%s:%s> ",user,system_name,cwd);
	}
	else
		printf("<%s@%s:%s> ",user,system_name,t);
}