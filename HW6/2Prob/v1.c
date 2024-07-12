#include<stdlib.h>
#include<stdio.h>

struct node {
	int value;
	struct node *next;
	
};

void swap( struct node *pnode, struct node *pnode2 ){
	
	struct node *temp = pnode2;
	pnode2 -> next -> next = temp;
	pnode2 -> next = temp -> next -> next; 
	pnode2 = temp -> next;
	pnode -> next = pnode2;

}

int main(int argc, char **argv){
	struct node *head = NULL, *tail = NULL, *new = NULL;

	printf("Enter a value: ");
	int input;

	while( scanf("%d", &input) != EOF){
		
		if(head == NULL){
			
			head = (struct node *)malloc(sizeof(struct node));
			new = (struct node *)malloc(sizeof(struct node));
			head -> next = new;
			head -> value = input;
		}

		else{
			
			new -> value = input;
			tail = (struct node *)malloc(sizeof(struct node));
			new -> next = tail;
			tail = NULL;
			new = new -> next;
		}

		printf("Enter a value: ");
	}
	
	struct node *pnode;
	pnode = head;
	int i = 0;
	printf("\nOriginal list: \n");

	while(pnode -> next != NULL){
		
		printf("\nindex: %d, value: %d \n", i, pnode -> value);
		pnode = pnode -> next;
		i++;
	}

	//bubble sort part
	pnode = head;
	struct node *pnode2;

	while( pnode -> next -> next != NULL ){
		pnode2 = head;

		while( pnode2 -> next -> next != NULL ){
			
			if ( pnode -> next -> value > pnode2 -> next -> value ){
			
				swap( pnode, pnode2 );
			}	
			
			pnode2 = pnode2 -> next;
		}

		pnode = pnode -> next;
	}

	//edge case for head node and tail nodes
	
	
	//printing result
	pnode = head;
	i = 0;

	while ( pnode -> next != NULL ){
		
		printf("index: %d, value: %d", i, pnode -> value);
	}
}
