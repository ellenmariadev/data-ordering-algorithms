#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Gera números aleatórios e preenche o array
void generateRandomNumbers(int arr[], int size) {
    // Usar uma seed baseada no tempo atual
    srand((unsigned)time(NULL));

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100000; // Limitar os números para um intervalo gerenciável
    }
}

// Escreve os números ordenados em um arquivo
void writeNumbersToFile(const char* filename, int arr[], int size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo %s\n", filename);
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", arr[i]); // Mudança para escrita em linha nova para melhor leitura
    }

    fclose(file);
}

// Ordenação por Insertion Sort
void insertionSort(int arr[], int n, int* comparisons, int* swaps) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        // Mover elementos de arr[0..i-1], que são maiores que key, para uma posição à frente de sua posição atual
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            (*comparisons)++;
            (*swaps)++;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int sizes[] = {10000, 50000, 100000, 500000}; // Ajustado para tamanhos gerenciáveis
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < numSizes; i++) {
        int* arr = (int*)malloc(sizes[i] * sizeof(int));
        if (arr == NULL) {
            printf("Erro na alocação de memória\n");
            return 1;
        }

        char filename[50];
        sprintf(filename, "randomFiles/%d.txt", sizes[i]);

        // Geração de números aleatórios e gravação no arquivo
        generateRandomNumbers(arr, sizes[i]);
        writeNumbersToFile(filename, arr, sizes[i]);

        // Estatísticas de ordenação
        int comparisons = 0, swaps = 0;

        // Medição do tempo de execução
        clock_t start = clock();
        insertionSort(arr, sizes[i], &comparisons, &swaps);
        clock_t end = clock();

        double runtime = (double)(end - start) / CLOCKS_PER_SEC;

        printf("\n**** Insertion Sort - Lista de tamanho [%d] ****", sizes[i]);
        printf("\nComparações: %d\nSwaps: %d\nTempo: %f segundos\n", comparisons, swaps, runtime);

        // Liberar memória alocada
        free(arr);
    }

    return 0;
}
