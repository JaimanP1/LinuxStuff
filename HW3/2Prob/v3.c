#include<stdlib.h>
#include<stdio.h>
#include <dirent.h> 
#include <string.h>

void lines(int *num, char *path){
	
	//opening file
	FILE* fptr;
	fptr = fopen(path, "r");
	if (fptr == NULL) {
       		printf("The file is not opened");
        	exit(0);
    	}
	//else{
		//printf("File has been opened");
		//printf("\n");
	//}

	//Counting lines
	char c;
	for (c = getc(fptr); c != EOF; c = getc(fptr)){
		if (c == '\n'){
			(*num)++;
		}
	}

	//Close file
	fclose(fptr);
}

int traverse(char *path, int *num) 
{ 
    struct dirent *de;  
    DIR *dr = opendir(path); 
	char placeholder[1000];
  
    if (dr == NULL)   
    { 
        printf("Directory could not be opened" ); 
        return 0; 
    } 
  
    while ((de = readdir(dr)) != NULL) {
		
		if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
        {
            //printf("%s\n", de->d_name);

            // making new path name
            strcpy(placeholder, path);
            strcat(placeholder, "/");
            strcat(placeholder, de->d_name);

			if (de->d_type == DT_DIR) {
                // Recur for subdirectories
                traverse(placeholder, num);
			}
			else if (de->d_type == DT_REG){
				char *ext = strrchr(de->d_name, '.');
                if (ext && strcmp(ext, ".txt") == 0) {
                    lines(num, placeholder);
				}
			}

        }

	}
             
    closedir(dr);     
    return 0; 
} 

int main() {
	
	//Reading an input
	char path[1000];
	printf("Enter a path: ");
	scanf("%s", path);
	printf("%s", path);
	printf("\n");

	//calling function
	int num = 0;
	traverse(path, &num);

	printf("The file has %s has %d lines \n", path, num);

	return 0;
}
