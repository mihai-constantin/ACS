#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <unistd.h>

#define QUEUE_SIZE 5
char queue[QUEUE_SIZE];
int front = 0, rear = 0;
int items = 0; /* number of items in queue */
int done = 1; /* show that the input file is finished to read */

pthread_mutex_t mutex;
pthread_cond_t item_available;
pthread_cond_t space_available;

void* producer_thread(); // producer thread function
void* consumer_thread(); // consumer thread function

int main(int argc, char const *argv[])
{
    int ret;
    pthread_t producer;
    pthread_t consumer;

    ret = pthread_create(&producer, NULL, producer_thread, NULL);
    if (ret != 0) {
        fprintf(stderr, "Producer thread creation failed!");
        exit(-1);
    }
    ret = pthread_create(&consumer, NULL, consumer_thread, NULL);
    if (ret != 0) {
        fprintf(stderr, "Consumer thread creation failed!");
        exit(-1);
    }

    ret = pthread_join(producer, NULL);
    if (ret != 0) {
        fprintf(stderr, "Producer thread join failed!");
        exit(-1);
    }
    ret = pthread_join(consumer, NULL);
    if (ret != 0) {
        fprintf(stderr, "Consumer thread join failed!");
        exit(-1);
    }
    return 0;
}

void* producer_thread() {
    FILE *in = fopen("data.in", "r");
    char c = getc(in);
    while(c != EOF) {
        sleep(1);
        pthread_mutex_lock(&mutex);

        // printf("[Producer before while] front<%d> rear <%d> items <%d>\n", front, rear, items);
        while(items >= QUEUE_SIZE) {
            pthread_cond_wait(&space_available, &mutex);
        }
        // printf("[Producer after while] front<%d> rear <%d> items <%d>\n", front, rear, items);
        
        queue[front] = c;
        front++;
        if (front == QUEUE_SIZE) {
            front = 0;
        }
        items++;
        printf("[Producer] character write to queue: <%c>\n", c);
        pthread_cond_signal(&item_available);
        
        pthread_mutex_unlock(&mutex);

        sleep(1);
        c = getc(in);
    }

    pthread_mutex_lock(&mutex);
    done = 0;
    pthread_cond_signal(&item_available);
    pthread_mutex_unlock(&mutex);

    fclose(in);
    pthread_exit(0);
}

void* consumer_thread() {
    FILE *out = fopen("data.out", "w");
    while(done != 0) {
        pthread_mutex_lock(&mutex);

        // printf("[Consumer before while] front<%d> rear <%d> items <%d>\n", front, rear, items);
        while(items <= 0 && done != 0) {
            pthread_cond_wait(&item_available, &mutex);
        }
        printf("[Consumer after while] front<%d> rear <%d> items <%d>\n", front, rear, items);

        if (items) {
            char c = queue[rear];
            rear++;
            if (rear == QUEUE_SIZE) {
                rear = 0;
            }
            items--;
            printf("[Consumer] character read from queue: <%c>\n", c);
            fprintf(out, "%c", c);
            pthread_cond_signal(&space_available);
        }
      
        pthread_mutex_unlock(&mutex);
    }

    fclose(out);
    pthread_exit(0);
}
