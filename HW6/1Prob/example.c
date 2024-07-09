#include <stdio.h>
#include <stdlib.h>
struct node{
  int id;
  char name[20];
  struct node *next;
};

int main(){
  struct node *head=NULL, *tail=NULL, *pnode;
  while(1){
    pnode=(struct node *)malloc(sizeof(struct node));
    printf("id:"); scanf("%d", &(pnode->id));
    if(pnode->id<0) break;
    printf("name:"); scanf("%s", pnode->name);
    pnode->next=NULL; /*ensure next pointer of last node is NULL */
    if(head==NULL) head=pnode;
    if(tail!=NULL) tail->next=pnode;
    tail=pnode;
  }
}
