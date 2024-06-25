//Autore: Michele Ginolfi
//Info: LAB Lezione 7 - 17/11/2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// funzione che gestisce il segnale
void ctrlc_handler(int signo) {
  char answer[512];

  // stampa un prompt di avviso del segnale ricevuto
  printf("\n\n%s%d\n\n%s", "Ricevuto segnale di interruzione! Segnale = ", signo, "Vuoi continuare (c) o uscire (q)? ");
  scanf("%s", answer);

  // continua se l'utente inserisce c
  if(*answer == 'c') {
    signal(SIGINT, ctrlc_handler);
  }
  // si ferma se l'utente inserisce q
  else {
    printf("\nProcesso terminato dall'utente.\n");
    exit(1);
  }
}

// funzione che trova i numeri di Fibonacci
int fib(int n) {
  if(n <= 1) {
    return n;
  }
  else {
    return (fib(n-1) + fib(n-2));
  }
}

int main() {
  int i;

  printf("Il segnale SIGINT equivale a %d\n", SIGINT);

  // rileva l'esecuzione del segnale SIGINT
  signal(SIGINT, ctrlc_handler);

  // stampa i numeri di Fibonacci
  for(i = 0; i < 50; ++i) {
    printf("fib(%2d) = %d\n", i, fib(i));
  }
}
