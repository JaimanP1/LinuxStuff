#include<stdio.h>
#include<string.h>

struct tag{
	char lname[20];
	char fname[20];
	int age;
	float rate;
};

struct tag my_struct;
void show_name(struct tag *p);

int main(void){
	struct tag *st_ptr;
	st_ptr = &my_struct;
	strcpy(my_struct.lname, "Jensen");
	strcpy(my_struct.fname, "Ted");
	printf("\n%s", my_struct.fname);
	printf("\n%s", my_struct.lname);
	my_struct.age = 63;
	show_name(st_ptr);
	return 0;
}

void show_name(struct tag *p){
	printf("\n%s", p->fname);
	printf("\n%s", p->lname);
	printf("\n%d", p->age);
}
