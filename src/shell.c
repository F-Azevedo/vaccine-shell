// Created by igor on 16/04/2021
// in T1_SHELL_C as shell.c 
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <limits.h>

#include "sinais.h"
#include "shell.h"
#include "Corzinha.h"
#include "Lista.h"

#define ARG_MAX 3

// Definição da struct comando.
typedef struct COMANDO{
    char* fullCommand;      // É o comando até o pipe.
    char* command;          // Só o comando.
    char** args;            // Argumentos do comando.
    int nargs;              //Número de argumentos do comando.
}tCommand;

// Função para personalizar o print da command line da VSH.
char * removePath(char * path){
    int i;
    for (i = (int)strlen(path)-1; path[i] != '/'; i--);
    char * new = malloc(sizeof(char) * (strlen(path)-i));
    for (int j=i+1; j <= strlen(path); j++){
        new[j-(i+1)] = path[j];
    }
    return new;
}

// Funçao para imprimir a command line.
void printLineCommand(){
    char cwd[PATH_MAX];
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
    // Preenche o comando.
    cmd->command = strtok_r(cmd->fullCommand, " ", &save);

    char    * arg = strtok_r(NULL, " ", &save),
            * all_args[ARG_MAX];

    // Descobre os argumentos do comando e armazena em um vetor auxiliar.
    for (; arg; cmd->nargs++, arg=strtok_r(NULL, " ", &save))
        all_args[cmd->nargs] = arg;

    // Cria vetor de argumentos na estrutura tCommand com tamanho correto para ser aceito pelo exec.
    cmd->args = malloc(sizeof(char*) * (cmd->nargs + 2));

    // Coloca o primeiro argumento como o nome do comando.
    cmd->args[0] = cmd->command;
    // Copia os argumentos.
    for (int i=1; i <= cmd->nargs; i++){
        cmd->args[i] = all_args[i-1];
    }
    // Coloca último argumento como NULL.
    cmd->args[cmd->nargs + 1] = NULL;

}

// Libera os argumentos do comando.
void freeCommandArgs(tCommand* cmd) {
    free(cmd->args);
}

// Função para executar um comando que for passado como foreground.
void foreground(tCommand cmd[5], Lista* list, struct sigaction* act){
    int pid = fork();
    if(pid == 0){
        // Filho da VSH que vai executar o comando.

        // Seta o tratador de sinais do filho foregorund para ingnorar SIGUSR 1 e 2.
        setSigactionForeground(act);

        // Filho executa o comando.
        if(execvp(cmd[0].command, cmd[0].args) == -1){
            printf("Da um comando válido robertinha\n");
            exit(0);
        }
    }
    else{
        // VSH muda seu tratador de sinais para passar os sinais recebidos por teclado para o filho.
        setSigactionVSH(act, pid);

        int status;
        // VSH espera o filho terminar ou ser suspenso.
        waitpid(pid, &status, WUNTRACED);

        // Se o filho foi suspenso, adiciona o filho na lista.
        if (WIFSTOPPED(status)){
            insereLista(list, pid);
        }

        // Reseta o Sigaction da VSH.
        resetSigaction(act);
        // Seta o Sigaction da VSH para o padrão.
        setSigactionPadraoVSH(act);
    }
}

// Função para liberar os pipes criados.
void liberaPipes(int pipes[][2], int type, int qtd) {
    for (int k = 0; k < qtd; k++) close(pipes[k][type]);
}

void background(tCommand cmd[5], int qtdCmds, Lista* list){
    int BACKGROUND = fork();

    if(BACKGROUND == 0){
        // Filho da VSH que vai executar as coisas em background.
        struct sigaction act;

        // Seta seu Sigaction para fazer o que é esperado dos processos
        // em background com relação aos sinais SIGUSR 1 e 2.
        setSigactionSIGUSR(&act);

        // Cria uma nova seção, e consequentemente um novo grupo.
        int newSession = setsid();

        if(newSession == -1){ perror("Erro na criação de uma nova sessão"); exit(1);}

        // Cria a quantidade de pipes adequada para a execução dos comandos.
        int qtdPipes = qtdCmds-1;
        int fd[qtdPipes][2];

        // Abre os pipes.
        for(int j = 0; j<qtdPipes; j++)
            if(pipe(fd[j]) < 0){ printf("Erro ao abrir pipe\n"); exit(1); }

        // Executa os comandos, sequencialmente.
        for (int j = 0; j < qtdCmds; j++) {
            // O processo cria um filho para executar o comando de indice j.
            int pid = fork();
            if (pid == 0) {

                // Se o comando for o primeiro, escreve sua saída no pipe de indice j.
                if (j == 0) {
                    dup2(fd[j][1], STDOUT_FILENO);
                }
                // Se o comando é o último, lê a entrada do pipe de indice j-1.
                else if (j == qtdPipes) {
                    dup2(fd[j - 1][0], STDIN_FILENO);
                }
                // Do contrário, lê a entrada do pipe indice j-1 e escreve sua saída no pipe indice j.
                else {
                    dup2(fd[j - 1][0], STDIN_FILENO);
                    dup2(fd[j][1], STDOUT_FILENO);
                }

                // Libera os todos os pipes.
                liberaPipes(fd, 0, qtdPipes);
                liberaPipes(fd, 1, qtdPipes);

                // Executa o comando.
                if(execvp(cmd[j].command, cmd[j].args) == -1) {
                    printf("Da um comando válido robertinha\n");
                    exit(0);
                }
            } else {
                // O pai fecha os pipes de escrita que não serão necessários aos próximos filhos.
                if(j < qtdPipes) close(fd[j][1]);
                int status;

                // Espera o filho acabar.
                waitpid(pid, &status, 0);

                // Chega se o filho terminou devido aos sinais SIGUSR, se sim,
                // chama o mesmo para matar seu grupo.
                if(status == 10 || status == 12) raise(SIGUSR1);
            }
        }

        // Libera todos pipes de leitura.
        liberaPipes(fd, 0, qtdPipes);

        // Libera os argumentos do comando.
        for(int j =0; j<qtdCmds; j++) freeCommandArgs(&cmd[j]);

        //Termina o filho.
        exit(0);
    }
    else{
        // VSH insere o pid do filho na lista.
        insereLista(list, BACKGROUND);
    }
}

// Função que define em que plano o comando deve ser executado.
void defineGround(tCommand cmd[5], int qtdCmds, Lista* list, struct sigaction* act){

    // Se receber 0 ou 1 comando executa em foreground.
    if(qtdCmds < 2) foreground(cmd, list, act);
    // Se receber 2 ou mais executa em background.
    else background(cmd, qtdCmds, list);

}

// Função para ler a linha, armazenar os comandos nas estruturas e chamar as funções para executar.
// Retorna 1 se for para continuar e 0 se for para terminar o programa.
int readLine(Lista* list, struct sigaction* act){
    tCommand cmd[5];
    int qtdCmds = 0;

    // Se prepara e faz a leitura da linha do STDIN.
    char* command_line, * save;
    size_t bufsize = LINE_MAX;
    command_line = (char*) malloc(bufsize * sizeof(char));
    getline(&command_line, &bufsize, stdin);
    command_line[strlen(command_line)-1] = 0;

    // Faz a leitura dos comandos da linha.
    cmd[qtdCmds].fullCommand = strtok_r(command_line, "|", &save);

    while (cmd[qtdCmds].fullCommand){
        // Se o comando for armageddon executa o mesmo.
        if(strcmp(cmd[qtdCmds].fullCommand, "armageddon") == 0){
            armageddon(list, getpid());
            free(command_line);
            return 0;
        }
        // Se o comando for libera moita executa o mesmo.
        else if(strcmp(cmd[qtdCmds].fullCommand, "liberamoita") == 0){
            liberaMoita(list);
            free(command_line);
            return 1;
        }
        preencheArgumentos(&cmd[qtdCmds]);
        qtdCmds++;
        cmd[qtdCmds].fullCommand = strtok_r(NULL, "|", &save);
    }

    // Define o plano do comando e executa.
    defineGround(cmd, qtdCmds, list, act);

    // Libera as estruturas usadas.
    free(command_line);
    for(int j =0; j<qtdCmds; j++) {
        freeCommandArgs(&cmd[j]);
    }
    return 1;
}

// Função que roda a shell.
void run_shell(Lista* list, struct sigaction* act) {
    do printLineCommand();
    while (readLine(list, act));
}