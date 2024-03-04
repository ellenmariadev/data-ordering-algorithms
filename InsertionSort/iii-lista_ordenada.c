#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generateOrderedNumbers(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
}

void insertionSort(int arr[], int n, int* comparisons, int* swaps) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* Move os elementos de arr[0..i-1], que são
          maiores que key, para uma posição à frente
          da sua posição atual */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            (*comparisons)++;
            (*swaps)++;
        }
        arr[j + 1] = key;
        if (j >= 0) (*comparisons)++;
    }
}

int main() {
    int sizes[] = {10000, 50000, 100000, 500000, 1000000, 10000000, 50000000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < numSizes; i++) {
        int* arr = malloc(sizes[i] * sizeof(int));

        generateOrderedNumbers(arr, sizes[i]);

        int comparisons = 0;
        int swaps = 0;

        clock_t start = clock();
        insertionSort(arr, sizes[i], &comparisons, &swaps);
        clock_t end = clock();

        double runtime = (double)(end - start) / CLOCKS_PER_SEC;

        printf("\n**** Insertion Sort - Lista ordenada de tamanho [%d] **** ", sizes[i]);
        printf("\n\nComparações: %d\n", comparisons);
        printf("Swaps: %d\n", swaps);
        printf("Tempo: %fs\n", runtime);
        fflush(stdout);

        free(arr);
    }

    return 0;
}
