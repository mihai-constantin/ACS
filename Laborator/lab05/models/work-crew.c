/* example structure for the Boss-Worker parallel programming model
 * see Thread Time: The Multithreaded Programming Guide
 * Scott J.Norton and Mark D.DiPasquale
 * 1997, Prentice Hall (www.prenhall.com)
 * ISBN: 0-13-190067-6
 * adapted by Bogdan Costinescu, march 1999
 */
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <malloc.h>
#include <time.h>

#include "queue.h"

#define dim 10
int a[dim][dim];
int b[dim][dim];
int c[dim][dim];

FILE *out;

/* global queue */
extern struct queue_struct thr_queue;

void check_error(int code, char *generator) {
  if(code != 0) {
    fprintf(stderr, "error: %s\n", generator);
    exit(-1);
  }
}

int queue_terminate_workers(struct queue_struct *queue) {
  if ((queue == NULL) || (queue->valid != QUEUE_VALID))
    return EINVAL;
  
  (void) pthread_mutex_lock(&queue->qlock);
  queue->qexit = 1;

  /* wakeup any waiting workers */
  (void) pthread_cond_broadcast(&queue->worker_cv);
  (void) pthread_mutex_unlock(&queue->qlock);

  return 0;
}

void queue_wait_workers(struct queue_struct *queue, int nthreads) {
  if ((queue == NULL) || (queue->valid != QUEUE_VALID))
    return;
  
  (void) pthread_mutex_lock(&queue->qlock);
  while (queue->worker_waiting != nthreads) {
    queue->boss_waiting++;
    (void) pthread_cond_wait(&queue->boss_cv, &queue->qlock);
    queue->boss_waiting--;
  }
  (void) pthread_mutex_unlock(&queue->qlock);
}

int optimal_number_of_threads(void) {
  return 8;
}

int optimal_queue_length(void) {
  return 16;
}

void process_tasks() {
#define MAX_THREADS 64
  int i, ret, nthreads, max_queue_len;
  pthread_t threads[MAX_THREADS];
  pthread_attr_t attr;
  void worker(), boss();

  /* initialization code */
  /* ... */

  /* determine the number of threads to create and max queue length */
  nthreads = optimal_number_of_threads();
  max_queue_len = optimal_queue_length();

  /* initialize the queue */
  if ( queue_init(&thr_queue, max_queue_len) != 0 ) {
    fprintf(stderr, "queue_init() error\n");
    exit(-1);
  }

  /* initialize any special thread attributes (if needed) */
  (void) pthread_attr_init(&attr);
  /* ... */

  /* create worker threads, inclusiv the boss ! */
  for (i = 0; (i < nthreads) && (i < MAX_THREADS); i++) {
    ret = pthread_create(&threads[i], &attr, (void *(*)())worker, NULL);
    check_error(ret, "pthread_create()");
  }
  (void) pthread_attr_destroy(&attr);

  /* we are in the boss thread */
  boss();

  /* request the workers terminate when all work is processed */
  if ( queue_terminate_workers(&thr_queue) != 0 ) {
    fprintf(stderr, "dequeue() error\n");
    exit(-1);
  }

  /* wait for the workers to terminate */
  for (i = 1; (i < nthreads) && (i < MAX_THREADS); i++) {
    ret = pthread_join(threads[i], NULL);
    check_error(ret, "pthread_join()");
  }

  /* perform any final processing and return */
}

int get_work(struct q_work_struct* w, int row) {
  if (row == dim) {
    return 0;
  }
  w->row = row;
  return 1;
}

void boss() {
  struct q_work_struct *ptr;
  int ret, row = 0;

  /* obtain work, return when complete */
  for ( ; ; ) {
    /* allocate a work structure */
    ptr = (struct q_work_struct *) malloc (sizeof(struct q_work_struct));
    if (ptr == NULL) {
      break;
    }
    
    /* create/obtain work and fill in the work structure */
    ret = get_work(ptr, row/dim);

    if (ret == 0) {
      free((void *)ptr);
      break;
    }

    /* queue up the work */
    if ( enqueue(&thr_queue, ptr) != 0 ) {
      fprintf(stderr, "enqueue() error\n");
      exit(-1);
    }
    row += dim;
  }
}

void worker() {
  struct q_work_struct *ptr;
  
  /* go into an infinite loop processing work received from
   * the work queue. If we are supposed to terminate, we
   * will never return from one of the calls to dequeue();
   */
  for ( ; ; ) {
    /* obtain the next work request */
    ptr = dequeue(&thr_queue);
    if ( ptr == NULL ) {
      fprintf(stderr, "dequeue() error\n");
      exit(-1);
    }
    
    /* process the work request */
    /* ... */
    int row = ptr->row;
    for (int j = 0; j < dim; j++) {
      c[row][j] = a[row][j] + b[row][j];
    }

    /* release memory for work request */
    free((void *)ptr);
  }
}  

int main()
{ 
  out = fopen("work-crew.out", "w");

  srand(time(NULL));
  for (int i = 0; i < dim; ++i) {
    for (int j = 0; j < dim; j++) {
      a[i][j] = rand() % 100;
      b[i][j] = rand() % 100;
    }
  }
  
  process_tasks();

  fprintf(out, "----- Matrix Addition -----\n");
  fprintf(out, "----- A -----\n");
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      fprintf(out, "%d ", a[i][j]);
    }
    fprintf(out, "\n");
  }
  fprintf(out, "\n");
  fprintf(out, "----- B -----\n");
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      fprintf(out, "%d ", b[i][j]);
    }
    fprintf(out, "\n");
  }
  fprintf(out, "\n");
  fprintf(out, "----- C -----\n");
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      fprintf(out, "%d ", c[i][j]);
    }
    fprintf(out, "\n");
  }

  return 0;
}
