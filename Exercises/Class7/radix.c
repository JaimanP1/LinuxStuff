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


void radix_sort_signed(int A[], int n){
	int positive[MAX], negative[MAX];
	int pos_count = 0, neg_count = 0;
	for(int i=0, i<n; i++){
		if(A[i]>=0){
			positive[pos_count++] = A[i];
		}
		else{
			negative[neg_count++] = ~A[i]; //ones complement to use unsigned radix sort
		}
	}
	radix_sort(positive, pos_count);
        radix_sort(negative, neg_count);
	
//join buckets
	for(int i=neg_count - 1; i>=0; i--){
		A[neg_count -1 -i] = ~negative[i]; //negating for original order
	}	
	for(int i=0; i<pos_count; i++){
		A[neg_count + i] = positive[i];
	}
}

int main(){
	//unsigned int A[] = {7,1,3,2,0,9,8,4,7,3,5};
	//unsigned int n = sizeof(a) / sizeof(A[0]);
	/*
	printf("Before sorting \n");
	for(int i=0; i<n; i++){
		printf("%d", A[i]);
	}
	printf("After sorting \n");
	radix_sort(A, n);
	for(int i=0; i<n; i++){
		printf("%d", A[i]);
	}
	*/

	int A[] = {-1, -5, 10, 8, 4, 0, -3, -2};
	int n = sizeof(A) / sizeof(A[0]);
	printf("before sorting: \n");
	for(int i=0; i<n; i++){
		printf("%d", A[i]);
	}
	radix_sort_signed(A, n);
	printf("after sorting: \n");
	for(int i=0; i<n; i++){
		printf("%d", A[i]);
	}
}
