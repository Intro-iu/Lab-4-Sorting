#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATA_SIZE_1 10
#define DATA_SIZE_2 1000
#define DATA_SIZE_3 100000

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertion_sort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void shell_sort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void countSort(int arr[], int n, int exp) {
    int *output = (int *)malloc(n * sizeof(int));
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];

    free(output);
}

void radix_sort(int arr[], int n) {
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

// Generate Random Data
void generate_data(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100000;
    }
}

// Measure Sorting Performance for two-parameter functions
void measure_performance(void (*sort_func)(int[], int), int *arr, int n, const char *sort_name) {
    int *copy = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        copy[i] = arr[i];
    }

    clock_t start = clock();
    sort_func(copy, n);
    clock_t end = clock();
    printf("%s: %lf seconds\n", sort_name, (double)(end - start) / CLOCKS_PER_SEC);

    free(copy);
}

// Measure Performance for Recursive Sort Functions with three parameters
void measure_performance_for_recursive(void (*sort_func)(int[], int, int), int *arr, int n, const char *sort_name) {
    int *copy = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        copy[i] = arr[i];
    }

    clock_t start = clock();
    sort_func(copy, 0, n - 1);
    clock_t end = clock();
    printf("%s: %lf seconds\n", sort_name, (double)(end - start) / CLOCKS_PER_SEC);

    free(copy);
}

int main() {
    srand(time(0));

    int sizes[] = {DATA_SIZE_1, DATA_SIZE_2, DATA_SIZE_3};
    for (int i = 0; i < 3; i++) {
        int n = sizes[i];
        int *arr = (int *)malloc(n * sizeof(int));
        generate_data(arr, n);

        printf("Data size: %d\n", n);
        measure_performance(insertion_sort, arr, n, "Insertion Sort");
        measure_performance(shell_sort, arr, n, "Shell Sort");
        measure_performance(bubble_sort, arr, n, "Bubble Sort");
        measure_performance(selection_sort, arr, n, "Selection Sort");
        measure_performance(heap_sort, arr, n, "Heap Sort");
        measure_performance_for_recursive(merge_sort, arr, n, "Merge Sort");
        measure_performance_for_recursive(quick_sort, arr, n, "Quick Sort");
        measure_performance(radix_sort, arr, n, "Radix Sort");

        free(arr);
        printf("\n");
    }

    return 0;
}
