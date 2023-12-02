#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include "PGM_Operations/PGM_Operations.h"

#define MAX_PATH_LENGTH 512

unsigned char *applyFilter(unsigned char *pData, int columns, int rows, int cursorSize);
/*int *quantizeMatrix(int *pData, int columns, int rows, int levels);
int *computeSCM(int *pData, int *matrix2, int columns, int rows, int levels, int maxPixelValue);*/

int main(int argc, char *argv[]){

    if (argc < 5) {
        printf("Usage: %s <CursorFilterSize> <InputFolder> <OutputFolder> <Quantization>\n", argv[0]);
        return 1;
    }

    int cursorFilterSize = atoi(argv[1]);
    const char *inputDirectory = argv[2];
    const char *outputDirectory = argv[3];
    int quantization = atoi(argv[4]);

    if (cursorFilterSize == 0 && argv[1][0] != '0') {
        printf("Error: Invalid input for CursorFilterSize.\n");
        return 2;
    }

    if (quantization == 0 && argv[4][0] != '0') {
        printf("Error: Invalid input for Quantization.\n");
        return 2;
    }

    DIR *dir = opendir(inputDirectory);

    if (dir == NULL) {
        printf("Error: Couldn't open the directory.\n");
        return 3;
    }

    struct dirent *entry;
    
    if (dir) {
        while ((entry = readdir(dir)) != NULL) {
            
            char filepath[MAX_PATH_LENGTH];
            char outputFilepath[MAX_PATH_LENGTH];

            snprintf(filepath, sizeof(filepath), "%s/%s", inputDirectory, entry->d_name);
            snprintf(outputFilepath, sizeof(outputFilepath), "%s/blurred_%s", outputDirectory, entry->d_name);
            
            struct pgm img;

            readPGMImage(&img,filepath);

            unsigned char *blurredData = applyFilter(img.pData, img.c, img.r, cursorFilterSize);

            struct pgm blurredImg;
            blurredImg.tipo = img.tipo;
            blurredImg.c = img.c;
            blurredImg.r = img.r;
            blurredImg.mv = img.mv;
            blurredImg.pData = blurredData;

            writePGMImage(&blurredImg, outputFilepath);

            free(img.pData);
            free(blurredData);
            
        }
    }

    closedir(dir);
    return 0;
}

unsigned char *applyFilter(unsigned char *pData, int columns, int rows, int cursorSize) {
    // Error Handling e malloc
    unsigned char *blurredData = (unsigned char *)malloc(columns * rows * sizeof(unsigned char));
    if (blurredData == NULL) return NULL;

    // Itera pela matrix
    for (int i = 0 ; i < rows ; i++) {
        for (int j = 0 ; j < columns ; j++) {
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
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < columns ) {
                        sum += pData[ni * columns + nj];
                    }

                    count++;

                }
            }

            // media
            blurredData[i * columns + j] = (unsigned char)sum / count;

        }
    }

    return blurredData;

}   

/*
int *quantizeMatrix(int *pData, int columns, int rows, int levels) {

    int *quantizedMatrix = (int *)malloc(matrixOrder * matrixOrder * sizeof(int));
    if (quantizedMatrix == NULL) return 5;

    // Quantization logic for each pixel value
    for (int i = 0; i < matrixOrder * matrixOrder; i++) {
        quantizedMatrix[i] = (int)(((float)matrix[i] / 256) * levels);
    }

    return quantizedMatrix;

}

int *computeSCM(int *pData, int *matrix2, int columns, int rows, int levels, int maxPixelValue) {
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

*/