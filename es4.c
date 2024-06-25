//Autore: Michele Ginolfi
//Info: LAB Lezione 6 - 10.11.2021


/* Scrivere un piccolo programma C che, utilizzando le system call studiate
simuli una piccola shell. In particolare, il processo associato al programma
dovrà ciclicamente:
- stampare un prompt;
- leggere il comando inserito dall'utente dopo il prompt;
- creare un nuovo figlio, che dovrà eseguire il comando utente;
- aspettare la terminazione del figlio, utilizzando waitpid.

I comandi da eseguire potranno avere fino a 5 argomenti. */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    char command[100];
    int val;

    do {
        //argomenti da prendere in input (max 5)
        char *c1 = NULL, *c2 = NULL, *c3 = NULL, *c4 = NULL, *c5 = NULL, *c6 = NULL;

        //indice iniziale stringa comandi
        int start = 0;
        //indice numero di argomenti
        int flag = 0;

        printf("SHELL: ");
        fgets(command, 100, stdin);

        //scorrimento stringa command
        for(int i = 0; command[i] != '\0'; i++) {
            if(isspace(command[i])) {
                for(int j = 0; start < i; start++, j++) {
                    switch(flag) {
                        case 0: if(isspace(command[start])) {
                            start++;
                        } 
                        if(j==0) {
                            c1 = malloc(10);
                        }
                        c1[j] = command[start];
                        break;

                        case 1: if(isspace(command[start])) {
                            start++;
                        } 
                        if(j==0) {
                            c2 = malloc(10);
                        }
                        c2[j] = command[start];
                        break;

                        case 2: if(isspace(command[start])) {
                            start++;
                        } 
                        if(j==0) {
                            c3 = malloc(10);
                        }
                        c3[j] = command[start];
                        break;

                        case 3: if(isspace(command[start])) {
                            start++;
                        } 
                        if(j==0) {
                            c4 = malloc(10);
                        }
                        c4[j] = command[start];
                        break;

                        case 4: if(isspace(command[start])) {
                            start++;
                        } 
                        if(j==0) {
                            c5 = malloc(10);
                        }
                        c5[j] = command[start];
                        break;

                        case 5: if(isspace(command[start])) {
                            start++;
                        } 
                        if(j==0) {
                            c6 = malloc(10);
                        }
                        c6[j] = command[start];
                        break;
                    }
                }
                flag++;
            }
        }

        val = fork();

        if(val < 0) {
            printf("\nErrore durante la creazione del processo!\n");
            exit(-1);
        }
        //se la execlp restituisce ed il comando non è exit, allora errore
        else if(!val) {
            if(execlp(c1,c1,c2,c3,c4,c5,c6, NULL) < 0 && strcmp("exit\n", command)) {
                printf("\nComando non esistente!\n");
                exit(-1);
            }
        }
        else if(val) {
            waitpid(val, NULL, 0);
        }
    } while(strcmp(command, "exit\n"));
}