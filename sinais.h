//
// Created by fernando on 28/04/2021.
//

#ifndef T1_SO_SINAIS_H
#define T1_SO_SINAIS_H

void signalHandler(int sig);
void comando(int sig);
void setSigactionForeground(struct sigaction* act, int pid);
void resetSigaction(struct sigaction* act);
void setSigactionMain(struct sigaction* act);
void setSigactionSIGUSR(struct sigaction* act);
void zeca(int sig);

#endif //T1_SO_SINAIS_H
