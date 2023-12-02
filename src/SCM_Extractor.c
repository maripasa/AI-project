#include <stdio.h>
#include <dirent.h>
#include "PGM_operations.h"

int *applyFilter(int *matrix, int matrixOrder, int cursorSize);
int *computeSCM(int *matrix1, int *matrix2, int matrixOrder, int levels);
int *quantizeMatrix(int *matrix, int matrixOrder, int levels);

int main(int argc, char *argv[]){

    if (argc < 3) {
        printf("Usage: %s <FilterSize> <Quantization>\n", argv[0]);
        return 1; // Return an error code
    }

    struct pgm img;

    DIR *d;
    struct dirent *dir;
    d = opendir("./images");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {



        }
    }

    closedir(d);
    return 0;

}

int *applyFilter(int *matrix, int matrixOrder, int cursorSize) {
    // Error Handling e malloc
    int *blurredMatrix = (int *)malloc(matrixOrder * matrixOrder * sizeof(int));
    if (blurredMatrix == NULL) return 0;

    // Itera pela matrix
    for (int i = 0 ; i < matrixOrder ; i++) {
        for (int j = 0 ; j < matrixOrder ; j++) {
            int sum = 0;
            int count = 0;

            // Itera pelos vizinhos selecionados pelo tamanho do vetor
            // cursorSize é a distancia das bordas partindo do centro,
            // Ex.: cursor 3x3 seria de tamanho 1
            for (int x = -cursorSize ; x <= cursorSize ; x++) {
                for (int y = -cursorSize ; y <= cursorSize ; y++) {

                    int ni = i + x;
                    int nj = j + y;

                    // Checa se os valores estão dentro da matrix
                    if (ni >= 0 && ni < matrixOrder && nj >= 0 && nj < matrixOrder ) {
                        sum += matrix[ni * matrixOrder + nj];
                    }

                    count++;

                }
            }

            // media
            blurredMatrix[i * matrixOrder + j] = sum / count;

        }
    }

    return blurredMatrix;

}   

int *quantizeMatrix(int *matrix, int matrixOrder, int levels) {

    int *quantizedMatrix = (int *)malloc(matrixOrder * matrixOrder * sizeof(int));
    if (quantizedMatrix == NULL) return 0;

    // Quantization logic for each pixel value
    for (int i = 0; i < matrixOrder * matrixOrder; i++) {
        quantizedMatrix[i] = (int)(((float)matrix[i] / 256) * levels);
    }

    return quantizedMatrix;

}

int *computeSCM(int *matrix1, int *matrix2, int matrixOrder, int levels) {
    int *quantizedMatrix1 = quantizeMatrix(matrix1, matrixOrder, levels);
    int *quantizedMatrix2 = quantizeMatrix(matrix2, matrixOrder, levels);

    int *scmMatrix = (int *)calloc((levels + 1) * (levels + 1), sizeof(int));
    if (scmMatrix == NULL) return 0;

    for (int i = 0; i < matrixOrder; i++) {
        for (int j = 0; j < matrixOrder; j++) {
            scmMatrix[quantizedMatrix1[i * matrixOrder + j] * (levels + 1) + quantizedMatrix2[i * matrixOrder + j]]++;
        }
    }

    free(quantizedMatrix1);
    free(quantizedMatrix2);

    return scmMatrix;
}