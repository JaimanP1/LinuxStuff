#include<stdio.h>
#define MAX 100

void radix_sort(unsigned int A[], unsigned int ){
	unsigned int bucket0[MAX], bucket1[MAX];
	unsigned int mask; count0; count1;
	for(int d=0; d<=31; d++){
		mask = 1 << d; 
		count0 = 0;
		count1 = 0;
		for(int i=0; i<n; i++){
			if(A[i]&mask == 0){
				bucket0[count0++] = A[i];
			}
			else{
				bucket1[count1++] = A[i];
			}
		}
	//joining buckets
	for(int i=0; i<count0; i++){
		A[i] = bucket0[i];
	}
	for(int i=0; i<count1; i++){
		A[count0 + i] = bucket1[i];
	}
	}
}

int main(){
	unsigned int A[] = {7,1,3,2,0,9,8,4,7,3,5};
	unsigned int n = sizeof(a) / sizeof(A[0]);
	printf("Before sorting \n");
	for(int i=0; i<n; i++){
		printf("%d", A[i]);
	}
	printf("After sorting \n");
	radix_sort(A, n);
	for(int i=0; i<n; i++){
		printf("%d", A[i]);
	}
}
