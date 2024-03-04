#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generateRandomNumbers(int arr[], int size) {
    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }
}

void writeNumbersToFile(char* filename, int arr[], int size) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Não foi possível abrir o arquivo %s\n", filename);
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", arr[i]);
    }

    fclose(file);
}

void bubbleSort(int arr[], int n, int* comparisons, int* swaps, int* iterations) {
    int i, j, temp;
    for (i = 0; i < n-1; i++) {
        (*iterations)++;
        for (j = 0; j < n-i-1; j++) {
            (*comparisons)++;
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                (*swaps)++;
            }
        }
    }
}

int main() {
    int sizes[] = {10000, 50000, 100000, 500000, 1000000, 10000000, 50000000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < numSizes; i++) {
        int* arr = malloc(sizes[i] * sizeof(int));

        char filename[50];
        sprintf(filename, "../randomFiles/%d.txt", sizes[i]);

        FILE* file = fopen(filename, "r");
        if (file == NULL) {
            generateRandomNumbers(arr, sizes[i]);
        } else {
            for (int j = 0; j < sizes[i]; j++) {
                fscanf(file, "%d", &arr[j]);
            }
            fclose(file);
        }

        int comparisons = 0;
        int swaps = 0;
        int iterations = 0;

        clock_t start = clock();
        bubbleSort(arr, sizes[i], &comparisons, &swaps, &iterations);
        clock_t end = clock();

        double runtime = (double)(end - start) / CLOCKS_PER_SEC;

        printf("\n**** Bubble Sort - Lista aleatória de tamanho [%d] **** ", sizes[i]);
        printf("\n\nComparações: %d\n", comparisons);
        printf("Swaps: %d\n", swaps);
        printf("Iterações: %d\n", iterations);
        printf("Tempo: %fs\n", runtime);
        fflush(stdout);

        writeNumbersToFile(filename, arr, sizes[i]);

        free(arr);
    }

    return 0;
}
