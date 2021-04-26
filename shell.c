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
    for (cmd->nargs; arg; cmd->nargs++, arg=strtok_r(NULL, " ", &save))
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

void freeComand(tCommand* cmd) {
    free(cmd->args);
}

int readLine2(Lista* list){
    tCommand cmd[5];
    int qtdCmds = 0;

    char* command_line, * save;
    size_t bufsize = LINE_MAX;
    command_line = (char*) malloc(bufsize * sizeof(char));
    getline(&command_line, &bufsize, stdin);
    command_line[strlen(command_line)-1] = 0;

    printf("\"%s\"\n", command_line);

    int temPipe = 0;
    for(int i=0; command_line[i] != 0; i++)
        if(command_line[i] == '|'){
            temPipe = 1;
            break;
        }

    cmd[qtdCmds].fullCommand = strtok_r(command_line, "|", &save);
    printf("PIPE COMMAND: '%s'\n", cmd[qtdCmds].fullCommand);
    while (cmd[qtdCmds].fullCommand){
        if(strcmp(cmd[qtdCmds].fullCommand, "armageddon") == 0){
            printf("SIM\n");
            free(command_line);
            return(0);
        }
        preencheArgumentos(&cmd[qtdCmds]);
        qtdCmds++;
        cmd[qtdCmds].fullCommand = strtok_r(NULL, "|", &save);
    }

    printf("TEM PIPE = %d\n", temPipe);

    if(temPipe == 0){
        int pid = fork();
        if(pid == 0){
            if(execvp(cmd[0].command, cmd[0].args) == -1){
                printf("Da um comando válido filha da puta\n");
                exit(0);
            }
        }
        else{
            waitpid(pid, NULL, 0);
        }
    }
    else{
        int BACKGROUND;

        BACKGROUND = fork();

        if(BACKGROUND == 0){
            printf("VOU CRIAR PIPES\n");

            setsid();

            int qtdPipes = qtdCmds-1;

            int fd[qtdPipes][2];

            for(int j = 0; j<qtdPipes; j++){
                if(pipe(fd[j]) < 0){
                    printf("Erro ao abrir pipe\n");
                    printf("I dont fell to good\n");
                    free(command_line);
                    return 1;
                }
            }
            printf("Sucesso ao abrir os %d pipes para os %d comandos\n", qtdPipes, qtdCmds);
            for (int j = 0; j < qtdCmds; j++) {
                int pid = fork();
                if (pid == 0) {
                    printf("Entrei no comando " BOLD VERMELHO "%s" RESET "\n", cmd[j].command);
                    if (j == 0) {
                        dup2(fd[j][1], STDOUT_FILENO);
                    } else if (j == qtdPipes) {
                        dup2(fd[j - 1][0], STDIN_FILENO);
                    } else {
                        dup2(fd[j - 1][0], STDIN_FILENO);
                        dup2(fd[j][1], STDOUT_FILENO);
                    }
                    for (int k = 0; k < qtdPipes; k++) {
                        close(fd[k][0]);
                        close(fd[k][1]);
                    }
                    if(execvp(cmd[j].command, cmd[j].args) == -1) {
                        printf("Da um comando válido filha da puta\n");
                        exit(0);
                    }
                } else {
                    if(j < qtdPipes)
                        close(fd[j][1]);
                    waitpid(pid, NULL, 0);
                }
            }
            for (int k = 0; k < qtdPipes; k++) {
                close(fd[k][0]);
            }

            for(int j =0; j<qtdCmds; j++) {
                freeComand(&cmd[j]);
            }
            printf("FILHO terminando\n");
            exit(0);
        }
        else{
            waitpid(BACKGROUND, NULL, 0);
            printf("VSH vai continuar\n");
            insereLista(list, BACKGROUND);
        }
    }
    free(command_line);
    for(int j =0; j<qtdCmds; j++) {
        freeComand(&cmd[j]);
    }
    return 1;
}

int readLine(Lista* list){

    tCommand cmd[5];
    int qtdCmds = 0;

    char* command_line, * save;
    size_t bufsize = LINE_MAX;
    command_line = (char*) malloc(bufsize * sizeof(char));
    getline(&command_line, &bufsize, stdin);
    command_line[strlen(command_line)-1] = 0;

    printf("\"%s\"\n", command_line);

    int temPipe = 0;
    for(int i=0; command_line[i] != 0; i++)
        if(command_line[i] == '|'){
            temPipe = 1;
            break;
        }
    printf("TEM PIPE = %d\n", temPipe);
    //    printf("\"%s\"\n", command_line);

    if(temPipe){
//        int VSH[2];
//        pipe(VSH);
        int BACKGROUND = fork();

        if(BACKGROUND == 0){
            printf("RES ANTIGO: %d\n", getsid(getpid()));
           int res = setsid();
//            int res = 1;
            printf("RES = %d\n", res);

//            char * bargs[PATH_MAX] = {"ps", "-Sf", NULL};
//            execvp("ps", bargs);

//            write(VSH[1], &res, sizeof(int));
//            close(VSH[0]);
//            close(VSH[1]);

            if(res != -1){
                printf("VOU CRIAR PIPES\n");

                cmd[qtdCmds].fullCommand = strtok_r(command_line, "|", &save);
                printf("PIPE COMMAND: '%s'\n", cmd[qtdCmds].fullCommand);
                while (cmd[qtdCmds].fullCommand){
                    if(strcmp(cmd[qtdCmds].fullCommand, "armageddon") == 0){
                        printf("SIM\n");
                        free(command_line);
                        return(0);
                    }
                    preencheArgumentos(&cmd[qtdCmds]);
                    qtdCmds++;
                    cmd[qtdCmds].fullCommand = strtok_r(NULL, "|", &save);
                }

//                for (int i=0; i < qtdCmds; i++) printCommand(&cmd[i]);

                int qtdPipes = qtdCmds-1;

                int fd[qtdPipes][2];

                for(int j = 0; j<qtdPipes; j++){
                    if(pipe(fd[j]) < 0){
                        printf("Erro ao abrir pipe\n");
                        printf("I dont fell to good\n");
                        free(command_line);
                        return 1;
                    }
                }
                printf("Sucesso ao abrir os %d pipes para os %d comandos\n", qtdPipes, qtdCmds);
                for (int j = 0; j < qtdCmds; j++) {
                    int pid = fork();
                    if (pid == 0) {
//                        printf("Entrei no comando " BOLD VERMELHO "%s" RESET "\n", cmd[j].command);
                        if (j == 0) {
                            dup2(fd[j][1], STDOUT_FILENO);
                        } else if (j == qtdPipes) {
                            dup2(fd[j - 1][0], STDIN_FILENO);
                        } else {
                            dup2(fd[j - 1][0], STDIN_FILENO);
                            dup2(fd[j][1], STDOUT_FILENO);
                        }
//                        char ta[PATH_MAX] = "\nSetando pipes no comando \"";
//                        strcat(ta, cmd[j].command);
//                        strcat(ta, "\"\n");
//                        strcat(ta, "Argumentos\n");
//                        strcat(ta, cmd[j].args[1]);
//                        strcat(ta, "\n\n");
//                        write(STDOUT_FILENO, ta, sizeof(ta));
//                        char ta[PATH_MAX];
//                        if (fscanf(stdin, "%s", ta) != 1) perror("ERRO\n");
//                        fprintf(stdout, "A saída recebeu isso: %s\n\n", ta);
//                        fflush(stdout);
//                        printf("\n\n"BOLD AMARELO"ATENÇÂO"RESET"\nVOU executar o comando \"%s\"\n\n", cmd[j].fullCommand);

                        for (int k = 0; k < qtdPipes; k++) {
                            close(fd[k][0]);
                            close(fd[k][1]);
                        }

                        if(execvp(cmd[j].command, cmd[j].args) == -1) {
                            printf("Da um comando válido filha da puta\n");
                            exit(0);
                        }
                    } else {
                        if(j < qtdPipes)
                            close(fd[j][1]);
                        if (j == qtdCmds-1) waitpid(pid, NULL, 0);
                    }
                }
                for (int k = 0; k < qtdPipes; k++) {
                    close(fd[k][0]);
                }

                for(int j =0; j<qtdCmds; j++) {
                    freeComand(&cmd[j]);
                }

            }
            //Termina o filho.
            exit(0);
        }
        else{
            printf("[MAIN] To paradão\n");
//            int filhoTrocouSessao;
//            read(VSH[0], &filhoTrocouSessao, sizeof(int));
//            close(VSH[0]);
//            close(VSH[1]);
//            if(filhoTrocouSessao != -1){
////                printf("Vou enfiar na lista\n");
            waitpid(BACKGROUND, NULL, 0);
            insereLista(list, BACKGROUND);
//            }
//            else{
//                printf("Deu erro no meu filho trocar sessão\n");
//            }
        }

    }
    else{
        printf("NAO VOI CRIAR PIPES\n");
        cmd[qtdCmds].fullCommand = strtok_r(command_line, "|", &save);
        printf("FULL COMMAND: '%s'\n", cmd[qtdCmds].fullCommand);
        while (cmd[qtdCmds].fullCommand){
            if(strcmp(cmd[qtdCmds].fullCommand, "armageddon") == 0){
                printf("SIM\n");
                free(command_line);
                return(0);
            }
            preencheArgumentos(&cmd[qtdCmds]);
            qtdCmds++;
            cmd[qtdCmds].fullCommand = strtok_r(NULL, "|", &save);
        }

//        printCommand(cmd);

        int pid = fork();
        if(pid == 0){
            if(execvp(cmd[0].command, cmd[0].args) == -1){
                printf("Da um comando válido filha da puta\n");
                exit(0);
            }
        }
        else{
            waitpid(pid, NULL, 0);
        }
    }

    free(command_line);
    for(int j =0; j<qtdCmds; j++) {
        freeComand(&cmd[j]);
    }
    return 1;

}

void run_shell(Lista* list) {

    do{
        printLineCommand();
    } while (readLine2(list));

}