#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <errno.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <pthread.h>

#define __NR_SYS_MICROQ_GETPARAMS 436
#define __NR_SYS_MICROQ_SETPARAMS 437

#define period_us 40
#define runtime_us 20


int thread_func(void)
{
	int policy;
	printf("child: created with pid %d, ppid %d\n",
		getpid(), getppid());
	policy = sched_getscheduler(getpid());
	printf("child %d policy is %d\n", getpid(), policy);
	return 0;
}

int main(int argc, char *argv[])
{
	pid_t child[10];
	pthread_t threads[10];
	int i, pid, res, policy, stats;
	struct sched_param param;
	unsigned int curr_period = 0, curr_runtime = 0, user_period,
		     user_runtime;
	param.sched_priority = 0xFFFFFFFF; //  0xC3509C40; // 50-40

	printf("main: pid %d, ppid %d\n", getpid(), getppid());

    res = syscall(144, getpid(), 7, &param);
    printf("(%d) set scheduler from %d to %d\n", res, policy, 7);
    res = syscall(__NR_SYS_MICROQ_SETPARAMS, pid, period_us, runtime_us);
    printf("(%d - %d) set period = %u, runtime = %u\n", res, errno, period_us, runtime_us);

	for (i = 0; i < 10; i++) {
		res = pthread_create(&threads[i], NULL, &thread_func, NULL);
		if (res < 0) {
			perror("problem creating a child");
			return -1;
		}
	}
	for (i = 0; i < 10; i++) {
		pthread_join(threads[i], NULL);
	}
	// wait(&stats);
	printf("Hello World!\n");
	return EXIT_SUCCESS;
}