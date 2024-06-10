#include <stdio.h>
#include <stdlib.h>

int main(){
   int array[3][2][2], value=0, i, j, k;
   int *p=(int *)array;

   for( i = 0; i < 3; i++) {
      for ( j = 0; j < 2; j++){
         for ( k = 0; k < 2; k++) {
            array[i][j][k] = value;
            value = value + 1;
         }
      }
   }
   for( i = 0; i < 12; i++)
      printf("%d ", p[i]);
   printf("\n");
   printf("Examine memory now.\n");
}

