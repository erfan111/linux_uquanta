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
    char str[20];
    u_int32_t params = 0;

    struct sched_param param;
    sprintf(str, "0x%s%s", argv[2],argv[1]);
    params = (u_int32_t) strtol(str, NULL, 0);
    printf("hex number is %s, %u, %lu\n", str, params, strtol("0xC3509C40", NULL, 0));
    param.sched_priority = params; //  0xC3509C40; // 50-40
    for(i=3; i < argc;i++)
    {
    	pid = atoi(argv[i]);
        policy = sched_getscheduler(pid);
        printf("policy = %d\n", policy);
        res = syscall(144, pid, 7, &param);
        printf("(%d) set sched returned %d (%d)\n", pid, res, errno);
        //for(i=0;i < 10000000000;i++)
        //{
           //if(!(i%10000))
	    //  printf("%d\n", i);
        //}
    }
    return 0;

}
