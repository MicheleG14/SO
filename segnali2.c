//Autore: Michele Ginolfi
//Info: LAB Lezione 8 - 25/11/2021

//#include <unistd.h>
//unsigned int sleep(unsigned int secs);

/* Il processo che chiama sleep dorme finché il numero di secondi indicato è
trascorso oppure interviene un segnale e il signal handler ritorna. Nel primo
caso restituisce 0, altrimenti il numero di secondi mancanti. */

//include <stdlib.h>
//void abort(void);

/* Non ritorna mai, invia il segnale SIGABRT al segnale che la invoca. */

//#include <unistd.h>
//unsigned int alarm(unsigned int secs);

/* Fa partire un conto alla rovescia di secs secondi, allo scadere al processo
viene inviato SIGALRM. In realtà potrebbero passare più secondi per ritardi di
schedulazione ad esempio. Vi è un'unica sveglia per processo, quindi se alla
chiamata di alarm vi era un'altra sveglia precedentemente caricata verrà 
risettata e verrà restituito il numero di secondi mancanti alla sveglia
precedente. Se seconds è 0 la sveglia precedente è cancellata e non si invia
SIGALRM. Restituisce 0 o il numero di secondi mancanti alla sveglia
precedentemente saltata. */

//#include <unistd.h>
//int pause(void);

/* pause sospende l'esecuzione finché non interviene un segnale ed il signal
handler ritorna. Restituisce -1 con errno settato a EINTTR. */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void nullfcn() {}

int sleep2(int secs) {
    if(signal(SIGALRM, nullfcn) == SIG_ERR) {
        printf("\nErrore di sistema: SIGALRM!\n");
        exit(1);
    }
    alarm(secs);
    pause();
}

int main() {
    printf("\nSleep2 per 2 secondi\n");
    sleep2(2);
    
    printf("\nSleep2 per 1 secondi\n");
    sleep2(1);

    printf("\nSleep2 per 4 secondi\n");
    sleep2(4);

    printf("\n");
}