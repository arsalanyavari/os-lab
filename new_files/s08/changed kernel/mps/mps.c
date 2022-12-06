#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/string.h>

struct proccess {
    char name[TASK_COMM_LEN];
    pid_t pid;
};


SYSCALL_DEFINE1(mps, void*, array)
{
    struct proccess *procc = (struct proccess*)array;
    struct task_struct *task;
    int i=0;
    for_each_process(task)
    {   
        strncpy(procc[i].name, task->comm, 16);
        procc[i].pid = task->pid;
        i++;
    }	
    
	return (long)i;
}

