#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct transaction{
	char name[20];
	int data;

}t1; *ptr = &t1;

//can also do:
//struct transation t1, *ptr = &t1
//or make the struct a typedef
//transaction t1, *ptr = &t1


int main(){
	strcpy(t1.name, "john");
	t1.data = 100;
	ptr -> data = 10;
	strcopy(ptr -> name, "jane");
	
	printf("%s %d", t1.name, t1.data);
	printf("%s %d", ptr-> name, ptr -> data);
}
