#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5


void *
perform_work(void *arguments)
{
    int index = *((int *)arguments);

    printf("THREAD %d\n", index);

    return NULL;
}

int
main(void)
{
    pthread_t threads[NUM_THREADS];
  
    //create all threads one by one
    for (int i = 0; i < NUM_THREADS; i++) {
        int ret;

        printf("IN MAIN: Creating thread %d.\n", i);

        ret = pthread_create(&threads[i], NULL, perform_work, &i);
        assert(!ret);

        printf("IN MAIN: Created thread %d.\n", i);

        ret = pthread_join(threads[i], NULL);
        assert(!ret);
    }

    printf("IN MAIN: All threads are created.\n");

    return 0;
}

