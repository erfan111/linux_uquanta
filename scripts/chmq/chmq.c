#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

int main(int argc, char **argv)
{

    int i, pid, res, policy;
    struct sched_param param;
    param.sched_priority = 0xC3509C40; // 50-40
    pid = getpid();
    policy = sched_getscheduler(pid);
    printf("policy = %d\n", policy);
    res = syscall(144, pid, 7, &param);
    printf("set sched returned %d (%d)\n", res, errno);
    res = execvp(argv[1], argv+1);
    printf("exec returned %d\n", res);
    //errexec(argv[0]);

    return 0;
}
