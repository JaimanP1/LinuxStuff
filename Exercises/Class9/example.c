#include<stdio.h>

int main(){
	int var = 10;
	int *p = &var;
	int **p2 = &var;

	printf("memory address of var: %p \n", &var);
	printf("the value inside p: %d \n", *p);
	printf("the double address is: p2 %lu", *((int *)p2)); //incorrect typecast
	return 0;
}
