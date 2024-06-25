//Autore: Michele Ginolfi
//Info: LAB Lezione 2 - 13.10.2021

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

//#include <unistd.h>
//pid_t getpid(void);
//getpid restituisce il processID del processo chiamante
//pid_t getppid(void);
//getppid restituisce il processID del processo padre

int main() {
  printf("\nPID del processo chiamante: %d\n", getpid());

  printf("PID del processo padre: %d\n\n", getppid());

  return 0;
}
