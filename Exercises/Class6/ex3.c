#include<stdio.h>

int main(){
	unsigned int x = 10;
	unsigned int y = 5;
	printf("%d", x&y);
	printf("\n");
	printf("%d", x>>0x10);
	printf("\n");
}
