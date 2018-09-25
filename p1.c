#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t staticVar = getpid();

    while (1) {
        sleep(3);
        printf("Address: %X; Value: %d\n", &staticVar, staticVar);
    }
    
}