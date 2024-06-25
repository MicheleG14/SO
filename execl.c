//Autore: Michele Ginolfi
//Info: LAB Lezione 5 - 03/11/2021

/* La funzione fork di solito è utilizzata per creare un nuovo processo,
detto processo figlio. Il figlio potrebbe dover eseguire un programma diverso
da quello del padre, e potrà farlo chiamando una delle funzioni di exec. 
Dopo la chiamata ad una funzione di exec, lo spazio indirizzi del figlio sarà
completamente rimpiazzato dal nuovo programma, senza modificare il suo PID. */

/* Dunque, una chiamata di exec reinizializza un processo: il text segment
(segmento istruzioni) e lo user data segment (segmento dati utente) cambiano
per l'esecuzione di un nuovo programma. Il segmento dati di sistema rimane
invece invariato. */

//#include <unistd.h>
//int execl(const chat *pathname, const chat *arg0, ... /* (char* )0 */ );
//int execv(const char *pathname, char *const argv[]);
//int execle(const char *pathname, const char *arg0, ... /* (char *)0, char *const envp[] */ );
//int execlp(const char *filename, const char *arg0, ... /* (char *)0 */ );
//int execvp(const char *filename, char *const argv[]);
//int fexecve(int fd, char *const argv[], char *const envp[]);

//exec restituisce -1 se c'è un errore, nulla altrimenti

/* Le lettere finali delle 7 funzioni indicano gli argomenti delle funzioni
stesse: l indica che la funzione avrà una lista di argomenti, invece la lettera
v indica un vettore argv[]. Quindi, le funzioni execlp, execl, execle
richiederanno che gli argomenti sulla linea di comando per il nuovo programma
siano specificati come argomenti separati della funzione. Per le altre 3
funzioni sarà necessario passara l'indirizzo di un array di puntato agli
argomenti sulla linea di comando del nuovo programma. */

/* La lettera p (execlp, execvp), indica che la funzione prende come argomento
un nome di file ed utilizza la variabile d'ambiente PATH per cercare la posizione
nel file system del file eseguibile. Se non vi è p allora sarà indicato il
pathname completo del file. La lettera e (execle, execve) indica che la funzione
prende un envp[] array invece di usare le variabili d'ambiente correnti. */

/* In alcune versioni di UNIX solo execve è una system call, le altre sono
funzioni di libreria che successivamente chiamano execve. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  //frase da stampare
  printf("\nSopra la panca\n");

  //invoca echo che stampa su schermo le stringhe
  execl("/bin/echo", "echo", "la", "capra", "campa", "\n", NULL);

  //istruzione saltata a cause della sostituzione dello spazio di indirizzi
  printf("Prova prova\n");
}


