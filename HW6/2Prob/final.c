#include <stdlib.h>
#include <stdio.h>

struct node {
    int value;
    struct node *next;
};

struct node *swap( struct node *pnode1, struct node *pnode2 ) {
    struct node *tmp = pnode2 -> next;
    pnode2 -> next = pnode1;
    pnode1 -> next = tmp;
    return pnode2;
}

int main() {
    struct node *head = NULL, *tail = NULL, *new = NULL;

    int input;

    while ( scanf("%d", &input ) != EOF) {
    
	    if ( head == NULL ) {
        
	    	head = (struct node *)malloc(sizeof(struct node));
                head -> value = input;
       	        head -> next = NULL;
                new = head;
	    }

	    else {
            	tail = (struct node *)malloc(sizeof(struct node));
            	tail -> value = input;
            	tail -> next = NULL;
            	new -> next = tail;
            	new = tail;
        }
    }

    struct node *pnode;
    pnode = head;
    int i = 0;

    while (pnode != NULL) {

        pnode = pnode -> next;
        i++;
    }

    // Bubble sort part
    struct node **p1;
    for (int j = 0; j < i; j++) {

        p1 = &head;

        for (int k = 0; k < i - 1; k++) {

            struct node *node1 = *p1;
            struct node *node2 = node1 -> next;

            if (node2 == NULL){
		    break;
	    }

            if (node1 -> value > node2 -> value) {

                *p1 = swap(node1, node2);
            }

            p1 = &(*p1) -> next;
        }
    }

    pnode = head;

    while (pnode != NULL) {

        printf("%d\n", pnode -> value);
        pnode = pnode -> next;
    }

    while (head != NULL) {

        struct node *temp = head;
        head = head -> next;
        free(temp);
    }

    return 0;
}

