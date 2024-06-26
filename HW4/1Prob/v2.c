#include <stdio.h>
#include <stdlib.h>

void radix_sort(unsigned int A[], unsigned int n) {
    unsigned int bucket0[100], bucket1[100];
    unsigned int mask, count0, count1;

    for (int d = 0; d <= 31; d++) {
        mask = 1 << d;
        count0 = 0;
        count1 = 0;
        for (int i = 0; i < n; i++) {
            if ((A[i] & mask) == 0) {
                bucket0[count0++] = A[i];
            } else {
                bucket1[count1++] = A[i];
            }
        }
        for (int i = 0; i < count0; i++) {
            A[i] = bucket0[i];
        }
        for (int i = 0; i < count1; i++) {
            A[count0 + i] = bucket1[i];
        }
    }
}

int main() {
    unsigned int n;
    scanf("%u", &n);  // Read the number of elements

    unsigned int *A = (unsigned int *)malloc(n * sizeof(unsigned int));
    if (A == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (unsigned int i = 0; i < n; i++) {
        scanf("%u", &A[i]);  // Read the elements
    }

    radix_sort(A, n);

    for (unsigned int i = 0; i < n; i++) {
        printf("%u\n", A[i]);  // Print the sorted elements
    }

    free(A);
    return 0;
}

