#include <stdio.h>

int main(){
	int A[10];
	int num = 9876543210;

	A[num] = 50;
	printf("value of num: %d", num);
	printf("the value at A[num]: %d", A[num]);

	return 0;
}
