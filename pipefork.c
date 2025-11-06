#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void){
	char write_size[BUFFER_SIZE] = "Hello World!\n";
	char read_size[BUFFER_SIZE];
	pid_t pid;

	int fd[2];
	if(pipe(fd) == -1){
		fprintf(stderr,"Error: pipe failed.\n");
		return 1;
	}

	pid = fork();

	if(pid < 0){
		fprintf(stderr, "Error: fork failed.\n");
		return 1;
	}

	if(pid > 0){
		close(fd[READ_END]);	// close the unused end of the pipe
		write(fd[WRITE_END], write_size, strlen(write_size)+1); // write to the pipe
		close(fd[WRITE_END]); // close the write end of the pipe
	} else {
		close(fd[WRITE_END]); // close the unused end of the pipe
		read(fd[READ_END], read_size, BUFFER_SIZE); // read from the pipe
		printf("read %s", read_size);
		
		close(fd[READ_END]);
	}

	return 0;
}
