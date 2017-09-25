#ifndef METODOS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>


#define METODOS_H

#define FALSE           0
#define TRUE            1
#define LINE_LEN        80
#define MAX_ARGS        64
#define MAX_ARG_LEN     64
#define MAX_PATHS       64
#define MAX_PATH_LEN    96
#define WHITESPACE      " .,\t&"
#define STD_INPUT       0
#define STD_OUTPUT      1

#ifndef NULL
#define NULL    0
#endif

static char commandInput = '\0';
static int buf_chars = 0;
static char *pathv[MAX_PATHS];
static char commandLine[LINE_LEN];

struct command_t {
        char *name;
        int argc;
        char *argv[MAX_ARGS];
};

struct command_t command;

void limparTela();
void self();
void mudarDir();
int verifCmdInterno();
int executarCmd();
int processarCmdPipe(int i);
int processarCmdSaidaArq(int i);
int processarCmdEntradaArq(int i);
int processarCmd();
void iniciarShell();

void imprimirPrompt();
void msgBoasVindas();
int lerCmd(char *commandLine, char *commandInput);
int analisarCmd(char *commandLine, struct command_t *command);
char * procurarCaminho(char **, char **);
int analisarCaminho(char **);
int exeCmdEntradaArq(char *, char **, char *);
int exeCmdSaidaArq(char *, char **, char *);
void exeCmdPipe(char **, char  **, char *, char *);

#endif
