#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    // Open a file
    int fd = open("file.txt", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open file");
        return 1;
    }

    // Duplicate the file descriptor
    int fd_copy = fcntl(fd, F_DUPFD, 0);
    if (fd_copy < 0) {
        perror("Failed to duplicate file descriptor");
        close(fd);
        return 1;
    }

    printf("Original FD: %d, Duplicated FD: %d\n", fd, fd_copy);

    // Close both file descriptors
    close(fd);
    close(fd_copy);

    return 0;
}
