#include <sched.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/syscall.h>
#include <stdlib.h>

#define PARENT_PRIORITY 5

int main(int argc, char **argv)
{
    int i, pid, res, policy;
    struct sched_param param;
    param.sched_priority = 0;//  0x75303A98;
    for(i=1; i < argc;i++)
    {
	pid = atoi(argv[i]);
        policy = sched_getscheduler(pid);
        printf("policy = %d\n", policy);
        res = syscall(144, pid, 0, &param);
        printf("set sched returned %d (%d)\n", res, errno);
        //for(i=0;i < 10000000000;i++)
        //{
           //if(!(i%10000))
	    //  printf("%d\n", i);
        //}
    }
    return 0;

}
