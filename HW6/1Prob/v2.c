#include<stdlib.h>
#include<stdio.h>

struct node {
	int value;
	struct node *next;
};

struct reverse_node {
	int value;
	struct reverse_node *previous;
};

int main (int argc, char **argv){
	
	struct node *head = NULL, *tail = NULL, *new = NULL;
	struct reverse_node *rhead = NULL, *rtail = NULL, *rnew = NULL;

	printf("Enter a value: ");
	int input;

	while( scanf("%d", &input) != EOF){
		
		if(head == NULL){
			
			head = (struct node *)malloc(sizeof(struct node));
			new = (struct node *)malloc(sizeof(struct node));
			head->next = new;
			head->value = input;
		}

		else {
			
			new->value = input;
			tail = (struct node *)malloc(sizeof(struct node));
			new->next = tail;
			tail = NULL;
			new = new->next;
		}

		printf("Enter a value: ");
	}

	struct node *pnode;
	pnode = head;
	int i = 0;
	while (pnode->next != NULL){
		
		printf("\nindex: %d, value: %d \n", i, pnode->value);
		
		//reversing the list
		if(rhead == NULL){
			rhead = (struct reverse_node *)malloc(sizeof(struct reverse_node));
			rhead->previous = NULL;
			rhead->value = pnode->value;
			rnew = (struct reverse_node *)malloc(sizeof(struct reverse_node));
			rnew->previous = rhead;
		}
		
		else{
			rnew->value = pnode->value;
			rtail = (struct reverse_node *)malloc(sizeof(struct reverse_node));
			rtail->previous = rnew;
			rnew = rtail;
		}
		
		pnode = pnode->next;
		i++;
	}

	printf("\nReversing list: \n");
	
	struct reverse_node *rpnode = rnew->previous;
	i--;
	while(rpnode != NULL){
		printf("\nindex: %d, value: %d \n", i--, rpnode->value);
		rpnode = rpnode->previous;
	}
}
