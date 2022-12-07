#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int main(void) {
	int i = 0 ;
	while (1){
		int ret = syscall(548, i);
		printf("Hello world %d\n", ret);
		fflush(stdout);
		sleep(2);
		i+=1;
	}
	return 0;
}
