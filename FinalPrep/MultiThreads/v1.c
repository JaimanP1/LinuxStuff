#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void* calculate(void* i){

	//calculate pi
	int *index = (int *)i;
	printf("calculate pi in parallel, id: %d \n", *index);
}

int main (int argc, char **argv){
	printf("serial part, enter number of processes: \n");
	pthread_t thread_id;
	int d;
	scanf("%d", &d);
	for(int i = 0; i < d; i++){
		pthread_create(&thread_id, NULL, calculate, &i);
	}
	pthread_join(thread_id, NULL);
	printf("end, serial\n");
	return 0;

}
