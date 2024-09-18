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

    // Move the file pointer to offset 10
    off_t offset = lseek(fd, 10, SEEK_SET);
    if (offset < 0) {
        perror("lseek failed");
        close(fd);
        return 1;
    }

    printf("File pointer moved to offset: %ld\n", offset);

    // Close the file
    close(fd);

    return 0;
}
