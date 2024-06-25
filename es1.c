//Autore: Michele Ginolfi
//Info: LAB Lezione 3 - 20/10/2021

/* Un processo P crea due figli ed aspetta la terminazione di entrambi.
Il primo figlio stampa sullo schermo un messaggio indicando il proprio PID ed
il PID del padre, poi termina. Il secondo figlio stampa sullo schermo la somma
del proprio PID + il PID del padre e poi termina. Dopo la terminazione dei due
figli, P stampa sullo schermo un messaggio indicando il PID dei due figli ed
il fatto che sono terminati, poi termina. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int value, value2, status;

  //creazione del primo processo figlio
  value = fork();

  //verifica l'esecuzione della prima fork
  if(value < 0) {
    fprintf(stderr, "\nErrore nella creazione del processo!\n");
    exit(1);
  }

  //stampa i PID del processo padre e figlio, poi termina
  if(value == 0) {
    printf("\n");
    printf("PROCESSO FIGLIO 1\nPID padre: %d PID figlio: %d\n", getppid(), getpid());
    exit(0);
  }

  //controllo al processo padre
  if(value > 0) {
    // creazione del secondo processo figlio
    value2 = fork();

    // verifica l'esecuzione della seconda fork
    if(value2 < 0) {
      fprintf(stderr, "\nErrore nella creazione del secondo processo!\n");
      exit(1);
    }

    //stampa i PID del processo padre e figlio, poi la loro somma, infine termina
    if(value2 == 0) {
      printf("\nPROCESSO FIGLIO 2\nPID padre: %d PID figlio: %d\n", getppid(), getpid());
      printf("Somma PID: %d\n", getpid()+getppid());
      exit(0);
    }
    //stampa i PID dei processi figli e ne notifica la terminazione
    else {
      //termina i due processi figli
      wait(&status);
      wait(&status);

      printf("\n");
      printf("PROCESSO PADRE\nPID figlio 1: %d PID figlio 2: %d\n", value, value2);
      printf("\nFigli terminati.\n");
      printf("\n");
    }
  }

  return 0;
}
