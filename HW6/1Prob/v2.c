#include<stdlib.h>
#include<stdio.h>

struct node {
	int value;
	struct node *next;
};

int main (int argc, char **argv){
	
	struct node *head = NULL, *tail = NULL, *new = NULL;

	printf("Enter a value: ");
	int input;
	scanf("%d", &input);

	while(input != EOF){
		
		if(head == NULL){
			
			head = (struct node *)malloc(sizeof(struct node));
			new = (struct node *)malloc(sizeof(struct node));
			head->next = new;
			head->value = input;
			//new->value = NULL;
		}

		else {
			
			new->value = input;
			tail = (struct node *)malloc(sizeof(struct node));
			new->next = tail;
			tail = NULL;
			new = *(new->next);
		}

		printf("Enter a value: ");
		scanf("%d", &input);
	}

	struct node *pnode;
	pnode = head;
	int i = 0;
	while (pnode != NULL){
		
		printf("index: %d, value: %d", i, pnode->value);
	}
}
