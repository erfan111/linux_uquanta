#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sched.h>
#include <math.h>
#include <errno.h>

#define NUM_THREADS 100
#define RUNTIME 40

void* do_work(void *threadid)
{
    struct timeval  tv1, tv2;
    int tid = (int) threadid, yres;
    u_int32_t counter = 0;
    printf("Thread %d starting\n", tid);
    double kNumber = 2350845.545, diff = 0;
    gettimeofday(&tv1, NULL);
    while(1)
    {
        gettimeofday(&tv1, NULL);
        gettimeofday(&tv2, NULL);
        diff = 0;
        while(diff <= RUNTIME)
        {
            for (int i = 0; i < 5; ++i) {
                double v = sqrt(i * kNumber);
            }
            counter++;
            gettimeofday(&tv2, NULL);
            diff = ((double) (tv2.tv_usec - tv1.tv_usec) + (double) (tv2.tv_sec - tv1.tv_sec)*1000000);
            // printf("(%d) elapsed %f, ctr = %d\n", tid, diff, counter);
        }
        if(diff > 2*RUNTIME)
            printf("(%d) elapsed %f, ctr = %d, yielding!\n", tid, diff, counter);
        yres = sched_yield();
        if(yres < 0)
            printf("(%d) warning! returned %d (%d)\n", tid, yres, errno);

    }
}

int main(int argc, char** argv)
{
    pthread_t threads[NUM_THREADS];
    u_int32_t args[NUM_THREADS];
    int rc;
    long t;
    for(t=0; t < NUM_THREADS; t++){
       printf("In main: creating thread %ld\n", t);
       args[t] = t;
       rc = pthread_create(&threads[t], NULL, do_work, (void *)args[t]);
       if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
       }
    }

    pthread_exit(NULL);
}