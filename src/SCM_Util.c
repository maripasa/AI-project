// SCM_Util

#include <stdio.h>
#include <stdlib.h>
#include "../include/SCM_Util.h"

// Filtra os dados
unsigned char *filterData(unsigned char *pData, int columns, int rows, int cursorSize) {

    // Aloca Ponteiro para os dados
    unsigned char *blurredData = (unsigned char *)malloc(columns * rows * sizeof(unsigned char));
    if (blurredData == NULL) return NULL;

    // Itera pela matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {

            float sum = 0.0; 
            int count = 0;

            // Itera pelos vizinhos selecionados pelo tamanho do vetor
            // cursorSize é a distancia das bordas partindo do centro,
            // Ex.: cursor 3x3 seria de tamanho 1
            for (int x = -cursorSize; x <= cursorSize; x++) {
                for (int y = -cursorSize; y <= cursorSize; y++) {

                    // Calcula os endereços da mini matrix
                    int ni = i + x;
                    int nj = j + y;

                    // Checa se os valores estão dentro da matrix
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < columns) {
                        sum += pData[ni * columns + nj];
                    }
                    count++;
                }
            }

            // Evita divisão por 0 e faz a média
            if (count > 0) {

                blurredData[i * columns + j] = (unsigned char)(sum / count);

            } else {

                blurredData[i * columns + j] = pData[i * columns + j];

            }
        }
    }

    return blurredData;
}

// Quantiza os dados
unsigned char *quantizeData(unsigned char *pData, int columns, int rows, int levels, int maxPixelValue) {

    // Aloca ponteiro para os dados
    unsigned char *quantizedData = (unsigned char*)malloc(columns * rows * sizeof(unsigned char));
    if (quantizedData == NULL) return NULL;

    // Quantiza cada pixel
    for (int i = 0; i < columns * rows; i++) {
        quantizedData[i] = (unsigned char)(((float)pData[i] / (maxPixelValue + 1)) * levels);
    }

    return quantizedData;

}

unsigned char *computeSCM(unsigned char *Data1, unsigned char *Data2, int columns, int rows, int levels) {

    // Aloca ponteiro para os dados
    unsigned char *scmMatrix = (unsigned char *)calloc((levels) * (levels), sizeof(unsigned char));
    if (scmMatrix == NULL) return 0;

    // Utiliza os valores de ambos os dados como index da matriz (Data1[i], Data2[i])
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            scmMatrix[Data1[i * columns + j] * (levels) + Data2[i * columns + j]]++;
        }
    }

    return scmMatrix;
}

void fprintSCM(FILE *file, unsigned char *scmMatrix, int quantizationLevels) {

    // Printa cada um dos valores dos dados da SCM
    for (int i = 0; i <= quantizationLevels; i++) {
        for (int j = 0; j <= quantizationLevels; j++) {
            fprintf(file, "%d, ", scmMatrix[i * (quantizationLevels + 1) + j]);
        }
    }
}

int extractLabelSCM(const char *filename) {
    // Toma o label no final e escreve no final de cada linha de dados
    int label;
    sscanf(filename, "%d_", &label);
    return label;
}