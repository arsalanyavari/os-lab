#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

#define NAME_LEN 16
#define TRUE 1

struct m_Proc
{
	char name[NAME_LEN];
	pid_t pid;
};


int main(void)
{
	struct m_Proc procl[200];
	int size;
	while (TRUE)
    {
		int ret = (int)syscall(548, procl);
		printf("Get %d\n", ret);
		printf("PID\t\tNAME\n");
		for(int i=0; i<ret; i++)
			printf("%d\t\t%s\n", procl[i].pid, procl[i].name);

		fflush(stdout);
		sleep(10);
	}
	return 0;
}
