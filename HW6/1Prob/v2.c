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

	while( scanf("%d", &input) != EOF){
		
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
			//new = (struct node *)*(new->next);
			new = new->next;
		}

		printf("Enter a value: ");
	}

	struct node *pnode;
	pnode = head;
	int i = 0;
	while (pnode->next != NULL){
		
		printf("\nindex: %d, value: %d \n", i, pnode->value);
		pnode = pnode->next;
		i++;
	}
}
