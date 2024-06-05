#include <stdio.h>

int main(){
	int num, j;
	printf("Enter a number: ");
	scanf("%d", &num);

	for (int i=1; i <= num; i++){
		j = j*i;
	}

	printf("The factorial is: %d", j);
}

