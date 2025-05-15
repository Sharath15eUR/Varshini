#include <stdio.h>
#include <stdlib.h>

// Function to rearrange the array in-place using the concept of pointers.

void rearrangeEvenOdd(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        int *current = arr + i;

        // If current number is odd, look ahead for next even number
        if (*current % 2 != 0) {
            int j = i + 1;
            while (j < size && *(arr + j) % 2 != 0) {
                j++;
            }

            // If found an even number ahead, shift elements to the right and place even number at the index i in the array.
            if (j < size) {
                int evenVal = *(arr + j);
                for (int k = j; k > i; k--) {
                    *(arr + k) = *(arr + k - 1);
                }
                *(arr + i) = evenVal;
            }
        }
    }
}

int main() {
    int size;
    // Take input for the size of the array
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    // Memory Allocation
    int *arr = (int *)malloc(size * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Take input for the array elements
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < size; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", arr + i);
    }

    // Rearrange the array 
    // Arranging even numbers first, preserving the order
    rearrangeEvenOdd(arr, size);

    // Displaying the rearranged array
    printf("\nRearranged array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");

    // Free the dynamically allocated memory
    free(arr);

    return 0;
}
