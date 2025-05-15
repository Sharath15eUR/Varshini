#include <stdio.h>
#include <stdbool.h>

// Function to search for a key in a sorted 2D matrix
bool searchMatrix(int n, int matrix[n][n], int key) {
    int row = 0;
    int col = n - 1;

    // Searching using the concept of Binary search in 2D Array
    while (row < n && col >= 0) {
        if (matrix[row][col] == key) {
            return true; // Key found
        } else if (matrix[row][col] > key) {
            col--; // Move left
        } else {
            row++; // Move down
        }
    }

    return false; // Key not found
}

int main() {
    int n, key;

    // Input matrix size
    printf("Enter the size of the matrix (n x n): ");
    scanf("%d", &n);

    int matrix[n][n];

    // Input matrix elements
    printf("Enter the elements of the matrix (each row and column in increasing order):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    // Input the key to search
    printf("Enter the key to search: ");
    scanf("%d", &key);

    // Search and display result
    if (searchMatrix(n, matrix, key)) {
        printf("Key %d found in the matrix.\n", key);
    } else {
        printf("Key %d not found in the matrix.\n", key);
    }

    return 0;
}

