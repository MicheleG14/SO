//Autore: Michele Ginolfi
//Info: LAB Lezione 8 - 25/11/2021

/* Scrivere un programma C che implementi la seguente situazione. Un processo P
crea due figli ed aspetta la terminazione di entrambi, i due figli saranno in 
esecuzione concorrente. Il primo figlio scriverà i primi 30 numeri di Fibonacci
e poi terminerà. In presenza di un CTRL-C immesso da tastiera dovrà scrivere a 
schermo il proprio PID e continuare la sua esecuzione. Il secondo figlio
scriverà i primi 20 fattoriali ed in presenza di un CTRL-C immesso da tastiera
dovrà chiedere all'utente se deve continuare la sua esecuzione o terminare e
regolarsi di conseguenza. Dopo la terminazione dei due figli il padre P stamperà
sullo schermo un messaggio indicando il PID dei due figli ed il fatto che sono
terminati e poi terminerà. */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

long fatt(long n) {
    if(n == 0) {
        return (1);
    }
    else {
        return (n * fatt(n-1));
    }
}

int fib(int n) {
    if(n <= 1) {
        return (n);
    }
    else {
        return (fib(n-1) + fib(n-2));
    }
}

void ctrlc_handler1(int sig) {
    char answer[512];

    printf("\n\nSegnale di interruzione %d!\n\n", sig);
    printf("\nFIGLIO 1\nPID: %d\n", getpid());
}

void ctrlc_handler2(int sig) {
    char answer[512];

    printf("\n\nSegnale di interruzione %d!\nVuoi continuare (c) o uscire (q)? ", sig);
    scanf("%s", answer);

    if(*answer == 'c') {
        printf("\nFIGLIO2\nContinuo:\n\n");
    }
    else{
        printf("\nProcesso terminato dall'utente.\n");
        exit(0);
    }
}

int main() {
    int i, value, value2;

    value = fork();

    if(value < 0) {
        fprintf(stderr, "\nErrore durante la creazione del processo!\n");
        exit(1);
    }

    //FIGLIO1
    if(value == 0) {
        signal(SIGINT, ctrlc_handler1);

        printf("\nStampo i primi 30 numeri di Fibonacci:\n");

        for(i = 0; i < 30; ++i) {
            printf("fib(%d) = %d\n", i, fib(i));
        }

        printf("\nStampo i primi 20 numeri fattoriali:\n");

        exit(0);
    }

    //PADRE
    if(value > 0) {
        value2 = fork();

        if(value2 < 0) {
            fprintf(stderr, "\nErrore durante la creazione del processo!\n");
            exit(1);
        }

        //FIGLIO2
        if(value2 == 0) {
            signal(SIGINT, ctrlc_handler2);

            for(i = 0; i < 20; ++i) {
                sleep(1);
                printf("fatt(%d) = %ld\n", i, fatt(i));
            }

            exit(0);
        }
        else {
            signal(SIGINT, SIG_IGN);
            wait(NULL);
            wait(NULL);

            printf("\n");
            printf("PROCESSO PADRE\nPID figlio1: %d\nPID figlio2: %d\n", value, value2);
            printf("\nFigli terminati.\n");
            printf("\n");

            exit(0);
        }
    }
}