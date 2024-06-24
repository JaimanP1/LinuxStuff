#include<stdio.h>
#include<stdlib.h>

int main(){
	
	//int arr[5];
	//for (int i = 0; i< 5; i++){
	//	arr[i] = i+1;
	//}
	//for (int i=0; i<5; i++){
	//	printf("%d, ", arr[i]);
	//}

	int *arr[5];
	for (int i =0; i<5; i++){
		arr[i] = (int*)malloc(sizeof(int));
		*arr[i] = i+1; //or **(arr+i) = i+1
	}

	for (int i=0; i<5; i++){
		printf("%d \n", *arr[i]);
	}
}
