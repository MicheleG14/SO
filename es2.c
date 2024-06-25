//Autore: Michele Ginolfi
//Info: LAB Lezione 4 - 27/10/2021

/* Un processo P crea due figli ed aspetta la terminazione di entrambi.
Il primo figlio stampa sullo schermo un messaggio indicando il proprio PID, e
poi stampa sullo schermo i numeri da 1 a 50 e poi termina. Il secondo figlio
stampa sullo schermo i PID del padre e poi stampa sullo schermo i numeri da 101
a 150 e poi termina. Dopo la terminazione dei due figli P stampa sullo
schermo un messaggio indicando il PID dei due figli ed il fatto che sono
terminati e poi termina. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int value, value2, status, i, j;

  //creazione del primo processo figlio
  value = fork();

  //verifica corretta esecuzione della prima fork
  if(value < 0) {
    fprintf(stderr, "\nErrore durante la creazione del processo!\n");
    exit(1);
  }

  //controllo al processo figlio1
  //stampa i PID del processo padre e figlio, stampa i numeri da 1 a 50,
  //poi termina
  if(value == 0) {
    printf("\n");
    printf("PROCESSO FIGLIO 1\nPID padre: %d PID figlio 1: %d\n", getppid(), getpid());

    printf("\nStampa i numeri da 1 a 50:\n");
    for(i = 0; i < 51; i++) {
      printf("%d ", i);
    }

    printf("\n");

    exit(0);
  }

  //controllo al processo padre
  if(value > 0) {
    //creazione del secondo processo figlio
    value2 = fork();

    //verifica corretta esecuzione della seconda fork
    if(value2 < 0) {
      fprintf(stderr, "\nErrore durante la creazione del processo!\n");
      exit(1);
    }

    //controllo al processo figlio2
    //stampa i PID del processo padre e figlio, stampa i numeri da 101 a 150,
    //poi termina
    if(value2 == 0) {
      printf("\n");
      printf("PROCESSO FIGLIO 2\nPID padre: %d PID figlio 2:%d\n", getppid(), getpid());

      printf("\nStampa i numeri da 101 a 150:\n");
      for(j = 101; j < 151; j++) {
        printf("%d ", j);
      }

      printf("\n");

      exit(0);
    }
    //controllo al processo padre
    //termina i figli, stampa i PID e ne notifica la terminazione
    else {
      waitpid(value, &status, 0);
      waitpid(value2, &status, 0);

      printf("\n");
      printf("PROCESSO PADRE\nPID figlio 1: %d PID figlio 2: %d\n", value, value2);
      printf("\nFigli terminati.\n");
      printf("\n");
    }
  }
}
