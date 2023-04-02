#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid, wpid;
    int status;

    pid = fork();
    int i = 12;
    if (pid == 0) { 
        printf("Child process started.\n");
        sleep(3);
        printf("Child process completed.\n");
        exit(10);
    } else if (pid > 0) { 
        printf("Parent process waiting for child process to complete.\n");
        wpid = waitpid(pid, &status, 0);
        if (wpid == -1) {
            perror("waitpid() failed");
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(status)) {
            printf("Child process exited with status %d.\n", WEXITSTATUS(status));
        } else {
            printf("Child process did not exit normally.\n");
        }
    } else { // fork error
        perror("fork() failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <semaphore.h>
// #include <unistd.h>
// #include <sys/wait.h>

// int main() {
//     sem_t *sem;
//     pid_t pid;

//     sem = sem_open("/my_semaphore", O_CREAT | O_EXCL, 0644, 1);
//     if (sem == SEM_FAILED) {
//         perror("Failed to open semaphore");
//         exit(EXIT_FAILURE);
//     }

//     pid = fork();
//     if (pid == -1) {
//         perror("Failed to fork");
//         exit(EXIT_FAILURE);
//     } else if (pid == 0) {
//         // Child process
//         printf("Child process waiting for semaphore...\n");
//         sem_wait(sem);
//         printf("Child process acquired semaphore\n");
//          int j = 0;
//        while(j < 10)
//        {
//         printf("child %d\n",j);
//         j++; 
//        }
//         // Access shared resource...
//         sem_post(sem);
//         printf("Child process released semaphore\n");
//         exit(EXIT_SUCCESS);
//     } else {
//         // Parent process
//         printf("Parent process waiting for semaphore...\n");
//         sem_wait(sem);
//         printf("Parent process acquired semaphore\n");
//         // Access shared resource...
//        int i = 0;
//        while(i < 10)
//        {
//         printf("man %d\n",i);
//         i++; 
//        }
//         sem_post(sem);
         
//         printf("Parent process released semaphore\n");
//         wait(NULL);
//     }

//     sem_unlink("/my_semaphore");
//     sem_close(sem);
//     return 0;
// }
