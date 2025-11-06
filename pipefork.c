#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void){
	int fd[2];
	if(pipe(fd) == -1){
		fprintf(stderr,"Error: pipe failed.\n");
		return 1;
	}
}
