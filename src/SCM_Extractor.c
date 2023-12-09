//SCM_Extractor.c
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include "../include/PGM_Operations.h"
#include "../include/SCM_Util.h"

// Define para strings dos nomes endereço/arquivo
#define MAX_PATH_LENGTH 512

int main(int argc, char *argv[]){

    // Checa o uso correto dos argumentos
    if (argc < 5) {
        printf("Usage: %s <CursorFilterSize> <InputDirectory> <OutputDirectory> <QuantizationLevels>\n", argv[0]);
        return 1;
    }

    // Recebe os dados dos argumentos
    int cursorFilterSize = atoi(argv[1]);
    const char *inputDirectory = argv[2];
    const char *outputDirectory = argv[3];
    int quantizationLevels = atoi(argv[4]);

    // Checa se os valores cursorFilter e quantizationLevels válidos
    if (cursorFilterSize == 0 && argv[1][0] != '0') {
        printf("Error: Invalid input for CursorFilterSize.\n");
        return 2;
    }
    if (quantizationLevels == 0 && argv[4][0] != '0') {
        printf("Error: Invalid input for Quantization.\n");
        return 2;
    }

    // Escreve em outputFilename o nome do arquivo de caracteristicas
    char outputFilename[MAX_PATH_LENGTH];
    snprintf(outputFilename, sizeof(outputFilename), "%s/features_%d_%d.txt", outputDirectory, cursorFilterSize, quantizationLevels);

    // Abre o arquivo de caracteristicas
    FILE *featureFile = fopen(outputFilename, "w");
    if (featureFile == NULL) {
        printf("Error: Couldn't open the combined feature file.\n");
        return 4;
    }
    // Abre o diretório de imagens input
    DIR *dir = opendir(inputDirectory);
    if (dir == NULL) {
        printf("Error: Couldn't open the directory.\n");
        return 3;
    }

    // Cria um struct para as entradas
    struct dirent *entry;
    
    // Verifica se dir é nulo
    if (dir) {
        
        // Itera por todos os itens do diretório
        while ((entry = readdir(dir)) != NULL) {
            
            // Pula as entradas especiais
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
            }

            // Escreve em filepath o endereço da imagem atual
            char filepath[MAX_PATH_LENGTH];
            snprintf(filepath, sizeof(filepath), "%s/%s", inputDirectory, entry->d_name);

            // Cria um struct img e escreve nele os dados da imagem
            struct pgm img;
            readPGMImage(&img,filepath);

            // Cria os dados "borrados", depois 
            unsigned char *blurredData = filterData(img.pData, img.c, img.r, cursorFilterSize);

            // Quantiza a original e borrada
            unsigned char *quantizedData1 = quantizeData(img.pData, img.c, img.r, quantizationLevels, img.mv);
            unsigned char *quantizedData2 = quantizeData(blurredData, img.c, img.r, quantizationLevels, img.mv);

            // Cria matrix SCM
            unsigned char *scmMatrix = computeSCM(quantizedData1, quantizedData2, img.c, img.r, quantizationLevels);

            fprintSCM(featureFile, scmMatrix, quantizationLevels);

            // Adicionar o rótulo no final do vetor
            int label = extractLabelSCM(entry->d_name);
            fprintf(featureFile, "%d\n", label);

            // Free all data
            free(img.pData);
            free(blurredData);
            free(quantizedData1);
            free(quantizedData2);
            free(scmMatrix);

        }
    }

    // Fechar arquivo de caracteristicas e diretório
    fclose(featureFile);
    closedir(dir);
    return 0;
}