//Autore: Michele Ginolfi
//Info: LAB Lezione 2 - 13.10.2021

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//#include <unistd.h>
//pid_t fork(void);
//fork restituisce 0 se eseguito dal processo figlio
//fork restituisce il processID del figlio se eseguito dal processo padre
//fork restituisce -1 se c'è un errore

int main() {
  int value;

  value = fork();

  if(value == 0) {
    printf("\nPROCESSO FIGLIO\nValore di ritorno di fork: %d\n\n", value);
    //restituisce 0
  }
  else {
    printf("\nPROCESSO PADRE\nValore di ritorno di fork: %d\n", value);
    //restituisce PID figlio
  }

  if(value < 0) {
    fprintf(stderr, "\nErrore durante la creazione del processo!\n");
    exit(1);
  }

  return 0;
}
