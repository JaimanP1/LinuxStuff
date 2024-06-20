#include <stdio.h>
#include <stdlib.h>

int Dimension(const char *filename, int *dim) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return 0;
    }

    fread(dim, sizeof(int), 1, file); 

    fclose(file);

    if (*dim > 100) {
        printf("Matrix dimension in file '%s' exceeds 100\n", filename);
        return 0;
    }

    return *dim;
}

int main() {
    int dim1, dim2;

    dim1 = Dimension("matrix1.bin", &dim1);
    dim2 = Dimension("matrix2.bin", &dim2);

    if (dim1 == 0 || dim2 == 0) {
        return 0; 
    }

    if (dim1 == dim2) {
        printf("Matrix dimensions match: %d\n", dim1);
    } else {
        printf("Matrix dimensions do not match\n");
    }

    return 0;
}
