//stdlib e time para rand
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *createMatrix(int matrixOrder, int matrixMaxSize);
void printMatrix(int *matrix, int matrixOrder);
int *applyFilter(int *matrix, int matrixOrder, int cursorSize);

int main(){

    srand(time(NULL));
	
    int matrixOrder = 8;
    int matrixCursorSize = 1;
    int matrixMaxNumber = 257;

    // Gera matrix
    int *matrix = createMatrix(matrixOrder, matrixMaxNumber);
    printMatrix(matrix, matrixOrder);

    puts("");

    // Borra matrix
    int *blurredMatrix = applyFilter(matrix, matrixOrder, matrixCursorSize);
    printMatrix(blurredMatrix, matrixOrder);

    // Free
    free(matrix);
    free(blurredMatrix);

    return 0;

}

// retorna um vetor de uma matrix aleatoriamente gerada
int *createMatrix(int matrixOrder, int matrixMaxSize) {
    // Error Handling e malloc
    int *matrix = (int *)malloc(matrixOrder * matrixOrder * sizeof(int));
    if (matrix == NULL) return 0;

    // Cria um valor aleatorio para cada valor de matrix
    for (int i = 0 ; i < (matrixOrder * matrixOrder) ; i++) {
        matrix[i] = rand() % matrixMaxSize;
    }
    return matrix;
}

// printa a matrix
void printMatrix(int *matrix, int matrixOrder) {
    
    for (int i = 0; i < matrixOrder; i++) {
        for (int j = 0; j < matrixOrder; j++) {
            printf("%d ", matrix[i * matrixOrder + j]);
        }
        puts("");
    }
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
