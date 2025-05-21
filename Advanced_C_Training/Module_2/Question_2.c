#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <signal.h>

int N;
volatile sig_atomic_t keep_running = 1;  


void handle_signal(int sig) {
    printf("\nSignal caught! But we won't terminate. Press Ctrl+C again to exit.\n");
}

bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++)
        if (num % i == 0)
            return false;
    return true;
}

//Thread A
void* thread_A(void* arg) {
    clock_t start_time = clock();  
    int count = 0, num = 2, sum = 0;

    while (count < N) {
        if (is_prime(num)) {
            sum += num;
            count++;
        }
        num++;
    }

    clock_t end_time = clock();  
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;  
    printf("Sum of first %d prime numbers is: %d\n", N, sum);
    printf("Thread A execution time: %.5f seconds\n", time_taken);

    pthread_exit(NULL);
}

// Thread B
void* thread_B(void* arg) {
    clock_t start_time = clock();
    time_t start = time(NULL);

    while (difftime(time(NULL), start) < 100 && keep_running) {
        printf("Thread 1 running\n");
        sleep(2);
    }

    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Thread B execution time: %.5f seconds\n", time_taken);
    pthread_exit(NULL);
}

// Thread C
    void* thread_C(void* arg) {
    clock_t start_time = clock();
    time_t start = time(NULL);

    while (difftime(time(NULL), start) < 100 && keep_running) {
        printf("Thread 2 running\n");
        sleep(3);
    }

    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Thread C execution time: %.5f seconds\n", time_taken);
    pthread_exit(NULL);
}

int main() {
    pthread_t tA, tB, tC;

    
    signal(SIGINT, handle_signal);

    printf("Enter N (number of prime numbers to sum): ");
    scanf("%d", &N);

    // Creation of threads
    pthread_create(&tA, NULL, thread_A, NULL);
    pthread_create(&tB, NULL, thread_B, NULL);
    pthread_create(&tC, NULL, thread_C, NULL);

   
    pthread_join(tA, NULL);
    pthread_join(tB, NULL);
    pthread_join(tC, NULL);

    printf("All threads completed.\n");

    return 0;
}
