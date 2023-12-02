#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include "PGM_Operations/PGM_Operations.h"

#define MAX_PATH_LENGTH 512

unsigned char *applyFilter(unsigned char *pData, int columns, int rows, int cursorSize);
int *quantizeData(int *pData, int columns, int rows, int levels, int maxPixelValue);
int *computeSCM(int *pData, int *blurredData, int columns, int rows, int levels);
int extractLabelFromFilename(const char *filename);

int main(int argc, char *argv[]){

    if (argc < 5) {
        printf("Usage: %s <CursorFilterSize> <InputDirectory> <OutputDirectory> <QuantizationLevels>\n", argv[0]);
        return 1;
    }

    int cursorFilterSize = atoi(argv[1]);
    const char *inputDirectory = argv[2];
    const char *outputDirectory = argv[3];
    int quantizationLevels = atoi(argv[4]);

    if (cursorFilterSize == 0 && argv[1][0] != '0') {
        printf("Error: Invalid input for CursorFilterSize.\n");
        return 2;
    }

    if (quantizationLevels == 0 && argv[4][0] != '0') {
        printf("Error: Invalid input for Quantization.\n");
        return 2;
    }

    char outputFilename[MAX_PATH_LENGTH];
    snprintf(outputFilename, sizeof(outputFilename), "%s/features_%d_%d.txt", outputDirectory, cursorFilterSize, quantizationLevels);

    FILE *featureFile = fopen(outputFilename, "w");
    if (featureFile == NULL) {
        printf("Error: Couldn't open the combined feature file.\n");
        return 4;
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
            
            struct pgm img;
            readPGMImage(&img,filepath);

            unsigned int *blurredData = applyFilter(img.pData, img.c, img.r, cursorFilterSize);
            unsigned int *scmMatrix = computeSCM(img.pData, blurredData, img.c, img.r, quantizationLevels);

            for (int i = 0; i <= quantizationLevels; i++) {
                for (int j = 0; j <= quantizationLevels; j++) {
                    fprintf(featureFile, "%d, ", scmMatrix[i * (quantizationLevels + 1) + j]);
                }
            }

            // Adicionar o rótulo no final do vetor
            int label = extractLabelFromFilename(entry->d_name);
            fprintf(featureFile, "%d\n", label);

            free(img.pData);
            free(blurredData);
            free(scmMatrix);
            
        }
    }

    closedir(dir);
    return 0;
}

int extractLabelFromFilename(const char *filename) {
    int label;
    sscanf(filename, "%d_", &label);
    return label;
}

unsigned char *applyFilter(unsigned char *pData, int columns, int rows, int cursorSize) {
    // Error Handling and malloc
    unsigned char *blurredData = (unsigned char *)malloc(columns * rows * sizeof(unsigned char));
    if (blurredData == NULL) return NULL;

    // Itera pela matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            float sum = 0.0;  // Change to float for more accurate average
            int count = 0;

            // Itera pelos vizinhos selecionados pelo tamanho do vetor
            // cursorSize é a distancia das bordas partindo do centro,
            // Ex.: cursor 3x3 seria de tamanho 1
            for (int x = -cursorSize; x <= cursorSize; x++) {
                for (int y = -cursorSize; y <= cursorSize; y++) {
                    int ni = i + x;
                    int nj = j + y;

                    // Checa se os valores estão dentro da matrix
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < columns) {
                        sum += pData[ni * columns + nj];
                        count++;
                    }
                }
            }

            // Avoid division by zero
            if (count > 0) {
                // media
                blurredData[i * columns + j] = (unsigned char)(sum / count);
            } else {
                // Handle the case where count is zero (division by zero)
                blurredData[i * columns + j] = pData[i * columns + j];
            }
        }
    }

    return blurredData;
}

int *quantizeData(int *pData, int columns, int rows, int levels, int maxPixelValue) {

    int *quantizedData = (int *)malloc(columns * rows * sizeof(int));
    if (quantizedData == NULL) return 5;

    // Quantization logic for each pixel value
    for (int i = 0; i < columns * rows; i++) {
        quantizedData[i] = (int)(((float)pData[i] / maxPixelValue) * levels);
    }

    return quantizedData;

}

int *computeSCM(int *pData, int *blurredData, int columns, int rows, int levels) {
    int *quantizedMatrix1 = quantizeMatrix(pData, columns, rows, levels);
    int *quantizedMatrix2 = quantizeMatrix(blurredData, columns, rows, levels);

    unsigned char *scmMatrix = (unsigned char *)calloc((levels + 1) * (levels + 1), sizeof(unsigned char));
    if (scmMatrix == NULL) return 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            scmMatrix[quantizedMatrix1[i * columns + j] * (levels + 1) + quantizedMatrix2[i * columns + j]]++;
        }
    }

    free(quantizedMatrix1);
    free(quantizedMatrix2);

    return scmMatrix;
}