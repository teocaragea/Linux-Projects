#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
   int n;
   for(int i=1;i<argc;i++)
   { n=atoi(argv[i]);
   // printf("%d n: ",n);   
 pid_t process_id=fork();
   
   
   if(process_id<0)
     perror(NULL);
   else if(process_id==0)
   {
   while(n!=1)
   {
    if(n%2==0)
      {
      printf("%d ",n/2);
      n=n/2;
      }
    else
      {
      printf("%d ",3*n+1);
      n=3*n+1;
      }
   }
      
   printf("Copil %d Parinte %d \n",getpid(),getppid());
   exit(0);
   }
   }

for(int i=1;i<argc;i++)
wait(NULL);
printf("Parinte a terminat");
return 0;
}
