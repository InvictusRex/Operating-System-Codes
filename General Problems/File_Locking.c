#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void lock_file(int fd, short lock_type) {
    struct flock lock;
    lock.l_type = lock_type;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Error locking file");
        exit(1);
    }

    printf("File locked (type: %s) by process %d.\n",
           (lock_type == F_RDLCK) ? "Read" : "Write", getpid());
}

void unlock_file(int fd) {
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    if (fcntl(fd, F_SETLK, &lock) == -1) {
        perror("Error unlocking file");
        exit(1);
    }

    printf("File unlocked by process %d.\n", getpid());
}

int main() {
    int fd = open("shared_file.txt", O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        lock_file(fd, F_RDLCK);
        printf("Process %d is reading the file...\n", getpid());
        sleep(3);
        unlock_file(fd);
    } else {
        lock_file(fd, F_WRLCK);
        printf("Process %d is writing to the file...\n", getpid());
        sleep(5);
        unlock_file(fd);
        wait(NULL);
    }

    close(fd);
    return 0;
}
