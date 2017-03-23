#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <stdio.h>
#define FILELEN 80

int main(void)
{
	int fd = -1;
	char buf[] = "quick brown fox jumps over the lazy dog";
	char *ptr = NULL;
	
	fd = open("mmap.txt", O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
	if(fd < 0){
		perror("mmap.txt");
		return -1;
		
	}
	lseek(fd,FILELEN-1, SEEK_SET);
	write(fd, 'a',1);
	
	ptr = (char*)mmap(NULL, FILELEN, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if(ptr == MAP_FAILED){
		perror("map failed");
		close(fd);
		return -1;
	}
	memcpy(ptr+16, buf, strlen(buf));
	munmap(ptr, FILELEN);
	close(fd);
	return 0;
		
	
}