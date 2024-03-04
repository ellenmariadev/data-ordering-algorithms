#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generatePartialSortNumbers(int arr[], int size, float percentage) {
    srand(time(NULL));
    int orderedSize = (int)(size * percentage);

    // Parte ordenada
    for (int i = 0; i < orderedSize; i++) {
        arr[i] = i + 1;
    }

    // Parte com números não ordenados e não duplicados
    int* temp = malloc((size - orderedSize) * sizeof(int));
    for (int i = 0; i < size - orderedSize; i++) {
        temp[i] = i + orderedSize + 1;
    }

    for (int i = size - 1; i >= orderedSize; i--) {
        int j = rand() % (i - orderedSize + 1);
        arr[i] = temp[j];
        temp[j] = temp[i - orderedSize];
    }

    free(temp);
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


void partialSortArray(int size, float percentage) {
    int* arr = malloc(size * sizeof(int));

    char filename[50];
    sprintf(filename, "../partialSortFiles/%d_%d.txt", size, (int)(percentage * 100));

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        generatePartialSortNumbers(arr, size, percentage);
        writeNumbersToFile(filename, arr, size);

        int comparisons = 0;
        int swaps = 0;

        clock_t start = clock();
        heapSort(arr, size, &comparisons, &swaps);
        clock_t end = clock();

        double runtime = (double)(end - start) / CLOCKS_PER_SEC;

        printf("\n**** Lista parcialmente ordenada de tamanho [%d] com [%d%%] por cento de ordenação **** ", size, (int)(percentage * 100));
        printf("\n\nComparações: %d\n", comparisons);
        printf("Swaps: %d\n", swaps);
        printf("Tempo: %fs\n", runtime);
        fflush(stdout);

    } else {
        for (int j = 0; j < size; j++) {
            fscanf(file, "%d", &arr[j]);
        }

        generatePartialSortNumbers(arr, size, percentage);
        writeNumbersToFile(filename, arr, size);
    
        int comparisons = 0;
        int swaps = 0;

        clock_t start = clock();
        heapSort(arr, size, &comparisons, &swaps);
        clock_t end = clock();

        double runtime = (double)(end - start) / CLOCKS_PER_SEC;

        printf("\n**** Lista parcialmente ordenada de tamanho [%d] com [%d%%] de ordenação **** ", size, (int)(percentage * 100));
        printf("\n\nComparações: %d\n", comparisons);
        printf("Swaps: %d\n", swaps);
        printf("Tempo: %fs\n", runtime);
        fflush(stdout);

        fclose(file);

    }
    free(arr);
}

int main() {
    int sizes[] = {10000, 50000, 100000, 500000, 1000000, 10000000, 50000000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < numSizes; i++) {
        partialSortArray(sizes[i], 0.5);
        partialSortArray(sizes[i], 0.75);
    }

    return 0;
}