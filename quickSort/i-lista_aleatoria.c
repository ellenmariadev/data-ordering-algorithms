#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void generateRandomNumbers(int arr[], int size) {
    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }
}

int main() {
    srand(time(NULL));

    int sizes[] = {10000, 50000, 100000, 500000, 1000000, 10000000, 50000000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    char* pivotStrategies[] = {"Original", "Mediana de três", "Amostragem aleatória"};

    for (int i = 0; i < numSizes; i++) {
        for (int j = 0; j < 3; j++) {
            int* arr = malloc(sizes[i] * sizeof(int));

            char filename[50];
            sprintf(filename, "../randomFiles/%d.txt", sizes[i]);

            // Gerar novos números aleatórios se já não tiver esses arquivos.
            FILE* file = fopen(filename, "r");
            if (file == NULL) {
                generateRandomNumbers(arr, sizes[i]);
                writeNumbersToFile(filename, arr, sizes[i]);
            } else {
                for (int k = 0; k < sizes[i]; k++) {
                    fscanf(file, "%d", &arr[k]);
                }
                fclose(file);
            }

            long long int comparisons = 0;
            long long int swaps = 0;

            clock_t start = clock();
            quickSort(arr, 0, sizes[i] - 1, &comparisons, &swaps, j);
            clock_t end = clock();

            double runtime = (double)(end - start) / CLOCKS_PER_SEC;

            printf("\n**** Lista aleatória de tamanho [%d] com estratégia de pivô [%s] **** ", sizes[i], pivotStrategies[j]);
            printf("\n\nComparações: %lld\n", comparisons);
            printf("Swaps: %lld\n", swaps);
            printf("Tempo: %fs\n", runtime);
            fflush(stdout);

            free(arr);
        }
    }

    return 0;
}