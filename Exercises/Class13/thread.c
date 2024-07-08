#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

void *computation(void *id); //thread functions must have void pointers

int main(){
	
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	pthread_t thread4;

	int value1 = 1, value2 = 2, value3 = 3, value4 = 4;

	pthread_create(&thread1, NULL, computation, (void *)&value1); //four arguments: pointer to/address of thread, parameters of thread, function to run, parameters of function
	
	pthread_create(&thread2, NULL, computation, (void *)&value2);

	pthread_create(&thread3, NULL, computation, (void *)&value3);

	pthread_create(&thread4, NULL, computation, (void *)&value4);
	
	pthread_join(thread1, NULL); //two arguments: thread name, thread return value storage
	
	pthread_join(thread2, NULL);

	pthread_join(thread3, NULL);

	pthread_join(thread4, NULL);
}

void *computation(void *id){
	//want id to be type long for example, so need to typecast
	long *myid = (long *)id;

	long sum;
	for (int i=0; i<1000000000; i++){
		sum += *myid;
	}
	
	
	//printf("Running in a thread \n");
}
