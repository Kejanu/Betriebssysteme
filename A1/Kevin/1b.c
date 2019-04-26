#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {

    int choice;
    printf("Your choice (Number): ");
    if (scanf("%d", &choice) < 1) {
        printf("Error while executing scanf\n");
        return 1;
    }

    // size 5, cause text + terminating 0
    char* answer[5];


    switch (choice) {
        case 1:
            *answer = "ps";
            break;
        case 2:
            *answer = "date";
            break;
        case 3:
            *answer = "ls";
            break;
        default:
            printf("Your choice wasn't in the specified range. Program exiting...\n");
            return 1;
    }

    printf("Your choice was: %s\n", *answer);

    int pid = fork();
    if (pid == 0) {
        // This is the child process
        printf("I'm the child process, pid=%d\n", getpid());

        // Exec the "ls" command
        execlp(*answer, *answer, (char *)NULL);
    } else if (pid == -1) {
        // Oh crap, our fork() failed!
    } else {
        // This is the parent process
        printf("I'm the parent process, pid=%d\n", getpid());
        int status;
        wait(&status);
        printf("%d", status);
    }
}
