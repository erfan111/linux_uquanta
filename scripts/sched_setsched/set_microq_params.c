#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <errno.h>
#include <sys/syscall.h>
#include <stdlib.h>

#define __NR_SYS_MICROQ_GETPARAMS 436
#define __NR_SYS_MICROQ_SETPARAMS 437

#define period_us   40
#define runtime_us  20

int main(int argc, char **argv)
{
    int i, pid, res, policy;
    struct sched_param param;
    unsigned int curr_period = 0, curr_runtime = 0, user_period, user_runtime;
    param.sched_priority = 0xFFFFFFFF; //  0xC3509C40; // 50-40

    if(argc < 4)
    {
        printf("Usage: ./set_microq_params PERIOD RUNTIME PID1 [PID2 ...]/n");
        exit(0);
    }
    user_period = atoi(argv[1]);
    user_runtime = atoi(argv[2]);
    for(i=3; i < argc;i++)
    {
        pid = atoi(argv[i]);
        policy = sched_getscheduler(pid);
        res = syscall(144, pid, 7, &param);
        printf("(%d) set scheduler from %d to %d\n", res, policy, 7);
        res = syscall(__NR_SYS_MICROQ_GETPARAMS, pid, &curr_period, &curr_runtime);
        printf("(%d - %d) Current period = %u, runtime = %u\n", res, errno, curr_period, curr_runtime);
        res = syscall(__NR_SYS_MICROQ_SETPARAMS, pid, period_us, runtime_us);
        printf("(%d - %d) set period = %u, runtime = %u\n", res, errno, user_period, user_runtime);
    }
    return 0;

}

