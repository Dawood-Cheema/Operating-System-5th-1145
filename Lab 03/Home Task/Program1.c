#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        // child: replace child process with top
        execlp("top", "top", (char *)NULL);
        perror("execlp"); // runs only if execlp fails
        exit(1);
    } else {
        // parent waits until child (top) exits
        wait(NULL);
        printf("Child (top) exited — parent finishing\n");
    }
    return 0;
}
