//Autore: Michele Ginolfi
//Info: LAB Lezione 6 - 10/11/2021

/* Un processo può terminare involontariamente se si sono verificati tentativi
di azioni illegali oppure a causa di interruzioni tramite segnali. Un processo
può anche terminare volontariamente, mediante una chiamata alla funzione exit()
oppure dopo l'esecuzione dell'ultima istruzione che gli è stata assegnata.
Quando un processo termina in uno di questi due modi, la sua immagine verrà
salvata automaticamente nel file core. */

/* Per ogni processo in esecuzione, il kernel esegue il codice del processo e
determina lo stato di terminazione: se normale, lo stato è l'argomento di
exit(); altrimenti il kernel genera uno stato di terminazione che indica il
motivo "anormale". In entrambi i casi, il padre del processo ottiene questo 
stato da wait o waitpid. */

//#include <stdlib.h>
//void exit(int status);

/* La system call exit() prevede un parametro status, mediante il quale il
sistema operativo può comunicare al padre del processo le informazioni sul
suo stato di terminazione, come ad esempio l'esito della sua esecuzione.
Questa funzione chiude tutti i descrittori di file di un processo, dealloca
le sue aree codice, dati e stack e quindi fa terminare il processo. E' sempre
una chiamata senza ritorno (void). */

/* In caso di terminazione di un figlio, la variabile status raccoglie il suo
stato di terminazione. Nell'ipotesi che lo stato sia un intero a 16 bit, se
il byte meno significativo di status è zero, il più significativo rappresenta
lo stato di terminazione (terminazione volontaria). In caso contrario, il byte
meno significativo di status descrive il segnale che ha terminato il figlio
(terminazione involontaria). */

/* Se un figlio termina prima del padre, allora il padre può ottenere lo stato
di terminazione del figlio con wait o waitpid. Se un padre termina prima del
figlio, allora il processo init diventa il nuovo padre. Se un figlio termina
prima del padre ma il padre non recupera il suo stato tramite una wait o
waitpid, il figlio diventa uno zombie. Uno zombie non ha aree codice, dati o
stack allocate, quindi non usa molte risorse di sistema ma continua ad avere
un PCB nella tabella dei processi. Quindi, la presenza di molti processi zombie
potrebbe costringere l'amministratore ad intervenire. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int pid, status;

    //crea un nuovo processo figlio
    pid = fork();

    //termina il processo figlio
    if(pid == 0) {
        printf("\nPROCESSO FIGLIO\nSto per terminare.\n");
        exit(0);
    }
    else {
        //padre controlla stato di terminazione del figlio e stampa prompt
        pid = wait(&status);
        printf("\nTermina il figlio con PID %d.\n", pid);

        //stampa un prompt in caso di terminazione volontaria
        if((char)status == 0) {
            printf("\nTerminazione volontaria con stato %d.\n\n", status>>8);
        }
        //stampa un prompt in caso di terminazione involontaria
        else {
            printf("\nTerminazione involontaria per segnale %d.\n", (char) status);
        }
    }
}