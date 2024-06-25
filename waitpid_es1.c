//Autore: Michele Ginolfi
//Info: LAB Lezione 4 - 27/10/2021

//#include <sys/wait.h>
//pid_t waitpid (pid_t pid, int* statloc, int options);

/* waitpid ottiene in statloc lo stato di terminazione del figlio specificato
in pid, il processo padre si blocca in attesa o meno secondo il contenuto
di options. waitpid restituisce il processID se OK, -1 in caso di errore. */

//pid == -1 aspetta per qualunque processo figlio (analogo di wait)
//pid > 0 aspetta il figlio che ha processID uguale al valore di pid
/* pid == 0 aspetta un qualsiasi figlio che ha processgroupID uguale a quello
che ha chiamato waitpid */
/* pid < -1 aspetta un qualsiasi figlio che ha processgroupID uguale al
valore assoluto di pid */

//waitpid restituirà errore se il processo o il processgroup non esistono

/* options serve a controllare ulteriormente waitpid, può essere 0 (nessuna
opzione), oppure ad esempio uguale a WNOHANG, in questo caso waitpid non
bloccherà il chiamante se il figlio specificato da pid non è già terminato
ma restituirà 0. */

/* In generale, con la funzione wait il processo si blocca in attesa se tutti
i figli sono in esecuzione, ritorna immediatamente con lo stato di un figlio,
ritorna immediatamente con un errore se non ha figli. */

/* waitpid, al contrario di wait, permette di aspettare uno specifico
processo e provvede una versione non-blocking di wait. */

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
      //termina figlio1
      waitpid(value, &status, 0);
      //termina figlio2
      waitpid(value2, &status, 0);

      printf("\n");
      printf("PROCESSO PADRE\nPID figlio 1: %d PID figlio 2: %d\n", value, value2);
      printf("\nFigli terminati.\n");
      printf("\n");
    }
  }

  return 0;
}
