#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generateDescendingNumbers(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
}

void selectionSort(int arr[], int n, int* comparisons, int* swaps, int* iterations) {
    int i, j, minIndex, temp;

    for (i = 0; i < n - 1; i++) {
        (*iterations)++;
        minIndex = i;
        for (j = i + 1; j < n; j++) {
            (*comparisons)++;
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }

        if (minIndex != i) {
            (*swaps)++;
            temp = arr[minIndex];
            arr[minIndex] = arr[i];
            arr[i] = temp;
        }
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
        selectionSort(arr, sizes[i], &comparisons, &swaps, &iterations);
        clock_t end = clock();

        double runtime = (double)(end - start) / CLOCKS_PER_SEC;

        printf("\n**** Lista decrescente de tamanho [%d] **** ", sizes[i]);
        printf("\n\nComparações: %d\n", comparisons);
        printf("Swaps: %d\n", swaps);
        printf("Iterações: %d\n", iterations);
        printf("Tempo: %fs\n", runtime);
        fflush(stdout);

        free(arr);
    }

    return 0;
}