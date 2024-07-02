#include<stdio.h>
int main(){
	int a[4] = {1, 2, 3, 4};
	for(int i; i < 4; i++){
		printf("%d", a[i]);
	}
	printf("\n");
	a[3] = 6;
	for(int i; i < 4; i++){
		printf("%d", a[i]);
	}
	printf("\n");
	3[a] = 9;
	for(int i; i < 4; i++){
		printf("%d", a[i]);
	}
	printf("\n");
}
