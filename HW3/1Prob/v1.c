#include <stdio.h>
#include <stdlib.h>

// Function to read a 3D matrix from a binary file
int*** readMatrix(const char *filename, int *dim) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    fread(dim, sizeof(int), 1, file);

    if (*dim > 100) {
        printf("Matrix dimension too large\n");
        fclose(file);
        exit(1);
    }

    int ***matrix = (int***)malloc(*dim * sizeof(int**));
    for (int i = 0; i < *dim; ++i) {
        matrix[i] = (int**)malloc(*dim * sizeof(int*));
        for (int j = 0; j < *dim; ++j) {
            matrix[i][j] = (int*)malloc(*dim * sizeof(int));
        }
    }

    for (int i = 0; i < *dim; ++i) {
        for (int j = 0; j < *dim; ++j) {
            for (int k = 0; k < *dim; ++k) {
                fread(&matrix[i][j][k], sizeof(int), 1, file);
            }
        }
    }

    fclose(file);
    return matrix;
}

// Function to write a 3D matrix to a binary file
void writeMatrix(const char *filename, int ***matrix, int dim) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    fwrite(&dim, sizeof(int), 1, file);

    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            for (int k = 0; k < dim; ++k) {
                fwrite(&matrix[i][j][k], sizeof(int), 1, file);
            }
        }
    }

    fclose(file);
}

// Function to perform element-wise multiplication of two 3D matrices
int*** multiplyMatrices(int ***matrix1, int ***matrix2, int dim) {
    int ***resultMatrix = (int***)malloc(dim * sizeof(int**));
    for (int i = 0; i < dim; ++i) {
        resultMatrix[i] = (int**)malloc(dim * sizeof(int*));
        for (int j = 0; j < dim; ++j) {
            resultMatrix[i][j] = (int*)malloc(dim * sizeof(int));
        }
    }

    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            for (int k = 0; k < dim; ++k) {
                resultMatrix[i][j][k] = matrix1[i][j][k] * matrix2[i][j][k];
            }
        }
    }

    return resultMatrix;
}

int main() {
    int dim1, dim2;
    int ***matrix1 = readMatrix("matrix1.bin", &dim1);
    int ***matrix2 = readMatrix("matrix2.bin", &dim2);

    if (dim1 != dim2) {
        printf("Matrix dimensions do not match\n");
        exit(1);
    }

    int dim = dim1;

    int ***resultMatrix = multiplyMatrices(matrix1, matrix2, dim);

    writeMatrix("result.bin", resultMatrix, dim);

    // Free allocated memory
    for (int i = 0; i < dim; ++i) {
        for (int j = 0; j < dim; ++j) {
            free(matrix1[i][j]);
            free(matrix2[i][j]);
            free(resultMatrix[i][j]);
        }
        free(matrix1[i]);
        free(matrix2[i]);
        free(resultMatrix[i]);
    }
    free(matrix1);
    free(matrix2);
    free(resultMatrix);

    return 0;
}

