#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* The signal handler isn't allowed to do anything except
 * access this variable and re-invoke signal().
 */
volatile sig_atomic_t alarm_flag = 0;

/* Prototype for signal handler */
void alarm_handler (int sig) {
    alarm_flag = sig;
    printf("We are in alarm handler");
}


int main (void) {
  // Call signal() to set up a handler for SIGALRM
  // void (*signal(int signo, void (*func )(int)))(int);
    signal(SIGALRM, alarm_handler);

    // Call alarm() to have the alarm go off in a few seconds
    alarm(5);

    while (!alarm_flag) {
        puts("Waiting for an alarm");
    }

  return 0;
}