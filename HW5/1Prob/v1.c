#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main (int argc, char **argv){
	
	//typecasting array 
	char **p = argv;
	
	printf("\nformat:\narray | first element | address of pointer\n");
	printf("argv | %p | %p\n", (void*)p ,(void *)&p);
	//need way to represent this in the 8 byte format

	printf("\n\ncount: %d\n\n", argc);
	printf("format:\nargv[i] |     value      |     pointer    | value's value's first element \n");
	
	for(int i = 0; i < argc; i++){
		//printing the index, address it points to, address of itself	
		printf("argv[%d] | %p | %p | %c\n", i, (void*)*(p + i), (void*)(p + i), **(p + i)); 	
	}

	//contigous memory portion
	int m = strlen(argv[argc -1]); //trying to find length of last argument
	//printf("\nlast argument: %s, size of last argument: %d\n", argv[argc -1], m);
	int n = *(p + argc - 1) - *p;
	printf("\nnumber of bytes of array: %d\n", n + m);

	//printing values in groups of 8
	unsigned long start = (unsigned long)(*p);
	unsigned long offset = start % 8;
	start -= offset;	
	printf("\nAligned addresses, starting at %p: \n", *p);
	
	for(unsigned long i = 0; i < m + n || (start + i) % 8 != 0; i++){
		char *address = (char *)(start + i);
		char val = *address;

		printf("%02x (%c)", val, val);

		if( (i + 1) % 8 == 0){
			printf("\n");
		}

	}
	return 0;
}
