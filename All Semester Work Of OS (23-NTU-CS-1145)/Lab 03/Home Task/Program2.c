#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        // Child: replace this process with the "date" command
        execlp("date", "date", (char *)NULL);
        perror("execlp"); // only runs if execlp fails
        return 1;
    } else {
        // Parent: wait for child, then print
        wait(NULL);
        printf("Child finished\n");
    }
    return 0;
}
