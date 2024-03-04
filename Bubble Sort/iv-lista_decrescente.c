#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generateDescendingNumbers(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
}

void bubbleSort(int arr[], int n, int* comparisons, int* swaps, int* iterations) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            (*comparisons)++;
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                (*swaps)++;
            }
        }
        (*iterations)++;
    }
}

int main() {
    int sizes[] = {10000, 50000, 100000, 500000, 1000000, 10000000, 50000000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < numSizes; i++) {
        int* arr = malloc(sizes[i] * sizeof(int));

        generateDescendingNumbers(arr, sizes[i]);

        int comparisons = 0;
        int swaps = 0;
        int iterations = 0;

        clock_t start = clock();
        bubbleSort(arr, sizes[i], &comparisons, &swaps, &iterations);
        clock_t end = clock();

        double runtime = (double)(end - start) / CLOCKS_PER_SEC;

        printf("\n**** Bubble Sort - Lista decrescente de tamanho [%d] **** ", sizes[i]);
        printf("\n\nComparações: %d\n", comparisons);
        printf("Swaps: %d\n", swaps);
        printf("Iterações: %d\n", iterations);
        printf("Tempo: %fs\n", runtime);
        fflush(stdout);

        free(arr);
    }

    return 0;
}