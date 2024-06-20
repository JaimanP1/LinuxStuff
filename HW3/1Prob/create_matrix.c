#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(){
	FILE *f;
	int dim, element;
	char filename[256];
	printf("Provide a filename.\n");
	scanf("%s", filename); //no ampersand sign before filename bc its array
	f = fopen(filename, "wb");
	if(f == NULL){
		printf("FILE DIDNT OPEN");
	}
	printf("Provide a size 'n' for the 3D array.\n");
	scanf("%d", &dim);
	printf("dim = %d\n", dim);
	fwrite(&dim, sizeof(dim), 1, f); //what we're writing?, the size of items, amt of items, the file. use man fwrite
	srandom(time(NULL)); // Seed the random number generator with the current time
	for(int i =0; i < dim * dim * dim; i++){
		element = random();
		printf("element %d: %d \n", i, element);
		fwrite(&element,sizeof(element), 1, f);
	}
	fclose(f);
	return 0;
}

