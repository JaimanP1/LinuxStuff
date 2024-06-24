#include<stdlib.h>
#include <stdio.h>
int main () {
  int** arr=(int **)malloc(5*sizeof(int *));
  for(int i=0; i<5; i++) {
    arr[i] = (int*)malloc(sizeof(int));
    *arr[i] = i;
  }
  return 0;
}

