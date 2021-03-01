#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <sched.h>
#include <sys/time.h>

#define MAXWORK 5

int work[MAXWORK];  // work to be done
int nitems = 0;  // number of items in the queue
int nextput = 0;  // producer will place number # at work[nextput]
int nextget = -1;  // consumer will obtain next # at work[nextget]
int done = 0;  // value 1 signals producer exceeded dim
int pwork;  // work done by producer
int *cwork;  // work done by the consumers
int nthreads;  // number of threads
int dim;
double* roots;

static int idx = 0;

void next(int *m)
{
    (*m)++; 
    if (*m >= MAXWORK) {
        *m = 0;
    }
}

void putwork(int k)
{
    int put = 0;
    while (!put)  {  
        if (nitems < MAXWORK)  {
            #pragma omp critical
            {  
                work[nextput] = k;
                if (nitems == 0) {
                    nextget = nextput;
                }
                next(&nextput);
                nitems++;
                put = 1;
            }
        }
        else {
            sched_yield();
        }
   }
}

int getwork()
{
    int k, get = 0;
    while (!get) {
        // leave if producer exceeded dim and we've used all it produced
        if (done && nitems == 0) {
            return -1;
        }
        if (nitems > 0) {
            #pragma omp critical
            {  
                if (nitems > 0)  {
                    k = work[nextget];
                    next(&nextget);
                    nitems--;
                    if (nitems == 0) {
                        nextget = -1;
                    }
                    get = 1;
                }
            }
        }
        else {
            sched_yield();
        }
   }
   return k;
}

void dowork()
{  
   #pragma omp parallel  
   {
        int current_thread = omp_get_thread_num();
        int num;
        #pragma omp single
        {
            int i;
            nthreads = omp_get_num_threads();  
            cwork = (int*) malloc(nthreads * sizeof(int));
            for (i = 1; i < nthreads; i++) {
                cwork[i] = 0;
            }
        }
        #pragma omp barrier  

        if (current_thread == 0) {  // Producer
            pwork = 0;
            while (1)  {
                num = idx++;
                putwork(num);
                pwork++;
                if (idx == dim) {
                    done = 1;
                    break;
                }
            }
        }
        else {  // Consumer
            while (1)  {
                num = getwork();
                if (num == -1) {
                    break;
                }
                cwork[current_thread]++;
                #pragma omp atomic
                roots[num] += sqrt(num);
            }
        }
   }
}

int main(int argc, char **argv)
{ 
    struct timeval startwtime, endwtime;
    double arr_time;

    if (argc != 2) {
        printf("Usage: %s <dim>\n", argv[0]);
        exit(-1);
    }

    dim = atoi(argv[1]);
    roots = (double*) malloc(dim * sizeof(double));

    int i;
    gettimeofday(&startwtime, NULL);
    dowork();
    gettimeofday(&endwtime, NULL);
    arr_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6 + endwtime.tv_sec - startwtime.tv_sec);
    printf("Time taken = %f\n", arr_time);

    FILE* out = fopen("data.out", "w");
    for (i = 0; i < dim; i++) {
        fprintf(out, "sqrt(%d): %lf\n", i, roots[i]);
    }

    fprintf(out, "work done by producer:  %d\n", pwork);
    fprintf(out, "work done by consumers:\n");
    for (i = 1; i < nthreads; i++) {
        fprintf(out, "%d\n", cwork[i]);
    }

    return 0;
}
