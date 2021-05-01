//
// Created by fernando on 28/04/2021.
//

#ifndef T1_SO_SINAIS_H
#define T1_SO_SINAIS_H

void zeca(int sig);
void passaProFilho(int sig);
void signalHandler(int sig);
void resetSigaction(struct sigaction* act);
void setSigactionPadraoVSH(struct sigaction* act);
void setSigactionSIGUSR(struct sigaction* act);
void setSigactionForeground(struct sigaction* act);
void setSigactionVSH(struct sigaction* act, int pid);

#endif //T1_SO_SINAIS_H
