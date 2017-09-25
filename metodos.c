#include "metodos.h"

void iniciarShell(){

	analisarCaminho(pathv);
	msgBoasVindas();


	while(TRUE) {
		imprimirPrompt();

		commandInput = getchar();
		if(commandInput == '\n') {
			continue;
		}
		else {
			lerCmd(commandLine, &commandInput);

			if((strcmp(commandLine, "exit") == 0) || (strcmp(commandLine, "quit") == 0))
				break;

			analisarCmd(commandLine, &command);

			if(verifCmdInterno() == 0) {
				command.name = procurarCaminho(command.argv, pathv);

				if(command.name == NULL) {
					printf("Erro!\n");
					continue;
				}

				processarCmd();
			}
		}
	}
}

void limparTela() {
	printf("\033[2J\033[1;1H");
}


void self() {
	printf("self...\n");
}


void mudarDir() {
	if (command.argv[1] == NULL) {
		chdir(getenv("HOME"));
	} else {
		if (chdir(command.argv[1]) == -1) {
			printf(" %s: Diretorio nao existe\n", command.argv[1]);
		}
	}
}


int verifCmdInterno() {

	if(strcmp("cd", command.argv[0]) == 0) {
		mudarDir();
		return 1;
	}
	if(strcmp("clear", command.argv[0]) == 0) {
		limparTela();
		return 1;
	}
	if(strcmp("self", command.argv[0]) == 0) {
		limparTela();
		return 1;
	}

	return 0;
}


int executarCmd() {

	int child_pid;
	int status;
	pid_t thisChPID;


	child_pid = fork();
	if(child_pid < 0 ) {
		fprintf(stderr, "Fork falhou: \n");
		return 1;
	}
	else if(child_pid==0) {
	
		execve(command.name, command.argv,0);
		printf("Processo-filho falhou\n");
		return 1;
	}
	else if(child_pid > 0) {


		do {
			thisChPID = waitpid(child_pid, &status, WUNTRACED | WCONTINUED);
            if (thisChPID == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

            if (WIFEXITED(status)) {
                return 0;
            } else if (WIFSIGNALED(status)) {
                printf("killed by signal %d\n", WTERMSIG(status));
            } else if (WIFSTOPPED(status)) {
                printf("stopped by signal %d\n", WSTOPSIG(status));
            } else if (WIFCONTINUED(status)) {
                printf("continued\n");
            }
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		return 0;
	}
	return 0;
}


int processarCmdPipe(int i) {
	char *argvA[5];
	char *argvB[5];
	char *nameA, *nameB;

	int ii;
	for(ii=0;ii<i;ii++) {
		argvA[ii] = command.argv[ii];
	}
	argvA[ii]=NULL;
	nameA = procurarCaminho(argvA, pathv);

	int j,jj=0;
	for(j=i+1; j<command.argc; j++) {
		argvB[jj] = command.argv[j];
		jj++;
	}
	argvB[jj]=NULL;
	nameB = procurarCaminho(argvB, pathv);

	int pid, status;
	fflush(stdout);

    switch ((pid = fork())) {
    case -1:
        perror("fork");
        break;
    case 0:
  
    	exeCmdPipe(argvA, argvB, nameA, nameB);
        break; 
    default:
        pid = wait(&status);
        return 0;
    }
    return 1;
}


int processarCmdSaidaArq(int i) {

	char *argv[5];
	char *commandName;
	int j;
	for(j=0; j<i; j++) {
		argv[j] = command.argv[j];
	}
	argv[j] = NULL;
	commandName = procurarCaminho(argv, pathv);

	return exeCmdSaidaArq(commandName, argv, command.argv[i+1]);
}


int processarCmdEntradaArq(int i) {
	char *argv[5];
	char *commandName;

	int j;
	for(j=0; j<i; j++) {
		argv[j] = command.argv[j];
	}
	argv[j] = NULL;
	commandName = procurarCaminho(argv, pathv);

	int pid, status;
	fflush(stdout);

    switch ((pid = fork())) {
    case -1:
        perror("fork");
        break;
    case 0:
    	exeCmdEntradaArq(commandName, argv, command.argv[i+1]);
        break;
    default:

        pid = wait(&status);
        return 0;
    }

	return 0;
}


int processarCmd() {

	int i;
	for(i=0;i<command.argc; i++) {
		if(strcmp(command.argv[i], ">") == 0) {
			return processarCmdSaidaArq(i);
		}
		else if(strcmp(command.argv[i], "<") == 0) {
			return processarCmdEntradaArq(i);

		}
		else if(strcmp(command.argv[i], "|") == 0) {
		    return processarCmdPipe(i);
		}
	}
	return executarCmd();
}

void msgBoasVindas() {
	printf("\nBem-vindo ao mini-shell RGB\n");
}


void imprimirPrompt() {
    char buffer[MAX_ARG_LEN];


    char defaultUser[] = "username";
    char* user = getenv("USER");
    if(user == 0){
        user = defaultUser;
    }
    strcpy(buffer,user);
    user = (char*)malloc(strlen(buffer)+1);
    if(user == NULL){
        printf("Impossivel alocar o nome de usuario.");
    }
    strcpy(user, buffer);

	printf("%s@cmd > ",user);
}


char * procurarCaminho(char **argv, char **dir) {
	char *result;
	char pName[MAX_PATH_LEN];
	if( *argv[0] == '/') {
		return argv[0];
	}
	else if( *argv[0] == '.') {
		if( *++argv[0] == '.') {
			 if(getcwd(pName,sizeof(pName)) == NULL)
				 perror("getcwd(): erro\n");
			 else {
				 *--argv[0];
				 printf(&result,"%s%s%s",pName,"/",argv[0]);
			 }
			 return result;
		}
		*--argv[0];
		if( *++argv[0] == '/') {
			if(getcwd(pName,sizeof(pName)) == NULL)
				perror("getcwd(): erro\n");
			else {
				asprintf(&result,"%s%s",pName,argv[0]);
			}
			return result;
		}
	}


	int i;
	for(i = 0 ; i < MAX_PATHS ; i++ ) {
		if(dir[i] != NULL) {
			asprintf(&result,"%s%s%s",  dir[i],"/",argv[0]);
			if(access(result, X_OK) == 0) {
				return result;
			}
		}
		else continue;
	}

	fprintf(stderr, "%s: comando nao encontrado\n", argv[0]);
	return NULL;
}

int analisarCaminho(char* dirs[]){
	int debug = 0;
	char* pathEnvVar;
	char* thePath;
	int i;

	for(i=0 ; i < MAX_ARGS ; i++ )
		dirs[i] = NULL;
	pathEnvVar = (char*) getenv("PATH");
	thePath = (char*) malloc(strlen(pathEnvVar) + 1);
	strcpy(thePath, pathEnvVar);

	char* pch;
	pch = strtok(thePath, ":");
	int j=0;

	while(pch != NULL) {
		pch = strtok(NULL, ":");
		dirs[j] = pch;
		j++;
	}


	if(debug){
		printf("Diretorios na variavel PATH\n");
		for(i=0; i<MAX_PATHS; i++)
			if(dirs[i] != '\0')
				printf("    Diretorio[%d]: %s\n", i, dirs[i]);
	}
}


int analisarCmd(char * commandLine, struct command_t * command) {
	int debug = 0;

	char * pch;
	pch = strtok (commandLine," ");
	int i=0;
	while (pch != NULL) {
		command->argv[i] = pch;
		pch = strtok (NULL, " ");
		i++;
	}
	command->argc = i;
	command->argv[i++] = NULL;


	if(debug) {
		printf("Stub: analisarCmd(char, struct);\n");
		printf("Array size: %i\n", sizeof(*command->argv));
		int j;
		for(j=0; j<i; j++) {
			printf("command->argv[%i] = %s\n", j, command->argv[j]);
		}
		printf("\ncommand->argc = %i\n", command->argc);

		if(command->argv[0] != NULL) {
			char **p;
			for(p = &command->argv[1]; *p != NULL; p++) {
				printf("%s\n", *p);
			}
		}
	}
	return 0;
}

int lerCmd(char * buffer, char * commandInput) {
	buf_chars = 0;


	while((*commandInput != '\n') && (buf_chars < LINE_LEN)) {
		buffer[buf_chars++] = *commandInput;
		*commandInput = getchar();
	}
	buffer[buf_chars] = '\0';

	return 0;
}


int exeCmdEntradaArq(char * commandName, char * argv[], char * filename) {
	int pipefd[2];

	if(pipe(pipefd)) {
		perror("pipe");
		exit(127);
	}

	switch(fork()) {
	case -1:
		perror("fork()");
		exit(127);
	case 0:
        close(pipefd[0]);  
        dup2(pipefd[1], 1);  
        close(pipefd[1]);  
 	   FILE * pFile;
 	   char mystring;

 	   pFile = fopen (filename , "r");
 	   if (pFile == NULL) perror ("Erro abrindo arquivo");
 	   else {

 		while ((mystring=fgetc(pFile)) != EOF) {
 				putchar(mystring); 
 			}
 	     fclose (pFile);
 	   }
 	  exit(EXIT_SUCCESS);

    default:

        close(pipefd[1]); 
        dup2(pipefd[0], 0);  
        close(pipefd[0]);  

        execve(commandName, argv, 0);
        perror(commandName);
        exit(125);

	}

	return 0;
}


int exeCmdSaidaArq(char * commandName, char * argv[], char * filename) {
	int def = dup(1);


    int file = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);
    if(file < 0)    return 1;

 
    if(dup2(file,1) < 0)    return 1;
    int pid;
    if( pid = fork() == 0) {
    	close(file);
    	close(def);
    	execve(commandName, argv,0);
    	return 0;
    }
    dup2(def, 1);
    close(file);
    close(def);
    wait(NULL);
 	close(file);
	return 0;
}


void exeCmdPipe(char *argvA[], char  *argvB[], char * nameA, char * nameB) {
	int pipefd[2];

	if(pipe(pipefd)) {
		perror("pipe");
		exit(127);
	}

	switch(fork()) {
	case -1:
		perror("fork()");
		exit(127);
	case 0:
        close(pipefd[0]); 
        dup2(pipefd[1], 1);  
        close(pipefd[1]);  
        execve(nameA, argvA, 0);
     
        perror(nameA);
        exit(126);
    default:

        close(pipefd[1]);  
        dup2(pipefd[0], 0);  
        close(pipefd[0]);  

        execve(nameB, argvB, 0);
        perror(nameB);
        exit(125);

	}
}
