#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	int data;
	struct node *next; //need to dynamically allocate memory on demand
	char name[20];
};

int main(){
	struct node *head = NULL; *tail = NULL, *pnode;
	while(1){
		pnode = (struct *)malloc(sizeof(struct node));
		printf("Enter data");
		scanf("%d", &(pnode -> data)); //why do we need location (&)
		if (pnode -> data < 0){
			break;
		}
		printf("Enter Name: ");
		scanf("%s", pnode -> name);
		pnode = pnode -> next;
		if(head == NULL){
                	head = pnode;
        	}                                                                                                                                    if(tail != NULL){
                	tail -> next = pnode;
        	}
		tail = pnode;
	
	}
	pnode = pnode -> next;
	
	while(pnode != NULL){
		printf("%d %s", pnode -> data, pnode -> name);
		ponode = pnode -> next;
	}	
}
