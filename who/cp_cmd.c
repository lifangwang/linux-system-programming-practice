#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define BUFSIZE 1024
#define COPYMODE 0644

void oops(char*, char*);

int main(int argc, char* argv[])
{
	int in_fd, out_fd, n_chars;
	char buf[BUFSIZE];
	
	if((in_fd = open(argv[1], O_RDONLY)) == -1){
		oops("can't open ", argv[1]);
		
	}
	if((out_fd = creat(argv[2], COPYMODE)) == -1){
		oops("can't create ", argv[2]);
	}
	
	while((n_chars = read(in_fd, buf, BUFSIZE)) > 0){
		if(write(out_fd, buf, n_chars) != n_chars){
			oops("write error to ", argv[2]);
		}
	}
	if(n_chars == -1){
		oops("read error ", argv[1]);
	}
	if(close(in_fd) <0 || close(out_fd) <0)
		oops("close error", "");
	
}

void oops(char*s1, char* s2){
	fprintf(stderr, "error:%s", s1);
	perror(s2);
	exit(1);
}