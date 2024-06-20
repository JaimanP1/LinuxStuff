#include <stdio.h>
#include <stdlib.h>

// Function to read matrix dimension from a binary file
int readMatrixDimension(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    int dim;
    fread(&dim, sizeof(int), 1, file); // Read the dimension from file

    fclose(file);

    if (dim > 100) {
        printf("Matrix dimension from file '%s' is too large (%d). Maximum allowed is 100.\n", filename, dim);
        exit(1);
    }

    return dim;
}

int main() {
    int dim1, dim2;

    // Read dimensions from files
    dim1 = readMatrixDimension("matrix1.bin");
    dim2 = readMatrixDimension("matrix2.bin");

    // Compare dimensions
    if (dim1 != dim2) {
        printf("Matrix dimensions do not match\n");
        exit(1);
    }

    printf("Matrix dimensions match: %d\n", dim1);

    return 0;
}

