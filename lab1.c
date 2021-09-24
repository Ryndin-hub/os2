#include <stdio.h>
#include <pthread.h>

#define PTHREAD_CREATE_SUCCESS 0
#define EXIT_ERROR 1
#define EXIT_SUCCESS 0
#define NUM_OF_LINES 10

void *print_lines(void *arg) {
    char *line = (char*) arg;
    for (int i = 0; i < NUM_OF_LINES; i++) {
        printf("%s\n",line);
    }
    return NULL;
}

int main() {
    pthread_t thread;
    int pthread_create_result = pthread_create(&thread, NULL, print_lines, "child");
    if (pthread_create_result != PTHREAD_CREATE_SUCCESS) {
        perror("Unable to create thread");
        exit(EXIT_ERROR);
    }
    print_lines("parent");
    pthread_exit(&thread);
    return EXIT_SUCCESS;
}
