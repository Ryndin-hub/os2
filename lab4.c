#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define PTHREAD_CREATE_SUCCESS 0
#define PTHREAD_CANCEL_SUCCESS 0
#define EXIT_ERROR 1
#define EXIT_SUCCESS 0
#define SLEEP_TIME 2

void *print_lines() {
    while (1){
        printf("aaa\n");
    }
    return NULL;
}

int main() {
    pthread_t thread;
    int pthread_create_result = pthread_create(&thread, NULL, print_lines, NULL);
    if (pthread_create_result != PTHREAD_CREATE_SUCCESS) {
        perror("Unable to create thread");
        exit(EXIT_ERROR);
    }
    sleep(SLEEP_TIME);
    int pthread_cancel_result = pthread_cancel(thread);
    if (pthread_cancel_result != PTHREAD_CANCEL_SUCCESS) {
        perror("Unable to cancel thread");
        exit(EXIT_ERROR);
    }
    pthread_exit(NULL);
    return EXIT_SUCCESS;
}