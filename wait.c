//Autore: Michele Ginolfi
//Info: LAB Lezione 3 - 20/10/2021

/* Quando un processo termina, il kernel manda al padre il segnale SIGCHLD,
il padre, per default, può ignorare il segnale oppure lanciare una funzione
(signal handler). In ogni caso il padre può chiedere informazioni sullo stato
di uscita del figlio. */

//#include <sys/wait.h>
//pid_t wait (int* statloc);
//wait ottiene in statloc lo stato di terminazione del figlio
//wait restituisce il processID se OK, -1 in caso di errore

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int pid1, pid2, pid3, status;

  //il padre crea un figlio
  pid1 = fork();

  if(pid1 == 0){
    //mette in attesa il figlio1 per 4 secondi
    sleep(4);
  }
  else {
    //il padre crea un secondo figlio
    pid2 = fork();

    if (pid2 == 0) {
      //mette in attesa il figlio2 per 1 secondo
      sleep(1);
    }
    else {
      //il padre crea un terzo figlio
      pid3 = fork();

      if (pid3 == 0) {
        //mette in attesa il figlio3 per 2 secondi
        sleep(2);
      }
      else {
        printf("\n");
        printf("Termina il figlio con PID %d\n", wait(&status)); //oppure wait(NULL)
        printf("Termina il figlio con PID %d\n", wait(&status));
        printf("Termina il figlio con PID %d\n", wait(&status));
        printf("\n");
      }
    }
  }
}
