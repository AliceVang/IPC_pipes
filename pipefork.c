#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100
#define READ_END 0
#define WRITE_END 1

int main(void){
	char parent_write[BUFFER_SIZE] = "I am your daddy! and my name is";
	char parent_read[BUFFER_SIZE];
	
	char child_write[BUFFER_SIZE] = "Daddy, my name is";
	char child_read[BUFFER_SIZE];

	pid_t pid;

	int parent_fd[2];
	int child_fd[2];

	if(pipe(parent_fd) == -1){
		fprintf(stderr,"Error: parent pipe failed.\n");
		return 1;
	}

	if(pipe(child_fd) == -1){
		fprintf(stderr, "Error: child pipe failed.\n");
		return 1;
	}

	pid = fork();

	if(pid < 0){
		fprintf(stderr, "Error: fork failed.\n");
		return 1;
	}

	if(pid > 0){ // parent process
		close(parent_fd[READ_END]);	// close the unused end of the parent pipe
		close(child_fd[WRITE_END]);	// close child write pipe end

		write(parent_fd[WRITE_END], parent_write, strlen(parent_write)+1); // write to the parent pipe
		close(parent_fd[WRITE_END]); // close the write end of the parent pipe after writing
		
		read(child_fd[READ_END], child_read, BUFFER_SIZE);
		printf("%s %d\n", child_read, getpid());
		fflush(stdout);
		close(child_fd[READ_END]); // close after reading

		int status;
		waitpid(pid, &status, 0);
		if(WIFEXITED(status)){
			// successful child exit
		} else {
			fprintf(stderr, "Error: child terminatation unsuccessful.\n");
		}

	} else { //child process
		close(child_fd[READ_END]);
		close(parent_fd[WRITE_END]); // close unused end of the pipe

		read(parent_fd[READ_END], parent_read, BUFFER_SIZE);
		printf("%s %d\n", parent_read, getpid());
		fflush(stdout);

		write(child_fd[WRITE_END], child_write, strlen(child_write)+1);
		close(child_fd[WRITE_END]);
		
		close(parent_fd[READ_END]);
	}
	return 0;
}
