#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void swap(char **val1, char **val2){
        char temp = **val1;
        **val1 = **val2;
        **val2 = temp;
}

void bubble_sort(char **envp, const int index){
	for(int i = 0; i < index - 1; i++){
		for(int j = 0; j < index - 1; j++){
			char *val1 = strtok(envp[j], "=");
			char *val2 = strtok(envp[j + 1], "=");
			if(strcmp(val1, val2) > 0){
				swap( &envp[j], &envp[j + 1]);
			}
			*(val1 + strlen(val1)) = '=';
			*(val2 + strlen(val2)) = '=';
		}
	}
}

int main(int argc, char **argv, char **envp){
	int index = 0;
	while(envp[index]){
		printf("%s\n", envp[index]);
		index++;
	}	

	bubble_sort(envp, index);

	printf("\nSorted variables: \n");

	for(int i = 0; i < index; i++){
		printf("%s\n", envp[i]);
	}

	return 0;
}
