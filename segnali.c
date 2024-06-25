//Autore: Michele Ginolfi
//Info: LAB Lezione 7 - 17.11.2021

/* Un segnale è un interrupt software che permette di gestire eventi
asincroni, come ad esempio un comando inviato da terminale da parte di un
utente o la fine prematura di un processo per un errore di sistema. Un segnale
può essere generato in qualsiasi istante, a volte da un processo utente, più
spesso dal kernel a seguito di un errore software o hardware o comunque di
un evento eccezionale. */

/* Ogni segnale ha un nome che comincia con SIG (ad es. SIGABORT, SIGALARM) a
cui viene associato una costante intera positiva definita in <signal.h>.
I segnali non contengono informazioni aggiuntive, in particolare chi li riceve
non può scoprire l'identità di chi li manda. */

/* Il segnale è un evento asincrono, esso può arrivare in un qualunque momento
ad un processo. E' importante notare che non sempre verrà eseguita un'azione in
seguito alla ricezione di un segnale. Vi sono azioni di default che vengono
compiute, oppure il processo può scegliere di ignorare il segnale o gestirlo in
maniera diversa dal default. */

/* Le azioni associate ad un segnale sono le seguenti:
- Ignorare il segnale: tranne che per SIGKILL e SIGSTOP che non possono essere
ignorati, perché sono il modo in cui il superuser può terminare o stoppare
momentaneamente qualsiasi processo.
- Catturare il segnale: equivale ad associare all'occorrenza del segnale
l'esecuzione di una funzione utente. Ad esempio se il segnale SIGTERM viene
catturato possiamo voler ripulire tutti i file temporanei generati dal processo.
- Eseguire l'azione di default associata: terminazione del processo per la
maggior parte dei segnali. */

/* SIGABRT: questo segnale è generato da una chiamata alla system call abort.
Il processo quindi termina abnormalmente.
SIGCHLD: ogni volta che un processo termina o viene fermato questo segnale
viene inviato al padre. Per default il padre lo ignora, se invece il padre
vuole intercettarlo chiamerà una delle wait per ottenere il PID del processo
ed il suo termination status.
SIGCONT: è inviato ad un processo che è fermo per fare riprendere la sua
esecuzione.
SIGFPE: (floating point exception) viene inviato quando c'è una divisione per 0.
SIGILL: (illegal instruction) viene inviato quando l'hardware individua una
istruzione illegale, come ad esempio istruzioni su floating point in un sistema
che non ha hardware per gestire la virgola.
SIGINT: (interrupt) viene inviato quando viene premuto il tasto di interrupt
(DELETE o CTRL-C), in genere termina un processo a run time.
SIGALRM: generato dalla system call alarm.
SIGQUIT: simile a SIGINT, ma viene inviato quando viene digitato CTRL-/,
generando un core file, una immagine in memoria del processo che può essere
utilizzata per debugging.
SIGKILL: è uno dei due segnali che non possono essere ignorati, termina il
processo che lo riceve.
SIGSEGV: (segment violation) il processo ha fatto riferimento ad un indirizzo
che non è nel suo spazio indirizzi.
SIGSTOP: ferma un processo, non può essere ignorato.
SIGSYS: (invalid system call) il processo ha eseguito una istruzione che il
kernel ha interpretato come system call senza però fornire i parametri adeguati.
SIGTERM: il segnale di terminazione inviato per default dalla chiamata kill.
SIGBUS, SIGEMT, SIGIOT, SIGTRAP: inviati quando sussistono problemi hardware,
la loro interpretazione è system dependent.
SIGUSR1, SIGUSR2: (user defined signals) possono essere utilizzati e definiti
dall'utente, a volte sono utilizzati in maniera impropria per la comunicazione
tra processi. */

//#include <signal.h>
//void (*signal(int signo, void (*func)(int)))(int);

//signal restituisce il puntatore al precedente gestore del segnale se OK
//signal restituisce SIG_ERR in caso di errore

/* signal prende due argomenti: il nome del segnale signo ed il puntatore alla
funzione func da eseguire come azione da associare all'arrivo di signo (nuovo
signal handler). Restituisce il puntatore ad una funzione che prende come 
argomento un intero (e non restituisce niente) che rappresenta il puntatore
al precedente signal handler. In caso di errore restituisce SIG_ERR (cioè -1). */

/* Il valore di func può essere:
- SIG_IGN per ignorare il segnale
- SIG_DFL  per settare l'azione associata al suo default
- L'indirizzo di una funzione che sarà eseguita quando il segnale occorre
L'azione del padre su un segnale viene ereditata dai figli. */

#include <sys/types.h>
#include <signal.h>
int kill (pid_t pid, int signo);
int raise (int signo);

//kill e raise restituiscono 0 se OK, -1 in caso di errore

//kill e raise inviano il segnale signo specificato come argomento
//raise(signo) = kill(getpid(), signo)

/* kill manda un segnale ad un processo o ad un gruppo di processi specificato
da pid. raise consente ad un processo di mandare un segnale a se stesso.
Se il valore di pid è:
> 0, il segnale è inviato al processo con PID pid.
== 0, il segnale è inviato a tutti i processi il cui processgroupID è uguale a
quello del processo che invia il segnale.
< 0, il segnale è inviato a tutti i processi il cui processgroupID è uguale al
valore assoluto di pid. */

/* Il superuser può inviare segnali a qualsiasi processo, ma un processo
necessita degli appositi permessi per inviare segnali ad un altro processo.
I segnali non sono consigliabili come forma di comunicazione tra processi. Un
messaggio inviato sotto forma di segnale può essere perso se quel segnale è
momentaneamente disattivato dal processo che lo deve ricevere. Inoltre, i
segnali interrompono qualsiasi cosa viene eseguita in quel momento e questo
potrebbe causare problemi. */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//funzione che conferma l'esecuzione dei segnali
void sig_usr(int signo) {
  //se il parametro è SIGUSR1 o SIGUSR2 conferma l'esecuzione dei
  //segnali stampando un avviso
  if(signo == SIGUSR1) {
    printf("\nRicevuto SIGUSR1\n");
  }
  else if(signo == SIGUSR2) {
    printf("\nRicevuto SIGUSR2\n");
  }
}

int main() {
  //rileva eventuali errori ed esegue la funzione
  //quando viene rilevato il segnale
  if(signal(SIGUSR1, sig_usr) == SIG_ERR) {
    fprintf(stderr, "\nErrore di sistema: SIGUSR1\n");
  }

  if(signal(SIGUSR2, sig_usr) == SIG_ERR) {
    fprintf(stderr, "\nErrore di sistema: SIGUSR2\n");
  }

  while(-1) {
    pause();
  }
}