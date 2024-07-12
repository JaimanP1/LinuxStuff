#include<stdlib.h>
#include<stdio.h>

struct node {
	int value;
	struct node *next;
	
};

struct node * swap( struct node *pnode, struct node *pnode2 ){
	
	//struct node **temp = &pnode2;
	//pnode2 -> next -> next = *temp;
	//pnode2 -> next = (*temp) -> next -> next; 
	//pnode2 = (*temp) -> next;
	//pnode -> next = pnode2;

	//struct node *temp = pnode2;
	//temp = pnode->next;
        //pnode->next = pnode2->next;
        //pnode2->next = temp;

        //temp = pnode->next->next;
        //pnode->next->next = pnode2->next->next;
        //pnode2->next->next = temp;
	

//	pnode -> next = pnode2 -> next;
//	pnode2 -> next = pnode -> next -> next;
//	pnode2 = pnode -> next;


	struct node* tmp = pnode2 -> next;
	pnode2 -> next = pnode;
	pnode -> next = tmp;
	return pnode2;
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
	struct node **p1;
	for (int j = 0; j < i; j++ ){

		p1 = &head;
		
		for( int k = 0; k < i; k++ ){

			struct node *node1 = *p1;
			struct node *node2 = node1 -> next;
			
			if( node2 == NULL ){
				break;
			}

			if( node1 -> value > node2 -> value ){

				*p1 = swap( node1, node2 );
			}

			p1 = &(*p1) -> next;
		}
	}

	//original
//	pnode = head;
//	struct node **pnode2;

//	while( pnode -> next -> next != NULL ){
//		pnode2 = head;

//		while( pnode2 -> next -> next != NULL ){
			
//			if ( pnode -> next -> value > pnode2 -> next -> value ){
			
//				swap( pnode, pnode2 );
//			}	
			
//			pnode2 = pnode2 -> next;
//		}

//		pnode = pnode -> next;
//	}

	//edge cases for head and tail?
	
	
	//printing result
	pnode = head;
	i = 0;

	while ( pnode -> next != NULL ){
		
		printf("index: %d, value: %d", i, pnode -> value);
		pnode = pnode -> next;
		i++;
	}
}
