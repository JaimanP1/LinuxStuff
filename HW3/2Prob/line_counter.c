#include<stdlib.h>
#include<stdio.h>

int main() {
	
	//Reading an input
	char path[1000];
	printf("Enter a path: ");
	scanf("%s", path);
	printf("%s", path);
	printf("\n");

	//Opening a file
	FILE* fptr;
	fptr = fopen(path, "r");
	if (fptr == NULL) {
       		printf("The file is not opened");
        	exit(0);
    	}
	else{
		printf("File has been opened");
		printf("\n");
	}

	//Counting lines
	int num = 0;
	char c;
	for (c = getc(fptr); c != EOF; c = getc(fptr)){
		if (c == '\n'){
			num++;
		}
	}

	//Close file
	fclose(fptr);
	printf("The file has %s has %d lines \n", path, num);

	return 0;
}
