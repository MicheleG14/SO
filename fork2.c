//Autore: Michele Ginolfi
//Info: LAB Lezione 2 - 13.10.2021

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//programma che crea 2 processi figli

int main() {
  int value, value2;

  value = fork();

  if(value == 0) {
    printf("\nPRIMO PROCESSO FIGLIO\nValore di ritorno di fork: %d\n", value);
    //restituisce 0
  }
  else {
    printf("\nPROCESSO PADRE\nValore di ritorno di fork: %d\n", value);
    //restituisce PID figlio
  }

  /* Fondamentale è distinguere il processo che deve effettuare le operazioni
  infatti, dato che fork eseguito dal padre restituisce un intero > 0
  ovvero il PID del figlio, è possibile utilizzare if(value > 0) per dare
  il controllo al processo padre che dovrà generare un altro figlio */

  if(value > 0) {
    value2 = fork();

    if(value2 == 0) {
      printf("\nSECONDO PROCESSO FIGLIO\nValore di ritorno di fork: %d\n\n", value2);
      //restituisce 0
    }
    else {
      printf("\nPROCESSO PADRE\nValore di ritorno di fork: %d\n", value2);
      //restituisce PID figlio
    }
  }

  if(value < 0) {
    fprintf(stderr, "\nErrore durante la creazione del processo!\n");
    exit(-1);
  }

  return 0;
}
