#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/mman.h>

int main(int argc, char* argv[])
{
   char shm_name[]="myshm";
   int shm_fd;
   shm_fd=shm_open(shm_name, O_CREAT|O_RDWR|O_TRUNC, S_IRUSR|S_IWUSR);
   if(shm_fd<0)
   {
   perror(NULL);
   return errno;
   }
   size_t shm_size=(argc-1)*getpagesize();
   if(ftruncate(shm_fd,shm_size)==-1)
   {
   perror(NULL);
   shm_unlink(shm_name);
   return errno;
   }

   int *shm_int=(int*)mmap(0,shm_size, PROT_READ, MAP_SHARED, shm_fd,0);
   if(shm_int==MAP_FAILED)
   {
   perror(NULL);
   shm_unlink(shm_name);
   return errno;
   }
   int n;
   for(int i=1;i<argc;i++)
   { n=atoi(argv[i]);  
    pid_t process_id=fork();
    int j=1;
   if(process_id<0)
     perror(NULL);
   else if(process_id==0)
   {
    int* shm2_int=(int*)mmap(0,getpagesize(),PROT_WRITE, MAP_SHARED, shm_fd, (i-1)*getpagesize());
   if(shm2_int==MAP_FAILED)
   {
   perror(NULL);
   exit(0);
   }
    shm2_int[0]=n;
    while(n!=1)
    {
    if(n%2==0)
      {
      shm2_int[j]=n/2;
      n=n/2;
      }
    else
      {
      shm2_int[j]=3*n+1;
      n=3*n+1;
      }
    j++;
     }
   munmap(shm2_int, getpagesize());   
   exit(0);
    }
   }

for(int i=1;i<argc;i++)
wait(NULL);


int nr_intreg=getpagesize()/sizeof(int);
for(int i=1;i<argc;i++)
{
 int *v=shm_int+(i-1)*nr_intreg;
 printf("%d \n ",*v);
 v++;
 while(*v!=1)
 {
 printf("%d ",v[0]);
 v++;
 }
 printf("%d \n",v[0]);
}

munmap(shm_int,shm_size);
shm_unlink(shm_name);

printf("Parinte a terminat");
return 0;
}
