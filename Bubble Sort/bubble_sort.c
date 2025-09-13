#include "hpm.h" // Include the performance counter library
#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int size = 500; // Increase size for larger workload
    int *arr = (int *)malloc(size * sizeof(int));

    // Populate the array with random numbers
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000; // Random numbers between 0 and 999
    }

    printf("Original array: \n");
    printArray(arr, size);

    /* Enable performance counters */
    hpm_init();

    printf("Sorting the array...\n");
    bubbleSort(arr, size);

    /* Print performance counter data */
    hpm_print();

    printf("Sorted array: \n");
    printArray(arr, size);

    free(arr); // Free the dynamically allocated memory
    return 0;
}
