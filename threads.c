#include<stdio.h>
#include<errno.h>
#include<pthread.h>
#include<stdlib.h>


struct argumente
{
 int **m1;
 int **m2;
 int linie;
 int coloana;
 int p;
};

int **A;
int **B;
int **C;

void* suma(void* v)
{
 struct argumente *arg;
 arg=(struct argumente *)v;
 C[arg->linie][arg->coloana]=0; 
 //printf("%d",arg->p);
 for(int k=0;k<arg->p;k++)
 {
 C[arg->linie][arg->coloana]+=A[arg->linie][k]*B[k][arg->coloana];
 }
 //printf("%d %d %d",arg->linie,arg->coloana,C[arg->linie][arg->coloana]);
 return NULL;
}

int main(int argc,char* argv[])
{
 int m,p,n;
 printf("Introduceti dimensiunile :\n");
 scanf("%d", &m);
 scanf("%d", &p);
 scanf("%d", &n);
 
 A=(int**)malloc(m*sizeof(int*));
 for(int i=0;i<m;i++)
 {
 A[i]=(int*)malloc(p*sizeof(int));
 }
 B=(int**)malloc(p*sizeof(int*));
 for(int i=0;i<p;i++)
 {
 B[i]=(int*)malloc(n*sizeof(int*));
 }
 C=(int**)malloc(m*sizeof(int*));
 for(int i=0;i<m;i++)
 {
 C[i]=(int*)malloc(n*sizeof(int*));
 }

 for(int i=0;i<m;i++)
  for(int j=0;j<p;j++)
    scanf("%d",&A[i][j]);

 for(int i=0;i<p;i++)
  for(int j=0;j<n;j++)
   scanf("%d",&B[i][j]);

 pthread_t *threads=(pthread_t *)malloc(m*n*sizeof(pthread_t));
 struct argumente *arg=(struct argumente*)malloc(m*n*sizeof(struct argumente));
 for(int i=0;i<m;i++)
 for(int j=0;j<n;j++)
{arg[i*n+j].p=p;
 arg[i*n+j].linie=i;
 arg[i*n+j].coloana=j;
 if(pthread_create(&threads[i*n+j],NULL,suma,&arg[i*n+j]))
 {
 perror(NULL);
 return 1;
 }
}
 for(int i=0;i<m;i++)
  for(int j=0;j<n;j++)
   if(pthread_join(threads[i*n+j],NULL))
     {
     perror(NULL);
     return errno;
     }
 for(int i=0;i<m;i++)
 { for(int j=0;j<n;j++)
 { 
 printf("%d ",C[i][j]);
 }
 printf("\n");
 }
 free(threads);
 return 1;
}


