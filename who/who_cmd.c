#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

#define SHOWHOST
void show_info(struct utmp*);
void show_time(long);
int main(int argc, char* argv[])
{
	struct utmp current_record;
	int utmpfd;
	int reclen = sizeof(current_record);
	
	if((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1){
		perror(UTMP_FILE);
		exit(1);
		
		
	}
	
	while(read(utmpfd, &current_record,reclen) == reclen){
		show_info(&current_record);
		
	}
	close(utmpfd);
	return 0;
}

void show_info(struct utmp* record){
	if(record->ut_type != USER_PROCESS)
		return;
	printf("%-8.8s %-8.8s   ", record->ut_name, record->ut_line);
	show_time(record->ut_time);
	#ifdef SHOWHOST
	if(record->ut_host)
		printf(" (%s)", record->ut_host);
	#endif
	printf("\n");
	
}

void show_time(long timeval){
	char* cp;
	cp = ctime(&timeval);
	printf("%12.12s" , cp+4);
}