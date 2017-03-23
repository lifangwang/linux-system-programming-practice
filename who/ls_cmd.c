#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void do_ls(char[]);
int main(int argc, char* argv[]){
	if(argc == 1){
		do_ls(".");
		
	}else{
		while(--argc){
			printf("%s:\n", *++argv);
			do_ls(*argv);
		}
	}
}

void do_ls(char* path){
	DIR* dir_ptr;
	struct dirent* direntp;
	if((dir_ptr = opendir(path)) == NULL){
		fprintf(stderr,"can't open dir %s\n", path);
		
	}else{
		while((direntp=readdir(dir_ptr)) != NULL){
			printf("\t%s\n", direntp->d_name);
		}
		closedir(dir_ptr);
	}
}