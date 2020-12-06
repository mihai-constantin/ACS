#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <pthread.h>
#include <errno.h>
#include "queue.h"

#define dim 100
int data[dim];
double ans[dim];

FILE *out;

/* global queue */
extern struct queue_struct thr_queue;

int queue_terminate_consumers(struct queue_struct *queue) {
    if ((queue == NULL) || (queue->valid != QUEUE_VALID)) {
        return EINVAL;
    }
    
    pthread_mutex_lock(&queue->qlock);
    queue->qexit = 1;

    /* wake-up any waiting consumers */
    pthread_cond_broadcast(&queue->worker_cv);
    pthread_mutex_unlock(&queue->qlock);
    return 0;
}

int get_work(struct q_work_struct* w, int idx) {
    if (idx >= dim) {
        return 0;
    }
    w->number = data[idx];
    w->idx = idx;
    return 1;
}

void* producer() {
    struct q_work_struct *ptr;
    int ret, idx = 0;

    /* obtain work, return when complete */
    while(1) {
        /* allocate a work structure */
        ptr = (struct q_work_struct *) malloc (sizeof(struct q_work_struct));
        if (ptr == NULL) {
            break;
        }
        /* create/obtain work and fill in the work structure */
        ret = get_work(ptr, idx);
        if (ret == 0) {
            free((void *)ptr);
            break;
        }
        /* queue up the work */
        if ( enqueue(&thr_queue, ptr) != 0 ) {
            fprintf(stderr, "enqueue error\n");
            exit(-1);
        }
        idx++;
    }
    return NULL;
}

void* consumer() {
    struct q_work_struct *ptr;
    while(1) {
        /* obtain the next work request */
        ptr = dequeue(&thr_queue);
        if ( ptr == NULL ) {
            fprintf(stderr, "dequeue() error\n");
            exit(-1);
        }
        
        /* process the work request */
        int x = ptr->number;
        int idx = ptr->idx;
        ans[idx] = sqrt(x);

        /* release memory for work request */
        free((void *)ptr);
    }
    return NULL;
}  

void process_tasks() {
    int i, ret, nconsumers = 4, max_queue_len = 5;
    pthread_t consumers[nconsumers];

    /* initialize the queue */
    if ( queue_init(&thr_queue, max_queue_len) != 0 ) {
        fprintf(stderr, "queue_init error\n");
        exit(-1);
    }

    /* create consumers threads */
    for (i = 1; i < nconsumers; i++) {
        ret = pthread_create(&consumers[i], NULL, consumer, NULL);
        if (ret != 0) {
            fprintf(stderr, "error: pthread_create\n");
            exit(-1);
        }
    }

    /* we are in the producer thread */
    producer();

    /* request the consumers terminate when all work is processed */
    if ( queue_terminate_consumers(&thr_queue) != 0 ) {
        fprintf(stderr, "dequeue() error\n");
        exit(-1);
    }

    /* wait for the consumers to terminate */
    for (i = 1; i < nconsumers; i++) {
        ret = pthread_join(consumers[i], NULL);
        if (ret != 0) {
            fprintf(stderr, "error: pthread_join\n");
            exit(-1);
        }
    }
}

int main(int argc, char const *argv[])
{ 
    out = fopen("data.out", "w");
    for (int i = 0; i < dim; i++) {
        data[i] = i;
    }
    process_tasks();
    for (int i = 0; i < dim; i++) {
        fprintf(out, "sqrt(%d): %lf\n", i, ans[i]);
    }

    return 0;
}
