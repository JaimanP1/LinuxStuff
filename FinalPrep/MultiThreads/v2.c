#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int count = 0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void * calculate(void *i){
	int *index = (int *)i;
	//printf("index is: %d \n", *index+1);

	pthread_mutex_lock( &mutex1 );
	if(count>=2){
		printf("Cannot increment beyond 2 \n");
	}	
	else{
		count++;
	}
	pthread_mutex_unlock( &mutex1 );

	printf("count: %d \n", count);
}

int main(int argc, char **argv){
	int num_threads;
	printf("number of threads: \n");
	scanf("%d", &num_threads);
	pthread_t *thread_array;
	int *ids;
	thread_array = (pthread_t *)malloc(sizeof(pthread_t) * num_threads);
	ids = (int *)malloc(sizeof(int) * num_threads);
	for(int i = 0; i < num_threads; i++){
		ids[i] = i;
		pthread_create(&thread_array[i], NULL, calculate, &ids[i]);
	}
	for(int i = 0; i < num_threads; i++){
		pthread_join(thread_array[i], NULL);
	}
}
