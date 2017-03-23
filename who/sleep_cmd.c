#include <stdio.h>
#include <signal.h>

void wakeup(int);
main(){
	printf("about sleep a while\n");
	signal(SIGALRM, wakeup);
	alarm(5);
	pause();
	printf("wakeuped\n");
}

void wakeup(int signum){
	printf("signal recired %d\n", signum);
}