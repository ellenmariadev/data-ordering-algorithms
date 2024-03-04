#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generateOrderedNumbers(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
}

void bubbleSort(int arr[], int n, int* comparisons, int* swaps, int* iterations) {
    int i, j, temp;
    int swapped;
    for (i = 0; i < n-1; i++) {
        swapped = 0;
        for (j = 0; j < n-i-1; j++) {
            (*comparisons)++;
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = 1;
                (*swaps)++;
            }
        }
        (*iterations)++;
        // Se não houve trocas nesta passagem, então a lista já está ordenada.
        if (swapped == 0)
            break;
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
        int iterations = 0;

        clock_t start = clock();
        bubbleSort(arr, sizes[i], &comparisons, &swaps, &iterations);
        clock_t end = clock();

        double runtime = (double)(end - start) / CLOCKS_PER_SEC;

        printf("\n**** Bubble Sort - Lista ordenada de tamanho [%d] **** ", sizes[i]);
        printf("\n\nComparações: %d\n", comparisons);
        printf("Swaps: %d\n", swaps);
        printf("Iterações: %d\n", iterations);
        printf("Tempo: %fs\n", runtime);
        fflush(stdout);

        free(arr);
    }

    return 0;
}
