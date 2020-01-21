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
    int i;
    struct sched_param param;
    int policy = sched_getscheduler(getpid());
    pid_t p = getpid();
    param.sched_priority = 0xffffffff;
    printf("policy = %d\n", policy);
    i = syscall(144, atoi(argv[1]), 7, &param);
    printf("set sched returned %d (%d)\n", i, errno);
    for(i=0;i < 10000000000;i++)
    {
        //if(!(i%10000))
	  //  printf("%d\n", i);
    }
    return 0;

}
