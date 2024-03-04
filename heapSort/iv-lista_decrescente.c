#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generateDescendingNumbers(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i, int* comparisons, int* swaps) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
        (*comparisons)++;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
        (*comparisons)++;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        (*swaps)++;
        heapify(arr, n, largest, comparisons, swaps);
    }
}

void heapSort(int arr[], int n, int* comparisons, int* swaps) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, comparisons, swaps);

    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        (*swaps)++;
        heapify(arr, i, 0, comparisons, swaps);
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

        clock_t start = clock();
        heapSort(arr, sizes[i], &comparisons, &swaps);
        clock_t end = clock();

        double runtime = (double)(end - start) / CLOCKS_PER_SEC;

        printf("\n**** Lista decrescente de tamanho [%d] **** ", sizes[i]);
        printf("\n\nComparações: %d\n", comparisons);
        printf("Swaps: %d\n", swaps);
        printf("Tempo: %fs\n", runtime);
        fflush(stdout);

        free(arr);
    }

    return 0;
}