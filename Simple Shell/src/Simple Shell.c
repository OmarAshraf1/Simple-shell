/*
 ============================================================================
 Name        : Simple.c
 Author      : Omar
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#define ARG_MAX 256     // Maximum number of arguments in a command
#define MAX_LINE_LENGTH ARG_MAX * 256   // Maximum number of characters in a command


int backgroundProcess  ; //Flag for background process

//Read command as string and return it in char array
char *ReadCommand(){
	char *input = malloc(sizeof(char) *MAX_LINE_LENGTH);

	int i=0 ; //to access array
	//check every char for a new line or end of file
	while(1){
		input[i] = getchar();
		if(input[i] == '\n' || input[i] == EOF){
			//to refer that command finished
			input[i] = '\0' ;
			//End of command
			break ;
		}
		i++ ;
	}


	return input ;
}
//split the user input , to store required input only
char **SplitCommand(char *input){
	char **command = malloc(sizeof(char *) * ARG_MAX);
	    int i = 0;

	    // Split line into tokens according to spaces
	    //so we have every token in each array index
	    //so command is at index 0 and its arguments are in the different next indices

	    char *split = strtok(input, " ");
	    while (split != NULL) {     // Looping through tokens to put them in args
	        command[i++] = split;
	        split = strtok(NULL, " ");
	    }

	    // Check for background process flag
	    if (strcmp(command[i - 1], "&") == 0) {
	        backgroundProcess = 1;
	        command[i - 1] = NULL;   // Remove that flag
	    }

	    return command;
}
//Event handler function
void handler(){

	 FILE *f;
	 f = fopen("logger.log", "a");
	 fprintf(f, "Child process was terminated\n");
	 fclose(f);

}
void Execute(char ** command){


	//if null take another command
	if(command[0] == NULL){
		return;
	}
	int child_status ;
	//if command is exit
	if(strcmp(command[0],"exit") == 0){
		free(command); //free memory of command
		//kill parent process
		kill(getppid(), SIGKILL);
		exit(0);
	}
	//create a child process
	pid_t pid  = fork() ;
	if(pid < 0) {//if child process not successfully created
		//error
		 perror("child process not successfully created\n");
	}
	else if (pid == 0){ //if we are in child process
        int status_code = execvp(command[0], command);
        //if process can not be executed
        if(status_code<0){

        	printf("Cannot execute command\n");
        	exit(1);

        }

	}
	else{   //we are in parent process

		//So we wait on child process if it is not a back ground process
		if(!backgroundProcess){
			waitpid(pid,&child_status,0) ;
		}

	}
}
int main(void) {
	//send signal to parent process that child process is finished , so we log it in log file

		//call signal
	signal(SIGCHLD, handler);

	//clear file
	FILE *f;
	f = fopen("logger.log", "w");
	fclose(f);

	while(1){



		backgroundProcess = 0;
		printf(">> ");

		char *command = ReadCommand();           // Reading command line
		char **args = SplitCommand(command);     // Splitting command line into arguments
		Execute(args);

	}



}












