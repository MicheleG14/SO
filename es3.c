//Autore: Michele Ginolfi
//Info: LAB Lezione 5 - 03/11/2021

/* Scrivere un piccolo programma C che, utilizzando le system call studiate
simuli una piccola shell. In particolare, il processo associato al programma
dovrà ciclicamente:
- stampare un prompt "%";
- leggere il comando inserito dall'utente dopo il prompt;
- creare un nuovo figlio, che dovrà eseguire il comando utente;
- aspettare la terminazione del figlio.

I comandi da eseguire non avranno argomenti. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char buf[512];
  int pid, status;

  //prompt
  printf("%%");

  //esegue finchè non viene terminato
  while(fgets(buf, 512, stdin) != NULL) {
    //sostituisce newline con NULL
    buf[strlen(buf) - 1] = 0;

    //controlla se c'è stato un errore nella fork
    if((pid = fork()) < 0) {
      fprintf(stderr, "Errore nella creazione del processo!\n");
      exit(1);
    }
    //il processo figlio esegue il comando richiesto
    else if(pid == 0){
      //controlla se è possibile eseguire il comando
      if(execlp(buf, buf, (char *) 0) == -1) {
        fprintf(stderr, "Impossibile eseguire il comando %s\n", buf);
        exit(1);
      }
      exit(0);
    }
    //il padre termina il processo figlio
    if((pid = waitpid(pid, &status, 0)) < 0) {
      fprintf(stderr, "Errore nel comando waitpid!\n");
      exit(1);
    }
    printf("%%");
  }
  exit(0);
}