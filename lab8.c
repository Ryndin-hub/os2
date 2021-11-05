#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_STEPS 200000000
#define SUCCESSFUL_RESULT 0

struct thread_data {
    int index;
    int numOfThreads;
    double piPart;
};

void *calculate_pi_thread(void *param) {
    struct thread_data *data = (struct thread_data *) param;

    int index = data->index;
    int numOfThreads = data->numOfThreads;

    double pi = 0;
    int i;

    for (i = index; i < NUM_STEPS ; i += numOfThreads) {
        pi += 1.0/(i*4.0 + 1.0);
        pi -= 1.0/(i*4.0 + 3.0);
    }
    pi = pi * 4.0;

    data->piPart = pi;
}

int main(int argc, char **argv) {
    if (argc != 2){
        printf("Wrong number of arguments\n");
        return EXIT_FAILURE;
    }

    char *end;
    int numOfThreads = strtol(argv[1], &end, 10);

    if (numOfThreads <= 0){
        printf("Wrong number of threads\n");
        return EXIT_FAILURE;
    }
    printf("Using %d threads\n", numOfThreads);

    pthread_t threads[numOfThreads];
    struct thread_data threadData[numOfThreads];
    for (int i = 0; i < numOfThreads; i++){
        threadData[i].index = i;
        threadData[i].numOfThreads = numOfThreads;
        int pthreadCreateResult = pthread_create(&threads[i], NULL, calculate_pi_thread, &threadData[i]);
        if (pthreadCreateResult != SUCCESSFUL_RESULT) {
            perror("Unable to create thread\n");
            pthread_exit(NULL);
        }
    }

    double sum = 0;
    for (int i = 0; i < numOfThreads; i++){
        int pthreadJoinResult = pthread_join(threads[i], NULL);
        if (pthreadJoinResult != SUCCESSFUL_RESULT){
            perror("Unable to join thread\n");
            pthread_exit(NULL);
        }
        sum += threadData[i].piPart;
    }
    printf("pi done - %.15g\n", sum);
    printf("compare - 3.14159265358979\n");

    return EXIT_SUCCESS;
}
