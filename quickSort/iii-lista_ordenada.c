#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generateOrderedNumbers(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
}

// Trocar elementos
void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high, long long int* comparisons, long long int* swaps) {
    int pivot = arr[high]; // Pivô é o último elemento 
    int i = (low - 1); // Índex do menor elemento

    // Realiza a troca se o elemento atual é menor que o pivô
    for (int j = low; j <= high - 1; j++) {
        (*comparisons)++;
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
            (*swaps)++;
        }
    }
    // Coloca o pivô na posição correta
    swap(&arr[i + 1], &arr[high]);
    (*swaps)++;
    return (i + 1);
}

// Amostragem aleatória
int randomPartition(int arr[], int low, int high, long long int* comparisons, long long int* swaps) {
    int random = low + rand() % (high - low);
    swap(&arr[random], &arr[high]);
    return partition(arr, low, high, comparisons, swaps);
}

// Mediana de três númerios (menor, médio, maior)
int medianOfThree(int arr[], int low, int high) {
    int mid = low + (high - low) / 2;

    // Ordena os números (menor, médio, maior)
    if (arr[low] > arr[mid])
        swap(&arr[low], &arr[mid]);
    if (arr[mid] > arr[high])
        swap(&arr[mid], &arr[high]);
    if (arr[low] > arr[mid])
        swap(&arr[low], &arr[mid]);

    return mid;
}

void quickSort(int arr[], int low, int high, long long int* comparisons, long long int* swaps, int pivotStrategy) {
    while (low < high) {
        int pi;

        // Escolhe a estratégia de pivô
        if (pivotStrategy == 0) {
            pi = partition(arr, low, high, comparisons, swaps);
        } else if (pivotStrategy == 1) {
            int median = medianOfThree(arr, low, high);
            swap(&arr[median], &arr[high]);
            pi = partition(arr, low, high, comparisons, swaps);
        } else {
            pi = randomPartition(arr, low, high, comparisons, swaps);
        }

        // Ordena os elementos antes e depois do pivô
        if (pi - low < high - pi) {
            quickSort(arr, low, pi - 1, comparisons, swaps, pivotStrategy);
            low = pi + 1;
        } else {
            quickSort(arr, pi + 1, high, comparisons, swaps, pivotStrategy);
            high = pi - 1;
        }
    }
}

void orderedListSort(int size, int pivotStrategy) {
    int* arr = malloc(size * sizeof(int));
    char* pivotStrategies[] = {"Original", "Mediana de três", "Amostragem aleatória"};

    generateOrderedNumbers(arr, size);

    long long int comparisons = 0;
    long long int swaps = 0;

    clock_t start = clock();
    quickSort(arr, 0, size - 1, &comparisons, &swaps, pivotStrategy);
    clock_t end = clock();

    double runtime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\n**** Lista ordenada de tamanho [%d] com estratégia de pivô [%s] **** ", size, pivotStrategies[pivotStrategy]);
    printf("\n\nComparações: %lld\n", comparisons);
    printf("Swaps: %lld\n", swaps);
    printf("Tempo: %fs\n", runtime);
    fflush(stdout);

    free(arr);
}


int main() {
    int sizes[] = {10000, 50000, 100000, 500000, 1000000, 10000000, 50000000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < numSizes; i++) {
        for (int j = 0; j < 3; j++) {
            orderedListSort(sizes[i], j);
        }
    }

    return 0;
}