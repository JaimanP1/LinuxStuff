#include <stdlib.h>
#include<stdio.h>
int main(){
	int i;
	float value, f[20];
	/* typecasting using a pointer */
	unsigned int *p = (unsigned int *) f;
	value = -10.5;
	for( i = 0; i < 20; i++) {
		f[i] = value;
		value = value + 1;
	} /* f has 20 float point numbers in ascending order */
	for( i = 0; i < 20; i++){
		printf("%.2f\t%u\t%u\n", f[i], p[i], (p[i]&0xFFFF0000)>>16);
	/* show the float point numbers (column 1) and the corresponding
	* unsigned int values (column 2). Bit-wise operations are used to
	* obtain the last column, showing that bit-wise operations can be
	* used after typecasting float point numbers to unsigned integers.
	*/
	}
}
