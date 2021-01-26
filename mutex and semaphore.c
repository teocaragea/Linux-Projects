#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#define NR_THREADS 10

pthread_mutex_t mtx;// mutex

sem_t sem;// semafoareee

int value = 0;



void barrier_point()/// aici e bariera

{

        pthread_mutex_lock(&mtx);
        value++;
        pthread_mutex_unlock(&mtx);

        if (value == NR_THREADS)

                sem_post(&sem);

        else

        {

		sem_wait(&sem);
		sem_post(&sem);

        }

}




void* tfun(void* v)

{

	int *tid = (int *)v;
	printf("%d a ajuns la bariera\n", *tid);
	barrier_point();// aici e bariera
	printf("%d a plecat de la bariera \n", *tid);
	free(tid);
	return NULL;

}



int main()

{

	int i = 0;
	int *current;
	pthread_mutex_init(&mtx, NULL);
	sem_init(&sem, 0, 0);// initializez semafoare
	pthread_t threads[NR_THREADS];


	while (i < NR_THREADS)
	{
		current = malloc(sizeof(int));
		*current = i;
		pthread_create(&threads[i], NULL, tfun, current);// creez threaduri ce apeleaza tfun, adica void ul bariere
		i++;

	}


	i = 0;

	while (i < NR_THREADS)

	{

		pthread_join(threads[i], NULL);//distrugem threaduri

		i++;

	}


	return 0;

}
