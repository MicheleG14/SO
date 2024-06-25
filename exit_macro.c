//Autore: Michele Ginolfi
//Info: LAB Lezione 6 - 10.11.2021

/* E' necessario conoscere la rappresentazione di status, lo standard Posix.1
prevede delle macro (definite nell'header del file <sys/wait.h>) per l'analisi
dello stato di terminazione. In particolare: 
- WIFEXITED(status) restituisce vero, se il processo figlio è terminato
volontariamente e in questo caso la macro WEXITSTATUS(status) restituisce lo
stato di terminazione.
- WIFSIGNALED(status) restituisce vero, se il processo figlio è terminato
involontariamente e in questo la caso WTERMSIG(status) restituisce il numero
dell'interruzione SW che ha causato l'interruzione. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int pid, status;

    //crea un nuovo processo figlio
    pid = fork();

    //termina il processo figlio
    if(pid == 0) {
        printf("\nPROCESSO FIGLIO\nSto per terminare.\n");
        exit(0);
    }
    else {
        //padre controlla stato di terminazione del figlio e stampa prompt
        pid = wait(&status);
        printf("\nTermina il figlio con PID %d.\n", pid);

        //stampa un prompt in caso di terminazione volontaria
        if(WIFEXITED(status)) {
            printf("\nTerminazione volontaria del processo %d con stato %d.\n\n", pid, WEXITSTATUS(status));
        }
        //stampa un prompt in caso di terminazione involontaria
        else {
            printf("\nTerminazione involontaria del processo %d a causa del segnale %d.\n", pid, WTERMSIG(status));
        }
    }
}