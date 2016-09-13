#include <stdio.h>
#include <string.h>
int main()
{

   FILE *fp,*exe;
   char buff[100],buf[100];
   int values[4]={0,1,4,12},i=0,k=0;
   char addr[30] = "/proc/10421";
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
   char adr[30] = "/proc/10421";
   strcat(adr,"/exe");
   strcat(path,adr);
   exe = popen(path,"r");
   while (fgets(buf,sizeof(buf),exe)!=NULL)
   {
      printf("%s",buf);
   }
   return 0;
}