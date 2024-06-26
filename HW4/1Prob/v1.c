#include<stdio.h>

void radix_sort(unsigned int A[], unsigned int n){
	unsigned int bucket0[100], bucket1[100];
	unsigned int mask, count0, count1;

	for(int d = 0; d <= 31; d++){
		mask = 1 << d;
		count0 = 0;
		count1 = 0;
		for(int i = 0; i < n; i++){
			if((A[i] & mask) == 0){
				bucket0[count0++] = A[i];
			}
			else{
				bucket1[count1++] = A[i];
			}
		}
	for(int i = 0; i < count0; i++){
                A[i] = bucket0[i];                                                                                                           }
        for(int i = 0; i < count1; i++){
                A[count0 + i] = bucket1[i];
        }
	}
}

int main(){
	int A[] = {1, 5, 10, 8, 4, 0, 3, 2};
	int n = sizeof(A) / sizeof(A[0]);
	//printf("before sorting: \n");
	//for(int i=0; i<n; i++){
	//	printf("%d, ", A[i]);
	//}
	//printf("\n");
	radix_sort(A, n);
	//printf("after sorting: \n");
	for(int i=0; i<n; i++){
		printf("%d done \n ", A[i]);
	}
	//printf("\n");
}
