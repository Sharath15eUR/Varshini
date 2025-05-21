#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

int N; 

bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++)
        if (num % i == 0)
            return false;
    return true;
}

// Thread A
void* thread_A(void* arg) {
    int count = 0, num = 2, sum = 0;

    while (count < N) {
        if (is_prime(num)) {
            sum += num;
            count++;
        }
        num++;
    }

    printf("Sum of first %d prime numbers is: %d\n", N, sum);
    pthread_exit(NULL);
}

// Thread B
void* thread_B(void* arg) {
    time_t start = time(NULL);
    while (difftime(time(NULL), start) < 100) {
        printf("Thread 1 running\n");
        sleep(2);
    }
    pthread_exit(NULL);
}

// Thread C
void* thread_C(void* arg) {
    time_t start = time(NULL);
    while (difftime(time(NULL), start) < 100) {
        printf("Thread 2 running\n");
        sleep(3);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tA, tB, tC;

    printf("Enter N (number of prime numbers to sum): ");
    scanf("%d", &N);

    // Creation of threads
    pthread_create(&tA, NULL, thread_A, NULL);
    pthread_create(&tB, NULL, thread_B, NULL);
    pthread_create(&tC, NULL, thread_C, NULL);

    pthread_join(tA, NULL);
    pthread_join(tB, NULL);
    pthread_join(tC, NULL);

    return 0;
}
