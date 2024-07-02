#include<stdio.h>
#include<string.h>

struct tag{
	char lname[20];
	char fname[20];
	int age;
	float rate;
};

struct tag my_struct;

int main (void){
	strcpy(my_struct.lname, "Jensen");
	strcpy(my_struct.fname, "Ted");
	printf("\n%s", my_struct.fname);
	printf("\n%s", my_struct.lname);
	return 0;
}
