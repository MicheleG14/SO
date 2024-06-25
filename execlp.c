//Autore: Michele Ginolfi
//Info: LAB Lezione 5 - 03/11/2021

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  //frase da stampare
  printf("\nSopra la panca\n");

  //invoca echo (con la variabile d'ambiente) che stampa su schermo le stringhe
  execlp("echo", "echo", "la", "capra", "campa", "\n", NULL);

  //istruzione saltata
  printf("Prova prova\n");
}