#include <stdio.h>
#include <pthread.h>

#define PTHREAD_CREATE_SUCCESS 0
#define EXIT_ERROR 1
#define EXIT_SUCCESS 0

void *print_line(void *arg) {
    int* a = (int*) arg;
    printf("thread %d\n",*a);
    return NULL;
}

int main() {
    pthread_t thread[4];
    int a[4] = {1,2,3,4};
    for (int i = 0; i < 4; i++){
        int pthread_create_result = pthread_create(&thread[i], NULL, print_line, (void*) &a[i]);
        if (pthread_create_result != PTHREAD_CREATE_SUCCESS) {
            perror("Unable to create thread");
            exit(EXIT_ERROR);
        }
    }
    for (int i = 0; i < 4; i++){
        pthread_join(thread[i], NULL);
    }
    pthread_exit(NULL);
    return EXIT_SUCCESS;
}
