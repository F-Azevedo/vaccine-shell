//
// Created by fernando on 25/04/2021.
//

#ifndef T1_SO_SHELL_H
#define T1_SO_SHELL_H

#include "Lista.h"

void printLineCommand();
void run_shell(Lista *, struct sigaction*);
void setSigactionMain(struct sigaction* act);

#endif //T1_SO_SHELL_H
