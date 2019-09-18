#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


volatile int thread = 0;

int itemCount = 0;
int buf[BUFSIZ];

void
sleep_()
{
    int cur = thread;
    while (thread == cur);
}

void
wakeup()
{
    thread = (thread ? 0 : 1);
}

int
produceItem()
{
    static int n = 0;
    return n++;
}

void
consumeItem(int n)
{
    (void) n;
    /* nothing here */
}

void
putItemIntoBuffer(int item)
{
    buf[itemCount++] = item;
}

int
removeItemFromBuffer()
{
    return buf[--itemCount];
}

void *
producer() 
{
    int tm = 0;
    
    for (;;) {
        int item = produceItem();

        if (itemCount == BUFSIZ)
            sleep_();

        putItemIntoBuffer(item);

        if (clock() / 100 > tm) {
            tm = clock() / 100;
            printf("produced %d\n", item);
        }

        if (itemCount == 1)
            wakeup();
    }
    return NULL;
}

void *
consumer() 
{
    int tm = 0;

    for (;;) {
        if (itemCount == 0)
            sleep_();

        int item = removeItemFromBuffer();

        if (itemCount == BUFSIZ - 1)
            wakeup();

        if (clock() / 100 > tm) {
            tm = clock() / 100;
            printf("consumed %d\n", item);
        }
        consumeItem(item);
    }
    return NULL;
}

int
main(void)
{
    pthread_t cons_thread, prod_thread;

    pthread_create(&cons_thread, NULL, consumer, NULL);
    pthread_create(&prod_thread, NULL, producer, NULL);

    pthread_join(cons_thread, NULL);
}
