#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generatePartialSortNumbers(int arr[], int size, float percentage) {
    srand((unsigned)time(NULL));
    int orderedSize = (int)(size * percentage);

    // Parte ordenada
    for (int i = 0; i < orderedSize; i++) {
        arr[i] = i + 1;
    }

    // Parte com números aleatórios para o restante do array
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

void insertionSort(int arr[], int n, int* comparisons, int* swaps) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            (*comparisons)++;
            (*swaps)++;
        }
        arr[j + 1] = key;
    }
}

void partialSortArray(int size, float percentage) {
    int* arr = malloc(size * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    char filename[50];
    sprintf(filename, "partialSortFiles/%d_%d.txt", size, (int)(percentage * 100));

    // Checa se o arquivo já existe para evitar regenerar os números
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        generatePartialSortNumbers(arr, size, percentage);
        writeNumbersToFile(filename, arr, size);
    } else {
        for (int j = 0; j < size; j++) {
            fscanf(file, "%d", &arr[j]);
        }
        fclose(file);
    }

    int comparisons = 0;
    int swaps = 0;

    clock_t start = clock();
    insertionSort(arr, size, &comparisons, &swaps);
    clock_t end = clock();

    double runtime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n**** Insertion Sort - Lista parcialmente ordenada de tamanho [%d] com [%d%%] de ordenação ****", size, (int)(percentage * 100));
    printf("\nComparações: %d\n", comparisons);
    printf("Swaps: %d\n", swaps);
    printf("Tempo: %f segundos\n", runtime);

    free(arr);
}

int main() {
    int sizes[] = {10000, 50000, 100000, 500000, 1000000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < numSizes; i++) {
        partialSortArray(sizes[i], 0.5);
        partialSortArray(sizes[i], 0.75);
    }

    return 0;
}
