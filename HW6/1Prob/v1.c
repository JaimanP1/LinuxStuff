#include<stdlib.h>
#include<stdio.h>

struct node {
	int value;
	struct node *next;
};

int main( int argc, char **argv){
	
	struct node *head = NULL, *tail = NULL, *new_node;
	
	int input;
	
	printf("Enter value of node: ");
	while ( scanf( "%d", &input) != EOF){
		
		if (head == NULL){
			//need to create the list from scratch: node's position is head and tail is new->next
                        head = (struct node *)malloc(sizeof(struct node)); //to exist beyond scope of loop
                        head->next = tail; //tail is reassigned to head's link, now end of list
			new_node = tail; //both pointing to the same spot
			head->value = input; //basically *head = input
		}

		else {
			tail = (struct node *)malloc(sizeof(struct node)); 
			new_node->next = tail; 
			new_node->value = input; //basically *new_node = input
			new_node = tail;
		}

		printf("Enter value of node: ");
	}
	
	struct node *pnode = head;
	int i = 0;
	while(pnode != NULL){
		printf("index: %d, value: %d \n", i, pnode->value);
		pnode = pnode->next;
		i++;
	}

}
