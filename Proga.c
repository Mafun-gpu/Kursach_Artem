#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void execute_command(char *command){
	pid_t pid = fork();
	if (pid==0){
		execlp("sh", "sh", "-c", command, NULL);
		exit(EXIT_FAILURE);
	} else if (pid > 0){
		wait(NULL);
	} else {
		perror("fork failed");
	}
}
int main() {
	char command[256];
	while (1) {
		printf("command> ");
		if (fgets(command, sizeof(command),stdin)==NULL)break;
		command[strcspn(command, "\n")] = 0;
		if (strcmp(command, "exit")==0) {
			break;
		} else {
			execute_command(command);
		}
	}
	return 0;
}
