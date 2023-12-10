//SCM_Extractor.c

/*************************************************************/
/* Aluno 01: Ásafe Silva Duarte Ximenes Frota                */
/* Matricula: 20231045050254                                 */
/*                                                           */
/* Aluno 02: Antonio Lucas Pereira Holanda                   */
/* Matricula: 20231045050246                                 */
/*                                                           */
/* Aluno 03: João Pedro Ibiapina Portela Neime               */
/* Matricula: 20231045050327                                 */
/*                                                           */
/* Aluno 04: Rafael Jorge Cabral Cardoso                     */
/* Matricula: 20231045050181                                 */
/*                                                           */
/* Avaliação 04: Trabalho Final                              */
/* 04.505.23 - 2023.2 - Prof. Daniel Ferreira                */
/* Compilador: gcc.exe (Rev7, Built by MSYS2 project) 13.1.0 */
/*************************************************************/

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <time.h>
#include "../include/PGM_Operations.h"
#include "../include/SCM_Util.h"

// Define para strings dos nomes endereço/arquivo
#define MAX_PATH_LENGTH 512

int main(int argc, char *argv[]){

    // Inicialização para timer
    clock_t begin, end;
	double time_per_img, time_total = 0;
    int fileNumber = 1;

    // Checa o uso correto dos argumentos
    if (argc < 5) {
        printf("Usage: %s <CursorFilterSize> <QuantizationLevels> <InputDirectory> <OutputDirectory>\n", argv[0]);
        return 1;
    }

    // Recebe os dados dos argumentos
    int cursorFilterSize = atoi(argv[1]);
    int quantizationLevels = atoi(argv[2]);
    const char *inputDirectory = argv[3];
    const char *outputDirectory = argv[4];

    // Checa se os valores cursorFilter e quantizationLevels válidos
    if (cursorFilterSize == 0 && argv[1][0] != '0') {
        printf("Error: Invalid input for CursorFilterSize.\n");
        return 2;
    }
    if (quantizationLevels == 0 && argv[2][0] != '0') {
        printf("Error: Invalid input for Quantization.\n");
        return 3;
    }

    // Escreve em outputFilename o nome do arquivo de caracteristicas
    char outputFilename[MAX_PATH_LENGTH];
    snprintf(outputFilename, sizeof(outputFilename), "%s/features_%d_%d.csv", outputDirectory, cursorFilterSize, quantizationLevels);

    char outputListFilename[MAX_PATH_LENGTH];
    snprintf(outputListFilename, sizeof(outputListFilename), "%s/features_%d_%d_FILELIST.txt", outputDirectory, cursorFilterSize, quantizationLevels);

    // Abre o arquivo de caracteristicas
    FILE *featureFile = fopen(outputFilename, "w");
    if (featureFile == NULL) {
        printf("Error: Couldn't open the combined feature file.\n");
        return 4;
    }

    // Abre o arquivo de lista das imagens
    FILE *nameList = fopen(outputListFilename, "w");
    if (outputListFilename == NULL) {
        printf("Error: Couldn't open the combined feature file !LIST!.\n");
        return 5;
    }

    // Abre o diretório de imagens input
    DIR *dir = opendir(inputDirectory);
    if (dir == NULL) {
        printf("Error: Couldn't open the directory.\n");
        return 6;
    }

    // Cria a primeira linha no arquivo
    for ( int x = 1 ; x <= (quantizationLevels * quantizationLevels) ; x++ ) {
	    fprintf(featureFile, "%d,", x);
    }
    fprintf(featureFile, "%d\n", (quantizationLevels * quantizationLevels + 1));

    // Cria um struct para as entradas
    struct dirent *entry;
    
    // Verifica se dir é nulo
    if (dir) {
        
        // Inicia o clock
	    begin = clock();
        
        // Itera por todos os itens do diretório
        while ((entry = readdir(dir)) != NULL) {
            
            // Pula as entradas especiais
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
            }

            // Escreve em filepath o endereço da imagem atual
            char filepath[MAX_PATH_LENGTH];
            snprintf(filepath, sizeof(filepath), "%s/%s", inputDirectory, entry->d_name);
            
            // Escreve o número do arquivo
            fprintf(nameList, "%d - %s\n", fileNumber, entry->d_name);
            fileNumber++;

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

            // Escreve stroma ou epithelium, 1,0 respectivamente
	        extractLabelSCM(featureFile, entry->d_name);

            // Free all data
            free(img.pData);
            free(blurredData);
            free(quantizedData1);
            free(quantizedData2);
            free(scmMatrix);

        }
    }

    // Fechar arquivo de caracteristicas e diretório e endclock
    fclose(featureFile);
    closedir(dir);
    end = clock();
	time_total = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Tempo Total: %lf\n",time_total);
	return 0;
}
