// Created by igor on 16/04/2021
// in T1_SHELL_C as shell.c 
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "Corzinha.h"
#include "Lista.h"
#include <limits.h>
#include <sys/wait.h>

#define ARG_MAX 3

typedef struct COMANDO{
    char* fullCommand;
    char* command;
    char** args;
    int nargs;
}tCommand;

void signalHandler(int sig){

    kill(0, SIGKILL);

}

void ctrlC(int sig){
    // Tem que ter acesso ao pid do filho.
    //kill( pid, SIGINT);
}

//Função para atribuir à vsh enquanto ela espera o processo de foreground terminar.
void atribuiSigactionForeground(struct sigaction* act){
    act->sa_handler = ctrlC;
    act->sa_flags = SA_RESTART;
    sigaction(SIGUSR1, act, NULL);
}

void atribuiSigaction(struct sigaction* act){
    act->sa_handler = signalHandler;
    act->sa_flags = SA_RESTART;
    sigaction(SIGUSR1, act, NULL);
    sigaction(SIGUSR2, act, NULL);
}

char * removePath(char * path){

    int i;
    for (i = strlen(path)-1; path[i] != '/'; i--);
    char * new = malloc(sizeof(char) * (strlen(path)-i));
    for (int j=i+1; j <= strlen(path); j++){
        new[j-(i+1)] = path[j];
    }
    return new;
}

void printLineCommand(){

    char cwd[PATH_MAX], user[NAME_MAX];
    getcwd(cwd, sizeof(cwd));
    char* func = removePath(cwd);
    printf(BOLD MAGENTA "afv:vsh "
           BOLD VERDE "%s "
           BOLD AZUL "%s > " RESET, getlogin(), func);
    free(func);

}

void preencheArgumentos(tCommand* cmd){

    char* save;

    cmd->nargs = 0;
    cmd->command = strtok_r(cmd->fullCommand, " ", &save);

    char    * arg = strtok_r(NULL, " ", &save),
            * all_args[ARG_MAX];

    // Find all args from command
    for (; arg; cmd->nargs++, arg=strtok_r(NULL, " ", &save))
        all_args[cmd->nargs] = arg;

    // Create arg vector to execute command.
    cmd->args = malloc(sizeof(char*) * (cmd->nargs + 2));
    cmd->args[0] = cmd->command;

    for (int i=1; i <= cmd->nargs; i++){
        cmd->args[i] = all_args[i-1];
    }

    cmd->args[cmd->nargs + 1] = NULL;

}

void printCommand(tCommand* cmd){

    printf(NORMAL MAGENTA "Comando inteiro:\n" RESET "%s\n", cmd->fullCommand);
    printf(NORMAL AZUL "Nome do comando:" RESET " %s\n", cmd->command);
    printf(NORMAL AMARELO "Argumentos:\n" RESET);
    for (int i=0; i < cmd->nargs+2; i++){
        printf("Arg[%d]: %s\n", i, cmd->args[i]);
    }
    printf("\n\n");
}

void freeCommandArgs(tCommand* cmd) {
    free(cmd->args);
}

void freeCommand(tCommand* cmd){
    freeCommandArgs(cmd);
    free(cmd);
}

void foreground(tCommand cmd[5]){

    int pid = fork();
    if(pid == 0){
        sigset_t sigset;
        sigemptyset(&sigset);
        sigaddset(&sigset, SIGUSR1);
        sigaddset(&sigset, SIGUSR2);
        if(sigprocmask(SIG_BLOCK, &sigset, NULL))
            perror("Erro na criação da sigprocmask\n");
        if(execvp(cmd[0].command, cmd[0].args) == -1){
            printf("Da um comando válido filhx da pute\n");
            exit(0);
        }
        sigprocmask(SIG_UNBLOCK, &sigset, NULL);

    }
    else{
        //Inicia o controle do tratamento de sinal para o CTRL-C
        waitpid(pid, NULL, 0);
        //Termina o tratamento de sinal do CTRL-C
    }

}

void liberaPipes(int pipes[][2], int type, int qtd) {

    for (int k = 0; k < qtd; k++) close(pipes[k][type]);

}

void background(tCommand cmd[5], int qtdCmds, Lista* list){

    int BACKGROUND = fork();

    if(BACKGROUND == 0){

        struct sigaction act;

        atribuiSigaction(&act);

        int newSession = setsid();

        if(newSession == -1){ perror("Erro na criação de uma nova sessão"); exit(1);}

        int qtdPipes = qtdCmds-1;
        int fd[qtdPipes][2];

        for(int j = 0; j<qtdPipes; j++)
            if(pipe(fd[j]) < 0){ printf("Erro ao abrir pipe\n"); exit(1); }

        for (int j = 0; j < qtdCmds; j++) {
            int pid = fork();
            if (pid == 0) {

                if (j == 0) {
                    dup2(fd[j][1], STDOUT_FILENO);
                } else if (j == qtdPipes) {
                    dup2(fd[j - 1][0], STDIN_FILENO);
                } else {
                    dup2(fd[j - 1][0], STDIN_FILENO);
                    dup2(fd[j][1], STDOUT_FILENO);
                }

                // Libera os todos os pipes
                liberaPipes(fd, 0, qtdPipes);
                liberaPipes(fd, 1, qtdPipes);

                if(execvp(cmd[j].command, cmd[j].args) == -1) {
                    printf("Da um comando válido filhx del pute\n");
                    exit(0);
                }
            } else {
                if(j < qtdPipes) close(fd[j][1]);
                int status;
                waitpid(pid, &status, 0);
                if(status == 10 || status == 12) raise(SIGUSR1);
            }
        }

        liberaPipes(fd, 0, qtdPipes);  // Libera todos pipes de leitura
        for(int j =0; j<qtdCmds; j++) freeCommandArgs(&cmd[j]);
        //Termina o filho.
        exit(0);
    }
    else insereLista(list, BACKGROUND);

}

void defineGround(tCommand cmd[5], int qtdCmds, Lista* list){

    if(qtdCmds < 2) foreground(cmd);
    else background(cmd, qtdCmds, list);

}

int readLine(Lista* list){

    tCommand cmd[5];
    int qtdCmds = 0;

    char* command_line, * save;
    size_t bufsize = LINE_MAX;
    command_line = (char*) malloc(bufsize * sizeof(char));
    getline(&command_line, &bufsize, stdin);
    command_line[strlen(command_line)-1] = 0;

    cmd[qtdCmds].fullCommand = strtok_r(command_line, "|", &save);

    while (cmd[qtdCmds].fullCommand){
        if(strcmp(cmd[qtdCmds].fullCommand, "armageddon") == 0){
            armageddon(list);
            free(command_line);
            return 0;
        }
        else if(strcmp(cmd[qtdCmds].fullCommand, "liberamoita") == 0){
            liberaMoita(list);
            free(command_line);
            return 1;
        }
        preencheArgumentos(&cmd[qtdCmds]);
        qtdCmds++;
        cmd[qtdCmds].fullCommand = strtok_r(NULL, "|", &save);
    }

    defineGround(cmd, qtdCmds, list);

    free(command_line);
    for(int j =0; j<qtdCmds; j++) {
        freeCommandArgs(&cmd[j]);
    }
    return 1;

}

void run_shell(Lista* list) {

    do printLineCommand();
    while (readLine(list));

}