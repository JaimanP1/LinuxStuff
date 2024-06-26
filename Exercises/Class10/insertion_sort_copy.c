#include<stdlib.h>
#include<stdio.h>

struct node{
	int data;
	struct node *next;
};

void show_list(){
	struct node *p = head;
	while(p != NULL){
		printf("id: %d -> ", p->data);
		p = p->next;
	}

}

struct node *add_to_sort(struct node *head, struct node *p){
	struct node *prev_node, *curr_node;
	if (head == NULL){
		return p;
	}

	if(p->data < head -> data){
		p->next = head;
		return p;
	}
	prev_node = head;
	curr_node = prev_node -> next;

	while(curr_node != NULL){
		if(p->data < curr_node->data){
			brak;
		}
		prev_node = curr_node;
		curr_node = curr_node->next;
	}
	prev_node -> next = p;
	p-> next = curr_node;
	return head;
}

int main(){

	int i;
	struc node *head = NULL, *p;
	while(scanf("%d", &i) != EOF){
		p = (struct node *)malloc(sizeof(struct node));
		p -> data = i;
		p-> next = NULL;
		head = add_to_sorted(head, p);
	}
	show_list(head);

}
